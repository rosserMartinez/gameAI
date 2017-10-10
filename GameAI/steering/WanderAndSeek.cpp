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
	mApplyDirectly = true;
}

Steering* WanderAndSeek::getSteering()
{
	
	//Steering* tmpSteering = new Steering();

	//float behaviorWeight = .5f; // 1 / 2
	//Vector2D tmpLinearAvoid;
	//Vector2D tmpLinearSeekWander;


	float shortestTime = infinityTM;
	bool collisionFound = false;
	int indexForTmpTarget;
	float tmpSep;
	float tmpDist;
	Vector2D tmpRelativePos;
	Vector2D tmpRelativeVel;

	for (size_t i = 0; i < gpGame->getUnitManager()->getUnitListSize(); ++i)
	{


		Vector2D relativePos = gpGame->getUnitManager()->getUnitList().at(i)->getPosition() - mpMover->getPosition();
		Vector2D relativeVel = gpGame->getUnitManager()->getUnitList().at(i)->getVelocity() - mpMover->getVelocity();
		float relativeSpeed = relativeVel.getLength();
		float dotProduct = (relativePos.getX() * relativeVel.getX()) + (relativePos.getY() * relativeVel.getY());
		float timeTilCollision = dotProduct / (relativeSpeed * relativeSpeed);

		float dist = relativePos.getLength();
		float sep = dist - (relativeSpeed * shortestTime);
		if (sep > 2 * mCollCheckRadius)
		{
			if (timeTilCollision > 0 && timeTilCollision < shortestTime /*&& collisionFound == false*/)
			{
				collisionFound = true;
				shortestTime = timeTilCollision;
				tmpRelativePos = relativePos;
				tmpRelativeVel = relativeVel;
				tmpDist = dist;
				tmpSep = sep;
				indexForTmpTarget = i;
			}
		}
	}

	if (collisionFound)
	{
		//relative pos for the sake of this loop here
		Vector2D tmpPos;
		//rest of code
		if (tmpSep <= 0 || tmpDist < 2 * mCollCheckRadius)
		{
			tmpPos = gpGame->getUnitManager()->getUnitList().at(indexForTmpTarget)->getPosition() - mpMover->getPosition();
		}
		else
		{
			tmpPos = tmpRelativePos + (tmpRelativeVel * shortestTime);
		}

		//avoid
		tmpPos.normalize();
		mLinear = tmpPos * mpMover->getMaxAcceleration();
		//tmpLinearAvoid = tmpPos * mpMover->getMaxAcceleration();


		//return this;
	}
	else
	{
		float a = (mpTarget->getPosition() - mpMover->getPosition()).getX();
		float b = (mpTarget->getPosition() - mpMover->getPosition()).getY();

		if ((a * a) + (b * b) < mReactionRadius)
		{
			//if (!mShouldFlee)
			//{
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
			//}
			//else
			//{
			//mLinear = mpMover->getPosition() - mpTarget->getPosition();
			//}

			mLinear.normalize();
			mLinear *= mpMover->getMaxVelocity();
			//mAngular = mpMover->getOrientation();
			mAngular = Kinematic::getOrientationFromVelocity(mpMover->getOrientation(), mLinear);

			//tmpLinearSeekWander = mpMover->getMaxVelocity();
			//return this;

		}
		else
		{
			mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
			mAngular = mpMover->getOrientation() + (genRandomBinomial() * mMAX_WANDER_ROTATION);

			//tmpLinearSeekWander = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();

			//return this;
		}
	}

	return this;

}