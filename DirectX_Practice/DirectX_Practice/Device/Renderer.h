#pragma once

#include "../Shader/Shader.h"
#include "../Utility/Math.h"
#include "../Utility/Singleton.h"
#include <memory>
#include <string>
#include <unordered_map>

class Mesh;
class Texture;

class Renderer {
    friend class Singleton<Renderer>;
public:
    std::shared_ptr<Mesh> getMesh(const std::string& fileName);
    std::shared_ptr<Shader> getShader(ShaderType type);
    std::shared_ptr<Texture> getTexture(const std::string& fileName);

    void clear();

private:
    Renderer();
    ~Renderer();

    std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
    std::unordered_map<ShaderType, std::shared_ptr<Shader>> mShaders;
    std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
};

