#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"
#include <allegro5\allegro.h>

const std::string velocityStr = "Velocity: ";
const std::string radiusStr = "RRadius : ";
const std::string angularStr = "Angular : ";

enum Property {
	VELOCITY,
	RADIUS,
	ANGULAR
};

class InputManager : public Trackable
{
private:
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyState;

	//inline bool getDebugStatus() { return mDebugToggled; };
	//inline int getProperty() { return mSelectedProperty; };

	//inline void setDebugStatus(bool status) { mDebugToggled = status; };
	//inline void setProperty(int newProperty) { mSelectedProperty = newProperty; };

	bool mDebugToggled;
	int mSelectedProperty;

public:
	InputManager();
	~InputManager();

	void checkInput();

};
#endif // !INPUTMANAGER_H
