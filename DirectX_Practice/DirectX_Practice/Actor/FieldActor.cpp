#include "FieldActor.h"
#include "../Component/MeshComponent.h"

FieldActor::FieldActor(const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, "sky_and_ground.obj")) {
}

void FieldActor::updateActor() {
}

void FieldActor::drawActor() const {
    mMesh->draw(getWorldTransform());
}
