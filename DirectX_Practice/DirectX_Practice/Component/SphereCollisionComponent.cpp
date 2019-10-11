#include "SphereCollisionComponent.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../System/GameSystem.h"
#include "../System/Physics.h"
#include "../Utility/Singleton.h"

SphereCollisionComponent::SphereCollisionComponent(Actor* owner) :
    Component(owner),
    mSphere(),
    mSphereMesh(nullptr),
    mDefaultRadius(0.f) {
    Singleton<GameSystem>::instance().getPhysics()->addSphere(this);
}

SphereCollisionComponent::~SphereCollisionComponent() {
    Singleton<GameSystem>::instance().getPhysics()->removeSphere(this);
}

void SphereCollisionComponent::start() {
    std::shared_ptr<MeshComponent> mesh = mOwner->getComponentManager()->getComponent<MeshComponent>();
    if (mesh) {
        mesh->getMesh()->createSphere(&mSphere);
        mSphere.mCenter = mOwner->getTransform()->getPosition();
        mDefaultRadius = mSphere.mRadius;
        mSphereMesh = new MeshComponent(mOwner, "Sphere.obj");
    }
}

void SphereCollisionComponent::update() {
}

void SphereCollisionComponent::onUpdateWorldTransform() {
    mSphere.mCenter = mOwner->getTransform()->getPosition();
    mSphere.mRadius = mDefaultRadius * mOwner->getTransform()->getScale().y;
}

void SphereCollisionComponent::drawMesh(float alpha) const {
    Matrix4 w = Matrix4::createScale(mSphere.mRadius * 2);
    w *= Matrix4::createTranslation(mOwner->getTransform()->getPosition());
    if (mSphereMesh) {
        mSphereMesh->draw(w, alpha);
    }
}

const Sphere SphereCollisionComponent::getSphere() const {
    return mSphere;
}
