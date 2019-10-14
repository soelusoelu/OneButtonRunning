#pragma once

#include "../Utility/Singleton.h"
#include "../Utility/Math.h"

class PlayerActor;

class Camera {
    friend class Singleton<Camera>;
public:
    void update(std::shared_ptr<PlayerActor> player);
    void update();
    Vector3 getPosition();
    Matrix4 getView();
    Matrix4 getProjection();

private:
    Camera();
    ~Camera() {};

    Vector3 mCameraPosition;
    Vector3 mLookAt;
    Vector3 mUp;
    Vector3 mPlayerPosition;

    Matrix4 mView;
    Matrix4 mProj;
};

