#define function%0(%1)          forward%0(%1); public%0(%1)
#define MAX_CHARS 3

#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 60
#endif 

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif

/** Colors */
#define 	X11_COLOR_PURPLE 		0xC2A2DAAA

#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, X11_LIGHT_SKY_BLUE_1, "SERVER:{FFFFFF} "%1)

#define SendSyntaxMessage(%0,%1) \
	SendClientMessageEx(%0, X11_GREY, "USAGE:{FFFFFF} "%1)

#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, X11_GREY, "ERROR: "%1)

#define SendCustomMessage(%0,%1,%2,%3) \
    SendClientMessageEx(%0, %1, %2": "%3)

#define PlayerPermissionError(%0) \
	SendErrorMessage(%0, "You don't have permission or authority to use this commands!")