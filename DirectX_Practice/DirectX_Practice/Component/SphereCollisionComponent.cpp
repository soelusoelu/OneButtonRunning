#include "SphereCollisionComponent.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Device/Physics.h"

SphereCollisionComponent::SphereCollisionComponent(Actor* owner) :
    Component(owner),
    mSphere(),
    mSphereMesh(nullptr),
    mDefaultRadius(0.f) {
}

SphereCollisionComponent::~SphereCollisionComponent() {
    Singleton<Physics>::instance().removeSphere(this);
}

void SphereCollisionComponent::start() {
    Singleton<Physics>::instance().addSphere(this);

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

    mSphere.mRadius *= 0.7f;
    mSphere.mCenter.y += mSphere.mRadius;
}

void SphereCollisionComponent::drawMesh(float alpha) const {
    Matrix4 w = Matrix4::createScale(mSphere.mRadius * 2);
    w *= Matrix4::createTranslation(mSphere.mCenter);
    if (mSphereMesh) {
        mSphereMesh->draw(w, alpha);
    }
}

const Sphere SphereCollisionComponent::getSphere() const {
    return mSphere;
}
