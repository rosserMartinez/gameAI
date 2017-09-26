#include "InputManager.h"
#include <sstream>
#include "Vector2D.h"
#include "GameMessage.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "Game.h"
#include <stdio.h>
#include "GraphicsSystem.h"
#include <ctime>
#include "SpawnUnitEvent.h"
#include "DeleteUnitEvent.h"
#include "EndGameEvent.h"
#include "SpriteManager.h"
#include "UnitManager.h"

InputManager::InputManager()
{
	srand(unsigned(time(NULL)));
}

InputManager::~InputManager()
{

}

void InputManager::checkInput()
{
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		GameMessage* pMessage = new PlayerMoveToMessage(pos);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}

	//create mouse text
	std::stringstream mousePos;
	mousePos << mouseState.x << ":" << mouseState.y;

	//write text at mouse position
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());

	gpGame->getGraphicsSystem()->swap();
	//mpGraphicsSystem->swap();

	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	if (al_key_down(&keyState, ALLEGRO_KEY_A))
	{

		Vector2D tempPos = gpGame->getUnitManager()->getPlayerUnit()->getPosition();
		Vector2D aPos(0.0f, 0.0f);
		Vector2D vel(0.0f, 0.0f);

		//check pos to see if its out of bounds
		if (tempPos.getX() > aRange)
		{
			aPos = tempPos;
			aPos.setX(tempPos.getX() - aRange);
		}
		else if (tempPos.getX() + aRange < gpGame->getGraphicsSystem()->getWidth())
		{
			aPos = tempPos;
			aPos.setX(tempPos.getX() + aRange);

		}

		if (tempPos.getY() > aRange)
		{
			aPos.setY(tempPos.getY() - aRange);

		}
		else if (tempPos.getY() + aRange > gpGame->getGraphicsSystem()->getHeight())
		{
			aPos.setY(tempPos.getY() - aRange);
		}
		

		//make new unit here
		KinematicUnit* arriveTmp = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 200.0f, 100.0f);
		arriveTmp->dynamicArrive(gpGame->getUnitManager()->getPlayerUnit());

		GameMessage* pSpawnMessage = new SpawnUnitEvent(arriveTmp);
		gpGame->getMessageManager()->addMessage(pSpawnMessage, 0);
	}

	if (al_key_down(&keyState, ALLEGRO_KEY_S))
	{
		//Vector2D sPos(mouseState.x, mouseState.y);

		Vector2D tempPos = gpGame->getUnitManager()->getPlayerUnit()->getPosition();
		Vector2D sPos(0.0f, 0.0f);
		Vector2D vel(0.0f, 0.0f);

		//check pos to see if its out of bounds
		if (tempPos.getX() > sRange)
		{
			sPos = tempPos;
			sPos.setX(tempPos.getX() - sRange);
		}
		else if (tempPos.getX() + sRange < gpGame->getGraphicsSystem()->getWidth())
		{
			sPos = tempPos;
			sPos.setX(tempPos.getX() + sRange);

		}
		
		if (tempPos.getY() > sRange)
		{
			//sPos = tempPos;
			sPos.setY(tempPos.getY() - sRange);

		}
		else if (tempPos.getY() + sRange > gpGame->getGraphicsSystem()->getHeight())
		{
			//sPos = tempPos;
			sPos.setY(tempPos.getY() - sRange);
		}

		//make new unit here
		KinematicUnit* seekTmp = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), sPos, 1, vel, 0.0f, 200.0f, 100.0f);
		seekTmp->dynamicSeek(gpGame->getUnitManager()->getPlayerUnit());

		GameMessage* pSpawnMessage = new SpawnUnitEvent(seekTmp);
		gpGame->getMessageManager()->addMessage(pSpawnMessage, 0);

	}
	if (al_key_down(&keyState, ALLEGRO_KEY_D))
	{
		//deleteunit event
		GameMessage* pDeleteMessage = new DeleteUnitEvent();
		gpGame->getMessageManager()->addMessage(pDeleteMessage, 0);
	}

	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		GameMessage* pEscapeMessage = new EndGameEvent();
		gpGame->getMessageManager()->addMessage(pEscapeMessage, 0);
	}
}

//void InputManager::checkKeyboardState()
//{

	////get current keyboard state
	//ALLEGRO_KEYBOARD_STATE keyState;
	//al_get_keyboard_state(&keyState);

	////if escape key was down then exit the loop
	//if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	//{
	//	mShouldExit = true;
	//}
//}