#pragma once

#include "Steering.h"

class KinematicUnit;

class Cohesion :public Steering
{
public:
	Cohesion(KinematicUnit* pMover);
	~Cohesion() {};

//	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:

	KinematicUnit* mpMover;
	float mMAX_WANDER_ROTATION = 1.0f;
	float mReactionRadius = 500.0f;
};
