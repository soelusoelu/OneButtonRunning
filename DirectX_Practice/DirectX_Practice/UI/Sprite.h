#pragma once

#include "../Utility/Math.h"
#include <memory>
#include <string>

enum class SpriteState {
    Active,
    Transparent,
    Dead
};

class Texture;

class Sprite {
public:
    Sprite(const std::string& fileName, const Vector2& size, float z);
    ~Sprite();
    void update();
    void draw();
    void setPosition(const Vector2& pos);
    void setPrimary(float z);
    const Vector2& getPosition() const;
    const float getDepth() const;
    void setScale(const Vector2& scale);
    const Vector2& getScale() const;
    void setColor(const Vector3& color);
    void setColor(float r, float g, float b);
    void setAlpha(float alpha);
    const Color& getColor() const;
    void setUV(const Rect& uv);
    void setUV(float l, float t, float w, float h);
    const Rect& getUV() const;
    const Vector2& getSize() const;
    void setState(SpriteState state);
    const SpriteState getState() const;
    const Matrix4& getWorld() const;
    const std::shared_ptr<Texture> getTexture() const;

public:
    static bool mZSortFlag;

private:
    Vector2 mSize;
    Vector3 mPosition;
    Vector2 mScale;
    Color mColor;
    Rect mUV;
    std::shared_ptr<Texture> mTexture;
    Matrix4 mWorld;
    bool mWorldUpdateFlag;
    SpriteState mState;
};

