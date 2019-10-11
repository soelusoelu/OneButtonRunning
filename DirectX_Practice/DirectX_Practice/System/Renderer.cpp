#include "Renderer.h"
#include "../Component/Mesh.h"
#include "../System/IDManager.h"

Renderer::Renderer() :
    mIDManager(std::make_unique<IDManager>()) {
}

Renderer::~Renderer() = default;

std::shared_ptr<Mesh> Renderer::getMesh(const std::string& filename) {
    std::shared_ptr<Mesh> mesh;
    auto itr = mMeshes.find(filename);
    if (itr != mMeshes.end()) { //既に読み込まれている
        mesh = itr->second;
    } else { //初読み込み
        mesh = std::make_shared<Mesh>();
        mesh->Init(filename);
        mMeshes.emplace(filename, mesh);
    }
    return mesh;
}

unsigned Renderer::getTexture(const std::string& filename) {
    unsigned id;
    auto itr = mTextures.find(filename);
    if (itr != mTextures.end()) { //既に読み込まれている
        id = itr->second;
    } else { //初読み込み
        id = mIDManager->pop(IDManager::Type::Texture);
        //gsLoadTexture(id, filename.c_str());
        mTextures.emplace(filename, id);
    }
    return id;
}

void Renderer::clear() {
    for (const auto& mesh : mMeshes) {
        //gsDeleteMesh(mesh.second);
    }
    mMeshes.clear();
    for (const auto& texture : mTextures) {
        //gsDeleteTexture(texture.second);
        mIDManager->push(texture.second, IDManager::Type::Texture);
    }
    mTextures.clear();

    mIDManager->clear();
}
