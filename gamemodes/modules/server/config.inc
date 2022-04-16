#include <YSI_Coding\y_hooks>

/** Database Configuration */
#define MYSQL_HOSTNAME "127.0.0.1"
#define MYSQL_USERNAME "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "asuy"

hook OnGameModeInitEx()
{
    DisableInteriorEnterExits();
	ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(0);
    SetNameTagDrawDistance(15.0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_OFF);
    return 1;
}