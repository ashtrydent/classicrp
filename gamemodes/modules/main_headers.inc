#define         SERVER_NAME_FIRST     		"C:RP 0.60a-2"
#define         SERVER_NAME_SECOND     		"Classic RolePlay"
#define         SERVER_NAME_PREFIX     		" (www.classic-rp.com)"
#define         SERVER_URL		     		"www.classic-rp.com"

//DEFINE
#define INVALID_PLAYER_ID (0xFFFF)
/*#if defined MAX_PLAYERS
#undef MAX_PLAYERS
#define MAX_PLAYERS 301
#else
#define MAX_PLAYERS 301
#endif*/


#if defined _ALS_IsPlayerConnected
	#undef IsPlayerConnected
#else
	#define _ALS_IsPlayerConnected
#endif
#define IsPlayerConnected CheckPlayer



//------------------------------------------------------------------------------
#define         ANTICHEAT_GM                13101
#define         ANTICHEAT_RELOGIN           13102
#define         ANTICHEAT_DGUN              12103
#define         ANTICHEAT_COORD             131034
//------------------------------------------------------------------------------
#define 		COLOR_MSGSERVER 			0x3C8DBCFF
#define 		COLOR_MSGADMIN				COLOR_MSGSERVER
#define 		COLOR_MSGDESC				0xA4ADAAFF
#define 		COLOR_MSGERROR				COLOR_TOMATO
#define			COLOR_TXD_RED         		0xFF0000FF
#define			COLOR_RED					COLOR_TOMATO
#define			COLOR_GRAY					0xAFAFAFAA
#define			COLOR_GRAY_FF				0xAFAFAFFF
#define			COLOR_GRAY_EE				0xAFAFAFEE
#define         COLOR_BLUE                  0x3080F2EE
#define 		COLOR_LIGHTBLUE 			0x00BFFFEE
#define 		COLOR_YELLOW 				0xFFFF00EE
#define 		COLOR_WHITE 				0xFFFFFFEE
#define 		COLOR_GREEN 				0x50A350EE
#define 		COLOR_PAPAYA 				0xE0C490EE
#define 		COLOR_TOMATO				0xD15C47EE
#define 		COLOR_SALMON				0xFF8282EE
#define 		COLOR_PURPLE				0x8080FFEE
#define 		COLOR_DEEP_BLUE 			0x54BDFCEE
#define 		COLOR_ORANGE				0xFF8000EE
#define 		COLOR_LEMON					0xFFFACDEE
#define 		COLOR_YELLOW_GREEN			0x33AA33EE
#define 		COLOR_LIGHT_CYAN			0xC8DDDDEE
#define         COLOR_ME					0xC2A2DAEE
#define			COLOR_LSPD					0x8d8dffEE
#define			COLOR_LSSD					0x194622EE
#define			COLOR_RCSD					0x5c4f20EE
#define			COLOR_LSFD					0x9a2035EE
#define			COLOR_FACTIONCHAT 			0x8080ffEE
#define			COLOR_BLACK					0x000000EE
#define 		COLOR_BROWN 				0xA52A2AAA
#define 		COLOR_ADUTY					COLOR_MSGSERVER
#define			COLOR_INFO					0x9AA79EFF

#define 		DRUG_COLOR_RED 				0xFFFF4515
#define 		DRUG_COLOR_BLUE 			0x1273FF15
#define 		DRUG_COLOR_LIGHTBLUE 		0x00BFFF15
#define 		DRUG_COLOR_GREEN 			0x33AA3315
#define 		DRUG_COLOR_PURPLE			0x8080FF15
#define 		DRUG_COLOR_DEEP_BLUE 		0x54BDFC15
#define 		DRUG_COLOR_ORANGE			0xFF800015
#define 		DRUG_COLOR_YELLOW_GREEN		0x33AA3315
#define 		DRUG_COLOR_LEMON			0xFFFACD15
#define			DRUG_COLOR_PAPAYA 			0xF5DEB315
#define			DRUG_COLOR_WHITE 			0xFFFFFF15


#define			PREMIUM_BRONZE				(1)
#define			PREMIUM_SILVER				(2)
#define			PREMIUM_GOLD				(3)
#define			PREMIUM_OLDGOLD				(4)

#define			FACTIONTYPE_STATE			(1)
#define			FACTIONTYPE_COMMERCIAL		(2)
#define			FACTIONTYPE_GANG			(3)
#define			FACTIONTYPE_MAFIA			(4)
//------------------------------------------------------------------------------
//
//#define         MAX_ITEMS                   90
#define         MAX_PROP					5000
#define         MAX_ITEM_DROP				500
#define         MAX_DAMAGES                 25
#define         MAX_FURNITURE               30000
#define         MAX_PHONE                   5000
#define         MAX_ATTACH                  5
#define         MAX_ENTERS                  1000
#define         MAX_DOORS                   1000
#define         MAX_PURCHASE                250
#define			MAX_FACTIONS				200
#define			MAX_GRAFF					1500
#define 		MAX_INV_SLOTS				15
#define			MAX_911						15
#define			MAX_ATM						150
#define			MAX_CCTV					150
#define			MAX_TICKETS					15
#define			MAX_ELEVATORS				50
#define			MAX_ACHAT					10
#define 		MAX_RADIO_STATION			50
#define 		MAX_MARIJUANA				200
#define			MAX_AD 						15
#define 		MAX_CRAFT					15

#define			FILL_PRICE					(5)
#define			ATM_OBJ						(19324)
#define			CCTV_OBJ					(1886) //(1622)
#define 		SUPER_ADMIN					(7)
//#define			MAX_VEHENTER				50

#define         ADDICTION_MAX_TIME          15000
#define         ADDICTION_HIGHT             80
#define         ADDICTION_LOW               50
//

/*#define         MYSQL_HOST                  "46.105.30.178"
#define         MYSQL_USER                  "root"
#define         MYSQL_PASS                  "gfhjkmgfhjkm111222333"
#define         MYSQL_BASE                  "pacificm_gamebase"*/



#define         MYSQL_DEBUG                 1

#define 		LSPD_FACTION				(1)
#define 		MECHANICS_FACTION			(77)
#define			SASD_FACTION				(74)
#define			LSSD_FACTION				(68)
#define			SADOC_FACTION				(3)
#define			SAHD_FACTION				(2)
#define			LSFD_FACTION				(15)
#define			SAN_FACTION					(25)
#define 		MAYOR_FACTION				(30)

#define 		OBJECTS_STREAM_SETTINGS		(1500)

#define 		DONATEKEY_BRONZEPREMIUM 	(20)
#define 		DONATEKEY_SILVERPREMIUM 	(40)
#define 		DONATEKEY_GOLDPREMIUM		(60)
#define 		DONATEKEY_CHANGENAME		(80)
#define 		DONATEKEY_BOX				(100)
#define 		DONATEKEY_HOURSRESET		(120)
#define 		DONATEKEY_CHANGEUCP			(140)
#define 		DONATEKEY_CHANGESEX			(160)
#define 		DONATEKEY_CHANGEBD			(180)


#define 		FLIMIT_GANG_DRUGS			(100)
#define 		FLIMIT_GANG_GUNS			(8)
#define 		FLIMIT_GANG_BULLS			(1200)
#define 		FLIMIT_MAFIA_DRUGS			(200)
#define 		FLIMIT_MAFIA_GUNS			(15)
#define 		FLIMIT_MAFIA_BULLS			(3000)
			
//------------------------------------------------------------------------------


