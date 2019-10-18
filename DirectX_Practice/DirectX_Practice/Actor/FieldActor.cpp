#include "FieldActor.h"
#include "FieldHeightValues.h"
#include "../Component/MeshComponent.h"
#include "../Component/TransformComponent.h"

FieldActor::FieldActor(const std::string& FileName, int no, const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, FileName)),
    mNo(no),
    FIRST(FieldHeightValues::FIRST_END[no * 2]),
    END(FieldHeightValues::FIRST_END[no * 2 + 1]) {
}

void FieldActor::updateActor() {
}

void FieldActor::drawActor() const {
    mMesh->draw(getWorldTransform());
}

const float FieldActor::getFirstY() const {
    return FIRST;
}

const float FieldActor::getEndY() const {
    return END;
}

int FieldActor::getNo() const {
    return mNo;
}
