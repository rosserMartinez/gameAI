#include "unitmanager.h"
#include <ctime>
#include "KinematicUnit.h"
#include "GraphicsBuffer.h"

UnitManager::UnitManager(KinematicUnit* playerUnit)
{
	mpPlayerUnit = playerUnit;

}

UnitManager::~UnitManager()
{
	delete mpPlayerUnit;
}

KinematicUnit* UnitManager::getPlayerUnit()
{
	return mpPlayerUnit;
}

void UnitManager::addUnit(KinematicUnit* unitToAdd)
{
	mpUnitList.push_back(unitToAdd);
}

void UnitManager::deleteRandomUnit()
{
	srand(unsigned(time(NULL)));

	int randomNum = rand() % mpUnitList.size();
	 
	delete mpUnitList.at(randomNum);

	mpUnitList.erase(mpUnitList.begin() + randomNum);
}

	 
void UnitManager::updateAndDrawAllUnits(float dt, GraphicsBuffer* targetBuffer)
{
	mpPlayerUnit->update(dt);

	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		mpUnitList.at(i)->update(dt);
	}

	mpPlayerUnit->draw(targetBuffer);

	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		mpUnitList.at(i)->draw(targetBuffer);
	}

}