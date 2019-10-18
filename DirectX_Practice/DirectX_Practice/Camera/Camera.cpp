#include "Camera.h"
#include "../Actor/PlayerActor.h"
#include "../Component/TransformComponent.h"
#include "../System/Game.h"

Camera::Camera() :
    mCameraPosition(Vector3::zero),
    mLookAt(Vector3::zero),
    mUp(Vector3::up),
    mPlayerPosition(mCameraPosition) {
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
    mProj = Matrix4::createPerspectiveFOV(45.f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 0.1f, 1000.f);
}

void Camera::update(std::shared_ptr<PlayerActor> player) {
    if (player) {
        //Vector3 eyeVec = player->getTransform()->forward();
        float posY = player->getTransform()->getPosition().y;
        posY = Math::Max<float>(posY, 0.f);

        //mCameraPosition = Vector3(
        //    player->getTransform()->getPosition().x + /*eyeVec.x * */7.f,
        //    player->getTransform()->getPosition().y + 2.f,
        //    player->getTransform()->getPosition().z - /*eyeVec.z * */5.f
        //);
        //posYにかけた値でジャンプ時のカメラを補正する
        mCameraPosition = Vector3(
            player->getTransform()->getPosition().x + 5.f + posY * 2.f,
            player->getTransform()->getPosition().y + 4.f - posY * 0.5f,
            player->getTransform()->getPosition().z - 5.f - posY * 2.5f
        );
        mPlayerPosition = player->getTransform()->getPosition();
        //mLookAt = Vector3(mPlayerPosition.x, mPlayerPosition.y + 1.5f, mPlayerPosition.z + 1.5f); //注視点
        mLookAt = Vector3(mPlayerPosition.x, mPlayerPosition.y + 1.5f, mPlayerPosition.z + 1.5f + posY * 0.5f); //注視点
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
