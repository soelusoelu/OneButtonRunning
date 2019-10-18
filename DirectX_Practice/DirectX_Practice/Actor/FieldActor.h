#pragma once

#include "Actor.h"
#include <string>
#include <vector>

class MeshComponent;

class FieldActor : public Actor {
public:
    FieldActor(const std::string& FileNmae, const char* tag = "Field");
    ~FieldActor() {};
    virtual void updateActor() override;
    virtual void drawActor() const override;

    static const std::vector<float> mPositionsY;
private:
    MeshComponent* mMesh;
	std::string mFileName;
};

