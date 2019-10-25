#pragma once
#include "Actor.h"

class EnemyMoveComponent;
class MeshComponent;
class SphereCollisionComponent;

class EnemyActor : public Actor {
public:
    EnemyActor(const char* tag = "Enemy");
    ~EnemyActor() {};
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    EnemyMoveComponent* mEnemyMove;
    MeshComponent* mMesh;
    SphereCollisionComponent* mSphere;
};

