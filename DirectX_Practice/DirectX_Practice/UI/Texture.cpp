#include "Texture.h"
#include "../Direct3D11.h"
#include "../Game.h"
#include "../Shader/Shader.h"
#include "../System/GameSystem.h"
#include "../System/Renderer.h"

Texture::Texture(Vector2 size) :
    mSize(size),
    mPosition(Vector2::zero),
    mScale(Vector2::one),
    mColor(Vector3::one, 1.f),
    mUV(0.f, 0.f, 1.f, 1.f) {
}

Texture::~Texture() {
    SAFE_RELEASE(mTexture);
    SAFE_RELEASE(mSampleLinear);
    SAFE_RELEASE(mVertexBuffer);
}

void Texture::init(const std::string& fileName) {
    mDevice = Direct3D11::mDevice;
    mDeviceContext = Direct3D11::mDeviceContext;

    mShader = Singleton<GameSystem>::instance().getRenderer()->getShader(Shader::ShaderType::Texture);

    if (FAILED(createTexture(fileName))) {
        MessageBox(0, L"テクスチャ作成失敗", NULL, MB_OK);
    }
}

void Texture::draw() const {
    //ワールドトランスフォーム（絶対座標変換）
    D3DXMATRIX world;
    D3DXMATRIX scale;
    D3DXMATRIX trans;
    D3DXMatrixScaling(&scale, mSize.x * mScale.x * mUV.width, mSize.y * mScale.y * mUV.height, 1.f);
    D3DXMatrixTranslation(&trans, mPosition.x, mPosition.y, 0.f);
    world = scale * trans;
    //ビュートランスフォーム（視点座標変換）
    D3DXMATRIX mView;
    D3DXVECTOR3 vEyePt(0.f, 0.f, -1.f); //カメラ（視点）位置
    D3DXVECTOR3 vLookatPt(0.f, 0.f, 0.f);//注視位置
    D3DXVECTOR3 vUpVec(0.f, 1.f, 0.f);//上方位置
    D3DXMatrixLookAtLH(&mView, &vEyePt, &vLookatPt, &vUpVec);
    //プロジェクション
    D3DXMATRIX mProj;
    D3DXMATRIX mProjTrans;
    D3DXMatrixScaling(&mProj, 2.f / Game::WINDOW_WIDTH, -2.f / Game::WINDOW_HEIGHT, 1.f);
    D3DXMatrixTranslation(&mProjTrans, -1.f, 1.f, 0.f);
    mProj *= mProjTrans;

    //使用するシェーダーの登録	
    mDeviceContext->VSSetShader(mShader->getVertexShader(), NULL, 0);
    mDeviceContext->PSSetShader(mShader->getPixelShader(), NULL, 0);

    //シェーダーのコンスタントバッファーに各種データを渡す
    D3D11_MAPPED_SUBRESOURCE pData;
    TextureShaderConstantBuffer cb;
    if (SUCCEEDED(mDeviceContext->Map(mShader->mConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
        //ワールド、カメラ、射影行列を渡す
        D3DXMATRIX m = world * mView * mProj;
        D3DXMatrixTranspose(&m, &m);
        cb.mWVP = m;
        cb.mColor = mColor;
        cb.mRect = mUV;
        //cb.mColor.w = alpha;
        memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
        mDeviceContext->Unmap(mShader->mConstantBuffer0, 0);
    }
    //このコンスタントバッファーを使うシェーダーの登録
    mDeviceContext->VSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    mDeviceContext->PSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);

    //頂点インプットレイアウトをセット
    mDeviceContext->IASetInputLayout(mShader->getVertexLayout());
    //プリミティブ・トポロジーをセット
    mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //テクスチャーをシェーダーに渡す
    mDeviceContext->PSSetSamplers(0, 1, &mSampleLinear);
    mDeviceContext->PSSetShaderResources(0, 1, &mTexture);
    //プリミティブをレンダリング
    mDeviceContext->Draw(4, 0);
}

void Texture::setPosition(Vector2 pos) {
    mPosition = pos;
}

void Texture::setScale(Vector2 scale) {
    mScale = scale;
}

void Texture::setColor(Vector3 color) {
    mColor.r = color.x;
    mColor.g = color.y;
    mColor.b = color.z;
}

void Texture::setColor(float r, float g, float b) {
    mColor.r = r;
    mColor.g = g;
    mColor.b = b;
}

void Texture::setAlpha(float alpha) {
    mColor.a = alpha;
}

void Texture::setUV(Rect uv) {
    mUV = uv;
}

void Texture::setUV(float l, float t, float w, float h) {
    mUV.left = l;
    mUV.top = t;
    mUV.width = w;
    mUV.height = h;
}

HRESULT Texture::createTexture(const std::string & fileName) {
    if (!mVertexBuffer) {
        //バーテックスバッファー作成
        TextureVertex vertices[] =
        {
            Vector3(0.f, 0.f, 0.f), Vector2(0.f, 0.f), //左上
            Vector3(1.f, 0.0f, 0.f), Vector2(1.f, 0.f), //右上
            Vector3(0.f, 1.f, 0.f), Vector2(0.f, 1.f), //左下
            Vector3(1.f, 1.f, 0.f), Vector2(1.f, 1.f), //右下
        };
        D3D11_BUFFER_DESC bd;
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = sizeof(TextureVertex) * 4;
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = 0;
        bd.MiscFlags = 0;

        D3D11_SUBRESOURCE_DATA InitData;
        InitData.pSysMem = vertices;
        if (FAILED(mDevice->CreateBuffer(&bd, &InitData, &mVertexBuffer))) {
            return E_FAIL;
        }
        //バーテックスバッファーをセット
        UINT stride = sizeof(TextureVertex);
        UINT offset = 0;
        mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    }
    //テクスチャー用サンプラー作成
    D3D11_SAMPLER_DESC SamDesc;
    ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
    SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    mDevice->CreateSamplerState(&SamDesc, &mSampleLinear);
    //テクスチャー作成
    setTextureDirectory();
    if (FAILED(D3DX11CreateShaderResourceViewFromFileA(mDevice, fileName.c_str(), NULL, NULL, &mTexture, NULL))) {
        return E_FAIL;
    }

    return S_OK;
}

ID3D11Buffer* Texture::mVertexBuffer = nullptr;

//何故かだめ
//ワールドトランスフォーム（絶対座標変換）
//Matrix4 world;
//Matrix4 scale;
//Matrix4 trans;
//scale = Matrix4::createScale(mSize.x * mScale.x * mUV.width, mSize.y * mScale.y * mUV.height, 1.f);
//trans = Matrix4::createTranslation(Vector3(mPosition, 0.f));
//world = scale * trans;
////ビュートランスフォーム（視点座標変換）
//Matrix4 mView;
//Vector3 vEyePt(0.f, 0.f, -1.f); //カメラ（視点）位置
//Vector3 vLookatPt(0.f, 0.f, 0.f);//注視位置
//Vector3 vUpVec(0.f, 1.f, 0.f);//上方位置
//mView = Matrix4::createLookAt(vEyePt, vLookatPt, vUpVec);
////プロジェクション
//Matrix4 mProj;
//mProj = Matrix4::createScale(2.f / Game::WINDOW_WIDTH, -2.f / Game::WINDOW_HEIGHT, 1.f);
//trans = Matrix4::createTranslation(Vector3(-1.f, 1.f, 0.f));
//mProj *= trans;
//
////使用するシェーダーの登録	
//mDeviceContext->VSSetShader(mShader->getVertexShader(), NULL, 0);
//mDeviceContext->PSSetShader(mShader->getPixelShader(), NULL, 0);
//
////シェーダーのコンスタントバッファーに各種データを渡す
//D3D11_MAPPED_SUBRESOURCE pData;
//TextureShaderConstantBuffer cb;
//if (SUCCEEDED(mDeviceContext->Map(mShader->mConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
//    //ワールド、カメラ、射影行列を渡す
//    Matrix4 m = world * mView * mProj;
//    m.transpose();
//    cb.mWVP = m;
//    cb.mColor = mColor;
//    cb.mRect = mUV;
//    //cb.mColor.w = alpha;
//    memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
//    mDeviceContext->Unmap(mShader->mConstantBuffer0, 0);
//}
