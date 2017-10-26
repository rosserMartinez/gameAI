#include "Alignment.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

Alignment::Alignment(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* Alignment::getSteering()
{
	//wander stuff
	///mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
	///mAngular = mpMover->getOrientation() + ( genRandomBinomial() * MAX_WANDER_ROTATION );

	//mlinear is the linear velocity of the steering, vectors should work out that way
	// LETS SEE UH

	Vector2D tmp = (0,0);
	int flockCount = 0;
	float a, b;

	for (size_t i = 0; i < gpGame->getUnitManager()->getUnitListSize(); i++)
	{
		//check if the unit in question is not THIS unit, hoping it doesnt gimme 
		//some WACK ASS behavior
		if (gpGame->getUnitManager()->getUnit(i)->getPosition().getX() !=
			mpMover->getPosition().getX() && 
			gpGame->getUnitManager()->getUnit(i)->getPosition().getY() !=
			mpMover->getPosition().getY())
		{
			a = (gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition()).getX();
			b = (gpGame->getUnitManager()->getUnit(i)->getPosition() - mpMover->getPosition()).getY();

			if ((a * a) + (b * b) < mReactionRadius)
			{
				tmp.setX(tmp.getX() + gpGame->getUnitManager()->getUnit(i)->getVelocity().getX());
				tmp.setY(tmp.getY() + gpGame->getUnitManager()->getUnit(i)->getVelocity().getY());

				++flockCount;
			}
		}

	}
	if (flockCount == 0)
	{
		mLinear = tmp;
		return this;
	}

	tmp.setX(tmp.getX() / flockCount);
	tmp.setY(tmp.getY() / flockCount);

	tmp.normalize();

	mLinear = tmp;

	return this;
}