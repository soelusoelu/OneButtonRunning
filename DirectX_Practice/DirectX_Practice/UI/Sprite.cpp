#include "Sprite.h"
#include "Texture.h"
#include "../System/GameSystem.h"
#include "../System/Renderer.h"
#include <cassert>

Sprite::Sprite(const std::string& fileName, Vector2 size) :
    mSize(size),
    mPosition(Vector2::zero),
    mScale(Vector2::one),
    mColor(ColorPalette::white, 1.f),
    mUV(0.f, 0.f, 1.f, 1.f) {
    mTexture = Singleton<GameSystem>::instance().getRenderer()->getTexture(fileName);
}

Sprite::~Sprite() {
}

void Sprite::draw() {
    mWorld = Matrix4::createScale(mSize.x * mScale.x * mUV.width, mSize.y * mScale.y * mUV.height, 1.f);
    mWorld *= Matrix4::createTranslation(Vector3(mPosition.x, mPosition.y, 0.f));

    mTexture->draw(mWorld, mColor, mUV);
}

void Sprite::setPosition(Vector2 pos) {
    mPosition = pos;
}

void Sprite::setScale(Vector2 scale) {
    mScale = scale;
}

void Sprite::setColor(Vector3 color) {
    mColor.r = color.x;
    mColor.g = color.y;
    mColor.b = color.z;
}

void Sprite::setColor(float r, float g, float b) {
    mColor.r = r;
    mColor.g = g;
    mColor.b = b;
}

void Sprite::setAlpha(float alpha) {
    mColor.a = alpha;
}

void Sprite::setUV(Rect uv) {
    assert(0.f <= uv.left || uv.left <= 1.f);
    assert(0.f <= uv.top || uv.top <= 1.f);
    assert(0.f <= uv.width || uv.width <= 1.f);
    assert(0.f <= uv.height || uv.height <= 1.f);

    mUV = uv;
}

void Sprite::setUV(float l, float t, float w, float h) {
    assert(0.f <= l || l <= 1.f);
    assert(0.f <= t || t <= 1.f);
    assert(0.f <= w || w <= 1.f);
    assert(0.f <= h || h <= 1.f);

    mUV.left = l;
    mUV.top = t;
    mUV.width = w;
    mUV.height = h;
}
