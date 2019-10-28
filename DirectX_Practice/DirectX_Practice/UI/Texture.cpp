#include "Texture.h"
#include "Sprite.h"
#include "../Device/Renderer.h"
#include "../Shader/Shader.h"
#include "../System/Direct3D11.h"
#include "../System/Game.h"

Texture::Texture() {
}

Texture::~Texture() {
    SAFE_RELEASE(mTexture);
    SAFE_RELEASE(mSampleLinear);
}

void Texture::init(const std::string& fileName) {
    if (!mShader) {
        mShader = Singleton<Renderer>::instance().getShader(ShaderType::Texture);
    }

    if (FAILED(createTexture(fileName))) {
        MessageBox(0, L"テクスチャ作成失敗", NULL, MB_OK);
    }
}

void Texture::end() {
    SAFE_RELEASE(mVertexBuffer);
}

void Texture::drawAll(std::vector<std::shared_ptr<Sprite>> sprites) {
    if (!mVertexBuffer || sprites.size() < 1) {
        return;
    }
    //プロジェクション
    Matrix4 proj = Matrix4::identity;
    //原点をスクリーン左上にするために平行移動
    proj.mat[3][0] = -1.f;
    proj.mat[3][1] = 1.f;
    //ピクセル単位で扱うために
    proj.mat[0][0] = 2.f / Game::WINDOW_WIDTH;
    proj.mat[1][1] = -2.f / Game::WINDOW_HEIGHT;

    //使用するシェーダーの登録
    Direct3D11::mDeviceContext->VSSetShader(mShader->getVertexShader(), NULL, 0);
    Direct3D11::mDeviceContext->PSSetShader(mShader->getPixelShader(), NULL, 0);
    //このコンスタントバッファーを使うシェーダーの登録
    Direct3D11::mDeviceContext->VSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    Direct3D11::mDeviceContext->PSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    //頂点インプットレイアウトをセット
    Direct3D11::mDeviceContext->IASetInputLayout(mShader->getVertexLayout());
    //プリミティブ・トポロジーをセット
    Direct3D11::mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //バーテックスバッファーをセット
    UINT stride = sizeof(TextureVertex);
    UINT offset = 0;
    Direct3D11::mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

    for (const auto& sprite : sprites) {
        if (sprite->getState() != SpriteState::Active) {
            continue;
        }
        //シェーダーのコンスタントバッファーに各種データを渡す
        D3D11_MAPPED_SUBRESOURCE pData;
        if (SUCCEEDED(Direct3D11::mDeviceContext->Map(mShader->mConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
            TextureShaderConstantBuffer cb;
            //ワールド、カメラ、射影行列を渡す
            Matrix4 m = sprite->getWorld();
            m *= proj;
            m.transpose();
            cb.mWP = m;
            cb.mColor = sprite->getColor();
            cb.mRect = sprite->getUV();
            memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
            Direct3D11::mDeviceContext->Unmap(mShader->mConstantBuffer0, 0);
        }
        //テクスチャーをシェーダーに渡す
        auto s = sprite->getTexture()->getSampleLinear();
        auto t = sprite->getTexture()->getTexture();
        Direct3D11::mDeviceContext->PSSetSamplers(0, 1, &s);
        Direct3D11::mDeviceContext->PSSetShaderResources(0, 1, &t);
        //プリミティブをレンダリング
        Direct3D11::mDeviceContext->Draw(4, 0);
    }
}

void Texture::draw(const Matrix4 & world, const Color & color, const Rect & uv) const {
    if (!mVertexBuffer) {
        return;
    }
    //プロジェクション
    Matrix4 proj = Matrix4::identity;
    //原点をスクリーン左上にするために平行移動
    proj.mat[3][0] = -1.f;
    proj.mat[3][1] = 1.f;
    //ピクセル単位で扱うために
    proj.mat[0][0] = 2.f / Game::WINDOW_WIDTH;
    proj.mat[1][1] = -2.f / Game::WINDOW_HEIGHT;

    //使用するシェーダーの登録
    Direct3D11::mDeviceContext->VSSetShader(mShader->getVertexShader(), NULL, 0);
    Direct3D11::mDeviceContext->PSSetShader(mShader->getPixelShader(), NULL, 0);
    //このコンスタントバッファーを使うシェーダーの登録
    Direct3D11::mDeviceContext->VSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    Direct3D11::mDeviceContext->PSSetConstantBuffers(0, 1, &mShader->mConstantBuffer0);
    //頂点インプットレイアウトをセット
    Direct3D11::mDeviceContext->IASetInputLayout(mShader->getVertexLayout());
    //プリミティブ・トポロジーをセット
    Direct3D11::mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    //バーテックスバッファーをセット
    UINT stride = sizeof(TextureVertex);
    UINT offset = 0;
    Direct3D11::mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);

    //シェーダーのコンスタントバッファーに各種データを渡す
    D3D11_MAPPED_SUBRESOURCE pData;
    if (SUCCEEDED(Direct3D11::mDeviceContext->Map(mShader->mConstantBuffer0, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData))) {
        TextureShaderConstantBuffer cb;
        //ワールド、カメラ、射影行列を渡す
        Matrix4 m = world;
        m *= proj;
        m.transpose();
        cb.mWP = m;
        cb.mColor = color;
        cb.mRect = uv;
        memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
        Direct3D11::mDeviceContext->Unmap(mShader->mConstantBuffer0, 0);
    }
    //テクスチャーをシェーダーに渡す
    Direct3D11::mDeviceContext->PSSetSamplers(0, 1, &mSampleLinear);
    Direct3D11::mDeviceContext->PSSetShaderResources(0, 1, &mTexture);
    //プリミティブをレンダリング
    Direct3D11::mDeviceContext->Draw(4, 0);

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
        if (FAILED(Direct3D11::mDevice->CreateBuffer(&bd, &InitData, &mVertexBuffer))) {
            return E_FAIL;
        }
        //バーテックスバッファーをセット
        UINT stride = sizeof(TextureVertex);
        UINT offset = 0;
        Direct3D11::mDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
    }
    //テクスチャー用サンプラー作成
    D3D11_SAMPLER_DESC SamDesc;
    ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
    SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    Direct3D11::mDevice->CreateSamplerState(&SamDesc, &mSampleLinear);
    //テクスチャー作成
    setTextureDirectory();
    if (FAILED(D3DX11CreateShaderResourceViewFromFileA(Direct3D11::mDevice, fileName.c_str(), NULL, NULL, &mTexture, NULL))) {
        return E_FAIL;
    }

    return S_OK;
}

std::shared_ptr<Shader> Texture::mShader = nullptr;
ID3D11Buffer* Texture::mVertexBuffer = nullptr;
