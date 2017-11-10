#pragma once

#include "GameMessage.h"
#include "Vector2D.h"
#include "GridPathfinder.h"

class ChangePathfindingMessage :public GameMessage
{
public:
	ChangePathfindingMessage(GridPathfinder* pathfinder);
	~ChangePathfindingMessage();

	const GridPathfinder* getPathfinder() const { return mpPathfinder; };

	void process();

private:
	GridPathfinder* mpPathfinder;
};