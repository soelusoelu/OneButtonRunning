#include "FieldActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/TransformComponent.h"

FieldActor::FieldActor(const std::string& FileName, const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, FileName)) {
	getTransform()->setPosition(Vector3(0.0f, 0.0f, 10.0f));
}

void FieldActor::updateActor() {
}

void FieldActor::drawActor() const {
    mMesh->draw(getWorldTransform());
}
