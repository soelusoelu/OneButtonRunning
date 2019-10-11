#pragma once

#include "../Utility/Singleton.h"
#include <memory>

class Renderer;
class Physics;
class Random;

class GameSystem {
    friend class Singleton<GameSystem>;
public:
    std::shared_ptr<Renderer> getRenderer() const;
    std::shared_ptr<Physics> getPhysics() const;
    std::shared_ptr<Random> getRandom() const;
    void clear();

private:
    GameSystem();
    ~GameSystem();

    std::shared_ptr<Renderer> mRenderer;
    std::shared_ptr<Physics> mPhysics;
    std::shared_ptr<Random> mRandom;
};

