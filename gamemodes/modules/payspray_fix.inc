#include <YSI\y_hooks>

Hook:paynspray_OnPlayerUpdate(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new Float:vHealth;
		GetVehicleHealth(GetPlayerVehicleID(playerid), vHealth);
		if(vHealth == 1000)
		{
			SetVehicleHealth(GetPlayerVehicleID(playerid), 999);
			
	        new const Float:paynspray[][] = {
	        {1025.05, -1024.23, 32.1}, // LS Temple
	        {487.68, -1740.87, 11.13}, // LS Santa Maria
			{-1420.73, 2583.37, 55.56}, // El Quebrados
			{-1904.39, 284.97, 40.75}, // Wang Cars
			{-2425.91, 1022.33, 50.10}, // Juniper Hill
			{1975.60, 2162.16, 10.77}, // LV Redsands
			{2065.38, -1831.51, 13.25}, // Idlewood
			{-99.55, 1118.36, 19.44}, // Fort Carson
			{721.07, -455.94, 16.04}, // Dillimore
			{2393.74, 1493.01, 10.52} // LV Unused (Pyramid)
	        };
	        for(new i=0; i<sizeof(paynspray); i++)
	        {
	            if(IsPlayerInRangeOfPoint(playerid, 10, paynspray[i][0], paynspray[i][1], paynspray[i][2]))
				{ 
					CallRemoteFunction("OnVehicleRespray", "iiii", playerid, GetPlayerVehicleID(playerid), -1, -1);
					return 1;
				}
			}
		}
	}
	return 1;
}

stock paynspray_CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, copsiren)
{
	new vid = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, copsiren);	
	SetVehicleHealth(vid, 999);
	return vid;
}

#if defined _ALS_CreateVehicle
	#undef CreateVehicle
#else
	#define _ALS_CreateVehicle
#endif
#define CreateVehicle paynspray_CreateVehicle

stock paynspray_AddStaticVehicleEx(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay)
{
	new vid = AddStaticVehicleEx(vehicletype, x, y, z, rotation, color1, color2, respawn_delay);
	SetVehicleHealth(vid, 999);
	return vid;
}

#if defined _ALS_AddStaticVehicleEx
	#undef AddStaticVehicleEx
#else
	#define _ALS_AddStaticVehicleEx
#endif
#define AddStaticVehicleEx paynspray_AddStaticVehicleEx

stock paynspray_AddStaticVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2)
{
	new vid = AddStaticVehicle(vehicletype, x, y, z, rotation, color1, color2);
	SetVehicleHealth(vid, 999);
	return vid;
}

#if defined _ALS_AddStaticVehicle
	#undef AddStaticVehicle
#else
	#define _ALS_AddStaticVehicle
#endif
#define AddStaticVehicle paynspray_AddStaticVehicle