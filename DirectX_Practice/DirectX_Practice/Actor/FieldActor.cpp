#include "FieldActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/TransformComponent.h"

FieldActor::FieldActor(const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, "Road1.obj")) {
	getTransform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));
}

void FieldActor::updateActor() {
}

void FieldActor::drawActor() const {
    mMesh->draw(getWorldTransform());
}
