YCMD:help(playerid, params[], help)
{
    new str[128];
    for(new i = 0; i < sizeof(g_CommandType); i++)
    {
        format(str, sizeof(str), "%s%s\n", str, g_CommandType[i]);
    }
    Dialog_Show(playerid, DIALOG_HELP, DIALOG_STYLE_LIST, "Help Menu", str, "Select", "Exit");
    return 1;
}

YCMD:melow(playerid, params[], help)
{
	if (isnull(params)) 
		return SendSyntaxMessage(playerid, "/melow [action]");

	SendMe(playerid, params, 6.0);
	return 1; 
}

YCMD:me(playerid, params[], help)
{
	if (isnull(params)) 
		return SendSyntaxMessage(playerid, "/me [action]");

	SendMe(playerid, params, 20.0);
	return 1; 
}

YCMD:do(playerid, params[], help)
{
	if (isnull(params)) 
		return SendSyntaxMessage(playerid, "/do [action]");

    SendAdo(playerid, params, 20.0);
	return 1; 
}

YCMD:dolow(playerid, params[], help)
{
	if (isnull(params)) 
		return SendSyntaxMessage(playerid, "/dolow [action]");

	SendAdo(playerid, params, 6.0);
	return 1; 
}

YCMD:ame(playerid, params[], help)
{
	new
	    string[128];
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/ame [action]");
	format(string, sizeof(string), "* %s",  params);
 	SetPlayerChatBubble(playerid, string, X11_COLOR_PURPLE, 30.0, 5000);
 	SendClientMessageEx(playerid, X11_WHITE, "* [AME]: {D0AEEB}%s", params);
	return 1;
}

YCMD:ado(playerid, params[], help)
{
	if (isnull(params))
		return SendSyntaxMessage(playerid, "/ado [action]");

	new str[128], time = strlen(params)*100;
	if(time < 10000)
	{
		time = 10000;
	}
	format (str, sizeof(str), "* %s (( %s ))", params, ReturnName(playerid));
	SetPlayerChatBubble(playerid, str, X11_COLOR_PURPLE, 20.0, time);
	
	SendClientMessageEx(playerid, X11_COLOR_PURPLE, "> %s (( %s ))", params, ReturnName(playerid));
	return 1;
}

YCMD:b(playerid, params[], help)
{
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/b [local ooc]");
	    
	SendNearbyMessage(playerid, 15.0, X11_GREY, "(( [OOC] %s: %s ))", playerid, GetName(playerid), params);
	return 1;
}

YCMD:l(playerid, params[], help)
{
	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/(l)ow [low text]");

	if (strlen(params) > 64)
	{
	    params[0] = toupper(params[0]);
	    SendNearbyMessage(playerid, 5.0, X11_WHITE, "[low] %s says: %.64s", ReturnName(playerid), params);
	    SendNearbyMessage(playerid, 5.0, X11_WHITE, "...%s", params[64]);
	}
	else
	{
 		params[0] = toupper(params[0]);
	    SendNearbyMessage(playerid, 5.0, X11_WHITE, "[low] %s says: %s", ReturnName(playerid), params);
	}
	return 1;
}

YCMD:low(playerid, params[], help) = l;
