#include "Physics.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/ActorManager.h"
#include "../Component/Mesh.h"
#include "../Component/MeshComponent.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Utility/Collision.h"
#include <algorithm>

Physics::Physics() = default;
Physics::~Physics() = default;

bool Physics::rayCastField(Ray* ray, CollisionInfo* outColl) {
    bool collided = false;
    float minLength = Math::infinity;
    Vector3 normal;
    //すべての地面のポリゴンとテスト
    for (const auto& field : Singleton<ActorManager>::instance().getFields()) {
        auto mesh = field->getComponentManager()->getComponent<MeshComponent>()->getMesh();
        for (int i = 0; i < mesh->getNumMaterial(); i++) {
            for (int k = 0; k < mesh->getNumFace()[i]; k++) {
                //このポリゴンの3点を取得
                D3DXVECTOR3 v1, v2, v3;
                int index1 = mesh->getVertexIndex()[i][k * 3 + 0];
                int index2 = mesh->getVertexIndex()[i][k * 3 + 1];
                int index3 = mesh->getVertexIndex()[i][k * 3 + 2];

                v1 = mesh->getVertexBuffer()[index1].mPos;
                v2 = mesh->getVertexBuffer()[index2].mPos;
                v3 = mesh->getVertexBuffer()[index3].mPos;
                //3点から平面方程式を作る
                D3DXPLANE plane;
                calcPlane(&plane, &v1, &v2, &v3);
                //平面とレイの交差を検出
                if (intersectPlane(plane, ray, v1, v2, v3, outColl)) {
                    collided = true;
                    if (minLength > outColl->mLength) {
                        normal.x = plane.a;//平面方程式の係数は面法線
                        normal.y = plane.b;
                        normal.z = plane.c;
                        minLength = outColl->mLength;
                    }
                }
            }
        }
    }

    outColl->mNormal = normal;
    outColl->mLength = minLength;
    return collided;
}

Vector3 Physics::slip(const Vector3& ray, Vector3 normal) {
    //Vector3 l = Vector3::normalize(ray->mEnd - ray->mStart);
    Vector3 l = ray;
    Vector3 s = l - ((Vector3::dot(normal, l)) / normal.lengthSq()) * normal;
    return s;
}

void Physics::calcPlane(D3DXPLANE* plane, D3DXVECTOR3* a, D3DXVECTOR3* b, D3DXVECTOR3* c) {
    //辺ベクトル
    D3DXVECTOR3 AB, BC;
    AB = *b - *a;
    BC = *c - *b;
    //平面法線ベクトル
    D3DXVECTOR3 vNormal;
    D3DXVec3Cross(&vNormal, &AB, &BC);
    // 法線は平面の傾きでもあるので、そのまま代入
    plane->a = vNormal.x;
    plane->b = vNormal.y;
    plane->c = vNormal.z;
    // d を計算
    plane->d = -(plane->a * a->x + plane->b * a->y + plane->c * a->z);
}

bool Physics::intersectPlane(D3DXPLANE plane, Ray* ray, D3DXVECTOR3 v1, D3DXVECTOR3 v2, D3DXVECTOR3 v3, CollisionInfo* outColl) {
    //パラメトリック方程式の媒介変数” t "を解く。
    float t = -((plane.a * ray->mEnd.x) + (plane.b * ray->mEnd.y) + (plane.c * ray->mEnd.z) + plane.d) /
        (((plane.a * ray->mStart.x) + (plane.b * ray->mStart.y) + (plane.c * ray->mStart.z)) - ((plane.a * ray->mEnd.x) + (plane.b * ray->mEnd.y) + (plane.c * ray->mEnd.z)));
    // t が０から１の間であるなら交差していることになる（この時点では、まだ無限遠平面との交差）
    if (t >= 0 && t <= 1.0) {
        //交点座標を得る　ｔが分かっていれば両端点から簡単に求まる
        D3DXVECTOR3 v;
        v.x = t * ray->mStart.x + (1 - t) * ray->mEnd.x;
        v.y = t * ray->mStart.y + (1 - t) * ray->mEnd.y;
        v.z = t * ray->mStart.z + (1 - t) * ray->mEnd.z;
        //交点が三角形の内か外かを判定　（ここで内部となれば、完全な交差となる）
        if (isInside(&v, &v1, &v2, &v3)) {
            //レイ始点と交点の距離を計算
            outColl->mLength = D3DXVec3Length(&(v - ray->mStart.toD3DXVECTOR3()));
            return true;
        }
        return false;
    }
    return false;
}

