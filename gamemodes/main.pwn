#define MAX_PLAYERS   1000

#include <a_samp>
#include <a_mysql>
#include <samp_bcrypt>

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_va>
#include <YSI_Data\y_iterate>
#include <YSI_Server\y_colours>
#include <YSI_Visual\y_commands>

#include <easyDialog>
#include <skintags>
#include <command-guess>
#include <android-check>
/** Module */
#include "modules\server\config.inc"
#include "modules\server\storage.inc"
#include "modules\util\macro.inc"
#include "modules\util\variable.inc"
#include "modules\core\player\player_accounts.inc"
#include "modules\core\player\player_function.inc"
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

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
    if(success == COMMAND_UNDEFINED)
    {
        new guessCmd[32],
        dist = Command_Guess(guessCmd, cmdtext);

        if (dist < 3)
        {
            SendErrorMessage(playerid, ""WHITE"Command \"%s\" is not found, did you mean \"%s\"?", cmdtext, guessCmd);
        }
        else
        {
            SendErrorMessage(playerid, ""WHITE"Command \"%s\" is not found", cmdtext);
        }
        return COMMAND_OK;
    }
    else if(!IsPlayerSpawned(playerid))
    {
        SendErrorMessage(playerid, "You are not spawned!");
        Command_SetDeniedReturn(true);
        return COMMAND_DENIED;
    }

    return COMMAND_OK;
}