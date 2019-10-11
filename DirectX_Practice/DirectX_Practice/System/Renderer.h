#pragma once

#include <string>
#include <unordered_map>
#include <memory>

class IDManager;
class Mesh;

class Renderer {
public:
    Renderer();
    ~Renderer();

    std::shared_ptr<Mesh> getMesh(const std::string& filename);
    unsigned getTexture(const std::string& filename);

    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
    std::unordered_map<std::string, unsigned> mTextures;
    std::unique_ptr<IDManager> mIDManager;
};