bool Physics::isInside(D3DXVECTOR3* intersect, D3DXVECTOR3* a, D3DXVECTOR3* b, D3DXVECTOR3* c) {
    //辺ベクトル
    D3DXVECTOR3 vAB, vBC, vCA;
    vAB = *b - *a;
    vBC = *c - *b;
    vCA = *a - *c;
    //辺ベクトルと「頂点から交点へ向かうベクトル」との、それぞれの外積用
    D3DXVECTOR3 vCrossAB, vCrossBC, vCrossCA;
    //「外積結果のベクトル」と平面法線ベクトルとの、それぞれの内積用
    FLOAT fAB, fBC, fCA;
    // 法線用
    D3DXVECTOR3 vNormal;
    // まず、3頂点から平面方程式を求める。これは、同時に平面の法線を求めることでもある
    D3DXPLANE pln;
    D3DXPlaneFromPoints(&pln, a, b, c);
    vNormal.x = pln.a;//法線のx成分は平面方程式のx係数
    vNormal.y = pln.b;//法線のy成分は平面方程式のy係数
    vNormal.z = pln.c;//法線のz成分は平面方程式のz係数
    D3DXVec3Normalize(&vNormal, &vNormal);

    // 各頂点から交点Iに向かうベクトルをvVとする
    D3DXVECTOR3 vV;
    // 辺ABベクトル（頂点Bベクトル-頂点Aベクトル)と、頂点Aから交点Iへ向かうベクトル、の外積を求める
    vV = *intersect - *a;
    D3DXVec3Cross(&vCrossAB, &vAB, &vV);
    // 辺BCベクトル（頂点Cベクトル-頂点Bベクトル)と、頂点Bから交点Iへ向かうベクトル、の外積を求める
    vV = *intersect - *b;
    D3DXVec3Cross(&vCrossBC, &vBC, &vV);
    // 辺CAベクトル（頂点Aベクトル-頂点Cベクトル)と、頂点Cから交点Iへ向かうベクトル、の外積を求める
    vV = *intersect - *c;
    D3DXVec3Cross(&vCrossCA, &vCA, &vV);
    // それぞれの、外積ベクトルとの内積を計算する
    fAB = D3DXVec3Dot(&vNormal, &vCrossAB);
    fBC = D3DXVec3Dot(&vNormal, &vCrossBC);
    fCA = D3DXVec3Dot(&vNormal, &vCrossCA);

    // ３つの内積結果のうち、一つでもマイナス符号のものがあれば、交点は外にある。
    if (fAB >= 0 && fBC >= 0 && fCA >= 0) {
        // 交点は、面の内にある
        return true;
    }
    // 交点は面の外にある
    return false;
}

void Physics::sweepAndPrune() {
    //mCenter.zが小さい順にソート
    std::sort(mSpheres.begin(), mSpheres.end(), [](SphereCollisionComponent* a, SphereCollisionComponent* b) {
        return a->getSphere().mCenter.z < b->getSphere().mCenter.z;
    });

    for (size_t i = 0; i < mSpheres.size(); i++) {
        //一番左がプレイヤーじゃなかったらもう一度
        if (mSpheres[i]->getOwner()->getTag() != "Player") {
            continue;
        }
        //mSpheres[i]の中心+半径を取得
        auto a = mSpheres[i]->getSphere();
        float max = a.mCenter.z + a.mRadius;
        for (size_t j = i + 1; j < mSpheres.size(); j++) {
            //もしmSpheres[j]の中心-半径が、mSpheres[i]の中心+半径を超えていたら、
            //mSpheres[i]と交差する可能性があるボックスは存在しない
            auto b = mSpheres[j]->getSphere();
            if (b.mCenter.z - b.mRadius > max) {
                break;
            } else if (intersect(a, b)) {
                hit(mSpheres[i]->getOwner(), mSpheres[j]->getOwner());
            }
        }
    }
}

void Physics::addSphere(SphereCollisionComponent* sphere) {
    mSpheres.emplace_back(sphere);
}

void Physics::removeSphere(SphereCollisionComponent* sphere) {
    auto itr = std::find(mSpheres.begin(), mSpheres.end(), sphere);
    if (itr != mSpheres.end()) {
        std::iter_swap(itr, mSpheres.end() - 1);
        mSpheres.pop_back();
    }
}

void Physics::hit(Actor* player, Actor* another) {
    Actor::destroy(another);
}
