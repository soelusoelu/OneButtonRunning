#pragma once

#include "../Utility/Math.h"
#include "Component.h"

class Actor;

class TransformComponent : public Component {
public:
    TransformComponent(Actor* owner, int updateOrder = 100);
    virtual void update() override;

    //位置、移動
    const Vector3& getPosition() const;
    void setPosition(const Vector3& pos);
    void translete(const Vector3& translation);

    //角度、回転
    const Quaternion& getRotation() const;
    void setRotation(const Quaternion& rot);
    void setRotation(const Vector3& axis, float angle);
    void rotate(const Vector3& euler); //挙動怪しい
    void rotate(const Vector3& axis, float angle);
    void lookAt(const Vector3& target); //未実装

    //拡縮
    const Vector3& getScale() const;
    void setScale(float scale);
    void setScale(const Vector3& scale);

    //向き
    const Vector3 forward() const;
    const Vector3 right() const;

    bool getRecomputeTransform() const;
    void setRecomputeTransform(bool set);

private:
    Vector3 mPosition;
    Quaternion mRotation;
    Vector3 mScale;
    bool mRecomputeTransform;
};

