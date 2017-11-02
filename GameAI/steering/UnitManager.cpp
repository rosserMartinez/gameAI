#include "unitmanager.h"
#include <ctime>
#include "KinematicUnit.h"
#include "GraphicsBuffer.h"
#include "allegro5/color.h"
#include "allegro5/allegro_primitives.h"
#include "Game.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "GraphicsSystem.h"


UnitManager::UnitManager()//KinematicUnit* playerUnit)
{
	//mpPlayerUnit = playerUnit;

}

UnitManager::~UnitManager()
{
	//delete mpPlayerUnit;

	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		delete mpUnitList.at(i);
		mpUnitList.at(i) = NULL;
	}
}

//KinematicUnit* UnitManager::getPlayerUnit()
//{
//	return mpPlayerUnit;
//}

KinematicUnit* UnitManager::getUnit(int index)
{
	return mpUnitList.at(index);
}

void UnitManager::addUnit(KinematicUnit* unitToAdd)
{
	mpUnitList.push_back(unitToAdd);
}

void UnitManager::deleteRandomUnit()
{
	if (mpUnitList.size() == 0)
	{
		gpGame->endGame();
		return;
	}
	srand(unsigned(time(NULL)));

	int randomNum = 0; 
	
	randomNum = rand() % mpUnitList.size();

	delete mpUnitList.at(randomNum);

	mpUnitList.erase(mpUnitList.begin() + randomNum);

}

	 
void UnitManager::updateAndDrawAllUnits(float dt, GraphicsBuffer* targetBuffer)
{
	//mpPlayerUnit->update(dt);

	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		mpUnitList.at(i)->update(dt);
	}

	//mpPlayerUnit->draw(targetBuffer);

	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		mpUnitList.at(i)->draw(targetBuffer);
	}

}

void UnitManager::updateFlockWeights()
{
	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		mpUnitList.at(i)->flock();
	}
}