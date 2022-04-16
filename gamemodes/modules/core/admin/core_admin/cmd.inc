YCMD:a(playerid, params[], help)
{
    if(UcpData[playerid][ucpAdmin] < 1)
        return PlayerPermissionError(playerid);
    
    if(isnull(params))
		return SendSyntaxMessage(playerid, "/a [admin chat]");
    
    SendAdminMessage(X11_GREEN, "%s(%d) %s: {FFFFFF}%s", GetAdminRankName(playerid), GetPlayerAdminLevel(playerid), ReturnName(playerid), params);
    return 1;
}