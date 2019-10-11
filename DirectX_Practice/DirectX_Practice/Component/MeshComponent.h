#pragma once

#include "Component.h"
#include "../Utility/Math.h"
#include <memory>
#include <string>

class Actor;
class Mesh;

class MeshComponent : public Component {
public:
    MeshComponent(Actor* owner, const std::string& filename);
    virtual void update() override;
    void draw(float alpha = 1.f) const;
    void draw(Matrix4 world, float alpha = 1.f) const;

    std::shared_ptr<Mesh> getMesh() const;
    void setEnable(bool set);
    bool getEnable() const;

private:
    std::shared_ptr<Mesh> mMesh;
    bool mEnabled;
};

