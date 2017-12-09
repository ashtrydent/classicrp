//--------------------------------------------------------------------------
//Данная версия инклуда проверена и оттестирована на версии античита 0.21 beta
//Использование конкретно этого инклуда на более новых версиях не рекомендовано!
//Обновляйте версию постоянно: http://pawno-info.ru/showthread.php?t=267265
//--------------------------------------------------------------------------
//Версия include: 0.21 beta
//--------------------------------------------------------------------------
#define NULL 							"\1\0"

#define AC_UNKNOWN_ID   				0					//Неизвестный чит
#define AC_FLYHACK_ID   				1					//Флайхак чит
#define AC_AIRBRK_ID    				2					//Аирбрейк чит
#define AC_TELEPORT_ID  				3					//Телепорт чит
#define AC_FAKESPAWN_ID  				4					//Фейкспавн чит
#define AC_CRDMST_ID        			5					//Коордмастер чит
#define AC_SPEEDHACK_ID 				6					//Спидхак чит
#define AC_CARSHOT_ID       			7					//Каршот чит
#define AC_INV_ID        				8					//Чит на ГМ
#define AC_HEALTH_ID        			9					//Чит на здоровье
#define AC_ARMOUR_ID        			10					//Чит на броню
#define AC_WEAPON_ID    				11					//Чит на оружие
#define AC_RAPID_ID     				12					//Рапид чит
#define AC_FAKEKILL_ID  				13					//Фейккилл чит
#define AC_CARFLOOD_ID  				14					//Карфлуд
#define AC_INVISIBLE_ID					15					//Невидимка
#define AC_SPAWNCAR_ID					16					//Спавн машин
#define AC_TPINCAR_ID   				17					//ТП в машину (через колёсико мышки)
#define AC_AIM_ID						18					//Аим чит (ProAIM)
#define AC_SPECACT_ID					19					//Специальные действия (типо джетпака)
#define AC_UNFREEZE_ID					20					//Разморозка
#define AC_CJRUN_ID						21					//CJ бег
#define AC_FAKE_COORDS                  22					//Отправка на сервер поддельных координат

#define AC_SOBEIT_ERROR					0
#define AC_SOBEIT_USE					1
#define AC_SOBEIT_NOT_USE				2
#define AC_SOBEIT_IGNORE				3

#define AC_SOBEIT_CHECK_AUTO			1
#define AC_SOBEIT_CHECK_MANUAL			2

//Паблики срабатывают при включенном ручном режиме (ManualControl = 1)
forward OnCheatDetected(playerid, anticheatid, ip[]);
forward OnCrasherDetected(playerid, crasher[], ip[]);
forward OnPlayerCheckSobeit(playerid, result, type);
/*
	native RegisterPlayerIsAdmin(playerid);
	native UnRegisterPlayerIsAdmin(playerid);
	native EnableAntiCheatForPlayer(playerid);
	native DisableAntiCheatForPlayer(playerid);
	native CheckPlayerUseSobeit(playerid);
	native IsPlayerUseSobeit(playerid);
*/
//////////////////////////////////////////////////////////////////////

#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif
#define OnPlayerText acpt_OnPlayerText
#if    defined    acpt_OnPlayerText
	forward acpt_OnPlayerText(playerid, text[]);
#endif  

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn acpt_OnPlayerSpawn
#if    defined    acpt_OnPlayerSpawn
	forward acpt_OnPlayerSpawn(playerid);
#endif  

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath acpt_OnPlayerDeath
#if    defined    acpt_OnPlayerDeath
	forward acpt_OnPlayerDeath(playerid, killerid, reason);
#endif  

#if defined _ALS_OnPlayerPickUpPickup
	#undef OnPlayerPickUpPickup
#else
	#define _ALS_OnPlayerPickUpPickup
#endif
#define OnPlayerPickUpPickup acpt_OnPlayerPickUpPickup
#if    defined    acpt_OnPlayerPickUpPickup
	forward acpt_OnPlayerPickUpPickup(playerid, pickupid);
