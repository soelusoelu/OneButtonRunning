#include "Camera.h"
#include "DirectXIncLib.h"
#include "Game.h"
#include "Actor/PlayerActor.h"
#include "Component/TransformComponent.h"

Camera::Camera() :
    mCameraPosition(0.f, 1.f, -3.f),
    mLookAt(Vector3::zero),
    mUp(Vector3::up),
    mPlayerPosition(mCameraPosition) {
    D3DXMatrixLookAtLH(&mView, &mCameraPosition.toD3DXVECTOR3(), &mLookAt.toD3DXVECTOR3(), &mUp.toD3DXVECTOR3());
    D3DXMatrixPerspectiveFovLH(&mProj, Math::Pi / 4, Game::WINDOW_WIDTH / Game::WINDOW_HEIGHT, 0.1f, 100.f);
}

void Camera::update(std::shared_ptr<PlayerActor> player) {
    if (player) {
        Vector3 eyeVec = player->getTransform()->forward();

        mCameraPosition = Vector3(
            player->getTransform()->getPosition().x + /*eyeVec.x * */7.f,
            player->getTransform()->getPosition().y + 2.f,
            player->getTransform()->getPosition().z - /*eyeVec.z * */5.f
        );
        mPlayerPosition = player->getTransform()->getPosition();
        mLookAt = Vector3(mPlayerPosition.x, mPlayerPosition.y + 1.5f, mPlayerPosition.z + 3.f); //注視点
    }

    D3DXMatrixLookAtLH(&mView, &mCameraPosition.toD3DXVECTOR3(), &mLookAt.toD3DXVECTOR3(), &mUp.toD3DXVECTOR3());
}

void Camera::update() {
    D3DXMatrixLookAtLH(&mView, &mCameraPosition.toD3DXVECTOR3(), &mLookAt.toD3DXVECTOR3(), &mUp.toD3DXVECTOR3());
}

D3DXVECTOR3 Camera::getPosition() {
    return mCameraPosition.toD3DXVECTOR3();
}

D3DXMATRIX Camera::getView() {
    return mView;
}

D3DXMATRIX Camera::getProjection() {
    return mProj;
}
