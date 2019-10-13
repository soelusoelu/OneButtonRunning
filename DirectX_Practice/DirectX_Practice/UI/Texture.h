#pragma once

#include "../DirectXIncLib.h"
#include "../Utility/Math.h"
#include <memory>
#include <string>

//頂点の構造体
struct TextureVertex {
    Vector3 mPos; //位置
    Vector2 mTex; //テクスチャ座標
};

struct TextureShaderConstantBuffer {
    D3DXMATRIX mWVP;
};

class Shader;

class Texture {
public:
    Texture();
    ~Texture();
    void init(const std::string& fileName);
    void draw() const;

private:
    HRESULT createTexture(const std::string& fileName);

    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;

    std::shared_ptr<Shader> mShader;
    ID3D11ShaderResourceView* mTexture; //テクスチャ
    ID3D11SamplerState* mSampleLinear;//テクスチャーのサンプラー
    ID3D11Buffer* mVertexBuffer;

    Vector3 mPosition;
};

