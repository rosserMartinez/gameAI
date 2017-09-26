#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "DeleteUnitEvent.h"
#include "UnitManager.h"

DeleteUnitEvent::DeleteUnitEvent()
	:GameMessage(DELETE_MESSAGE)
{
}

DeleteUnitEvent::~DeleteUnitEvent()
{

}

void DeleteUnitEvent::process()
{
	gpGame->getUnitManager()->deleteRandomUnit();

}

