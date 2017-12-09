

#define Random(%0,%1) random(%1 - %0)+%0

#define CAR 0
#define BIKE 1
#define MOTORBIKE 2
#define BOAT 3
#define PLANE 4
#define RC 5
#define TRAIN 6
#define TRAILER 7
#define HELICOPTER 8

#define MAX_PROCESS 9000
#define Radius 4
#define PRESSED(%0) (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))

new PlayerText:PT_MYTIMER[MAX_PLAYERS][2];
new Text:T_MYTIMER[2];

new Float:PosProgressBar[MAX_PLAYERS];

new Text:ChangeColor[66];
new ColorsAvailable[66] = {
    1, 0, 2, 3, 4, 6, 8, 12, 13, 16, 17, 20, 24, 28, 44, 43, 46, 51, 52, 55, 57, 79, 93, 86, 87, 65, 97, 112, 117, 118, 126, 111, 103, 102, 128, 145, 136, 139, 143, 158, 175, 170, 171, 154, 176, 179, 182, 191, 194, 195, 196, 198, 215, 224, 225, 237, 241, 244, 245, 248, 251, 252, 253, 254
};
new AllCarColors[256] = {
    0x000000FF,0xFFFFFFFF,0x55aaa7FF,0xce575bFF,0x58685dFF,0xb06c77FF,0xf8ad38FF,0x7a96acFF,0xdfdec9FF,0x81897aFF,
    0x677776FF,0x93948eFF,0x7e9689FF,0x807c70FF,0xe8eac3FF,0xbab9a5FF,0x73996aFF,0xa54549FF,0xc55063FF,0xd8d5b2FF,
    0x86979eFF,0xa66b67FF,0x8e4556FF,0xcfc3a9FF,0x6c6d65FF,0x5b5a55FF,0xafb295FF,0x77705eFF,0x5a6466FF,0xa89f82FF,
    0x64433aFF,0x73423dFF,0xb5bcb4FF,0xa1a58aFF,0x96947fFF,0x918a6cFF,0x5a5b53FF,0x5b6656FF,0xa8b186FF,0x8d9389FF,
    0x3f3c35FF,0x80765dFF,0x873b3bFF,0x7d3334FF,0x3b5741FF,0x71413dFF,0xaaa176FF,0x89815dFF,0xc2b894FF,0xd6d0b0FF,
    0xa9a98fFF,0x647d67FF,0x849283FF,0x495261FF,0x565b61FF,0x9d846eFF,0xb0af90FF,0xa19273FF,0x7a3138FF,0x5c6c69FF,
    0x9e9c83FF,0x887554FF,0x803c3dFF,0x928f7cFF,0xcfcda7FF,0xd4d27fFF,0x6f534fFF,0xa7ada1FF,0xe1dd9eFF,0xd9b79bFF,
    0xa84645FF,0x96a097FF,0x6f725dFF,0xb6bd93FF,0x764040FF,0x434842FF,0xb0ac89FF,0xb5a778FF,0x8a473fFF,0x375369FF,
    0x9a555aFF,0xaa9c75FF,0xac5359FF,0x56665bFF,0x786151FF,0x995061FF,0x60843cFF,0x72858bFF,0x7c454aFF,0xa7a373FF,
    0xb8b29aFF,0x585e5cFF,0x827f6eFF,0x388a85FF,0x4b6566FF,0x4c5858FF,0xc3c0a1FF,0x97a79aFF,0x80a999FF,0xe1c99dFF,
    0x6e8c8aFF,0x57585cFF,0xd6b98dFF,0x426d80FF,0xa29368FF,0x818274FF,0x3d717fFF,0xb6ab7eFF,0x587482FF,0x696a62FF,
    0x8f7d59FF,0xa3a091FF,0x80948bFF,0x786954FF,0x72866aFF,0xaa4553FF,0x53616aFF,0x8f4f4fFF,0xbfc1b6FF,0x938369FF,
    0xb5a180FF,0x763b41FF,0x747567FF,0x846c50FF,0x914b4dFF,0x38526bFF,0xef87a2FF,0x3c3d38FF,0x6cb85dFF,0x725a4eFF,
    0x78acaaFF,0x987e59FF,0x9b675aFF,0x545d4cFF,0x706c83FF,0x7dc6bdFF,0xcb90c6FF,0x7fca6fFF,0xf7ebc3FF,0x9697abFF,
    0xc3bda3FF,0xbdaf88FF,0xcdbf67FF,0xab8e90FF,0xa28796FF,0xd2ee99FF,0xbd8a93FF,0xaa6a85FF,0x72715cFF,0x665b45FF,
    0x656952FF,0x7e926fFF,0x7398b5FF,0x7da477FF,0x6bcf79FF,0x65c8a9FF,0xe0d59dFF,0xc8c5b4FF,0xde7c5fFF,0x77694cFF,
    0x5d6d49FF,0xd17f74FF,0x6f93b3FF,0x62b79aFF,0x667264FF,0x6aa998FF,0x6daaa5FF,0xaa7faaFF,0x875e4aFF,0xbfb1b0FF,
    0xb4a8acFF,0x987f9dFF,0x686947FF,0x80604bFF,0x8e6c50FF,0xd8685aFF,0xd294a9FF,0xbf9899FF,0xbb839cFF,0x826168FF,
    0xbd825aFF,0xba6254FF,0xd28865FF,0xcf7958FF,0xc88c84FF,0xbba899FF,0x4f5847FF,0x516b48FF,0x6c825bFF,0x677c5bFF,
    0xaa757dFF,0x8dca85FF,0xd4c7a4FF,0xc0bfaaFF,0xdfd249FF,0xbac775FF,0xbdc2a2FF,0xbabb5eFF,0x717caaFF,0x7d7b4aFF,
    0xc1aa74FF,0x536370FF,0x79936cFF,0x606f6cFF,0x798f8dFF,0x515459FF,0x4d585aFF,0x677a76FF,0x7d99a7FF,0x5d7b7dFF,
    0x6f8b8cFF,0x72668aFF,0xac6c53FF,0xd3caadFF,0x98a053FF,0x545945FF,0xcc996eFF,0xa3caafFF,0xd29779FF,0xcc9054FF,
    0xdd888fFF,0xd6c377FF,0xd07151FF,0x596271FF,0x936556FF,0x89864fFF,0x9cd665FF,0x5a765dFF,0xd0b858FF,0x66b758FF,
    0x83605aFF,0xb79153FF,0xc37d9fFF,0xbf6791FF,0x5b7f51FF,0x71894fFF,0x5d7166FF,0xc3919dFF,0xcca470FF,0xaf6c52FF,
    0x77c4a4FF,0x99c556FF,0x9b616fFF,0x63bd63FF,0x7c5d49FF,0x57694fFF,0x809ea8FF,0x748080FF,0x935d5bFF,0x90575eFF,
    0xaaa184FF,0x7d7e70FF,0x716d62FF,0xc9c3a3FF,0x9b907aFF,0x838786FF
};

