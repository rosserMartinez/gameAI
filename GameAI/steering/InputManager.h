#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"
#include <allegro5\allegro.h>

//class ALLEGRO_MOUSE_STATE;

class InputManager : public Trackable
{
private:
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyState;

	//ALLEGRO_FONT* mpGameFont;

public:
	InputManager();
	~InputManager();

	void checkInput();
	//void checkKeyboardState();
};
#endif // !INPUTMANAGER_H
