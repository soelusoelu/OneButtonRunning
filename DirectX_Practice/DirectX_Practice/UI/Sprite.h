#pragma once

#include "../Utility/Math.h"
#include <memory>
#include <string>
#include <vector>

enum class SpriteState {
    Active,
    Transparent,
    Dead
};

class Texture;
class UI;

class Sprite : public std::enable_shared_from_this<Sprite> {
public:
    Sprite(UI* owner, const std::string& fileName, Vector2 size, float z);
    ~Sprite();
    void update();
    void setPosition(Vector2 pos);
    const float getDepth() const;
    void setScale(Vector2 scale);
    void setColor(Vector3 color);
    void setColor(float r, float g, float b);
    const Color& getColor() const;
    void setAlpha(float alpha);
    void setUV(Rect uv);
    void setUV(float l, float t, float w, float h);
    const Rect& getUV() const;
    void setPrimary(float z);
    void setState(SpriteState state);
    const SpriteState getState() const;
    const Matrix4& getWorld() const;
    const std::shared_ptr<Texture> getTexture() const;
    bool getSortFlag() const;

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
    bool mZSortFlag;
};

