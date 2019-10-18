#include "EnemyActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/TransformComponent.h"

EnemyActor::EnemyActor(const char* tag) :
    Actor(tag),
    mMesh(new MeshComponent(this, "RobotB.obj")),
    mSphere(new SphereCollisionComponent(this)) {
    getTransform()->setScale(0.25f);
}

void EnemyActor::updateActor() {
}

void EnemyActor::drawActor() const {
    mMesh->draw(getWorldTransform());
    mSphere->drawMesh();
}
