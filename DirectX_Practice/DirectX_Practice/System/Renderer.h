#pragma once

#include "../Shader/Shader.h"
#include "../Utility/Math.h"
#include <memory>
#include <string>
#include <unordered_map>

class Mesh;
class Texture;

class Renderer {
public:
    Renderer();
    ~Renderer();

    std::shared_ptr<Mesh> getMesh(const std::string& fileName);
    std::shared_ptr<Shader> getShader(Shader::ShaderType type);
    std::shared_ptr<Texture> getTexture(const std::string& fileName, Vector2 size);

    void clear();

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
    std::unordered_map<Shader::ShaderType, std::shared_ptr<Shader>> mShaders;
    std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
};

