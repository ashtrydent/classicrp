enum gate_struct
{
	factionid,
	GateStatus,
	Float:GateSpeed,
	Float:PosStartX,
	Float:PosStartY,
	Float:PosStartZ,
	Float:PosStartRX,
	Float:PosStartRY,
	Float:PosStartRZ,
	Float:PosEndX,
	Float:PosEndY,
	Float:PosEndZ,
	Float:PosEndRX,
	Float:PosEndRY,
	Float:PosEndRZ
}

new GateList[][gate_struct] = {
	{LSFD_FACTION,0,0.5,		2233.487792, -1956.873291, 15.818886, 0.000000, 0.000000, 0.000000, 			2233.487792, -1954.390991, 15.826192, -89.600028, 0.000000, 0.000000},
	{LSFD_FACTION,0,0.5,		2242.491455, -1956.873291, 15.818886, 0.000000, 0.000000, 0.000000,				2242.491943, -1954.390991, 15.826192, -89.600028, 0.000000, 0.000000},
	{LSFD_FACTION,0,0.5,		2251.483886, -1956.873291, 15.818886, 0.000000, 0.000000, 0.000000, 			2251.485839, -1954.390991, 15.826192, -89.600028, 0.000000, 0.000000},
	{LSFD_FACTION,0,0.5,		2260.485839, -1956.873291, 15.818886, 0.000000, 0.000000, 0.000000, 			2260.478027, -1954.390991, 15.826192, -89.600028, 0.000000, 0.000000},
	{LSPD_FACTION,0,0.3,		517.9440000, -1772.185000, 7.6470000, 0.000000, 0.000000, 87.79900,				517.8750000, -1773.986000, 9.1400000, 0.00000000, 90.20000, 87.79900},
	//{LSPD_FACTION,0,0.3,		517.9440000, -1772.185000, 7.6470000, 0.000000, 0.000000, 87.79900,				517.8750000, -1773.986000, 9.1400000, 0.00000000, 90.20000, 87.79900}
	{LSSD_FACTION,0,1.0,		2423.865, 112.691, 26.035, 0.0, 0.0, 90.0,										2423.865, 123.2931, 26.035, 0.0, 0.0, 90.0}
};

new Gate[100];
stock CreateGate()
{
	Gate[0] = CreateDynamicObject(19906, GateList[0][PosStartX], GateList[0][PosStartY], GateList[0][PosStartZ], GateList[0][PosStartRX], GateList[0][PosStartRY], GateList[0][PosStartRZ]);
	SetDynamicObjectMaterial(Gate[0], 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
	
	Gate[1] = CreateDynamicObject(19906, GateList[1][PosStartX], GateList[1][PosStartY], GateList[1][PosStartZ], GateList[1][PosStartRX], GateList[1][PosStartRY], GateList[1][PosStartRZ]);
	SetDynamicObjectMaterial(Gate[1], 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
	
	Gate[2] = CreateDynamicObject(19906, GateList[2][PosStartX], GateList[2][PosStartY], GateList[2][PosStartZ], GateList[2][PosStartRX], GateList[2][PosStartRY], GateList[2][PosStartRZ]);
	SetDynamicObjectMaterial(Gate[2], 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
	
	Gate[3] = CreateDynamicObject(19906, GateList[3][PosStartX], GateList[3][PosStartY], GateList[3][PosStartZ], GateList[3][PosStartRX], GateList[3][PosStartRY], GateList[3][PosStartRZ]);
	SetDynamicObjectMaterial(Gate[3], 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
	
	Gate[4] = CreateDynamicObject(11327, GateList[4][PosStartX], GateList[4][PosStartY], GateList[4][PosStartZ], GateList[4][PosStartRX], GateList[4][PosStartRY], GateList[4][PosStartRZ]);
	
	Gate[5] = CreateDynamicObject(980,2423.865,112.691,26.035,0.000,0.000,90.000,-1,-1,-1,300.000,300.000);
	SetDynamicObjectMaterial(Gate[5], 0, 14634, "blindinglite", "ws_volumetriclight", 0x00000000);
	SetDynamicObjectMaterial(Gate[5], 1, 14634, "blindinglite", "ws_volumetriclight", 0x00000000);
	SetDynamicObjectMaterial(Gate[5], 3, 14634, "blindinglite", "ws_volumetriclight", 0x00000000);
	SetDynamicObjectMaterial(Gate[5], 5, 14634, "blindinglite", "ws_volumetriclight", 0x00000000);
	
}



stock OpenGate(playerid)
{
	for(new i; i<sizeof(GateList); i++)
	{		

		new Float:GateRange;
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid)==PLAYER_STATE_DRIVER)
			GateRange = 7.0;
		else
			GateRange = 3.0;
		
		if(IsPlayerInRangeOfPoint(playerid, GateRange, GateList[i][PosStartX], GateList[i][PosStartY], GateList[i][PosStartZ]) && InFactionId(playerid, GateList[i][factionid]))		
		{
			if(GateList[i][GateStatus])
			{
				MoveDynamicObject(Gate[i], GateList[i][PosStartX], GateList[i][PosStartY], GateList[i][PosStartZ], GateList[i][GateSpeed], GateList[i][PosStartRX], GateList[i][PosStartRY], GateList[i][PosStartRZ]);
				GateList[i][GateStatus] = 0;
			}
			else
			{
				MoveDynamicObject(Gate[i], GateList[i][PosEndX],GateList[i][PosEndY],GateList[i][PosEndZ], GateList[i][GateSpeed], GateList[i][PosEndRX], GateList[i][PosEndRY], GateList[i][PosEndRZ]);
				GateList[i][GateStatus] = 1;
			}
		}
	}
	return 0;
}


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (newkeys & KEY_CROUCH && IsPlayerInAnyVehicle(playerid))
		OpenGate(playerid);
	if (newkeys & KEY_CTRL_BACK && !IsPlayerInAnyVehicle(playerid))
		OpenGate(playerid);
	
	SAMPAC_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
}

#if defined SAMPAC_OnPlayerKeyStateChange
	forward SAMPAC_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif
#if defined _ALS_OnPlayerKeyStateChange
	#undef OnPlayerKeyStateChange
#else
	#define _ALS_OnPlayerKeyStateChange
#endif
#define OnPlayerKeyStateChange SAMPAC_OnPlayerKeyStateChange