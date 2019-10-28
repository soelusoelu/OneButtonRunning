#pragma once

#include "../Utility/IManager.h"
#include <memory>
#include <vector>

class Sprite;

class SpriteManager : public IManager<Sprite> {
public:
    SpriteManager();
    ~SpriteManager();
    virtual void update() override;
    virtual void draw() const override;
    virtual void add(Sprite* add) override;
    virtual void remove() override;
    virtual void clear() override;

private:
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;
    void sortByZ();

private:
    std::vector<std::shared_ptr<Sprite>> mSprites;
};

