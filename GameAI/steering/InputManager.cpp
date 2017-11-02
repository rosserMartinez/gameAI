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
#include <fstream>

InputManager::InputManager()
{
	srand(unsigned(time(NULL)));

	mAWeightTmp = gpGame->getAlignmentWeight();
	mCWeightTmp = gpGame->getCohesionWeight();
	mSWeightTmp = gpGame->getSeparationWeight();
	mWWeightTmp = gpGame->getWanderWeight();

	currentProperty = ALIGNWEIGHT;

	mWeightChange = 125;
	mYTextOffset = 25;
/*
	mATextPos.setX(35);
	mATextPos.setY(10);

	mCTextPos.setX(35);
	mCTextPos.setY(35);

	mSTextPos.setX(35);
	mSTextPos.setY(60);

	mWTextPos.setX(35);
	mWTextPos.setY(85);*/

	mHelpTextPos.setX(35);
	mHelpTextPos.setY(245);

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

	displayDebugText();

	//mpGraphicsSystem->swap();

	//get current keyboard state
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);

	if (al_key_down(&keyState, ALLEGRO_KEY_H))
	{
		displayHelpText();
	}
	gpGame->getGraphicsSystem()->swap();

	if (al_key_down(&keyState, ALLEGRO_KEY_I))
	{
		Vector2D aPos(mouseState.x, mouseState.y);
		Vector2D vel(0.0f, 0.0f);

		float xOffset = 10.0f;

		//its ya boid
		//create unit, give it flock and then increment the pos by the offset
		KinematicUnit* boid = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 125.0f, 100.0f);
		boid->flock();
		aPos.setX(aPos.getX() + xOffset);

		KinematicUnit* boid2 = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 125.0f, 100.0f);
		boid2->flock();
		aPos.setX(aPos.getX() + xOffset);

		KinematicUnit* boid3 = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 125.0f, 100.0f);
		boid3->flock();
		aPos.setX(aPos.getX() + xOffset);

		KinematicUnit* boid4 = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 125.0f, 100.0f);
		boid4->flock();
		aPos.setX(aPos.getX() + xOffset);

		KinematicUnit* boid5 = new KinematicUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), aPos, 1, vel, 0.0f, 125.0f, 100.0f);
		boid5->flock();

		GameMessage* pSpawnMessage = new SpawnUnitEvent(boid);
		gpGame->getMessageManager()->addMessage(pSpawnMessage, 0);

		GameMessage* pSpawnMessage2 = new SpawnUnitEvent(boid2);
		gpGame->getMessageManager()->addMessage(pSpawnMessage2, 0);

		GameMessage* pSpawnMessage3 = new SpawnUnitEvent(boid3);
		gpGame->getMessageManager()->addMessage(pSpawnMessage3, 0);

		GameMessage* pSpawnMessage4 = new SpawnUnitEvent(boid4);
		gpGame->getMessageManager()->addMessage(pSpawnMessage4, 0);

		GameMessage* pSpawnMessage5 = new SpawnUnitEvent(boid5);
		gpGame->getMessageManager()->addMessage(pSpawnMessage5, 0);
	}

	if (al_key_down(&keyState, ALLEGRO_KEY_D))
	{
		//deleteunit event
		GameMessage* pDeleteMessage = new DeleteUnitEvent();
		gpGame->getMessageManager()->addMessage(pDeleteMessage, 0);
	}


	//CHANGE PROPERTY
	if (al_key_down(&keyState, ALLEGRO_KEY_A))
	{
		currentProperty = ALIGNWEIGHT;
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_C))
	{
		currentProperty = COHESWEIGHT;
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_S))
	{
		currentProperty = SEPWEIGHT;
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_W))
	{
		currentProperty = WANDERWEIGHT;
	}


	if (al_key_down(&keyState, ALLEGRO_KEY_EQUALS))
	{
		
		if (currentProperty == ALIGNWEIGHT)
		{
			mAWeightTmp += mWeightChange;
		}
		else if (currentProperty == COHESWEIGHT)
		{
			mCWeightTmp += mWeightChange;
		}
		else if (currentProperty == SEPWEIGHT)
		{
			mSWeightTmp += mWeightChange;
		}
		else if (currentProperty == WANDERWEIGHT)
		{
			mWWeightTmp += mWeightChange;
		}
	}

	if (al_key_down(&keyState, ALLEGRO_KEY_MINUS))
	{
		if (currentProperty == ALIGNWEIGHT)
		{
			mAWeightTmp -= mWeightChange;
		}
		else if (currentProperty == COHESWEIGHT)
		{
			mCWeightTmp -= mWeightChange;
		}
		else if (currentProperty == SEPWEIGHT)
		{
			mSWeightTmp -= mWeightChange;
		}
		else if (currentProperty == WANDERWEIGHT)
		{
			mWWeightTmp -= mWeightChange;
		}
	}


	if (al_key_down(&keyState, ALLEGRO_KEY_S) && (al_key_down(&keyState, ALLEGRO_KEY_LCTRL)))
	{
		//apply and save data

		gpGame->setAlignmentWeight(mAWeightTmp);
		gpGame->setCohesionWeight(mCWeightTmp);
		gpGame->setSeparationWeight(mSWeightTmp);
		gpGame->setWanderWeight(mWWeightTmp);

		gpGame->getUnitManager()->updateFlockWeights();

		mFout.open(gpGame->getDebugStats());

		mFout << mAWeightTmp << std::endl
			<< mCWeightTmp << std::endl
			<< mSWeightTmp << std::endl
			<< mWWeightTmp << std::endl;

		mFout.close();
	}


	//if escape key was down then exit the loop
	if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
	{
		GameMessage* pEscapeMessage = new EndGameEvent();
		gpGame->getMessageManager()->addMessage(pEscapeMessage, 0);
	}
}