#endif

#if defined _ALS_OnPlayerPickUpDynamicPicku
	#undef OnPlayerPickUpDynamicPickup
#else
	#define _ALS_OnPlayerPickUpDynamicPicku
#endif
#define OnPlayerPickUpDynamicPickup acpt_OnPlayerPickUpDynamicPicku
#if    defined    acpt_OnPlayerPickUpDynamicPicku
	forward acpt_OnPlayerPickUpDynamicPicku(playerid, pickupid);
#endif  

#if defined _ALS_OnPlayerEnterCheckpoint
	#undef OnPlayerEnterCheckpoint
#else
	#define _ALS_OnPlayerEnterCheckpoint
#endif
#define OnPlayerEnterCheckpoint acpt_OnPlayerEnterCheckpoint
#if    defined    acpt_OnPlayerEnterCheckpoint
	forward acpt_OnPlayerEnterCheckpoint(playerid);
#endif

#if defined _ALS_OnPlayerEnter\
RaceCheckpoint
	#undef OnPlayerEnterRaceCheckpoint
#else
	#define _ALS_OnPlayerEnter\
	RaceCheckpoint
#endif
#define OnPlayerEnterRaceCheckpoint acpt_OnPlayerEnterRaceCheckpoin
#if    defined    acpt_OnPlayerEnterRaceCheckpoin
	forward acpt_OnPlayerEnterRaceCheckpoin(playerid);
#endif

#if defined _ALS_OnPlayerEnterDynamicCP
	#undef OnPlayerEnterDynamicCP
#else
	#define _ALS_OnPlayerEnterDynamicCP
#endif
#define OnPlayerEnterDynamicCP acpt_OnPlayerEnterDynamicCP
#if    defined    acpt_OnPlayerEnterDynamicCP
	forward acpt_OnPlayerEnterDynamicCP(playerid, checkpointid);
#endif

#if defined _ALS_OnPlayerEnterDynamicRaceCP
	#undef OnPlayerEnterDynamicRaceCP
#else
	#define _ALS_OnPlayerEnterDynamicRaceCP
#endif
#define OnPlayerEnterDynamicRaceCP acpt_OnPlayerEnterDynamicRaceCP
#if    defined    acpt_OnPlayerEnterDynamicRaceCP
	forward acpt_OnPlayerEnterDynamicRaceCP(playerid, checkpointid);
#endif

#if defined _ALS_OnDialogResponse
    #undef    OnDialogResponse
#else
    #define    _ALS_OnDialogResponse
#endif
#define    OnDialogResponse    acpt_OnDialogResponse
#if defined acpt_OnDialogResponse
	forward acpt_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif  

#if defined _ALS_OnPlayerWeaponShot
    #undef    OnPlayerWeaponShot
#else
    #define    _ALS_OnPlayerWeaponShot
#endif
#define    OnPlayerWeaponShot    acpt_OnPlayerWeaponShot
#if defined acpt_OnPlayerWeaponShot
	forward acpt_OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
#endif  

#if defined _ALS_OnPlayerUpdate
    #undef    OnPlayerUpdate
#else
    #define    _ALS_OnPlayerUpdate
#endif
#define    OnPlayerUpdate    acpt_OnPlayerUpdate
#if defined acpt_OnPlayerUpdate
	forward acpt_OnPlayerUpdate(playerid);
#endif

