#pragma once

#include "../Utility/Singleton.h"
#include <unordered_set>
#include <memory>

class Actor;
class PlayerActor;

class ActorManager {
    friend class Singleton<ActorManager>;
public:
    void update();
    void draw() const;

    //アクター追加
    void addActor(Actor* actor);
    //所有アクターをすべて削除
    void clear();
    //プレイヤー以外スクロール
    void scrollExceptPlayer(std::shared_ptr<Actor> scrollTarget);
    //画面から消えたら削除
    void deleteScreenOut(std::shared_ptr<Actor> actor);

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
    //Dead状態のアクターを削除
    void removeDeadActor();

    std::unordered_set<std::shared_ptr<Actor>> mActors;
    std::unordered_set<std::shared_ptr<Actor>> mPendingActors;
    std::unordered_set<std::shared_ptr<Actor>> mFieldActors;
    bool mUpdatingActors;
};