stock fix_EditDynamicObject(playerid, objid)
{
	printf("fix_EditDynamicObject %d:%d", playerid, objid);
	SetPVarInt(playerid, "EditObject", 1);
	EditDynamicObject(playerid, objid);
	EditDynamicObject(playerid, objid);
	//SetTimerEx("OnEditDynamicObject", 500, false, "dd", playerid, objid);
	return true;
}

#if defined _ALS_EditDynamicObject
	#undef EditDynamicObject
#else
	#define _ALS_EditDynamicObject
#endif
#define EditDynamicObject fix_EditDynamicObject


#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) \
        (((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define IsAduty(%0)         		player_info[%0][aduty]
#define xyz                 		x, y, z
#define floatxyz            		Float:x, Float:y, Float:z
#define isPlayerDriver(%0)			(IsPlayerInAnyVehicle(%0) && GetPlayerState(%0) == PLAYER_STATE_DRIVER)
#define CharacterAndPlayerName(%0)  player_info[%0][login], character_info[%0][name]
#define FreePlayer					TogglePlayerControllable
#define senderitems(%0)         	Items[%0][Name]
#define OwnerInProp(%0)             GetPlayerVirtualWorld(%0) > 200 && character_info[%0][id] == prop_info[GetLocalIdProp(character_info[%0][prop])][owner]
#define DrugEffect(%0)              character_info[playerid][drug_effect][type] == %0
//#define GunTest(%0,%1,%2)           if(gunid == %0 && character_info[playerid][inv][id][item_slot] != %1 || gunid == %0 && character_info[playerid][inv][id][item_slot] != %2) return 1
#define RadioTest(%0)               checkitem(%0, 83) <= -1
#define ErrorSkin                   playerskin+i == 74 || playerskin+i == 70 || playerskin+i == 71 || playerskin+i >= 265 && playerskin+i <= 267 || playerskin+i >= 300 && playerskin+i <= 311 || playerskin+i >= 274 && playerskin+i <= 288
#define         SCM                 SendClientMessage
#define         SPD                 ShowPlayerDialog
#define 		devTest(%0)			GetPVarInt(%0, "_dev_")
#define			IsDuty(%0)			character_info[%0][duty]

#define			AJAIL_POS			-221.059051, 1408.984008, 27.773437
#define			AJAIL_VW			5
#define			AJAIL_INT			18
#define			GoToAjail(%0)		SetPlayerPosEx(%0, AJAIL_POS, AJAIL_VW, AJAIL_INT)
#define 		CMDError(%0)		SCM(%0, COLOR_MSGERROR, ">{FFFFFF} Данной команды не существует!")

#define			Sound_Fail(%0) 		PlayerPlaySound(%0, 1084, 0.0, 0.0, 0.0)
#define			Sound_Succ(%0)		PlayerPlaySound(%0, 1083, 0.0, 0.0, 0.0)

#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_MSGSERVER, ">{FFFFFF} "%1)

#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_MSGERROR, ">{FFFFFF} "%1)
	
#define SendAdminMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_MSGADMIN, ">{FFFFFF} "%1)
	
//------------------------------------------------------------------------------
new LogIn[MAX_PLAYERS];
new cctvoff = 0;

enum call_struct
{
	msg_1[128],
	msg_2[128],
	msg_3[128]
}
new Call911[MAX_PLAYERS][call_struct];


enum Donate_struct
{
	Name[50],
	Price,
	Key,
};
new Donate[][Donate_struct] = 
{
	{"Bronze Premium", 100, DONATEKEY_BRONZEPREMIUM }, 	//0
	{"Silver Premium", 200, DONATEKEY_SILVERPREMIUM }, 	//1
	{"Gold Premium", 500, DONATEKEY_GOLDPREMIUM },		//2
	{"Смена ника", 30, DONATEKEY_CHANGENAME },			//3
	{"Коробка с секретом", 100, DONATEKEY_BOX },			//4
	{"Смена UCP никнейма", 50, DONATEKEY_CHANGEUCP },		//5
	{"Смена пола персонажа", 20, DONATEKEY_CHANGESEX }, //6
	{"Смена даты рождения", 20, DONATEKEY_CHANGEBD }	//7
};


enum Music_struct
{
	name[50],
	URL[128]
}
new Music[][Music_struct] = 
{
	{".977 - Today's Hits", 	"http://7599.live.streamtheworld.com:3690/977_HITS_SC"},
	{"Gay FM",	 				"http://tuner.gayfm.de/;459600429688871stream.nsv"},
	{"Hot 108 Jamz",			"http://sc.hot108.com:4020/;7673965389174535stream.nsv"},
	{".977 - 50s 60s Hits",		"http://7599.live.streamtheworld.com/977_OLDIES_SC"},
	{"The Vibe of Vegas",		"http://icyrelay.181.fm/181-vibe_128k.mp3"},
	{"Los Santos Radio",		"http://aska.ru-hoster.com:2199/tunein/patton.pls"},
	{"Herald Radio",			"http://streaming.shoutcast.com/HeraldRadio"},
	{"Sharp Radio",				"http://s19.myradiostream.com:7498/;stream.mp3"},
	{"Hubu.FM",					"http://yp.shoutcast.com/sbin/tunein-station.m3u?id=1476859"},
	{"1POWER",					"http://powerhitz.powerhitz.com:5040/"},
	{"DEFJAY Radio",			"http://icepool.silvacast.com/DEFJAYcom.mp3"},
	{"1.FM Rock Classics",		"http://sc3b-sjc.1.fm:10060/"},
	{"Flower Power Radio",		"http://flower.serverhostingcenter.com:8433/"},
	{"181.fm 90s Country",		"http://relay.181.fm:8050/"},
	{"WGLT Blues Radio",		"http://wgltradio.ilstu.edu:8000/wgltblues.mp3"},
	{"KIIS 106.5",				"http://icecast.arn.com.au/1065.mp3"},
	{"JOY 94.9",				"http://audio.joy.org.au/proxy/joy949?mp=/live"}
};


enum craft_info_struct
{
	cItem[MAX_CRAFT],
	cCount[MAX_CRAFT]
}
new craft_info[MAX_PLAYERS][craft_info_struct];

enum prison_struct 
{
	id,
	chid_officer,
	name_officer[25],
	Reason[64],
	Days
}
new prison_info[MAX_PLAYERS][prison_struct];

enum ads_struct
{
	owner,
	msg[180]
}
new ads_info[MAX_AD][ads_struct];

enum radio_stations_struct
{
	Name[50],
	URL[100]
}
new radio_station[MAX_RADIO_STATION][radio_stations_struct];
enum HelpInfo_struct {
	CMDTEXT[25],
	CMDDESC[128],
	TYPE
}

enum Tune_struct
{
	component,
	name[25],
	price
}
new Tune_Wheels[][Tune_struct] = {
	{1073, "Shadow", 100},
	{1074, "Mega", 100},
	{1075, "Rimshine", 100},
	{1076, "Wires", 100},
	{1077, "Classic", 100},
	{1078, "Twist", 100},
	{1079, "Cutter", 100},
	{1080, "Switch", 100},
	{1081, "Grove", 100},
	{1082, "Import", 100},
	{1083, "Dollar", 100},
	{1084, "Trance", 100},
	{1085, "Atomic", 100}
};
new AHelpInfo[][HelpInfo_struct] = {
	{"/a", "Чат администраторов", 1},
	{"/ans", "Ответ на вопрос/репорт", 1},
	{"/admins", "Список админов онлайн", 1},
	{"/aduty", "Выход на дежурство", 1},
	
	{"/ac", "Просмотр описания кода античита", 2},
	{"/spawn", "Отправить игрока на спаун", 2},
	{"/mute", "Выдать игроку ООС мут.", 2},
	{"/askoff", "Отключить вопросы(/ask)", 2},
	{"/stats", "Укажите ID игрока и вы увидите его статистику вместо своей", 2},
	{"/carlist", "Укажите ID игрока и вы увидите его автомобили вместо своих", 2},
	{"/gotocar", "Телепорт к автомобилю", 2},
	{"/getherecar", "Телепорт автомобиля к себе", 2},
	{"/slap", "Подкинуть игрока", 2},
	{"/goto", "Телепорт к игроку", 2},
	{"/gethere", "Телепорт игрока к себе", 2},
	{"/hp", "Восполнить себе здоровье", 2},
	{"/aheal", "Исцелить игрока", 2},
	{"/world", "Изменить свой виртуальный мир", 2},
	{"/int", "Изменить свой интерьер", 2},
	{"/serverint", "Телепорт в серверный интерьер", 2},
	{"/kick", "Отключить игрока от сервера", 2},
	{"/afixcar", "Починить автомобиль", 2},
	{"/setfuel", "Установить топливо автомобилю", 2},
	{"/getname", "Узнать логин или имя персонажа по обратному", 2},
	{"/spawncar", "Заспавнить автомобиль", 2},
	{"/sp", "Слежка за игроком", 2},
	{"/spoff", "Выход из слежки", 2},
	{"/ajail", "Посадить в деморган", 2},
	{"/unjail", "Выпустить игрока из деморгана", 2},

	{"/o", "Глобальный чат", 3},
	{"/oic", "Глобальный IC чат", 3},
	{"/dgraf", "Удалить граффити", 3},
	{"/dmdo", "Удалить чужой mdo", 3},
	{"/setskin", "Изменить скин игроку", 3},
	{"/veh", "Создать автомобиль", 3},
	{"/dveh", "Удалить автомобиль (удаляет его полностью из базы данных)", 3},
	{"/ban", "Забанить игрока. Бан на 0 дней - бессрочный бан", 3},
	{"/gopos", "Телепорт по координатам (или установите метку на карте)", 3},
	{"/frisk", "Обыск игрока", 3},

	{"/getitem", "Найти ID предмета по названию/его части", 4},
	{"/ck", "Выдать CharacterKill персонажу(его удаление)", 4},
	{"/unban", "Разбанить игрока по логину UCP", 4},
	{"/editint", "Изменить интерьер имущества", 4},
	{"/maskid", "Узнать имя игрока по ID маски", 4},
	{"/acceptchangename", "Подтвердить изменение имени персонажа", 4},

	{"/adelitem", "Забрать предмет у игрока", 5},
	{"/clearinv", "Очистить инвентарь игроку", 5},
	{"/addprop", "Установить имущество", 5},
	{"/setprop", "Установить имущество (упрощенный стиль)", 5},
	{"/setweather", "Установить погоду", 5},
	{"/vehex", "Расширенное создание автомобиля с указанием владельца(chid)", 5},
	{"/entercreate", "Создать вход", 5},
	{"/factions", "Управление фракциями", 5},
	{"/playerfaction", "Изменить фракцию и ранг игроку", 5},
	{"/createdoor", "Установить дверь фракции", 5},
	{"/addatm", "Создать банкомат", 5},
	{"/editatm", "Создать банкомат", 5},
	{"/cctv", "Создать/удалить CCTV камеру", 5},
	{"/dellallveh", "Удалить все автомобили созданные администраторами", 5},
	{"/clearchat", "Очистить чат", 5},

	{"/createmic", "Создать микрофон.", 6},
	{"/delmic", "Удалить микрофон.", 6},
	{"/updateprop", "Обновить имущество (Не используйте, если не знаете зачем)", 6},
	{"/agiveitem", "Выдать предмет игроку", 6},
	{"/agivemoney", "Выдать деньги", 6},
	{"/setadmin", "Изменить уровень администратора игроку", 6},
	{"/delprop", "Удалить имущество", 6},
	{"/gmx", "Рестарт сервера", 6}
};
new HelpInfo[][HelpInfo_struct] = {
	{"/stats", "Информация о персонаже", 0}, // Основная информация
	{"/report", "Написать жалобу на игрока", 0},
	{"/ask", "Задать вопрос", 0},
	{"/inv", "Открыть инвентарь (Клавиша: Y)", 0},
	{"/pay", "Передать деньги", 0},
	{"/pr", "Меню имущества", 0},
	{"/buyprop", "Приобрести имущество", 0},
	{"/acceptdeath", "Принять смерть", 0},
	{"/id", "Поиск по игрокам", 0},
	{"/pm", "Отправить ООС сообщение игроку", 0},
	{"/settings", "Меню настроек", 0},
	{"/damages", "Просмотр полученного урона игрока", 0},
	{"/heal", "Вылечить игрока с помощью аптечки (альтернатива)", 0},
	{"/cmdsearch", "Поиск по командам", 0},
	{"/donate", "Открыть donate меню", 0},
	{"/changename", "Изменить имя персонажа (донат-услуга)", 0},
	{"/charity", "Слить деньги", 0},
	{"/ad", "Подать объявление", 0},
	{"/sanoff", "Отключить новости/объявления", 0},
	{"/time", "Посмотреть время", 0},
	
	{"/me", "Действия персонажа", 1}, // Команды для отыгровки и чаты
	{"/ame", "Незначительные действия игрока (только над головой)", 1},
	{"/do", "Отыгровка от третьего лица", 1},
	{"/coin", "Подкинуть монетку", 1},
	{"/low", "Говорить тихо", 1},
	{"/w", "Шептать определенному игроку", 1},
	{"/s", "Кричать", 1},
	{"/mdo", "Установить 3D текст на земле", 1},
	{"/description", "Описание персонажа", 1},
	{"/voice", "Описание голоса", 1},
	{"/look", "Посмотреть описание другого персонажа (ПКМ+H)", 1},
	{"/anim", "Список анимаций", 1},
	{"/db", "Звонок в дверь", 1},
	{"/ds", "Крик через дверь", 1},
	{"/b", "OOC чат", 1},
	
	{"/carlist", "Список ваших автомобилей", 2}, // Транспорт
	{"/getcar", "Найти свой автомобиль", 2},
	{"/lock", "Закрыть/открыть автомобиль", 2},
	{"/wi", "Управление стеклами", 2},
	{"/en", "Завести двигатель (NUM2)", 2},
	{"/park", "Припарковать автомобиль", 2},
	{"/checkplate", "Просмотр номеров транспорта (ID как необязательный параметр)", 2},
	{"/boot", "Открыть/закрыть багажник", 2},
	{"/bonnet", "Открыть/закрыть капот", 2},
	{"/fill", "Заправиться на заправке", 2},
	{"/buyfill", "Купить канистру", 2},
	{"/sellcar", "Продать автомобиль", 2},
	{"/carcolor", "Перекрасить автомобиль", 2},
	{"/towing", "Прицепить транспорт (для тягача)", 2},
	{"/gps", "Навигация по городу", 2},
	
	{"/pager", "Отправить сообщение", 3}, // Телефон и пейджер
	{"/pagerinv", "Убрать пейджер", 3},	
	{"/phone", "Открыть меню телефона", 3},
	{"/p", "Взять трубку", 3},
	{"/h", "Положить трубку", 3},
	{"/call", "Позвонить", 3},
	{"/sms", "Отправить сообщение", 3},
	{"/smshistory", "История сообщений", 3},
	{"/contacts", "Список контактов", 3},
	{"/phoneinv", "Убрать телефон", 3},
	{"/gps", "Навигация по городу", 3},
	
	{"/invwep", "Убрать оружие из рук в инвентарь", 4}, // Оружие
	{"/charge", "Зарядить оружие (альтернатива использованию патронов)", 4},
	{"/discharge", "Разрядить оружие", 4},
	{"/give", "Передать оружие из рук", 4},
	
	{"/faction", "Меню фракции", 5}, // Фракции
	{"/invite", "Принять во фракцию", 5},
	{"/uninvite", "Уволить из фракции", 5},
	{"/offuninvite", "Уволить из фракции в оффлайне", 5},
	{"/giverank", "Изменить ранг игроку", 5},
	{"/f", "OOC чат фракции", 5},
	{"/members", "Игроки фракции онлайн", 5},
	{"/offmembers", "Все игроки фракции", 5},
	{"/duty", "Заступить на дежурство(для государственных)", 5},
	{"/po", "Управление аттачами фракции(для государственных)", 5},
	{"/fobj", "Управление объектами фракции(для государственных)", 5},
	
	{"/mdc", "Бортовой компьютер", -1}, // FOR PD
	{"/taser", "Достать тазер", -1},
	{"/rb", "Достать помповый дробовик (только у авто)", -1},
	{"/m", "Использование мегафона", -1},
	{"/ticket", "Выписать штраф игроку", -1},
	{"/cuff", "Надеть наручники", -1},
	{"/uncuff", "Снять наручники", -1},
	{"/incar", "Затащить игрока в автомобиль", -1},
	{"/outcar", "Вытащить игрока из автомобиля", -1},
	{"/frisk", "Обыск игрока", -1},
	{"/take", "Изьять незаконные предметы", -1},
	{"/callsign", "Маркировка", -1},
	{"/su", "Объявить в розыск", -1},
	{"/cctv", "Управление камерами", -1},
	{"/arecord", "Арестрекорды", -1},
	{"/apb", "APB", -1},
	{"/fingerprint", "Снять отпечатки пальцев с предмета на земле", -1},
	{"/lw", "Предупреждение на права", -1},
	{"/sellweaponlic", "Продажа лицензии на оружие", -1},
	
	{"/setradio", "Дать персонажу доступ в эфир", -2}, // FOR SAN
	{"/radio", "Войти/выйти в эфир", -2},
	{"/editad", "Модерировать объявление", -2},
	
	{"/r", "Чат рации по общему слоту", 6}, // Рация
	{"/rr", "Чат рации по определенному слоту", 6},
	{"/slot", "Выбор слота рации", 6},
	{"/channel", "Выбор канала рации", 6},
	{"/rinfo", "Информация о используемой рации", 6}
};

enum Item {
	Alias[25],
	Name[50],
	Model,
	bool:compound,
	Float:TDX,
	Float:TDY,
	Float:TDZ,
	TDZoom
}


new Items[][Item] = {
	{"(Empty)","(Пусто)", 0, true},                       			// 0
	{"First Aid Kit","Аптечка", 19577, true}, 								// 1
	{"Cartridges","Патроны", 2043, true}, 								// 2
	{"Desert Eagle","Desert Eagle", 348, false}, 							// 3
	{"M4A1","M4A1", 356, false}, 									// 4
	{"Shotgun","Shotgun", 349, false}, 								// 5
	{"AK47","AK47", 355, false}, 									// 6
	{"UZI","UZI", 352, false}, 									// 7
	{"TEC-9","TEC-9", 372, false}, 									// 8
	{"MP-5","MP-5", 353, false}, 									// 9
	{"Spawn-off shotgun","Spawn-off shotgun", 350, false},						// 10
	{"SD-Pistol","SD-Pistol", 347, false}, 								// 11
	{"Glock","Glock", 346, false}, 									// 12
	{"Sniper Rifle","Sniper Rifle", 358, false}, 							// 13
	{"Country Rifle","Country Rifle", 357, false}, 							// 14
	{"Phone","Телефон", 18874, false},                 				// 15
	{"SWAT helmet","Шлем SWAT", 19141, true},                 			// 16
	{"Helmet","Шлем", 19200, true},                    				// 17
	{"No","Нет", 0, true},        								// 18
	{"Flak jacket","Бронежилет", 19515, true},      						// 19
	{"Rubber baton","Резиновая дубинка", 334, true},           			// 20
	{"Knife","Нож", 335, true},                         			// 21
	{"Bit","Бита", 336, true},                        			// 22
	{"Shovel","Лопата", 337, true},                      			// 23
	{"Cue","Кий", 338, true},                      				// 24
	{"Katana","Катана", 339, true},                      			// 25
	{"MDMA","МДМА", 1579, true},                       			// 26
	{"Cocaine","Кокаин", 1575, true},                     			// 27
	{"Marijuana","Марихуана", 1578, true},                  			// 28
	{"Crack","Крэк", 1577, true},                       			// 29
	{"Methamphetamine","Метамфетамин", 1580, true},               			// 30
	{"Heroin","Героин", 1576, true},                     			// 31
	{"Mescaline","Мескалин", 1577, true},                   			// 32
	{"LSD","ЛСД", 1579, true},                        			// 33
	{"Desert Eagle","Desert Eagle", 348, true}, 							// 34
	{"M4A1","M4A1", 356, true}, 									// 35
	{"Shotgun","Shotgun", 349, true}, 								// 36
	{"AK47","AK47", 355, true}, 									// 37
	{"UZI","UZI", 352, true}, 									// 38
	{"TEC-9","TEC-9", 372, true}, 									// 39
	{"MP-5","MP-5", 353, true}, 									// 40
	{"Spawn-off shotgun","Spawn-off shotgun", 350, true},						// 41
	{"SD-Pistol","SD-Pistol", 347, true}, 								// 42
	{"Glock","Glock", 346, true}, 									// 43
	{"Sniper Rifle","Sniper Rifle", 358, true}, 							// 44
	{"Country Rifle","Country Rifle", 357, true}, 							// 45
	{"Skin","Скин", 2386, false},                                  // 46
	{"Gold watches","Золотые часы", 19039, true},                          // 47
	{"Bag with things","Сумка с вещами", 11745, true},	                    // 48
	{"Backpack","Рюкзак", 371, true},                      	 		// 49
	{"Large backpack","Большой рюкзак", 1310, true},                        // 50
	{"Case","Кейс", 1210, true},					                  // 51
	{"Regular glasses","Обычные очки ", 19015, true},                         // 52
	{"Aviators blue","Авиаторы синие", 19023, true},             			// 53
	{"Aviators purple","Авиаторы фиолетовые", 19024, true},        			// 54
	{"Aviators pink","Авиаторы розовые", 19025, true},           			// 55
	{"Red Aviators","Авиаторы красные", 19026, true},           			// 56
	{"Aviators orange","Авиаторы оранжевые", 19027, true},         			// 57
	{"Aviators yellow","Авиаторы желтые", 19027, true},            			// 58
	{"White Scarf","Белый шарф", 19469, true},                            // 59
	{"Black Hat 1","Черная шапка 1", 18953, true},                        // 60
	{"Beige hat","Бежевая шапка", 18954, true},                         // 61
	{"High black hat","Высокая черная шапка", 19554, true},                  // 62
	{"Black Hat 2","Черная шапка 2", 19069, true},             			// 63
	{"Balaclava","Балаклава", 19801, true},                             // 64
	{"Black cap","Кепка чёрная", 18941, true},         					// 65
	{"Beige cap","Кепка бежевая", 18942, true},        					// 66
	{"Cap green","Кепка зеленая", 18943, true},        					// 67
	{"Helmet (blue)","Шлем (синий) ", 18976, true}, 						// 68
	{"Helmet (red)","Шлем (красный)", 18977, true},           				// 69
	{"Helmet (white)","Шлем (белый)", 18978, true},             				// 70
	{"Helmet (Pink)","Шлем (розовый) ", 18979, true},           			// 71
	{"Bandana (blue)","Бандана (синяя) ", 18891, true},            			// 72
	{"Bandana (red)","Бандана (красная) ", 18892, true},          			// 73
	{"Bandana (black)","Бандана (черная) ", 18896, true},           			// 74
	{"Bandana (blue)","Бандана (голубая) ", 18897, true},          			// 75
	{"Bandana (pink)","Бандана (розовая) ", 18898, true},          			// 76
	{"Bandana (green)","Бандана (зеленая) ", 18899, true},          			// 77
	{"Bandana (black)","Бандана (черная) ", 18912, true},             		// 78
	{"Bandana (green)","Бандана (зеленая) ", 18913, true},            		// 79
	{"Bandana (pink)","Бандана (розовая) ", 18915, true},            		// 80
	{"Bandana (yellow)","Бандана (желтая) ", 18916, true},             		// 81
	{"Bandana (white)","Бандана (белая) ", 18919, true},               		// 82
	{"Radio","Рация", 19942, true},                                 // 83
	{"Balonchik","Балончик", 365, false},								// 84
	{"Empty balonchik","Пустой балончик", 365, true},							// 85
	{"Police badge # 1","Полицейский жетон №1", 0, true},						// 86
	{"Police badge number 2","Полицейский жетон №2", 0, true},						// 87
	{"Police badge","Полицейский бейдж", 0, true},							// 88
	{"Passepartout","Отмычка", 0, true},									// 89
	{"(*) FBI inscription","(*) Надпись FBI", 19777, true},						// 90
	{"(*) Holster","(*) Кобура", 19773, true},							// 91
	{"(*) Handcuffs","(*) Наручники", 11750, true},							// 92
	{"(*) Flashlight","(*) Фонарик", 18641, true},							// 93
	{"(*) LTSU for weapons","(*) ЛЦУ на оружие", 18643, true},						// 94
	{"(*) Shield","(*) Щит", 18637, true},								// 95
	{"(*) FBI inscription","(*) Надпись FBI", 19777, true},						// 96
	{"(*) Helmet of moto-unit","(*) Шлем мото-юнита", 19200},							// 97
	{"(*) Traffic unit vest","(*) Жилет траффик-юнита", 19904, true},				// 98
	{"(*) Cap","(*) Фуражка", 19520, true},							// 99
	{"(*) Cap 2","(*) Фуражка 2", 19521, true},							// 100
	{"(*) Gray cap","(*) Кепка серая", 18636, true},						// 101
	{"(*) Black cap","(*) Кепка чёрная", 19161, true},						// 102
	{"(*) Cap blue","(*) Кепка синяя", 19162, true},						// 103
	{"(*) Cowboy hat","(*) Ковбойская шляпа", 18962, true},					// 104
	{"(*) Police Hat","(*) Шляпа Police", 19099, true},						// 105
	{"(*) Hat of Police 2","(*) Шляпа Police 2", 19100, true},					// 106
	{"(*) Black glasses","(*) Очки чёрные", 19138, true},						// 107
	{"(*) Red glasses","(*) Очки красные", 19139, true},						// 108
	{"(*) Blue glasses","(*) Очки синие", 19140, true},						// 109
	{"(*) Bag with things","(*) Сумка с вещами", 11745, true},					// 110
	{"(*) Bag BLS","(*) Сумка BLS", 11738, true},							// 111
	{"Mask","Маска", 0, true},										// 112
	{"Full canister","Полная канистра", 19621, true},						// 113
	{"Empty canister","Пустая канистра", 19621, true},						// 114
	{"Chainsaw","Бензопила", 341, true},								// 115
	{"Fire extinguisher","Огнетушитель", 366, true},							// 116
	{"Scrap","Лом", 18634, true},									// 117
	{"Shovel","Лопата", 337, true},									// 118
	{"Katana","Катана", 339, true},									// 119
	{"(*) Respirator","(*) Респиратор", 19472, true},						// 120
	{"(*) Helmet 1","(*) Каска 1", 19330, true},							// 121
	{"(*) Helmet 2","(*) Каска 2", 19331, true},							// 122
	{"(*) A hammer","(*) Молоток", 18634, true},							// 123
	{"(*) Screwdriver","(*) Отвертка", 18644, true},							// 124
	{"(*) The key","(*) Ключ", 18663, true},								// 125
	{"(*) A bag","(*) Сумка", 11745, true},								// 126
	{"(*) Gas supply 1","(*) Газовый балон 1", 1008, true},					// 127
	{"(*) Gas bottle 2","(*) Газовый балон 2", 1009, true},					// 128
	{"(*) Gas bottle 3","(*) Газовый балон 3", 1010, true},					// 129
	{"Whiskey","Виски", 19823, true},									// 130
	{"Beer","Пиво", 1486, true},									// 131
	{"Wine","Вино", 1669, true},									// 132
	{"Champagne","Шампанское", 19822, true},							// 133
	{"Cigarettes","Сигареты", 19897, true},								// 134
	{"Soda","Газировка", 1546, true},								// 135
	{"Glass of water","Стакан воды", 1546, true},							// 136
	{"Coffee","Кофе", 19835, true},									// 137
	{"Pizza","Пицца", 19580, true},									// 138
	{"Burger","Бургер", 2768, true},									// 139
	{"Roll","Ролл", 2769, true},									// 140
	{"Salad","Салат", 2355, true},									// 141
	{"Boombox","Бумбокс", 2226, true},								// 142
	{"(*) Counter","(*) Жетон", 19774, true},								// 143
	{"(*) Badge 2","(*) Жетон 2", 19775, true},							// 144
	{"(*) Body armor","(*) Бронежилет", 19142, true},						// 145
	{"(*) Body armor 2","(*) Бронежилет 2", 19515, true},						// 146
	{"(*) Body armor 3","(*) Бронежилет 3", 1242, true},						// 147
	{"House key","Ключ от дома", 0, false},								// 148
	{"Car key","Ключ от автомобиля", 0, false},						// 149
	{"Seeds of marijuana","Семена марихуаны", 0, true},							// 150
	{"(OOC) Box with a secret","(OOC) Коробка с секретом", 0, true}, 					// 151
	{"(*) The flag of the USA","(*) Флаг США", 11245, true},							// 152
	{"Checker Taxi","Шашка Такси", 19308, true},							// 153
	{"(*) Badge Detective","(*) Бейдж детектива", 19776, true},					// 154
	{"(*) Walkie-talkie","(*) Рация", 19942, true},								// 155
	{"(*) Cudgel","(*) Дубинка", 334, true},								// 156
	{"(*) Helmet 1","(*) Шлем 1", 19141, true},							// 157
	{"(*) Helmet 2","(*) Шлем 2", 19514, true},							// 158
	{"Christmas hat","Рождественская шапка", 19064, true},					// 159
	{"Photo camera","Фотоапарат", 367, false},								// 160
	{"Red glasses","Очки красные",     19006, true},						// 161
	{"Glasses, orange","Очки оранжевые",     19007, true},              		// 162
	{"Glasses green","Очки зеленые", 19008, true},							// 163
	{"Blue Glasses","Очки голубые",    19009, true},						// 164
	{"Glasses pink","Очки розовые",    19010, true},
	{"Glasses yellow","Очки желтые",    19011, true},
	{"Brown glasses","Очки коричневые",    19012, true},
	{"Glasses","Очки",    19013, true},
	{"Glasses","Очки",    19014, true},
	{"Glasses transparent","Очки прозрачные",   19015, true},
	{"Aviators X-Ray","Авиаторы X-Ray",   19016, true},
	{"Glasses","Очки",   19017, true},
	{"Glasses","Очки",   19018, true},
	{"Glasses","Очки",   19019, true},
	{"Glasses","Очки",   19020, true},
	{"Glasses","Очки",   19021, true},
	{"Aviators of gold","Авиаторы золотые",   19022, true},  
	{"Aviators blue","Авиаторы синие",   19023, true},
	{"Aviators purple","Авиаторы фиолетовые",   19024, true},
	{"Aviators pink","Авиаторы розовые",   19025, true},
	{"Red Aviators","Авиаторы красные",   19026, true},
	{"Aviators orange","Авиаторы оранжевые",   19027, true},
	{"Aviators yellow","Авиаторы желтые",   19028, true},
	{"Aviators green","Авиаторы зеленые",   19029, true},
	{"Aviators are transparent","Авиаторы прозрачные",   19030, true},
	{"Glasses","Очки",   19031, true},
	{"Glasses","Очки",   19032, true},
	{"Black Aviators","Авиаторы черные",   19033, true},
	{"Glasses","Очки",   19034, true},
	{"Aviators with patterns","Авиаторы с узорами",   19035, true},
	{"Eye patch","Повязка на глаз",    19085, true},
	{"Police glasses black","Полицейские очки черные",  19138, true},
	{"Police glasses red","Полицейские очки красные",  19139, true},
	{"Police glasses blue","Полицейские очки синие",  19140, true},
	{"Police Cap","Полицейская кепка",18636, true},
	{"Black hat","Черная шляпа", 18639, true},
	{"Black beret","Черный берет", 18921, true},
	{"Red beret","Красный берет",   18922, true},
	{"Blue beret","Синий берет",       18923, true},
	{"Camouflage Beret","Камуфляжный берет",18924, true},
	{"Raspberry Beret","Малиновый берет",   18925, true},
	{"Camouflage cap","Камуфляжная кепка", 18926, true},
	{"Cap blue with patterns","Кепка синяя с узорами", 18927, true},
	{"Purple cap with patterns","Кепка фиолетовая с узорами", 18928, true},
	{"Cap green with patterns","Кепка зеленая с узорами", 18929, true},
	{"Red cap with patterns","Кепка красная с узорами", 18930, true},
	{"Cap with zippers","Кепка с узорами молнии", 18931, true},
	{"Orange cap with patterns","Кепка оранжевая с узорами",18932, true},
	{"Gray cap with patterns","Кепка серая с узорами",18933, true},
	{"Cap Red","Кепка красная",   18934, true},
	{"Yellow cap","Кепка желтая", 18935, true},
	{"Cap","Кепка",          18939, true},
	{"Blue cap with patterns","Кепка голубая с узорами",   18940, true},
	{"Black cap","Кепка черная",     18941, true},
	{"Gray cap","Кепка серая",       18942, true},
	{"Cap green","Кепка зеленая",   18943, true},
	{"Red hat with patterns","Шляпа красная с узорами", 18944, true},
	{"Green hat with patterns","Шляпа зеленая с узорами",18945, true},
	{"Gray hat","Шляпа серая",       18946, true},
	{"Black hat","Шляпа черная",     18947, true},
	{"Turquoise hat","Шляпа бирюзовая",       18948, true},
	{"The hat is green","Шляпа зеленая",       18949, true},
	{"The hat is red","Шляпа красная",       18950, true},
	{"Light hat","Шляпа светлая",       18951, true},
	{"Black cap","Шапка черная",     18953, true},
	{"Marsh hat","Шапка болотная",     18954, true},
	{"Orange cap with patterns","Кепка оранжевая с узорами",     18955, true},
	{"Cap black with patterns","Кепка черная с узорами",       18956, true},
	{"Cap blue with patterns","Кепка синяя с узорами ",        18957, true},
	{"Golden cap with patterns","Кепка золотая с узорами",     18958, true},
	{"Camouflaged cap","Кепка камуфляжная",       18959, true},
	{"Cap with patterns","Кепка с узорами",        18960, true},
	{"Cap \"TRUCK\"","Кепка \"TRUCK\"",        18961, true},
	{"Dark Hat","Шляпа темная",     18962, true},
	{"Black cap","Шапка черная",     18964, true},
	{"Hat with patterns","Шапка с узорами",        18965, true},
	{"Hat with patterns","Шапка с узорами",        18966, true},
	{"Panama Black","Панама черная",           18967, true},
	{"Panama checkered","Панама клетчатая",         18968, true},
	{"Panama Orange","Панама оранжевая",         18969, true},
	{"Tiger's Hat","Шляпа тигровая",     18970, true},
	{"A checkered hat","Шляпа клетчатая",       18971, true},
	{"Hat spotted","Шляпа пятнистая",       18972, true},
	{"Hat of camouflage","Шляпа камуфляжная",       18973, true},
	{"Red cap","Шапка красная",       19067, true},
	{"Gray cap with patterns","Шапка серая с узорами",     19068, true},
	{"Black cap","Шапка черная",     19069, true},
	{"Gray hat","Шляпа серая",       19095, true},
	{"Black hat","Шляпа черная",     19096, true},
	{"The hat is red","Шляпа красная",       19097, true},
	{"Brown Hat","Шляпа коричневая",     19098, true},
	{"Black police hat","Шляпа полицейская черная",      19099, true},
	{"Brown police hat","Шляпа полицейская коричневая",      19100, true},
	{"Black police cap","Кепка полицейская черная",      19161, true},
	{"Cap police blue","Кепка полицейская синяя",        19162, true},
	{"Hat white","Шляпа белая",       19488, true},
	{"Hat thatched","Шляпа соломенная",     19553, true},
	{"Black cap","Шапка черная",         19554, true},
	{"Cap with pizza","Кепка с пиццей",      19558, true},
	{"Bandana Black","Бандана черная",     18891, true},
	{"Bandana red","Бандана красная",       18892, true},
	{"Bandana red","Бандана красная с узорами",     18893, true},
	{"Bandana Orange","Бандана оранжевая",       18894, true},
	{"Bandana Black 1","Бандана черная с черепами",     18895, true},
	{"Bandana Black 2","Бандана черная с узорами",       18896, true},
	{"Bandana blue","Бандана синяя с узорами",     18897, true},
	{"Bandana green","Бандана зеленая с узорами",     18898, true},
	{"Bandana crimson","Бандана малиновая",       18899, true},
	{"Bandana with Patterns","Бандана с узорами",        18900, true},
	{"Bandana brown","Бандана коричневая",     18901, true},
	{"Bandana sand","Бандана песчанная",       18902, true},
	{"Bandana coffee","Бандана кофейная",     18903, true},
	{"Bandana with Patterns","Бандана с узорами",        18904, true},
	{"Bandana yellow","Бандана желтая",     18905, true},
	{"Bandana Orange","Бандана оранжевая",       18906, true},
	{"Bandana with","Бандана с узорами",        18907, true},
	{"Bandana blue","Бандана синяя с узорами",     18908, true},
	{"Bandana Gray","Бандана серая",       18909, true},
	{"Bandana red","Бандана красная",       18910, true},
	{"Bandana Black 3","Бандана черная c черепами",          18911, true},
	{"Bandana Black 4","Бандана черная",         18912, true},
	{"Bandana green","Бандана зеленая",           18913, true},
	{"Bandana Camouflage","Бандана камуфляжная",           18914, true},
	{"Bandana crimson","Бандана малиновая",           18915, true},
	{"Bandana with Patterns","Бандана с узорами",            18916, true},
	{"Bandana Blue","Бандана синяя",           18917, true},
	{"Bandana dark green","Бандана тёмно-зелёная",            18918, true},
	{"Bandana Gray","Бандана серая",           18919, true},
	{"Bandana with Patterns","Бандана с узорами",            18920, true},
	{"Lemon clock","Часы лимонные",        19039, true},
	{"Gold watches","Часы золотые",        19040, true},
	{"Bronze watches","Часы бронзовые",        19041, true},
	{"Clock yellow","Часы желтые",        19042, true},
	{"Silver watches","Часы серебрянные",        19043, true},
	{"Raspberry watches","Часы малиновые",        19044, true},
	{"Red watches","Часы красные",        19045, true},
	{"Hours green","Часы зеленые",        19046, true},
	{"Watches, purple","Часы фиолетовые",        19047, true},
	{"Watch 1","Часы с узорами молнии",        19048, true},
	{"Clock 2","Часы фиолетовые с узорами",        19049, true},
	{"Clock 3","Часы голубые с узорами",        19050, true},
	{"Clock 4","Часы оранжевые с узорами",        19051, true},
	{"Clock 5","Часы розовые с узорами",        19052, true},
	{"Camo Watch","Часы камуфляжные",        19053, true},
	{"Helmet (blue)","Шлем (синий) ", 18976, true},
	{"Helmet (red)","Шлем (красный)", 18977, true},         			
	{"Helmet (white)","Шлем (белый)", 18978, true},        			
	{"Helmet (Pink)","Шлем (розовый)", 18979, true},
	{"Wig","Парик", 18640, true},
	{"Helmet (Gray)","Шлем (серый)", 18936, true},
	{"Helmet (Black)","Шлем (черный)", 18937, true},
	{"Case","Кейс", 1210, true},
	{"Suitcase","Чемодан", 19624, true},
	{"Backpack","Рюкзак", 1310, true},
	{"Large backpack","Большой рюкзак", 371, true},
	{"Large Gray Bag","Большая сумка серая", 2919, true},
	{"Large black bag","Большая сумка черная", 11745, true},
	{"Traveler's Backpack","Рюкзак путешественника", 19559, true},
	{"Small backpack","Рюкзак малый", 3026, true},
	{"Basketball","Баскетбольный мяч", 2114, true},
	{"Skate","Скейт", 19878, true},
	{"Wig","Парик", 19077, true},
	{"Wig Afro","Парик афро", 18975, true},
	{"Antennae","Усики", 19351, true},
	{"Skipping panties","Пропуск в трусики", 19350, true},
	{"Boxing gloves (left)","Боксерская перчата (левая)", 19555, true},
	{"Boxing gloves (right)","Боксерская перчата (правая)", 19556, true},
	{"Boxing helmet","Боксерский шлем", 18952, true},
	{"Wig","Парик", 19136, true},
	{"Wig","Парик", 19136, true},
	{"Headphones yellow","Наушники желтые", 19421, true},
	{"Headphones black","Наушники черные", 19422, true},
	{"Headphones red","Наушники красные", 19423, true},
	{"Headphones gray","Наушники серые", 19424, true},
	{"Purple Friend","Фиолетовый друг", 321, true},  //335
	{"Dildo","Фаллоимитатор", 322, true}, //336
	{"Vibrator","Вибратор", 323, true}, //337
	{"Silver Vibrator","Серебряный Вибратор", 324, true}, //338
	{"Bas-guitar","Бас-гитара", 19317, true},
	{"Electric guitar","Электро-гитара", 19318, true},	//340
	{"pager", "Пейджер", 18875, false}, //341
	{"Silencer", "Глушитель", 347, false}	// 342
};


new MAX_ITEMS = sizeof(Items);


enum ticket_struct
{
	tId,
	tSumm,
	tReason[32],
	tDate[24]
}
new ticket_info[MAX_PLAYERS][MAX_TICKETS][ticket_struct];

enum inv_struct {
	id[MAX_INV_SLOTS],
	count[MAX_INV_SLOTS]
}

/*enum arecord_struct
{
	arecordID,
	arecordText[32],
	arecordDate[18]
}
new arecord_info[MAX_PLAYERS][arecord_struct];*/

enum achat_stuct
{
	Playerid,
	Code,
	bool:New
}
new achat_info[MAX_ACHAT][achat_stuct];
new Text:ACHAT[MAX_ACHAT];
enum graff_struct 
{
	gID,
	gText[32],
	gFont[32],
	gFontsize,
	gColor[8],
	gOwner,
	gObj,
	Float:gX,
	Float:gY,
	Float:gZ,
	Float:gRX,
	Float:gRY,
	Float:gRZ
}
new graff_info[MAX_GRAFF][graff_struct];


enum cctv_struct
{
	id,
	description[24],
	Float:posX,
	Float:posY,
	Float:posZ,
	Float:posRX,
	Float:posRY,
	Float:posRZ,
	VW, 
	Interior,
	aObj,
	Text3D:a3d,
	destroyed,
	timeout
}
new cctv_info[MAX_CCTV][cctv_struct];
enum atm_struct
{
	id, 
	Float:posX,
	Float:posY,
	Float:posZ,
	Float:posRX,
	Float:posRY,
	Float:posRZ,
	VW,
	aObj,
	Text3D:a3d
}
new atm_info[MAX_ATM][atm_struct];

enum faction_struct
{
	Name[25],
	Leader,
	Type,
	FactionFreeze,
	invite_rank,
	uninvite_rank,
	giverank_rank,
	drugs,
	guns,
	bank,
	bulls
}


new factions[MAX_FACTIONS][faction_struct];
new faction_ranks[MAX_FACTIONS][21][33];

enum purchase_struct
{
	iditem,
	count,
}
new purchase[MAX_FACTIONS][MAX_PURCHASE][purchase_struct];
new purchase_price[MAX_FACTIONS];
enum door_stuct
{
	Model,
	Float:posX,
	Float:posY,
	Float:posZ,
	Float:posRX,
	Float:posRY,
	Float:posRZ,
	Float:posXS,
	Float:posYS,
	Float:posZS,
	Float:posRXS,
	Float:posRYS,
	Float:posRZS,
	intid,
	vworld,
	factionid,
	bool:open
}

new door[MAX_DOORS][door_stuct];

enum list_store_struct
{
	iditem,
	price
}
new list_store[][list_store_struct] = {
	{1, 100},
	{23, 70},
	{24, 70},
	{15, 200},
	{341, 150},
	{83, 100},
	{84, 100},
	{112, 500},
	{89, 300},
	{134, 150},
	{142, 200},
	{153, 500},
	{159, 50},
	{160, 150}

};

new list_club[][list_store_struct] = {
	{130, 120},
	{131, 40},
	{132, 100},
	{133, 100},
	{135, 50},
	{136, 10}
};

new list_bar[][list_store_struct] = {
	{130, 120},
	{131, 40},
	{132, 100},
	{133, 100},
	{135, 50},
	{136, 10}
};

new list_eatery[][list_store_struct] = {
	{135, 50},
	{136, 10},
	{138, 80},
	{139, 50},
	{140, 50},
	{141, 50}
};

enum list_deal_struct
{
	iditem,
	price
}
new list_deal[][list_deal_struct] = {
	{2, 15},
	{34, 2500},
	{36, 3000},
	{37, 5000},
	{38, 3000},
	{39, 3000},
	{40, 4500},
	{41, 3000},
	{42, 2000},
	{43, 2000},
	{44, 12500},
	{45, 7000},
	
	{26, 80},
	{27, 180},
	{28, 40},
	{29, 70},
	{30, 100},
	{31, 100},
	{32, 70},
	{33, 100}
};



enum enter_struct
{
	id,
	Float:posX,
	Float:posY,
	Float:posZ,
	vworld,
	intid,
	Float:posXE,
	Float:posYE,
	Float:posZE,
	vworldE,
	intidE,
	Text[24],
	Text3D:id3dtext,
	Text3D:id3dtexte
}

new enter_info[MAX_ENTERS][enter_struct];

new Text3D:MDO[MAX_PLAYERS];
enum contacts_struct
{
	Name[25],
	Phone
}
new contacts_info[MAX_PLAYERS][12][contacts_struct];

enum attach_struct
{
	iditem,
	bone,
	Float:posX,
	Float:posY,
	Float:posZ,
	Float:posRX,
	Float:posRY,
	Float:posRZ,
	Float:posSX,
	Float:posSY,
	Float:posSZ
}
new attachStatus[MAX_PLAYERS];
new attach[MAX_PLAYERS][MAX_ATTACH][attach_struct];

enum history_struct
{
	number,
	bool:type,
	duration,
	date[16]
}
enum sms_struct
{
	number,
	bool:type,
	msg[128],
	date[16]
}
/*enum phone_struct
{
	id,
	number,
	history[history_struct],
	last_sms[sms_struct]
}
new phone_info[MAX_PHONE][phone_struct][];*/

enum veh_struct
{
	id,
	owner,
	vcolor1, vcolor2,
	bool:lock,
	bool:engine,
	bool:lights,
	bool:window_1,
	bool:window_2,
	bool:window_3,
	bool:window_4,
	bool:boonet,
	bool:boot,
	bool:alarm,
	alarm_timer,
	Float:fuel,
	Float:posX, Float:posY, Float:posZ, Float:vAngle,
	timerid, destroy_time,
	inv[inv_struct],
	VW,
	number[11],
	Text3D:callsign,
	Float:filling,
	alarm_type,
	lock_type,
	gunrack_1_gun,
	gunrack_2_gun,
	gunrack_3_gun,
	gunrack_2_ammo,
	gunrack_3_ammo,
	RadioURL,
	taxi,
	siren,
	wheels,
	towing,
	Radio,
	Station,
	takeweapons
}
new veh_info[MAX_VEHICLES][veh_struct];
enum item_drop
{
 	id,
 	myitem,
 	item_count,
	Float:posX,
	Float:posY,
	Float:posZ,
	Float:posRX,
	Float:posRY,
	Float:posRZ,
	vworld,
	inter,
	charactername[25]
}
new items_drop[MAX_ITEM_DROP][item_drop];

enum struct_911 
{
	id,
	owner[25],
	time_911[6],
	text_911[128],
	Float:posX,
	Float:posY, 
	Float:posZ,
	Zone[32]
}

new list_911[MAX_911+1][struct_911];
new count_911;

enum furniture_struct
{
	id,
	houseid,
	model,
	Float:cordX,
	Float:cordY,
	Float:cordZ,
 	Float:cordRX,
	Float:cordRY,
	Float:cordRZ
}
new furniture[MAX_FURNITURE][furniture_struct];

new property[][48] = {
	"Дом",											// 0
	"24/7",											// 1
	"Магазин одежды",								// 2
	"Бар",											// 3
	"Клуб",											// 4
	"Закусочная",									// 5
	"Помещение",									// 6
	"Подъезд"										// 7
};

enum prop_struct
{
	id,
	owner,
	Float:posX,
	Float:posY,
	Float:posZ,
	price,
	lock,
	serverint,
	vworld,
	intid,
	money,
	type,
	Text3D:id3dtext,
	PropZone,
	inv[inv_struct],
	Days,
	Name[32],
	neighbor[6],
	enter_price
}
new prop_info[MAX_PROP][prop_struct];
enum player
{
	loged,
	fail_input_password,
	id,
	login[24],
	admin,
	bool:aduty,
	inv_selected,
	perm,
	vip,
	vip_time,
	vkid,
	donate,
	changename,
	settings[3], // 0 - районы, 1 - PM, 2 - инвентарь
	mute,
	atime,
	passchanged
}
new player_info[MAX_PLAYERS][player];

enum damages_struct
{
	part[MAX_DAMAGES],
	gun_id[MAX_DAMAGES],
	hour_damages[MAX_DAMAGES],
	minute_damages[MAX_DAMAGES],
	Float:damage_hp[MAX_DAMAGES],
}
enum drug_effect_struct {
	type,
	time_effect
}
enum character
{
    bool:kicked,
	id,
	skin,
	name[22],
	money,
	newlife, 
	hospital,
	bank,
	faction,
	rank,
	Float:posX,
	Float:posY,
	Float:posZ,
	VW,
	Interior,
	inv[inv_struct],
	gun,
	ammo,
	silencer,
	wound,
	drunk_time,
 	accept_death,
 	accept_death_timer,
 	prop,
 	editobject,
 	type_editobj,
 	AFK,
 	damages[damages_struct],
 	phoneslot,
 	pager,
 	addiction,
 	time_addiction,
 	drug_effect[drug_effect_struct],
 	payday,
 	hours_today,
 	lvl,
 	r_channel,
 	r_slot,
	driveLic,
	driveLicWarn,
	gunLic,
	flyLic,
	description[256],
	duty,
	duty_gun_1,
	duty_gun_2,
	duty_gun_special,
	duty_ammo_2,
	duty_gun_3,
	duty_ammo_3,
	duty_skin,
	su,
	su_reason[32],
	ajail_time,
	jail_time,
	birthDate[18],
	voice[32],
	sex,
	Float:Health,
	spawned,
	lock
}

enum fobj_struct
{
	Model[10],
	fObj[10],
	Text3D:f3d[10]
}
new fobj_info[MAX_PLAYERS][fobj_struct];


enum flood_struct
{
	ooc,
	report,
	mute
}
new flood[MAX_PLAYERS][flood_struct];

enum elevator_struct
{
	elevatorid,
	desc[32],
	Float:posX,
	Float:posY,
	Float:posZ,
	VW,
	Interior
}
new elevator_info[MAX_ELEVATORS][elevator_struct];

new weatherid = 1;
new PlayerText:TDEditor_PTD[MAX_PLAYERS][10];
new PlayerText:Textdraw[MAX_PLAYERS][4];
new PlayerText:Areas[MAX_PLAYERS];
new PlayerText:Loading[MAX_PLAYERS];
new PlayerText:FullMonitor[MAX_PLAYERS];
new PlayerText:DrugEffect[MAX_PLAYERS][5];
new Menu:buy_skin_menu;
new dbHandle;
new dialog_data[MAX_PLAYERS][10];
new restart = 60;
new ASP, CSP;
new character_info[MAX_PLAYERS][character];
new select_character_id[MAX_PLAYERS][3];
//new select_character_name[MAX_PLAYERS][3][25];
new hour,minute,second, year, month, day;
new AuthTimeoutTimer[MAX_PLAYERS];
new Text:Logo[2];
new Text:restartingtd[3];