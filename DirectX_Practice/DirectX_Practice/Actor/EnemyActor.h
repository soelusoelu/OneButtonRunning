#pragma once
#include "Actor.h"

class MeshComponent;
class SphereCollisionComponent;

class EnemyActor : public Actor {
    friend class Actor;
public:
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    EnemyActor(const char* tag = "Enemy");
    ~EnemyActor() {};

    MeshComponent* mMesh;
    SphereCollisionComponent* mSphere;
};

