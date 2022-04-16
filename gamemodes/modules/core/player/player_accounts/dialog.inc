Dialog:DIALOG_REGISTER(playerid, response, listitem, inputtext[])
{
    new str[256];

    if(!response)
        return Kick(playerid);

    format(str, sizeof(str), "Welcome to Roleplay Server!\n\nYour UCP: %s\nERROR: Password length cannot below 7 or above 32!\nPlease insert your Password below to register:", GetName(playerid));
    if(strlen(inputtext) < 7)
        return Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "UCP - Register", str, "Register", "Exit");

    if(strlen(inputtext) > 32)
        return Dialog_Show(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "UCP - Register", str, "Register", "Exit");
          
    bcrypt_hash(playerid, "HashPlayerPassword", inputtext, BCRYPT_COST);
    return 1;
}

Dialog:DIALOG_LOGIN(playerid, response, listitem, inputtext[])
{
    new pwQuery[256], hash[BCRYPT_HASH_LENGTH];
    if(!response)
	    return Kick(playerid);
	        
    if(strlen(inputtext) < 1)
    {
		new str[256];
        format(str, sizeof(str), "Welcome Back to Roleplay Server!\n\nYour UCP: %s\nPlease insert your Password below to logged in:", GetName(playerid));
        Dialog_Show(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "UCP - Login", str, "Login", "Exit");
        return 1;
	}

	mysql_format(MySQL_Handle, pwQuery, sizeof(pwQuery), "SELECT Password FROM PlayerUCP WHERE UCP = '%e' LIMIT 1", GetName(playerid));
	mysql_query(MySQL_Handle, pwQuery);
		
    cache_get_value_name(0, "Password", hash, sizeof(hash));
        
    bcrypt_verify(playerid, "OnPlayerPasswordChecked", inputtext, hash);
    return 1;
}

Dialog:DIALOG_CHARLIST(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		if (PlayerChar[playerid][listitem][0] == EOS)
			return Dialog_Show(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Insert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Exit");

		PlayerData[playerid][pChar] = listitem;
		SetPlayerName(playerid, PlayerChar[playerid][listitem]);
		new cQuery[256];
		mysql_format(MySQL_Handle, cQuery, sizeof(cQuery), "SELECT * FROM `characters` WHERE `Name` = '%s' LIMIT 1;", PlayerChar[playerid][PlayerData[playerid][pChar]]);
		mysql_tquery(MySQL_Handle, cQuery, "MySQL_LoadCharacterData", "d", playerid);	
	}
    return 1;
}

Dialog:DIALOG_MAKECHAR(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
			return Dialog_Show(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Insert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Back");

		if(!IsRoleplayName(inputtext))
			return Dialog_Show(playerid, DIALOG_MAKECHAR, DIALOG_STYLE_INPUT, "Create Character", "Insert your new Character Name\n\nExample: Finn_Xanderz, Javier_Cooper etc.", "Create", "Back");

		new characterQuery[178];
		mysql_format(MySQL_Handle, characterQuery, sizeof(characterQuery), "SELECT * FROM `characters` WHERE `Name` = '%s'", inputtext);
		mysql_tquery(MySQL_Handle, characterQuery, "InsertPlayerName", "ds", playerid, inputtext);
		format(PlayerData[playerid][pUCP], 22, GetName(playerid));
	}
    return 1;
}

Dialog:DIALOG_AGE(playerid, response, listitem, inputtext[])
{
    if(response)
	{
		if(strval(inputtext) >= 70)
			return Dialog_Show(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "ERROR: Cannot more than 70 years old!", "Continue", "Cancel");

		if(strval(inputtext) < 13)
			return Dialog_Show(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "ERROR: Cannot below 13 Years Old!", "Continue", "Cancel");

		PlayerData[playerid][pAge] = strval(inputtext);
		ShowPlayerRegion(playerid);
	}
	else
	{
		Dialog_Show(playerid, DIALOG_AGE, DIALOG_STYLE_INPUT, "Character Age", "Please Insert your Character Age", "Continue", "Cancel");
	}
    return 1;
}

Dialog:DIALOG_ORIGIN(playerid, response, listitem, inputtext[])
{
    if(!response)
	    return ShowPlayerRegion(playerid);

	new originName[16];
	GetOriginNameFromID(listitem, originName);
    format(PlayerData[playerid][pOrigin], 32, originName);
    Dialog_Show(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Character Gender", "Male\nFemale", "Continue", "Cancel");
    return 1;
}

Dialog:DIALOG_GENDER(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return Dialog_Show(playerid, DIALOG_GENDER, DIALOG_STYLE_LIST, "Character Gender", "Male\nFemale", "Continue", "Cancel");

	if(listitem == 0)
	{
        new rand = random(sizeof(g_aMaleSkins));
		PlayerData[playerid][pGender] = 1;
		PlayerData[playerid][pSkin] = g_aMaleSkins[rand];
		PlayerData[playerid][pHealth] = 100.0;
		SetupPlayerData(playerid);
	}
    else if(listitem == 1)
	{
        new rand = random(sizeof(g_aFemaleSkins));
		PlayerData[playerid][pGender] = 2;
		PlayerData[playerid][pSkin] = g_aFemaleSkins[rand];
		PlayerData[playerid][pHealth] = 100.0;
		SetupPlayerData(playerid);
	}
    return 1;
}