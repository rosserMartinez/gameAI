#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "SpawnUnitEvent.h"
#include "UnitManager.h"

SpawnUnitEvent::SpawnUnitEvent(KinematicUnit* unitToSpawn)
	:GameMessage(SPAWN_MESSAGE)
	, mUnitToSpawn(unitToSpawn)
{
}

SpawnUnitEvent::~SpawnUnitEvent()
{

}

void SpawnUnitEvent::process()
{
	gpGame->getUnitManager()->addUnit(mUnitToSpawn);
}

