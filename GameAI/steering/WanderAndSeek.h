#pragma once

#include "Steering.h"

class KinematicUnit;

//this is supposed to be infinity but idk how to rotate my 8s
const float infinityTM = 500000;

class WanderAndSeek :public Steering
{
public:
	WanderAndSeek(KinematicUnit* pMover, KinematicUnit* pTarget, float newReactionRadius, bool shouldFlee = false);
	~WanderAndSeek() {};

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	Vector2D mMainWhisker;
	Vector2D mOffWhiskerUp;
	Vector2D mOffWhiskerDown;

	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;
	float mReactionRadius;
	float mMAX_WANDER_ROTATION = 1.0f;
	float mCollCheckRadius = 500.0f;
};