#include "Flocking.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
//#include "Steering.h"
#include "Alignment.h"
#include "Cohesion.h"
#include "Separation.h"
#include "KinematicWanderSteering.h"

Flocking::Flocking(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;

	mpAlignment = new Alignment(pMover);
	mpCohesion = new Cohesion(pMover);
	mpSeparation = new Separation(pMover);
	mpWander = new KinematicWanderSteering(pMover);

	//VELOCITY MATCHING????
}

Flocking::~Flocking()
{
	delete mpAlignment;
	delete mpCohesion;
	delete mpSeparation;
	delete mpWander;
}

Steering* Flocking::getSteering()
{

	///VELOCITY MATCHING?!?!?!?!?!?
	//mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();

	Vector2D tmpAlign = mpAlignment->getSteering()->getLinear();
	Vector2D tmpCohese = mpCohesion->getSteering()->getLinear();
	Vector2D tmpSeparate = mpSeparation->getSteering()->getLinear();
	Vector2D tmpWander = mpWander->getSteering()->getLinear();

	mLinear.setX((mLinear.getX() + (tmpAlign.getX() * mAlignmentWeight) + (tmpCohese.getX() * mCohesionWeight) + (tmpSeparate.getX() * mSeparationWeight) + (tmpWander.getX() * mWanderWeight)));
	mLinear.setY((mLinear.getY() + (tmpAlign.getY() * mAlignmentWeight) + (tmpCohese.getY() * mCohesionWeight) + (tmpSeparate.getY() * mSeparationWeight) + (tmpWander.getY() * mWanderWeight)));

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	//	* mpMover->getMaxVelocity()

	mAngular = mpWander->getSteering()->getAngular();


	//BLEND STEERING HERE
	return this;
}