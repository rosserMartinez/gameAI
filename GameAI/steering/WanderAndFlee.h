#pragma once

#include "Steering.h"

class KinematicUnit;

const float MAX_WANDER_ROTATION = 1.0f;

class WanderAndFlee :public Steering
{
public:
	WanderAndFlee(KinematicUnit* pMover, KinematicUnit* pTarget, float newReactionRadius, bool shouldFlee = false);
	~WanderAndFlee() {};

	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	bool mShouldFlee;
	float mReactionRadius;
};