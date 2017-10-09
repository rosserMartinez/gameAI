#include "WanderAndSeek.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"


WanderAndSeek::WanderAndSeek(KinematicUnit *pMover, KinematicUnit* pTarget,  float newReactionRadius, bool shouldFlee)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mShouldFlee(shouldFlee)
	, mReactionRadius(newReactionRadius)
{
	mApplyDirectly = false;
}

Steering* WanderAndSeek::getSteering()
{
	float a = (mpMover->getPosition() - gpGame->getUnitManager()->getPlayerUnit()->getPosition()).getX();
	float b = (mpMover->getPosition() - gpGame->getUnitManager()->getPlayerUnit()->getPosition()).getY();

	if ((a * a) + (b * b) < mReactionRadius)
	{


		//if (!mShouldFlee)
		//{
		mLinear = mpTarget->getPosition() - mpMover->getPosition();
		//}
		//else
		//{
		//	mLinear = mpMover->getPosition() - mpTarget->getPosition();
		//}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
		return this;

	}
	else
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() + (genRandomBinomial() * MAX_WANDER_ROTATION);
		return this;
	}
}