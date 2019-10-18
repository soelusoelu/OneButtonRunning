#include "FieldActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/TransformComponent.h"

FieldActor::FieldActor(const std::string& FileName, const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, FileName)) {
}

void FieldActor::updateActor() {
}

void FieldActor::drawActor() const {
    mMesh->draw(getWorldTransform());
}
