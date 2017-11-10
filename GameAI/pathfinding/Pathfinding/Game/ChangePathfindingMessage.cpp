#include "ChangePathfindingMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Grid.h"
#include "GridGraph.h"

ChangePathfindingMessage::ChangePathfindingMessage(GridPathfinder* pathfinder)
	:GameMessage(PATH_TO_MESSAGE)
	, mpPathfinder(pathfinder)
{
}

ChangePathfindingMessage::~ChangePathfindingMessage()
{
}

void ChangePathfindingMessage::process()
{
	dynamic_cast<GameApp*>(gpGame)->setPathfinder(mpPathfinder);
}
