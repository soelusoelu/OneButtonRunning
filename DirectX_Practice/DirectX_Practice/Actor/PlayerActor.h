#pragma once

#include "Actor.h"

class PlayerMoveComponent;
class MeshComponent;
class SphereCollisionComponent;

class PlayerActor : public Actor {
    friend class Actor;
public:
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    PlayerActor(const char* tag = "Player");
    ~PlayerActor() {};

    PlayerMoveComponent* mPlayerMove;
    MeshComponent* mMesh;
    SphereCollisionComponent* mSphere;
};

