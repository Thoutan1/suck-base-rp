#define CGEN_MEMORY   20000
#define MAX_PLAYERS   1000
#define YSI_YES_HEAP_MALLOC

#include <a_samp>
#include <a_mysql>
#include <samp_bcrypt>
#include <sscanf2>
#include <strlib>

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_va>
#include <YSI_Data\y_iterate>
#include <YSI_Server\y_colours>
#include <YSI_Visual\y_commands>
#include <YSI_Visual\y_dialog>

#include <easyDialog>
#include <streamer>
#include <skintags>
#include <command-guess>
#include <android-check>
/** Module */
#include "modules\server\config.inc"
#include "modules\server\storage.inc"
#include "modules\util\point.inc"
#include "modules\util\macro.inc"
#include "modules\util\variable.inc"
#include "modules\core\player\player_accounts.inc"
#include "modules\core\player\player_function.inc"
#include "modules\core\player\player_command.inc"
#include "modules\core\admin\admin.inc"

forward OnGameModeInitEx();

public OnGameModeInit()
{
	print("Starting configurate gamemode.");

	MySQL_INIT();
	CallLocalFunction(#OnGameModeInitEx, "");
	return 1;
}

public OnGameModeInitEx()
{
	LoadDynamicPoint();
    print("Gamemode successfully configurated.");
    return 1;
}

public OnGameModeExit()
{
	for (new i = 0, j = GetPlayerPoolSize(); i <= j; i++)
	{
		if (IsPlayerConnected(i))
		{
			MySQL_SaveDataPlayer(i);
			OnPlayerDisconnect(i, 1);
		}
	}

	mysql_close(MySQL_Handle);
	return 1;
}

public OnPlayerConnect(playerid)
{
    g_RaceCheck{playerid} ++;
	SetPlayerPos(playerid, 155.3337, -1776.4384, 14.8978+5.0);
	SetPlayerCameraPos(playerid, 155.3337, -1776.4384, 14.8978);
	SetPlayerCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128);
	InterpolateCameraLookAt(playerid, 156.2734, -1776.0850, 14.2128, 156.2713, -1776.0797, 14.7078, 5000, CAMERA_MOVE);
	SetTimerEx("PlayerCheck", 1000, false, "ii", playerid, g_RaceCheck{playerid});
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	ResetPlayerVariable(playerid);
    MySQL_SaveDataPlayer(playerid);
    return 1;
}


public OnPlayerSpawn(playerid)
{
	if(!IsPlayerSpawned(playerid))
	{
	    PlayerData[playerid][pSpawned] = true;
	    SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
	    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
	}
	return 1;
}

public OnPlayerText(playerid, text[])
{
	SendNearbyMessage(playerid, 20.0, -1, "%s says: %s", GetName(playerid), text);
    return 0;
}

function OnQueryExecutedSuccesfully(playerid, E_QUERY_TYPE:query_type, race_check)
{
	if(!IsPlayerConnected(playerid))
		return 0;

	switch(query_type)
	{
		case QUERY_CHECK_ACCOUNT:
		{
			if(race_check != g_RaceCheck[playerid])
                return Kick(playerid);

			if(cache_num_rows())
			{
				cache_get_value_name(0, "UCP", tempUCP[playerid]);
				cache_get_value_name_int(0, "ID", UcpData[playerid][ucpID]);
				cache_get_value_name_int(0, "AdminLevel", UcpData[playerid][ucpAdmin]);

				new str[252];
				format(str, sizeof(str), ""WHITE"Welcome back "LIGHTGREEN"%s!"WHITE" You have "YELLOW"3 minutes "WHITE"to logged in.\nPlease input your "RED"password "WHITE"of this account.", GetName(playerid));
				Dialog_ShowCallback(playerid, using public LoginPage<iiiis>, DIALOG_STYLE_PASSWORD, "Login - Page", str, "Login", "Exit");
			}
			else
			{
				Dialog_ShowCallback(playerid, using public PageRegister<iiiis>, DIALOG_STYLE_PASSWORD, "Page - Register", "Register", "Register", "Exit");
			}
		}

		case QUERY_CREATE_ACCOUNT:
		{
			UcpData[playerid][ucpID] = cache_insert_id();
			SendServerMessage(playerid, "Your account password have been generated successfully");
			UcpData[playerid][ucpLogged] = true;
			MySQL_CheckAccount(playerid);
		}

		case QUERY_LOAD_CHARACTER:
		{
			for (new i = 0; i < MAX_CHARS; i ++)
			{
				PlayerChar[playerid][i][0] = EOS;
			}
			for (new i = 0; i < cache_num_rows(); i ++)
			{
				cache_get_value_name(i, "Name", PlayerChar[playerid][i]);
			}
			ShowCharacterList(playerid);
		}
	}
	return 1;
}