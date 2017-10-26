#include "Cohesion.h"
#include "KinematicUnit.h"
#include "Game.h"
#include "UnitManager.h"

Cohesion::Cohesion(KinematicUnit *pMover)
	:mpMover(pMover)
{
	mApplyDirectly = true;
}

Steering* Cohesion::getSteering()
{

	//mlinear is the linear velocity of the steering, vectors should work out that way
	// LETS SEE UH

	Vector2D tmp = (0, 0);
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
				tmp.setX(tmp.getX() + gpGame->getUnitManager()->getUnit(i)->getPosition().getX());
				tmp.setY(tmp.getY() + gpGame->getUnitManager()->getUnit(i)->getPosition().getY());

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

	tmp.setX(tmp.getX() - mpMover->getPosition().getX());
	tmp.setY(tmp.getY() - mpMover->getPosition().getY());

	///GOTTA GET A GRIP
	tmp.normalize();

	mLinear = tmp;

	return this;
}