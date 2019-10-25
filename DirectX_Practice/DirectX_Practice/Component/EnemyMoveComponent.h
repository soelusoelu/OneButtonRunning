#include "Component.h"

class Actor;

class EnemyMoveComponent : public Component {
public:
    EnemyMoveComponent(Actor* owner);
    virtual void update() override;

private:
    void onField();
    void rotate();
};