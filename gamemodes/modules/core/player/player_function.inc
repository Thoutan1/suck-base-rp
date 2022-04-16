stock IsPlayerSpawned(playerid)
	return PlayerData[playerid][pSpawned];

stock GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
 	GetPlayerName(playerid,name,sizeof(name));
	return name;
}

stock IsRoleplayName(const player[])
{
    for(new n = 0; n < strlen(player); n++)
    {
        if (player[n] == '_' && player[n+1] >= 'A' && player[n+1] <= 'Z') return 1;
        if (player[n] == ']' || player[n] == '[') return 0;
	}
    return 0;
}

stock IsPlayerNearPlayer(playerid, targetid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;
	GetPlayerPos(targetid, fX, fY, fZ);
	return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

stock SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args
	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start
	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
        foreach (new i : Player)
		{
			if (IsPlayerNearPlayer(i, playerid, radius) && IsPlayerSpawned(i))
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (IsPlayerNearPlayer(i, playerid, radius) && IsPlayerSpawned(i))
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[145];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}

stock ClearPlayerChat(playerid, count)
{
    for (new i = 0; i < count; i ++)
	{
        SendClientMessage(playerid, -1,"");
    }
}

stock GetRandomMaleSkin()
{
    new maleSkin = random(16);
    switch(maleSkin)
    {
        case 1, 2, 7, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 66, 67, 240: return GetRandomMaleSkin();
    }
    return maleSkin;
}

stock GetRandomFemaleSkin()
{
    new FemaleSkin = random(7);
    switch(FemaleSkin)
    {
        case 226, 233, 224, 216, 91, 56: return GetRandomFemaleSkin();
    }
    return FemaleSkin;
}

stock ReturnName(playerid, underscore = 1)
{
    new
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));

    if(!underscore) {
        for (new i = 0, len = strlen(name); i < len; i ++) {
                if(name[i] == '_') name[i] = ' ';
        }
    }
    return name;
}

stock Acronym(const string[])
{
    new phrase[32], index = 0;

    for (new i = 0, len = strlen(string); i != len; i ++)
    {
        if (('A' <= string[i] <= 'Z') && (i == 0 || string[i - 1] == ' '))
            phrase[index++] = string[i];
    }
    return phrase;
}