#include <a_samp>
#include <ZCMD>
#include <sscanf2>
#include <streamer>

#include <YSI_Data\y_foreach>

// Defines
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_LIGHTBLUE 0x33CCFFFF
#define COLOR_GREY 0xAFAFAFFF

// Clearing variables
public OnPlayerConnect(playerid)
{
    DeletePVar(playerid, "BoomboxObject"); DeletePVar(playerid, "BoomboxURL");
    DeletePVar(playerid, "bposX"); DeletePVar(playerid, "bposY"); DeletePVar(playerid, "bposZ"); DeletePVar(playerid, "bboxareaid");
    if(IsValidDynamicObject(GetPVarInt(playerid, "BoomboxObject"))) DestroyDynamicObject(GetPVarInt(playerid, "BoomboxObject"));
    return 1;
}

// Clearing variables & Stopping boombox music on disconnect (Double check)
public OnPlayerDisconnect(playerid)
{
	if(GetPVarType(playerid, "BoomboxObject"))
	{
		DestroyDynamicObject(GetPVarInt(playerid, "BoomboxObject"));
		if(GetPVarType(playerid, "bboxareaid"))
		{
   			foreach(Player,i)
		    {
		    	if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid")))
		        {
		        	StopAudioStreamForPlayer(i);
		             SendClientMessage(i, COLOR_GREY, " The boombox creator has disconnected from the server.");
				}
			}
		}
	}
	return 1;
}


// Boombox command - Usage: /boombox [URL]
CMD:admboombox(playerid, params[])
{
	new string[128];
	if(!GetPVarType(playerid, "BoomboxObject"))
	{
	    if(sscanf(params, "s[256]", params)) return SendClientMessage(playerid, COLOR_WHITE, "USAGE: /boombox [music url]");
		foreach(Player, i)
	    {
	        if(GetPVarType(i, "BoomboxObject"))
	        {
    			if(IsPlayerInRangeOfPoint(playerid, 30.0, GetPVarFloat(i, "bposX"), GetPVarFloat(i, "bposY"), GetPVarFloat(i, "bposZ")))
				{
				    SendClientMessage(playerid, COLOR_GREY, " There is another boombox nearby, place yours somewhere else.");
				    return 1;
				}
			}
		}
		
		new Float:x, Float:y, Float:z, Float:a;
	    GetPlayerPos(playerid, x, y, z); GetPlayerFacingAngle(playerid, a);
	    SetPVarInt(playerid, "BoomboxObject", CreateDynamicObject(2103, x, y, z, 0.0, 0.0, 0.0, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid)));
	    SetPVarFloat(playerid, "bposX", x); SetPVarFloat(playerid, "bposY", y); SetPVarFloat(playerid, "bposZ", z);
		SetPVarInt(playerid, "bboxareaid", CreateDynamicSphere(x, y, z, 300.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)));
	    format(string, sizeof(string), " You have placed your boombox at your location.");
	    SendClientMessage(playerid, COLOR_LIGHTBLUE, string);
	    foreach(Player, i)
		{
			if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid")))
			{
				PlayAudioStreamForPlayer(i, params, GetPVarFloat(playerid, "bposX"), GetPVarFloat(playerid, "bposY"), GetPVarFloat(playerid, "bposZ"), 30.0, 1);
			}
    	}
		SetPVarString(playerid, "BoomboxURL", params);
	}
	else
	{
	    DestroyDynamicObject(GetPVarInt(playerid, "BoomboxObject"));
	    DeletePVar(playerid, "BoomboxObject"); DeletePVar(playerid, "BoomboxURL");
	    DeletePVar(playerid, "bposX"); DeletePVar(playerid, "bposY"); DeletePVar(playerid, "bposZ");
	    if(GetPVarType(playerid, "bboxareaid"))
	    {
	        foreach(Player,i)
	        {
	            if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid")))
	            {
	                StopAudioStreamForPlayer(i);
	                SendClientMessage(i, COLOR_GREY, " The boombox creator has removed his boombox.");
				}
			}
	        DeletePVar(playerid, "bboxareaid");
		}
		SendClientMessage(playerid, COLOR_LIGHTBLUE, " You have removed your boombox.");
	}
	return 1;
}

// Boombox editing - Usage: /boomboxnext [url]
CMD:boomboxnext(playerid, params[])
{
	if(!Boombox[playerid]) return SendClientMessage(playerid, COLOR_GREY, "You don't have a boombox placed.");
    if(sscanf(params, "s[256]", params)) return SendClientMessage(playerid, COLOR_WHITE, "USAGE: /boomboxnext [music url]");
    SendClientMessage(playerid, COLOR_GREY, " You have changed the music your boombox is playing.");
    foreach(Player, i)
	{
		if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "bboxareaid")))
		{
			PlayAudioStreamForPlayer(i, params, GetPVarFloat(playerid, "bposX"), GetPVarFloat(playerid, "bposY"), GetPVarFloat(playerid, "bposZ"), 30.0, 1);
		}
    }
	SetPVarString(playerid, "BoomboxURL", params);
	return 1;
}

// Playing/Stopping boombox music for nearby players / Updated from Onplayerupdate
public OnPlayerEnterDynamicArea(playerid, areaid)
{
	foreach(Player, i)
	{
	    if(GetPVarType(i, "bboxareaid"))
	    {
	        new station[256];
	        GetPVarString(i, "BoomboxURL", station, sizeof(station));
	        if(areaid == GetPVarInt(i, "bboxareaid"))
	        {
	            PlayAudioStreamForPlayer(playerid, station, GetPVarFloat(i, "bposX"), GetPVarFloat(i, "bposY"), GetPVarFloat(i, "bposZ"), 30.0, 1);
				SendClientMessage(playerid, COLOR_GREY, " You are listening to music coming out of a nearby boombox.");
				return 1;
	        }
	    }
	}
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
    foreach(Player, i)
	{
	    if(GetPVarType(i, "bboxareaid"))
	    {
	        if(areaid == GetPVarInt(i, "bboxareaid"))
	        {
	            StopAudioStreamForPlayer(playerid);
	            SendClientMessage(playerid, COLOR_GREY, " You have went far away from the boombox.");
				return 1;
	        }
	    }
	}
	return 1;
}