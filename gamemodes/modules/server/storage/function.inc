stock MySQL_INIT()
{
    new MySQLOpt: option_id = mysql_init_options();

	mysql_set_option(option_id, AUTO_RECONNECT, true); 

	MySQL_Handle = mysql_connect(MYSQL_HOSTNAME, MYSQL_USERNAME, MYSQL_PASSWORD, MYSQL_DATABASE, option_id);
	if (MySQL_Handle == MYSQL_INVALID_HANDLE)
	{
		printf("[ERROR] Fatal Error! There was an invalid Handle.");
		printf("[ERROR] Error number: %d", mysql_errno(MySQL_Handle));
		SendRconCommand("exit");
		return 0;
	}

	if (mysql_errno(MySQL_Handle) != 0)
	{
		new str[128];
		mysql_error(str, sizeof(str));
		printf("[ERROR] Fatal Error! Could not connect to MySQL: Host %s - DB: %s - User: %s", MYSQL_HOSTNAME, MYSQL_DATABASE, MYSQL_USERNAME);
		print("[ERROR] Note: Make sure that you have provided the correct connection credentials.");
		printf("[ERROR] Error number: %d", mysql_errno(MySQL_Handle));
		SendRconCommand("exit");
		return 0;
	} else {
        CallLocalFunction(#OnDatabaseConnected, "");
    }
    return 1;
}