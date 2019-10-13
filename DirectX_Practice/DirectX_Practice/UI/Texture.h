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
    Color mColor;
    Rect mRect;
};

class Shader;

class Texture {
public:
    Texture(Vector2 size);
    ~Texture();
    void init(const std::string& fileName);
    void draw() const;

    void setPosition(Vector2 pos);
    void setScale(Vector2 scale);
    void setColor(Vector3 color);
    void setColor(float r, float g, float b);
    void setAlpha(float alpha);
    void setUV(Rect uv);
    void setUV(float l, float t, float w, float h);

private:
    HRESULT createTexture(const std::string& fileName);

    ID3D11Device* mDevice;
    ID3D11DeviceContext* mDeviceContext;

    std::shared_ptr<Shader> mShader;
    ID3D11ShaderResourceView* mTexture; //テクスチャ
    ID3D11SamplerState* mSampleLinear;//テクスチャーのサンプラー
    static ID3D11Buffer* mVertexBuffer;

    Vector2 mSize;
    Vector2 mPosition;
    Vector2 mScale;
    Color mColor;
    Rect mUV;
};