forward MyTimer(playerid,time,text[]);
public MyTimer(playerid,time,text[])
{
	new Float:count12;


	count12 = (178.380661-124.500732)/time;
	
	PosProgressBar[playerid] += count12;
	
	new str[32];
	format(str,sizeof(str),"%s",text);
	TextDrawSetString(T_MYTIMER[0],str);
	
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][1], 124.500732+PosProgressBar[playerid], -4.666666);
	
	PlayerTextDrawShow(playerid,PT_MYTIMER[playerid][0]);
	PlayerTextDrawShow(playerid,PT_MYTIMER[playerid][1]);
	
	TextDrawShowForPlayer(playerid,T_MYTIMER[0]);
	TextDrawShowForPlayer(playerid,T_MYTIMER[1]);

}

forward MyTimerEnd(playerid);
public MyTimerEnd(playerid)
{
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][1], 124.500732, -4.666666);
	PosProgressBar[playerid] = 0.0;
	PlayerTextDrawHide(playerid,PT_MYTIMER[playerid][0]);
	PlayerTextDrawHide(playerid,PT_MYTIMER[playerid][1]);
		
	TextDrawHideForPlayer(playerid,T_MYTIMER[0]);
	TextDrawHideForPlayer(playerid,T_MYTIMER[1]);
	
}

