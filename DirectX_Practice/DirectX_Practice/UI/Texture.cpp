#include "Texture.h"
#include "../Device/Renderer.h"
#include "../Shader/Shader.h"
#include "../System/Direct3D11.h"
#include "../System/Game.h"

Texture::Texture() {
}

Texture::~Texture() {
    SAFE_RELEASE(mTexture);
    SAFE_RELEASE(mSampleLinear);
    SAFE_RELEASE(mVertexBuffer);
}

void Texture::init(const std::string& fileName) {
    mDevice = Direct3D11::mDevice;
    mDeviceContext = Direct3D11::mDeviceContext;

    mShader = Singleton<Renderer>::instance().getShader(Shader::ShaderType::Texture);

    if (FAILED(createTexture(fileName))) {
        MessageBox(0, L"テクスチャ作成失敗", NULL, MB_OK);
    }
}

void Texture::draw(Matrix4 world, Color color, Rect uv) const {
    //プロジェクション
    D3DXMATRIX proj;
    D3DXMatrixIdentity(&proj);
    //原点をスクリーン左上にするために平行移動
    proj._41 = -1.f;
    proj._42 = 1.f;
    //ピクセル単位で扱うために
    proj._11 = 2.f / Game::WINDOW_WIDTH;
    proj._22 = -2.f / Game::WINDOW_HEIGHT;

    //使用するシェーダーの登録
    mDeviceContext->VSSetShader(mShader->getVertexShader(), NULL, 0);
    mDeviceContext->PSSetShader(mShader->getPixelShader(), NULL, 0);

    //シェーダーのコンスタントバッファーに各種データを渡す
    D3D11_MAPPED_SUBRESOURCE pData;
    if (SUCCEEDED(mDeviceContext->Map(mShader->mConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
        TextureShaderConstantBuffer cb;
        //ワールド、カメラ、射影行列を渡す
        D3DXMATRIX m = world.toD3DXMATRIX();
        D3DXMatrixTranspose(&m, &m);
        cb.mWorld = m;
        D3DXMatrixTranspose(&proj, &proj);
        cb.mProj = proj;
        cb.mColor = color;
        cb.mRect = uv;
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
