#include <YSI_Coding\y_hooks>

public OnDataPlayerLoaded(playerid)
{
	ClearPlayerChat(playerid, 20);
	SendServerMessage(playerid, "Your account data has been "GREEN"successfully "WHITE"loaded.");
	if(IsPlayerUsingAndroid(playerid))
	{
		SendServerMessage(playerid, "You connected using "YELLOW"Mobile "WHITE"Platform");
	}
	else
	{
		SendServerMessage(playerid, "You connected using "GREEN"Desktop "WHITE"Platform");
	}
	return 1;
}