stock LoadJob()
{

	//CreateActor(8, 2695.6311,-2472.9978,2340.4041,233.6272);
	//CreateDynamic3DTextLabel("{008080}Работа грузчика\n{BFC0C2}N чтобы начать работу",-1,2695.6311,-2472.9978,2340.4041,5.0);

	CreateDynamicPickup(1650,23,1329.0520,-879.2369,39.5781);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,1329.0520,-879.2369,39.5781,5.0);
	
	CreateDynamicPickup(1650,23,2250.7344,-55.3851,26.4751);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,2250.7344,-55.3851,26.4751,5.0);
	
	CreateDynamicPickup(1650,23,618.6074,-586.5919,17.2330);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,618.6074,-586.5919,17.2330,5.0);

	CreateDynamicPickup(1650,23,1560.3517,-1694.3448,5.8970);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,1560.3517,-1694.3448,5.8970,5.0);
	
	CreateDynamicPickup(1650,23,2209.8601,-2551.0078,22.0444);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,2209.8601,-2551.0078,22.0444,5.0);
	
	CreateDynamicPickup(1650,23,2208.9705,-2520.9858,22.0464);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,2208.9705,-2520.9858,22.0464,5.0);
	
	CreateDynamicPickup(1650,23,2049.6257,-2053.9443,13.6072);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,2049.6257,-2053.9443,13.6072,5.0);
	
	CreateDynamicPickup(1650,23,2301.0442,-1937.7793,13.5838);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,2301.0442,-1937.7793,13.5838,5.0);
	
	CreateDynamicPickup(1650,23,1097.7919,-1314.7067,13.6940);
	CreateDynamic3DTextLabel("Ремонт и заправка\n{ffffff}Нажмите 'N' чтобы починить и заправить автомобиль.",COLOR_INFO,1097.7919,-1314.7067,13.6940,5.0);
//	
	
	
	
	CreateDynamicPickup(1241,23,1141.9927,-1322.5067,13.5871);
	
	
}

stock FixText(string[]) 
{ 
	new result[256]; 
	for (new i=0; i < 256; i++) 
	{ 
		switch (string[i]) 
		{ 
			case 'а', 'А': result[i] = 'A'; 
			case 'б', 'Б': result[i] = 'Ђ'; 
			case 'в', 'В': result[i] = 'B'; 
			case 'г', 'Г': result[i] = '‚'; //
			case 'д', 'Д': result[i] = 'ѓ'; 
			case 'е', 'Е': result[i] = 'E'; 
			case 'ё', 'Ё': result[i] = 'E'; 
			case 'ж', 'Ж': result[i] = '„'; 
			case 'з', 'З': result[i] = '3';
			case 'и', 'И': result[i] = '…'; 
			case 'й', 'Й': result[i] = '†'; 
			case 'к', 'К': result[i] = 'K'; 
			case 'л', 'Л': result[i] = '‡'; 
			case 'м', 'М': result[i] = 'M'; 
			case 'н', 'Н': result[i] = 'H'; 
			case 'о', 'О': result[i] = 'O'; 
			case 'п', 'П': result[i] = 'Њ'; 
			case 'р', 'Р': result[i] = 'P'; 
			case 'с', 'С': result[i] = 'C'; 
			case 'т', 'Т': result[i] = 'T'; 
			case 'у', 'У': result[i] = 'Y'; 
			case 'ф', 'Ф': result[i] = 'Ѓ'; 
			case 'х', 'Х': result[i] = 'X'; 
			case 'ц', 'Ц': result[i] = '‰'; 
			case 'ч', 'Ч': result[i] = 'Ќ'; 
			case 'ш', 'Ш': result[i] = 'Ћ'; 
			case 'щ', 'Щ': result[i] = 'Љ'; 
			case 'ъ', 'Ъ': result[i] = 'ђ'; 
			case 'ы', 'Ы': result[i] = '‘'; 
			case 'ь', 'Ь': result[i] = '’'; 
			case 'э', 'Э': result[i] = '“'; 
			case 'ю', 'Ю': result[i] = '”'; 
			case 'я', 'Я': result[i] = '•'; 
			default: result[i] = string[i]; 
		} 
	} 
	return result; 
}  

