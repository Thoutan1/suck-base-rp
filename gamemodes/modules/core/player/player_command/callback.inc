#include <YSI_Coding\y_hooks>

hook OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
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

