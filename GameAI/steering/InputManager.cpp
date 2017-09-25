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
		int range = 200;

		Vector2D tempPos = gpGame->getUnitManager()->getPlayerUnit()->getPosition();
		Vector2D aPos(0.0f, 0.0f);

		//calculate random pos over here but do that after you know it works
		Vector2D vel(0.0f, 0.0f);

		//if (tempPos.getX() - range < 0)
		//{
		//	aPos = (tempPos.getX() - range, tempPos.getY());
		//}
		//else if (tempPos.getX() + range < gpGame->getGraphicsSystem()->getWidth())
		//{
		//	aPos = (tempPos.getX() + range, tempPos.getY());
		//}
		//else if (tempPos.getY() - range < 0)
		//{
		//	aPos = (tempPos.getX(), tempPos.getY() - range);
		//}
		//else if (tempPos.getY() + range < gpGame->getGraphicsSystem()->getHeight())
		//{
		//	aPos = (tempPos.getX(), tempPos.getY() + range);
		//}

		

		//make new unit here
		KinematicUnit* arriveTmp = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 200.0f, 100.0f);
		arriveTmp->dynamicArrive(gpGame->getUnitManager()->getPlayerUnit());

		GameMessage* pSpawnMessage = new SpawnUnitEvent(arriveTmp);
		gpGame->getMessageManager()->addMessage(pSpawnMessage, 0);
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_S))
	{
		Vector2D sPos(mouseState.x, mouseState.y);

		//calculate random pos over here but do that after you know it works
		Vector2D vel(0.0f, 0.0f);
		//100 range

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