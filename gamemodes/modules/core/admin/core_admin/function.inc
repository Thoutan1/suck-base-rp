stock SendAdminMessage(color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args
	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start
	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
        foreach (new i : Player) if(IsPlayerSpawned(i))
		{
			if (UcpData[i][ucpAdmin] >= 1)
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player) if(IsPlayerSpawned(i))
	{
		if (UcpData[i][ucpAdmin] >= 1)
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock GetPlayerAdminLevel(playerid)
{
    return UcpData[playerid][ucpAdmin];
}

stock SetPlayerAdmin(playerid, level)
{
    UcpData[playerid][ucpAdmin] = level;
    return 1;
}

stock GetAdminRankName(playerid)
{
    new name[128];
    switch(UcpData[playerid][ucpAdmin])
    {
        case ADMIN_LEVEL_ONE: name = "Helper";
        case ADMIN_LEVEL_TWO: name = "Moderator";
        case ADMIN_LEVEL_THREE: name = "General Admin";
        case ADMIN_LEVEL_FOUR: name = "Senior Admin";
        case ADMIN_LEVEL_FIVE: name = "High Admin";
        case ADMIN_LEVEL_SIX: name = "Game Master";
    }
    return name;
}