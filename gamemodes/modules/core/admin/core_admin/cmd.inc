YCMD:a(playerid, params[], help)
{
    if(UcpData[playerid][ucpAdmin] < 1)
        return PlayerPermissionError(playerid);
    
    if(isnull(params))
		return SendSyntaxMessage(playerid, "/a [admin chat]");
    
    SendAdminMessage(X11_GREEN, "%s(%d) %s: {FFFFFF}%s", GetAdminRankName(playerid), GetPlayerAdminLevel(playerid), PlayerData[playerid][pUCP], params);
    return 1;
}

YCMD:setadmin(playerid, params[], help)
{
    new userid, level;
    if(UcpData[playerid][ucpAdmin] < 6)
        return PlayerPermissionError(playerid);

    if(sscanf(params, "ud", userid, level))
        return SendSyntaxMessage(playerid, "/setadmin [playerid/name]  [admin level]");

    if(userid == INVALID_PLAYER_ID)
        return SendErrorMessage(playerid, "You entered invalid player");

    if(level < 1 || level > 5)
        return SendErrorMessage(playerid, "Admin level limit is only 1-5");

    SetPlayerAdmin(userid, level);
    SendAdminMessage(X11_TOMATO_1, "AdmCmd: "WHITE"%s have been set to admin level %d. Congrats.", ReturnName(userid), level);
    return 1;
}
