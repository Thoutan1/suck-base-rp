Dialog:DIALOG_HELP(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new str[2012];
        format(str, sizeof(str), "Command\tDescription\n");
        for(new i = 0; i < sizeof(g_HelpComands); i++) if(g_HelpComands[i][E_HELP_TYPE] == listitem)
        {
            format(str, sizeof(str), "%s%s\t%s\n", str, g_HelpComands[i][E_HELP_CMD], g_HelpComands[i][E_HELP_DESCRIPTION]);
        }
        Dialog_Show(playerid, DIALOG_UNUSED, DIALOG_STYLE_TABLIST_HEADERS, "Help Commands", str, "Close", "");
    }
    return 1;
}
