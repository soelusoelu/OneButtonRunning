#pragma once
#include "Actor.h"

class MeshComponent;
class SphereCollisionComponent;

class EnemyActor : public Actor {
public:
    EnemyActor(const char* tag = "Enemy");
    ~EnemyActor() {};
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    MeshComponent* mMesh;
    SphereCollisionComponent* mSphere;
};

