stock CheckAccount(playerid)
{
	new query[256];
	format(query, sizeof(query), "SELECT * FROM `PlayerUCP` WHERE `UCP` = '%s' LIMIT 1;", GetName(playerid));
	mysql_tquery(MySQL_Handle, query, "CheckPlayerUCP", "d", playerid);
	return 1;
}

stock SetupPlayerData(playerid)
{
    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], 1642.1681, -2333.3689, 13.5469, 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

stock MySQL_SaveDataPlayer(playerid)
{
	new query[1012];
	if(IsPlayerSpawned(playerid))
	{
		GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		mysql_format(MySQL_Handle, query, sizeof(query), "UPDATE `characters` SET ");
		mysql_format(MySQL_Handle, query, sizeof(query), "%s`PosX`='%.4f', ", query, PlayerData[playerid][pPos][0]);
        mysql_format(MySQL_Handle, query, sizeof(query), "%s`PosY`='%.4f', ", query, PlayerData[playerid][pPos][1]);
        mysql_format(MySQL_Handle, query, sizeof(query), "%s`PosZ`='%.4f', ", query, PlayerData[playerid][pPos][2]);
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`Health`='%.4f', ", query, PlayerData[playerid][pHealth]);
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`World`='%d', ", query, GetPlayerVirtualWorld(playerid));
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`Interior`='%d', ", query, GetPlayerInterior(playerid));
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`Age`='%d', ", query, PlayerData[playerid][pAge]);
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`Origin`='%s', ", query, PlayerData[playerid][pOrigin]);
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`Gender`='%d', ", query, PlayerData[playerid][pGender]);
	    mysql_format(MySQL_Handle, query, sizeof(query), "%s`Skin`='%d', ", query, PlayerData[playerid][pSkin]);
		mysql_format(MySQL_Handle, query, sizeof(query), "%s`UCP`='%s' ", query, PlayerData[playerid][pUCP]);
		mysql_format(MySQL_Handle, query, sizeof(query), "%sWHERE `pID` = %d", query, PlayerData[playerid][pID]);
		mysql_query(MySQL_Handle, query, true);
	}
	return 1;
}