//Available language: ru/en
stock SetScriptLanguage(language[] = "ru") return CallRemoteFunction("acpt_SetScriptLanguage", "s", (strlen(language) == 0) ? (NULL) : language);  
stock RegisterPlayerIsAdmin(acpt_playerid) return CallRemoteFunction("acpt_RegisterPlayerIsAdmin", "d", acpt_playerid);  
stock UnRegisterPlayerIsAdmin(acpt_playerid) return CallRemoteFunction("acpt_UnRegisterPlayerIsAdmin", "d", acpt_playerid); 
stock EnableAntiCheatForPlayer(acpt_playerid) return CallRemoteFunction("acpt_EnableAntiCheatForPlayer", "d", acpt_playerid); 
stock DisableAntiCheatForPlayer(acpt_playerid) return CallRemoteFunction("acpt_DisableAntiCheatForPlayer", "d", acpt_playerid);
stock GetPlayerDistance(acpt_playerid) return CallRemoteFunction("acpt_GetPlayerDistance", "d", acpt_playerid);
stock GetVehicleDistance(acpt_vehicleid) return CallRemoteFunction("acpt_GetVehicleDistance", "d", acpt_vehicleid);
stock CheckPlayerUseSobeit(acpt_playerid) return CallRemoteFunction("acpt_CheckPlayerUseSobeit", "d", acpt_playerid);
stock IsPlayerUseSobeit(acpt_playerid) return CallRemoteFunction("acpt_IsPlayerUseSobeit", "d", acpt_playerid);

