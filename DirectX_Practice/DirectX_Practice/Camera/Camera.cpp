#include "Camera.h"
#include "../Actor/PlayerActor.h"
#include "../Component/TransformComponent.h"
#include "../System/Game.h"

Camera::Camera() :
    mCameraPosition(Vector3::zero),
    mLookAt(Vector3::zero),
    mUp(Vector3::up),
    mPlayerPosition(mCameraPosition),
    mView(Matrix4::identity),
    mProj(Matrix4::identity) {
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
    mProj = Matrix4::createPerspectiveFOV(45.f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 0.1f, 1000.f);
}

void Camera::update(std::shared_ptr<PlayerActor> player) {
    if (player) {
        //Vector3 eyeVec = player->getTransform()->forward();
        float posY = player->getTransform()->getPosition().y;
        posY = Math::Max<float>(posY, 0.f);

        //posYにかけた値でジャンプ時のカメラを補正する
        mCameraPosition = Vector3(
            player->getTransform()->getPosition().x + 18.f + posY * 0.7f,
            player->getTransform()->getPosition().y + 2.f + posY * 0.2f,
            player->getTransform()->getPosition().z + 13.f
        );
        mPlayerPosition = player->getTransform()->getPosition();
        mLookAt = Vector3(0.f, mPlayerPosition.y + 1.f - posY * 0.5f, mCameraPosition.z); //注視点
    }

    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
}

void Camera::update() {
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
}

Vector3 Camera::getPosition() {
    return mCameraPosition;
}

Matrix4 Camera::getView() {
    return mView;
}

Matrix4 Camera::getProjection() {
    return mProj;
}
