#pragma once

#include "Actor.h"
#include <string>
#include <vector>

class MeshComponent;

class FieldActor : public Actor {
public:
    FieldActor(const std::string& FileNmae, int no, const char* tag = "Field");
    ~FieldActor() {};
    virtual void updateActor() override;
    virtual void drawActor() const override;
    const float getFirstY() const;
    const float getEndY() const;
    int getNo() const;

private:
    MeshComponent* mMesh;
	std::string mFileName;
    const float FIRST;
    const float END;
    int mNo;
};

