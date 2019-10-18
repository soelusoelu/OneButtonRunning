#include "FieldActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/TransformComponent.h"

FieldActor::FieldActor(const std::string& FileName, int no, float first, float end, const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, FileName)),
    mFieldNo(no),
    FIRST(first),
    END(end) {
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
    return mFieldNo;
}
