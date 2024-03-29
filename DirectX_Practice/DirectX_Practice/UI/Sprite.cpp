﻿#include "Sprite.h"
#include "Texture.h"
#include "../Device/Renderer.h"
#include <cassert>

Sprite::Sprite(const std::string& fileName, const Vector2& size, float z) :
    mSize(size),
    mPosition(Vector2::zero, z),
    mScale(Vector2::one),
    mColor(ColorPalette::white, 1.f),
    mUV(0.f, 0.f, 1.f, 1.f),
    mWorld(Matrix4::identity),
    mWorldUpdateFlag(true),
    mState(SpriteState::Active) {
    mTexture = Singleton<Renderer>::instance().getTexture(fileName);
    mZSortFlag = true;
}

Sprite::~Sprite() = default;

void Sprite::update() {
    //ワールド行列に変更が生じたら
    if (!mWorldUpdateFlag) {
        return;
    }
    mWorldUpdateFlag = false;
    mWorld = Matrix4::createScale(mSize.x * mScale.x * mUV.width, mSize.y * mScale.y * mUV.height, 1.f);
    mWorld *= Matrix4::createTranslation(mPosition);
}

void Sprite::draw() {
    update();
    mTexture->draw(mWorld, mColor, mUV);
}

void Sprite::setPosition(const Vector2& pos) {
    mPosition.x = pos.x;
    mPosition.y = pos.y;
    mWorldUpdateFlag = true;
}

void Sprite::setPrimary(float z) {
    mPosition.z = z;
    mWorldUpdateFlag = true;
    mZSortFlag = true;
}

const Vector2& Sprite::getPosition() const {
    return Vector2(mPosition.x, mPosition.y);
}

const float Sprite::getDepth() const {
    return mPosition.z;
}

void Sprite::setScale(const Vector2& scale) {
    mScale = scale;
    mWorldUpdateFlag = true;
}

const Vector2 & Sprite::getScale() const {
    return mScale;
}

void Sprite::setColor(const Vector3& color) {
    mColor.r = color.x;
    mColor.g = color.y;
    mColor.b = color.z;
    mWorldUpdateFlag = true;
}

void Sprite::setColor(float r, float g, float b) {
    mColor.r = r;
    mColor.g = g;
    mColor.b = b;
    mWorldUpdateFlag = true;
}

void Sprite::setAlpha(float alpha) {
    mColor.a = alpha;
    mWorldUpdateFlag = true;
}

const Color& Sprite::getColor() const {
    return mColor;
}

void Sprite::setUV(const Rect& uv) {
    assert(0.f <= uv.left || uv.left <= 1.f);
    assert(0.f <= uv.top || uv.top <= 1.f);
    assert(0.f <= uv.width || uv.width <= 1.f);
    assert(0.f <= uv.height || uv.height <= 1.f);

    mUV = uv;
    mWorldUpdateFlag = true;
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
    mWorldUpdateFlag = true;
}

const Rect& Sprite::getUV() const {
    return mUV;
}

void Sprite::setState(SpriteState state) {
    mState = state;
}

const SpriteState Sprite::getState() const {
    return mState;
}

const Matrix4& Sprite::getWorld() const {
    return mWorld;
}

const std::shared_ptr<Texture> Sprite::getTexture() const {
    return mTexture;
}

const Vector2& Sprite::getSize() const {
    return mSize;
}

bool Sprite::mZSortFlag = true;
