#pragma once

#include <memory>
#include <vector>

class Sprite;

class SpriteManager {
public:
    SpriteManager();
    ~SpriteManager();
    void addSprite(Sprite* sprite);
    void update();
    void draw() const;
    void clear();

private:
    void removeSprite();
    void sortByZ(bool flag);

    std::vector<std::shared_ptr<Sprite>> mSprites;
};

