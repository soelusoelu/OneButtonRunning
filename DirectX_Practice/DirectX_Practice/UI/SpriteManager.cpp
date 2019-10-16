#include "SpriteManager.h"
#include "Sprite.h"
#include "Texture.h"
#include <algorithm>

SpriteManager::SpriteManager() = default;
SpriteManager::~SpriteManager() {
    mSprites.clear();
}

void SpriteManager::addSprite(Sprite* sprite) {
    mSprites.emplace_back(sprite);
}

void SpriteManager::update() {
    bool sortFlag = false;
    for (auto&& sprite : mSprites) {
        sprite->update();
        sortFlag = sprite->getSortFlag() ? true : sortFlag;
    }
    sortByZ(sortFlag);
    removeSprite();
}

void SpriteManager::draw() const {
    Texture::drawAll(mSprites);
}

void SpriteManager::removeSprite() {
    auto itr = mSprites.begin();
    while (itr != mSprites.end()) {
        if ((*itr)->getState() == SpriteState::Dead) {
            itr = mSprites.erase(itr);
        } else {
            ++itr;
        }
    }
}

void SpriteManager::sortByZ(bool flag) {
    if (flag) { //z値を変更したやつがいればソート
        std::sort(mSprites.begin(), mSprites.end(), [](std::shared_ptr<Sprite> a, std::shared_ptr<Sprite> b) {
            return a->getDepth() > b->getDepth();
        });
    }
}

void SpriteManager::clear() {
    mSprites.clear();
}
