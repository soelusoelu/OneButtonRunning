#pragma once

#include "Actor.h"
#include <string>

class MeshComponent;

class FieldActor : public Actor {
    friend class Actor;
public:
    virtual void updateActor() override;
    virtual void drawActor() const override;

    FieldActor(const std::string& FileNmae, const char* tag = "Field");
    ~FieldActor() {};
private:

    MeshComponent* mMesh;
	std::string mFileName;
};

