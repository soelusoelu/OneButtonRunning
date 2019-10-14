#pragma once

#include "../Utility/Math.h"
#include <memory>
#include <string>

class Texture;

class Sprite {
public:
    Sprite(const std::string& fileName, Vector2 size);
    ~Sprite();
    void draw();
    void setPosition(Vector2 pos);
    void setScale(Vector2 scale);
    void setColor(Vector3 color);
    void setColor(float r, float g, float b);
    void setAlpha(float alpha);
    void setUV(Rect uv);
    void setUV(float l, float t, float w, float h);

private:
    Vector2 mSize;
    Vector2 mPosition;
    Vector2 mScale;
    Color mColor;
    Rect mUV;
    std::shared_ptr<Texture> mTexture;
    Matrix4 mWorld;
};

