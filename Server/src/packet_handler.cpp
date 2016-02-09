#include "packet_handler.h"
#include "server.h"
#include "game.h"
#include "lobby.h"
#include "Unit.h"
#include "Map.h"

#include "lib/showmsg.h"

#include "packets/packet.h"
#include "packets/account_creation.h"
#include "packets/action.h"
#include "packets/lobby_chat.h"
#include "packets/lobby_countdown.h"
#include "packets/lobby_list.h"
#include "packets/lobby_update.h"
#include "packets/login.h"
#include "packets/player_update.h"

namespace packethandler
{
	uint8 PacketSizes[256];
	void(*PacketParser[256])(session_data_t*, CPlayer*, int8*);

	void EmptyHandler(session_data_t* session, CPlayer* PPlayer, int8* data)
	{
		ShowWarning(CL_YELLOW"packet parser: unhandled packet %02hX from username %s\n" CL_RESET, RBUFB(data, 0), PPlayer->GetName());
	}

	//Login Status
	void Packet0x01(session_data_t* session, CPlayer* player, int8* data)
	{
		char* query = "SELECT id, handle, wins, losses FROM accounts WHERE handle = '%s' AND password = PASSWORD('%s');";

		char handle[11];
		memset(handle, 0, sizeof handle);
		memcpy(handle, data + 0x02, 10);
		char pass[17];
		memset(pass, 0, sizeof pass);
		memcpy(pass, data + 0x0C, 16);

		char escapedHandle[(sizeof handle) * 2 + 1];
		char escapedPass[(sizeof pass) * 2 + 1];

		Sql_EscapeStringLen(SqlHandle, escapedHandle, handle, sizeof handle);
		Sql_EscapeStringLen(SqlHandle, escapedPass, pass, sizeof pass);

		int ret = Sql_Query(SqlHandle, query, escapedHandle, escapedPass);

		if (ret != SQL_ERROR)
		{
			if (Sql_NumRows(SqlHandle) != 0 && Sql_NextRow(SqlHandle) == SQL_SUCCESS)
			{
				//fill in account specific stuff (wins/losses/etc)
				delete session->PPlayer;
				session->PPlayer = new CPlayer(Sql_GetUIntData(SqlHandle, 0));
				session->PPlayer->SetName(handle);
				session->PPlayer->SetWins(Sql_GetUIntData(SqlHandle, 2));
				session->PPlayer->SetLosses(Sql_GetUIntData(SqlHandle, 3));
				session->PPlayer->pushPacket(new CLoginPacket(session->PPlayer, LOGIN_SUCCESS));
				session->PPlayer->pushPacket(new CLobbyListPacket());
				ShowDebug("Player %s has logged in\n", session->PPlayer->GetName());
			}
			else
			{
				session->PPlayer->pushPacket(new CLoginPacket(session->PPlayer, LOGIN_INVALID_CRED));
			}
		}
		else
		{
			session->PPlayer->pushPacket(new CLoginPacket(session->PPlayer, LOGIN_UNDEF));
		}
	}
	//Account Creation
	void Packet0x02(session_data_t* session, CPlayer* player, int8* data)
	{
		char* query = "SELECT id, handle FROM accounts WHERE handle LIKE '%s';";

		char handle[11];
		memset(handle, 0, sizeof handle);
		memcpy(handle, data + 0x02, 10);
		char pass[17];
		memset(pass, 0, sizeof pass);
		memcpy(pass, data + 0x0C, 16);

		char escapedHandle[(sizeof handle) * 2 + 1];
		char escapedPass[(sizeof pass) * 2 + 1];

		Sql_EscapeStringLen(SqlHandle, escapedHandle, handle, sizeof handle);
		Sql_EscapeStringLen(SqlHandle, escapedPass, pass, sizeof pass);

		int ret = Sql_Query(SqlHandle, query, escapedHandle);

		//TODO: validate name/pass
		if (ret != SQL_ERROR)
		{
			if (Sql_NumRows(SqlHandle) == 0)
			{
				query = "INSERT INTO accounts (handle, password) VALUES('%s', PASSWORD('%s'));";

				ret = Sql_Query(SqlHandle, query, escapedHandle, escapedPass);

				if (ret != SQL_ERROR && Sql_AffectedRows(SqlHandle) == 1)
				{
					session->PPlayer->pushPacket(new CAccountCreatePacket(CREATE_SUCCESS));
					ShowDebug("Account %s has been created\n", handle);
				}
				else
				{
					session->PPlayer->pushPacket(new CAccountCreatePacket(CREATE_UNDEF));
				}
			}
			else
			{
				session->PPlayer->pushPacket(new CAccountCreatePacket(CREATE_NAME_TAKEN));
			}
		}
		else
		{
			session->PPlayer->pushPacket(new CAccountCreatePacket(CREATE_UNDEF));
		}
	}
	//Lobby Join
	void Packet0x03(session_data_t* session, CPlayer* player, int8* data)
	{
		uint32 lobbyID = WBUFW(data, 0x02);
		CLobby* lobby = lobbies::getLobby(lobbyID);

		if (lobbyID == 0 || !lobby)
		{
			lobby = lobbies::createLobby();
			lobby->addPlayer(player);
			lobby->setHost(player);
		}
		else if (lobby && lobby->playerList.size() < lobby->getMaxSize())
		{
			lobby->addPlayer(player);
		}
	}
	//Lobby Chat
	void Packet0x04(session_data_t* session, CPlayer* player, int8* data)
	{
		int length = WBUFB(data, 0x02);
		CLobby* lobby = lobbies::getLobby(player);
		if (lobby)
		{
			for (auto p : lobby->playerList)
			{
				if (p != player)
				{
					p->pushPacket(new CLobbyChatPacket(player, data + 0x03, length));
				}
			}
		}
	}
	//Lobby Action
	void Packet0x05(session_data_t* session, CPlayer* player, int8* data)
	{
		int action = WBUFB(data, 0x02);
		CLobby* lobby = lobbies::getLobby(player);

		if (lobby && lobby->getHost() == player)
		{
			if (action == 0x01 && lobby->getStatus() == LOBBY_IDLE && lobby->playerList.size() > 1)
			{
				lobby->startCountdown();
			}
			else if (action == 0x02 && lobby->getStatus() == LOBBY_STARTING)
			{
				lobby->cancelCountdown();
			}
		}
	}
	//Turn Change
	void Packet0x13(session_data_t* session, CPlayer* player, int8* data)
	{
		CGame* game = games::getGame(player);

		if (game && game->isActivePlayer(player))
		{
			game->endTurn();
		}
	}
	//Action
	void Packet0x15(session_data_t* session, CPlayer* player, int8* data)
	{
		CGame* game = games::getGame(player);
		Map* map = game->getMap();

		uint16 unitID = WBUFW(data, 0x02);
		uint8 xpos = WBUFB(data, 0x03);
		uint8 ypos = WBUFB(data, 0x04);
		uint8 action = WBUFB(data, 0x05);
		uint16 targetID = WBUFW(data, 0x07);

		Unit* initiator = game->getUnit(unitID);
		Unit* target = game->getUnit(targetID);

		switch (action)
		{
		case ACTION_MOVE:
			if (map->moveUnit(initiator, xpos, ypos))
			{
				game->sendAction(initiator, target, ACTION_MOVE, 0, 0, std::pair<uint8, uint8>(xpos, ypos));
				game->updateEntity(initiator);
			}
			break;
		case ACTION_ATTACK:
		{
			int targetdamage = 0, unitdamage = 0;
			if (map->attackUnit(initiator, xpos, ypos, target, &targetdamage, &unitdamage))
			{
				game->sendAction(initiator, target, ACTION_ATTACK, targetdamage, unitdamage, std::pair<uint8, uint8>(xpos, ypos));
				game->updateEntity(initiator);
				game->updateEntity(target);
				if (!game->getMap()->unitsRemain(target->getOwner()))
				{
					game->playerDefeated(target->getOwner());
				}
				player->pushPacket(new CPlayerUpdatePacket(player));
				game->checkVictoryCondition();
			}
		}
			break;
		case ACTION_CAPTURE:
			game->getMap()->captureStructure(xpos, ypos);
			break;
		case ACTION_PRODUCE:
			initiator = game->getMap()->produceUnit(xpos, ypos, player, (UnitType)unitID);
			game->updateEntity(initiator);
			player->pushPacket(new CPlayerUpdatePacket(player));
			break;
		default:
			break;
		}
	}

	void init()
	{
		for (uint8 i = 0; i < 255; ++i)
		{
			PacketSizes[i] = 0;
			PacketParser[i] = &EmptyHandler;
		}
		PacketSizes[0x01] = 0x1C; PacketParser[0x01] = &Packet0x01;
		PacketSizes[0x02] = 0x1C; PacketParser[0x02] = &Packet0x02;
		PacketSizes[0x03] = 0x04; PacketParser[0x03] = &Packet0x03;
		PacketSizes[0x04] = 0x00; PacketParser[0x04] = &Packet0x04;
		PacketSizes[0x05] = 0x03; PacketParser[0x05] = &Packet0x05;
		PacketSizes[0x13] = 0x02; PacketParser[0x13] = &Packet0x13;
		PacketSizes[0x15] = 0x09; PacketParser[0x15] = &Packet0x15;
	}
}