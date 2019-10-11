#pragma once

#include "Actor.h"

class MeshComponent;

class FieldActor : public Actor {
    friend class Actor;
public:
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    FieldActor(const char* tag = "Field");
    ~FieldActor() {};

    MeshComponent* mMesh;
};

