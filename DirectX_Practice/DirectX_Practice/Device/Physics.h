﻿#pragma once

#include "../Utility/Math.h"
#include "../Utility/Collision.h"
#include "../Utility/Singleton.h"
#include <vector>
#include <memory>

class GamePlay;
class SphereCollisionComponent;
class Actor;

class Physics {
    friend class Singleton<Physics>;
public:
    struct CollisionInfo {
        //衝突した点
        Vector3 mPoint;
        //衝突した点の法線
        Vector3 mNormal;
        //交差したコンポーネント
        //BoxComponent* mBox;
        //コンポーネントを所有するアクター
        //Actor* mActor;
        float mLength;
    };

    bool rayCastField(Ray* ray, CollisionInfo* outColl);
    Vector3 slip(const Vector3& ray, Vector3 normal);
    //総当たり判定
    void sweepAndPrune();

    //ボックスコンポーネントの追加・削除
    void addSphere(SphereCollisionComponent* sphere);
    void removeSphere(SphereCollisionComponent* sphere);

private:
    Physics();
    ~Physics();

    void calcPlane(D3DXPLANE* plane, D3DXVECTOR3* a, D3DXVECTOR3* b, D3DXVECTOR3* c);
    bool intersectPlane(D3DXPLANE plane, Ray* ray, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, CollisionInfo* outColl);
    bool isInside(D3DXVECTOR3* intersect, D3DXVECTOR3* a, D3DXVECTOR3* b, D3DXVECTOR3* c);
    void hit(Actor* player, Actor* another);

    std::vector<SphereCollisionComponent*> mSpheres;
};
