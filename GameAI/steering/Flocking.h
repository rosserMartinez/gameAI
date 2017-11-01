#pragma once

#include "Steering.h"

class KinematicUnit;
class Alignment;
class Cohesion;
class Separation;
class KinematicWanderSteering;

class Flocking :public Steering
{
public:
	Flocking(KinematicUnit* pMover);
	~Flocking();

	//	void setTarget(KinematicUnit* pTarget) { mpTarget = pTarget; };

	virtual Steering* getSteering();

private:

	//KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	/*float mMAX_WANDER_ROTATION = 1.0f;
	float mReactionRadius = 500.0f;*/

	Alignment* mpAlignment;
	Cohesion* mpCohesion;
	Separation* mpSeparation;
	KinematicWanderSteering* mpWander;

	float mAlignmentWeight = 3000.0f;
	float mCohesionWeight = 2000.0f;
	float mSeparationWeight = 6000.0f;
	float mWanderWeight = 10.0f;

};