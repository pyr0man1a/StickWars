
#include "post_game.h"

#include "../lib/socket.h"
#include "../player.h"
#include "../game.h"

CPostGamePacket::CPostGamePacket(CPlayer* player, CGame* game)
{
	this->type = 0x06;
	this->size = 0x0F;

	WBUFL(packet, 0x02) = player->id;
	WBUFB(packet, 0x06) = player->GetColor();
	WBUFB(packet, 0x07) = player->GetTeam();
	WBUFB(packet, 0x08) = game->isWinner(player);
	WBUFL(packet, 0x09) = player->GetScore();
	WBUFB(packet, 0x0D) = player->GetWins();
	WBUFB(packet, 0x0E) = player->GetLosses();
}