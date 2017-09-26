#pragma once

#include "GameMessage.h"
#include "Vector2D.h"

class Vector2D;

class EndGameEvent :public GameMessage
{
public:
	EndGameEvent();
	~EndGameEvent();

	void process();

private:

};