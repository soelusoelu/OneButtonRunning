#include "Mesh.h"
#include "SphereCollisionComponent.h"
#include "../Camera/Camera.h"
#include "../Device/Renderer.h"
#include "../Shader/Shader.h"
#include "../System/Direct3D11.h"
#include "../System/Game.h"

Mesh::Mesh() {
    ZeroMemory(this, sizeof(Mesh));
}

Mesh::~Mesh() {
    SAFE_DELETE_ARRAY(mMaterial);
    SAFE_DELETE_ARRAY(mIndexBuffer);
    SAFE_RELEASE(mVertexBuffer);
    SAFE_RELEASE(mSampleLinear);
    SAFE_RELEASE(mTexture);
    SAFE_DELETE_ARRAY(mMyVertexBuffer);

    //メモリリークの原因
    for (int i = 0; i < mNumMaterial; i++) {
        SAFE_DELETE_ARRAY(mVertexIndex[i]);
    }
    SAFE_DELETE_ARRAY(mVertexIndex);

    SAFE_DELETE_ARRAY(mNumFaceInMaterial);
    SAFE_DELETE_ARRAY(mCoord);
}

HRESULT Mesh::init(const std::string& fileName) {
    mDevice = Direct3D11::mDevice;
    mDeviceContext = Direct3D11::mDeviceContext;
    mRasterizerState = Direct3D11::mRasterizerState;
    mRasterizerStateBack = Direct3D11::mRasterizerStateBack;

    mShader = Singleton<Renderer>::instance().getShader(ShaderType::Mesh);
    if (FAILED(LoadStaticMesh(fileName))) {
        MessageBox(0, L"メッシュ作成失敗", NULL, MB_OK);
        return E_FAIL;
    }

    return S_OK;
}

void Mesh::draw(Matrix4 world, float alpha) const {
    mDeviceContext->RSSetState(mRasterizerState);
    RendererMesh(world, alpha);
    mDeviceContext->RSSetState(mRasterizerStateBack);
    RendererMesh(world, alpha);
}

void Mesh::createSphere(Sphere* sphere) const {
    //バウンディングスフィア作成
    D3DXVECTOR3 center;
    D3DXComputeBoundingSphere(mCoord, mNumVert, sizeof(D3DXVECTOR3), &center, &sphere->mRadius);
    sphere->mCenter.x = center.x;
    sphere->mCenter.y = center.y;
    sphere->mCenter.z = center.z;
}

HRESULT Mesh::LoadMaterialFromFile(const std::string& fileName, Material** ppMaterial) {
    //マテリアルファイルを開いて内容を読み込む
    FILE* fp = NULL;
    fopen_s(&fp, fileName.c_str(), "rt");
    char key[110] = { 0 };
    D3DXVECTOR4 v(0, 0, 0, 1);

    //マテリアル数を調べる
    mNumMaterial = 0;
    while (!feof(fp)) {
        //キーワード読み込み
        fscanf_s(fp, "%s ", key, sizeof(key));
        //マテリアル名
        if (strcmp(key, "newmtl") == 0) {
            mNumMaterial++;
        }
    }
    Material* pMaterial = new Material[mNumMaterial];

    //本読み込み	
    fseek(fp, SEEK_SET, 0);
    INT iMCount = -1;

    while (!feof(fp)) {
        //キーワード読み込み
        fscanf_s(fp, "%s ", key, sizeof(key));
        //マテリアル名
        if (strcmp(key, "newmtl") == 0) {
            iMCount++;
            fscanf_s(fp, "%s ", key, sizeof(key));
            strcpy_s(pMaterial[iMCount].szName, key);
        }
        //Ka　アンビエント
        if (strcmp(key, "Ka") == 0) {
            fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
            pMaterial[iMCount].Ka = v;
        }
        //Kd　ディフューズ
        if (strcmp(key, "Kd") == 0) {
            fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
            pMaterial[iMCount].Kd = v;
        }
        //Ks　スペキュラー
        if (strcmp(key, "Ks") == 0) {
            fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
            pMaterial[iMCount].Ks = v;
        }
        //map_Kd　テクスチャー
        if (strcmp(key, "map_Kd") == 0) {
            fscanf_s(fp, "%s", &pMaterial[iMCount].szTextureName, sizeof(pMaterial[iMCount].szTextureName));
            //テクスチャーを作成
            if (FAILED(D3DX11CreateShaderResourceViewFromFileA(mDevice, pMaterial[iMCount].szTextureName, NULL, NULL, &pMaterial[iMCount].pTexture, NULL))) {
                return E_FAIL;
            }
        }
    }
    fclose(fp);

    *ppMaterial = pMaterial;

    return S_OK;
}

