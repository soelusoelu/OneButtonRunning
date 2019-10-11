#pragma once

#include "../Utility/Math.h"
#include <memory>

class ComponentManagementOfActor;
class TransformComponent;

class Actor {
public:
    enum State {
        Active,
        Dead
    };
    Actor(const char* tag = "");
    virtual ~Actor() {};

    //すべての更新
    void update();
    //アクター固有の更新
    virtual void updateActor() = 0;
    //描画
    virtual void drawActor() const = 0;

    //位置、角度、スケールに変更があった際に更新
    void computeWorldTransform();

    //アクター生成
    template<typename T>
    static T* instantiate() {
        return new T();
    }
    template<typename T>
    static void instantiate(const Vector3& position, const Quaternion& rotation) {
        T* t = new T();
        t->mTransform->setPosition(position);
        t->mTransform->setRotation(rotation);
    }
    //アクター削除
    static void destroy(Actor* actor);
    static void destroy(std::shared_ptr<Actor> actor);

    //ゲッター、セッター
    std::shared_ptr<ComponentManagementOfActor> getComponentManager() const;
    const Matrix4& getWorldTransform() const;
    TransformComponent* getTransform() const;
    State getState() const;
    const char* getTag() const;

private:
    std::shared_ptr<ComponentManagementOfActor> mComponentManager;
    State mState;
    Matrix4 mWorldTransform;
    TransformComponent* mTransform;
    const char* mTag;
};

