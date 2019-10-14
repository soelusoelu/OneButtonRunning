#pragma once

#include <list>

class IDManager {
public:
    enum Type {
        Mesh,
        Skeleton,
        Animation,
        Texture
    };

    IDManager();
    ~IDManager() {};
    void push(unsigned id, Type type);
    unsigned pop(Type type);
    void clear();

private:
    std::list<unsigned> mMeshIDs;
    std::list<unsigned> mSkeletonIDs;
    std::list<unsigned> mAnimationIDs;
    std::list<unsigned> mTextureIDs;
};
