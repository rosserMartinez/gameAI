#include "Game.h"
#include "KinematicUnit.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	gpGame->getPlayerUnit()->arrive(mPos);

	//just get the playerunit from unitmanager and tell that boy to move directly

}

