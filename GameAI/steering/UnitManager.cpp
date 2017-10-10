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


UnitManager::UnitManager(KinematicUnit* playerUnit)
{
	mpPlayerUnit = playerUnit;

}

UnitManager::~UnitManager()
{
	delete mpPlayerUnit;

	for (size_t i = 0; i < mpUnitList.size(); ++i)
	{
		delete mpUnitList.at(i);
		mpUnitList.at(i) = NULL;
	}


	for (size_t i = 0; i < mpWallList.size(); ++i)
	{
		delete mpWallList.at(i);
		mpWallList.at(i) = NULL;
	}
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

	//dont look jeff please   SHIELD YOUR EYES
	// IM SORRY
	al_draw_filled_rectangle(0, 0, 1024, 50, al_map_rgb(160,32,240));
	al_draw_filled_rectangle(984, 0, 1024, 768, al_map_rgb(160, 32, 240));
	al_draw_filled_rectangle(0, 718, 1024, 768, al_map_rgb(160, 32, 240));
	al_draw_filled_rectangle(0, 0, 50, 768, al_map_rgb(160, 32, 240));

}

void UnitManager::setReactionRadius(float newRadius)
{
	mCurrentReactionRadius = newRadius;
}

void UnitManager::setUnitWalls()
{
	KinematicUnit* tmpUnit;
	int wallCount = 15;
	Vector2D spawnPos = (0,0);

	float wallOffset = 25;
	float xOffset = gpGame->getGraphicsSystem()->getWidth() - (wallOffset * 2);
	float yOffset = gpGame->getGraphicsSystem()->getHeight() - (wallOffset);

	float xSize = gpGame->getGraphicsSystem()->getWidth() / wallCount;
	float ySize = gpGame->getGraphicsSystem()->getHeight() / wallCount;

	//horizontal
	for (size_t i = 0; i < wallCount; i++)
	{
		spawnPos = (0, wallOffset);
		float newX = i * xSize;

		spawnPos.setX(newX);

		tmpUnit = new KinematicUnit(gpGame->getSpriteManager()->getSprite(PLAYER_ICON_SPRITE_ID), spawnPos, 1, (0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
		addWall(tmpUnit);
		
		spawnPos.setY(yOffset);

		tmpUnit = new KinematicUnit(gpGame->getSpriteManager()->getSprite(PLAYER_ICON_SPRITE_ID), spawnPos, 1, (0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
		addWall(tmpUnit);



	}

	//vertical
	for (size_t i = 0; i < wallCount; i++)
	{
		spawnPos = (wallOffset, 0);
		float newY = i * ySize;

		spawnPos.setY(newY);

		tmpUnit = new KinematicUnit(gpGame->getSpriteManager()->getSprite(PLAYER_ICON_SPRITE_ID), spawnPos, 1, (0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
		addWall(tmpUnit);

		spawnPos.setX(xOffset);

		tmpUnit = new KinematicUnit(gpGame->getSpriteManager()->getSprite(PLAYER_ICON_SPRITE_ID), spawnPos, 1, (0.0f, 0.0f), 0.0f, 0.0f, 0.0f);
		addWall(tmpUnit);

	
	}

	//i think the last memory leak is here but it wont delete without pausing proably because im instantiating it so many times

	//delete tmpUnit;
	//tmpUnit = NULL;

}