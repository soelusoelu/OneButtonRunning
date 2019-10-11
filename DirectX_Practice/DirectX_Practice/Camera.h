#pragma once

#include "Utility/Singleton.h"
#include "Utility/Math.h"
#include <memory>

class PlayerActor;

class Camera {
    friend class Singleton<Camera>;
public:
    void update(std::shared_ptr<PlayerActor> player);
    void update();
    D3DXVECTOR3 getPosition();
    D3DXMATRIX getView();
    D3DXMATRIX getProjection();

private:
    Camera();
    ~Camera() {};

    Vector3 mCameraPosition;
    Vector3 mLookAt;
    Vector3 mUp;
    Vector3 mPlayerPosition;

    D3DXMATRIX mView;
    D3DXMATRIX mProj;
};

