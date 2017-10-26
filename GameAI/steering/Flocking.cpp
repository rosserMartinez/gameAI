#include "Flocking.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"
//#include "Steering.h"
#include "Alignment.h"
#include "Cohesion.h"
#include "Separation.h"

Flocking::Flocking(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;

	mpAlignment = new Alignment(pMover);
	mpCohesion = new Cohesion(pMover);
	mpSeparation = new Separation(pMover);


	//VELOCITY MATCHING????
}

Steering* Flocking::getSteering()
{

	///VELOCITY MATCHING?!?!?!?!?!?
	//mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();

	Vector2D tmpAlign = mpAlignment->getSteering()->getLinear();
	Vector2D tmpCohese = mpCohesion->getSteering()->getLinear();
	Vector2D tmpSeparate = mpSeparation->getSteering()->getLinear();

	//mLinear.setX(mLinear.getX() + (tmpAlign.getX() * mAlignmentWeight) + (tmpCohese.getX() * mCohesionWeight) + (tmpSeparate.getX() * mSeparationWeight));
	//mLinear.setY(mLinear.getY() + (tmpAlign.getY() * mAlignmentWeight) + (tmpCohese.getY() * mCohesionWeight) + (tmpSeparate.getY() * mSeparationWeight));

	//mLinear.normalize();

	//BLEND STEERING HERE
	return this;
}