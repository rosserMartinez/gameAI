#pragma once

#include "Steering.h"

class KinematicUnit;

const float alsoInfinityTM = 500000;

class WanderAndFlee :public Steering
{
public:
	WanderAndFlee(KinematicUnit* pMover, KinematicUnit* pTarget, float newReactionRadius, bool shouldFlee = false);
	~WanderAndFlee() {};

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
	float MAX_WANDER_ROTATION = 1.0f;
	float mCollCheckRadius = 500.0f;

};