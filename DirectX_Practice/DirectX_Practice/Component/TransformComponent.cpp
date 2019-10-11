#include "TransformComponent.h"

TransformComponent::TransformComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mPosition(Vector3::zero),
    mRotation(Quaternion::identity),
    mScale(Vector3::one),
    mRecomputeTransform(true) {
}

void TransformComponent::update() {
}

const Vector3& TransformComponent::getPosition() const {
    return mPosition;
}

void TransformComponent::setPosition(const Vector3& pos) {
    mPosition = pos;
    mRecomputeTransform = true;
}

void TransformComponent::translete(const Vector3& translation) {
    mPosition += translation;
    mRecomputeTransform = true;
}

const Quaternion& TransformComponent::getRotation() const {
    return mRotation;
}

void TransformComponent::setRotation(const Quaternion& rot) {
    mRotation = rot;
    mRecomputeTransform = true;
}

void TransformComponent::setRotation(const Vector3& axis, float angle) {
    angle *= 0.5f * Math::deg2Rad;
    float sinAngle = Math::sin(angle);

    mRotation.x = axis.x * sinAngle;
    mRotation.y = axis.y * sinAngle;
    mRotation.z = axis.z * sinAngle;
    mRotation.w = Math::cos(angle);

    mRecomputeTransform = true;
}

void TransformComponent::rotate(const Vector3& euler) {
    rotate(Vector3::left, euler.x);
    rotate(Vector3::up, euler.y);
    rotate(Vector3::forward, euler.z);

    //Vector3 angles = euler * 0.5f * Math::deg2Rad;
    //Quaternion inc;
    //inc.x = Math::sin(angles.x);
    //inc.y = Math::sin(angles.y);
    //inc.z = Math::sin(angles.z);
    //inc.w = Math::cos(angles.x) * Math::cos(angles.y) * Math::cos(angles.z);

    //mRotation = Quaternion::concatenate(mRotation, inc);

    mRecomputeTransform = true;
}

void TransformComponent::rotate(const Vector3& axis, float angle) {
    angle *= 0.5f * Math::deg2Rad;
    float sinAngle = Math::sin(angle);

    Quaternion inc;
    inc.x = axis.x * sinAngle;
    inc.y = axis.y * sinAngle;
    inc.z = axis.z * sinAngle;
    inc.w = Math::cos(angle);

    mRotation = Quaternion::concatenate(mRotation, inc);

    mRecomputeTransform = true;
}

void TransformComponent::lookAt(const Vector3& target) {
    Matrix4::createLookAt(mPosition, target, Vector3::up);
    mRecomputeTransform = true;
}

const Vector3& TransformComponent::getScale() const {
    return mScale;
}

void TransformComponent::setScale(float scale) {
    mScale = Vector3(scale, scale, scale);
    mRecomputeTransform = true;
}

void TransformComponent::setScale(const Vector3& scale) {
    mScale = scale;
    mRecomputeTransform = true;
}

const Vector3 TransformComponent::forward() const {
    return Vector3::transform(Vector3::forward, mRotation);
}

const Vector3 TransformComponent::right() const {
    return Vector3::transform(Vector3::right, mRotation);
}

bool TransformComponent::getRecomputeTransform() const {
    return mRecomputeTransform;
}

void TransformComponent::setRecomputeTransform(bool set) {
    mRecomputeTransform = set;
}
