#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include "../Utility/Collision.h"
#include <memory>

class Actor;
class MeshComponent;

class SphereCollisionComponent : public Component {
public:
    SphereCollisionComponent(Actor* owner);
    ~SphereCollisionComponent();
    virtual void start() override;
    virtual void update() override;
    virtual void onUpdateWorldTransform() override;
    void drawMesh(float alpha = 0.5f) const;
    const Sphere getSphere() const;

private:
    Sphere mSphere;
    MeshComponent* mSphereMesh;
    float mDefaultRadius;
};

