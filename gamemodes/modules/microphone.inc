enum microphone_struct
{
	status,
	item1,
	item2,
	Text3D:item3,
	Float:posX,
	Float:posY,
	Float:posZ
}

new microphone[100][microphone_struct];

CMD:createmic(playerid)
{
	if(IsAdmin(playerid, 6)) 
		return 1;
	
	new Float:x, Float:y, Float:z, Float:ploca;
    GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid,ploca);
	
	x += 1*floatsin(-ploca, degrees);
	y += 1*floatcos(-ploca, degrees);
			
	new value = FindEmptyMic();
	
	microphone[value][item1] = CreateDynamicObject(19611, x, y, z-0.98, 0.0, 0.0, ploca+180, GetPlayerVirtualWorld(playerid));
	microphone[value][item2] = CreateDynamicObject(19610, x, y-0.012, z-0.98+1.56, 28.0, 113.819, ploca+180, GetPlayerVirtualWorld(playerid));
	
	new str[32];
	format(str, sizeof(str), "[%d]", value);
	microphone[value][item3] = Create3DTextLabel(str, 0x00FFFFFF, x, y, z, 1.0, 0, GetPlayerVirtualWorld(playerid));
	
	microphone[value][posX] = x;
	microphone[value][posY] = y;
	microphone[value][posZ] = z;
	microphone[value][status] = 1;
	return 1;
}

CMD:mic(playerid, params[])
{
	if(isnull(params))
		return SyntaxCMD(playerid, "/mic [text]");
	
	if(IsMicRadius(playerid))
	{	
		new str[128];
		
		if (strlen(params) > 64)
		{
			format(str, sizeof(str), "%s говорит в микрофон: %.64s", sendername(playerid, true), params[0]);
			ProxDetector(40.0, GetPlayerVirtualWorld( playerid ), playerid, str, str, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
			
			format(str, sizeof(str), "...%s", params[64]);
			ProxDetector(40.0, GetPlayerVirtualWorld( playerid ), playerid, str, str, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
		}
		else
		{
			format(str, sizeof(str), "%s говорит в микрофон: %s", sendername(playerid, true), params[0]);
			ProxDetector(40.0, GetPlayerVirtualWorld( playerid ), playerid, str, str, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
		}
		return 1;
	}
	
	return 1;
}

CMD:delmic(playerid, params[])
{
	if(IsAdmin(playerid, 6))
		return 1;
	new micid;
	if(sscanf(params,"d", micid))
		return 1;
	
	DestroyDynamicObject(microphone[micid][item1]);
	DestroyDynamicObject(microphone[micid][item2]);
	Delete3DTextLabel(microphone[micid][item3]);
	
	microphone[micid][status] = 0;	
	return 1;
}

stock FindEmptyMic()
{
	for(new i; i < sizeof(microphone); i++)
	{
		if(microphone[i][status] == 0)
			return i;
	}
	return 1;
}

stock IsMicRadius(playerid)
{
	for(new i; i<sizeof(microphone); i++)
	{		
		if(IsPlayerInRangeOfPoint(playerid, 2.0, microphone[i][posX] , microphone[i][posY] , microphone[i][posZ]) && microphone[i][status] == 1) 
			return 1;
		
	}
	return 0;
}
