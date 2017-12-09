/*	=============================

	Limex's Swimming Include
	
	Made by Limex / A
	
	New function:
	IsPlayerSwimming(playerid)
	
	New callbacks:
	OnPlayerStartSwimming(playerid)
	OnPlayerStopSwimming(playerid)
	
	Enjoy!

	============================= */

#include <a_samp>

new bool:swimming[MAX_PLAYERS];

forward OnPlayerStartSwimming(playerid);
forward OnPlayerStopSwimming(playerid);
forward IsPlayerSwimming(playerid);

public IsPlayerSwimming(playerid)
{
	if(swimming[playerid]) return 1;
	return 0;
}