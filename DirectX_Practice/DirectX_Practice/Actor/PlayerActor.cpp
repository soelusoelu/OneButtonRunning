#include "PlayerActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/TransformComponent.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mPlayerMove(new PlayerMoveComponent(this)),
    mMesh(new MeshComponent(this, "LINK.obj")),
    mSphere(new SphereCollisionComponent(this)) {
	getTransform()->setScale(0.4f);
	getTransform()->setPosition(Vector3(0.0f, 6.0f, 0.f));
}

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
    mMesh->draw();
    mSphere->drawMesh();
}
