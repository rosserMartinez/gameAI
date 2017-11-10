#include "InputManager.h"
#include <sstream>
#include "Vector2D.h"
#include "GameMessage.h"
#include "GameMessageManager.h"
#include "Game.h"
#include <stdio.h>
#include "GraphicsSystem.h"
#include <ctime>
#include "SpriteManager.h"
#include <fstream>
#include "ChangePathfindingMessage.h"
#include "GameApp.h"
#include "AStarPathfinder.h"
#include "DijkstraPathfinder.h"
#include "GridGraph.h"
#include "GridPathfinder.h"
#include "PathToMessage.h"

InputManager::InputManager()
{
	srand(unsigned(time(NULL)));

}

InputManager::~InputManager()
{

}

void InputManager::checkInput()
{

		static Vector2D lastPos(0.0f, 0.0f);

	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		Vector2D pos(mouseState.x, mouseState.y);
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			dynamic_cast<GameApp*>(gpGame)->getMessageManager()->addMessage(pMessage, 0);
			lastPos = pos;
		}
	}

	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	//CHANGE PROPERTY
	if (al_key_down(&keyState, ALLEGRO_KEY_A))
	{
		////ASTAR
		lastPos = (0.0f, 0.0f);

		Graph* gridGraphCast = dynamic_cast<GameApp*>(gpGame)->getGridGraph();
		mpAStar = new AStarPathfinder(gridGraphCast);

		dynamic_cast<GameApp*>(gpGame)->setDijkstra(false);

		GameMessage* pAStarMessage = new ChangePathfindingMessage(mpAStar);
		dynamic_cast<GameApp*>(gpGame)->getMessageManager()->addMessage(pAStarMessage, 0);
	}

	if (al_key_down(&keyState, ALLEGRO_KEY_D))
	{
		////DIJKSTRA
		lastPos = (0.0f, 0.0f);

		Graph* gridGraphCast = dynamic_cast<GameApp*>(gpGame)->getGridGraph();
		mpDijkstra = new DijkstraPathfinder(gridGraphCast);

		dynamic_cast<GameApp*>(gpGame)->setDijkstra(true);

		GameMessage* pDijkstraMessage = new ChangePathfindingMessage(mpDijkstra);
		dynamic_cast<GameApp*>(gpGame)->getMessageManager()->addMessage(pDijkstraMessage, 0);
	}

}