#define YAHOOO 0.42
stock IsPlayerAimingVehicle(playerid, vehicleid)
{
    new Float:X1, Float:Y1, Float:Z1, Float:X2, Float:Y2, Float:Z2;
    GetPlayerPos(playerid, X1, Y1, Z1);
    GetVehiclePos(vehicleid, X2, Y2, Z2);
    new Float:Distance = floatsqroot(floatpower(floatabs(X1-X2), 2) + floatpower(floatabs(Y1-Y2), 2));
    if(Distance < 350)
    {
        new Float:A;
        GetPlayerFacingAngle(playerid, A);
        X1 += (Distance * floatsin(-A, degrees));
        Y1 += (Distance * floatcos(-A, degrees));
        Distance = floatsqroot(floatpower(floatabs(X1-X2), 2) + floatpower(floatabs(Y1-Y2), 2));
        if(Distance < YAHOOO )return true;
    }
    return false;
}
 
hook OnPlayerConnect(playerid)
{
	
	PT_MYTIMER[playerid][0] = CreatePlayerTextDraw(playerid, 128.032226, 280.333374, "back");
	PlayerTextDrawLetterSize(playerid, PT_MYTIMER[playerid][0], 0.000000, 0.392405);
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][0], 124.500732, 1.166667);
	PlayerTextDrawAlignment(playerid, PT_MYTIMER[playerid][0], 1);
	PlayerTextDrawColor(playerid, PT_MYTIMER[playerid][0], 0);
	PlayerTextDrawUseBox(playerid, PT_MYTIMER[playerid][0], true);
	PlayerTextDrawBoxColor(playerid, PT_MYTIMER[playerid][0], -2139062017);
	PlayerTextDrawSetShadow(playerid, PT_MYTIMER[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PT_MYTIMER[playerid][0], 0);
	PlayerTextDrawFont(playerid, PT_MYTIMER[playerid][0], 0);


	PT_MYTIMER[playerid][1] = CreatePlayerTextDraw(playerid, 128.032226, 280.333374, "font");
	PlayerTextDrawLetterSize(playerid, PT_MYTIMER[playerid][1], 0.000000, 0.392405);
	PlayerTextDrawTextSize(playerid, PT_MYTIMER[playerid][1], 124.500732, -4.666666);//178.380661
	PlayerTextDrawAlignment(playerid, PT_MYTIMER[playerid][1], 1);
	PlayerTextDrawColor(playerid, PT_MYTIMER[playerid][1], 0);
	PlayerTextDrawUseBox(playerid, PT_MYTIMER[playerid][1], true);
	PlayerTextDrawBoxColor(playerid, PT_MYTIMER[playerid][1], -1061109505);
	PlayerTextDrawSetShadow(playerid, PT_MYTIMER[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PT_MYTIMER[playerid][1], 0);
	PlayerTextDrawFont(playerid, PT_MYTIMER[playerid][1], 0);
	
	return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	
		
	if (PRESSED(KEY_NO))
	{
	
		if(IsPlayerInRangeOfPoint(playerid,5.0,1560.3517,-1694.3448,5.8970) || IsPlayerInRangeOfPoint(playerid,5.0,2301.0442,-1937.7793,13.5838) || IsPlayerInRangeOfPoint(playerid,5.0,1097.7919,-1314.7067,13.6940))
		{
			if(!IsPlayerInAnyVehicle(playerid)) return 1;
			if(character_info[playerid][faction] == 1 || character_info[playerid][faction] == 2 || character_info[playerid][faction] == 68)
			Dialog_Show(playerid,dFixxx,DIALOG_STYLE_MSGBOX,"Ремеонт и заправка","Вы действительно хотите отремонтировать и заправить ваш служебный автомобиль?","Да","Нет");
		}
	}
	return 1;
}
