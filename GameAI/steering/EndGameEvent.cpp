#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "EndGameEvent.h"
#include "UnitManager.h"

EndGameEvent::EndGameEvent()
	:GameMessage(ESCAPE_MESSAGE)
{
}

EndGameEvent::~EndGameEvent()
{

}

void EndGameEvent::process()
{
	gpGame->endLoop();
}

