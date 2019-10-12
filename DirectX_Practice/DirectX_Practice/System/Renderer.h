#pragma once

#include <string>
#include <unordered_map>
#include <memory>

class IDManager;
class Mesh;
class Shader;

class Renderer {
public:
    Renderer();
    ~Renderer();

    std::shared_ptr<Mesh> getMesh(const std::string& filename);
    std::shared_ptr<Shader> getShader(const std::string& fileName);
    unsigned getTexture(const std::string& filename);

    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
    std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;
    std::unordered_map<std::string, unsigned> mTextures;
    std::unique_ptr<IDManager> mIDManager;
};

