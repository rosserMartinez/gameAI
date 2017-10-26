#pragma once

#include "Steering.h"

class KinematicUnit;

class Alignment :public Steering
{
public:
	Alignment(KinematicUnit* pMover);
	~Alignment() {};

	//	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:

	//KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	float mMAX_WANDER_ROTATION = 1.0f;
	float mReactionRadius = 500.0f;
};