#include "PlayerActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/TransformComponent.h"
#include "../UI/Score.h"

PlayerActor::PlayerActor(Score* score, const char* tag) :
    Actor(tag),
	mScore(score),
    mPlayerMove(new PlayerMoveComponent(this, mScore)),
    mMesh(new MeshComponent(this, "LINK.obj")),
    mSphere(new SphereCollisionComponent(this)) {
	getTransform()->setScale(0.6f);
	getTransform()->setPosition(Vector3(0.0f, 6.0f, 0.f));
}

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
    mMesh->draw();
    mSphere->drawMesh();
}

Score* PlayerActor::getScore()
{
	return mScore;
}
