forward SetPlayerNameEx(playerid, const __string__[]);
forward OnGetName(playerid);
forward SetToCamera(playerid, objectid);
forward OnLoadTickets(playerid);
forward OnOffMembers(playerid);
forward enter_unblock(playerid);
forward OnDgraf(playerid, i);
forward OnGetPlayerByMaskId(playerid, maskid);
forward OnCreatePhone(playerid, phonenumber);
forward show_login(playerid);
forward ActorVWFix(playerid);
forward ActorVWFixContinue(playerid);
forward ActorVWFixContinueEx(playerid);
forward gmx_timer();
forward OnGenerateCarNumber(v, vnumber[]);
forward StopUsingAnim(playerid);
forward knockout(playerid, time);
forward set_wound_free(playerid);
forward set_wound(playerid, mycount);
forward invwep_fix(playerid);
forward Spawn(playerid);
forward BannedTest(playerid);
forward OnLoadAttachments(playerid);
forward OnLoadPrison(playerid);
forward MyHttpResponse(index, response_code, data[]);
forward character_check(playerid, userid);
forward character_set(playerid, ch_id);
forward character_setEx(playerid);
forward AlarmDisactivate(v);
forward characters_checkEx(playerid, userid);
forward GunReTest(playerid);
forward SecondTimerServer();
forward VehTimer(v);
forward TimerKickEx(playerid);
forward KickEx(playerid);
forward player_check(playerid);
forward auth(playerid);
forward onloadenters();
forward load_furniture();
forward load_property(bool:furniture_load);
forward PointToPoint(Float:radi, Float:oldposx, Float:oldposy, Float:oldposz, Float:x, Float:y, Float:z);
forward PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z);
forward save_player(playerid, bool:relog);
forward Freeze(playerid, time);
forward Unfreeze(playerid);
forward killmsg_unblock(playerid);
forward OnLoadContacts(playerid, phonenumber);
forward OnSmsHistory(playerid, phonenumber);
forward OnCarsInfoByPlayerid(playerid);
forward OnCarsInfo(playerid);
forward OnPropInfo(playerid);
forward timeout_door_null(playerid);
forward BuySkinMenu(playerid);
forward ChatOff(playerid);
forward OnPreload(playerid);
forward SetPlayerPosAntiCheatEx(playerid, Float:x, Float:y, Float:z, virtualworld, interiorid);
forward SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, virtualworld, interiorid);
forward OnPlayerDisconnectEx(playerid, reason);
forward AuthTimeout(playerid);
forward OnLoadFactions();
forward OnLoadDoors();
forward AchatOld(playerid, code);
forward OnCheatDetected(playerid, ip_address[], ttype, code);
forward OnLoadCars(playerid);
forward OnLoadGraff();
forward OnAPBList(playerid, page);
forward OnAPBShow(playerid, apb_number);
forward OnAPBDelete(playerid, apb_number);
forward OnLoadCCTV();
forward OnLoadATM();
forward OnLoadArecords(playerid);
forward OnLoadServerint();
forward OnLoadElevators();
forward OnLoadRadioStations();
forward SearchCharacterMDC(playerid);
forward ChangeUCPLogin(playerid,newlogin);
forward OnCreatePager(playerid, phonenumber);
forward OnLoadPager(playerid, phonenumber);
forward CDeath(playerid);

new ArrayList:myList3;
new WObj = 0;

public CDeath(playerid)
{
	if(GetPVarInt(playerid,"Ranen_") != -1)
	{
		KillTimer(GetPVarInt(playerid,"Ranen_"));
		SetPVarInt(playerid,"Ranen_",-1);
	
	}
	if(GetPVarInt(playerid,"ChangeState_Time") != -1)
	{
		KillTimer(GetPVarInt(playerid,"ChangeState_Time"));
		SetPVarInt(playerid,"ChangeState_Time",-1);
	
	}
	
	
	KillTimer(GetPVarInt(playerid,"cmytimer"));
	MyTimerEnd(playerid);
	
	
	set_wound(playerid, 0);
	StopUsingAnim(playerid);
	SetPVarInt(playerid,"cdeath",-1);
}

forward Ranen(playerid);
public Ranen(playerid)
{
	if(character_info[playerid][wound] == 2)
	{
		new Keys, UpDown, LeftRight;
		GetPlayerKeys(playerid, Keys, UpDown, LeftRight);
		if((UpDown != 0) || ((LeftRight != 0) && (!UpDown)))
		{
			UseAnim(playerid,"PED","WALK_fatold",4.0,0,1,1,0,0);
		}
	}
}

#define floatrandom(%0) (float(random(%0))+float(random(1000))/1000)
forward ChangeState(playerid);
public ChangeState(playerid)
{

	if(character_info[playerid][wound] == 2 || character_info[playerid][wound] == 4)
	{
		new Float:pos[3];
		GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
	
		
	
		ArrayList::Add (myList3, CreateObject(19836,pos[0]+floatrandom(1)-0.5,pos[1]+floatrandom(1)-0.5,pos[2]-0.95,0.0,0.0,0.0,50.0));
		
		WObj++;
	}
	
}