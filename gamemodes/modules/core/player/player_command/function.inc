stock SendMe(playerid, emote[], Float:range = 20.0)
{
	if(strlen(emote) > 86)
	{
		SendNearbyMessage(playerid, range, X11_COLOR_PURPLE, "* %s %.86s", ReturnName(playerid), emote); 
		SendNearbyMessage(playerid, range, X11_COLOR_PURPLE, "* ...%s (( %s ))", emote[86], ReturnName(playerid));
	}
	else SendNearbyMessage(playerid, range, X11_COLOR_PURPLE, "* %s %s", ReturnName(playerid), emote);
}

stock SendAdo(playerid, emote[], Float:range = 20.0) 
{
	if(strlen(emote) > 86)
	{
		SendNearbyMessage(playerid, range, X11_COLOR_PURPLE, "* %.86s ... (( %s ))", emote, ReturnName(playerid)); 
		SendNearbyMessage(playerid, range, X11_COLOR_PURPLE, "* ... %s (( %s ))", emote[86], ReturnName(playerid));
	}
	else SendNearbyMessage(playerid, range, X11_COLOR_PURPLE, "* %s (( %s ))", emote, ReturnName(playerid));
}

stock SendAMe(playerid, emote[])
{
	new str[128], time = strlen(emote)*100;
	if(time < 10000)
	{
		time = 10000;
	}
	format (str, sizeof(str), "* %s %s", ReturnName(playerid), emote);
	SetPlayerChatBubble(playerid, str, X11_COLOR_PURPLE, 20.0, time);
}