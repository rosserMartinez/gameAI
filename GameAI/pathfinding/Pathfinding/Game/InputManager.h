#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"
#include <allegro5\allegro.h>
#include "Vector2D.h"

class DijkstraPathfinder;
class AStarPathfinder;

class InputManager : public Trackable
{
private:
	//ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyState;

	DijkstraPathfinder* mpDijkstra; //yikestra
	AStarPathfinder* mpAStar;
	
public:
	InputManager();
	~InputManager();

	void checkInput();

};
#endif // !INPUTMANAGER_H
