#include "Renderer.h"
#include "../Component/Mesh.h"
#include "../UI/Texture.h"

Renderer::Renderer() = default;
Renderer::~Renderer() = default;

std::shared_ptr<Mesh> Renderer::getMesh(const std::string& fileName) {
    std::shared_ptr<Mesh> mesh;
    auto itr = mMeshes.find(fileName);
    if (itr != mMeshes.end()) { //既に読み込まれている
        mesh = itr->second;
    } else { //初読み込み
        mesh = std::make_shared<Mesh>();
        mesh->init(fileName);
        mMeshes.emplace(fileName, mesh);
    }
    return mesh;
}

std::shared_ptr<Shader> Renderer::getShader(ShaderType type) {
    std::shared_ptr<Shader> shader;
    auto itr = mShaders.find(type);
    if (itr != mShaders.end()) { //既に読み込まれている
        shader = itr->second;
    } else { //初読み込み
        shader = std::make_shared<Shader>();
        shader->init(type);
        mShaders.emplace(type, shader);
    }
    return shader;
}

std::shared_ptr<Texture> Renderer::getTexture(const std::string& fileName) {
    std::shared_ptr<Texture> texture;
    auto itr = mTextures.find(fileName);
    if (itr != mTextures.end()) { //既に読み込まれている
        texture = itr->second;
    } else { //初読み込み
        texture = std::make_shared<Texture>();
        texture->init(fileName);
        mTextures.emplace(fileName, texture);
    }
    return texture;
}

void Renderer::clear() {
    mMeshes.clear();
    mShaders.clear();
    mTextures.clear();
}