function MySQL_LoadCharacterData(playerid)
{
	cache_get_value_name_int(0, "pID", PlayerData[playerid][pID]);
	cache_get_value_name(0, "Name", PlayerData[playerid][pName]);
	cache_get_value_name_float(0, "PosX", PlayerData[playerid][pPos][0]);
	cache_get_value_name_float(0, "PosY", PlayerData[playerid][pPos][1]);
	cache_get_value_name_float(0, "PosZ", PlayerData[playerid][pPos][2]);
	cache_get_value_name_float(0, "Health", PlayerData[playerid][pHealth]);
	cache_get_value_name_int(0, "Interior", PlayerData[playerid][pInterior]);
	cache_get_value_name_int(0, "World", PlayerData[playerid][pWorld]);
	cache_get_value_name_int(0, "Age", PlayerData[playerid][pAge]);
	cache_get_value_name(0, "Origin", PlayerData[playerid][pOrigin]);
	cache_get_value_name_int(0, "Gender", PlayerData[playerid][pGender]);
	cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
	cache_get_value_name(0, "UCP", PlayerData[playerid][pUCP]);
	
	SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
	CallLocalFunction(#OnDataPlayerLoaded, "d", playerid);
    return 1;
}

stock MySQL_LoadUcpData(playerid)
{
	cache_get_value_name_int(0, "ID", UcpData[playerid][ucpID]);
	cache_get_value_name_int(0, "AdminLevel", UcpData[playerid][ucpAdmin]);
	return 1;
}

function HashPlayerPassword(playerid, hashid)
{
	new
		query[256],
		hash[BCRYPT_HASH_LENGTH];

    bcrypt_get_hash(hash, sizeof(hash));
	GetPlayerName(playerid, tempUCP[playerid], MAX_PLAYER_NAME + 1);
	format(query,sizeof(query),"INSERT INTO `PlayerUCP` (`UCP`, `Password`) VALUES ('%s', '%s')", tempUCP[playerid], hash);
	mysql_tquery(MySQL_Handle, query);
	UcpData[playerid][ucpID] = cache_insert_id();

    SendServerMessage(playerid, "Your UCP is successfully registered!");
    CheckAccount(playerid);
	return 1;
}

function OnPlayerPasswordChecked(playerid, bool:success)
{
	new str[256];
    format(str, sizeof(str), "Welcome Back to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to logged in:", GetName(playerid));
    
	if(!success)
        return Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", str, "Login", "Exit");
		
	new query[256], query2[256];
	format(query, sizeof(query), "SELECT `Name` FROM `characters` WHERE `UCP` = '%s' LIMIT %d;", GetName(playerid), MAX_CHARS);
	format(query2, sizeof(query2), "SELECT * FROM `playerucp` WHERE `UCP` = '%s'", GetName(playerid));
	mysql_tquery(MySQL_Handle, query, "LoadCharacter", "d", playerid);
	mysql_tquery(MySQL_Handle, query2, "LoadUCPData", "d", playerid);
	return 1;
}

stock ShowCharacterList(playerid)
{
	new name[256], count, sgstr[128];
	for (new i; i < MAX_CHARS; i ++) if(PlayerChar[playerid][i][0] != EOS)
	{
	    format(sgstr, sizeof(sgstr), "%s\n", PlayerChar[playerid][i]);
		strcat(name, sgstr);
		count++;
	}
	if(count < MAX_CHARS)
		strcat(name, "< Create Character >");
	Dialog_Show(playerid, DIALOG_CHARLIST, DIALOG_STYLE_LIST, "Character List", name, "Select", "Quit");
	return 1;
}

function LoadCharacter(playerid)
{
	for (new i = 0; i < MAX_CHARS; i ++)
	{
		PlayerChar[playerid][i][0] = EOS;
	}
	for (new i = 0; i < cache_num_rows(); i ++)
	{
		cache_get_value_name(i, "Name", PlayerChar[playerid][i]);
	}
  	ShowCharacterList(playerid);
  	return 1;
}

function PlayerCheck(playerid, rcc)
{
    if(rcc != g_RaceCheck{playerid})
	    return Kick(playerid);
	    
	CheckAccount(playerid);
	return true;
}

function CheckPlayerUCP(playerid)
{
    new rows = cache_num_rows();
	new str[256];
	if (rows)
	{
	    cache_get_value_name(0, "UCP", tempUCP[playerid]);
		cache_get_value_name_int(0, "ID", UcpData[playerid][ucpID]);
		cache_get_value_name_int(0, "AdminLevel", UcpData[playerid][ucpAdmin]);

	    format(str, sizeof(str), "Welcome Back to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to logged in:", GetName(playerid));
		Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", str, "Login", "Exit");
	}
	else
	{
	    format(str, sizeof(str), "Welcome to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to register:", GetName(playerid));
		Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "UCP - Register", str, "Register", "Exit");
	}
	return 1;
}

function InsertPlayerName(playerid, name[])
{
	new count = cache_num_rows(), query[145], Cache:execute;
	if(count > 0)
	{
        Dialog_Show(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "ERROR: This name is already used by the other player!\nInsert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Back");
	}
	else
	{
		mysql_format(MySQL_Handle,query,sizeof(query),"INSERT INTO `characters` (`Name`,`UCP`) VALUES('%e','%e')",name,GetName(playerid));
		execute = mysql_query(MySQL_Handle, query);
		PlayerData[playerid][pID] = cache_insert_id();
	 	cache_delete(execute);
	 	SetPlayerName(playerid, name);
		format(PlayerData[playerid][pName], MAX_PLAYER_NAME, name);
	 	Dialog_Show(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "Please Insert your Character Age", "Continue", "Cancel");
	}
	return 1;
}

stock ShowPlayerRegion(playerid)
{
	new gstr[412];
	strcat(gstr, "Select the region!\n");
	strcat(gstr, "America\n");
    strcat(gstr, "Mexico\n");
    strcat(gstr, "Canada\n");
    strcat(gstr, "Jerman\n");

	Dialog_Show(playerid, DIALOG_ORIGIN, DIALOG_STYLE_TABLIST_HEADERS, "Region List", gstr, "Select", "Close");
	return 1;
}

stock GetOriginNameFromID(lisitem, result[], maxlength = sizeof result)
{
	new name[16] = "";
	switch (lisitem)
	{
		case 0: name = "America";
		case 1: name = "Mexico";
		case 2: name = "Canada";
		case 3: name = "Jerman";
	}

	strcopy(result, name, maxlength);
}