HRESULT Mesh::LoadStaticMesh(const std::string& fileName) {
    float x, y, z;
    int v1 = 0, v2 = 0, v3 = 0;
    int vn1 = 0, vn2 = 0, vn3 = 0;
    int vt1 = 0, vt2 = 0, vt3 = 0;
    DWORD dwVCount = 0;//読み込みカウンター
    DWORD dwVNCount = 0;//読み込みカウンター
    DWORD dwVTCount = 0;//読み込みカウンター
    DWORD dwFCount = 0;//読み込みカウンター

    char key[200] = { 0 };
    //OBJファイルを開いて内容を読み込む
    setAssetsDirectory();
    FILE* fp = NULL;
    fopen_s(&fp, fileName.c_str(), "rt");

    //事前に頂点数、ポリゴン数を調べる
    while (!feof(fp)) {
        //キーワード読み込み
        fscanf_s(fp, "%s ", key, sizeof(key));
        //マテリアル読み込み
        if (strcmp(key, "mtllib") == 0) {
            fscanf_s(fp, "%s ", key, sizeof(key));
            LoadMaterialFromFile(key, &mMaterial);
        }
        //頂点
        if (strcmp(key, "v") == 0) {
            mNumVert++;
        }
        //法線
        if (strcmp(key, "vn") == 0) {
            dwVNCount++;
        }
        //テクスチャー座標
        if (strcmp(key, "vt") == 0) {
            dwVTCount++;
        }
        //フェイス（ポリゴン）
        if (strcmp(key, "f") == 0) {
            mNumFace++;
        }
    }

    //一時的なメモリ確保（頂点バッファとインデックスバッファ）
    mMyVertexBuffer = new MeshVertex[mNumVert];
    mCoord = new D3DXVECTOR3[mNumVert];
    D3DXVECTOR3* pvNormal = new D3DXVECTOR3[dwVNCount];
    D3DXVECTOR2* pvTexture = new D3DXVECTOR2[dwVTCount];

    //本読み込み	
    fseek(fp, SEEK_SET, 0);
    dwVCount = 0;
    dwVNCount = 0;
    dwVTCount = 0;
    dwFCount = 0;

    while (!feof(fp)) {
        //キーワード 読み込み
        ZeroMemory(key, sizeof(key));
        fscanf_s(fp, "%s ", key, sizeof(key));

        //頂点 読み込み
        if (strcmp(key, "v") == 0) {
            fscanf_s(fp, "%f %f %f", &x, &y, &z);
            mCoord[dwVCount].x = x;
            mCoord[dwVCount].y = y;
            mCoord[dwVCount].z = z;
            dwVCount++;
        }

        //法線 読み込み
        if (strcmp(key, "vn") == 0) {
            fscanf_s(fp, "%f %f %f", &x, &y, &z);
            pvNormal[dwVNCount].x = x;
            pvNormal[dwVNCount].y = y;
            pvNormal[dwVNCount].z = z;
            dwVNCount++;
        }

        //テクスチャー座標 読み込み
        if (strcmp(key, "vt") == 0) {
            fscanf_s(fp, "%f %f", &x, &y);
            pvTexture[dwVTCount].x = -x;//OBJファイルはX成分が逆なので合わせる
            pvTexture[dwVTCount].y = -y;//OBJファイルはY成分が逆なので合わせる
            dwVTCount++;
        }
    }

    //マテリアルの数だけインデックスバッファーを作成
    mIndexBuffer = new ID3D11Buffer*[mNumMaterial];

    //フェイス　読み込み　バラバラに収録されている可能性があるので、マテリアル名を頼りにつなぎ合わせる
    bool boFlag = false;
    int* piFaceBuffer = new int[mNumFace * 3];//３頂点ポリゴンなので、1フェイス=3頂点(3インデックス)
    mVertexIndex = new int*[mNumMaterial];
    mNumFaceInMaterial = new DWORD[mNumMaterial];
    for (DWORD i = 0; i < mNumMaterial; i++) {
        fseek(fp, SEEK_SET, 0);
        dwFCount = 0;

        while (!feof(fp)) {
            //キーワード 読み込み
            ZeroMemory(key, sizeof(key));
            fscanf_s(fp, "%s ", key, sizeof(key));

            //フェイス 読み込み→頂点インデックスに
            if (strcmp(key, "usemtl") == 0) {
                fscanf_s(fp, "%s ", key, sizeof(key));
                if (strcmp(key, mMaterial[i].szName) == 0) {
                    boFlag = true;
                } else {
                    boFlag = false;
                }
            }
            if (strcmp(key, "f") == 0 && boFlag == true) {
                if (mMaterial[i].pTexture != NULL) { //テクスチャーありサーフェイス
                    fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
                } else { //テクスチャー無しサーフェイス
                    fscanf_s(fp, "%d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3);
                }

                piFaceBuffer[dwFCount * 3] = v1 - 1;
                piFaceBuffer[dwFCount * 3 + 1] = v2 - 1;
                piFaceBuffer[dwFCount * 3 + 2] = v3 - 1;
                dwFCount++;
                //頂点構造体に代入
                mMyVertexBuffer[v1 - 1].mPos = mCoord[v1 - 1];
                mMyVertexBuffer[v1 - 1].mNorm = pvNormal[vn1 - 1];
                mMyVertexBuffer[v1 - 1].mTex = pvTexture[vt1 - 1];
                mMyVertexBuffer[v2 - 1].mPos = mCoord[v2 - 1];
                mMyVertexBuffer[v2 - 1].mNorm = pvNormal[vn2 - 1];
                mMyVertexBuffer[v2 - 1].mTex = pvTexture[vt2 - 1];
                mMyVertexBuffer[v3 - 1].mPos = mCoord[v3 - 1];
                mMyVertexBuffer[v3 - 1].mNorm = pvNormal[vn3 - 1];
                mMyVertexBuffer[v3 - 1].mTex = pvTexture[vt3 - 1];
            }
        }
        if (dwFCount == 0) { //使用されていないマテリアル対策
            mIndexBuffer[i] = NULL;
            mNumFaceInMaterial[i] = NULL;
            continue;
        }

        //インデックスバッファーを作成
        D3D11_BUFFER_DESC bd;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(int) * dwFCount * 3;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        bd.MiscFlags = 0;
        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = piFaceBuffer;
        InitData.SysMemPitch = 0;
        InitData.SysMemSlicePitch = 0;
        if (FAILED(mDevice->CreateBuffer(&bd, &InitData, &mIndexBuffer[i]))) {
            return FALSE;
        }
        mMaterial[i].dwNumFace = dwFCount;
        //頂点インデックスデータを保存しておく
        mVertexIndex[i] = new int[dwFCount * 3];
        memcpy(mVertexIndex[i], piFaceBuffer, sizeof(int) * dwFCount * 3);

        mNumFaceInMaterial[i] = dwFCount;
    }
    delete[] piFaceBuffer;
    fclose(fp);

    //バーテックスバッファーを作成
    D3D11_BUFFER_DESC bd;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(MeshVertex) * mNumVert;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;
    D3D11_SUBRESOURCE_DATA InitData;
    InitData.pSysMem = mMyVertexBuffer;
    if (FAILED(mDevice->CreateBuffer(&bd, &InitData, &mVertexBuffer))) {
        return FALSE;
    }

    //一時的な入れ物は、もはや不要
    delete[] pvNormal;
    delete[] pvTexture;

    //テクスチャー用サンプラー作成
    D3D11_SAMPLER_DESC SamDesc;
    ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));

    SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    mDevice->CreateSamplerState(&SamDesc, &mSampleLinear);

    return S_OK;
}

