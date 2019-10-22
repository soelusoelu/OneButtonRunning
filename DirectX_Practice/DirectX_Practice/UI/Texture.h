#pragma once

#include "../System/DirectXIncLib.h"
#include "../Utility/Math.h"
#include <memory>
#include <string>
#include <vector>

//頂点の構造体
struct TextureVertex {
    Vector3 mPos; //位置
    Vector2 mTex; //テクスチャ座標
};

struct TextureShaderConstantBuffer {
    Matrix4 mWP;
    Color mColor;
    Rect mRect;
};

class Shader;
class Sprite;

class Texture {
public:
    Texture();
    ~Texture();
    void init(const std::string& fileName);
    static void drawAll(std::vector<std::shared_ptr<Sprite>> sprites);
    ID3D11ShaderResourceView* getTexture() const {
        return mTexture;
    }
    ID3D11SamplerState* getSampleLinear() const {
        return mSampleLinear;
    }

private:
    HRESULT createTexture(const std::string& fileName);

    ID3D11ShaderResourceView* mTexture; //テクスチャ
    ID3D11SamplerState* mSampleLinear;//テクスチャーのサンプラー
    static std::shared_ptr<Shader> mShader;
    static ID3D11Buffer* mVertexBuffer;
};