void InputManager::displayDebugText()
{
	int lineNum = 0;

	//alignmentweight
	std::string aStr = "ALIGNMENT WEIGHT = " + std::to_string(mAWeightTmp);
	//cohesion weight
	std::string cStr = "COHESION WEIGHT = " + std::to_string(mCWeightTmp);
	//separation weight
	std::string sStr = "SEPARATION WEIGHT = " + std::to_string(mSWeightTmp);
	//wander weight
	std::string wStr = "WANDER WEIGHT = " + std::to_string(mWWeightTmp);
	
	//jeff i know the formatting here is real gross but look at how nice and organized it looks, forgive me for the lineNum++ after my lines
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "***************************"); lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "*** D E B U G   I N F O ***"); lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "***************************");	lineNum++;
	if (currentProperty == ALIGNWEIGHT)
	{
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, aStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, cStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, sStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, wStr.c_str());					lineNum++;
	}
	else if (currentProperty == COHESWEIGHT)
	{
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, aStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, cStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, sStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, wStr.c_str());					lineNum++;
	}
	else if (currentProperty == SEPWEIGHT)
	{
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, aStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, cStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, sStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, wStr.c_str());					lineNum++;
	}
	else if (currentProperty == WANDERWEIGHT)
	{
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, aStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, cStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, sStr.c_str());					lineNum++;
		al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, wStr.c_str());					lineNum++;
	}
	
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "***************************"); lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mTextPos.getX(), mTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "HOLD THE H KEY FOR HELP!");   lineNum++;


}

void InputManager::displayHelpText()
{
	int lineNum = 0;

	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mHelpTextPos.getX(), mHelpTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "******************************************");	lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mHelpTextPos.getX(), mHelpTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "I inserts 5 boids, D deletes a random boid");	lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mHelpTextPos.getX(), mHelpTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "A C S W selects a weight, +/- alters weight");	lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mHelpTextPos.getX(), mHelpTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "CTRL-S applies current altered weight values");	    lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mHelpTextPos.getX(), mHelpTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "and saves temp changes for next time!");	    lineNum++;
	al_draw_text(gpGame->getFont(), al_map_rgb(0, 0, 0), mHelpTextPos.getX(), mHelpTextPos.getY() + (lineNum * mYTextOffset), ALLEGRO_ALIGN_LEFT, "******************************************");	lineNum++;

}