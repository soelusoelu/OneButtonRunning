#include "MeshComponent.h"
#include "Mesh.h"
#include "../Actor/Actor.h"
#include "../Device/Renderer.h"
#include <string>

MeshComponent::MeshComponent(Actor* owner, const std::string& filename) :
    Component(owner),
    mEnabled(true) {
    mMesh = Singleton<Renderer>::instance().getMesh(filename);
}

void MeshComponent::update() {
}

void MeshComponent::draw(float alpha) const {
    if (mEnabled) {
        auto w = mOwner->getWorldTransform();
        mMesh->draw(w, alpha);
    }
}

void MeshComponent::draw(Matrix4 world, float alpha) const {
    if (mEnabled) {
        mMesh->draw(world, alpha);
    }
}

std::shared_ptr<Mesh> MeshComponent::getMesh() const {
    return mMesh;
}

void MeshComponent::setEnable(bool set) {
    mEnabled = set;
}

bool MeshComponent::getEnable() const {
    return mEnabled;
}
