#include "EnemyActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/TransformComponent.h"

EnemyActor::EnemyActor(const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, "Rock1.obj")),
    mSphere(new SphereCollisionComponent(this)) {
    getTransform()->setPosition(Vector3(-2.f, 15.f, 10.f));
    getTransform()->setScale(1.f);
}

void EnemyActor::updateActor() {
}

void EnemyActor::drawActor() const {
    mMesh->draw(getWorldTransform());
    mSphere->drawMesh();
}
