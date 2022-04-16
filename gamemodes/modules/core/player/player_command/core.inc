new const g_CommandType[][] = {
    "Chat Commands",
    "Action Commands"
};

enum _:E_HELP_TYPES
{
    HELP_TYPE_CHAT = 0,
    HELP_TYPE_ACTION
};

enum E_HELP
{
    E_HELP_TYPE,
    E_HELP_CMD[16],
    E_HELP_DESCRIPTION[64]
};

new const g_HelpComands[][E_HELP] = {
    {HELP_TYPE_ACTION, "/me", "Me action"},
    {HELP_TYPE_ACTION, "/do", "Do action"},
    {HELP_TYPE_ACTION, "/ado", "Ado action"},
    {HELP_TYPE_ACTION, "/ame", "Ame action"},
    {HELP_TYPE_CHAT, "/b", "Out of characters Chat"},
    {HELP_TYPE_CHAT, "/l", "Low your characters Chat"}
};