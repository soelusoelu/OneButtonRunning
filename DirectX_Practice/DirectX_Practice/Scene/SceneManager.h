#include "SceneBase.h"
#include <memory>

class SceneManager {
public:
    SceneManager();
    ~SceneManager() = default;
    void update();
    void draw() const;

private:
    void change(Scene next);

private:
    std::unique_ptr<SceneBase> mCurrentScene;
};
