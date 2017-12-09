/*

	Anticheat by Johnathan Goodman
	
*/


new ACveh[MAX_PLAYERS];

forward Anticheat();
public Anticheat()
{
	foreach (new userid : Player)
	{
		new weaponid = GetPlayerWeapon(userid);
		
		if(character_info[userid][AFK] == 0 && player_info[userid][loged] == 1 && character_info[userid][spawned] == 1)
		{
			GetPlayerHealth(userid, character_info[userid][Health]);
			//character_info[userid][Interior] = GetPlayerInterior(userid);
			//character_info[userid][VW] = GetPlayerVirtualWorld(userid);
			if(character_info[userid][wound] == 0) {
				GetPlayerPos(userid, character_info[userid][posX], character_info[userid][posY], character_info[userid][posZ]);
			}
			
		}
		if(GetPlayerSpecialAction(userid) == SPECIAL_ACTION_USEJETPACK)
			Kick(userid);
				
		if(weaponid != 0 && !IsDuty(userid) && player_info[userid][admin] < 6)
			if(weaponid != character_info[userid][gun] && weaponid != character_info[userid][duty_gun_1] && weaponid != character_info[userid][duty_gun_2] && weaponid != character_info[userid][duty_gun_3] && weaponid != character_info[userid][duty_gun_special])
				AntiCheat(userid, "попытался начитерить оружие", ANTICHEAT_DGUN);
	}
	
	return 1;
}

forward TrySitCar(playerid,vehicleid,ispassenger);
public TrySitCar(playerid,vehicleid,ispassenger)
{
	ACveh[playerid] = vehicleid;
	return 0;
}


stock isBoat(vehicleid)
{
	if(vehicleid == 430 || vehicleid == 446 || vehicleid == 452 || vehicleid == 453 || vehicleid == 454 || vehicleid == 472 || vehicleid == 473 || vehicleid == 484 || vehicleid == 493 || vehicleid == 595)
		return 1;
	else
		return 0;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	if(isBoat(vehicleid))
		TrySitCar(playerid,vehicleid,0);
	else
		SetTimerEx("TrySitCar", 400, false, "%d%d", playerid, vehicleid);
	
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	return 1;
}