stock acpt_SendClientMessage(acpt_playerid, color, const text[]) return CallRemoteFunction("acpt_SendClientMessage", "dds", acpt_playerid, color, (strlen(text) == 0) ? (NULL) : text);
stock acpt_SendClientMessageToAll(color, const text[]) return CallRemoteFunction("acpt_SendClientMessageToAll", "ds", color, (strlen(text) == 0) ? (NULL) : text);
stock acpt_TogglePlayerControllable(acpt_playerid, toggle) return CallRemoteFunction("acpt_TogglePlayerControllable", "dd", acpt_playerid, toggle);
stock acpt_TogglePlayerSpectating(acpt_playerid, toggle) return CallRemoteFunction("acpt_TogglePlayerSpectating", "dd", acpt_playerid, toggle);
stock acpt_SetPlayerArmedWeapon(acpt_playerid, acpt_weaponid)	return CallRemoteFunction("acpt_SetPlayerArmedWeapon", "dd", acpt_playerid, acpt_weaponid);
stock acpt_SetPlayerHealth(acpt_playerid, Float:health)	return CallRemoteFunction("acpt_SetPlayerHealth", "df", acpt_playerid, health);
stock acpt_SetPlayerArmour(acpt_playerid, Float:armour)	return CallRemoteFunction("acpt_SetPlayerArmour", "df", acpt_playerid, armour);
stock acpt_ShowPlayerDialog(acpt_playerid, dialogid, style, const caption[], const text[], const button1[], const button2[])	
{
	return CallRemoteFunction("acpt_ShowPlayerDialog", "dddssss", acpt_playerid, dialogid, style, (strlen(caption) == 0) ? (NULL) : caption, (strlen(text) == 0) ? (NULL) : text, (strlen(button1) == 0) ? (NULL) : button1, (strlen(button2) == 0) ? (NULL) : button2);
}
stock acpt_SpawnPlayer(acpt_playerid) return CallRemoteFunction("acpt_SpawnPlayer", "d", acpt_playerid);
stock acpt_ResetPlayerWeapons(acpt_playerid) return CallRemoteFunction("acpt_ResetPlayerWeapons", "d", acpt_playerid);
stock acpt_GivePlayerWeapon(acpt_playerid, acpt_gunid, acpt_ammo) return CallRemoteFunction("acpt_GivePlayerWeapon", "ddd", acpt_playerid, acpt_gunid, acpt_ammo);
stock acpt_SetPlayerAmmo(acpt_playerid, acpt_gunid, acpt_ammo) return CallRemoteFunction("acpt_SetPlayerAmmo", "ddd", acpt_playerid, acpt_gunid, acpt_ammo);
stock acpt_SetPlayerPosFindZ(acpt_playerid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetPlayerPosFindZ", "dfff", acpt_playerid, X, Y, Z);
stock acpt_SetPlayerPos(acpt_playerid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetPlayerPos", "dfff", acpt_playerid, X, Y, Z);
stock acpt_SetVehicleHealth(acpt_vehicleid, Float:health) return CallRemoteFunction("acpt_SetVehicleHealth", "df", acpt_vehicleid, health);
stock acpt_RepairVehicle(acpt_vehicleid) return CallRemoteFunction("acpt_RepairVehicle", "d", acpt_vehicleid);
stock acpt_SetVehiclePos(acpt_vehicleid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetVehiclePos", "dfff", acpt_vehicleid, X, Y, Z);
stock acpt_AddStaticVehicle(acpt_modelid, Float:X, Float:Y, Float:Z, Float:Rotation, color1, color2) return CallRemoteFunction("acpt_AddStaticVehicle", "dffffdd", acpt_modelid, X, Y, Z, Rotation, color1, color2);
stock acpt_AddStaticVehicleEx(acpt_modelid, Float:X, Float:Y, Float:Z, Float:Rotation, color1, color2, respawn_delay, addsiren = 0) return CallRemoteFunction("acpt_AddStaticVehicleEx", "dffffdddd", acpt_modelid, X, Y, Z, Rotation, color1, color2, respawn_delay, addsiren); 
stock acpt_CreateVehicle(acpt_modelid, Float:X, Float:Y, Float:Z, Float:Rotation, color1, color2, respawn_delay, addsiren = 0) return CallRemoteFunction("acpt_CreateVehicle", "dffffdddd", acpt_modelid, X, Y, Z, Rotation, color1, color2, respawn_delay, addsiren);
stock acpt_RemovePlayerFromVehicle(acpt_playerid) return CallRemoteFunction("acpt_RemovePlayerFromVehicle", "d", acpt_playerid);
stock acpt_ChangeVehicleColor(acpt_vehicleid, color1, color2) return CallRemoteFunction("acpt_ChangeVehicleColor", "ddd", acpt_vehicleid, color1, color2);
stock acpt_AddVehicleComponent(acpt_vehicleid, componentid) return CallRemoteFunction("acpt_AddVehicleComponent", "dd", acpt_vehicleid, componentid);
stock acpt_RemoveVehicleComponent(acpt_vehicleid, componentid) return CallRemoteFunction("acpt_RemoveVehicleComponent", "dd", acpt_vehicleid, componentid);
stock acpt_PutPlayerInVehicle(acpt_playerid, acpt_vehicleid, seat) return CallRemoteFunction("acpt_PutPlayerInVehicle", "ddd", acpt_playerid, acpt_vehicleid, seat);
stock acpt_LinkVehicleToInterior(acpt_vehicleid, interiorid) return CallRemoteFunction("acpt_LinkVehicleToInterior", "dd", acpt_vehicleid, interiorid);
stock acpt_SetPlayerCameraPos(acpt_playerid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetPlayerCameraPos", "dfff", acpt_playerid, X, Y, Z);
stock acpt_SetPlayerCameraLookAt(acpt_playerid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetPlayerCameraLookAt", "dfff", acpt_playerid, X, Y, Z);
stock acpt_SetCameraBehindPlayer(acpt_playerid) return CallRemoteFunction("acpt_SetCameraBehindPlayer", "d", acpt_playerid);
stock acpt_InterpolateCameraPos(acpt_playerid, Float:X, Float:Y, Float:Z, Float:ToX, Float:ToY, Float:ToZ, timer, cut = CAMERA_CUT) return CallRemoteFunction("acpt_InterpolateCameraPos", "dffffffdd", acpt_playerid, X, Y, Z, ToX, ToY, ToZ, timer, cut);
stock acpt_InterpolateCameraLookAt(acpt_playerid, Float:X, Float:Y, Float:Z, Float:ToX, Float:ToY, Float:ToZ, timer, cut = CAMERA_CUT) return CallRemoteFunction("acpt_InterpolateCameraLookAt", "dffffffdd", acpt_playerid, X, Y, Z, ToX, ToY, ToZ, timer, cut);
stock acpt_SetPlayerSpecialAction(acpt_playerid, actionid) return CallRemoteFunction("acpt_SetPlayerSpecialAction", "dd", acpt_playerid, actionid);
stock acpt_SetVehicleParamsEx(acpt_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective) return CallRemoteFunction("acpt_SetVehicleParamsEx", "dddddddd", acpt_vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
stock acpt_ManualVehicleEngineAndLigh() return CallRemoteFunction("acpt_ManualVehicleEngineAndLigh", "");

stock acpt_SetPlayerCheckpoint(acpt_playerid, Float:X, Float:Y, Float:Z, Float:size) return CallRemoteFunction("acpt_SetPlayerCheckpoint", "dffff", acpt_playerid, X, Y, Z, size);
stock acpt_SetPlayerRaceCheckpoint(acpt_playerid, type, Float:X, Float:Y, Float:Z, Float:nextx, Float:nexty, Float:nextz, Float:size) return CallRemoteFunction("acpt_SetPlayerRaceCheckpoint", "ddfffffff", acpt_playerid, type, X, Y, Z, nextx, nexty, nextz, size);
stock acpt_CreateDynamicCP(Float:X, Float:Y, Float:Z, Float:size, worldid = -1, interiorid = -1, acpt_playerid = -1, Float:streamdistance = 300.0) return CallRemoteFunction("acpt_CreateDynamicCP", "ffffdddd", X, Y, Z, size, worldid, interiorid, acpt_playerid, streamdistance);
stock acpt_CreateDynamicRaceCP(type, Float:X, Float:Y, Float:Z, Float:nextx, Float:nexty, Float:nextz, Float:size, worldid = -1, interiorid = -1, acpt_playerid = -1, Float:streamdistance = 300.0) return CallRemoteFunction("acpt_CreateDynamicRaceCP", "dfffffffdddd", type, X, Y, Z, nextx, nexty, nextz, size, worldid, interiorid, acpt_playerid, streamdistance);
stock acpt_CreatePickup(modelid, type, Float:X, Float:Y, Float:Z, Virtualworld = -1) return CallRemoteFunction("acpt_CreatePickup", "ddfffd", modelid, type, X, Y, Z, Virtualworld);
stock acpt_CreateDynamicPickup(modelid, type, Float:X, Float:Y, Float:Z, worldid = -1, interiorid = -1, acpt_playerid = -1, Float:streamdistance = 300.0)  return CallRemoteFunction("acpt_CreateDynamicPickup", "ddfffdddf", modelid, type, X, Y, Z, worldid, interiorid, acpt_playerid, streamdistance);

stock acpt_SetSpawnInfo(acpt_playerid, team, skin, Float:x, Float:y, Float:z, Float:Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo) return CallRemoteFunction("acpt_SetSpawnInfo", "dddffffdddddd", acpt_playerid, team, skin, x, y, z, Angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);
stock acpt_SetPlayerVelocity(acpt_playerid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetPlayerVelocity", "dfff", acpt_playerid, X, Y, Z);
stock acpt_SetVehicleVelocity(acpt_vehicleid, Float:X, Float:Y, Float:Z) return CallRemoteFunction("acpt_SetVehicleVelocity", "dfff", acpt_vehicleid, X, Y, Z);

#if defined _ALS_SendClientMessage
    #undef    SendClientMessage
#else
    #define    _ALS_SendClientMessage
#endif
#define    SendClientMessage    acpt_SendClientMessage

#if defined _ALS_SendClientMessageToAll
    #undef    SendClientMessageToAll
#else
    #define    _ALS_SendClientMessageToAll
#endif
#define    SendClientMessageToAll    acpt_SendClientMessageToAll

#if defined _ALS_TogglePlayerControllable
    #undef    TogglePlayerControllable
#else
    #define    _ALS_TogglePlayerControllable
#endif
#define    TogglePlayerControllable    acpt_TogglePlayerControllable

#if defined _ALS_TogglePlayerSpectating
    #undef    TogglePlayerSpectating
#else
    #define    _ALS_TogglePlayerSpectating
#endif
#define    TogglePlayerSpectating    acpt_TogglePlayerSpectating

#if defined _ALS_SetPlayerArmedWeapon
    #undef    SetPlayerArmedWeapon
#else
    #define    _ALS_SetPlayerArmedWeapon
#endif
#define    SetPlayerArmedWeapon    acpt_SetPlayerArmedWeapon

#if defined _ALS_SetPlayerHealth
    #undef    SetPlayerHealth
#else
    #define    _ALS_SetPlayerHealth
#endif
#define    SetPlayerHealth    acpt_SetPlayerHealth

#if defined _ALS_SetPlayerArmour
    #undef    SetPlayerArmour
#else
    #define    _ALS_SetPlayerArmour
#endif
#define    SetPlayerArmour    acpt_SetPlayerArmour

#if defined _ALS_ShowPlayerDialog
    #undef    ShowPlayerDialog
#else
    #define    _ALS_ShowPlayerDialog
#endif
#define    ShowPlayerDialog    acpt_ShowPlayerDialog

#if defined _ALS_SpawnPlayer
    #undef SpawnPlayer
#else
    #define _ALS_SpawnPlayer
#endif
#define SpawnPlayer acpt_SpawnPlayer

#if defined _ALS_ResetPlayerWeapons
    #undef ResetPlayerWeapons
#else
    #define _ALS_ResetPlayerWeapons
#endif
#define ResetPlayerWeapons acpt_ResetPlayerWeapons

#if defined _ALS_GivePlayerWeapon
    #undef    GivePlayerWeapon
#else
    #define    _ALS_GivePlayerWeapon
#endif
#define    GivePlayerWeapon    acpt_GivePlayerWeapon

#if defined _ALS_SetPlayerAmmo
    #undef    SetPlayerAmmo
#else
    #define    _ALS_SetPlayerAmmo
#endif
#define    SetPlayerAmmo    acpt_SetPlayerAmmo

#if defined _ALS_SetPlayerCameraPos
    #undef    SetPlayerCameraPos
#else
    #define    _ALS_SetPlayerCameraPos
#endif
#define    SetPlayerCameraPos    acpt_SetPlayerCameraPos

#if defined _ALS_SetPlayerCameraLookAt
    #undef    SetPlayerCameraLookAt
#else
    #define    _ALS_SetPlayerCameraLookAt
#endif
#define    SetPlayerCameraLookAt    acpt_SetPlayerCameraLookAt

#if defined _ALS_SetCameraBehindPlayer
    #undef    SetCameraBehindPlayer
#else
    #define    _ALS_SetCameraBehindPlayer
#endif
#define    SetCameraBehindPlayer    acpt_SetCameraBehindPlayer

#if defined _ALS_InterpolateCameraPos
    #undef    InterpolateCameraPos
#else
    #define    _ALS_InterpolateCameraPos
#endif
#define    InterpolateCameraPos    acpt_InterpolateCameraPos

#if defined _ALS_InterpolateCameraLookAt
    #undef    InterpolateCameraLookAt
#else
    #define    _ALS_InterpolateCameraLookAt
#endif
#define    InterpolateCameraLookAt    acpt_InterpolateCameraLookAt

#if defined _ALS_SetPlayerPosFindZ
    #undef    SetPlayerPosFindZ
#else
    #define    _ALS_SetPlayerPosFindZ
#endif
#define    SetPlayerPosFindZ    acpt_SetPlayerPosFindZ

#if defined _ALS_SetPlayerPos
    #undef    SetPlayerPos
#else
    #define    _ALS_SetPlayerPos
#endif
#define    SetPlayerPos    acpt_SetPlayerPos

#if defined _ALS_SetVehicleHealth
    #undef    SetVehicleHealth
#else
    #define    _ALS_SetVehicleHealth
#endif
#define    SetVehicleHealth    acpt_SetVehicleHealth

#if defined _ALS_RepairVehicle
    #undef    RepairVehicle
#else
    #define    _ALS_RepairVehicle
#endif
#define    RepairVehicle    acpt_RepairVehicle

#if defined _ALS_SetVehiclePos
    #undef    SetVehiclePos
#else
    #define    _ALS_SetVehiclePos
#endif
#define    SetVehiclePos    acpt_SetVehiclePos

#if defined _ALS_AddStaticVehicle
    #undef    AddStaticVehicle
#else
    #define    _ALS_AddStaticVehicle
#endif
#define    AddStaticVehicle    acpt_AddStaticVehicle

#if defined _ALS_AddStaticVehicleEx
    #undef    AddStaticVehicleEx
#else
    #define    _ALS_AddStaticVehicleEx
#endif
#define    AddStaticVehicleEx    acpt_AddStaticVehicleEx

#if defined _ALS_CreateVehicle
    #undef    CreateVehicle
#else
    #define    _ALS_CreateVehicle
#endif
#define    CreateVehicle    acpt_CreateVehicle

#if defined _ALS_RemovePlayerFromVehicle
    #undef    RemovePlayerFromVehicle
#else
    #define    _ALS_RemovePlayerFromVehicle
#endif
#define    RemovePlayerFromVehicle    acpt_RemovePlayerFromVehicle

#if defined _ALS_SetVehicleParamsEx
    #undef    SetVehicleParamsEx
#else
    #define    _ALS_SetVehicleParamsEx
#endif
#define    SetVehicleParamsEx    acpt_SetVehicleParamsEx

#if defined _ALS_ManualVehicleEngineAndLigh
    #undef    ManualVehicleEngineAndLights
#else
    #define    _ALS_ManualVehicleEngineAndLigh
#endif
#define    ManualVehicleEngineAndLights    acpt_ManualVehicleEngineAndLigh

#if defined _ALS_ChangeVehicleColor
    #undef    ChangeVehicleColor
#else
    #define    _ALS_ChangeVehicleColor
#endif
#define    ChangeVehicleColor    acpt_ChangeVehicleColor

#if defined _ALS_AddVehicleComponent
    #undef    AddVehicleComponent
#else
    #define    _ALS_AddVehicleComponent
#endif
#define    AddVehicleComponent    acpt_AddVehicleComponent

#if defined _ALS_RemoveVehicleComponent
    #undef    RemoveVehicleComponent
#else
    #define    _ALS_RemoveVehicleComponent
#endif
#define    RemoveVehicleComponent    acpt_RemoveVehicleComponent

#if defined _ALS_PutPlayerInVehicle
    #undef    PutPlayerInVehicle
#else
    #define    _ALS_PutPlayerInVehicle
#endif
#define    PutPlayerInVehicle    acpt_PutPlayerInVehicle

#if defined _ALS_LinkVehicleToInterior
    #undef    LinkVehicleToInterior
#else
    #define    _ALS_LinkVehicleToInterior
#endif
#define    LinkVehicleToInterior    acpt_LinkVehicleToInterior

#if defined _ALS_SetPlayerSpecialAction
    #undef    SetPlayerSpecialAction
#else
    #define    _ALS_SetPlayerSpecialAction
#endif
#define    SetPlayerSpecialAction    acpt_SetPlayerSpecialAction

#if defined _ALS_SetPlayerCheckpoint
    #undef    SetPlayerCheckpoint
#else
    #define    _ALS_SetPlayerCheckpoint
#endif
#define    SetPlayerCheckpoint	acpt_SetPlayerCheckpoint

#if defined _ALS_SetPlayerRaceCheckpoint
    #undef    SetPlayerRaceCheckpoint
#else
    #define    _ALS_SetPlayerRaceCheckpoint
#endif
#define    SetPlayerRaceCheckpoint	acpt_SetPlayerRaceCheckpoint

#if defined _ALS_CreateDynamicCP
    #undef    CreateDynamicCP
#else
    #define    _ALS_CreateDynamicCP
#endif
#define    CreateDynamicCP	acpt_CreateDynamicCP

#if defined _ALS_CreateDynamicRaceCP
    #undef    CreateDynamicRaceCP
#else
    #define    _ALS_CreateDynamicRaceCP
#endif
#define    CreateDynamicRaceCP	acpt_CreateDynamicRaceCP

#if defined _ALS_CreatePickup
    #undef    CreatePickup
#else
    #define    _ALS_CreatePickup
#endif
#define    CreatePickup		acpt_CreatePickup

#if defined _ALS_CreateDynamicPickup
    #undef    CreateDynamicPickup
#else
    #define    _ALS_CreateDynamicPickup
#endif
#define    CreateDynamicPickup		acpt_CreateDynamicPickup

#if defined _ALS_SetSpawnInfo
    #undef    SetSpawnInfo
#else
    #define    _ALS_SetSpawnInfo
#endif
#define    SetSpawnInfo		acpt_SetSpawnInfo

#if defined _ALS_SetPlayerVelocity
    #undef    SetPlayerVelocity
#else
    #define    _ALS_SetPlayerVelocity
#endif
#define    SetPlayerVelocity	acpt_SetPlayerVelocity

#if defined _ALS_SetVehicleVelocity
    #undef    SetVehicleVelocity
#else
    #define    _ALS_SetVehicleVelocity
#endif
#define    SetVehicleVelocity	acpt_SetVehicleVelocity

/*
//Примеры скриптов:

1) Отключение античита для игрока с ником Test

	public OnPlayerConnect(playerid)
	{
		new nick[MAX_PLAYER_NAME];
		GetPlayerName(playerid, nick, sizeof(nick));
		if(strcmp(nick, "Test", false) == 0) DisableAntiCheatForPlayer(playerid);
	}
	
2) Включаем оповещения о читах игроку с ником Test
	
	public OnPlayerConnect(playerid)
	{
		new nick[MAX_PLAYER_NAME];
		GetPlayerName(playerid, nick, sizeof(nick));
		if(strcmp(nick, "Test", false) == 0) RegisterPlayerIsAdmin(playerid);
	}

	
3) Получаем список всех игроков, которые используют собейт

	public OnPlayerText(playerid, cmdtext[])
	{
		new string[MAX_PLAYER_NAME + 5];
		if(strcmp(cmdtext, "/soblist", false) == 0)
		{
			new count, nick[MAX_PLAYER_NAME];
			SendClientMessage(playerid, 0xFFA500FF, "Список игроков, использующих собейт:")
			for(new i = GetPlayerPoolSize(); i >= 0; i--)
			{
				if(!IsPlayerConnected(i) || !IsPlayerUseSobeit(i)) continue;
				GetPlayerName(i, nick, sizeof(nick));
				format(string, sizeof(string), "%d. %s", count + 1, nick);
				SendClientMessage(playerid, 0x42AAFFFF, string);
				count ++;
			}
			if(count == 0) SendClientMessage(playerid, 0xFF6347FF, "Игроков, использующих собейт нет")
		}
		return 1;
	}

4) Блокируем вход на сервер игрокам, использующим собейт
	
	public OnPlayerCheckSobeit(playerid, result, type)
	{
		if(type == AC_SOBEIT_CHECK_AUTO && (result == AC_SOBEIT_USE || result == AC_SOBEIT_IGNORE)) 
		{
			SendClientMessage(playerid, 0xFF6347FF, "Вы используете запрещенное программное обеспечение, т.н собейт");
			SendClientMessage(playerid, 0xFF6347FF, "Использование данного софта строго запрещенно на нашем сервере");
			SendClientMessage(playerid, 0xFF6347FF, "Для успешного входа на сервер, удалите запрещённое программное обеспечение");
			return Kick(playerid);
		}
	}

5) Переводим собейтера в читерский вирт. мир
	
	public OnPlayerSpawn(playerid)
	{
		// тут ваш код //
		if(IsPlayerUseSobeit(playerid)) SetPlayerVirtualWorld(playerid, 15000);
	}


*/