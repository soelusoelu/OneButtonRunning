#pragma once

#include "../Utility/IManager.h"
#include "../Utility/Singleton.h"
#include <unordered_set>
#include <memory>

class Actor;
class PlayerActor;

class ActorManager : public IManager<Actor> {
    friend class Singleton<ActorManager>;
public:
    virtual void update() override;
    virtual void draw() const override;
    virtual void add(Actor* add) override;
    virtual void remove() override;
    virtual void clear() override;

    //全アクターの取得
    std::unordered_set<std::shared_ptr<Actor>> getActors() const;
    //全地形の取得
    std::unordered_set<std::shared_ptr<Actor>> getFields() const;
    //アクター配列の中からプレイヤーを取得
    std::shared_ptr<PlayerActor> getPlayer() const;

private:
    ActorManager();
    ~ActorManager();
    //アクターをフィールドと分別
    void divideActor(std::shared_ptr<Actor> actor);
    //プレイヤー以外スクロール
    void scrollExceptPlayer(std::shared_ptr<Actor> scrollTarget);
    //画面から消えたら削除
    void deleteScreenOut(std::shared_ptr<Actor> actor);

    std::unordered_set<std::shared_ptr<Actor>> mActors;
    std::unordered_set<std::shared_ptr<Actor>> mPendingActors;
    std::unordered_set<std::shared_ptr<Actor>> mFieldActors;
    bool mUpdatingActors;
};