void Mesh::RendererMesh(Matrix4 world, float alpha) const {
    //使用するシェーダーの登録
    mDeviceContext->VSSetShader(mShader->getVertexShader(), NULL, 0);
    mDeviceContext->PSSetShader(mShader->getPixelShader(), NULL, 0);
    //シェーダーのコンスタントバッファーに各種データを渡す
    D3D11_MAPPED_SUBRESOURCE pData;
    if (SUCCEEDED(mDeviceContext->Map(mShader->mConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
        //テクスチャでないの、ほぼ確定でこのif文の中
        SIMPLESHADER_CONSTANT_BUFFER0 sg;
        //ワールド行列を渡す
        sg.mW = world;
        sg.mW.transpose();
        //ワールド、カメラ、射影行列を渡す
        sg.mWVP = world * Singleton<Camera>::instance().getView() * Singleton<Camera>::instance().getProjection();
        sg.mWVP.transpose();
        //ライトの方向を渡す
        sg.vLightDir = Vector4(1.f, -1.f, 1.f, 0.0f);
        //視点位置を渡す
        sg.vEye = Vector4(Singleton<Camera>::instance().getPosition(), 0);

        memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SIMPLESHADER_CONSTANT_BUFFER0));
        mDeviceContext->Unmap(mShader->mConstantBuffer0, 0);
    }
    //このコンスタントバッファーを使うシェーダーの登録
    mDeviceContext->VSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    mDeviceContext->PSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    //頂点インプットレイアウトをセット
    mDeviceContext->IASetInputLayout(mShader->getVertexLayout());
    //プリミティブ・トポロジーをセット
    mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    //バーテックスバッファーをセット
    UINT stride = sizeof(MeshVertex);
    UINT offset = 0;
    mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    //マテリアルの数だけ、それぞれのマテリアルのインデックスバッファ－を描画
    for (DWORD i = 0; i < mNumMaterial; i++) {
        //使用されていないマテリアル対策
        if (mMaterial[i].dwNumFace == 0) {
            continue;
        }
        //インデックスバッファーをセット
        stride = sizeof(int);
        offset = 0;
        mDeviceContext->IASetIndexBuffer(mIndexBuffer[i], DXGI_FORMAT_R32_UINT, 0);

        //マテリアルの各要素をエフェクト（シェーダー）に渡す
        D3D11_MAPPED_SUBRESOURCE pData;
        if (SUCCEEDED(mDeviceContext->Map(mShader->mConstantBuffer1, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
            SIMPLESHADER_CONSTANT_BUFFER1 sg;
            //テクスチャーをシェーダーに渡す
            if (mMaterial[i].szTextureName[0] != NULL) {
                mDeviceContext->PSSetSamplers(0, 1, &mSampleLinear);
                mDeviceContext->PSSetShaderResources(0, 1, &mMaterial[i].pTexture);
                sg.vTexture.x = 1;
            } else {
                sg.vTexture.x = 0;
            }

            sg.vAmbient = mMaterial[i].Ka;//アンビエントををシェーダーに渡す
            sg.vDiffuse = mMaterial[i].Kd;//ディフューズカラーをシェーダーに渡す
            sg.vDiffuse.w = alpha;
            sg.vSpecular = mMaterial[i].Ks;//スペキュラーをシェーダーに渡す
            memcpy_s(pData.pData, pData.RowPitch, (void*)&sg, sizeof(SIMPLESHADER_CONSTANT_BUFFER1));
            mDeviceContext->Unmap(mShader->mConstantBuffer1, 0);
        }
        mDeviceContext->VSSetConstantBuffers(1, 1, &mShader->mConstantBuffer1);
        mDeviceContext->PSSetConstantBuffers(1, 1, &mShader->mConstantBuffer1);
        //プリミティブをレンダリング
        mDeviceContext->DrawIndexed(mMaterial[i].dwNumFace * 3, 0, 0);
    }
}
