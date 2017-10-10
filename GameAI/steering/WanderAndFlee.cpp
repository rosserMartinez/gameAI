#include "WanderAndFlee.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"


WanderAndFlee::WanderAndFlee(KinematicUnit *pMover, KinematicUnit* pTarget, float newReactionRadius, bool shouldFlee)
	:mpMover(pMover)
	, mpTarget(pTarget)
	, mShouldFlee(shouldFlee)
	, mReactionRadius(newReactionRadius)
{
	mApplyDirectly = true;
}

Steering* WanderAndFlee::getSteering()
{


	float shortestTime = alsoInfinityTM;
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


		return this;
	}
	else
	{
		float a = (mpMover->getPosition() - mpTarget->getPosition()).getX();
		float b = (mpMover->getPosition() - mpTarget->getPosition()).getY();

		if ((a * a) + (b * b) < mReactionRadius)
		{
			//std::cout << "yikes \n";

			//if (!mShouldFlee)
			//{
			//mLinear = mpTarget->getPosition() - mpMover->getPosition();
			//}
			//else
			//{
			mLinear = mpMover->getPosition() - mpTarget->getPosition();
			//}

			mLinear.normalize();
			mLinear *= mpMover->getMaxVelocity();
			mAngular = mpMover->getOrientationFromVelocity(mpMover->getRotation(), mLinear);
			return this;

		}
		else
		{
			mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
			mAngular = mpMover->getOrientation() + (genRandomBinomial() * MAX_WANDER_ROTATION);
			return this;
		}
	}
}