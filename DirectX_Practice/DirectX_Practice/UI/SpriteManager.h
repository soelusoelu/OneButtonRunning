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
    void sortByZ(bool flag);

    std::vector<std::shared_ptr<Sprite>> mSprites;
};

