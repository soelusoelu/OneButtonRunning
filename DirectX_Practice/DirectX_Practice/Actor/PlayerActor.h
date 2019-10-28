#pragma once

#include "Actor.h"

class PlayerMoveComponent;
class MeshComponent;
class SphereCollisionComponent;
class Score;

class PlayerActor : public Actor {
    friend class Actor;
public:
	PlayerActor(Score* score ,const char* tag = "Player");
	~PlayerActor() {};

    virtual void updateActor() override;
    virtual void drawActor() const override;

	Score* getScore();

private:
    
	Score* mScore;
    PlayerMoveComponent* mPlayerMove;
    MeshComponent* mMesh;
    SphereCollisionComponent* mSphere;	
};

