#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class DeleteUnitEvent :public GameMessage
{
public:
	DeleteUnitEvent();
	~DeleteUnitEvent();

	void process();

private:
};