#pragma once

#include "GameMessage.h"
#include "Vector2D.h"
#include "KinematicUnit.h"

class Vector2D;

class SpawnUnitEvent :public GameMessage
{
public:
	SpawnUnitEvent(KinematicUnit* unitToSpawn);
	~SpawnUnitEvent();

	void process();

private:
	//Vector2D mPos;
	KinematicUnit* mUnitToSpawn;
};