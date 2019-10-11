#pragma once

#include "Math.h"

struct Ray {
    Ray(const Vector3& start, const Vector3& end);
    //線分上の点を返す 0 <= t <= 1
    Vector3 pointOnSegment(float t) const;
    //最短距離の2乗
    float minDistanceSquare(const Vector3& point) const;
    //2本の線分から最短距離の2乗を取得
    static float minDistanceSquare(const Ray& s1, const Ray& s2);

    Vector3 mStart;
    Vector3 mEnd;
};

struct Sphere {
    Sphere();
    Sphere(const Vector3& center, float radius);
    void set(const Vector3& center, float radius);
    bool contains(const Vector3& point) const;

    Vector3 mCenter;
    float mRadius;
};

//oriented bounding box つまり回転する直方体
//AABBよりはるかに計算コストが高い
struct OBB {
    Vector3 mCenter;
    Quaternion mRotation;
    Vector3 mExtents;
};

//交差判定
bool intersect(const Sphere& a, const Sphere& b);

bool intersect(const Ray& r, const Sphere& s, float* outT);

bool SweptSphere(const Sphere& P0, const Sphere& P1, const Sphere& Q0, const Sphere& Q1, float* t);
