#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Trackable.h"
#include <allegro5\allegro.h>
#include "Vector2D.h"
#include <fstream>

//class Vector2D;

enum Property {
	ALIGNWEIGHT,
	COHESWEIGHT,
	SEPWEIGHT,
	WANDERWEIGHT
};

class InputManager : public Trackable
{
private:
	ALLEGRO_MOUSE_STATE mMouseState;
	ALLEGRO_KEYBOARD_STATE mKeyState;

	//inline bool getDebugStatus() { return mDebugToggled; };
	inline int getProperty() { return mSelectedProperty; };

	//inline void setDebugStatus(bool status) { mDebugToggled = status; };
	inline void setProperty(int newProperty) { mSelectedProperty = newProperty; };

	bool mDebugToggled;
	int mSelectedProperty;

	Vector2D mTextPos;
	Vector2D mHelpTextPos;
	int mYTextOffset;

	int mWeightChange;

	int mAWeightTmp;
	int mCWeightTmp;
	int mSWeightTmp;
	int mWWeightTmp;

	std::ofstream mFout;

	Property currentProperty;

public:
	InputManager();
	~InputManager();

	void checkInput();
	void displayDebugText();
	void displayHelpText();

};
#endif // !INPUTMANAGER_H
