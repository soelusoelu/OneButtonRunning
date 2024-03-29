﻿#pragma once

#include "../Utility/IManager.h"
#include "../Utility/Singleton.h"
#include <list>
#include <memory>
#include <unordered_set>

class Actor;
class FieldActor;
class PlayerActor;

class ActorManager : public IManager<Actor> {
    friend class Singleton<ActorManager>;
public:
	virtual void init();
    virtual void update() override;
    virtual void draw() const override;
    virtual void add(Actor* add) override;
    virtual void remove() override;
    virtual void clear() override;

    //全アクターの取得
    std::unordered_set<std::shared_ptr<Actor>> getActors() const;
    //全地形の取得
    std::list<std::shared_ptr<Actor>> getFields() const;
    //アクター配列の中からプレイヤーを取得
    std::shared_ptr<PlayerActor> getPlayer() const;
    //最後のフィールドを取得
    std::shared_ptr<FieldActor> getLastField() const;
	const bool notExistPlayer() const;

private:
    ActorManager();
    ~ActorManager();
    ActorManager(const ActorManager&) = delete;
    ActorManager& operator=(const ActorManager&) = delete;
    //アクターをフィールドと分別
    void divideActor(std::shared_ptr<Actor> actor);
    //プレイヤー以外スクロール
    void scrollExceptPlayer(std::shared_ptr<Actor> scrollTarget);
    //画面から消えたら削除
    void deleteScreenOut(std::shared_ptr<Actor> actor);
    //フィールドの数と位置をコントロール
    void controlField();

private:
    std::unordered_set<std::shared_ptr<Actor>> mActors;
    std::unordered_set<std::shared_ptr<Actor>> mPendingActors;
    std::list<std::shared_ptr<Actor>> mFieldActors;
    std::shared_ptr<FieldActor> mLastField;
    bool mUpdatingActors;
	bool mIsPlayerDead;
};

