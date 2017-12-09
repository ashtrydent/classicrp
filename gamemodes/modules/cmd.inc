CMD:oedit(playerid, params[])
{
    if(IsAdmin(playerid, 6)) 
		return 1;
		
	SelectObject(playerid);
 	return 1;
}
CMD:sellweaponlic(playerid, params[])
{
	if(!IsCop(playerid))
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	if(!IsDuty(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"ud", params[0], params[1])) SyntaxCMD(playerid, "/sellweaponlic [ID/Часть имени] [Цена]");
	if(!IsPlayerLoged(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн."); 
	new Float:x, Float:y, Float:z;
	GetPlayerPos(params[0], x, y, z);
	if(!IsPlayerInRangeOfPoint(playerid, 5.0, x, y, z))
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");  
	if(params[1] < 2500 || params[1] > 10000) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверная цена! (от 2,500$ до 10,0000$)"); 	
	if(character_info[params[0]][money] < params[1]) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У игрока недостаточно средств!"); 
	out_id = params[0];
	out_id_i = playerid;
	out_price = params[1];
	new str[256];
	format(str, sizeof(str), "{FFFFFF}%s предложил вам приобрести лицензию на оружие.\nЦена: %d$", sendername(playerid), params[1]);
	ShowPlayerDialog(params[0], 156, DIALOG_STYLE_MSGBOX, "Лицензия на оружие", str, "Согласен", "Отмена"); 
	return 1;
}
CMD:pager(playerid, params[]) {
	new pagernumber, text[125];
	if(sscanf(params,"ds[125]", pagernumber, text)) 
		return SyntaxCMD(playerid, "/pager [пейджер] [текст]");
	if(character_info[playerid][pager] == -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет пейджера в слоте!");
	if(pagernumber == -1) return 1;

	foreach(new p : Player) {
		if(character_info[p][pager] == pagernumber) {
			SendClientMessageEx(p, COLOR_YELLOW, "[PAGER]: %s (Отправитель: %d)", character_info[playerid][pager], text);
			SendClientMessageEx(playerid, COLOR_YELLOW, "[PAGER]: %s (Получатель: %d)", character_info[p][pager], text);
			SetPlayerChatBubble(p,"получил оповещение на пейджер",COLOR_ME,30.0,5000);
			
			return 1;
		}
	}

	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверный пейджер!");
	return 1;
}

CMD:sms(playerid, params[])
{
	new number_unformat[25];
    if(sscanf(params,"s[25]s[125]", number_unformat, params[1])) 
		return SyntaxCMD(playerid, "/sms [номер / имя контакта] [текст]");
    
	if(character_info[playerid][phoneslot] == -1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте!");
    
	new number_rec = search_phonenumber(playerid, number_unformat);
    if(number_rec < 1) 
		number_rec = strval(number_unformat);
    
	foreach(new p : Player)
    {
        if(!IsPlayerConnected(p)) 
			return 1;
		
		if(character_info[p][phoneslot] == number_rec)
		{
			new str[125], contacts_slot_sender = search_phonename(playerid, character_info[p][phoneslot]), contacts_slot_rec = search_phonename(p, character_info[playerid][phoneslot]);

			if(contacts_slot_rec == -1)	format(str, sizeof(str), "SMS от %d: %s", character_info[playerid][phoneslot], params[1]);
			else format(str, sizeof(str), "SMS от %s [%d]: %s", contacts_info[p][contacts_slot_rec][Name], character_info[playerid][phoneslot], params[1]);
			SCM(p, COLOR_YELLOW, str);

			if(contacts_slot_sender == -1) format(str, sizeof(str), "SMS к %d: %s", character_info[p][phoneslot], params[1]);
			else format(str, sizeof(str), "SMS к %s [%d]: %s", contacts_info[playerid][contacts_slot_sender][Name], character_info[p][phoneslot], params[1]);
			SCM(playerid, COLOR_YELLOW, str);

			new wire_str[180];
			format(wire_str, sizeof(wire_str), " > %d (SMS): %s", character_info[p][phoneslot], params[1]);
			WireMsg(playerid, p, wire_str);
			
			new qu[256], temp[256], lyear, lmonth, lday;
			getdate(lyear, lmonth, lday);
			format(str, sizeof(str), "%02d:%02d %02d.%02d", hour, minute, lday, lmonth);
			mysql_real_escape_string(params[1], temp);
	 		format(qu, sizeof(qu), "INSERT INTO `phone_sms`(`phone`, `from`, `text`, `time`) VALUES (%d,%d,'%s','%s')", character_info[p][phoneslot], character_info[playerid][phoneslot], temp, str);
			mysql_function_query(dbHandle, qu, false, "", "");
			return 1;
		}
    }
    SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный номер не обслуживается!");
    return 1;
}

CMD:smshistory(playerid)
{
    if(character_info[playerid][phoneslot] == -1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте!");
	
	new qu[256];
	format(qu, sizeof(qu), "SELECT * FROM `phone_sms` WHERE `phone`='%d' or `from`='%d' ORDER BY  `phone_sms`.`id` DESC LIMIT 15", character_info[playerid][phoneslot], character_info[playerid][phoneslot]);
	mysql_function_query(dbHandle, qu, true, "OnSmsHistory", "ii", playerid, character_info[playerid][phoneslot]);
	return 1;
}

CMD:contacts(playerid)
{
	new str[512], myname[25], myphone[25];
    if(character_info[playerid][phoneslot] == -1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте!");
    //new phonenumber = character_info[playerid][phoneslot];
    for(new i = 0; i<12; i++)
	{
	    if(!strcmp(contacts_info[playerid][i][Name], "0", true, 10 ))  format(myname, sizeof(myname), "{AFAFAF}(Пусто) {FFFFFF}");
		else format(myname, sizeof(myname), "%s", contacts_info[playerid][i][Name]);
		if(contacts_info[playerid][i][Phone] <= 0) format(myphone, sizeof(myphone), " ");
		else format(myphone, sizeof(myphone), "%d", contacts_info[playerid][i][Phone]);

	    format(str, sizeof(str), "%s%s\t%s\n", str, myname, myphone);
	}
	ShowPlayerDialog(playerid, 24, DIALOG_STYLE_TABLIST, "Контакты", str, "Выбрать", "Закрыть");
	return 1;
}


CMD:entercreate(playerid)
{
    if(IsAdmin(playerid, 5)) 
		return 1;
    
	SPD(playerid, 35, DIALOG_STYLE_TABLIST, "Создать вход", "Установить текст\nСохранить координаты входа\nСохранить координаты выхода\nУстановить вход", "Выбрать", "Закрыть");
    return 1;
}

CMD:enterdelete(playerid, params[])
{
	if(IsAdmin(playerid, SUPER_ADMIN)) 
		return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/enterdelete [ENTERID]");
	new qu[30+11];
	format(qu, sizeof(qu), "DELETE FROM `enters` WHERE id=%d",params[0]);
	mysql_function_query(dbHandle, qu, false, "", "");
	UnLoadEnters();
	LoadEnters();
	SCM(playerid, COLOR_GREEN, "Вы удалили вход!");
	return 1;
}

CMD:enterupdate(playerid)
{
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	UnLoadEnters();
	LoadEnters();
	Sound_Succ(playerid);
	return 1;
}
CMD:gopos(playerid, params[])
{
 	if(IsAdmin(playerid, 3)) return 1;
	new Float:x, Float:y, Float:z;
	if(sscanf(params,"fff", x, y ,z)) return SyntaxCMD(playerid, "/gopos [Pos X] [Pos Y] [Pos Z]");
	SetPlayerPos(playerid, x, y ,z);
	return 1;
}
CMD:buy(playerid)
{
	if(PlayerToPoint(2.5, playerid, 1154.7264,-1440.3060,15.7969))
	{
		ShowPlayerDialog(playerid, 133, DIALOG_STYLE_TABLIST, "Ключи", "Сделать ключ для имущества\nСделать ключ для автомобиля", "Выбрать", "Отмена");
	}
	else if(InPropType(playerid, 5))
    {
        new str[256];
        for(new i=0; i<sizeof(list_eatery); i++)
        {
        	format(str, sizeof(str), "%s%s\t%d$\n", str, senderitems(list_eatery[i][iditem]), list_eatery[i][price]);
        }
        ShowPlayerDialog(playerid, 126, DIALOG_STYLE_TABLIST, "Клуб", str, "Выбрать", "Отмена");
    }
	else if(InPropType(playerid, 4))
    {
        new str[256];
        for(new i=0; i<sizeof(list_club); i++)
        {
        	format(str, sizeof(str), "%s%s\t%d$\n", str, senderitems(list_club[i][iditem]), list_club[i][price]);
        }
        ShowPlayerDialog(playerid, 125, DIALOG_STYLE_TABLIST, "Клуб", str, "Выбрать", "Отмена");
    }
	else if(InPropType(playerid, 3))
    {
        new str[256];
        for(new i=0; i<sizeof(list_bar); i++)
        {
        	format(str, sizeof(str), "%s%s\t%d$\n", str, senderitems(list_bar[i][iditem]), list_bar[i][price]);
        }
        ShowPlayerDialog(playerid, 124, DIALOG_STYLE_TABLIST, "Бар", str, "Выбрать", "Отмена");
    }
    else if(InPropType(playerid, 2))
    {
        ShowPlayerDialog(playerid, 51, DIALOG_STYLE_TABLIST, "Магазин одежды", "{FFFFFF}Покупка одежды\t150$\nПокупка аксессуаров\t70$", "Выбрать", "Отмена");
    }
	else if(InPropType(playerid, 1))
    {
        new str[256];
        for(new i=0; i<sizeof(list_store); i++)
        {
        	format(str, sizeof(str), "%s%s\t%d$\n", str, senderitems(list_store[i][iditem]), list_store[i][price]);
        }
        ShowPlayerDialog(playerid, 43, DIALOG_STYLE_TABLIST, "Магазин 24/7", str, "Выбрать", "Отмена");
    }
	return 1;
}
CMD:charge(playerid, params[])
{
    if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/charge [количество патронов]");
    new item_slot = checkitem(playerid, 2);
	if(params[0] > character_info[playerid][inv][count][item_slot] || params[0] < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверное количество патронов.");
	if(character_info[playerid][gun] < 22 || character_info[playerid][gun] == 41) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны держать огнестрельное оружие в руках.");
	deleteitem(playerid, 2, params[0]);
	character_info[playerid][ammo] += params[0];
	ResetPlayerWeapons(playerid);
	GivePlayerWeapon(playerid, character_info[playerid][gun],character_info[playerid][ammo]);
	SCM(playerid, COLOR_GREEN, ">{FFFFFF} Вы зарядили свое оружие.");
	SCM(playerid, COLOR_GREEN, ">{FFFFFF} Используйте /discharge чтобы разрядить оружие.");
	return 1;
}
CMD:discharge(playerid)
{
	if(character_info[playerid][gun] < 22 || character_info[playerid][gun] == 41 || character_info[playerid][gun] == 43) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны держать огнестрельное оружие в руках.");
	if(character_info[playerid][ammo] > 0)
	{
		giveitem(playerid, 2, character_info[playerid][ammo]);
	    character_info[playerid][ammo] = 0;
		ResetPlayerWeapons(playerid);
		SCM(playerid, COLOR_GREEN, ">{ffffff} Вы разрядили свое оружие.");
	}
	return 1;
}
CMD:faction(playerid)
{
    if(!InFaction(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь во фракции или она заморожена!");
    ShowPlayerDialog(playerid, 54, DIALOG_STYLE_TABLIST, "Фракции", "Информация\nЧлены фракции онлайн\nВсе члены фракции\nПокинуть фракцию\nНастройки", "Выбрать", "Отмена");
    return 1;
}
CMD:factions(playerid)
{
    if(IsAdmin(playerid, 5)) return 1;
    new str[1028] = "Название\tID Лидера\tТип\tЗаморожена\nСоздать фракцию\n", temp[32];
	
	for(new i=0; i<sizeof(factions); i++)
	{
	    if(strlen(factions[i][Name]) < 2) 
			continue;
		if(factions[i][Type] == 1) 
			format(temp, sizeof(temp), "Государственная");
		else if(factions[i][Type] == 2) 
			format(temp, sizeof(temp), "Коммерческая");
        else if(factions[i][Type] == 3) 
			format(temp, sizeof(temp), "Банда");
        else if(factions[i][Type] == 4) 
			format(temp, sizeof(temp), "Мафия");
		else
			format(temp, sizeof(temp), "UNKNOWN");

	    format(str, sizeof(str), "%s[%d] %s\t%d\t%s", str, i, factions[i][Name], factions[i][Leader], temp);

		if(factions[i][FactionFreeze] == 0) 
			format(temp, sizeof(temp), "{b1b1b1}Нет{ffffff}");
		else 
			format(temp, sizeof(temp), "{ff0000}Да{ffffff}");
	    
		format(str, sizeof(str), "%s\t%s\n", str, temp);
	}
	
	ShowPlayerDialog(playerid, 45, DIALOG_STYLE_TABLIST_HEADERS, "Фракции", str, "Выбрать", "Отмена");
	return 1;
}

CMD:playerfaction(playerid, params[])
{
    if(IsAdmin(playerid, 5)) return 1;
    if(sscanf(params,"ddd", params[0], params[1], params[2])) SyntaxCMD(playerid, "/playerfaction [id] [faction] [rank]");
    if(params[1] > -1) character_info[params[0]][faction] = params[1];
    if(params[2] > -1) character_info[params[0]][rank] = params[2];
   	new str[128];
	format(str, sizeof(str), "%s(%d) назначил персонажу %s фракцию %d и ранг %d", player_info[playerid][login], playerid, character_info[params[0]][name], character_info[params[0]][faction], character_info[params[0]][rank] );
	AdminLog(str);
    return 1;
}
CMD:createdoor(playerid, params[])
{
    if(IsAdmin(playerid, 5)) return 1;
	if(sscanf(params, "dd", params[0], params[1])) return SyntaxCMD(playerid, "/createdoor [model] [factionid]");
	if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
		return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");

	new Float:angle, Float:x,Float:y,Float:z, obj;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	x += floatsin(-angle, degrees);
	y += floatcos(-angle, degrees);
	obj = CreateDynamicObject(params[0], x+2.5, y+2.5, z, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

	character_info[playerid][editobject] = obj;
	character_info[playerid][type_editobj] = 4;
    SetPVarInt(playerid, "createdoor_objectid", params[0]);
	SetPVarInt(playerid, "createdoor_factionid", params[1]);
	SCM(playerid, COLOR_YELLOW, "Выберите позицию закрытой двери");
	EditDynamicObject(playerid, obj);
	return 1;
}

CMD:spawn(playerid, params[])
{
	if(IsAdmin(playerid, 2)) 
		return 1;
	
	if(sscanf(params,"d", params[0])) 
		return SyntaxCMD(playerid, "/spawn [id]");
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	if(character_info[params[0]][jail_time] > 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный игрок в тюрьме!");
	
	if(character_info[params[0]][ajail_time] > 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный игрок в админ тюрьме!");
	
	SetPlayerPos(params[0], 1777.1, -1939.08, 13.558);
	SetPlayerVw(params[0], 0);
	SetPlayerInt(params[0], 0);
	new str[128];
	
	format(str, sizeof(str), "%s заспаунил %s", player_info[playerid][login], character_info[params[0]][name]);
	AdminLog(str);
	return 1;
}

CMD:ajail(playerid, params[])
{
    if(IsAdmin(playerid, 2)) return 1;
    if(sscanf(params,"dds[64]", params[0], params[1], params[2])) return SyntaxCMD(playerid, "/ajail [id] [minute] [reason]");
    if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
    if(params[1] < 0 || params[1] > 9999) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество минут!");
    new str[124];
	format(str, sizeof(str), "%s(%d) посадил игрока %s на %d минут в тюрьму. Причина: %s",
	player_info[playerid][login], playerid, character_info[params[0]][name], params[1], params[2]);
   	AdminMessage(str);
   	format(str, sizeof(str), "был отправлен в AJAIL администратором %s. Причина: %s", player_info[playerid][login], params[2]);
    OOCMSG(params[0], str);
    GoToAjail(params[0]);
	character_info[params[0]][ajail_time] = params[1]*60;
    return 1;
}
CMD:unban(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"s[25]", params[0])) return SyntaxCMD(playerid, "/unban [name]");
	new qu[70+25];
	format(qu, sizeof(qu), "DELETE FROM `ban` WHERE userid=(SELECT id FROM users WHERE login='%s')", params[0]);
	mysql_function_query(dbHandle, qu, false, "", "");
	SCM(playerid, COLOR_GREEN, "Вы разбанили игрока!");
	new str[180];
	format(str, sizeof(str), "%s[%d] разбанил %s", player_info[playerid][login], playerid, params[0]);
	AdminMessage(str);
	return 1;
}

CMD:ban(playerid, params[])
{
    if(IsAdmin(playerid, 2)) 
		return 1;
    new days;
    if(sscanf(params,"uds[116]", params[0], days, params[2])) 
		return SyntaxCMD(playerid, "/ban [id / name] [days] [reason]");
    if(player_info[playerid][admin] < 6 && days < 1 || days > 30) {
    	return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете банить более чем на 30 дней.");
    } 
	if(!IsPlayerConnected(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
    
	if(days < 0 || days > 9999) 
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество дней");
	new str[512];
	
	if(GetPVarInt(playerid, "LastBanCount") >= 2)
	{
		format(str, sizeof(str), "%s лишен своих админ прав из-за возможного несанкционированном использования /ban.", player_info[playerid][login]);
		AdminMessage(str);
		player_info[playerid][admin] = 0;
		KickEx(playerid);
		return 1;
	}
	
   	new qu[124], temp[64];
   	mysql_real_escape_string(params[2], temp);
	if(days != 0) 	
		format(qu, sizeof(qu), "INSERT INTO `ban`(`userid`, `banid`, `reason`, `time`) VALUES (%d, %d, '%s', %d)", player_info[params[0]][id], player_info[playerid][id], temp, gettime() + (3600*24)*days);
	else 
   		format(qu, sizeof(qu), "INSERT INTO `ban`(`userid`, `banid`, `reason`, `time`) VALUES (%d, %d, '%s', 0)", player_info[params[0]][id], player_info[playerid][id], temp);

	mysql_function_query(dbHandle, qu, false, "", "");
 	
	if(days != 0) 
		format(str, sizeof(str), "%s(%d) заблокировал игрока %s на %d дней. Причина: %s", player_info[playerid][login], playerid, character_info[params[0]][name], days, temp);
 	else 
		format(str, sizeof(str), "%s(%d) заблокировал игрока %s. Причина: %s", player_info[playerid][login], playerid, character_info[params[0]][name], temp);
   	
	AdminMessage(str);
   	format(str, sizeof(str), "был заблокирован администратором %s. Причина: %s", player_info[playerid][login], params[2]);
    OOCMSG(params[0], str);
   	KickEx(params[0]);
	
	if(GetPVarInt(playerid, "LastBan")+30 >= gettime()) 
		SetPVarInt(playerid, "LastBanCount", GetPVarInt(playerid, "LastBanCount")+1);
	else 
		DeletePVar(playerid, "LastBanCount");
	
	SetPVarInt(playerid, "LastBan", gettime());
   	return 1;
}

CMD:channel(playerid, params[])
{
	if(!anyRadio(playerid))
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет рации!");
	
	if(sscanf(params,"d", params[0])) 
		return SyntaxCMD(playerid, "/channel [канал]");
	
	if(params[0] < 0 || params[0] > 5000) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} /channel [0 - 5000]");
	
	if(!InFactionType(playerid, 1) && params[0] == 911) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете пользоваться защищенным каналом!");
	
	character_info[playerid][r_channel] = params[0];
	SCM(playerid, COLOR_GREEN, ">{ffffff} Канал рации настроен!");
	return 1;
}
CMD:slot(playerid, params[])
{
	if(!anyRadio(playerid))
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет рации!");
		
    if(sscanf(params,"d", params[0])) 
		return SyntaxCMD(playerid, "/slot [подканал]");
    
	if(params[0] < 0 || params[0] > 10000) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} /slot [0 - 10000]");
	
	character_info[playerid][r_slot] = params[0];
	SCM(playerid, COLOR_GREEN, ">{ffffff} Подканал рации настроен!");
	return 1;
}
CMD:f(playerid, params[])
{
    if(!InFaction(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть во фракции!");
	
	if(sscanf(params,"s[128]", params[0])) 
		return SyntaxCMD(playerid, "/f [текст]");
	
	if(player_info[playerid][mute])
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} ООС чаты для вас заблокированы!");
	
	new str[180];
	format(str, sizeof(str), "(( %s %s(%d): %s ))", faction_ranks[character_info[playerid][faction]][character_info[playerid][rank]], character_info[playerid][name], playerid, params[0]);
	foreach(new p : Player)
	{
	    if(!IsPlayerLoged(p) || character_info[playerid][faction] != character_info[p][faction]) continue;
	    SCM(p, COLOR_FACTIONCHAT, str);
	}
	return 1;
}
CMD:d(playerid, params[])
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) return 1;
	if(sscanf(params,"s[180]", params[0])) return SyntaxCMD(playerid, "/d [текст]");
	new str[180];
	
	/*faction_ranks[character_info[playerid][factionid]][character_info[playerid][rank]]
	factions[character_info[playerid][factionid]][Name]
	*/
	format(str, sizeof(str), "[%s] %s %s: %s", factions[character_info[playerid][faction]][Name], faction_ranks[character_info[playerid][faction]][character_info[playerid][rank]], sendername(playerid, true), params[0]);
	
	foreach(new p : Player)
	{
		if(!IsPlayerLoged(p) || !InFactionType(p, 1)) continue;
		SCM(p, 0xff96a000, str);
	}
	return 1;
}
CMD:rr(playerid, params[])
{
    
	if(!anyRadio(playerid))
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет рации!");
	
	if(character_info[playerid][r_channel] < 1 || character_info[playerid][r_slot] < 1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверно настроена волна рации!");
	
	if(sscanf(params,"s[180]", params[0])) 
		return SyntaxCMD(playerid, "/r [текст]");
    
	if(!InFactionType(playerid, 1) && character_info[playerid][r_channel] >= 911 && character_info[playerid][r_channel] <= 999) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете пользоваться защищенным каналом!");
	
    new str[180];
	new str_radio_local[180];
	SetPlayerChatBubble(playerid,str_radio_local,COLOR_ME,30.0,5000);
	format(str_radio_local, sizeof(str_radio_local), "%s говорит в рацию: %s",  sendername(playerid, true), params[0]);
	foreach(new p : Player)
	{
		if(!IsPlayerLoged(p)) continue;
	    if(character_info[playerid][r_channel] != character_info[p][r_channel] || character_info[playerid][r_slot] != character_info[p][r_slot]) continue;
        if(!InFactionType(p, 1) && character_info[p][r_channel] >= 911 && character_info[p][r_channel] <= 999) continue;
		format(str, sizeof(str), "**[CH: %d, S: %d] %s: %s", character_info[playerid][r_channel], character_info[playerid][r_slot], sendername(playerid, true), params[0]);
		Log_Write("logs/chat_log.txt", "[%s] [CH: %d, S: %d] %s: %s", ReturnDate(), character_info[playerid][r_channel], character_info[playerid][r_slot], sendername(playerid, true), params[0]);
	    SCM(p, COLOR_PAPAYA, str);
	}
	return 1;
}

CMD:r(playerid, params[])
{	

	if(!anyRadio(playerid))
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет рации!");
	
	if(character_info[playerid][r_channel] < 1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверно настроена волна рации!");
	
	if(sscanf(params,"s[180]", params[0])) 
		return SyntaxCMD(playerid, "/r [текст]");
	
	if(!InFactionType(playerid, 1) && character_info[playerid][r_channel] >= 911 && character_info[playerid][r_channel] <= 999) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете пользоваться защищенным каналом!");
    
	new str[180];
	new str_radio_local[180];
	
	format(str_radio_local, sizeof(str_radio_local), "%s говорит в рацию: %s",  sendername(playerid, true), params[0]);
	SetPlayerChatBubble(playerid, str_radio_local, COLOR_ME, 30.0,5000);
	
	foreach(new p : Player)
	{
		if(anyRadio(p))
		{
			if(!IsPlayerLoged(p) || character_info[playerid][r_channel] != character_info[p][r_channel]) 
				continue;
			if(!InFactionType(p, 1) && character_info[p][r_channel] >= 911 && character_info[p][r_channel] <= 999) 
				continue;
			format(str, sizeof(str), "**[CH: %d, S: 0] %s: %s", character_info[playerid][r_channel], sendername(playerid, true), params[0]);
			SCM(p, COLOR_PAPAYA, str);
		}
	}
	return 1;
}
CMD:rinfo(playerid)
{
	new str[256], temp[24];

	if(!InFactionType(playerid, 1) && character_info[playerid][r_channel] >= 911 && character_info[playerid][r_channel] <= 999) format(temp, sizeof(temp), "{FF6347}Не пройдена");
	else if(InFactionType(playerid, 1) && character_info[playerid][r_channel] >= 911 && character_info[playerid][r_channel] <= 999) format(temp, sizeof(temp), "{33AA33}Пройдена");
	else format(temp, sizeof(temp), "{AFAFAF}Не требуется");

	format(str, sizeof(str), "{FFFFFF}Используемый канал: {AFAFAF}%d\n{FFFFFF}Используемый подканал: {AFAFAF}%d\n\n{FFFFFF}Аунтификация защищенного канала: %s", character_info[playerid][r_channel], character_info[playerid][r_slot], temp);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "RADIO", str, "Закрыть", "");
}

ALTX:sp("/spec", "/re", "/recon");
CMD:sp(playerid, params[])
{
    if(IsAdmin(playerid, 2)) 
		return 1;
	
	if(sscanf(params, "d", params[0])) 
	{
		if(GetPVarInt(playerid, "SPEC"))
			return cmd_spoff(playerid);
		return SyntaxCMD(playerid, "/sp [id]");
	}
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		PVarPosSave(playerid);
	
	SetPVarInt(playerid, "SPEC", 1);
	SetPVarInt(playerid, "SPEC_PLAYER", params[0]);
	
	SetPlayerInt(playerid, GetPlayerInterior(params[0]));
	SetPlayerVw(playerid, GetPlayerVirtualWorld(params[0]));
	
	TogglePlayerSpectating(playerid, 1);
	
	if(GetPlayerState(params[0]) == 1) 
		PlayerSpectatePlayer(playerid, params[0]);
	else if(GetPlayerState(params[0]) == 2 || GetPlayerState(params[0]) == 3) 
		PlayerSpectateVehicle(playerid, GetPlayerVehicleID(params[0]));
	
	GameTextForPlayer(playerid, "~g~/spoff", 1000, 3);
	return 1;
}


ALTX:spoff("/specoff", "/reoff", "/reconoff");
CMD:spoff(playerid)
{
    if(IsAdmin(playerid, 2) || !GetPVarInt(playerid, "SPEC")) 
		return 1;
    
	if (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не в режиме просмотра.");
	
	PlayerSpectatePlayer(playerid, INVALID_PLAYER_ID);
	PlayerSpectateVehicle(playerid, INVALID_VEHICLE_ID);
	
	SetSpawnInfo(playerid, 0, character_info[playerid][skin], GetPVarFloat(playerid, "pos_x"), GetPVarFloat(playerid, "pos_y"), GetPVarFloat(playerid, "pos_z"), 0.0, 0, 0, 0, 0, 0, 0);

	TogglePlayerSpectating(playerid, false);
	return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы покинули режим наблюдения.");
}

CMD:invite(playerid, params[])
{
	if(!InFaction(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
	if(character_info[playerid][rank] < factions[character_info[playerid][faction]][invite_rank]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/invite [id игрока]");
	new Float:x,Float:y,Float:z;
	GetPlayerPos(params[0], x,y,z);
	if(!PlayerToPoint(10.0, playerid, x,y,z)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится рядом с выбранным персонажем!");
	if(character_info[params[0]][faction] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный игрок находится в другой фракции!");
	SetPVarInt(params[0], "invited_faction", character_info[playerid][faction]);
	SetPVarInt(params[0], "invited_player", playerid);
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы отправили приглашение во фракцию данному игроку!");
	new str[128];
	format(str, sizeof(str), "{FFFFFF}Вы действительно хотите вступить в фракцию %s?", factions[character_info[playerid][faction]][Name]);
	ShowPlayerDialog(params[0], 63, DIALOG_STYLE_MSGBOX, "Приглашение во фракцию", str, "Да", "Нет");
	return 1;
}
ALTX:giverank("/rank", "/setrank", "/changerank");
CMD:giverank(playerid, params[])
{
    if(!InFaction(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
    if(character_info[playerid][rank] < factions[character_info[playerid][faction]][giverank_rank]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
    if(sscanf(params,"dd", params[0], params[1])) return SyntaxCMD(playerid, "/giverank [id игрока] [ранг]");
	if(params[1] < 1 || params[1] > 20 || params[1] > character_info[playerid][rank] && !InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте значение от 1 до 20!");
	if(params[0] == playerid && !InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете изменть свой ранг!");
   	new Float:x,Float:y,Float:z;
	GetPlayerPos(params[0], x,y,z);
	//if(!PlayerToPoint(10.0, playerid, x,y,z)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится рядом с выбранным персонажем!");
    if(character_info[params[0]][faction] != character_info[playerid][faction]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный игрок не находится в вашей фракции!");
    if(character_info[playerid][rank] <= character_info[params[0]][rank] && !InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете изменить ранг персонажа, чей ранг не ниже вашего!");
	new str[128];
	format(str, sizeof(str), ">{FFFFFF} %s изменил ваш ранг с %d на %d", character_info[playerid][name], character_info[params[0]][rank], params[1]);
	SCM(params[0], COLOR_MSGSERVER, str);
	format(str, sizeof(str), ">{FFFFFF} Вы изменили ранг %s с %d на %d", character_info[params[0]][name], character_info[params[0]][rank], params[1]);
	SCM(playerid, COLOR_MSGSERVER, str);
	character_info[params[0]][rank] = params[1];
	return 1;
}

CMD:offuninvite(playerid, params[])
{
    if(!InFaction(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
    
	if(character_info[playerid][rank] < factions[character_info[playerid][faction]][uninvite_rank]) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
    
	if(sscanf(params,"s[24]", params[0])) 
		return SyntaxCMD(playerid, "/offuninvite [Имя игрока]");
    
	new qu[512];
    format(qu, sizeof(qu), "UPDATE `characters` SET `faction` = '0' WHERE `name` = '%s' and `faction`='%d'", params[0], character_info[playerid][faction]);
    
	foreach(new p : Player)
    {
    	if(!IsPlayerLoged(p))
			continue;
    	if(CompareStrings(params[0], character_info[playerid][name]))
    	{
    		cmd_uninvite(playerid, params[0]);
    		return 1;
    	}
    }
	
	mysql_function_query(dbHandle, qu, false, "", "");
	SCM(playerid, COLOR_GREEN, ">{ffffff} Если человек был в вашей фракции значит он уволен. Проверку делать мне было лень. :(");
    return 1;
}
CMD:uninvite(playerid, params[])
{
    if(!InFaction(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
    if(character_info[playerid][rank] < factions[character_info[playerid][faction]][uninvite_rank]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
    if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/uninvite [id игрока]");
    if(params[0] == playerid) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете уволить себя!");
    new Float:x,Float:y,Float:z;
	GetPlayerPos(params[0], x,y,z);
	//if(!PlayerToPoint(10.0, playerid, x,y,z)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится рядом с выбранным персонажем!");
    if(character_info[params[0]][faction] != character_info[playerid][faction]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный игрок не находится в вашей фракции!");
    if(character_info[playerid][rank] <= character_info[params[0]][rank] && !InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете уволить персонажа, чей ранг не ниже вашего!");
	new str[128];
	format(str, sizeof(str), "Вы были уволены из фракции %s", character_info[playerid][name]);
	SCM(params[0], COLOR_PAPAYA, str);
	format(str, sizeof(str), "Вы уволили из фракции %s", character_info[params[0]][name]);
	SCM(playerid, COLOR_PAPAYA, str);
	character_info[params[0]][faction] = 0;
	character_info[params[0]][rank] = 0;
    return 1;
}
CMD:members(playerid)
{
	if(!InFaction(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть во фракции!");
	new str[64];
	foreach(new p : Player)
	{
	    if(!IsPlayerLoged(p) || character_info[p][faction] != character_info[playerid][faction]) continue;
	    format(str, sizeof(str), "%s - %s[%d]", character_info[p][name], faction_ranks[character_info[p][faction]][character_info[p][rank]], character_info[p][rank]);
	    SCM(playerid, COLOR_WHITE, str);
	}
	return 1;
}
CMD:offmembers(playerid)
{
    if(!InFaction(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть во фракции!");
    new qu[128];
    format(qu, sizeof(qu), "SELECT name, rank FROM characters WHERE faction=%d", character_info[playerid][faction]);
  	mysql_function_query(dbHandle, qu, true, "OnOffMembers", "i", playerid);
  	return 1;
}

CMD:b(playerid, params[])
{
    if(sscanf(params,"s[124]", params[0])) 
		return SyntaxCMD(playerid, "/b [text]");
	
	new str[180];
	Log_Write("logs/chat_log.txt", "[%s] [OOC]: (( %s(%d): %s ))", ReturnDate(), sendername(playerid), playerid, params[0]);
	format(str, sizeof(str), "(( {%06x}%s(%d){ffffff}: %s ))", GetPlayerColor(playerid) >>> 8, sendername(playerid), playerid, params[0]);
	ProxDetector( 7.5, GetPlayerVirtualWorld( playerid ), playerid, str, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);
	return 1;
	
	/*	
	antib[playerid] = gettime()+15;
	new str[180];
	Log_Write("logs/chat_log.txt", "[%s] [OOC]: (( %s(%d): %s ))", ReturnDate(), sendername(playerid), playerid, params[0]);
	format(str, sizeof(str), "(( {%06x}%s(%d){ffffff}: %s ))", GetPlayerColor(playerid) >>> 8, sendername(playerid), playerid, params[0]);
	ProxDetector( 7.5, GetPlayerVirtualWorld( playerid ), playerid, str, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE );
	return 1;
	*/
}
CMD:ab(playerid, params[])
{
    if(sscanf(params,"s[124]", params[0])) 
		return SyntaxCMD(playerid, "/ab [text]");
	
	if(player_info[playerid][mute])
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} ООС чаты для вас заблокированы!");
	
	if(flood[playerid][ooc] > gettime())
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Доступно раз в 15 секунд!");
	flood[playerid][ooc] = gettime()+10;
	
	new str[180];
	Log_Write("logs/chat_log.txt", "[%s] [AB]: (( %s: %s ))", ReturnDate(), sendername(playerid), params[0]);
	format(str, sizeof(str), "(( %s(%d): %s ))", sendername(playerid), playerid, params[0]);
	SetPlayerChatBubble(playerid,str,COLOR_WHITE,30.0,5000);
	SendClientMessageEx(playerid, COLOR_WHITE, str);
	return 1;
}
CMD:s(playerid, params[])
{
    if(sscanf(params,"s[124]", params[0])) return SyntaxCMD(playerid, "/s [text]");
	new str[180];
	format(str, sizeof(str), "%s кричит: %s", sendername(playerid, true), params[0]);
	ProxDetector( 25.0, GetPlayerVirtualWorld( playerid ), playerid, str, str, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE, COLOR_WHITE );
	return 1;
}


CMD:setfuel(playerid, params[])
{
	if(IsAdmin(playerid, 2)) 
		return 1;
	
	if(sscanf(params,"dd", params[0], params[1])) 
		return SyntaxCMD(playerid, "/setfuel [id] [fuel]");
	
	if(params[1] > 100 || params[1] < 0)
		return SyntaxCMD(playerid, "/setfuel [id] [fuel]");
	
	veh_info[params[0]][fuel] = params[1];
	return 1;
}


CMD:pm(playerid, params[])
{
	if(sscanf(params,"ds[128]", params[0], params[1])) 
		return SyntaxCMD(playerid, "/pm [id] [текст]");
	
	if(player_info[playerid][mute])
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} ООС чаты для вас заблокированы!");
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
	
	if (params[0] == playerid)
	    return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете отправлять приватные сообщения себе!");
	
	if(!player_info[playerid][settings][1]) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас отключены PM сообщения!");
	
	if(!player_info[params[0]][settings][1]) 
		return SCM(playerid, COLOR_TOMATO, "У игрока отключены PM сообщения!");
	
	new str[128];
	Log_Write("logs/chat_log.txt", "[%s] [PM]: %s -> %s: %s", ReturnDate(), sendername(params[0],true), sendername(playerid, true), params[1]);
	format(str, sizeof(str), "(( PM от %s[%d]: %s ))", sendername(playerid,true), playerid, params[1]);
	SCM(params[0], COLOR_YELLOW, str);
	format(str, sizeof(str), "(( PM к %s[%d]: %s ))", sendername(params[0],true), params[0], params[1]);
	SCM(playerid, COLOR_YELLOW, str);
 	return 1;
}

CMD:deliver(playerid)
{
    ResultPurchase(playerid);
}

CMD:mdc(playerid)
{
	if(TestMDC(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту функцию!");
	
	ShowPlayerDialog(playerid, 73, DIALOG_STYLE_LIST, "Police MDC System", 
	"Поиск по имени\n\
	Поиск по номеру авто\n\
	Поиск имущества\n\
	Обвинения/Судимости\n\
	Последние звонки в 911\n\
	Последние аресты\n\
	База данных осужденных\n\
	База данных по штрафам\n\
	Выписать предупреждение на вод. лицензию", "Выбрать", "Отмена");
	return 1;
}
CMD:devon(playerid)
{
	if(IsAdmin(playerid, 5)) return 1;
	SetPVarInt(playerid, "_dev_", 1);
	SCM(playerid, COLOR_GREEN, "Вы включили DEV режим!");
	return 1;
}

CMD:devoff(playerid)
{
	if(IsAdmin(playerid, 5)) return 1;
	DeletePVar(playerid, "_dev_");
	SCM(playerid, COLOR_GREEN, "Вы выключили DEV режим!");
	return 1;
}

CMD:settings(playerid)
{
	new str[256] = "Параметр\tСостояние";
	
	format(str, sizeof(str), "%s\nОтображение района над картой\t", str);
	if(player_info[playerid][settings][0]) 
		strcat(str, "{33AA33}ON"); 
	else 
		strcat(str, "{FF6347}OFF"); 
	
	format(str, sizeof(str), "%s\nPM чат\t", str);
	if(player_info[playerid][settings][1]) 
		strcat(str, "{33AA33}ON"); 
	else 
		strcat(str, "{FF6347}OFF"); 
		
	ShowPlayerDialog(playerid, 119, DIALOG_STYLE_TABLIST_HEADERS, "Настройки", str, "Выбрать", "Отмена");
}
ALTX:settings("/tog");

CMD:look(playerid, params[])
{
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/look [id/часть ника]");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(params[0], xyz);
	if(!PlayerToPoint(15.0, playerid,xyz)) return 1;
	new str[300];
	if(!CompareStrings(character_info[params[0]][description], "NULL")) format(str, sizeof(str), "{FFFFFF}%s", character_info[params[0]][description]);
	else format(str, sizeof(str), "{b1b1b1}Описание персонажа не установлено!");
	if(IsCop(playerid))
	{
		if(CopSkin(GetPlayerSkin(params[0])))
		{
			format(str, sizeof(str), "%s\n\n{b1b1b1}[Бейдж/Жетон]\n#%d, %s", str, character_info[params[0]][id], faction_ranks[character_info[params[0]][faction]][character_info[params[0]][rank]]);
		}
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, sendername(params[0]), str, "Закрыть", "");
	return 1;
}

CMD:description(playerid)
{
	new str[256];
	format(str, sizeof(str), "{FFFFFF}%s\n\nВведите новое описание: ", character_info[playerid][description]);
	ShowPlayerDialog(playerid, 80, DIALOG_STYLE_INPUT, "Новое описание персонажа", str, "Ввод", "Закрыть");
	return 1;
}
ALTX:description("/pame", "/desc");

CMD:accept(playerid, params[])
{
	if(sscanf(params, "d", params[0])) 
		return SyntaxCMD(playerid, "/accept [номер вызова]");
	
	if(InFactionType(playerid, FACTIONTYPE_STATE))
	{
		for(new i; i<count_911; i++)
		{
			if(list_911[i][id] == params[0])
			{
				DestroyCheckpoint(playerid);
				SetPVarInt(playerid, "search_checkpoint", 1);
				SetPlayerCheckpoint(playerid, list_911[i][posX], list_911[i][posY], list_911[i][posZ], 3.0);
				
				new str[180];
				format(str, sizeof(str), "принял вызов %d", params[0]);
				fmsg(playerid, str);
				return 1;
			}
		}
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы указали неверный номер вызова");
		return 1;
	}
	else
	{
		if(!isPlayerDriver(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть водителем такси!");
		new v = GetPlayerVehicleID(playerid);
		if(!IsValidDynamicObject(veh_info[v][taxi])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть водителем такси!");
		if(GetPVarFloat(params[0], "taxiX") == 0.0 || GetPVarFloat(params[0], "taxiY") == 0.0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Такого вызова не существует!");
		DestroyCheckpoint(playerid);
		SetPVarInt(playerid, "search_checkpoint", 1);
		SetPlayerCheckpoint(playerid, GetPVarFloat(params[0], "taxiX"), GetPVarFloat(params[0], "taxiY"), GetPVarFloat(params[0], "taxiZ"), 3.0);
		DeletePVar(params[0], "taxiX");
		DeletePVar(params[0], "taxiY");
		DeletePVar(params[0], "taxiZ");
		new str[180];
		format(str, sizeof(str), "Вызов #%d был принят!", params[0]);
		TaxiMsg(str);
		SCM(params[0], COLOR_GREEN, ">{ffffff} Ваш вызов такси приняли!");
	}
	return 1;
}
CMD:untaxi(playerid)
{
	if(!isPlayerDriver(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть водителем такси!");
	new v = GetPlayerVehicleID(playerid);
	if(!IsValidDynamicObject(veh_info[v][taxi])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть водителем такси!");
	DestroyDynamicObject(veh_info[v][taxi]);
	veh_info[v][taxi] = 0;
	giveitem(playerid, 153, 1);
	return 1;
}

CMD:todo(playerid)
{
	//return PlayAudioStreamForPlayer(playerid, "http://pacific-coast.ru/music/todo.mp3");
	return 0;
}

CMD:duty(playerid)
{
	if(!IsDutyPickup(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду здесь!");
	
	if(IsCop(playerid) || character_info[playerid][faction] == MAYOR_FACTION) 
		ShowPlayerDialog(playerid, 81, DIALOG_STYLE_LIST, "DUTY", "Выход на дежурство\nВзять рацию\nВзять бронежилет\nВзять оружие\nПоложить оружие\nВыбрать скин", "Выбрать", "Закрыть");
	
	else if(IsMedic(playerid))
		ShowPlayerDialog(playerid, 116, DIALOG_STYLE_LIST, "DUTY", "Выход на дежурство\nВыбрать скин\nВзять бронежилет\nВзять рацию\nСнаряжение", "Выбрать", "Закрыть");
	
	else if(character_info[playerid][faction] == SAN_FACTION)
		ShowPlayerDialog(playerid, 153, DIALOG_STYLE_LIST, "DUTY", "Выход на дежурство\nВзять рацию\nВзять фотоаппарат\nВыбрать скин", "Выбрать", "Закрыть");
	
	return 1;
}
CMD:acoff(playerid)
{
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	SetPVarInt(playerid, "not_anticheat", 1);
	return 1;
}
CMD:taser(playerid)
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(character_info[playerid][duty_gun_special] == 0)
	{
		character_info[playerid][duty_gun_special] = 23;
		SYS_AME(playerid, "достает тазер");
	}
	else 
	{
		character_info[playerid][duty_gun_special] = 0;
		SYS_AME(playerid, "убирает тазер");
	}
	
	UpdateDutyGuns(playerid);
	return 1;
}
CMD:ticket(playerid, params[])
{
	//if(!InFactionType(playerid, FACTIONTYPE_STATE)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(sscanf(params,"uds[32]", params[0], params[1], params[2])) 
		return SyntaxCMD(playerid, "/ticket [id] [сумма] [причина]");
	
	if(!IsPlayerLoged(params[0])) 
	{
		//printf("/ticket %d %d %d", params[0], params[1], params[2]);
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
	}
	if(params[1] < 1 || params[1] > 100000) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверную сумму штрафа!");
	if(!AddTicket(params[0], params[1], params[2])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Произошла ошибка!");
	new str[180];
	format(str, sizeof(str), "выписывает %s штраф в %d$", sendername(params[0], true), params[1]);
	cmd_me(playerid, str);
	//fmsg(playerid, str);
	new dialogstr[197+25+11+32];
	format(dialogstr, sizeof(dialogstr), "{FF6347}Вам выписан штраф!\n{ffffff}%s выписал вам штраф в %d$\nПричина: {b1b1b1}%s\n\n(Вы сможете оплатить его в любом банкомате, в противном случае вы будете получать в два раза меньше зарплаты!)", sendername(playerid), params[1], params[2]);
	ShowPlayerDialog(params[0], 0, DIALOG_STYLE_MSGBOX, "Штраф", dialogstr, "Закрыть", "");
	return 1;
}

CMD:vticket(playerid, params[])
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	new vehnumber[11], vehsumm, vehreason[32];
	if(sscanf(params,"s[11]ds[32]", vehnumber, vehsumm, vehreason)) return SyntaxCMD(playerid, "/vticket [номерной знак] [сумма] [причина]");
	for(new v; v<MAX_VEHICLES; v++)
	{
		if(strlen(veh_info[v][number]) < 4) continue;
		if(!strcmp(vehnumber, veh_info[v][number], true, 11))
		{
			for(new i; i<MAX_PLAYERS; i++)
			{
				if(veh_info[v][owner] == character_info[i][id])
				{
					new str[32+11+11];
					format(str, sizeof(str), "%d %d %s", i, vehsumm, vehreason);
					//printf(str);
					cmd_ticket(playerid, str);
					return 1;
				}
			}
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Автомобиль не найден!");
	return 1;
}

CMD:m(playerid, params[])
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	if(sscanf(params,"s[124]", params[0])) return SyntaxCMD(playerid, "/m [text]");
	new Float:x, Float:y, Float:z;
	for(new i=0; i<MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, xyz);
		if(character_info[playerid][faction] == ntop(veh_info[i][owner]) && PlayerToPoint(3.0, playerid, xyz)) 
		{
			new str[180];
			
			format(str, sizeof(str), "[Mегафон] %s: %s", sendername(playerid, true), params[0]);
			linebreak(playerid, str, 30.0, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
			GetPlayerPos(playerid, xyz);
			foreach(new p : Player) 
			{
				if(!IsPlayerLoged(p)) continue;
				if(!PlayerToPoint(25.0, p, xyz)) continue;
				PlayerPlaySoundEx(playerid,15800);
				//PlayerPlaySound(playerid, 1141, 0.0,0.0,1.0);
			}
			return 1;
		}
		
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится рядом с фракционным транспортом!");
	return 1;
}

CMD:rb(playerid)
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	if(character_info[playerid][duty_gun_special] != 0)
	{
		character_info[playerid][duty_gun_special] = 0;
		SYS_AME(playerid, "убирает помповый дробовик");
		UpdateDutyGuns(playerid);
		return 1;
	}
	new Float:x, Float:y, Float:z;
	for(new i=0; i<MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, xyz);
		if(character_info[playerid][faction] == ntop(veh_info[i][owner]) && PlayerToPoint(3.0, playerid, xyz)) 
		{
			character_info[playerid][duty_gun_special] = 25;
			SYS_AME(playerid, "достает помповый дробовик");
			UpdateDutyGuns(playerid);
			return 1;
		}
		
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится рядом с фракционным транспортом!");
	return 1;
}
CMD:arrest(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	if(sscanf(params,"dd", params[0], params[1])) 
		return SyntaxCMD(playerid, "/arrest [ID] [Минуты]");
	
	new j = -1;
	for(new i; i<sizeof(ArrestZone); i++) 
	{
		if(PlayerToPoint(3.0, playerid, ArrestZone[i][posX], ArrestZone[i][posY], ArrestZone[i][posZ]) && GetPlayerVirtualWorld(playerid) == ArrestZone[i][VW] && GetPlayerInterior(playerid) == ArrestZone[i][Interior]) 
		{
			j = i;
			break;
		}
	}
	if(j <= -1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не в месте ареста!");	
    
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
    
	if(params[1] < 1 || params[1] > 180) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество минут!");
	
	new floatxyz;
	GetPlayerPos(params[0], xyz);
	if(!PlayerToPoint(5.0, playerid, xyz)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть рядом с игроком!");
    
	new str[124];
	format(str, sizeof(str), "посадил игрока %s в тюрьму.", sendername(params[0], true));
	cmd_me(playerid, str);
	
	character_info[params[0]][jail_time] = params[1]*60;
    SetPlayerPosEx(params[0], ArrestZone[j][posRX], ArrestZone[j][posRY], ArrestZone[j][posRZ], ArrestZone[j][VW], ArrestZone[j][Interior]);
	
	character_info[params[0]][su] = 0;

	new qu[62+22];
	format(qu, sizeof(qu), "UPDATE `characters` SET `su`=0,`su_reason`='-' WHERE id='%d'", character_info[params[0]][id]);
	mysql_function_query(dbHandle, qu, false, "", "");	
	
	return 1;
}
CMD:unjail(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/unjail [ID]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	
	if(character_info[params[0]][jail_time] > 0) 
		character_info[params[0]][jail_time] = 2;
	
	if(character_info[params[0]][ajail_time] > 0) 
		character_info[params[0]][ajail_time] = 2;
	
	new str[124];
	format(str, sizeof(str), "%s(%d) выпустил игрока %s(%d) из тюрьмы",
	player_info[playerid][login], playerid, character_info[params[0]][name], params[0]);
   	AdminMessage(str);
	return 1;
}
CMD:cuff(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(GetPVarInt(playerid, "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду, пока сами находитесь в наручниках!");
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/cuff [ID]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	if(playerid == params[0]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду по отношению к себе!");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid,xyz);
	if(!PlayerToPoint(2.5, params[0], x, y, z)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь рядом с выбраным игроком!");
	new str[128];
	format(str, sizeof(str), "закрепляет наручники на руках %s", sendername(params[0], true));
	SYS_AME(playerid, str);
	SetPlayerAttachedObject(params[0], MAX_ATTACH+2, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000); 
    SetPlayerSpecialAction(params[0], SPECIAL_ACTION_CUFFED); 
	SetPVarInt(params[0], "cuffed", 1);
	return 1;
}
CMD:uncuff(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(GetPVarInt(playerid, "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду, пока сами находитесь в наручниках!");
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/uncuff [ID]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	if(playerid == params[0]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду по отношению к себе!");
	if(!GetPVarInt(params[0], "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Персонаж не в наручниках!");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid,xyz);
	if(!PlayerToPoint(2.5, params[0], x, y, z)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь рядом с выбраным игроком!");
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	
	new str[128];	
	format(str, sizeof(str), "снимает наручники с рук %s", sendername(params[0], true));
	SYS_AME(playerid, str);
	
	RemovePlayerAttachedObject(params[0], MAX_ATTACH+2);
	SetPlayerSpecialAction(params[0], SPECIAL_ACTION_NONE);
	DeletePVar(params[0], "cuffed");
	FreePlayer(params[0], 1);
	return 1;
}
CMD:incar(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(GetPVarInt(playerid, "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду, пока сами находитесь в наручниках!");
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"ud", params[0],params[1])) return SyntaxCMD(playerid, "/incar [ID] [1/2/3]");
	if(!GetPVarInt(params[0], "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не в наручниках!");
	if(IsPlayerInAnyVehicle(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок уже находится в машине!");
	if(params[1] < 1 || params[1] > 3) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте номер места от 1 до 3!");
	new Float:x, Float:y, Float:z, v;
	GetPlayerPos(playerid,xyz);
	if(!PlayerToPoint(2.5, params[0], x, y, z)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь рядом с выбраным игроком!");
	for(new i=0; i<MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, xyz);
		if(character_info[playerid][faction] == ntop(veh_info[i][owner]) && PlayerToPoint(3.0, playerid, xyz)) 
		{
			v = i;
			break;
		}
		
	}
	foreach(new p : Player)
	{
		if(!IsPlayerLoged(p) || GetPlayerVehicleID(p) != v) continue;
		if(GetPlayerVehicleSeat(p) == params[1]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Выбранное место занято!"); 
	}
	PutInCar(params[0], v, params[1]);
	FreePlayer(params[0], 0);
	new str[128];	
	format(str, sizeof(str), "заталкивает %s в транспорт", sendername(params[0]));
	SYS_AME(playerid, str);
	return 1;
}
CMD:outcar(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(GetPVarInt(playerid, "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду, пока сами находитесь в наручниках!");
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/outcar [ID]");
	if(!GetPVarInt(params[0], "cuffed")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не в наручниках!");
	if(!IsPlayerInAnyVehicle(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не находится в машине!");
	RemovePlayerFromVehicle(params[0]);
	FreePlayer(params[0], 1);
	return 1;
}

CMD:frisk(playerid, params[])
{
	if(sscanf(params,"u", params[0])) 
		return SyntaxCMD(playerid, "/frisk [ID]");
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	if(!IsAdmin(playerid, 2, true)) 
		return FriskPlayer(playerid, params[0], false);
	
	new floatxyz;
	GetPlayerPos(playerid, xyz);
	if(!PlayerToPoint(5.0, params[0], xyz)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть рядом с выбранным игроком!");
	
	if(IsCop(playerid) && IsDuty(playerid))
		return FriskPlayer(playerid, params[0]);
	else
	{
		SCM(playerid, COLOR_PAPAYA, "Запрос на обыск был отправлен!");
		new str[128];
		format(str, sizeof(str), "%s хочет обыскать вас.\nВы согласны?", sendername(playerid));
		SetPVarInt(params[0], "frisk", playerid+1);
		ShowPlayerDialog(params[0], 86, DIALOG_STYLE_MSGBOX, "Обыск", str, "Согласен", "Отказываюсь");
	}
	return 1;
}

CMD:take(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/take [ID]");
	if(playerid == params[0]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете применить действие к себе!");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	SetPVarInt(playerid, "targetid", params[0]+1);
	ShowPlayerDialog(playerid, 87, DIALOG_STYLE_LIST, "Забрать", "Оружие\nНаркотики\nЛицензию на вождение", "Выбрать", "Отмена"); 
	return 1;
}
CMD:checkplate(playerid, params[])
{
	if(sscanf(params,"d", params[0])) 
	{
		for(new i=1; i<MAX_VEHICLES; i++)
		{
			new Float:x, Float:y, Float:z;
			GetVehiclePos(i, xyz);
			if(GetPlayerVehicleID(playerid) != i && PlayerToPoint(3.0, playerid, xyz))
			{
				params[0] = i;
				break;
			}
			if(i == MAX_VEHICLES-1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Рядом нет транспорта или вы сидите внутри!");
		}
	}
	else 
	{
		new Float:x, Float:y, Float:z;
		GetVehiclePos(params[0], xyz);
		if(!PlayerToPoint(5.0, playerid, xyz)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко от этого автомобиля!");
	}
	
	new str[180];
	format(str, sizeof(str), "Номер %s [ID: %d]: %s", VehicleNames[GetVehicleModel(params[0])-400], params[0], veh_info[params[0]][number]);
	SCM(playerid, COLOR_YELLOW_GREEN, str);
	return 1;
}
CMD:callsign(playerid, params[])
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(!isPlayerDriver(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится за рулем!");
	new v = GetPlayerVehicleID(playerid);
	if(veh_info[v][owner] >= 0 || character_info[playerid][faction] != ntop(veh_info[v][owner])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете установить маркировку на этот транспорт!");
	if(sscanf(params,"s[32]", params[0]))
	{
		if(IsValidDynamic3DTextLabel(veh_info[v][callsign]))
		{
			//printf("[debug_3d] callsign remove [1]");
			SCM(playerid, COLOR_GREEN, ">{Ffffff} Вы удалили маркировку транспорта!");
			DestroyDynamic3DTextLabel(veh_info[v][callsign]);
			veh_info[v][callsign] = Text3D:INVALID_3DTEXT_ID;
		}
		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} /callsign [текст]");
		return 1;
	}
	if(!IsValidDynamic3DTextLabel(veh_info[v][callsign]))
	{
		veh_info[v][callsign] = CreateDynamic3DTextLabel(params[0], COLOR_GRAY_EE, -0.8, -2.65, -0.3, 5.0, INVALID_PLAYER_ID, v);
		SCM(playerid, COLOR_GREEN, ">{ffffff} Вы создали маркировку транспорта!");
		//printf("[debug_3d] callsign create");
	}
	else 
	{
		//printf("[debug_3d] callsign remove [2]");
		SCM(playerid, COLOR_GREEN, "Вы удалили маркировку транспорта!");
		DestroyDynamic3DTextLabel(veh_info[v][callsign]);
		veh_info[v][callsign] = Text3D:INVALID_3DTEXT_ID;
	}
	return 1;
}

ALTX:boot("/trunk");
CMD:boot(playerid, params[])
{
	new v = 0;
	if(IsPlayerInAnyVehicle(playerid)) v = GetPlayerVehicleID(playerid);
	else
	{
		for(new i=1; i<MAX_VEHICLES; i++)
		{
			new Float:x, Float:y, Float:z;
			GetCoordBootVehicle(i, xyz);
			if(PlayerToPoint(2.0, playerid, xyz) && !IsMoto(i))
			{
				v = i;
				break;
			}
		}
		if(v == 0) return 1;
	}

	if(!InFactionId(playerid, SASD_FACTION) && !InFactionId(playerid, LSPD_FACTION) && !InFactionId(playerid, LSSD_FACTION))
	{
		if(veh_info[v][owner] < 0 && character_info[playerid][faction] != ntop(veh_info[v][owner]) || veh_info[v][owner] > 0 && veh_info[v][owner] != character_info[playerid][id] && !searchitemcount(playerid, 149, veh_info[v][id])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете открыть багажник этого транспорта!");
	}

	if(veh_info[v][boot] == false)
	{
		veh_info[v][boot] = true;
		UpdateVehParams(v);
		GameTextForPlayer(playerid, "~g~BOOT OPEN", 1000, 3);
		//printf("%s open boot %d", sendername(playerid), veh_info[v][id]);
		SYS_AME(playerid, "открыл багажник.");
	}
	else if(veh_info[v][boot] == true)
	{
		veh_info[v][boot] = false;
		UpdateVehParams(v);
		GameTextForPlayer(playerid, "~r~BOOT CLOSED", 1000, 3);
		SYS_AME(playerid, "закрыл багажник");
	}
    return 1;
}

CMD:bonnet(playerid, params[])
{
	new v = 0;
	if(IsPlayerInAnyVehicle(playerid)) v = GetPlayerVehicleID(playerid);
	else
	{
		for(new i=1; i<MAX_VEHICLES; i++)
		{
			new Float:x, Float:y, Float:z;
			GetCoordBonnetVehicle(i, xyz);
			if(PlayerToPoint(2.0, playerid, xyz))
			{
				v = i;
				break;
			}
		}
		if(v == 0) return 1;
	}

	if(veh_info[v][owner] < 0 && character_info[playerid][faction] != ntop(veh_info[v][owner]) || veh_info[v][owner] > 0 && veh_info[v][owner] != character_info[playerid][id]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете открыть капот этого транспорта!");
	if(veh_info[v][boonet] == false)
	{
		veh_info[v][boonet] = true;
		UpdateVehParams(v);
		GameTextForPlayer(playerid, "~g~BOONET OPEN", 1000, 3);
		SYS_AME(playerid, "открыл капот.");
	}
	else if(veh_info[v][boonet] == true)
	{
		veh_info[v][boonet] = false;
		UpdateVehParams(v);
		GameTextForPlayer(playerid, "~r~BOONET CLOSED", 1000, 3);
		SYS_AME(playerid, "закрыл капот");
	}
    return 1;
}
CMD:buyfill(playerid)
{
	for(new i; i<sizeof(GasStations); i++)
	{
		if(PlayerToPoint(5.0, playerid, GasStations[i][posX],GasStations[i][posY],GasStations[i][posZ]))
		{
			if(takemoney(playerid, FILL_PRICE*110, "buy fill") == 1) 
			{
				giveitem(playerid, 113);
				prop_info[GetLocalIdProp(GasStations[i][idprop])][money] += (FILL_PRICE*100)-(FILL_PRICE*100/4);
				SCM(playerid, COLOR_GREEN, ">{ffffff} Вы купили канистру!");
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
		}
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь на заправке!");
	}
}
CMD:fill(playerid, params[])
{
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/fill [топливо]");
	new v;
	if(IsPlayerInAnyVehicle(playerid)) v = GetPlayerVehicleID(playerid);
	else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть в автомобиле чтобы использовать эту команду!");
	if(veh_info[v][filling] > 0.0 || IsBike(v)) return 1;
	for(new i; i<sizeof(GasStations); i++)
	{
		if(PlayerToPoint(5.0, playerid, GasStations[i][posX],GasStations[i][posY],GasStations[i][posZ]))
		{
			if(params[0] > floatround(101.0-veh_info[v][fuel], floatround_tozero))
			{
				new str[52];
				format(str, sizeof(str), "Вы ввели слишком большое количество! (макс %d)", floatround(101.0-veh_info[v][fuel], floatround_tozero));
				SCM(playerid, COLOR_GRAY, str);
				return 1;
			}
			if(params[0] <= 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество");
			if(takemoney(playerid, FILL_PRICE*params[0], "filling") == 1) 
			{
				prop_info[GetLocalIdProp(GasStations[i][idprop])][money] += (FILL_PRICE*params[0])-(FILL_PRICE*params[0]/4);
				SCM(playerid, COLOR_PAPAYA, "Вы начали заправку автомобиля!");
				veh_info[v][filling] = params[0];
				Freeze(playerid, 100);
				veh_info[v][engine] = false;
				UpdateVehParams(v);
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь на заправке!");
	return 1;
}

CMD:su(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"us[64]", params[0], params[1])) return SyntaxCMD(playerid, "/su [id] [причина]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	if(character_info[params[0]][su] > 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот игрок уже находится в розыске. Вы можете использовать /unsu.");
	character_info[params[0]][su] = character_info[playerid][id];
	format(character_info[params[0]][su_reason], 32, "%s", params[1]);
	new str[128];
	format(str, sizeof(str), "объявляет %s в розыск (%s)", character_info[params[0]][name], character_info[params[0]][su_reason]);
	fmsg(playerid, str); 
	
	new temp[40];
	mysql_real_escape_string(character_info[params[0]][su_reason], temp);
	new qu[62+22+40];
	format(qu, sizeof(qu), "UPDATE `characters` SET `su`=%d,`su_reason`='%s' WHERE id='%d'", character_info[params[0]][su], temp, character_info[params[0]][id]);
	mysql_function_query(dbHandle, qu, false, "", "");
	return 1;
}
CMD:unsu(playerid, params[])
{
	
	if(!IsDuty(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	
	if(sscanf(params,"u", params[0])) 
		return SyntaxCMD(playerid, "/unsu [id]");
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	if(character_info[params[0]][su] <= 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот игрок не находится в розыске!");
	
	new str[128];
	format(str, sizeof(str), "прекращает розыск %s", character_info[params[0]][name]);
	fmsg(playerid, str); 
	character_info[params[0]][su] = 0;
	new qu[62+22];
	format(qu, sizeof(qu), "UPDATE `characters` SET `su`=0,`su_reason`='-' WHERE id='%d'", character_info[params[0]][id]);
	mysql_function_query(dbHandle, qu, false, "", "");	
	return 1;
}

CMD:cctv(playerid, params[])
{
	new ADMIN_LEVEL = 5;
	if(IsAdmin(playerid, ADMIN_LEVEL, true))
	{
		if(!InFactionType(playerid, FACTIONTYPE_STATE) || !IsDuty(playerid)) 
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	}
	new action[24], secoption[180];
	if(sscanf(params,"s[24]S(NULL)[128]", action, secoption))
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /cctv [действие]");
		if(player_info[playerid][admin] >= ADMIN_LEVEL) 
		{
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} [A] * /cctv create [description]");
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} [A] * /cctv destroy [id]");
		}
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /cctv list");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /cctv detalis [id]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /cctv find [id]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		return 1;
	}
	if(CompareStrings(action, "create"))
	{
		if(IsAdmin(playerid, ADMIN_LEVEL)) return 1;
		new info[180];
		sscanf(secoption,"s[180]",info);
		if(!strcmp(info, "NULL", true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} /cctv create [description]");
		if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit")) return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");
		SetPVarString(playerid, "cctv_create_desc", info);
		new Float:angle, Float:x,Float:y,Float:z, obj;
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);
		x += floatsin(-angle, degrees);
		y += floatcos(-angle, degrees);
		obj = CreateDynamicObject(CCTV_OBJ, x+2.5, y+2.5, z, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

		character_info[playerid][editobject] = obj;
		character_info[playerid][type_editobj] = 8;
		EditDynamicObject(playerid, obj);
	}
	if(CompareStrings(action, "destroy"))
	{
		if(IsAdmin(playerid, ADMIN_LEVEL)) return 1;
		new shadow_number;
		if(sscanf(params,"{s[64]}d",shadow_number)) return SyntaxCMD(playerid, "/cctv remove [id]");
		new qu[64];
		format(qu, sizeof(qu), "DELETE FROM `cctv` WHERE id=%d", shadow_number);
		mysql_function_query(dbHandle, qu, false, "", "");
		mysql_function_query(dbHandle, "SELECT * FROM cctv WHERE 1", true, "OnLoadCCTV", "");
	}
	if(CompareStrings(action, "list"))
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________ CCTV ________________");
		for(new c; c<MAX_CCTV; c++)
		{
			if(cctv_info[c][id] <= 0) continue;
			new i, Float:x, Float:y;
			x = cctv_info[c][posX];
			y = cctv_info[c][posY];
			for(; i != sizeof(gSAZones); i++ )
			{
				if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) break;
			}


			new str[180];
			format(str, sizeof(str), "CAM #%d: %s - %s", cctv_info[c][id], gSAZones[i][SAZONE_NAME], cctv_info[c][description]);
			SCM(playerid, COLOR_WHITE, str);
		}
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
	}
	if(CompareStrings(action, "detalis"))
	{
		new shadow_number;
		if(sscanf(params,"{s[64]}d",shadow_number)) return SyntaxCMD(playerid, "/cctv detalis [id]");
		for(new c; c<MAX_CCTV; c++)
		{
			if(cctv_info[c][id] == shadow_number)
			{
				new i, Float:x, Float:y;
				x = cctv_info[c][posX];
				y = cctv_info[c][posY];
				for(; i != sizeof(gSAZones); i++ )
				{
					if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) break;
				}

	
				new str[180];
				format(str, sizeof(str), "CAM #%d: %s - %s", cctv_info[c][id], gSAZones[i][SAZONE_NAME], cctv_info[c][description]);
				SCM(playerid, COLOR_GREEN, str);
				return 1;
			}
		}
	}
	if(CompareStrings(action, "find"))
	{
		new shadow_number;
		if(GetPVarInt(playerid, "search_checkpoint")) return DestroyCheckpoint(playerid);
		if(sscanf(params,"{s[64]}d",shadow_number)) return SyntaxCMD(playerid, "/cctv detalis [id]");
		for(new i; i<MAX_CCTV; i++)
		{
			if(cctv_info[i][id] == shadow_number)
			{
				DestroyCheckpoint(playerid);
				SetPVarInt(playerid, "search_checkpoint", 1);
				SetPlayerCheckpoint(playerid, cctv_info[i][posX], cctv_info[i][posY], cctv_info[i][posZ], 3.0);
				return 1;
			}
		}
	}
	return 1;
}
CMD:arecord(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	new action[24], secoption[180];
	if(sscanf(params,"s[24]S(NULL)[128]", action, secoption))
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /arecord [действие]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /arecord show [id]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /arecord create [id] [причина]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /arecord remove [номер записи]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		return 1;
	}
	
	if(CompareStrings(action, "show"))
	{
		new targetid;
		if(sscanf(params,"{s[64]}d",targetid)) return SyntaxCMD(playerid, "/arecord show [id]");
		if(!IsPlayerLoged(targetid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
		LoadArecords(playerid, targetid);
	}
	else if(CompareStrings(action, "create"))
	{
		new targetid, rreason[64];
		if(sscanf(secoption,"us[64]", targetid, rreason)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} /arecord create [id] [причина]");
		if(!IsPlayerLoged(targetid)) return 1;
		
		new str[180];
		format(str, sizeof(str), "добавил ARECORD на %s (%s)", sendername(targetid), rreason);
		fmsg(playerid, str);

		
		new qu[57+11+64];
		mysql_real_escape_string(rreason, rreason);
		format(qu, sizeof(qu), "INSERT INTO `arecord`(`characterid`, `text`) VALUES (%d,'%s')", character_info[targetid][id], rreason);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	else if(CompareStrings(action, "remove"))
	{
		new rnumber;
		if(sscanf(params,"{s[64]}d",rnumber)) return SyntaxCMD(playerid, "/arecord remove [номер записи]");
		
		new str[180];
		format(str, sizeof(str), "удалил ARECORD #%d", rnumber);
		fmsg(playerid, str);
		
		new qu[32+11];
		format(qu, sizeof(qu), "DELETE FROM `arecord` WHERE id=%d", rnumber);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	else cmd_arecord(playerid, "");
	return 1;
}
ALTX:arecord("/arecords");

CMD:apb(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(!IsDuty(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	
	new action[24], secoption[180];
	if(sscanf(params,"s[24]S(NULL)[128]", action, secoption))
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /apb [действие]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /apb list [1-... страница]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /apb show [номер записи]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /apb create  [>|информация]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /apb remove  [номер записи]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		return 1;
	}
	
	if(CompareStrings(action, "list"))
	{
		new page;
		if(sscanf(params,"{s[64]}d",page)) page = 1;
		if(page < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте положительное число!");
		GameTextForPlayer(playerid, "~r~LOADING...", 10000, 3);
		new qu[128];
		format(qu, sizeof(qu), "SELECT `id`, `desc`, `violation` FROM  `apb` ORDER BY  `apb`.`id` DESC LIMIT %d,15", (page-1)*15);
		mysql_function_query(dbHandle, qu, true, "OnAPBList", "ii", playerid, page);
	}
	
	else if(CompareStrings(action, "show"))
	{
		new shadow_number;
		if(sscanf(params,"{s[64]}d",shadow_number)) return SyntaxCMD(playerid, "/apb show [номер записи]");
		new qu[135];
		format(qu, sizeof(qu), "SELECT apb.desc, apb.violation, apb.date, characters.name FROM `apb` JOIN `characters` ON apb.chid=characters.id WHERE apb.id=%d", shadow_number);
		mysql_function_query(dbHandle, qu, true, "OnAPBShow", "ii", playerid, shadow_number);
	}
	else if(CompareStrings(action, "remove"))
	{
		new shadow_number;
		if(sscanf(params,"{s[64]}d",shadow_number)) return SyntaxCMD(playerid, "/apb remove [номер записи]");
		new qu[128];
		format(qu, sizeof(qu), "SELECT `id` FROM `apb` WHERE id=%d", shadow_number);
		mysql_function_query(dbHandle, qu, true, "OnAPBDelete", "ii", playerid, shadow_number);
	}
	else if(CompareStrings(action, "create"))
	{
		new info[180];
		sscanf(secoption,"s[180]",info);
		if(!strcmp(info, "NULL", true)) return SyntaxCMD(playerid, "/apb create [>|преступление]");
		new tmpa[2][128];
		//explode(tmpa, info, "|");
		mysql_real_escape_string(info, info);
		sscanf(info, "p<|>s[128]s[128]",
				tmpa[0],
				tmpa[1]);
		if(strlen(tmpa[1]) < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} /apb create [>|преступление]");
		new qu[256+128];
		fmsg(playerid, "создает новый APB.");
		format(qu, sizeof(qu), "INSERT INTO `apb`(`desc`, `violation`, `chid`) VALUES ('%s', '%s', %d)", tmpa[0], tmpa[1], character_info[playerid][id]);
		mysql_function_query(dbHandle, qu, false, "", "");
		SCM(playerid, COLOR_GREEN, "APB создан!");
	}
	
	else cmd_apb(playerid, "");
	return 1;
}
CMD:whereim(playerid)
{
	SendClientMessageEx(playerid, -1, "%d %d", GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
	SendClientMessageEx(playerid, -1, "%d %d", character_info[playerid][VW], character_info[playerid][Interior]);
	return 1;
}

CMD:addatm(playerid)
{
	if(IsAdmin(playerid, 5)) 
		return 1;
	
	if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
		return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");

	new Float:angle, Float:x,Float:y,Float:z, obj;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	x += floatsin(-angle, degrees);
	y += floatcos(-angle, degrees);
	obj = CreateDynamicObject(ATM_OBJ, x+2.5, y+2.5, z, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

	character_info[playerid][editobject] = obj;
	character_info[playerid][type_editobj] = 7;
	EditDynamicObject(playerid, obj);	
	return 1;
}

CMD:atm(playerid)
{
	if(!InATM(playerid)) return 1;
	Freeze(playerid, 500);
	new str[512];
	format(str, sizeof(str), "Снять деньги со счета\tБаланс: %d$\nПоложить деньги на счет\nПеревести деньги на другой счет\nОплата штрафов", character_info[playerid][bank], character_info[playerid][money]);
	ShowPlayerDialog(playerid, 92, DIALOG_STYLE_TABLIST, "Банкомат", str, "Выбрать", "Закрыть");
	return 1;
}

CMD:editint(playerid, params[])
{
	if(IsAdmin(playerid, 4)) return 1;
	if(sscanf(params,"dd", params[0], params[1])) return SyntaxCMD(playerid, "/editint [id prop] [intid]");
	prop_info[GetLocalIdProp(params[0])][serverint] = params[1];
	new qu[46+22];
	format(qu, sizeof(qu), "UPDATE property SET `serverint`=%d WHERE id=%d", params[1], params[0]);
	mysql_function_query(dbHandle, qu, false, "", "");
	return 1;
}
CMD:addprop(playerid)
{
	if(IsAdmin(playerid, 4)) return 1;
	
	if(!GetPVarInt(playerid, "addprop_step2"))
	{
		new str[256];
		format(str, sizeof(str), "Тип имущества: %s\nСтоимость имущества: %d$\nСохранить координаты и начать выбор интерьера", property[GetPVarInt(playerid, "addprop_type")], GetPVarInt(playerid, "addprop_price"));
		ShowPlayerDialog(playerid, 97, DIALOG_STYLE_TABLIST, "Создание имущества", str,"Выбрать", "Отмена");
	}
	else 
	{
		ShowPlayerDialog(playerid, 98, DIALOG_STYLE_TABLIST, "Создание имущества", "Вернуться назад\nУстановить интерьер", "Выбрать", "Отмена");
	}
	return 1;
}

CMD:tune(playerid)
{
	//new v = GetPlayerVehicleID(playerid);
	switch(IsFixPickup(playerid))
	{
		case 0: return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду здесь!");
		case 2: ShowPlayerDialog(playerid, 102, DIALOG_STYLE_TABLIST, "TUNE", "Установить новый замок\nУстановить сигнализаци\nУстановить диски", "Выбрать", "Отмена");
	}
	
	return 1;
}

CMD:fingerprint(playerid)
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	new bool:sys_param=true;
	for(new i=0; i<MAX_ITEM_DROP; i++)
	{
		if(PlayerToPoint(1.5, playerid, items_drop[i][posX],items_drop[i][posY],items_drop[i][posZ]) && GetPlayerVirtualWorld(playerid) == items_drop[i][vworld] && GetPlayerInterior(playerid) == items_drop[i][inter] && items_drop[i][id] > 0)
		{
			if(sys_param)
			{
				SYS_AME(playerid, "снимает отпечатки с предметов на земле");
				SCM(playerid, COLOR_GREEN, "Отпечатки пальцев: ");
				sys_param = false;
			}
			new str[180];
			format(str, sizeof(str), "%s(%d) > %s", senderitems(items_drop[i][myitem]), items_drop[i][item_count], items_drop[i][charactername]);
			SCM(playerid, COLOR_GRAY, str);
		}
	}
	if(sys_param) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Ничего не найдено!");
	return 1;
}
ALTX:fingerprint("/fp");


CMD:po(playerid)
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
	
	if(InFactionId(playerid, LSPD_FACTION) || InFactionId(playerid, SASD_FACTION) || InFactionId(playerid, LSSD_FACTION)) 
	{
		new str[512];
		for(new i; i<sizeof(PoliceAttaches); i++) format(str, sizeof(str), "%s%s\n", str, senderitems(PoliceAttaches[i]));
		ShowPlayerDialog(playerid, 107, DIALOG_STYLE_LIST, "ATTACHES", str, "Выбрать", "Отмена");
	}
	else if(IsMedic(playerid)) 
	{
		new str[512];
		for(new i; i<sizeof(LSFDAttaches); i++) format(str, sizeof(str), "%s%s\n", str, senderitems(LSFDAttaches[i]));
		ShowPlayerDialog(playerid, 107, DIALOG_STYLE_LIST, "ATTACHES", str, "Выбрать", "Отмена");
	}
	return 1;
}

CMD:fobj(playerid, params[])
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
	
	new action[24], secoption[180];
	if(sscanf(params,"s[24]S(NULL)[128]", action, secoption))
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /fobj [действие]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /fobj create");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /fobj remove [id]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /fobj list");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /fobj text3D");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		return 1;
	}
	
	if(CompareStrings(action, "create"))
	{
		//new page;
		//if(sscanf(params,"{s[64]}d",page)) page = 1;
		
		new str[1028];
		for(new i; i<sizeof(FactionObjects); i++)
		{
			format(str, sizeof(str), "%s%d. %s\n", str, i+1, FactionObjects[i][Name]);
		}
		ShowPlayerDialog(playerid, 109, DIALOG_STYLE_LIST, "FACTION OBJECTS", str, "Выбрать", "Отмена");
	}
	else if(CompareStrings(action, "list"))
	{
		for(new i; i<20; i++)
		{
			if(fobj_info[playerid][fObj][i] < 1) continue;
			new str[128];
			new f;
			for(f=0; f<sizeof(FactionObjects); f++)
			{
				if(FactionObjects[f][Model] == fobj_info[playerid][Model][i]) break;
			}
			format(str, sizeof(str), "%d. %s", i+1, FactionObjects[f][Name]);
			SCM(playerid, COLOR_GREEN, str);
		}
	}
	else if(CompareStrings(action, "remove"))
	{
		new slot;
		if(sscanf(params,"{s[64]}d", slot)) return SyntaxCMD(playerid, "/fobj remove [id]");
		slot--;
		if(fobj_info[playerid][fObj][slot] < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы выбрали свободный слот!");
		fobj_info[playerid][Model][slot] = 0;
		if(IsValidDynamic3DTextLabel(fobj_info[playerid][f3d][slot])) 
		{
			DestroyDynamic3DTextLabel(fobj_info[playerid][f3d][slot]);
			//printf("[debug_3d] delete fobj remove");
			fobj_info[playerid][f3d][slot] = Text3D:INVALID_3DTEXT_ID;
		}
		DestroyDynamicObject(fobj_info[playerid][fObj][slot]);
		fobj_info[playerid][fObj][slot] = 0;
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы удалили объект!");
	}
	else if(CompareStrings(action, "text3D"))
	{
		//printf(">>> %d", GetPVarInt(playerid, "fobj_3d_off"));
		if(!GetPVarInt(playerid, "fobj_3d_off"))
		{
			for(new i; i<20; i++)
			{
				if(fobj_info[playerid][fObj][i] < 1) continue;
				if(IsValidDynamic3DTextLabel(fobj_info[playerid][f3d][i])) 
				{
					//printf("[debug_3d] delete fobj off 3d");
					DestroyDynamic3DTextLabel(fobj_info[playerid][f3d][i]);
					fobj_info[playerid][f3d][i] = Text3D:INVALID_3DTEXT_ID;
				}
			}
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы выключили отображение 3D текста объектов!");
			SetPVarInt(playerid, "fobj_3d_off", 1);
		}
		else 
		{
			for(new i; i<10; i++)
			{
				if(fobj_info[playerid][fObj][i] < 1) continue;
				new floatxyz;
				GetDynamicObjectPos(fobj_info[playerid][fObj][i], xyz);
				
				new str[24];
				format(str, sizeof(str), "#%d", i+1);
				if(!IsValidDynamic3DTextLabel(fobj_info[playerid][f3d][i]))
				{ 
					fobj_info[playerid][f3d][i] = CreateDynamic3DTextLabel(str, COLOR_GRAY_EE, xyz, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
					//printf("[debug_3d] create fobj on 3d");
				}
			}
			SetPVarInt(playerid, "fobj_3d_off", 0);
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы включили отображение 3D текста объектов!");
		}
	}
	else cmd_fobj(playerid, "");
	
	return 1;
}

CMD:wire(playerid, params[])
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
	new action[24], secoption[180];
	if(sscanf(params,"s[24]S(NULL)[128]", action, secoption))
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /wire [действие]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /wire on [number]");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} * /wire off");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} __________________________________");
		return 1;
	}
	else if(CompareStrings(action, "on"))
	{
		new numberphone;
		if(sscanf(params,"{s[64]}d", numberphone)) return SyntaxCMD(playerid, "/wire on [number]");
		SetPVarInt(playerid, "wire_phone", numberphone);
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы начали прослушку телефона!");
	}
	else if(CompareStrings(action, "off"))
	{
		DeletePVar(playerid, "wire_phone");
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы закончили прослушку телефона!");
	}
	else cmd_wire(playerid, "");
	return 1;
}

CMD:serverintadd(playerid, params[])
{
	if(sscanf(params,"s[32]", params[0])) return SyntaxCMD(playerid, "/serverintadd [название]"); 
	if(IsAdmin(playerid, 6)) return 1;
	new floatxyz, interior = GetPlayerInterior(playerid);
	GetPlayerPos(playerid, xyz);
	new qu[256];
	mysql_real_escape_string(params[0], params[0]);
	format(qu, sizeof(qu), "INSERT INTO `serverint`(`name`, `posX`, `posY`, `posZ`, `intid`) VALUES ('%s', %f, %f, %f, %d)", params[0], xyz, interior);
	mysql_function_query(dbHandle, qu, true, "", "");
	UpdateServerInt();
	SCM(playerid, COLOR_GREEN, "Вы добавили новый интерьер!");
	return 1;
}

CMD:heal(playerid, params[])
{
	if(sscanf(params,"d", params[0])) 
		return SyntaxCMD(playerid, "/heal [id]");
	
	if(params[0] == playerid) 
		return 1;
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	new Float:x, Float:y, Float:z;
	GetPlayerPos(params[0], x,y,z);
	
	if(!PlayerToPoint(5.0, playerid, x,y,z) || GetPlayerVirtualWorld(playerid) != GetPlayerVirtualWorld(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко от этого персонажа!");
	
	if(character_info[params[0]][wound] == 3) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Персонаж мертв!");
	
	if(!IsMedic(playerid) && !IsCop(playerid)) 
		if(deleteitem(playerid, 1, 1) != 1) 
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет аптечки!");
	
	if(character_info[params[0]][wound] != 0) set_wound(params[0], 0);
	else if(character_info[params[0]][wound] == 0) SetPlayerHealth(params[0], 100);
	
	SCM(playerid, COLOR_GREEN, "Вы вылечили персонажа!");
	new str[40];
	format(str, sizeof(str), "%s вылечил вас!", sendername(playerid));
	SCM(params[0], COLOR_GREEN, str);
	format(str, sizeof(str), "вылечил %s", sendername(params[0]));
	SYS_AME(playerid, str);
	return 1;
}
CMD:unmask(playerid)
{
	if(MaskOff(playerid)) 
	{
		giveitem(playerid, 112);
		SCM(playerid, COLOR_GREEN, "Вы сняли маску!");
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет маски на лице!");
}
CMD:mask(playerid)
{
	new slot = finditem(playerid, 122);
	if(slot == -1) 
		return Sound_Fail(playerid);
	useitem(playerid, slot);
	return 1;
}
CMD:maskid(playerid, params[])
{
	if(IsAdmin(playerid, 4)) return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/maskid [ID маски]");
	GetPlayerByMaskId(playerid, params[0]);
	return 1;
}
CMD:fines(playerid, params[])
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду!");
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/fines [ID]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");

	new bool:isset=false, str[(32+18+11)*MAX_TICKETS] = "Сумма\tПричина\tДата\n";
	for(new i; i<MAX_TICKETS; i++)
	{
		if(ticket_info[params[0]][i][tId] <= 0) continue;
		if(!isset) isset=true;
		format(str, sizeof(str), "%s$%d\t%s\t%s\n", str, ticket_info[params[0]][i][tSumm], ticket_info[params[0]][i][tReason], ticket_info[params[0]][i][tDate]);
	}
	if(!isset) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У выбранного игрока нет штрафов!");
	else ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Штрафы", str, "Закрыть", "");
	
	return 1;
}
CMD:gunrack(playerid)
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду!");
	new v = IsFactionCar(playerid);
	if(v <= -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле фракционного автомобиля!");
	new str[180];
	format(str, sizeof(str), "> Слот 1: %s | Слот 2: %s | Слот 3: %s", Items[GetItemByGun(veh_info[v][gunrack_1_gun])][Name], Items[GetItemByGun(veh_info[v][gunrack_2_gun])][Name], Items[GetItemByGun(veh_info[v][gunrack_3_gun])][Name]);
	SCM(playerid, COLOR_PAPAYA, str);
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /placegun чтобы положить оружие в слот или /takegun чтобы достать его.");
	return 1;
}
CMD:placegun(playerid, params[0])
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду!");
	new v = IsFactionCar(playerid);
	if(v <= -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле фракционного автомобиля!");
	if(sscanf(params,"d", params[0]))
	{
		if(GetPlayerWeapon(playerid) == character_info[playerid][duty_gun_1]) params[0] = 1;
		else if(GetPlayerWeapon(playerid) == character_info[playerid][duty_gun_2]) params[0] = 2;
		else if(GetPlayerWeapon(playerid) == character_info[playerid][duty_gun_3]) params[0] = 3;
		else return SyntaxCMD(playerid, "/placegun [слот оружия] (Либо в руке должно находится нужное оружие)");
	}
	if(params[0] < 1 || params[0] > 3) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы указали неверный слот!");
	new str[128];
	switch(params[0])
	{
		case 1: 
		{
			if(veh_info[v][gunrack_1_gun] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Слот в автомобиле не пустой!");
			if(character_info[playerid][duty_gun_1] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет оружия в этом слоте!");
			veh_info[v][gunrack_1_gun] = character_info[playerid][duty_gun_1];
			character_info[playerid][duty_gun_1] = 0;

			format(str, sizeof(str), "закрепляет %s в крепление крузера", Items[GetItemByGun(veh_info[v][gunrack_1_gun])][Name]);
			SYS_AME(playerid, str);
		}
		case 2: 
		{	
			if(veh_info[v][gunrack_2_gun] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Слот в автомобиле не пустой!");
			if(character_info[playerid][duty_gun_2] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет оружия в этом слоте!");
			veh_info[v][gunrack_2_gun] = character_info[playerid][duty_gun_2];
			veh_info[v][gunrack_2_ammo] = character_info[playerid][duty_ammo_2];
			character_info[playerid][duty_gun_2] = 0;
			character_info[playerid][duty_ammo_2] = 0;
			
			format(str, sizeof(str), "закрепляет %s в крепление крузера", Items[GetItemByGun(veh_info[v][gunrack_2_gun])][Name]);
			SYS_AME(playerid, str);
		}
		case 3:
		{
			if(veh_info[v][gunrack_3_gun] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Слот в автомобиле не пустой!");
			if(character_info[playerid][duty_gun_3] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет оружия в этом слоте!");
			veh_info[v][gunrack_3_gun] = character_info[playerid][duty_gun_3];
			veh_info[v][gunrack_3_ammo] = character_info[playerid][duty_ammo_3];
			character_info[playerid][duty_gun_3] = 0;
			character_info[playerid][duty_ammo_3] = 0;
			
			format(str, sizeof(str), "закрепляет %s в крепление крузера", Items[GetItemByGun(veh_info[v][gunrack_3_gun])][Name]);
			SYS_AME(playerid, str);
		}
	}
	UpdateDutyGuns(playerid);
	
	return 1;
}
CMD:takegun(playerid, params[])
{
	if(!IsCop(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду!");
	new v = IsFactionCar(playerid);
	if(v <= -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле фракционного автомобиля!");
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/takegun [слот с оружием]");
	if(params[0] < 1 || params[0] > 3) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы указали неверный слот!");
	new str[128];
	
	switch(params[0])
	{
		case 1:
		{
			if(veh_info[v][gunrack_1_gun] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Слот в автомобиле пустой!");
			if(character_info[playerid][duty_gun_1] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас есть оружие в этом слоте!");
			character_info[playerid][duty_gun_1] = veh_info[v][gunrack_1_gun];
			veh_info[v][gunrack_1_gun] = 0;
			
			format(str, sizeof(str), "снимает %s из крепление крузера", Items[GetItemByGun(character_info[playerid][duty_gun_1])][Name]);
			SYS_AME(playerid, str);
		}
		case 2:
		{
			if(veh_info[v][gunrack_2_gun] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Слот в автомобиле пустой!");
			if(character_info[playerid][duty_gun_2] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас есть оружие в этом слоте!");
			character_info[playerid][duty_gun_2] = veh_info[v][gunrack_2_gun];
			character_info[playerid][duty_ammo_2] = veh_info[v][gunrack_2_ammo];
			veh_info[v][gunrack_2_gun] = 0;
			veh_info[v][gunrack_2_ammo] = 0;
			
			format(str, sizeof(str), "снимает %s из крепление крузера", Items[GetItemByGun(character_info[playerid][duty_gun_2])][Name]);
			SYS_AME(playerid, str);
		}
		case 3:
		{
			if(veh_info[v][gunrack_3_gun] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Слот в автомобиле пустой!");
			if(character_info[playerid][duty_gun_3] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас есть оружие в этом слоте!");
			character_info[playerid][duty_gun_3] = veh_info[v][gunrack_3_gun];
			character_info[playerid][duty_ammo_3] = veh_info[v][gunrack_3_ammo];
			veh_info[v][gunrack_3_gun] = 0;
			veh_info[v][gunrack_3_ammo] = 0;
			
			format(str, sizeof(str), "снимает %s из крепление крузера", Items[GetItemByGun(character_info[playerid][duty_gun_3])][Name]);
			SYS_AME(playerid, str);
		}
	}
	UpdateDutyGuns(playerid);
	return 1;
}
CMD:changecharacter(playerid)
{
	//return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Команда временно отключена!");
	OnPlayerDisconnectEx(playerid, 999);
	return 1;
}
ALTX:changecharacter("/relogin", "/characterchange"); 

CMD:color(playerid)
{
	if(!InFaction(playerid)) 
		return 1;
	if(!GetPVarInt(playerid, "OFF_COLOR")) 
		SetPVarInt(playerid, "OFF_COLOR", 1);
	else 
		DeletePVar(playerid, "OFF_COLOR");
	
	UpdatePlayerColor(playerid);
	SCM(playerid, COLOR_GREEN, "Вы обновили цвет!");
	return 1;
}
CMD:give(playerid, params[])
{
	if(sscanf(params,"u", params[0])) 
		return SyntaxCMD(playerid, "/give [id персонажа]");
	
	if(character_info[playerid][gun] == 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас в руках нет оружия!");
	
	if(character_info[params[0]][gun] != 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У выбранного персонажа уже есть оружие!");
	
	if(character_info[params[0]][lvl] < 5) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У игрока недостаточно часов в игре!");
	
	new floatxyz;
	GetPlayerPos(params[0], xyz);
	
	if(!PlayerToPoint(5.0, playerid, xyz)) 
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть рядом с игроком!");
	
	new str[128];
	format(str, sizeof(str), "передал %s %s", Items[GetItemByGun(character_info[playerid][gun])][Name], sendername(params[0], true));
	cmd_ame(playerid, str);
	
	character_info[params[0]][gun] = character_info[playerid][gun];
	character_info[params[0]][ammo] = character_info[playerid][ammo]; 
	character_info[playerid][gun] = 0;
	character_info[playerid][ammo] = 0;
	ResetPlayerWeapons(playerid);
	ResetPlayerWeapons(params[0]);
	
	if(character_info[params[0]][gun] != 41) 
		GivePlayerWeapon(params[0], character_info[params[0]][gun], character_info[params[0]][ammo]);
	else 
		GivePlayerWeapon(params[0], character_info[params[0]][gun], 999999999);
	
	// 
	return 1;
}

CMD:o(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"s[128]", params[0])) return SyntaxCMD(playerid, "/o [текст]");
	new str[180];
	format(str, sizeof(str), "[OOC] {F5DEB3}%s: %s", player_info[playerid][login], params[0]);
	SendClientMessageToAll(COLOR_MSGSERVER, str);
	return 1;
}
CMD:oic(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"s[128]", params[0])) return SyntaxCMD(playerid, "/oic [текст]");
	new str[180];
	//printf("%s (%d)", params[0], strlen(params[0]));
	format(str, sizeof(str), "[OIC]{F5DEB3} %s", params[0]);
	SendClientMessageToAll(COLOR_MSGSERVER, str);
	//printf("[GLOBAL IC] %s: %s", player_info[playerid][login], params[0]);
	return 1;
}
CMD:amute(playerid, params[])
{
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/amute [id]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	new str[180];
	
	if(GetPVarInt(params[0], "amute"))
	{
		format(str, sizeof(str), "%s[%d] снял админ-молчанку с %s[%d]", player_info[playerid][login], playerid, player_info[params[0]][login], params[0]);
		AdminMessage(str);
		DeletePVar(params[0], "amute");
	}
	else 
	{
		format(str, sizeof(str), "%s[%d] выдал админ-молчанку %s[%d]", player_info[playerid][login], playerid, player_info[params[0]][login], params[0]);
		AdminMessage(str);
		SetPVarInt(params[0], "amute", 1);
	}
	return 1;
}
CMD:version(playerid, params[])
{
	new text[10];
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	if(sscanf(params,"s[10]", text)) return Sound_Fail(playerid);
	
	new File:opnfile; // создаём файловую переменную
	opnfile=fopen("server_version.txt",io_readwrite); /* открываем файл file с возможностью чтения и записываем его идентификатор в opnfile */
	fwrite(opnfile, text); 
	fclose(opnfile); // закрываем работу с файлом
	Sound_Succ(playerid);
	UpdateGameModeText();
	return 1; // возвращаем 1 давая знать что всё прошло успешно
}


CMD:carfix(playerid)
{
	new v;
	if(GetPlayerVehicleID(playerid) <= 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть в автомобиле!");
	
	v = GetPlayerVehicleID(playerid);
	
	
	switch(IsFixPickup(playerid))
	{
		case 0: return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду здесь!");
		case 1:
		{
			if(veh_info[v][owner] >= 0) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть в автомобиле фракции!");
			veh_info[v][fuel] = 100.0;
			RepairVehicle(v);
			SetVehicleHealth(v, 999);
		}
		case 2:
		{
			if(takemoney(playerid, 200, "spray") != 1) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!"); 
			RepairVehicle(v);
			SetVehicleHealth(v, 999);
		}
	}

	return 1;
}
CMD:afixcar(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	new v;
	if(sscanf(params,"d", v)) 
	{
		if(GetPlayerVehicleID(playerid) <= 0) return SyntaxCMD(playerid, "/afixcar [id car]");
		v = GetPlayerVehicleID(playerid);
	}
	SetVehicleHealth(v, 999);
	RepairVehicle(v);
	SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы починили автомобиль!");
	return 1;
}
CMD:buycar(playerid)
{
	if(!ShowCarShowroom(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле автосалона!");
	return 1;
}

CMD:cmdsearch(playerid, params[])
{
	if(sscanf(params,"s[25]", params[0])) 
	{
		SyntaxCMD(playerid, "/cmdsearch [команда]");
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны искать команду вместе со знаком / (слэш)!");
	}
	for(new i; i<sizeof(HelpInfo); i++)
	{
		if(CompareStrings(HelpInfo[i][CMDTEXT], params[0]))
		{
			new str[180];
			format(str, sizeof(str), "[CMDSEARCH] {F5DEB3}%s: {b1b1b1}%s", HelpInfo[i][CMDTEXT], HelpInfo[i][CMDDESC]);
			SCM(playerid, COLOR_GRAY, str);
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Команда не найдена в справке!");
	return 0;
}



CMD:changesex(playerid)
{
	if(character_info[playerid][sex] != 1 && character_info[playerid][sex] != 2)
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Ошибка при смене пола. Сообщите об этом на форум в тех. раздел.");
	
	if(player_info[playerid][donate] < Donate[6][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены пола нехватает %d р.", Donate[6][Price] - player_info[playerid][donate]);

	new playersex[8],str[128];
	if(character_info[playerid][sex] == 1)
		playersex = "женский";
	else
		playersex = "мужской";
	
	format(str, sizeof(str), "Стоимоть услуги %d р.\nВы подтверждаете смену пола персонажа на %s?",Donate[6][Price], playersex);
	Dialog_Show(playerid, SexChange, DIALOG_STYLE_MSGBOX, "Подтверждение смены пола.", str, "Да", "Нет");
	
	return 1;
}


CMD:changebd(playerid)
{
	if(player_info[playerid][donate] < Donate[7][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены дня рождения нехватает %d р.", 55 - player_info[playerid][donate]);
	
	Dialog_Show(playerid, changebirthday, DIALOG_STYLE_INPUT, "Смена даты рождения.", "Введите дату нового дня рождения.\nФормат: день/месяц/год", "Продолжить", "Отмена");
	return 1;
}

CMD:changeucp(playerid)
{
	if(player_info[playerid][donate] < Donate[5][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены UCP логина нехватает %d р.", Donate[6][Price] - player_info[playerid][donate]);
	
	new str[128];
	format(str, sizeof(str), "Стоимоть услуги %d р.\nВведите новый логин.",Donate[6][Price]);
	Dialog_Show(playerid, changeucp, DIALOG_STYLE_INPUT, "Смена UCP логина.", str, "Продолжить", "Отмена");
	return 1;
}

CMD:donate(playerid)
{
	new str_header[32];
	new str[256] = "Услуга\tСтоимость\n";
	format(str_header, sizeof(str_header), "Баланс: %d руб.", player_info[playerid][donate]);
	for(new i; i<sizeof(Donate); i++) 
		format(str, sizeof(str), "%s%s\t%d руб.\n", str, Donate[i][Name], Donate[i][Price]);
	
	ShowPlayerDialog(playerid, 121, DIALOG_STYLE_TABLIST_HEADERS, str_header, str, "Выбрать", "Отмена");
	return 1;
}
CMD:changename(playerid, params[])
{
	if(!IsPremium(playerid, PREMIUM_GOLD))
	{
		if(player_info[playerid][changename] <= 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете изменить ник!");
	}
	if(sscanf(params,"s[24]", params[0])) 
	{
		SyntaxCMD(playerid, "/changename [новый ник]");
		if(player_info[playerid][changename] > 0)
		{
			new str[128];
			format(str, sizeof(str), "> У вас имеется возможность сменить ник %d раз", player_info[playerid][changename]);
			SCM(playerid, COLOR_PAPAYA, str);
		}
		return 1; 
	}
	if(strfind(params[0],"%",true)!=-1 || strfind(params[0], "'",true) !=-1 || strfind(params[0], "=",true) !=-1 || strfind(params[0], " ",true) !=-1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы использовали запрещенные символы!");
	
	SetPVarString(playerid, "changename", params[0]);
	SetPVarInt(playerid, "changename_qu", 1);
	new str[180];
	format(str, sizeof(str), "запрашивает смену ника на %s (/acceptchangename %d)", params[0], playerid);
	PlayerLog(playerid, str);
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы подали заявку на смену ника.");
	return 1;
}

CMD:acceptchangename(playerid, params[])
{
	if(IsAdmin(playerid, 3)) 
		return 1;
	
	if(sscanf(params,"u", params[0])) 
		return SyntaxCMD(playerid, "/acceptchangename [ID]");
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	if(player_info[params[0]][changename] <= 0 && !IsPremium(params[0], PREMIUM_GOLD)) 
		return SCM(params[0], COLOR_MSGERROR, ">{FFFFFF} Игрок не может изменить ник!");
	
	if(!GetPVarInt(params[0], "changename_qu")) 
		return 1;
	
	new change_name[24];
	GetPVarString(params[0], "changename", change_name, 24);
	new oldname[25];
	format(oldname, sizeof(oldname), "%s", character_info[params[0]][name]);
	format(character_info[params[0]][name], 24, "%s", change_name);
	SetPlayerNameEx(params[0], character_info[params[0]][name]);
	
	new str[256];
	format(str, sizeof(str), "UPDATE `characters` SET `name`='%s' WHERE id=%d", character_info[params[0]][name], character_info[params[0]][id]);
	mysql_function_query(dbHandle, str, false, "", "");
	format(str, sizeof(str), "INSERT INTO `changename`(`characterid`, `oldname`, `newname`, `adminid`) VALUES (%d, '%s', '%s', %d)", character_info[params[0]][id], oldname, character_info[params[0]][name], player_info[playerid][id]);
	mysql_function_query(dbHandle, str, false, "", "");

	if(!IsPremium(params[0], PREMIUM_GOLD)) 
		player_info[params[0]][changename]--;
	
	format(str, sizeof(str), "{ffffff} %s(%d) подтвердил смену ника %s > %s", player_info[playerid][login], playerid, oldname, character_info[params[0]][name]);
	AdminLog(str);
	SCM(params[0], COLOR_GREEN, str);
	DeletePVar(playerid, "changename");
	DeletePVar(playerid, "changename_qu");
	return 1;
}

ALTX:sellcar("/sc");
CMD:sellcar(playerid, params[])
{
	new v = GetPlayerVehicleID(playerid);
	if(v <= 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны сидеть в нужном транспорте!");
	
	if(veh_info[v][owner] <= 0 || veh_info[v][owner] != character_info[playerid][id]) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Это не ваш автомобиль!");
	
	if(sscanf(params,"ud", params[0], params[1])) 
	{
		new vehmodel = GetVehicleModel(v);
		for(new i; i<sizeof(BuyCars); i++) 
		{
			//printf("%d | %d == %d", i, BuyCars[i][Model], vehmodel);
			if(BuyCars[i][Model] == vehmodel) 
			{
				SetPVarInt(playerid, "veh_price", BuyCars[i][Price] / 2);
				SetPVarInt(playerid, "veh_id", v);
				break;
			}
		}
		
		new str[201];
		format(str, sizeof(str), "{FF6347}Вы действительно хотите продать автомобиль государству?\n{FFFFFF}Продав автомобиль государству вы получите: {33AA33}%d$\n\n\n{b1b1b1}Для продажи игроку используйте /sellcar [id] [цена]", GetPVarInt(playerid, "veh_price"));
		ShowPlayerDialog(playerid, 122, DIALOG_STYLE_MSGBOX, "Продажа автомобиля государству", str, "Согласен", "Отмена");
		return 1;
	}
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	if(params[1] < 1 || params[1] > 1000000) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверная цена!");
	if(IsMaximumCars(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Выбранный игрок больше не может иметь автомобиль!");
	new floatxyz;
	GetPlayerPos(playerid, xyz);
	if(!PlayerToPoint(5.0, params[0], xyz)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");
	SetPVarInt(params[0], "sellcar_playerid", playerid+1);
	SetPVarInt(params[0], "sellcar_vehid", v);
	SetPVarInt(params[0], "sellcar_price", params[1]);
	new str[180];
	format(str, sizeof(str), ">{FFFFFF} Вы предложили %s купить у вас автомобиль за %d$", sendername(params[0]), params[1]);
	SCM(playerid, COLOR_MSGSERVER, str);
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} > Не покидайте автомобиль, иначе предложение перестанет быть активным!");
	format(str, sizeof(str), "{FFFFFF}%s предложил вам приобрести его автомобиль!\nМарка автомобиля: %s\nЦена: %d$", sendername(playerid), VehicleNames[GetVehicleModel(v)-400], params[1]);
	ShowPlayerDialog(params[0], 123, DIALOG_STYLE_MSGBOX, "Покупка автомобиля", str, "Согласен", "Отмена"); 
	return 1;
}
CMD:setdonate(playerid, params[])
{
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	if(sscanf(params,"ud", params[0], params[1])) SyntaxCMD(playerid, "/setdonate [ID] [SUMM]");
	if(params[1] < 1) return 1;
	player_info[params[0]][donate] = params[1];
	Sound_Succ(playerid);
	return 1;
}
CMD:givedonate(playerid, params[])
{
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	if(sscanf(params,"ud", params[0], params[1])) SyntaxCMD(playerid, "/setdonate [ID] [SUMM]");
	player_info[params[0]][donate] += params[1];
	Sound_Succ(playerid);
	return 1;
}
CMD:flashbang(playerid)
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	for(new i = 0; i<MAX_PROP; i++)
	{
		if(PlayerToPoint(1.5, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid])
		{
			if(!prop_info[i][lock])
			{
				GameTextForPlayer(playerid, "~g~FLASHED!!!", 2000, 3);
				cmd_me(playerid, "закидывает световую гранату в здание.");
				foreach(new p : Player)
				{
					if(i == GetLocalIdProp(character_info[p][prop]) && character_info[p][prop] != 0777777)
					{
						if(character_info[p][wound] <= 1) 
						{
							SetPVarInt(p, "Flashed", 1);
							PlayerTextDrawHide(p, FullMonitor[p]);
							PlayerTextDrawBoxColor(p, FullMonitor[p], COLOR_WHITE);
							PlayerTextDrawBackgroundColor(p, FullMonitor[p], COLOR_WHITE);
							PlayerTextDrawShow(p, FullMonitor[p]);
							set_wound(p, 1);
							SetTimerEx("knockout", 35000, false, "i", p);
							GameTextForPlayer(p, "~r~FLASHED!!!", 2000, 3);
						}
						SCM(p, COLOR_ME, "В помещение залетела световая граната.");
					}
				}
				return 1;
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Дверь дома закрыта!");
		}
	}
	return 1;
}

CMD:ram(playerid)
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	for(new i = 0; i<MAX_PROP; i++)
	{
		if(PlayerToPoint(1.5, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid])
		{
			if(prop_info[i][lock])
			{
				GameTextForPlayer(playerid, "~g~OPEN", 2000, 3);
				prop_info[i][lock] = false;
				cmd_me(playerid, "взламывает замок имущества");
				return 1;
			}
			else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Дверь дома уже открыта!");
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле двери!");
	return 1;
}

CMD:vram(playerid)
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	
	new v = 0;
	if(IsPlayerInAnyVehicle(playerid)) v = GetPlayerVehicleID(playerid);
	else
	{
		for(new i=1; i<MAX_VEHICLES; i++)
		{
			new Float:x, Float:y, Float:z;
			GetCoordBootVehicle(i, xyz);
			if(PlayerToPoint(2.0, playerid, xyz) && !IsMoto(i))
			{
				v = i;
				break;
			}
		}
		if(v == 0) return 1;
	}

	if(veh_info[v][boot] == false)
	{
		veh_info[v][boot] = true;
		UpdateVehParams(v);
		GameTextForPlayer(playerid, "~g~BOOT OPEN", 1000, 3);
		SYS_AME(playerid, "вскрыл багажник.");
	}
	return 1;
}

CMD:ships(playerid)
{
	if(!InFactionType(playerid, 1)) 
		return 1;
				
	for(new i; i<10; i++)
	{
		if(fobj_info[playerid][fObj][i] > 0) continue;
		
		new Float:angle, Float:x,Float:y,Float:z, obj;

		GetPlayerPos(playerid, xyz); 
        GetPlayerFacingAngle(playerid,angle); 
		
		if(!GetPVarInt(playerid, "fobj_3d_off"))
		{
			new str[24];
			format(str, sizeof(str), "#%d", i+1);
			fobj_info[playerid][f3d][i] = CreateDynamic3DTextLabel(str, COLOR_GRAY_EE, x,y,z, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
			//printf("[debug_3d] create ships");
		}
		
		obj = CreateDynamicObject(2899, x, y, z-0.9, 0.0, 0.0, angle, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

		fobj_info[playerid][Model][i] = 2899;
		fobj_info[playerid][fObj][i] = obj;
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы создали объект!");
		cmd_bomb(playerid);
		SYS_AME(playerid, "установил шипы");
		break;
	}
	return 1;
}

ALTX:ships("/ship");

CMD:boombox(playerid)
{
	if(!GetPVarInt(playerid, "PlacedBB")) 
		return SendClientMessage(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не устанавливали бумбокс!");
	
	ShowPlayerDialog(playerid, 128, DIALOG_STYLE_LIST, "Бумбокс", "Убрать бумбокс\nНастроить волну", "Выбрать", "Отмена");
	
	return 1;
}

ALTX:enter("/exit");
CMD:enter(playerid)
{
	if(character_info[playerid][lock])
		return 1;
		//return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Доступно раз в несколько секунд!");
	
	if(character_info[playerid][jail_time] > 0 || character_info[playerid][ajail_time] > 0) 
		return 1;
	
	if(isPlayerDriver(playerid))
	{
		if(character_info[playerid][faction] != 0)
			GoToVehEnter(playerid);
	}
	
	if(GetPlayerVehicleID(playerid) > 0) 
		return 1;
	
	if(GetPVarInt(playerid, "Freezed") && GetPVarInt(playerid, "enter_block")) 
		return 1;
	
	SetPVarInt(playerid, "enter_block", 1);
	
	SetTimerEx("enter_unblock", 2000, false, "d", playerid);
	if(GetPVarInt(playerid, "SkinBuy"))
	{
		DeletePVar(playerid, "SkinBuy");
		SetPlayerSkin(playerid, character_info[playerid][skin]);
	}
	
	for(new i=0; i<MAX_PROP; i++)
	{
		new si = prop_info[i][serverint];
		//printf("[%d] %f %f %f (%d)", i, Interiors[si][posX], Interiors[si][posY], Interiors[si][posZ], si);
	 	if(prop_info[i][id] > 0)
	  	{
			if(PlayerToPoint(1.5, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid])
			{			
		 		if(!prop_info[i][lock])
		 		{
		 			if(prop_info[i][enter_price] > 0) 
		 			{
		 				if(takemoney(playerid, prop_info[i][enter_price], "enter prop") != 1) 
							return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!"); 
		 				
						prop_info[i][money] += prop_info[i][enter_price];
		 			}
				 	return gotoInt(playerid, si, prop_info[i][id]+200);
		 		}
				else
		 			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Дверь закрыта!");
			}
			else if(PlayerToPoint(1.5, playerid, Interiors[si][posX], Interiors[si][posY], Interiors[si][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][id]+200 && GetPlayerInterior(playerid) == Interiors[si][Interior])
			{
				if(GetPVarInt(playerid, "ShotInProp")) 
					DeletePVar(playerid, "ShotInProp");
				return 
					gotoProp(playerid, GetLocalIdProp(prop_info[i][id]));
			}
	  	}
	}

	for(new i=0; i<MAX_ENTERS; i++)
	{
		if(PlayerToPoint(2.0, playerid, enter_info[i][posX],enter_info[i][posY],enter_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == enter_info[i][vworld] && GetPlayerInterior(playerid) == enter_info[i][intid])
		{
			
			SetPlayerPos(playerid, enter_info[i][posXE],enter_info[i][posYE],enter_info[i][posZE]);
			SetPlayerInt(playerid, enter_info[i][intidE]);
			SetPlayerVw(playerid, enter_info[i][vworldE]);
			
			Freeze(playerid, 2000+(GetPlayerPing(playerid)*20));
			return 1;
		}
		else if(PlayerToPoint(2.0, playerid, enter_info[i][posXE],enter_info[i][posYE],enter_info[i][posZE]) && GetPlayerVirtualWorld(playerid) == enter_info[i][vworldE] && GetPlayerInterior(playerid) == enter_info[i][intidE])
		{
			if(devTest(playerid))
			{
				new str[128];
				format(str, sizeof(str), "ENTER ID: %d", enter_info[i][id]);
				devmsg(playerid, str);
			}
			SetPlayerPos(playerid, enter_info[i][posX],enter_info[i][posY],enter_info[i][posZ]);
			SetPlayerInt(playerid, enter_info[i][intid]);
			SetPlayerVw(playerid, enter_info[i][vworld]);
			
			Freeze(playerid, 2000+(GetPlayerPing(playerid)*20));
			return 1;
		}
		
		if(devTest(playerid) && PlayerToPoint(2.0, playerid, enter_info[i][posXE],enter_info[i][posYE],enter_info[i][posZE]) && GetPlayerVirtualWorld(playerid) == enter_info[i][vworldE] && GetPlayerInterior(playerid) == enter_info[i][intidE] || devTest(playerid) && PlayerToPoint(2.0, playerid, enter_info[i][posX],enter_info[i][posY],enter_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == enter_info[i][vworld] && GetPlayerInterior(playerid) == enter_info[i][intid])
		{
			new str[128];
			format(str, sizeof(str), "ENTER ID: %d", i);
			devmsg(playerid, str);
			return 1;
		}
	}
	
	new elevator = -1;
	for(new i; i<MAX_ELEVATORS; i++)
	{
		if(PlayerToPoint(2.5, playerid, elevator_info[i][posX], elevator_info[i][posY], elevator_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == elevator_info[i][VW])
		{
			elevator = elevator_info[i][elevatorid];
			break;
		}
	}
	if(elevator != -1)
	{
		new str[256];
		for(new i; i<MAX_ELEVATORS; i++)
		{
			if(elevator_info[i][elevatorid] == elevator)
			{
				if(PlayerToPoint(2.5, playerid, elevator_info[i][posX], elevator_info[i][posY], elevator_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == elevator_info[i][VW])format(str,sizeof(str), "%s{b1b1b1}%s{ffffff}\n", str,elevator_info[i][desc]);
				else format(str,sizeof(str), "%s%s\n", str,elevator_info[i][desc]);
			}		
		}
		SetPVarInt(playerid, "target_elevator", elevator);
		ShowPlayerDialog(playerid, 114, DIALOG_STYLE_LIST, "Лифт", str, "Выбрать", "Отмена");
	}
	return 1;
}

CMD:delprop(playerid, params[])
{
    if(IsAdmin(playerid, 5)) 
		return 1;
	
	if(sscanf(params,"d", params[0])) 
		return SyntaxCMD(playerid, "/delrpop [id]");
	
	new p = GetLocalIdProp(params[0]);
	if(p == -1) 
		return Sound_Fail(playerid);
	
	new qu[254];
	format(qu, sizeof(qu), "DELETE FROM `property` WHERE id=%d", params[0]);
	mysql_function_query(dbHandle, qu, false, "", "");
	
	mysql_function_query(dbHandle, "SELECT * FROM `property` WHERE 1", true, "load_property", "d", false);
	prop_info[p][id] = 0;
	DestroyDynamicArea(prop_info[p][PropZone]);
	SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы удалили имущество.");
	SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Если имущество не пропало, введите команду /updateprop.");
	//printf("%s delete prop %d", player_info[playerid][login], params[0]);

	return 1;
}

CMD:setprop(playerid, params[])
{
    if(IsAdmin(playerid, 5)) 
		return 1;
    
	if(sscanf(params,"ddd", params[0], params[1], params[2])) 
		return SyntaxCMD(playerid, "/setprop [type] [id interior] [price]");
	
	new Float:x, Float:y, Float:z, vw = GetPlayerVirtualWorld(playerid), interiorid = GetPlayerInterior(playerid); 
	GetPlayerPos(playerid, x,y,z);
	
	if(GetPVarInt(playerid, "addprop_step2"))
	{
		x = GetPVarFloat(playerid, "addprop_step2_posX");
		y = GetPVarFloat(playerid, "addprop_step2_posY");
		z = GetPVarFloat(playerid, "addprop_step2_posZ");
		vw = GetPVarInt(playerid, "addprop_step2_vw");
		interiorid = GetPVarInt(playerid, "addprop_step2_int");
	}
    new qu[254];
	format(qu, sizeof(qu), "INSERT INTO `property`(`posX`, `posY`, `posZ`, `price`,`serverint`, `vw`, `intid`,`type`) VALUES (%f, %f, %f, %d, %d, %d, %d, %d)",
			x,y,z, params[2], params[1], vw, interiorid, params[0]
			);
	mysql_function_query(dbHandle, qu, false, "", "");
	
	//save_prop();
	mysql_function_query(dbHandle, "SELECT * FROM `property` WHERE 1", true, "load_property", "d", false);
	//CreateDynamic3DTextLabel("<В этом месте появится имущество после рестарта>", COLOR_GRAY, x,y,z, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, vw, interiorid, -1, 5.5);
	Sound_Succ(playerid);
	SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы установили имущество в этом месте.");
	SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Если имущество не появилось, введите команду /updateprop.");
	return 1;
}

CMD:updateprop(playerid)
{
	if(IsAdmin(playerid, 6)) 
		return 1;
	
	mysql_function_query(dbHandle, "SELECT * FROM `property` WHERE 1", true, "load_property", "d", false);	
	return 1;
}

CMD:serverint(playerid, params[])
{
    if(IsAdmin(playerid, 2)) return 1;
    if(sscanf(params,"d", params[0])) 
	{
		if(!PVarPosIsset(playerid)) 
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте /serverint [id интерьера]");
		else 
			PVarPosTeleport(playerid);
		return 1;
	}
	if(!PVarPosIsset(playerid))
		PVarPosSave(playerid);
		
	
	new str[14];
	format(str, sizeof(str), "~g~%d", params[0]);
	GameTextForPlayer(playerid, str, 3000, 3);
	
    if(params[0] >= 0) gotoInt(playerid, params[0], 200);
	return 1;
}

CMD:putcar(playerid, params[])
{
	if(IsAdmin(playerid, 6)) 
		return 1;
	
	if(sscanf(params,"ud", params[0],params[1])) 
		return SyntaxCMD(playerid, "/putcar [ID] [CARID]");
	
	
	PutInCar(params[0], params[1], 0);
	return 1;
}

CMD:gmx(playerid, params[])
{
    if(IsAdmin(playerid, 6)) return 1;
	new timegmx;
    if(sscanf(params,"d", params[0])) timegmx = 60;
    else timegmx = params[0];
    Log_Write("logs/admins_log.txt", "[%s] %s start restarting", ReturnDate(), CharacterAndPlayerName(playerid));
	//printf("%s (%s) запускает рестарт.", CharacterAndPlayerName(playerid));
    gmx(timegmx);
	return 1;
}

CMD:aduty(playerid)
{
	if(IsAdmin(playerid, 1, false, false)) 
		return 1;
	
	new str[64];
	if(!IsAduty(playerid)) {
		player_info[playerid][aduty] = true;
	    UpdatePlayerColor(playerid);
	    GameTextForPlayer(playerid, "~g~ADUTY", 3000, 3);

	    format(str,sizeof(str), "%s[%d] заступает на админ-дежурство.", player_info[playerid][login], playerid);
		
		if(player_info[playerid][admin] < 6)
			AdminLog(str);
		
		if(player_info[playerid][admin] >= 2) 
			for(new i; i<MAX_ACHAT; i++) 
				TextDrawShowForPlayer(playerid, ACHAT[i]);
	}
	else {
	    player_info[playerid][aduty] = false;
	    format(str,sizeof(str), "%s[%d] покидает админ дежурство.", player_info[playerid][login], playerid);
		
		if(player_info[playerid][admin] < 6)
			AdminLog(str);
	    
		UpdatePlayerColor(playerid);
	    GameTextForPlayer(playerid, "~r~ADUTY", 3000, 3);
		for(new i; i<MAX_ACHAT; i++) 
			TextDrawHideForPlayer(playerid, ACHAT[i]);
	}
	return 1;
}


CMD:ahelp(playerid)
{
	if(IsAdmin(playerid, 1, false, false)) return 1;
	new str[2400] = "Команда\tДействие\n{ffffff}";
	new new_str[64+25];
	for(new i; i<sizeof(AHelpInfo); i++)
	{
		if(AHelpInfo[i][TYPE] <= player_info[playerid][admin])
		{
			format(new_str, sizeof(new_str), "%s\t%s\n", AHelpInfo[i][CMDTEXT], AHelpInfo[i][CMDDESC]);
			strcat(str, new_str);
		}
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "AHELP", str, "Закрыть", "");
	
	
	return 1;
}
CMD:clearchat(playerid)
{ 
    if(IsAdmin(playerid, 3)) 
		return 1;
	for(new i; i<101; i++) 
	{ 
	SendClientMessageToAll(-1,""); 
	} 
	SendClientMessageToAll(-1, ""); 
	return 1; 
	}

CMD:veh(playerid, params[])
{
    if(IsAdmin(playerid, 3)) 
		return 1;
    
	static
	    vmodel[32],
		color1,
		color2,
		time;

	if (sscanf(params, "s[32]I(-1)I(-1)d", vmodel, color1, color2,time))
	    return SyntaxCMD(playerid, "/veh [id/name] <color 1> <color 2> <min>");
    
	if ((vmodel[0] = GetVehicleModelByName(vmodel)) == 0)
	    return SendErrorMessage(playerid, "Неверно указан ID или название транспорта (400-611)");
    
    new Float:X, Float:Y, Float:Z, Float:Angle;
    GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid,Angle);
	
	X += 2*floatsin(-Angle, degrees);
	Y += 2*floatcos(-Angle, degrees);
	
	new v = CreateVehicleEx(vmodel[0], X, Y, Z, Angle, GetPlayerVirtualWorld(playerid), color1, color2, 50, false, false, false, false);
	veh_info[v][destroy_time] = time*60;
	
	new str[180];
	format(str, sizeof(str), "%s(%d) создал автомобиль MODEL %d", player_info[playerid][login], playerid, vmodel[0]);
 	AdminLog(str);
    return 1;
}
CMD:updatecrimelimit(playerid, params[]) {
	if(IsAdmin(playerid, 6)) return 1;
	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/updatecrimelimit [factionid]");
	UpdateCrimeLimit(params[0]);
	new str[180];
	format(str, sizeof(str), "%s(%d) обновил лимиты фркации %d", player_info[playerid][login], playerid, params[0]);
 	AdminLog(str);

	return 1;
}
CMD:dveh(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/dveh [ID]");
	if(veh_info[params[0]][owner] != 0 && IsAdmin(playerid, 5, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете удалить этот автомобиль!");
	new str[180];
	format(str, sizeof(str), "%s(%d) удалил автомобиль ID %d", player_info[playerid][login], playerid, params[0]);
 	AdminLog(str);
	SCM(playerid, COLOR_GREEN, ">{ffffff} Вы удалили автомобиль!");
	
	if(veh_info[params[0]][owner] != 0)
	{
		new qu[128];
		format(qu, sizeof(qu), "DELETE FROM cars WHERE id=%d", veh_info[params[0]][id]);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	DestroyVehicleEx(params[0]);
	return 1;
}

CMD:vehex(playerid, params[])
{
	//CreateVehicleEx(carid, Float:X, Float:Y, Float:Z, Float:Angle, col1, col2, Float:vfuel, bool:vlock, bool:vengine, bool:vwindows, bool:vlights, vid=-1, vowner=-1)
    if(IsAdmin(playerid, 5)) 
		return 1;
    static
	    vmodel[32];
		
	if(sscanf(params,"s[32]ddd", vmodel, params[1], params[2], params[3])) 
		return SyntaxCMD(playerid, "/veh [id car] [id color 1] [id color 2] [owner]");
    
	if ((vmodel[0] = GetVehicleModelByName(vmodel)) == 0)
	    return SendErrorMessage(playerid, "Неверно указан ID или название транспорта (400-611)");
	
	if(params[1] < 0 || params[1] > 255) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} ID цвета должен быть до 255!");
    
	if(params[2] < 0 || params[2] > 255) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} ID цвета должен быть до 255!");
	

    
    new Float:X, Float:Y, Float:Z, Float:Angle;
    GetPlayerPos(playerid, X, Y, Z);
	GetPlayerFacingAngle(playerid,Angle);
	
	X += 2*floatsin(-Angle, degrees);
	Y += 2*floatcos(-Angle, degrees);
	
	new qu[256];
	format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `col1`, `col2`, `fuel`, `posX`, `posY`, `posZ`, `Angle`, `virtualworld`) VALUES (%d, %d, %d, %d, 100, %f, %f, %f, %f, %d)", 
	vmodel[0], params[3], params[1], params[2],
	X, Y, Z, Angle,GetPlayerVirtualWorld(playerid)
	);
	mysql_function_query(dbHandle, qu, false, "", "");
	format(qu, sizeof(qu), "SELECT * FROM `cars` WHERE owner=%d", params[3]); 
	mysql_function_query(dbHandle, qu, true, "OnLoadCars", "d", -1);
	SCM(playerid, COLOR_GREEN, ">{ffffff} Вы создали автомобиль и присвоили его игроку.");
    return 1;
}


ShowSpeed(playerid)
{
	if(IsBike(GetPlayerVehicleID(playerid))) 
		return 1;
    
	PlayerTextDrawShow(playerid, Textdraw[playerid][0]);
    PlayerTextDrawShow(playerid, Textdraw[playerid][1]);
    PlayerTextDrawShow(playerid, Textdraw[playerid][2]);
    PlayerTextDrawShow(playerid, Textdraw[playerid][3]);
	return 0;
}

HideSpeed(playerid)
{
	if(IsBike(GetPlayerVehicleID(playerid))) 
		return 1;
    
	PlayerTextDrawHide(playerid, Textdraw[playerid][0]);
    PlayerTextDrawHide(playerid, Textdraw[playerid][1]);
    PlayerTextDrawHide(playerid, Textdraw[playerid][2]);
    PlayerTextDrawHide(playerid, Textdraw[playerid][3]);
	return 0;
}
stock GetCar(playerid, bool:incar=false)
{
	for(new i=1; i<MAX_VEHICLES; i++)
	{
	    new Float:x, Float:y, Float:z;
	    GetVehiclePos(i, xyz);
	    if(GetPlayerVehicleID(playerid) == i || !incar && PlayerToPoint(3.0, playerid, xyz)) return i;
	}
	return 0;
}
CMD:park(playerid)
{
	new v;
	if(IsPlayerInAnyVehicle(playerid))
		v = GetPlayerVehicleID(playerid);
	else
		return SCM(playerid, COLOR_RED, ">{ffffff} Доступно внутри транспорта!");
	
	if(v != 0)
	{
		if(veh_info[v][owner] < 0 && InFactionId(playerid, ntop(veh_info[v][owner]), true) || veh_info[v][owner] > 0 && veh_info[v][owner] == character_info[playerid][id])
		{
			if(veh_info[v][id] < 1) 
				return SCM(playerid, COLOR_RED, ">{ffffff} Внутренняя ошибка. У транспорта отсутствует глобальный ID!");
			
			new qu[256];
			new Float:x, Float:y, Float:z, Float:angle, _vworld_ = GetVehicleVirtualWorld(v), Float:health;
			GetVehiclePos(v, xyz);
			GetVehicleHealth(v, health);
			GetVehicleZAngle(v, angle);
			format(qu, sizeof(qu), "UPDATE `cars` SET posX=%f, posY=%f, posZ=%f, Angle=%f, virtualworld=%d, health=%f WHERE id='%d'", xyz,angle,_vworld_, health, veh_info[v][id]);
			mysql_function_query(dbHandle, qu, false, "", "");
			
			format(qu, sizeof(qu), "SELECT * FROM `cars` WHERE id='%d'", veh_info[v][id]);
			DestroyVehicleEx(v);
			mysql_function_query(dbHandle, qu, true, "OnLoadCars", "d", playerid);
			SCM(playerid, COLOR_GREEN, ">{ffffff} Вы припарковали свой автомобиль!");
		}
		else 
			SCM(playerid, COLOR_RED, ">{ffffff} У вас нет доступа для парковки данного автомобиля!");
	}
	else 
		SCM(playerid, COLOR_RED, ">{ffffff} Этот автомобиль не привязан к игроку или фракции. Он будет удален после рестарта и припарковать его невозможно!");
	return 1;
}
CMD:carlist(playerid, params[])
{
	new p;
	if(IsAdmin(playerid, 2, true)) p = playerid;
	else if(sscanf(params,"u", p)) p = playerid;

	new str[64];
	SCM(playerid, COLOR_MSGERROR, "{FFFFFF} ________________");
	for(new v; v<MAX_VEHICLES; v++)
	{
		if(veh_info[v][owner] > 0 && veh_info[v][owner] == character_info[p][id])
		{
			format(str, sizeof(str), "%s [ID: %d]", VehicleNames[GetVehicleModel(v)-400], v);
			SCM(playerid, COLOR_YELLOW_GREEN, str);
		}
	}
	SCM(playerid, COLOR_MSGERROR, "{FFFFFF} ________________");
	return 1;
}
CMD:gotocar(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	new v;
	if(sscanf(params,"d", v)) return SyntaxCMD(playerid, "/gotocar [id car]");
	
	new floatxyz;
	GetVehiclePos(v, xyz);
	SetPlayerPosEx(playerid, xyz, GetVehicleVirtualWorld(v), 0);
	return 1;
}
CMD:gotoprop(playerid, params[]) {
	if(IsAdmin(playerid, 2)) return 1;
	new globalPropid;
	if(sscanf(params,"d", globalPropid)) return SyntaxCMD(playerid, "/gotoprop [id]");

	new p = GetLocalIdProp(globalPropid);
	SetPlayerPosEx(playerid, prop_info[p][posX], prop_info[p][posY], prop_info[p][posZ], prop_info[p][vworld], prop_info[p][intid]);
	return 1;
}

CMD:getherecar(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	new v;
	if(sscanf(params,"d", v)) return SyntaxCMD(playerid, "/getherecar [id car]");
	
	new floatxyz;
	GetPlayerPos(playerid, xyz);
	
	SetVehiclePos(v, xyz);
	
	SetVehiclePos(v, xyz);
	SetVehicleVirtualWorld(v, GetPlayerVirtualWorld(playerid));
	foreach(new p : Player)
	{
		if(!IsPlayerLoged(p)) 
			continue;
		if(GetPlayerVehicleID(p) == v)
			SetPlayerVw(p, GetPlayerVirtualWorld(playerid));
	}
	return 1;
}

CMD:damages(playerid, params[])
{
    if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/damages [id игрока/часть ника]");
	new str[1024] = "{AFAFAF}Часть тела\t{AFAFAF}Оружие\t{AFAFAF}Урон\t{AFAFAF}Время\n";
	for(new i = 0; i<MAX_DAMAGES; i++)
	{
	    if(character_info[params[0]][damages][part][i] != -1)
	    {
	        new bodypart[25] = "UNKNOWN", gunname[25] = "UNKNOWN";
			if(character_info[params[0]][damages][part][i] == 3) bodypart = "Торс";
			else if(character_info[params[0]][damages][part][i] == 4) bodypart = "Пах";
			else if(character_info[params[0]][damages][part][i] == 5) bodypart = "Левая рука";
			else if(character_info[params[0]][damages][part][i] == 6) bodypart = "Правая рука";
			else if(character_info[params[0]][damages][part][i] == 7) bodypart = "Левая нога";
			else if(character_info[params[0]][damages][part][i] == 8) bodypart = "Правая нога";
			else if(character_info[params[0]][damages][part][i] == 9) bodypart = "Голова";

			if(character_info[params[0]][damages][gun_id][i] == 0) gunname = "Рукопашный бой";
			else if(character_info[params[0]][damages][gun_id][i] == 1) gunname = "Кастет";
			else if(character_info[params[0]][damages][gun_id][i] == 2) gunname = "Клюшка";
			else if(character_info[params[0]][damages][gun_id][i] == 3) gunname = "Резиновая дубинка";
			else if(character_info[params[0]][damages][gun_id][i] == 4) gunname = "Нож";
			else if(character_info[params[0]][damages][gun_id][i] == 5) gunname = "Бита";
			else if(character_info[params[0]][damages][gun_id][i] == 6) gunname = "Лопата";
			else if(character_info[params[0]][damages][gun_id][i] == 7) gunname = "Кий";
			else if(character_info[params[0]][damages][gun_id][i] == 8) gunname = "Катана";
			else if(character_info[params[0]][damages][gun_id][i] == 9) gunname = "Бензопила";
			else if(character_info[params[0]][damages][gun_id][i] == 10) gunname = "Дилдо";
			else if(character_info[params[0]][damages][gun_id][i] == 11) gunname = "Дилдо";
			else if(character_info[params[0]][damages][gun_id][i] == 12) gunname = "Дилдо";
			else if(character_info[params[0]][damages][gun_id][i] == 13) gunname = "Дилдо";
			else if(character_info[params[0]][damages][gun_id][i] == 14) gunname = "Цветы";
			else if(character_info[params[0]][damages][gun_id][i] == 15) gunname = "Трость";
			else if(character_info[params[0]][damages][gun_id][i] == 16) gunname = "Граната";
			else if(character_info[params[0]][damages][gun_id][i] == 17) gunname = "Дымовая граната";
			else if(character_info[params[0]][damages][gun_id][i] == 18) gunname = "Коктейль молотова";
			else if(character_info[params[0]][damages][gun_id][i] == 22) gunname = "Colt";
			else if(character_info[params[0]][damages][gun_id][i] == 23) gunname = "SD Pistol";
			else if(character_info[params[0]][damages][gun_id][i] == 24) gunname = "Desert Eagle";
			else if(character_info[params[0]][damages][gun_id][i] == 25) gunname = "Shotgun";
			else if(character_info[params[0]][damages][gun_id][i] == 26) gunname = "Spawn-Off Shotgun";
			else if(character_info[params[0]][damages][gun_id][i] == 27) gunname = "Стрёмная штука";
			else if(character_info[params[0]][damages][gun_id][i] == 28) gunname = "UZI";
			else if(character_info[params[0]][damages][gun_id][i] == 29) gunname = "MP-5";
   			else if(character_info[params[0]][damages][gun_id][i] == 30) gunname = "AK-47";
			else if(character_info[params[0]][damages][gun_id][i] == 31) gunname = "M4A1";
			else if(character_info[params[0]][damages][gun_id][i] == 32) gunname = "TEC-9";
			else if(character_info[params[0]][damages][gun_id][i] == 33) gunname = "Rifle";
			else if(character_info[params[0]][damages][gun_id][i] == 34) gunname = "Sniper Rifle";
			else if(character_info[params[0]][damages][gun_id][i] == 35) gunname = "Рокетница";
			else if(character_info[params[0]][damages][gun_id][i] == 36) gunname = "Рокетница";
			else if(character_info[params[0]][damages][gun_id][i] == 37) gunname = "Огнемет";
			else if(character_info[params[0]][damages][gun_id][i] == 38) gunname = "Миниган";
			else if(character_info[params[0]][damages][gun_id][i] == 39) gunname = "Взрывчатка";
			else if(character_info[params[0]][damages][gun_id][i] == 41) gunname = "Балончик";
			else if(character_info[params[0]][damages][gun_id][i] == 42) gunname = "Огнетушитель";
			format(str, sizeof(str), "%s%s\t%s\t%.1f%%\t%02d:%02d\n", str, bodypart, gunname, character_info[params[0]][damages][damage_hp][i], character_info[params[0]][damages][hour_damages][i], character_info[params[0]][damages][minute_damages][i]);
		}
 	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Урон", str, "Закрыть", "");

	return 1;
}

CMD:pay(playerid, params[])
{
    if(sscanf(params,"ud", params[0], params[1])) return SyntaxCMD(playerid, "/pay [id] [summ]");
	if(params[0] == playerid) return Sound_Fail(playerid);
    if(!IsPlayerLoged(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не в сети!");
	new Float:x,Float:y,Float:z, virtworld = GetPlayerVirtualWorld(params[0]), myinterior = GetPlayerInterior(params[0]);
	GetPlayerPos(params[0], xyz);
    if(!PlayerToPoint(1.5, playerid, xyz) || GetPlayerVirtualWorld(playerid) != virtworld || GetPlayerInterior(playerid) != myinterior) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко от этого персонажа!");
	new str[64], where[15], from[15];
	format(where, sizeof(where), "to %d", character_info[params[0]][id]);
	format(from, sizeof(where), "from %d", character_info[playerid][id]);
    if(transfermoney(playerid, params[0], params[1], where, from))
	{
		format(str, sizeof(str), ">{FFFFFF} %s получил от Вас %d$.", sendername(params[0]), params[1]);
	    SCM(playerid, COLOR_MSGSERVER, str);
	    format(str, sizeof(str), ">{FFFFFF} %s передал Вам %d$.", sendername(playerid), params[1]);
	    SCM(params[0], COLOR_MSGSERVER, str);
		Log_Write("logs/give_log.txt", "[%s] %s giving %s %d$", ReturnDate(), sendername(params[0]), params[0], params[1]);
		
		format(str, sizeof(str), "передал %s(%d) %d$", sendername(params[0]), params[0], params[1]);
		PlayerLog(playerid, str);
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
    return 1;
}

CMD:world(playerid, params[])
{
	if(IsAdmin(playerid, 2)) 
		return 1;
	new i;
    
	if(sscanf(params, "d", i)) 
		return 1;
    
	SetPlayerVw(playerid, i);
    return 1;
}

CMD:int(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	new i;
    if(sscanf(params, "d", i)) return 1;
    SetPlayerInt(playerid, i);
    return 1;
}
CMD:where(playerid)
{
	new str[180];
    format(str, sizeof(str), "World: %d | Interior: %d | prop: %d", GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), character_info[playerid][prop]);
    SCM(playerid, COLOR_WHITE, str);
	
	new floatxyz;
	GetPlayerPos(playerid, xyz);
	format(str, sizeof(str), "%f %f %f", xyz);
    SCM(playerid, COLOR_WHITE, str);
}

CMD:id(playerid, params[])
{
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/id [id игрока/часть ника]");
	if(!IsPlayerConnected(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
	new str[180];
	new afk_string[25];
	if(character_info[playerid][AFK] > 5) format(afk_string, sizeof(afk_string), " | AFK: %d", character_info[playerid][AFK]);
	if(!GetPVarInt(params[0], "MASKED")) format(str, sizeof(str), "%d: %s {AFAFAF}| %s (uid: %d, chid: %d) %s", params[0], sendername(params[0]), player_info[params[0]][login], player_info[params[0]][id], character_info[params[0]][id], afk_string);
	else format(str, sizeof(str), "%d: %s", params[0], sendername(params[0]));
 	SCM(playerid, COLOR_MSGSERVER, str);
 	return 1;
}

CMD:resetvw(playerid, params[])
{
	if (GetPlayerInterior(playerid) == 0 && GetPlayerVirtualWorld(playerid) > 0)
	{
	    SetPlayerVw(playerid, 0);
	    SendServerMessage(playerid, "Ваш виртуальный мир поправлен.");
	}
	else 
		SendErrorMessage(playerid, "Ваш виртуальный мир впорядке.");
	return 1;
}
CMD:buyprop(playerid)
{
    for(new i = 0; i<MAX_PROP; i++)
	{
	    if(prop_info[i][id] > 0)
	    {
			if(PlayerToPoint(1.5, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid])
			{
				new propid = i;
				if(prop_info[propid][type] == 7) return 1;
				if(prop_info[propid][owner] != 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данное имущество уже кто-то приобрел.");
				new str[32];

				if(IsMaximumProp(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы больше не можете иметь имущество!");
				
				format(str, sizeof(str), "buy property #%d", prop_info[propid][id]);
				if(takemoney(playerid, prop_info[propid][price], str) > 0)
				{
				    prop_info[propid][owner] = character_info[playerid][id];
				    SendServerMessage(playerid, "Вы купили данное имущество!");
					UpdateDaysProp(playerid, GetGlobalIdProp(propid));
				}
				else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");

				break;
			}
		}
	}
	return 1;
}

CMD:greet(playerid, params[]) {
	new a_string[512];
	if(sscanf(params, "ud", params[0], params[1])) 
		return SyntaxCMD(playerid, "/greet [id игрока] [тип]");
	
	if(params[1] < 1 || params[1] > 9) 
		return SendErrorMessage(playerid, "Тип от 1 до 9!");
	
	if (!IsPlayerNearPlayer(playerid, params[0], 2.0))
		return SendErrorMessage(playerid, "Вы не находитесь поблизости с этим игроком.");
	
	format(a_string, sizeof a_string, ">{FFFFFF} Вы предложили %s рукопожатие.", sendername(params[0]));
	SCM(playerid, COLOR_MSGSERVER, a_string);
	format(a_string, sizeof a_string, ">{FFFFFF} %s предложил вам рукопожатие (Нажмите Y для согласия).", sendername(playerid));
	SCM(params[0], COLOR_MSGSERVER, a_string);
	SetPVarInt(params[0], "AcceptType", 4);
	SetPVarInt(params[0], "AcceptAnimType", params[1]);
	SetPVarInt(params[0], "AcceptPlayer", playerid+1);
	return true;
	
}

CMD:acceptdeath(playerid)
{
	if(character_info[playerid][accept_death] == 0) 
		SendClientMessage(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы еще не можете принять смерть.");
	else {
    	SetTimerEx("set_wound", 1000, false, "ii", playerid, 3);
		character_info[playerid][accept_death_timer] = 0;
	}
}

CMD:aheal(playerid,params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	
	if(sscanf(params,"d", params[0])) 
		return SyntaxCMD(playerid, "/aheal [id]");
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_GRAY, "Игрок оффлайн!");
		
	set_wound(params[0], 0);
	
	SetPlayerHealth(params[0],100.0);
	UpdateDamages(params[0]);
	
	character_info[params[0]][newlife] = -1;
	character_info[params[0]][hospital] = -1;
	
	if(GetPVarInt(params[0],"Ranen_") != -1)
	{
		KillTimer(GetPVarInt(params[0],"Ranen_"));
		SetPVarInt(params[0],"Ranen_",-1);
	
	}
	
	if(GetPVarInt(params[0],"ChangeState_Time") != -1)
	{
		KillTimer(GetPVarInt(params[0],"ChangeState_Time"));
		SetPVarInt(params[0],"ChangeState_Time",-1);
	
	}
	
	new str[128];
	format(str, sizeof(str), "%s[%d] вылечил %s(%s)", player_info[playerid][login], playerid, player_info[params[0]][login], character_info[params[0]][name]);
	AdminMessage(str);
	
	return 1;
}

CMD:hug(playerid, params[]) {

    new a_string[128];
	if(sscanf(params, "u", params[0])) return SyntaxCMD(playerid, "/hug [id игрока]");
        
	if (!IsPlayerNearPlayer(playerid, params[0], 2.0))
		return SendErrorMessage(playerid, "Вы не находитесь поблизости с этим игроком.");
	
	format(a_string, sizeof a_string, ">{FFFFFF} Вы предложили %s семейное приветствие.", sendername(params[0]));
	SCM(playerid, COLOR_MSGSERVER, a_string);
	format(a_string, sizeof a_string, ">{FFFFFF} %s предложил вам семейное приветствие (Нажмите Y для согласия).", sendername(playerid));
	SCM(params[0], COLOR_MSGSERVER, a_string);
	SetPVarInt(params[0], "AcceptPlayer", playerid+1);
	SetPVarInt(params[0], "AcceptType", 1);
	return true;
}

CMD:hand(playerid, params[]) {
	new a_string[128];
	if(sscanf(params, "u", params[0])) return SyntaxCMD(playerid, "/hand [id игрока]");
	new floatxyz;
	GetPlayerPos(params[0], xyz);
	if(!PlayerToPoint(3.0, playerid, xyz)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок далеко от Вас!");
	format(a_string, sizeof a_string, ">{FFFFFF} Вы предложили %s рукопожатие.", sendername(params[0]));
	SCM(playerid, COLOR_MSGSERVER, a_string);
	format(a_string, sizeof a_string, ">{FFFFFF} %s предложил вам рукопожатие (Нажмите Y для согласия).", sendername(playerid));
	SCM(params[0], COLOR_MSGSERVER, a_string);
	SetPVarInt(params[0], "AcceptPlayer", playerid+1);
	SetPVarInt(params[0], "AcceptType", 2);
	return true;
}

CMD:kiss(playerid, params[]) {
	new a_string[128];
	
	if(sscanf(params, "u", params[0])) 
		return SyntaxCMD(playerid, "/kiss [id игрока]");
	
	if (!IsPlayerNearPlayer(playerid, params[0], 2.0))
		return SendErrorMessage(playerid, "Вы не находитесь поблизости с этим игроком.");
	
	format(a_string, sizeof a_string, ">{FFFFFF} Вы предложили %s поцелуй.", sendername(params[0]));
	SCM(playerid, COLOR_MSGSERVER, a_string);
	format(a_string, sizeof a_string, ">{FFFFFF} %s предложил вам поцелуй (Нажмите Y для согласия).", sendername(playerid));
	SCM(params[0], COLOR_MSGSERVER, a_string);
	
	SetPVarInt(params[0], "AcceptType", 3);
	SetPVarInt(params[0], "AcceptPlayer", playerid+1);
	return true;
}

CMD:anim(playerid) {
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /handsup, /sit, /aim, /cellin, /cellout, /drunk, /kicking");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /bomb, /bar, /stoptaxi, /getarrested, /laugh, /lookout, /cry");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /crossarms, /hide, /vomit, /eat, /sipdrink, /slapass");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /chat, /fucku, /taichi, /injured, /no, /yes, /crawl, /push");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /akick, /facepalm, /balls, /lowbodypush, /aspray, /medic");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /koface, /kostomach, /lifejump, /rollfall, /hoodfrisked, /flip");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /tired, /box, /chant, /finger, /gpunch, /gkick, /lowthrow");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /riot, /abp, /taxiR, /taxiL, /gro, /seat, /shotgun, /colt");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /tatto, /strip, /dance, /deal, /asmoke, /rap, /bat, /car");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /basked, /lean, /lay, /gsign, /walk, /wave, /police, /crack");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /waimL, /waimR, /lookback, /caim, /creep, /sroll, /gesture");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /lookoutR, /lookoutL, /agreement, /bend, /rod, /tgro, /cmouth");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /gog, /nfall, /hsit, /csit, /bracing, /pool, /ssearch, /daim");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /rhandL, /rhandR, /hstand, /nlean, /shelter, /lookback, /wsit");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /waim, /hangon, /sleepL, /sleepR, /blowj, /rseat, /polwalk");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /wallow, /nflip, /csdead, /follow, /grnd, /copa, /cmon, /lose");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /win, /gunthreat, /givecash, /robr, /serend, /heist, /beckon");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /frontfall, /pants, /tired, /climb, /tlean, /pushup, /protection");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /swallow, /stand, /pullhand, /nlook, /extend, /stopit, /ksit");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /esit, /tsit, /repcar, /onehand, /backwalk, /feettog, /mirro");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /hips, /pullo, /rtake, /obalance, /wobalance, /taction, /catch");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /despair, /rooting, /spyglass, /looksky, /mshow, /wshow, /hshow");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /sh, /crossfingers, /delight, /hdelight, /showtable, /tfacepalm");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /tpull, /fail, /joy, /fsit, /crushjump, /scatch, /lookfloor, /wear");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /tramplefloor, /swing, /nbp, /takehead, /readtable, /squat");
	SendClientMessage(playerid, COLOR_LEMON, ">{FFFFFF} /sprawl, /throwmoney, /sho, /faim, /piss, /swingback, /hnds");
	return true;
}

CMD:ame(playerid, params[])
{
	new string[180];
	if(sscanf(params,"s[124]", params[0])) return SyntaxCMD(playerid, "/ame [действие]");
	format(string, 180, "%s %s", sendername(playerid, true), params[0]);
	Log_Write("logs/chat_log.txt", "[%s] [ame] * %s %s", ReturnDate(), sendername(playerid, true), params[0]);
	SetPlayerChatBubble(playerid,string,COLOR_ME,30.0,5000);
	
	format(string, sizeof(string), "> %s", string);
	SCM(playerid, COLOR_ME, string);
    return 1;
}

//
CMD:sa(playerid)
{
	if(character_info[playerid][wound] > 0) 
		return 1;
    
	StopUsingAnim(playerid);
    return 1;
}

CMD:handsup(playerid) {
	UseAnim(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
	return true;
}

CMD:sit(playerid) {
	UseAnim(playerid,"PED","SEAT_down",4.0,0,0,1,1,0);
	return true;
}

CMD:aim(playerid) {
	UseAnim(playerid,"PED","gang_gunstand",3.0, 0, 1, 1,1,0);
	return true;
}


CMD:cellin(playerid) {
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
	return true;
}

CMD:cellout(playerid) {
	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
	return true;
}


CMD:drunk(playerid) {
	UseAnim(playerid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
	return true;
}

CMD:kicking(playerid) {
	UseAnim(playerid,"GANGS","shake_carK",4.0,0,0,0,0,0);
	return true;
}

CMD:bomb(playerid) {
	UseAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
	return true;
}

CMD:bar(playerid) {
	UseAnim(playerid,"BAR","Barserve_bottle",4.0,0,0,0,0,0);
	return true;
}

CMD:stoptaxi(playerid) {
	UseAnim(playerid,"PED","IDLE_taxi",4.0,0,0,0,0,0);
	return true;
}

CMD:getarrested(playerid) {
	UseAnim(playerid,"ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1);
	return true;
}

CMD:laugh(playerid) {
	UseAnim(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
	return true;
}

CMD:lookout(playerid) {
	UseAnim(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0);
	return true;
}

CMD:crossarms(playerid) {
	UseAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	return true;
}

CMD:hide(playerid) {
	UseAnim(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
	return true;
}

CMD:vomit(playerid) {
	UseAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
	return true;
}

CMD:eat(playerid) {
	UseAnim(playerid, "FOOD", "EAT_Burger", 4.1,1,1,1,1,1);
	return true;
}

CMD:sipdrink(playerid) {
	UseAnim(playerid, "GANGS", "drnkbr_prtl", 4.1,1,1,1,1,1);
	return true;
}

CMD:slapass(playerid) {
	UseAnim(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
	return true;
}

CMD:chat(playerid) {
	UseAnim(playerid,"PED","IDLE_CHAT",4.0,1,0,0,1,1);
	return true;
}

CMD:fucku(playerid) {
	UseAnim(playerid,"PED","fucku",4.0,0,0,0,0,0);
	return true;
}

CMD:taichi(playerid) {
	UseAnim(playerid,"PARK","Tai_Chi_Loop",4.0,1,0,0,0,0);
	return true;
}

CMD:injured(playerid) {
	UseAnim(playerid, "SWEET", "Sweet_injuredloop", 4.0,0,0,1,1,0);
	return true;
}

CMD:no(playerid) {
	UseAnim(playerid,"GANGS","Invite_No",4.0,0,0,0,0,0);
	return true;
}

CMD:yes(playerid) {
	UseAnim(playerid,"GANGS","Invite_Yes",4.0,0,0,0,0,0);
	return true;
}

CMD:crawl(playerid) {
	UseAnim(playerid,"PED","CAR_crawloutRHS",4.0,0,0,0,0,0);
	return true;
}

CMD:push(playerid) {
	UseAnim(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
	return true;
}

CMD:akick(playerid) {
	UseAnim(playerid,"POLICE","Door_Kick",4.0,0,0,0,0,0);
	return true;
}

CMD:facepalm(playerid) {
	UseAnim(playerid,"MISC","plyr_shkhead",4.0,0,0,0,0,0);
	return true;
}

CMD:balls(playerid) {
	UseAnim(playerid,"MISC","scratchballs_01",4.0,0,0,0,0,0);
	return true;
}

CMD:lowbodypush(playerid) {
	UseAnim(playerid,"GANGS","shake_carSH",4.0,0,0,0,0,0);
	return true;
}

CMD:aspray(playerid) {
	UseAnim(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,0,0);
	return true;
}

CMD:medic(playerid) {
	UseAnim(playerid,"MEDIC","CPR",4.0,0,0,0,0,0);
	return true;
}

CMD:koface(playerid) {
	UseAnim(playerid,"PED","KO_shot_face",4.0,0,1,1,1,0);
	return true;
}

CMD:kostomach(playerid) {
	UseAnim(playerid,"PED","KO_shot_stom",4.0,0,1,1,1,0);
	return true;
}

CMD:lifejump(playerid) {
	UseAnim(playerid,"PED","EV_dive",4.0,0,1,1,1,0);
	return true;
}

CMD:rollfall(playerid) {
	UseAnim(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,0);
	return true;
}

CMD:hoodfrisked(playerid) {
	UseAnim(playerid,"POLICE","crm_drgbst_01",1.0,0,1,1,1,0);
	return true;
}

CMD:flip(playerid) {
	UseAnim(playerid,"PED","KD_left",4.1,0,1,1,1,0);
	return true;
}

CMD:box(playerid) {
	UseAnim(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,0);
	return true;
}

CMD:chant(playerid) {
	UseAnim(playerid,"RIOT","RIOT_CHANT",4.0,1,1,1,1,0);
	return true;
}

CMD:finger(playerid) {
	UseAnim(playerid,"RIOT","RIOT_FUKU",2.0,0,0,0,0,0);
	return true;
}

CMD:gpunch(playerid) {
	UseAnim(playerid,"FIGHT_B","FightB_G",4.0,0,0,0,0,0);
	return true;
}

CMD:gkick(playerid) {
	UseAnim(playerid,"FIGHT_D","FightD_G",4.0,0,0,0,0,0);
	return true;
}

CMD:lowthrow(playerid) {
	UseAnim(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
	return true;
}

CMD:riot(playerid) {
	UseAnim(playerid,"RIOT","RIOT_ANGRY",4.0,0,0,0,0,0);
	return true;
}

CMD:abp(playerid) {
	UseAnim(playerid,"benchpress","gym_bp_celebrate",4.0,0,0,0,0,0);
	return true;
}

CMD:cry(playerid) {
	UseAnim(playerid,"GRAVEYARD","mrnF_loop",4.0,1,0,0,0,0);
	return true;
}

CMD:taxir(playerid) {
	UseAnim(playerid, "MISC","hiker_pose", 3.0,0,1,1,1,0);
	return true;
}

CMD:taxil(playerid) {
	UseAnim(playerid, "MISC","hiker_pose_L", 3.0,0,1,1,1,0);
	return true;
}

CMD:gro(playerid) {
	UseAnim(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
	return true;
}

CMD:seat(playerid) {
	UseAnim(playerid,"INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
	return true;
}

CMD:tatto(playerid) {
	UseAnim(playerid,"TATTOOS", "TAT_ArmR_Pose_P", 4.1, 0, 1, 1, 1, 0);
	return true;
}

CMD:waiml(playerid) {
	UseAnim(playerid,"PED","Driveby_L",4.1,0,1,1,1,1);
	return true;
}

CMD:waimr(playerid) {
	UseAnim(playerid,"PED","Driveby_R",4.1,0,1,1,1,1);
	return true;
}

CMD:caim(playerid) {
	UseAnim(playerid,"PED","IDLE_ROCKET",4.1,0,1,1,1,1);
	return true;
}

CMD:creep(playerid) {
	UseAnim(playerid,"PED","Player_Sneak",4.1,1,1,1,1,1);
	return true;
}

CMD:sroll(playerid) {
	UseAnim(playerid,"SWAT","JMP_Wall1m_180",4.1,0,1,1,1,0);
	return true;
}

CMD:gesture(playerid) {
	UseAnim(playerid,"SWAT","swt_lkt",4.0,0,0,0,0,0);
	return true;
}

CMD:lookoutr(playerid) {
	UseAnim(playerid,"SWAT","swt_wllpk_L",4.0,0,0,1,1,0);
	return true;
}

CMD:lookoutl(playerid) {
	UseAnim(playerid,"SWAT","swt_wllpk_R",4.0,0,0,1,1,0);
	return true;
}

CMD:agreement(playerid) {
	UseAnim(playerid,"COP_AMBIENT","Coplook_think",4.0,1,0,0,0,0);
	return true;
}

CMD:bend(playerid) {
	UseAnim(playerid,"BAR","Barserve_order",4.0,0,0,0,0,0);
	return true;
}

CMD:rod(playerid) {
	UseAnim(playerid,"benchpress","gym_bp_up_A",4.0,0,0,1,1,0);
	return true;
}

CMD:tgro(playerid) {
	UseAnim(playerid,"CAMERA","camcrch_cmon",4.0,0,0,1,1,0);
	return true;
}

CMD:cmouth(playerid) {
	UseAnim(playerid,"ON_LOOKERS","panic_in",4.0,0,0,1,1,0);
	return true;
}

CMD:gog(playerid) {
	UseAnim(playerid,"goggles","goggles_put_on",4.1,0,1,1,1,1);
	return true;
}

CMD:nfall(playerid) {
	UseAnim(playerid,"HEIST9","CAS_G2_GasKO",4.1,0,1,1,1,0);
	return true;
}

CMD:hsit(playerid) {
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.0,1,0,1,1,0);
	return true;
}

CMD:csit(playerid) {
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Type_Loop",4.0,1,0,1,1,0);
	return true;
}

CMD:bracing(playerid) {
	UseAnim(playerid,"PLAYIDLES","stretch",4.0,0,0,0,0,0);
	return true;
}

CMD:pool(playerid) {
	UseAnim(playerid,"POOL","POOL_Long_Start",4.1,0,1,1,1,0);
	return true;
}

CMD:ssearch(playerid) {
	UseAnim(playerid,"ROB_BANK","CAT_Safe_Rob",4.0,1,0,0,0,0);
	return true;
}

CMD:daim(playerid) {
	UseAnim(playerid,"RYDER","Van_Stand_Crate",3.0,0,1,1,1,0);
	return true;
}

CMD:rhandl(playerid) {
	UseAnim(playerid,"SCRATCHING","scdlulp",4.0,0,0,1,1,0);
	return true;
}

CMD:rhandr(playerid) {
	UseAnim(playerid,"SCRATCHING","scdrulp",4.0,0,0,1,1,0);
	return true;
}

CMD:hstand(playerid) {
	UseAnim(playerid,"SCRATCHING","scdrdlp",4.0,0,0,1,1,0);
	return true;
}

CMD:nlean(playerid) {
	UseAnim(playerid,"SHAMAL","SHAMAL_align",4.1,0,1,1,1,0);
	return true;
}

CMD:shelter(playerid) {
	UseAnim(playerid,"SHOP","SHP_Duck_Fire",4.0,0,0,1,1,0);
	return true;
}

CMD:lookback(playerid) {
	UseAnim(playerid,"PED","flee_lkaround_01",4.0,0,0,0,0,0);
	return true;
}

CMD:wsit(playerid) {
	UseAnim(playerid,"SHOP","SHP_Gun_Duck",4.0,0,0,1,1,0);
	return true;
}

CMD:waim(playerid) {
	UseAnim(playerid,"TEC","TEC_reload",4.1,0,1,1,1,1);
	return true;
}

CMD:hangon(playerid) {
	UseAnim(playerid,"TRAIN","tran_ouch",4.0,0,0,1,1,0);
	return true;
}

CMD:sleepl(playerid) {
	UseAnim(playerid,"INT_HOUSE","BED_In_L",4.0,0,0,1,1,0);
	return true;
}

CMD:sleepr(playerid) {
	UseAnim(playerid,"INT_HOUSE","BED_In_R",4.0,0,0,1,1,0);
	return true;
}

CMD:blowj(playerid) {
	UseAnim(playerid,"BLOWJOBZ", "BJ_COUCH_START_W", 4.1, 0, 1, 1, 1, 0 );
	return true;
}

CMD:rseat(playerid) {
	UseAnim(playerid,"BLOWJOBZ", "BJ_COUCH_START_P", 4.1, 0, 1, 1, 1, 0 );
	return true;
}

CMD:polwalk(playerid) {
	UseAnim(playerid,"POLICE","Cop_move_FWD",3.0,1,1,1,1,1);
	return true;
}

CMD:nflip(playerid) {
	UseAnim(playerid,"PED","BIKE_fall_off",4.1,0,1,1,1,0);
	return true;
}

CMD:csdead(playerid) {
	UseAnim(playerid,"WUZI","CS_Dead_Guy",4.1,0,1,1,1,0);
	return true;
}

CMD:follow(playerid) {
	UseAnim(playerid,"WUZI","Wuzi_follow",4.1,0,1,1,1,1);
	return true;
}

CMD:grnd(playerid) {
	UseAnim(playerid,"WUZI","Wuzi_grnd_chk",4.0,0,0,0,0,0);
	return true;
}

CMD:copa(playerid) {
	UseAnim(playerid,"COP_AMBIENT","Copbrowse_in",4.1,0,1,1,1,0);
	return true;
}

CMD:cmon(playerid) {
	UseAnim(playerid,"OTB","wtchrace_cmon",4.1,0,1,1,1,0);
	return true;
}

CMD:lose(playerid) {
	UseAnim(playerid,"OTB","wtchrace_lose",4.1,0,1,1,1,0);
	return true;
}

CMD:win(playerid) {
	UseAnim(playerid,"OTB","wtchrace_win",4.1,0,1,1,1,0);
	return true;
}

CMD:gunthreat(playerid) {
	UseAnim(playerid,"SHOP","SHP_Gun_Threat",4.1,0,1,1,1,0);
	return true;
}

CMD:givecash(playerid) {
	UseAnim(playerid,"SHOP","SHP_Rob_GiveCash",4.1,0,1,1,1,0);
	return true;
}

CMD:robr(playerid) {
	UseAnim(playerid,"SHOP","SHP_Rob_React",4.1,0,1,1,1,0);
	return true;
}

CMD:serend(playerid) {
	UseAnim(playerid,"SHOP","SHP_Serve_End",4.1,0,1,1,1,0);
	return true;
}

CMD:heist(playerid) {
	UseAnim(playerid,"HEIST9","Use_SwipeCard",4.0,0,0,0,0,0);
	return true;
}

CMD:frontfall(playerid) {
	UseAnim(playerid,"PED","FLOOR_hit_f",4.1,0,1,1,1,0);
	return true;
}

CMD:pants(playerid) {
	UseAnim(playerid,"BLOWJOBZ","BJ_STAND_END_P",4.0,0,0,0,0,0);
	return true;
}
/////////////////////////////////////////////////////////////////////////
CMD:tired(playerid) {
	UseAnim(playerid,"FAT","IDLE_tired",4.0,0,0,1,1,0);
	return true;
}

CMD:climb(playerid) {
	UseAnim(playerid,"PED","CLIMB_jump",4.0,0,0,1,1,0);
	return true;
}

CMD:tlean(playerid) {
	UseAnim(playerid,"PED","DRIVE_BOAT",4.0,0,0,1,1,0);
	return true;
}

CMD:pushup(playerid) {
	UseAnim(playerid,"PED","getup_front",4.0,1,0,1,1,0);
	return true;
}

CMD:protection(playerid) {
	UseAnim(playerid,"PED","FightShB",4.0,0,1,1,1,1);
	return true;
}

CMD:swallow(playerid) {
	UseAnim(playerid,"PED","gum_eat",4.0,0,0,0,0,0);
	return true;
}

CMD:stand(playerid) {
	UseAnim(playerid,"PED","IDLE_HBHB",3.0,0,1,1,1,0);
	return true;
}

CMD:pullhand(playerid) {
	UseAnim(playerid,"PED","Jetpack_Idle",3.0,0,1,1,1,0);
	return true;
}

CMD:nlook(playerid) {
	UseAnim(playerid,"PED","roadcross_gang",4.0,0,0,0,0,0);
	return true;
}

CMD:extend(playerid) {
	UseAnim(playerid,"PED","Shove_Partial",4.1,0,1,1,1,1);
	return true;
}

CMD:stopit(playerid) {
	UseAnim(playerid,"PED","Walk_DoorPartial",4.0,0,0,0,0,0);
	return true;
}

CMD:ksit(playerid) {
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Crash",4.0,1,0,1,1,0);
	return true;
}

CMD:esit(playerid) {
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Drink",4.0,1,0,1,1,0);
	return true;
}

CMD:tsit(playerid) {
	UseAnim(playerid,"INT_OFFICE","OFF_Sit_Watch",4.0,0,0,1,1,0);
	return true;
}

CMD:rtake(playerid) {
	UseAnim(playerid,"BAR","Barserve_give",4.0,0,0,0,0,0);
	return true;
}

CMD:forwardlook(playerid) {
	UseAnim(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
	return true;
}

CMD:wforwardlook(playerid) {
	UseAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
	return true;
}

CMD:taction(playerid) {
	UseAnim(playerid,"BD_FIRE","wash_up",4.0,0,0,0,0,0);
	return true;
}

CMD:catch(playerid) {
	UseAnim(playerid,"MD_CHASE","MD_HANG_Loop",4.1,0,1,1,1,0);
	return true;
}

CMD:despair(playerid) {
	UseAnim(playerid,"BSKTBALL","BBALL_react_miss",4.0,0,0,0,0,0);
	return true;
}

CMD:rooting(playerid) {
	UseAnim(playerid,"BSKTBALL","BBALL_react_score",4.1,1,1,1,1,0);
	return true;
}

CMD:spyglass(playerid) {
	UseAnim(playerid,"CAMERA","picstnd_take",4.1,0,1,1,1,0);
	return true;
}

CMD:looksky(playerid) {
	UseAnim(playerid,"ON_LOOKERS","lkup_loop",4.1,0,1,1,1,0);
	return true;
}

CMD:mshow(playerid) {
	UseAnim(playerid,"ON_LOOKERS","panic_point",4.1,0,1,1,1,0);
	return true;
}

CMD:wshow(playerid) {
	UseAnim(playerid,"ON_LOOKERS","panic_shout",4.1,0,1,1,1,0);
	return true;
}

CMD:hshow(playerid) {
	UseAnim(playerid,"ON_LOOKERS","point_loop",4.1,0,1,1,1,0);
	return true;
}

CMD:sh(playerid) {
	UseAnim(playerid,"ON_LOOKERS","shout_in",4.0,0,0,0,0,0);
	return true;
}

CMD:crossfingers(playerid) {
	UseAnim(playerid,"CASINO","cards_loop",4.1,0,1,1,1,0);
	return true;
}

CMD:delight(playerid) {
	UseAnim(playerid,"CASINO","manwinb",4.0,0,0,0,0,0);
	return true;
}

CMD:hdelight(playerid) {
	UseAnim(playerid,"CASINO","manwind",4.0,0,0,0,0,0);
	return true;
}

CMD:showtable(playerid) {
	UseAnim(playerid,"CASINO","Roulette_bet",4.1,0,1,1,1,0);
	return true;
}

CMD:tfacepalm(playerid) {
	UseAnim(playerid,"CASINO","Roulette_lose",4.1,0,1,1,1,0);
	return true;
}

CMD:tpull(playerid) {
	UseAnim(playerid,"CASINO","Slot_in",4.1,0,1,1,1,0);
	return true;
}

CMD:fail(playerid) {
	UseAnim(playerid,"CASINO","Slot_lose_out",4.0,0,0,0,0,0);
	return true;
}

CMD:joy(playerid) {
	UseAnim(playerid,"CASINO","Slot_win_out",4.0,0,0,0,0,0);
	return true;
}

CMD:wear(playerid) {
	UseAnim(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
	return true;
}

CMD:fsit(playerid) {
	UseAnim(playerid,"JST_BUISNESS","girl_02",4.1,0,1,1,1,0);
	return true;
}

CMD:crushjump(playerid) {
	UseAnim(playerid,"DODGE","Crush_Jump",4.1,0,1,1,1,0);
	return true;
}

CMD:scatch(playerid) {
	UseAnim(playerid,"FINALE","FIN_LegsUp_Loop",4.1,0,1,1,1,0);
	return true;
}

CMD:lookfloor(playerid) {
	UseAnim(playerid,"FINALE","FIN_Cop1_Loop",4.1,0,1,1,1,0);
	return true;
}

CMD:tramplefloor(playerid) {
	UseAnim(playerid,"FINALE","FIN_Cop1_Stomp",4.1,1,1,1,1,0);
	return true;
}

CMD:swing(playerid) {
	UseAnim(playerid,"Freeweights","gym_free_B",4.1,0,1,1,1,0);
	return true;
}

CMD:nbp(playerid) {
	UseAnim(playerid,"Freeweights","gym_free_celebrate",4.0,0,0,0,0,0);
	return true;
}

CMD:takehead(playerid) {
	UseAnim(playerid,"HAIRCUTS","BRB_Cut",4.1,0,1,1,1,0);
	return true;
}

CMD:readtable(playerid) {
	UseAnim(playerid,"SCRATCHING","sclng_r",4.1,0,1,1,1,0);
	return true;
}

CMD:squat(playerid) {
	UseAnim(playerid,"TEC","TEC_crouchfire",4.1,0,1,1,1,0);
	return true;
}

CMD:sprawl(playerid) {
	UseAnim(playerid,"TATTOOS","TAT_Idle_Loop_T",4.1,0,1,1,1,0);
	return true;
}

CMD:throwmoney(playerid) {
	UseAnim(playerid,"STRIP","PUN_CASH",4.0,0,0,0,0,0);
	return true;
}

CMD:sho(playerid) {
	UseAnim(playerid,"STRIP","PUN_HOLLER",4.0,0,0,0,0,0);
	return true;
}

CMD:faim(playerid) {
	UseAnim(playerid,"SWORD","sword_IDLE",4.1,0,1,1,1,0);
	return true;
}

CMD:piss(playerid) {
	UseAnim(playerid,"PAULNMAC","Piss_in",4.1,0,1,1,1,0);
	return true;
}

CMD:swingback(playerid) {
	UseAnim(playerid,"PED","getup",4.1,0,1,1,1,0);
	return true;
}

CMD:onehand(playerid) {
	UseAnim(playerid,"PED","CLIMB_jump2fall",4.1,0,1,1,1,0);
	return true;
}

CMD:backwalk(playerid) {
	UseAnim(playerid,"PED","gas_cwr",4.1,1,1,1,1,1);
	return true;
}

CMD:feettog(playerid) {
	UseAnim(playerid,"PED","Idlestance_fat",4.1,0,1,1,1,0);
	return true;
}

CMD:mirro(playerid) {
	UseAnim(playerid,"CLOTHES","CLO_Pose_Hat",4.1,0,1,1,1,0);
	return true;
}

CMD:hips(playerid) {
	UseAnim(playerid,"COP_AMBIENT","Coplook_shake",4.1,0,1,1,1,0);
	return true;
}

CMD:pullo(playerid) {
	UseAnim(playerid,"AIRPORT","thrw_barl_thrw",4.1,0,1,1,1,0);
	return true;
}

CMD:obalance(playerid) {
	UseAnim(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
	return true;
}

CMD:wobalance(playerid) {
	UseAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
	return true;
}
CMD:dance(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/dance [1-12]");
	switch(params[0]) {
		case 1 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		case 2 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		case 3 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		case 4 : SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
		case 5 : UseAnim(playerid,"DANCING","bd_clap",4.1,1,1,1,1,1);
		case 6 : UseAnim(playerid,"DANCING","bd_clap1",4.1,1,1,1,1,1);
		case 7 : UseAnim(playerid,"DANCING","DAN_Down_A",4.1,1,1,1,1,1);
		case 8 : UseAnim(playerid,"DANCING","DAN_Left_A",4.1,1,1,1,1,1);
		case 9 : UseAnim(playerid,"DANCING","DAN_Loop_A",4.1,1,1,1,1,1);
		case 10 : UseAnim(playerid,"DANCING","DAN_Right_A",4.1,1,1,1,1,1);
		case 11 : UseAnim(playerid,"DANCING","DAN_Up_A",4.1,1,1,1,1,1);
		case 12 : UseAnim(playerid,"DANCING","dnce_M_a",4.1,1,1,1,1,1);
		default : SyntaxCMD(playerid, "/dance [1-12]");
	}
	return true;
}

CMD:repcar(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/repcar [1-2]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"CAR","Fixn_Car_Loop",3.0,0,1,1,1,0);
		case 2 : UseAnim(playerid,"CAR","Fixn_Car_Out",3.0,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/repcar [1-2]");
	}
	return true;
}


CMD:hnds(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/hnds [1-7]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkB",4.1,0,1,1,1,1);
		case 2 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkC",4.1,0,1,1,1,1);
		case 3 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkD",4.1,0,1,1,1,1);
		case 4 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkE",4.1,0,1,1,1,1);
		case 5 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkF",4.1,0,1,1,1,1);
		case 6 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkG",4.1,0,1,1,1,1);
		case 7 : UseAnim(playerid,"LOWRIDER","prtial_gngtlkH",4.1,0,1,1,1,1);
		default : SyntaxCMD(playerid, "/hnds [1-7]");
	}
	return true;
}

CMD:strip(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/strip [1-14]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
		case 2 : UseAnim(playerid,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1 );
		case 3 : UseAnim(playerid,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1 );
		case 4 : UseAnim(playerid,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1 );
		case 5 : UseAnim(playerid,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1 );
		case 6 : UseAnim(playerid,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1 );
		case 7 : UseAnim(playerid,"STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1 );
     	case 8: ApplyAnimation(playerid,"STRIP","STR_A2B",4.1,1,1,1,1,1);
        case 9: ApplyAnimation(playerid,"STRIP","STR_B2C",4.1,1,1,1,1,1);
        case 10: ApplyAnimation(playerid,"STRIP","STR_C1",4.1,1,1,1,1,1);
        case 11: ApplyAnimation(playerid,"STRIP","STR_C2",4.1,1,1,1,1,1);
        case 12: ApplyAnimation(playerid,"STRIP","STR_Loop_A",4.1,1,1,1,1,1);
        case 13: ApplyAnimation(playerid,"STRIP","STR_Loop_B",4.1,1,1,1,1,1);
        case 14: ApplyAnimation(playerid,"STRIP","STR_Loop_C",4.1,1,1,1,1,1);
		default : SyntaxCMD(playerid, "/strip [1-14]");
	}
	return true;
}


CMD:deal(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/deal [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
		case 2 : UseAnim(playerid, "DEALER","DEALER_IDLE", 3.0,0,1,1,1,0);
		case 3 : UseAnim(playerid,"GRAVEYARD","mrnM_loop",3.0,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/deal [1-3]");
	}
	return true;
}

CMD:asmoke(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/asmoke [1-4]");
	switch(params[0]) {
		case 1 : UseAnim(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		case 2 : UseAnim(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		case 3 : UseAnim(playerid, "SMOKING","M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0);
		case 4 : UseAnim(playerid, "SMOKING","M_smk_out", 4.0, 0, 0, 0, 0, 0);
		default : SyntaxCMD(playerid, "/asmoke [1-4]");
	}
	return true;
}

CMD:rap(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/rap [1-9]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"RAPPING","RAP_A_Loop",4.0,1,0,0,0,0);
		case 2 : UseAnim(playerid,"RAPPING","RAP_C_Loop",4.0,1,0,0,0,0);
		case 3 : UseAnim(playerid,"GANGS","prtial_gngtlkD",4.0,1,0,0,1,1);
		case 4 : UseAnim(playerid,"GANGS","prtial_gngtlkH",4.0,1,0,0,1,1);
		case 5 : UseAnim(playerid,"GANGS","prtial_gngtlkF",4.0,1,0,0,1,1);
		case 6 : UseAnim(playerid,"GANGS","prtial_gngtlkG",4.0,1,0,0,1,1);
		case 7 : UseAnim(playerid,"PED","ATM",4.0,0,0,0,0,0);
		case 8 : UseAnim(playerid,"RAPPING","RAP_B_IN",3.0,0,1,1,1,0);
		case 9 : UseAnim(playerid,"GYMNASIUM","gym_tread_celebrate",4.1,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/rap [1-9]");
	}
	return true;
}

CMD:bat(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/bat [1-2]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"CRACK","Bbalbat_Idle_02",4.0, 1, 0, 0, 0, 0);
		case 2 : UseAnim(playerid,"CRACK","Bbalbat_Idle_01",4.0, 1, 0, 0, 0, 0);
		default : SyntaxCMD(playerid, "/bat [1-2]");
	}
	return true;
}

CMD:basket(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/basket [1-6]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"BSKTBALL","BBALL_idleloop",4.0,1,0,0,0,0);
		case 2 : UseAnim(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
		case 3 : UseAnim(playerid,"BSKTBALL","BBALL_pickup",4.0,0,0,0,0,0);
		case 4 : UseAnim(playerid,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
		case 5 : UseAnim(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
		case 6 : UseAnim(playerid,"BSKTBALL","BBALL_Dnk",4.0,0,0,0,0,0);
		default : SyntaxCMD(playerid, "/basket [1-6]");
	}
	return true;
}

CMD:lean(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/lean [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"GANGS","leanIDLE",4.0,0,0,1,1,0);
		case 2 : UseAnim(playerid,"MISC","Plyrlean_loop",4.0,0,1,1,1,0);
		case 3 : UseAnim(playerid,"CAR_CHAT","car_talkm_loop",4.0,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/lean [1-3]");
	}
	return true;
}

CMD:lay(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/lay [1-5]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
		case 2 : UseAnim(playerid,"SUNBATHE","Lay_Bac_in",3.0,0,1,1,1,0);
		case 3 : UseAnim(playerid,"BEACH","ParkSit_W_loop",3.0,0,1,1,1,0);
		case 4 : UseAnim(playerid,"BEACH","SitnWait_loop_W",4.0, 1, 0, 0, 0, 0);
		case 5 : UseAnim(playerid,"SUNBATHE","SBATHE_F_LieB2Sit",3.0,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/lay [1-5]");
	}
	return true;
}

CMD:gsign(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/gsign [1-10]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"GHANDS","gsign1",4.1,0,1,1,1,1);
		case 2 : UseAnim(playerid,"GHANDS","gsign1LH",4.1,0,1,1,1,1);
		case 3 : UseAnim(playerid,"GHANDS","gsign2",4.1,0,1,1,1,1);
		case 4 : UseAnim(playerid,"GHANDS","gsign2LH",4.1,0,1,1,1,1);
		case 5 : UseAnim(playerid,"GHANDS","gsign3",4.1,0,1,1,1,1);
		case 6 : UseAnim(playerid,"GHANDS","gsign3LH",4.1,0,1,1,1,1);
		case 7 : UseAnim(playerid,"GHANDS","gsign4",4.1,0,1,1,1,1);
		case 8 : UseAnim(playerid,"GHANDS","gsign4LH",4.1,0,1,1,1,1);
		case 9 : UseAnim(playerid,"GHANDS","gsign5",4.1,0,1,1,1,1);
		case 10 : UseAnim(playerid,"GHANDS","gsign5LH",4.1,0,1,1,1,1);
		default : SyntaxCMD(playerid, "/gsign [1-10]");
	}
	return true;
}

CMD:walk(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/walk [1-12]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"PED","WALK_player",4.1,1,1,1,1,1);
		case 2 : UseAnim(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
		case 3 : UseAnim(playerid,"PED","WOMAN_walkfatold",4.1,1,1,1,1,1);
		case 4 : UseAnim(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
		case 5 : UseAnim(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
		case 6 : UseAnim(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
		case 7 : UseAnim(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
		case 8 : UseAnim(playerid,"PED","Walk_Wuzi",4.1,1,1,1,1,1);
		case 9 : UseAnim(playerid,"PED","WALK_armed",4.1,1,1,1,1,1);
		case 10 : UseAnim(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
		case 11 : UseAnim(playerid,"PED","WALK_drunk",4.1,1,1,1,1,1);
		case 12 : UseAnim(playerid,"WUZI","Wuzi_Walk",4.1,1,1,1,1,1);
		default : SyntaxCMD(playerid, "/walk [1-12]");
	}
	return true;
}

CMD:wave(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/wave [1-4]");
	switch(params[0]) {
		case 1 : UseAnim(playerid, "KISSING","gfwave2", 4.1,0,1,1,0,0);
		case 2 : UseAnim(playerid, "ON_LOOKERS","wave_loop", 4.1,1,1,1,0,0);
		case 3 : UseAnim(playerid,"CAMERA","camstnd_cmon",4.0,0,0,0,0,0);
		case 4 : UseAnim(playerid,"PED","endchat_01",4.1,0,1,1,0,0);
		default : SyntaxCMD(playerid, "/wave [1-4]");
	}
	return true;
}

CMD:police(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/police [1-4]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"POLICE","CopTraf_Away",3.0,1,0,0,1,0);
		case 2 : UseAnim(playerid,"POLICE","CopTraf_Come",3.0,1,0,0,1,0);
		case 3 : UseAnim(playerid,"POLICE","CopTraf_Left",3.0,1,0,0,1,0);
		case 4 : UseAnim(playerid,"POLICE","CopTraf_Stop",3.0,1,0,0,1,0);
		default : SyntaxCMD(playerid, "/police [1-4]");
	}
	return true;
}

CMD:crack(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/crack [1-7]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"CRACK","crckdeth2",3.0,1,1,1,1,0);
		case 2 : UseAnim(playerid,"CRACK","crckdeth4",3.0,0,1,1,1,0);
		case 3 : UseAnim(playerid,"CRACK","crckidle1",3.0,0,1,1,1,0);
		case 4 : UseAnim(playerid,"CRACK","crckidle2",3.0,0,1,1,1,0);
		case 5 : UseAnim(playerid,"CRACK","crckidle3",3.0,0,1,1,1,0);
		case 6 : UseAnim(playerid,"CRACK","crckdeth1",3.0,0,1,1,1,0);
		case 7 : UseAnim(playerid,"CRACK","crckdeth3",3.0,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/crack [1-7]");
	}
	return true;
}

CMD:car(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/car [1-11]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"LOWRIDER","lrgirl_bdbnce",4.1,0,1,1,1,0);
		case 2 : UseAnim(playerid,"LOWRIDER","lrgirl_hair",4.1,0,1,1,1,0);
		case 3 : UseAnim(playerid,"LOWRIDER","lrgirl_idle_to_l0",4.1,0,1,1,1,0);
		case 4 : UseAnim(playerid,"PED","Tap_hand",4.1,0,1,1,1,0);
		case 5 : UseAnim(playerid,"PED","Tap_handP",4.1,0,1,1,1,0);
		case 6 : UseAnim(playerid,"LOWRIDER","lrgirl_l12_to_l0",4.1,0,1,1,1,0);
		case 7 : UseAnim(playerid,"LOWRIDER","lrgirl_l2_to_l3",4.1,0,1,1,1,0);
		case 8 : UseAnim(playerid,"PED","CAR_LB",4.1,0,1,1,1,0);
		case 9 : UseAnim(playerid,"PED","CAR_sitp",4.1,0,1,1,1,0);
		case 10 : UseAnim(playerid,"PED","CAR_sitpLO",4.1,0,1,1,1,0);
		case 11 : UseAnim(playerid,"CAR_CHAT","carfone_loopA",4.1,1,1,1,1,0);
		default : SyntaxCMD(playerid, "/car [1-11]");
	}
	return true;
}

CMD:wallow(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/wallow [1-2]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll",4.1,0,1,1,1,0);
		case 2 : UseAnim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F",4.1,0,1,1,1,0);
		default : SyntaxCMD(playerid, "/wallow [1-2]");
	}
	return true;
}

CMD:beckon(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/beckon [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"RYDER","RYD_Beckon_01",4.1,0,1,1,1,1);
		case 2 : UseAnim(playerid,"RYDER","RYD_Beckon_02",4.1,0,1,1,1,1);
		case 3 : UseAnim(playerid,"RYDER","RYD_Beckon_03",4.1,0,1,1,1,1);
		default : SyntaxCMD(playerid, "/beckon [1-3]");
	}
	return true;
}

CMD:shotgun(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/shotgun [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"SHOTGUN","shotgun_crouchfire",4.1,0,1,1,1,1);
		case 2 : UseAnim(playerid,"SHOTGUN","shotgun_fire",4.1,0,1,1,1,1);
		case 3 : UseAnim(playerid,"SHOTGUN","shotgun_fire_poor",4.1,0,1,1,1,1);
		default : SyntaxCMD(playerid, "/shotgun [1-3]");
	}
	return true;
}

CMD:colt(playerid, params[]) {

	if(sscanf(params, "d", params[0])) return SyntaxCMD(playerid, "/colt [1-3]");
	switch(params[0]) {
		case 1 : UseAnim(playerid,"COLT45","colt45_fire_2hands",4.1,0,1,1,1,1);
		case 2 : UseAnim(playerid,"COLT45","colt45_reload",4.1,0,1,1,1,1);
		case 3 : UseAnim(playerid,"COLT45","sawnoff_reload",4.1,0,1,1,1,1);
		default : SyntaxCMD(playerid, "/colt [1-3]");
	}
	return true;
}

CMD:me(playerid, params[])
{
	if(sscanf(params,"s[128]", params[0])) 
		return SyntaxCMD(playerid, "/me [действие]");
	
	new str[180];
	Log_Write("logs/chat_log.txt", "[%s] [me] * %s %s", ReturnDate(), sendername( playerid, true ), params[0]);
		
	format(str, sizeof(str), "* %s %s", sendername( playerid, true ), params[0]);
	linebreak(playerid, str, 15.0, COLOR_ME, COLOR_ME, COLOR_ME, COLOR_ME, COLOR_ME);
    
	return 1;
}
CMD:w(playerid, params[])
{
	if(sscanf(params,"ds[128]", params[0], params[1])) return SyntaxCMD(playerid, "/w [id] [text]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(params[0], xyz);
	if(!PlayerToPoint(5.0, playerid, xyz)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится рядом с выбраным игроком!");
	
	new str[180];
	format(str, sizeof(str), "%s шепчет вам: %s", sendername(playerid, true), params[1]);
	SCM(params[0], COLOR_GRAY, str);
	format(str, sizeof(str), "Вы прошептали %s: %s", sendername(params[0], true), params[1]);
	SCM(playerid, COLOR_GRAY, str);
	return 1;
}
CMD:low(playerid, params[])
{
	if(sscanf(params,"s[128]", params[0])) 
		return SyntaxCMD(playerid, "/low [текст]");
	
	new str[180];
	Log_Write("logs/chat_log.txt", "[%s] %s шепчет: %s", ReturnDate(), sendername(playerid, true), params[0]);
	format(str, sizeof(str), "%s шепчет: %s", sendername(playerid, true), params[0]);
	linebreak(playerid, str, 2.0, 0xcbcbcbAA, 0xcbcbcbAA, 0xcbcbcbAA, 0xb0b0b0AA, 0x8c8c8cAA);
	return 1;
}
ALTX:low("/l");

CMD:do(playerid, params[])
{
	if(sscanf(params,"s[128]", params[0])) 
		return SyntaxCMD(playerid, "/do [действие]");
	new string[180];
	Log_Write("logs/chat_log.txt", "[%s] [do] * %s (( %s ))", ReturnDate(), params[0], sendername( playerid, true ));
 		
	format( string, sizeof(string), "* %s (( %s )) " , params[0], sendername( playerid, true ));
	linebreak(playerid, string, 15.0, COLOR_ME, COLOR_ME, COLOR_ME, COLOR_ME, COLOR_ME);
	
	//ProxDetector( 15.0, GetPlayerVirtualWorld( playerid ), playerid, string, string, COLOR_ME, COLOR_ME, COLOR_ME, COLOR_ME, COLOR_ME );
    return 1;
}
CMD:coin(playerid)
{
    new string[128], result[8], rand = random(2);
    if(rand) format(result, 8, "орел");
    else format(result, 8, "решка");
    format( string, 128, "* %s подкидывает монетку и выпадает %s" , sendername( playerid,true ), result);
	ProxDetector( 15.0, GetPlayerVirtualWorld( playerid ), playerid, string, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE );
}

CMD:dice(playerid)
{
    new string[128], rand = 1+random(5);
    format( string, 128, "* %s кидает кости и выпадает %d" , sendername( playerid,true ), rand);
	ProxDetector( 15.0, GetPlayerVirtualWorld( playerid ), playerid, string, string, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE, COLOR_PURPLE );
}

CMD:getcar(playerid, params[])
{
	new v;
	if(sscanf(params,"d", v)) return SyntaxCMD(playerid, "/(g)et(c)ar [id car]");
	if(veh_info[v][owner] > 0 && veh_info[v][owner] == character_info[playerid][id])
	{
		DestroyCheckpoint(playerid);
		new Float:x, Float:y, Float:z;
		GetVehiclePos(v, xyz);
		SetPVarInt(playerid, "search_checkpoint", 1);
		SetPlayerCheckpoint(playerid, xyz, 3.0);
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам не пренадлежит этот транспорт!");
	
	return 1;
}

ALTX:getcar("/gc");
CMD:lock(playerid)
{
	for(new i=1; i<MAX_VEHICLES; i++)
	{
	    new Float:x, Float:y, Float:z;
	    GetVehiclePos(i, xyz);
	    if(GetPlayerVehicleID(playerid) == i || PlayerToPoint(2.5, playerid, xyz) && GetVehicleVirtualWorld(i) == GetPlayerVirtualWorld(playerid))
		{
			if(veh_info[i][owner] < 0 && !InFactionId(playerid, ntop(veh_info[i][owner]))) 
				return 1;
			
			if(veh_info[i][owner] > 0 && veh_info[i][owner] != character_info[playerid][id] && !searchitemcount(playerid, 149, veh_info[i][id])) 
				return 1;
			
			if(veh_info[i][lock] == false)
		    {
				veh_info[i][lock] = true;
				GameTextForPlayer(playerid, "~r~CAR CLOSED", 1000, 3);
            }
			else
		    {
				veh_info[i][lock] = false;
    			GameTextForPlayer(playerid, "~g~CAR OPEN", 1000, 3);
            }
			UpdateVehParams(i);
   			break;
		}
	}
	return 1;
}

CMD:wi(playerid, params[])
{
	if(sscanf(params,"d", params[0])) params[0] = 5;
	for(new i=1; i<MAX_VEHICLES; i++)
	{
	    //PlayerToPoint(playerid, 2.0, veh_info[i][posX], veh_info[i][posY], veh_info[i][posZ])
	    if(GetPlayerVehicleID(playerid) == i)
		{
			if(IsMoto(i))
			{
				veh_info[i][window_1] = false;
				veh_info[i][window_2] = false;
				veh_info[i][window_3] = false;
				veh_info[i][window_4] = false;
				UpdateVehParams(i);
				SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете закрыть стекла этого транспорта!");
				return 1;
			}
			
			//----------------------------------------------------
			if(veh_info[i][window_1] == false && params[0] == 1)
			{
				veh_info[i][window_1] = true;
				GameTextForPlayer(playerid, "~r~WINDOWS CLOSED", 1000, 3);
				SYS_AME(playerid, "закрывает окна транспорта.");
			}
			else if(veh_info[i][window_1] == true && params[0] == 1)
			{
				veh_info[i][window_1] = false;
				GameTextForPlayer(playerid, "~r~WINDOWS OPEN", 1000, 3);
				SYS_AME(playerid, "открывает окна транспорта.");
			}
			//----------------------------------------------------
			else if(veh_info[i][window_2] == false && params[0] == 2)
			{
				veh_info[i][window_2] = true;
				GameTextForPlayer(playerid, "~r~WINDOWS CLOSED", 1000, 3);
				SYS_AME(playerid, "закрывает окна транспорта.");
			}
			else if(veh_info[i][window_2] == true && params[0] == 2)
			{
				veh_info[i][window_2] = false;
				GameTextForPlayer(playerid, "~r~WINDOWS OPEN", 1000, 3);
				SYS_AME(playerid, "открывает окна транспорта.");
			}
			//----------------------------------------------------
			else if(veh_info[i][window_3] == false && params[0] == 3)
			{
				veh_info[i][window_3] = true;
				GameTextForPlayer(playerid, "~r~WINDOWS CLOSED", 1000, 3);
				SYS_AME(playerid, "закрывает окна транспорта.");
			}
			else if(veh_info[i][window_3] == true && params[0] == 3)
			{
				veh_info[i][window_3] = false;
				GameTextForPlayer(playerid, "~r~WINDOWS OPEN", 1000, 3);
				SYS_AME(playerid, "открывает окна транспорта.");
			}
			//----------------------------------------------------
			else if(veh_info[i][window_3] == false && params[0] == 4)
			{
				veh_info[i][window_3] = true;
				GameTextForPlayer(playerid, "~r~WINDOWS CLOSED", 1000, 3);
				SYS_AME(playerid, "закрывает окна транспорта.");
			}
			else if(veh_info[i][window_3] == true && params[0] == 1)
			{
				veh_info[i][window_3] = false;
				GameTextForPlayer(playerid, "~r~WINDOWS OPEN", 1000, 4);
				SYS_AME(playerid, "открывает окна транспорта.");
			}
			
			//----------------------------------------------------
			else if(!veh_info[i][window_1] || !veh_info[i][window_2] || !veh_info[i][window_3] || !veh_info[i][window_4])
			{
				veh_info[i][window_1] = true;
				veh_info[i][window_2] = true;
				veh_info[i][window_3] = true;
				veh_info[i][window_4] = true;
				GameTextForPlayer(playerid, "~r~WINDOWS CLOSED", 1000, 3);
				SYS_AME(playerid, "закрывает окна транспорта.");
			}
			else
			{
				veh_info[i][window_1] = false;
				veh_info[i][window_2] = false;
				veh_info[i][window_3] = false;
				veh_info[i][window_4] = false;
				GameTextForPlayer(playerid, "~r~WINDOWS OPEN", 1000, 3);
				SYS_AME(playerid, "открывает окна транспорта.");
			}
			//------------------------------------------------------
			UpdateVehParams(i);
   			break;
		}
	}
	return 1;
}

CMD:li(playerid)
{
	if(isPlayerDriver(playerid))
	{
		 new i = GetPlayerVehicleID(playerid);
		 if(veh_info[i][owner] < 0 && !InFactionId(playerid, ntop(veh_info[i][owner])) || veh_info[i][owner] > 0 && veh_info[i][owner] != character_info[playerid][id]) return 1;
	     if(veh_info[i][lights] == false)
	     {
	        veh_info[i][lights] = true;
	        UpdateVehParams(i);
	        SYS_AME(playerid, "включил фары транспорта.");
	     }
		 else if(veh_info[i][lights] == true)
	     {
	        veh_info[i][lights] = false;
	        UpdateVehParams(i);
	        SYS_AME(playerid, "выключил фары транспорта.");
	     }
	}
	return 1;
}
ALTX:li("/lights", "/light");

CMD:en(playerid)
{
	if(isPlayerDriver(playerid))
	{
		 new i = GetPlayerVehicleID(playerid);
		 if(veh_info[i][engine] == false)
		 {
			 if(veh_info[i][owner] < 0 && !InFactionId(playerid, ntop(veh_info[i][owner])) || veh_info[i][owner] > 0 && veh_info[i][owner] != character_info[playerid][id] && !searchitemcount(playerid, 149, veh_info[i][id])) 
			 {
				if(checkitem(playerid,89) != -1) 
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете завести этот траснпорт, но вы можете попытаться воспользоваться отмычкой!");
				return 1;
			 }
		 }
	     if(veh_info[i][fuel] > 0 && veh_info[GetPlayerVehicleID(playerid)][engine] == false)
	     {
			new Float:vhealth;
			GetVehicleHealth(i, vhealth);
			if(vhealth <= 350 || veh_info[i][filling] > 0.0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот транспорт невозможно завести!");
	        veh_info[i][engine] = true;
	        UpdateVehParams(i);
			if(veh_info[i][alarm] && veh_info[i][owner] == character_info[i][id]) AlarmDisactivate(i);
	        SYS_AME(playerid, "завёл двигатель транспорта.");
	     }
		 else if(veh_info[i][engine] == true)
	     {
			if(IsBike(i)) return 1;
	        veh_info[i][engine] = false;
	        UpdateVehParams(i);
	        SYS_AME(playerid, "заглушил двигатель транспорта.");
	     }
		 else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} В транспорте недостаточно бензина!");
	}
	return 1;
}
ALTX:en("/engine");

CMD:nameoff(playerid)
{
    for(new i = GetPlayerPoolSize(); i != -1; --i) ShowPlayerNameTagForPlayer(playerid, i, false);
    return 1;
}
CMD:nameon(playerid)
{	
    for(new i = GetPlayerPoolSize(); i != -1; --i) ShowPlayerNameTagForPlayer(playerid, i, true);
    return 1;
}
CMD:admins(playerid)
{
	new str[180];
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Администраторы онлайн: ");
	foreach(new p : Player)
	{
		if(player_info[p][admin] >= 1)
		{
			new status[35];
			if(IsAduty(p)) format(status, sizeof(status), "{33AA33}(На дежурстве)");
			else format(status, sizeof(status), "{b1b1b1}(Не на дежурстве)");
			format(str, sizeof(str), ">{FFFFFF} (A%d) %s(%d) %s", player_info[p][admin], player_info[p][login], p, status);
			if(GetPVarInt(p, "SPEC") && player_info[playerid][admin] >= 2) format(str, sizeof(str), "%s{b1b1b1} > /sp %d", str, GetPVarInt(p, "SPEC_PLAYER"));
			SCM(playerid, COLOR_MSGSERVER, str);
		}
	}
	return 1;
}
CMD:move(playerid, params[])
{
    if(IsAdmin(playerid, 3)) return 1;
    if(sscanf(params,"d", params[0]))
	{
    	FreePlayer(GetPVarInt(playerid, "move_player"), true);
    	SetPVarInt(playerid, "move_player", -1);
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Перемещение игрока отключено!");
		return 1;
	}
	SetPVarInt(playerid, "move_player", params[0]);
	FreePlayer(params[0], false);
 	SetPlayerFacingAngle(params[0], -90);
 	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Перемещение игрока активированно!");
    return 1;
}

stock UpdateArm(playerid)
{
	SetPlayerArmour(playerid, GetPVarFloat(playerid, "arrmor"));
	return 1;
}

ALTX:graffiti("/graffity", "/graff", "/graf", "/grafity", "/grafiti");
CMD:graffiti(playerid)
{
    // 19482
	if(!InFactionType(playerid, FACTIONTYPE_GANG) && !InFactionType(playerid, FACTIONTYPE_MAFIA) && !IsPremium(playerid, PREMIUM_BRONZE)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна данная команда!");
	
	if(character_info[playerid][gun] != 41) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} В вашей руке должен быть балончик"); 
	
	new str[256], temp[32], temp_int;
	format(str, sizeof(str), "{FFFFFF}Установить граффити\t ");
	
	GetPVarString(playerid, "graf_text", temp, 32);
	if(strlen(temp) > 0)
		format(str, sizeof(str), "%s\nТекст граффити\t%s",str, temp);
	else 
		format(str, sizeof(str), "%s\nТекст граффити\t{AFAFAF}(Пусто){FFFFFF}",str);
	format(temp, sizeof(temp), "");
	
	GetPVarString(playerid, "graf_color", temp, 32);
	if(strlen(temp) > 0)
		format(str, sizeof(str), "%s\nЦвет граффити\t%s",str, temp);
	else 
		format(str, sizeof(str), "%s\nЦвет граффити\t{AFAFAF}(Пусто){FFFFFF}",str);
	format(temp, sizeof(temp), "");
	
	GetPVarString(playerid, "graf_font", temp, 32);
	
	if(strlen(temp) > 0)
		format(str, sizeof(str), "%s\nШрифт граффити\t%s",str, temp);
	else 
		format(str, sizeof(str), "%s\nШрифт граффити\t{AFAFAF}(Пусто){FFFFFF}",str);
	format(temp, sizeof(temp), "");
	
	temp_int = GetPVarInt(playerid, "graf_fontsize");
	if(temp_int)
		format(str, sizeof(str), "%s\nРазмер граффити\t%d",str, temp_int);
	else 
		format(str, sizeof(str), "%s\nРазмер граффити\t{AFAFAF}(Пусто){FFFFFF}",str);
	
	
	ShowPlayerDialog(playerid, 68, DIALOG_STYLE_TABLIST, "Граффити", str, "Выбрать", "Отмена");
	/*new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, xyz);
	new obj = CreateDynamicObject( 19482, xyz, 0,0,0, -1, 0, -1, 200);
	new _color[8];
	switch(random(6))
	{
		case 0: format(_color, sizeof(_color), "FFFFFF");
		case 1: format(_color, sizeof(_color), "00008B");
		case 2: format(_color, sizeof(_color), "8B0000");
		case 3: format(_color, sizeof(_color), "00FF00");
		case 4: format(_color, sizeof(_color), "000000");
		case 5: format(_color, sizeof(_color), "FFE4C4");
	}
	new str[64];
	format(str, sizeof(str), "{%s}fuck you", _color);
	SetDynamicObjectMaterialText(obj, 0, str, OBJECT_MATERIAL_SIZE_256x128, "Arial", 24, 1, COLOR_WHITE, 0, 0);
	SCM(playerid, COLOR_WHITE, str);*/
	return 1;
}

CMD:attach(playerid)
{
	CancelEdit(playerid);
	new str[256] = "Предмет\tЧасть тела\n";
	for(new i=0; i<MAX_ATTACH; i++)
	{
	    if(attach[playerid][i][iditem] != -1)
	    {
	        new bonename[24];
	        switch(attach[playerid][i][bone])
	        {
	            case 1:format(bonename, sizeof(bonename), "Спина");
				case 2:format(bonename, sizeof(bonename), "Голова");
				case 3:format(bonename, sizeof(bonename), "Плечо левой руки");
				case 4:format(bonename, sizeof(bonename), "Плечо правой руки");
				case 5:format(bonename, sizeof(bonename), "Левая рука");
				case 6:format(bonename, sizeof(bonename), "Правая рука");
				case 7:format(bonename, sizeof(bonename), "Левое бедро");
				case 8:format(bonename, sizeof(bonename), "Правое бедро");
				case 9:format(bonename, sizeof(bonename), "Левая нога");
				case 10:format(bonename, sizeof(bonename), "Правая нога");
				case 11:format(bonename, sizeof(bonename), "Правые икры");
				case 12:format(bonename, sizeof(bonename), "Левые икры");
				case 13:format(bonename, sizeof(bonename), "Левое предплечье");
				case 14:format(bonename, sizeof(bonename), "Правое предплечье");
				case 15:format(bonename, sizeof(bonename), "Левая ключица");
				case 16:format(bonename, sizeof(bonename), "Правая ключица");
				case 17:format(bonename, sizeof(bonename), "Шея");
				case 18:format(bonename, sizeof(bonename), "Челюсть");

	        }
			format(str, sizeof(str), "%s{FFFFFF}%s\t%s\n",str, Items[attach[playerid][i][iditem]][Name], bonename);
		}
		else
		    format(str, sizeof(str), "%s{AFAFAF}(Пусто)\n",str);
	}
	if(character_info[playerid][gun] != 0) 
		format(str, sizeof(str), "%s{AFAFAF}Редактирование положения текущего оружия\n",str);
	
	SPD(playerid, 22, DIALOG_STYLE_TABLIST_HEADERS, "Прикрепленные объекты", str, "Выбрать", "Отменить");
}

CMD:phoneinv(playerid)
{
	if(character_info[playerid][phoneslot] == -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телефона в слоте!");
	if(giveitem(playerid, 15, character_info[playerid][phoneslot]))
	{
	    SendServerMessage(playerid, "Телефон добавлен в инвентарь.");
		
		WireMsg(playerid, playerid, " выключает телефон.");
		
	    character_info[playerid][phoneslot] = -1;
	}
	return 1;
}

CMD:pagerinv(playerid)
{
	if(character_info[playerid][pager] == -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет пейджера в слоте!");
	if(giveitem(playerid, 341, character_info[playerid][pager]))
	{
	    SendServerMessage(playerid, "Пейджер добавлен в инвентарь.");
		
		
	    character_info[playerid][pager] = -1;
	}
	return 1;
}
CMD:time(playerid)
{
	new str[128];
    
    new timetopayday = (3600-character_info[playerid][payday]) / 60;
	format(str, sizeof(str), ">{FFFFFF} Сейчас %02d:%02d, %02d/%02d. До зарплаты: %02d минут(-ы)", hour, minute, day, month, timetopayday);
	
	
	SCM(playerid, COLOR_MSGSERVER, str);
	
	if(player_info[playerid][mute])
	{
		format(str, sizeof(str), ">{FFFFFF} Блокировка ООС чата: %d сек. .", player_info[playerid][mute]);
		SCM(playerid, COLOR_MSGSERVER, str);
	}
	
	if(character_info[playerid][jail_time])
	{
		format(str, sizeof(str), ">{FFFFFF} Срок в тюрьме: %d сек. .", character_info[playerid][jail_time]);
		SCM(playerid, COLOR_MSGSERVER, str);
	}
	
	if(character_info[playerid][ajail_time])
	{
		format(str, sizeof(str), ">{FFFFFF} Срок в админ тюрьме: %d сек. .", character_info[playerid][ajail_time]);
		SCM(playerid, COLOR_MSGSERVER, str);
	}

	
	return 1;
}
CMD:jailtime(playerid)
{
	new str[180];
	if(character_info[playerid][ajail_time] > 0)
	{
		format(str, sizeof(str), ">{FFFFFF} Осталось сидеть в админ тюрьме: %d минут", (character_info[playerid][ajail_time] / 60)+1);
		SCM(playerid, COLOR_MSGSERVER, str);
	}
	else if(character_info[playerid][jail_time] > 0)
	{
		format(str, sizeof(str), ">{FFFFFF} Осталось сидеть в тюрьме: %d минут", (character_info[playerid][jail_time] / 60)+1);
		SCM(playerid, COLOR_MSGSERVER, str);
	}
	else Sound_Fail(playerid);
	return 1;
}
CMD:phone(playerid)
{
	if(character_info[playerid][jail_time] > 0 || character_info[playerid][ajail_time] > 0) return 1;
	
    if(character_info[playerid][phoneslot] == -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте!");
	SPD(playerid, 28, DIALOG_STYLE_TABLIST_HEADERS, "Меню телефона", "Действие\tАльт. команда\n{FFFFFF}Отключить телефон\t{AFAFAF}(/phoneinv)\n{FFFFFF}Контакты\t{AFAFAF}(/contacts)\n{FFFFFF}Позвонить\t{AFAFAF}(/call)\n{FFFFFF}Отправить СМС\t{AFAFAF}(/sms)\n{FFFFFF}Список СМС\t{AFAFAF}(/smshistory)\n", "Выбрать", "Закрыть");
    return 1;
}
CMD:p(playerid)
{
	if(GetPVarInt(playerid, "call_qu") && !GetPVarInt(playerid, "call_qu_start"))
	{
		phoneAnim(playerid, 1);
	    new p = GetPVarInt(playerid, "call_qu")-1;
        DeletePVar(playerid, "call_qu"), DeletePVar(p, "call_qu"), DeletePVar(p, "call_qu_start"), DeletePVar(playerid, "call_qu_start");
		SetPVarInt(playerid, "call", p+1);
		SetPVarInt(p, "call", playerid+1);
		SendServerMessage(playerid, "Вы взяли трубку.");
		SendServerMessage(p, "Абонент взял трубку!");
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам никто не звонит!");
}
CMD:h(playerid)
{
	if(GetPVarInt(playerid, "call_qu") != 0)
	{
	    new p = GetPVarInt(playerid, "call_qu")-1;
		DeletePVar(playerid, "call_qu"), DeletePVar(p, "call_qu"), DeletePVar(p, "call_qu_start"), DeletePVar(playerid, "call_qu_start");
		phoneAnim(playerid, 0);
		phoneAnim(p, 0);
		SendServerMessage(p, "Вызов завершен!");
  		SendServerMessage(playerid, "Вызов завершен!");
		WireMsg(playerid, p, " | Вызов завершен!");
	}
	else if(GetPVarInt(playerid, "call") != 0)
	{
 		new p = GetPVarInt(playerid, "call")-1;
		DeletePVar(playerid, "call"), DeletePVar(p, "call");
		SendServerMessage(p, "Звонок завершен!");
		phoneAnim(playerid, 0);
		phoneAnim(p, 0);
  		SendServerMessage(playerid, "Звонок завершен!");
		WireMsg(playerid, p, " | Звонок завершен!");
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет входящих/исходящих вызовов.");

	if(GetPayphone(playerid) != -1) {
		UnusePayphone(playerid, GetPayphone(playerid));
	} 
	return 1;
}
CMD:call(playerid, params[])
{
    if(GetPVarInt(playerid, "call_qu") != 0 || GetPVarInt(playerid, "call") != 0)
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете звонить сейчас!");

	new number_unformat[25];
    if(sscanf(params,"s[25]", number_unformat)) return SyntaxCMD(playerid, "/call [номер / имя контакта]");

    new phonenumber = GetPhonenumber(playerid);
    if(phonenumber == -1) {
    	return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте!");
    }
    if(IsPlayerAtPayphone(playerid, phonenumber-1000) != -1) {
    	if(takemoney(playerid, 5, "use payphone") != 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
    	UsePayphone(playerid, phonenumber-1000);
    }

    new number_rec = search_phonenumber(playerid, number_unformat);
    
    if(number_rec < 1) number_rec = strval(number_unformat);
    if(number_rec == 314159)
	{
		if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) 
			return SCM(playerid, COLOR_PAPAYA, "Вызов завершен!");
		
		if(factions[character_info[playerid][faction]][guns] == 0 && factions[character_info[playerid][faction]][drugs] == 0 && factions[character_info[playerid][faction]][bulls] == 0)
		{
		    SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: У меня нет времени с тобой трепать, ты и так многое от меня получил.");
		    SCM(playerid, COLOR_PAPAYA, "Вызов завершен!");
		    SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Если у вас уже существует заказ, используйте /deliver!");
		    return 1;
		}
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы можете использовать /deliver, как альтернативный способ, чтобы доставить заказ!");
		new r;
		if(GetPVarInt(playerid, "deal_called")) r = random(16);
		else r = random(8);
		switch(r)
		{
			case 0: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Решай быстрее...");
			case 1: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Я буду в городе ровно час, говори что тебе надо.");
            case 2: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Это я, ты готов?");
            case 3: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Я только вернулся, выбирай.");
            case 4: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: ...");
            case 5: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Где ты пропадаешь?!");
            case 6: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Алло... Кто это?!");
            case 7: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Это ты?");

            case 8: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Может прекратишь мне названивать?");
            case 9: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Кажется, ты уже звонил мне?");
            case 10: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: В чём дело? Мы же уже разговаривали...");
            case 11: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Мы же уже разговаривали...");
            case 12: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Опять ты?");
            case 13: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Это опять он!");
            case 14: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Он опять звонит!");
            case 15: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Мне кажется, или ты уже звонил?");
            default: SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Алло!");
		}
		SetPVarInt(playerid, "deal_called", 1);

  		new str[256];
  		format(str, sizeof(str), "Товар\tЦена\n");
        for(new i=0; i<sizeof(list_deal); i++)
        {
        	format(str, sizeof(str), "%s%s\t%d$\n", str, senderitems(list_deal[i][iditem]), list_deal[i][price]);
        }
        ShowPlayerDialog(playerid, 64, DIALOG_STYLE_TABLIST_HEADERS, "Диллер", str, "Выбрать", "Отмена");
		return 1;
	}
	else if(number_rec == 911)
	{
		phoneAnim(playerid, 1);	
		ShowPlayerDialog(playerid, 129, DIALOG_STYLE_INPUT, "Вызвать 911", "9-1-1, что у Вас произошло?", "Ввод", "Отмена");
		return 1;
	}
	else if(number_rec == 555)
	{
		SCM(playerid, COLOR_GREEN, ">{ffffff} Вы вызвали такси!");
		new floatxyz;
		GetPlayerPos(playerid, xyz);
		SetPVarFloat(playerid, "taxiX", x); 
		SetPVarFloat(playerid, "taxiY", y);
		SetPVarFloat(playerid, "taxiZ", z);
		new str[180];
		new i;
		for(; i != sizeof(gSAZones); i++ )
		{
			if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) break;
		}
		
		format(str, sizeof(str), "%d вызвал такси! Район: %s. (/accept %d)", phonenumber, gSAZones[i][SAZONE_NAME], playerid);
		TaxiMsg(str);
		return 1;
	}
    foreach(new p : Player)
    {
        if(!IsPlayerConnected(p)) return 1;
		if(character_info[p][phoneslot] == number_rec)
		{
			new str[100], contacts_slot_sender = search_phonename(playerid, character_info[p][phoneslot]), contacts_slot_rec = search_phonename(p, phonenumber);
			
			phoneAnim(playerid, 1);
			
			new wire_str[180];
			format(wire_str, sizeof(wire_str), " вызывает %d", character_info[p][phoneslot]);
			WireMsg(playerid, p, wire_str);
			
			if(contacts_slot_rec == -1)
			{
				format(str, sizeof(str), ">{FFFFFF} Вам звонит неизвестный номер(%d), введите /p чтобы поднять трубку.", phonenumber);
			}
			else
			{
				format(str, sizeof(str), ">{FFFFFF} Вам звонит %s (%d), введите /p чтобы поднять трубку.", contacts_info[p][contacts_slot_rec][Name], phonenumber);
			}
			SCM(p, COLOR_MSGSERVER, str);

			if(contacts_slot_sender == -1)
			{
				format(str, sizeof(str), ">{FFFFFF} Вы звоните на номер %d.", character_info[p][phoneslot]);
			}
			else
			{
				format(str, sizeof(str), ">{FFFFFF} Вы звоните на номер %s (%d).", contacts_info[playerid][contacts_slot_sender][Name], character_info[p][phoneslot]);
			}
			SCM(playerid, COLOR_MSGSERVER, str);

			SetPVarInt(p, "call_qu", playerid+1);
			SetPVarInt(playerid, "call_qu", p+1);
			SetPVarInt(playerid, "call_qu_start", true);
			phoneAnim(playerid, 1);
			return 1;
		}
    }
    SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный номер не обслуживается!");
    return 1;
}

CMD:dellallveh(playerid)
{
	if(IsAdmin(playerid, 6)) return 1;
	for(new i; i<MAX_VEHICLES; i++)
	{
		if(veh_info[i][owner] == 0) 
			DestroyVehicle(i);
	}
	SendAdminMessage(playerid, "Вы удалили все автомобили!");
	return 1;
}
CMD:charity(playerid, params[])
{
	if(sscanf(params,"d", params[0])) SyntaxCMD(playerid, "/charity [money]");
	if(params[0] < 1 || params[0] > 999999999) return 1; 
	if(takemoney(playerid, params[0], "charity"))
	{
		new str[128];
		format(str, sizeof(str), "сливает %d$", params[0]);
		PlayerLog(playerid, str);
	}
	return 1;
}
CMD:carcolor(playerid, params[])
{
	if(sscanf(params,"dd", params[0], params[1])) 
		return SyntaxCMD(playerid, "/carcolor [color 1] [color 2]");
	
	if(GetPVarInt(playerid, "Freezed")) 
		return 1;
	
	new v = GetPlayerVehicleID(playerid);
	
	if(v <= 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не сидите в автомобиле!");
	
	if(veh_info[v][owner] != character_info[playerid][id]) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не владелец этого автомобиля!");
	
	if(takemoney(playerid, 250, "carcolor") == 1)
	{
		veh_info[v][vcolor1] = params[0];
		veh_info[v][vcolor2] = params[1];
		ChangeVehicleColor(v, veh_info[v][vcolor1], veh_info[v][vcolor2]);
		SendServerMessage(playerid, "Вы изменили цвет автомобиля!");
		OOCMSG(playerid, "перекрасил свой автомобиль");
		Freeze(playerid, 3000);
	}
	else
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег! (250$)");
	return 1;
}

CMD:cctvoff(playerid)
{
	if(IsAdmin(playerid, SUPER_ADMIN)) return 1;
	if(cctvoff) 
	{
		Sound_Fail(playerid);
		cctvoff = 0;
	}
	else 
	{
		Sound_Succ(playerid);
		cctvoff = 1;
	}
	return 1;
}

CMD:setradio(playerid, params[])
{
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/setradio [id]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	new floatxyz;
	GetPlayerPos(params[0], xyz);
	if(!PlayerToPoint(5.0, playerid, xyz) && !GetPVarInt(params[0], "ether")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь возле выбранного игрока!");
	
	if(GetPVarInt(params[0], "ether"))
	{
		new str[128];
		format(str, sizeof(str), ">{FFFFFF} Вы отняли у %s доступ в эфир!", sendername(params[0], true));
		SCM(playerid, COLOR_MSGSERVER, str);
		SendServerMessage(playerid, "Вы потеряли доступ к эфиру!");
		DeletePVar(params[0], "ether");
		DeletePVar(params[0], "in_ether");
	}
	else
	{
		new str[128];
		format(str, sizeof(str), "Вы предоставили %s доступ в эфир!", sendername(params[0], true));
		SCM(playerid, COLOR_MSGSERVER, str);
		format(str, sizeof(str), "%s предоставил вам доступ в эфир! Используйте /radio, чтобы начать вещать.", sendername(playerid, true));
		SendServerMessage(params[0], "Вы потеряли доступ к эфиру!");
		SetPVarInt(params[0], "ether", 1);
	}
	return 1;
}

CMD:music(playerid)
{
	if(!IsPlayerInAnyVehicle(playerid))
		return SyntaxCMD(playerid, "в транспорте!");
	
	new str[1024];
	
	for(new i; i<sizeof(Music); i++) 
		format(str, sizeof(str), "%s%s\n",str, Music[i][name]);
	
	return Dialog_Show(playerid, RADIO_STATION, DIALOG_STYLE_LIST, "Радио станции", str, "PLAY", "STOP");	
}

CMD:radio(playerid)
{
	if(!InFactionId(playerid, SAN_FACTION) && !GetPVarInt(playerid, "ether")) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет доступа к этой команде!");
	
	if(GetPVarInt(playerid, "in_ether"))
	{
		fmsg(playerid, "покинул эфир", SAN_FACTION);
		SendServerMessage(playerid, "Вы покинули эфир!");
		DeletePVar(playerid, "in_ether");
	}
	else
	{
		fmsg(playerid, "вошел в эфир", SAN_FACTION);
		SendServerMessage(playerid, "Вы вошли в эфир!");
		SetPVarInt(playerid, "in_ether", 1);
	}
	return 1;
}
CMD:sanoff(playerid)
{
	if(GetPVarInt(playerid, "san_off"))
	{
		SendServerMessage(playerid, "Вы включили SAN чаты!");
		DeletePVar(playerid, "san_off");
	}
	else 
	{
		SendServerMessage(playerid, "Вы отключили SAN чаты!");
		SetPVarInt(playerid, "san_off", 1);
	}

}

CMD:ad(playerid, params[])
{
	if(sscanf(params,"s[120]", params[0])) 
		return SyntaxCMD(playerid, "/ad [текст]");

	new lastad = GetPVarInt(playerid, "ad_last");
	
	if(lastad > gettime())
		return SCM(playerid, COLOR_ME, "* Из телефона доносятся короткие гудки");
	
	if(character_info[playerid][phoneslot] == -1)
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет активного телефона!"); 
	
	if(takemoney(playerid, 50, "buy ads") != 1) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!"); 
	
	if(!AddAd(playerid, params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} К сожалению, сейчас нельзя подать объявление. Попробуйте позже...");
	
	SendServerMessage(playerid, "Ваше объявление отправлено на модерацию!");
	SetPVarInt(playerid, "ad_last", gettime()+30);
	return 1;
}

CMD:admenu(playerid)
{
	if(!InFactionId(playerid, SAN_FACTION)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет доступа к этой команде!");
	
	new str[180*MAX_AD], temp[1080];
	
	format(temp, sizeof(temp), "Отправитель \t Сообщение \n");
	format(str, sizeof(str), "%s%s\n", str, temp);
	for(new i; i<MAX_AD; i++)
	{
		if(ads_info[i][owner] == -1)
			format(temp, sizeof(temp), "{b1b1b1} - \t - ");
		else 
			format(temp, sizeof(temp), "{ffffff}%s\t%s",sendername(ads_info[i][owner]), ads_info[i][msg]);

		format(str, sizeof(str), "%s%s\n", str, temp);
	}
	ShowPlayerDialog(playerid, 136, DIALOG_STYLE_TABLIST_HEADERS, "ADMENU", str, "Выбрать", "Отмена");
	return 1;
}
ALTX:admenu("/editad");

CMD:gps(playerid)
{
	new str[256];
	
	if(character_info[playerid][phoneslot] || IsPlayerInAnyVehicle(playerid)) 
	{
		for(new i; i<sizeof(gps_data); i++)
		{
			format(str, sizeof(str), "%s%s\n", str, gps_data[i][Name]);
		}
		ShowPlayerDialog(playerid, 137, DIALOG_STYLE_LIST, "GPS", str, "Выбрать", "Отмена");
	}
	else
	{
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте или вы не в транспорте!");
	}
	return 1;
}


CMD:getname(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	if(sscanf(params,"s[25]", params[0])) return SyntaxCMD(playerid, "/getname [name / login]");
	new qu[139+25+25];
	format(qu, sizeof(qu), "select users.login, characters.name FROM users join characters on users.id=characters.userid where users.login='%s' or characters.name='%s'", params[0],params[0]);
	mysql_function_query(dbHandle, qu, true, "OnGetName", "d", playerid);
	return 1;
}

ALTX:spawncar("/respawncar");
CMD:spawncar(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/spawncar [id car]");
	SetVehicleVirtualWorld(params[0], veh_info[params[0]][VW]);
	SetVehicleToRespawn(params[0]);
	return 1;
}
CMD:menu(playerid)
{
		new str[512] = "{AFAFAF}Действие\t{AFAFAF}Альтернативная команда\n";
		format(str, sizeof(str), "%s{FFFFFF}Статистика персонажа\t{AFAFAF}(/stats)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Инвентарь\t{AFAFAF}(/inventory)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Помощь по командам\t{AFAFAF}(/help)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Отправить сообщение администрации\t{AFAFAF}(/report)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Задать вопрос\t{AFAFAF}(/ask)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Смена персонажа\t{AFAFAF}(/relogin)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Описание персонажа\t{AFAFAF}(/description)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Настройки\t{AFAFAF}(/settings)", str);
		SPD(playerid, 139, DIALOG_STYLE_TABLIST_HEADERS, "Игровое меню", str, "Выбрать", "Закрыть");
		return 1;
	}
ALTX:menu("/mm", "/mn");

// ---------------------------------------------------------------------------------
CMD:db(playerid)
{
	for(new i=0; i<MAX_PROP; i++)
	{
		if(prop_info[i][id] == 0) continue;
		if(PlayerToPoint(2.0, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid])
		{
			foreach(new p : Player) if(character_info[p][prop] == prop_info[i][id]) SendServerMessage(p, "Кто-то звонит в дверь!");  
			cmd_me(playerid, "звонит в дверь.");
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны стоять возле двери!");
	return 1;
}
CMD:ddo(playerid, params[])
{
	if(sscanf(params,"s[180]", params[0])) return SyntaxCMD(playerid, "/ddo [текст]");
	for(new i=0; i<MAX_PROP; i++)
	{
		if(prop_info[i][id] == 0) continue;
		if(PlayerToPoint(4.0, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid] || PlayerToPoint(4.0, playerid, Interiors[prop_info[i][serverint]][posX], Interiors[prop_info[i][serverint]][posY], Interiors[prop_info[i][serverint]][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][id]+200 && GetPlayerInterior(playerid) == Interiors[prop_info[i][serverint]][Interior])
		{
			new str[180];
			Log_Write("logs/chat_log.txt", "[%s] * %s (( %s (Дверь) ))", ReturnDate(), params[0], sendername(playerid, true));
			format(str, sizeof(str), "* %s (( %s (Дверь) )) ", params[0], sendername(playerid, true));
			foreach(new p : Player) if(character_info[p][prop] == prop_info[i][id] || PlayerToPoint(4.0, p, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(p) == prop_info[i][vworld] && GetPlayerInterior(p) == prop_info[i][intid]) SCM(p, COLOR_WHITE, str);  
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны стоять возле двери!");
	return 1;	
}
CMD:ds(playerid, params[])
{
	if(sscanf(params,"s[180]", params[0])) return SyntaxCMD(playerid, "/ds [текст]");
	for(new i=0; i<MAX_PROP; i++)
	{
		if(prop_info[i][id] == 0) continue;
		if(PlayerToPoint(4.0, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid] || PlayerToPoint(4.0, playerid, Interiors[prop_info[i][serverint]][posX], Interiors[prop_info[i][serverint]][posY], Interiors[prop_info[i][serverint]][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][id]+200 && GetPlayerInterior(playerid) == Interiors[prop_info[i][serverint]][Interior])
		{
			new str[180];
			format(str, sizeof(str), "(Дверь) %s кричит: %s", sendername(playerid, true), params[0]);
			foreach(new p : Player) if(character_info[p][prop] == prop_info[i][id] || PlayerToPoint(4.0, p, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(p) == prop_info[i][vworld] && GetPlayerInterior(p) == prop_info[i][intid]) SCM(p, COLOR_WHITE, str);  
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны стоять возле двери!");
	return 1;
}
CMD:voice(playerid, params[])
{
	if(sscanf(params,"s[32]", params[0])) 
		return SyntaxCMD(playerid, "/voice [описание голоса]");
	
	format(character_info[playerid][voice], 32, "%s", params[0]);
	if(!CompareStrings(params[0], "off"))
		SendServerMessage(playerid, "Вы сохранили описание голоса. Используйте /voice off для того, чтобы отключить его.");
	else 
		SendServerMessage(playerid, "Вы отключили описание голоса!");

	new str[26+32];
	format(str, sizeof(str), "описал голос персонажа: %s", params[0]);
	PlayerLog(playerid, str);

	new qu[52+11+32];
	mysql_real_escape_string(params[0], params[0]);
	format(qu, sizeof(qu), "update characters set voice='%s' where id=%d limit 1", params[0], character_info[playerid][id]);
	mysql_function_query(dbHandle, qu, false, "", "");
	return 1;
}
ALTX:towing("/tow", "/towcar");
CMD:towing(playerid)
{
	new v = GetPlayerVehicleID(playerid);
	new bool:Driver = false;
	if(isPlayerDriver(playerid)) Driver = true;
	if(!Driver || GetVehicleModel(v) != 525) return SendErrorMessage(playerid, "Вы должны находится в специализированном транспорте!");
	if(!veh_info[v][engine]) return SendErrorMessage(playerid, "Вы должны завести транспорт для использования этой команды!");
	
	for(new i; i<MAX_VEHICLES; i++)
	{
		new floatxyz;
		GetVehiclePos(i, xyz);
		if(PlayerToPoint(8.0, playerid, xyz) && i != v)
		{
			AttachTrailerToVehicle(i, v);
			veh_info[v][towing] = i;
			return SendServerMessage(playerid, "Вы прицепили автомобиль, используйте команду /untowing чтобы отцепить авто.");
		}
	}
	SendErrorMessage(playerid, "Рядом нет автомобилей, которые можно подцепить!");

	return 1;
}
CMD:untowing(playerid)
{
	new v = GetPlayerVehicleID(playerid);
	new bool:Driver = false;
	if(isPlayerDriver(playerid)) Driver = true;
	if(!Driver || GetVehicleModel(v) != 525) return SendErrorMessage(playerid, "Вы должны находится в специализированном транспорте!");
	if(!veh_info[v][engine]) return SendErrorMessage(playerid, "Вы должны завести транспорт для использования этой команды!");

	DetachTrailerFromVehicle(v);
	SendServerMessage(playerid, "Вы отцепили автомобиль!");
	return 1;
}

/*
CMD:craft(playerid)
{
	new str[256] = "Добавить предмет\n";
	new count_craft;
	for(new i; i < MAX_CRAFT; i++) if(craft_info[playerid][cItem][i] != 0) count_craft++;
	
	// Test crafting > 2 items
	if(count_craft < 2) format(str, sizeof(str), "%s{b1b1b1}Совместить\n", str);
	else format(str, sizeof(str), "%sСовместить\n", str);
	count_craft = 0;

	// while output selected items for craft
	for(new i; i < MAX_CRAFT; i++)
	{ 
		if(craft_info[playerid][cItem][i] != 0) 
		{
			count_craft++;
			format(str, sizeof(str), "%s{b1b1b1}%d. %s (%d)\n", str, i+1, senderitems(craft_info[playerid][cItem][i]), craft_info[playerid][cCount][i]);
		}
		else format(str, sizeof(str), "%s{b1b1b1}%d. Пусто\n", str, i+1);
	}
	if(count_craft != 0) // if > 0 items searched in while
		format(str, sizeof(str), "%sОчистить\n", str);		

	ShowPlayerDialog(playerid, 150, DIALOG_STYLE_LIST, "CRAFT", str, "Выбрать", "Отмена");
	return 1;
}
*/

CMD:changegunattach(playerid)
{
	if(character_info[playerid][gun] == 0) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не используете оружия!");
	
	ShowPlayerDialog(playerid, 85, DIALOG_STYLE_TABLIST, "Выберите кость", "Спина\nГолова\nПлечо левой руки\nПлечо правой руки\nЛевая рука\nПравая рука\nЛевое бедро\nПравое бедро\nЛевая нога\nПравая нога\nПравые икры\nЛевые икры\nЛевое предплечье\nПравое предплечье\nЛевая ключица\nПравая ключица\nШея\nЧелюсть", "Выбрать", "Отмена");
	return 1;
}

CMD:help(playerid)
{
	SPD(playerid, 120, DIALOG_STYLE_LIST, "Помощь по серверу", "Общие команды\nКоманды для отыгровки и чаты\nТранспорт\nПейджер и телефон\nОружие\nФракции\nРация", "Далее", "Закрыть");
	return 1;
}
ALTX:help("/рудз");

CMD:ca(playerid)
{
	if(GetPVarInt(playerid, "CAOFF"))
	{
		SendServerMessage(playerid, "Вы включили анимацию разговора!");
		DeletePVar(playerid, "CAOFF");
	}
	else 
	{
		SendServerMessage(playerid, "Вы выключили анимацию разговора!");
		SetPVarInt(playerid, "CAOFF", 1);
	}
	return 1;
}
CMD:stats(playerid, params[])
{
	new p;
	if(IsAdmin(playerid, 2, true)) 
		p = playerid;
	else if(sscanf(params,"u", p)) 
		p = playerid;
	
	new string[180];
	format(string, sizeof(string), "____________%s %d/%d/%d %d:%d ____________",sendername(p, true),day, month, year, hour, minute);
	SCM(playerid,COLOR_GREEN, string);
	
	format(string, sizeof(string), "ПЕРСОНАЖ | Фракция: %s[%d] | Ранг: %s[%d] | Дата рождения: %s", factions[character_info[p][faction]][Name], character_info[p][faction], faction_ranks[character_info[p][faction]][character_info[p][rank]], character_info[p][rank], character_info[p][birthDate]);
	SCM(playerid,COLOR_WHITE, string);
	
	format(string, sizeof(string), "ПЕРСОНАЖ | Деньги: %d$ | В банке: %d$ | Время до PayDay: %d минут", character_info[p][money], character_info[p][bank], (3600-character_info[p][payday]) / 60);
	SCM(playerid,COLOR_WHITE, string);

	new str[30];
	if(character_info[p][addiction] >= ADDICTION_HIGHT) 
		format(str, sizeof(str), "{FF6347}Высокий{FFFFFF}");
	else if(character_info[p][addiction] >= ADDICTION_LOW) format(str, sizeof(str), "{FFFF00}Средний{FFFFFF}");
	else if(character_info[p][addiction] >= 10) format(str, sizeof(str), "{33AA33}Низкий{FFFFFF}");
	else if(character_info[p][addiction] >= 0) format(str, sizeof(str), "{AFAFAF}Отсутствует{FFFFFF}");

	format(string, sizeof(string), "ПЕРСОНАЖ | Номер телефона: %d | Пейджер: %d | Часов в игре: %d | Зависимость: %s",character_info[p][phoneslot], character_info[p][pager], character_info[p][lvl], str);
	SCM(playerid,COLOR_WHITE, string);
	
	new status[32+11];
	if(player_info[p][admin] == 0) format(status, sizeof(status), "Игрок");
	if(player_info[p][admin] == 1) format(status, sizeof(status), "{33AA33}Помощник{FFFFFF}");
	if(player_info[p][admin] >= 2) format(status, sizeof(status), "{33AA33}Администратор (%d){FFFFFF}", player_info[p][admin]);
	
	new premium[30];
	if(player_info[p][vip] <= 0) format(premium, sizeof(premium), "{AFAFAF}Отсутствует{FFFFFF}");
	else if(player_info[p][vip] == 1) format(premium, sizeof(premium), "{CD7F32}BRONZE{FFFFFF}");
	else if(player_info[p][vip] == 2) format(premium, sizeof(premium), "{C0C0C0}SILVER{FFFFFF}");
	else if(player_info[p][vip] >= 3) format(premium, sizeof(premium), "{FFD700}GOLD{FFFFFF}");
	
	format(string, sizeof(string), "АККАУНТ | Никнейм: %s | Статус: %s | Премиум: %s | Донат: %d | Смен ника: %d", player_info[p][login], status, premium, player_info[p][donate], player_info[p][changename]);
	SCM(playerid,COLOR_WHITE, string);
	if(!IsAdmin(playerid, 2, true))
	{
		new ipplayer[16];
		GetPlayerIp(p, ipplayer, sizeof(ipplayer));
		format(string, sizeof(string), "АДМИНИСТРАТИВНОЕ | IP Адрес: %s | В тюрьме на %d сек. | В админ-тюрьме на %d сек.", ipplayer, character_info[p][jail_time], character_info[p][ajail_time]);
		SCM(playerid,COLOR_WHITE, string);
	}
	format(string, sizeof(string), "__________________________________________",sendername(p, true),day, month, year, hour, minute);
	SCM(playerid,COLOR_GREEN, string);
	
 	return 1;
}
CMD:showid(playerid, params[])
{
	if(sscanf(params,"u", params[0])) 
		return SyntaxCMD(playerid, "/showid [id]");
	
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	
	new floatxyz;
	GetPlayerPos(params[0], xyz);
	
	if(!PlayerToPoint(5.0, playerid, xyz)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть рядом с игроком!");
	
	new str[128];
	
	format(str, sizeof(str), "показывает ID карту %s", sendername(params[0], true));
	cmd_me(playerid, str);
	
	SCM(params[0], COLOR_GREEN, "______________ Айди-карта ______________");
	
	format(str, sizeof(str), "Полное имя: %s", sendername(playerid, true));
	SCM(params[0], COLOR_WHITE, str);
	
	if(character_info[playerid][driveLic]) 
	{
		format(str, sizeof(str), "Водительские права: {33AA33}Имеются");
		SCM(params[0], COLOR_WHITE, str);
		
		format(str, sizeof(str), " Предупреждения: %d", character_info[playerid][driveLicWarn]);
		SCM(params[0], COLOR_WHITE, str);
	}
	else 
	{
		format(str, sizeof(str), "Водительские права: {FF6347}Отсутствует");
		SCM(params[0], COLOR_WHITE, str);
	}
	new bool:first=false;
	
	for(new v; v<MAX_VEHICLES; v++)
	{
		if(veh_info[v][owner] > 0 && veh_info[v][owner] == character_info[playerid][id])
		{
			if(!first) 
			{
				first=true;
				SCM(params[0], COLOR_WHITE, "Имеющийся транспорт:");
			}
			format(str, sizeof(str), "%s [%s]", VehicleNames[GetVehicleModel(v)-400], veh_info[v][number]);
			SCM(params[0], COLOR_WHITE, str);
		}
	}
	
	SCM(params[0], COLOR_WHITE, "");
	
	if(character_info[params[0]][flyLic]) 
		format(str, sizeof(str), "Лицензия на полеты: {33AA33}Имеется");
	else 
		format(str, sizeof(str), "Лицензия на полеты: {FF6347}Отсутствует");
	
	SCM(params[0], COLOR_WHITE, str);
	if(character_info[params[0]][gunLic]) 
		format(str, sizeof(str), "Лицензия на оружие: {33AA33}Имеется");
	else 
		format(str, sizeof(str), "Лицензия на оружие: {FF6347}Отсутствует");
	
	SCM(params[0], COLOR_WHITE, str);
		
	//SCM(params[0], COLOR_GREEN, "_____________________________________");
	return 1;
}
ALTX:showid("/showpass", "/pass", "/password");

CMD:licensewarning(playerid, params[])
{
	if(!IsCop(playerid)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в этой фракции!");
	if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/(l)icense(w)arning [id]");
	character_info[params[0]][driveLicWarn] += 1;
	new str[180];
	format(str, sizeof(str), "выписывает предупреждение на водительскую лицензию %s", sendername(params[0], true));
	cmd_me(playerid, str);
	format(str, sizeof(str), ">{FFFFFF} %s выписал предупреждение на вашу водительскую лицензию!", sendername(playerid, true));
	SCM(params[0], COLOR_MSGSERVER, str);
	return 1;
}
ALTX:licensewarning("/lw");


CMD:setstat(playerid, params[])
{
	if(IsAdmin(playerid, 6)) return 1;
	if(sscanf(params,"ddd", params[0], params[1], params[2])) {
		SyntaxCMD(playerid, "/setstat [param] [value]");
		SCM(playerid, COLOR_MSGDESC, ">:{FFFFFF} Доступные параметры: 1.faction, 2.rank");
		SCM(playerid, COLOR_MSGDESC, ">:{FFFFFF} 3.money, 4.bank, 5.hours, 6.addiction");
		SCM(playerid, COLOR_MSGDESC, ">:{FFFFFF} 7.donate, 8.changename");
	}
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не авторизован!");
	switch(params[1]) {
		case 1: character_info[params[0]][faction] = params[2];
		case 2: character_info[params[0]][rank] = params[2];
		case 3: character_info[params[0]][money] = params[2];
		case 4: character_info[params[0]][bank] = params[2];
		case 5: character_info[params[0]][lvl] = params[2];
		case 6: character_info[params[0]][addiction] = params[2];
		case 7: player_info[params[0]][donate] = params[2];
		case 8: player_info[params[0]][changename] = params[2];
		default: return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверный параметр!");
	}
 	SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы изменили статистку игрока.");
 	Log_Write("logs/admins_log.txt", "[%s] [A] %s use setstat %s(%s) %d %d", ReturnDate(), player_info[playerid][login], player_info[params[0]][login], character_info[params[0]][name], params[1], params[2]);
	return 1;
}
CMD:agivemoney(playerid, params[])
{
	if(IsAdmin(playerid, 6)) return 1;
	if(sscanf(params,"dd", params[0], params[1])) SyntaxCMD(playerid, "/agivemoney [id] [money]");
	new str[64];
	format(str, sizeof(str), "from admin %d", player_info[playerid][id]);
	if(givemoney(params[0], params[1], str) == 1)
	{
		Log_Write("logs/admins_log.txt", "[%s] [A] %s give %s %d$", ReturnDate(), player_info[playerid][login], character_info[params[0]][name], params[1]);
		format(str, sizeof(str), "%s[%d] выдал %s(%s) %d$", player_info[playerid][login], playerid, player_info[params[0]][login], character_info[params[0]][name], params[1]);
		AdminMessage(str);
		SCM(params[0], COLOR_YELLOW, str);
	}
	return 1;
}
CMD:getitem(playerid, params[])
{
	if(sscanf(params,"s[25]", params[0])) return SyntaxCMD(playerid, "/getitem [часть названия предмета]");
	if(IsAdmin(playerid, 4)) return 1;
	new str[64];
	format(str, sizeof(str), ">{FFFFFF} Результаты по ""%s"":", params[0]);
	SCM(playerid, COLOR_MSGSERVER, str);
	for(new i; i<MAX_ITEMS; i++)
	{
		if(strfind(Items[i][Name], params[0], false)!=-1 || strfind(Items[i][Name], params[0], true)!=-1) 
		{
			format(str, sizeof(str), ">{FFFFFF} [%d] %s", i, Items[i][Name]);
			SCM(playerid, COLOR_MSGSERVER, str);
		}
	}
	return 1;
}
CMD:setadmin(playerid, params[])
{
    if(IsAdmin(playerid, 6)) 
		return 1;
    
	if(sscanf(params,"ud", params[0], params[1])) 
		return SyntaxCMD(playerid, "/setadmin [id] [level]");
	
    new str[180];
	if(!IsPlayerLoged(params[0])) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	if(params[1] < 0 || params[1] >= SUPER_ADMIN) 
		return 1;
    
	player_info[params[0]][admin] = params[1];
    format(str, sizeof(str), "%s[%d] назначил %s(%s) администратором %d уровня.", player_info[playerid][login], playerid, player_info[params[0]][login], character_info[params[0]][name], params[1]);
	AdminMessage(str);
    return 1;
}
CMD:ac(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/ac [код античита]");
	if(params[0] < 0) return 1;
	new text[128];
	switch(params[0])
	{
		case 0: text = "Anti-AirBreak (onfoot)";
		case 1: text = "Anti-AirBreak (in vehicle)";
		case 2: text = "Anti-teleport hack (onfoot)";
		case 3: text = "Anti-teleport hack (in vehicle)";
		case 4: text = "Anti-teleport hack (into/between vehicles)";
		case 5: text = "Anti-teleport hack (vehicle to player)";
		case 6: text = "Anti-teleport hack (pickups)";
		case 7: text = "Anti-FlyHack (onfoot)";
		case 8: text = "Anti-FlyHack (in vehicle)";
		case 9: text = "Anti-SpeedHack (onfoot)";
		case 10: text = "Anti-SpeedHack (in vehicle)";
		case 11: text = "Anti-Health hack (in vehicle)";
		case 12: text = "Anti-Health hack (onfoot)";
		case 13: text = "Anti-Armour hack";
		case 14: text = "Anti-Money hack";
		case 15: text = "Anti-Weapon hack";
		case 16: text = "Anti-Ammo hack (add)";
		case 17: text = "Anti-Ammo hack (infinite)";
		case 18: text = "Anti-Special actions hack";
		case 19: text = "Anti-GodMode from bullets (onfoot)";
		case 20: text = "Anti-GodMode from bullets (in vehicle)";
		case 21: text = "Anti-Invisible hack";
		case 22: text = "Anti-lagcomp-spoof";
		case 23: text = "Anti-Tuning hack";
		case 24: text = "Anti-Parkour mod";
		case 25: text = "Anti-Quick turn";
		case 26: text = "Anti-Rapid fire";
		case 27: text = "Anti-FakeSpawn";
		case 28: text = "Anti-FakeKill";
		case 29: text = "Anti-Pro Aim";
		case 30: text = "Anti-CJ run";
		case 31: text = "Anti-CarShot";
		case 32: text = "Anti-CarJack";
		case 34: text = "Anti-AFK Ghost";
		case 35: text = "Anti-Full Aiming";

		case 36: text = "Anti-Fake NPC";
		case 37: text = "Anti-Reconnect";
		case 38: text = "Anti-High ping";
		case 39: text = "Anti-Dialog hack";
		case 40: text = "Protection from the sandbox";
		case 41: text = "Protection against an invalid version";
		case 42: text = "Anti-Rcon hack";
		
		case 43: text = "Anti-Tuning crasher";
		case 44: text = "Anti-Invalid seat crasher";
		case 45: text = "Anti-Dialog crasher";
		case 46: text = "Anti-Attached object crasher";
		case 47: text = "Anti-Weapon Crasher";

		case 48: text = "Flood protection connects to one slot";
		case 49: text = "Anti-flood callback functions";
		case 50: text = "Anti-flood change seat";

		case 51: text = "Anti-Ddos";

		case 52: text = "Anti-NOP";
		
		default: text = "{b1b1b1}Данный код не найден в справке!\nВозможно вы ввели неверный код или информации по этому коду просто нет."; 
	}
	new str_title[32];
	format(str_title, sizeof(str_title), "AC CODE #%d", params[0]);
	new str_body[128];
	format(str_body, sizeof(str_body), "{ffffff}%s", text);
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, str_title, str_body, "Закрыть", "");
	return 1;
}

CMD:a(playerid, params[])
{
	if(IsAdmin(playerid, 1)) return 1;
	if(GetPVarInt(playerid, "amute")) return SCM(playerid, COLOR_TOMATO, "У вас админ-молчанка!");
	if(sscanf(params,"s[128]", params[0])) return SyntaxCMD(playerid, "/a [текст]");
	new str[128];
	format(str, sizeof(str), "%s[%d]: %s", player_info[playerid][login], playerid, params[0]);
	AdminMessage(str);
 	return 1;
}

CMD:report(playerid, params[])
{
	if(sscanf(params,"s[128]", params[0])) 
		return SyntaxCMD(playerid, "/report [текст]");
	
	if(flood[playerid][report] > gettime())
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Доступно раз в 10 секунд!");
	flood[playerid][report] = gettime()+10;
	
	new str[128];
	format(str, sizeof(str), ">{FFFFFF} Репорт от %s[%d]: %s", sendername(playerid, true), playerid, params[0]);
	foreach(new p : Player)
	{
		if(IsAdmin(p, 2, true)) continue;
		SendClientMessage(p, COLOR_MSGADMIN, str);
	}
	SendServerMessage(playerid, "Ваше сообщение было успешно отправлено администрации.");
 	return 1;
}
CMD:askoff(playerid)
{
	if(IsAdmin(playerid, 2)) return 1;
	if(GetPVarInt(playerid, "ASKOFF"))
	{
		GameTextForPlayer(playerid, "~g~ON", 1000, 3);
		DeletePVar(playerid, "ASKOFF");
	}
	else if(!GetPVarInt(playerid, "ASKOFF"))
	{
		GameTextForPlayer(playerid, "~r~OFF", 1000, 3);
		SetPVarInt(playerid, "ASKOFF", 1);
	}
	return 1;
}
CMD:ask(playerid, params[])
{
	if(sscanf(params,"s[128]", params[0])) 
		return SyntaxCMD(playerid, "/ask [текст]");
	
	if(flood[playerid][report] > gettime())
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Доступно раз в 10 секунд!");
	flood[playerid][report] = gettime()+10;
	
	new str[128];
	format(str, sizeof(str), ">{FFFFFF} Вопрос от %s[%d]: %s", sendername(playerid, true), playerid, params[0]);
	foreach(new p : Player)
	{
		if(IsAdmin(p, 1, true) || GetPVarInt(p, "ASKOFF")) continue;
		SendClientMessage(p, COLOR_MSGADMIN, str);
	}
	SendServerMessage(playerid, "Ваше сообщение было успешно отправлено администрации.");
 	return 1;
}
ALTX:report("/rep");
ALTX:ask("/support", "/request", "/вопрос");

CMD:ans(playerid, params[])
{
    if(IsAdmin(playerid, 1)) 
		return 1;
	
	if(sscanf(params,"ds[128]", params[0], params[1])) 
		return SyntaxCMD(playerid, "/ans [id] [ответ]");
		
	new str[128];
	format(str, sizeof(str), ">{FFFFFF} %s[%d] ответил %s[%d]: %s", player_info[playerid][login], playerid, character_info[params[0]][name], params[0], params[1]);
	
	SendClientMessage(params[0], COLOR_MSGADMIN, str);
	foreach(new p : Player)
	{
		if(IsAdmin(p, 1, true)) continue;
		SendClientMessage(p, COLOR_MSGADMIN, str);
	}
 	return 1;
}

CMD:mute(playerid, params[])
{
    if(IsAdmin(playerid, 2)) 
		return 1;
	if(sscanf(params,"uds[128]", params[0], params[1], params[2])) 
		return SyntaxCMD(playerid, "/mute [id] [время в минутах] [причина]");
	if(params[1] < 0)
		return SyntaxCMD(playerid, "/mute [id] [время в минутах] [причина]");
	
	new str[128];
	if(params[1] == 0)
	{
		if(player_info[params[0]][mute] == 0)
			return SyntaxCMD(playerid, "У данного игрока нет мута!");
		
		format(str, sizeof(str), "%s снял мут %s. Причина: %s", player_info[playerid][login],character_info[params[0]][name], params[2]);
		player_info[params[0]][mute] = 0;
	}
	else
	{
		format(str, sizeof(str), "%s выдал мут %s на %d мин. Причина: %s", player_info[playerid][login],character_info[params[0]][name], params[1], params[2]);
		player_info[params[0]][mute] = params[1]*60;		
	}	
	
	AdminMessage(str);
	return 1;
}

CMD:ck(playerid, params[])
{
	if(IsAdmin(playerid, 4)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/ck [id]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_GRAY, "Игрок оффлайн!");
	new str[68+25];
	format(str, sizeof(str), "получил CK. (Выдал администратор: %s)", player_info[playerid][login]);
    OOCMSG(params[0], str);
	SCM(playerid, COLOR_GREEN, "Вы выдали CK выбранному игроку!");
	new qu[69+11];
	format(qu, sizeof(qu), "update characters set userid=-%d where id=%d", player_info[params[0]][id], character_info[params[0]][id]);
	mysql_function_query(dbHandle, qu, false, "", "");
	KickEx(params[0]);
	
	return 1;
}

CMD:unck(playerid, params[])
{
	if(IsAdmin(playerid, 5)) return 1;
	if(sscanf(params,"s[25]", params[0])) return SyntaxCMD(playerid, "/unck [Name]");
	SCM(playerid, COLOR_GREEN, "Вы сняли CK с выбранного персонажа!");
	Log_Write("logs/admins_log.txt", "[%s] %s unck %s", ReturnDate(), player_info[playerid][login], params[0]);
	//printf("%s unck %s", );

	mysql_real_escape_string(params[0], params[0]);
	new qu[80+25];
	format(qu, sizeof(qu), "update characters set userid=userid+userid+userid where name='%s' and userid < 0", params[0]);
	mysql_function_query(dbHandle, qu, false, "", "");
	return 1;
}
CMD:vishnyagoodchelik(playerid)
{
	if(IsAdmin(playerid, 6)) return 1;
	new str[128];
	GameTextForPlayer(playerid, "~g~SUCCESS", 3000, 3);
	format(str, sizeof(str), "(( ДАННЫЙ ИГРОК ПЕТУХ. ))");	
	SetPlayerChatBubble(playerid, str,COLOR_TOMATO,10.0,5000);
	return 1;
}
CMD:block(playerid, params[]) {
	if(IsAdmin(playerid, 2)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/block [id]");
	if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
	
	new str[68+25];
	format(str, sizeof(str), "отпрален на ретест. (Выдал администратор: %s)", player_info[playerid][login]);
    OOCMSG(params[0], str);
	SendAdminMessage(playerid, "Вы выдали ретест выбранному игроку!");
	new qu[69+11];
	format(qu, sizeof(qu), "update characters set status=-1 where id=%d", player_info[params[0]][id]);
	mysql_function_query(dbHandle, qu, false, "", "");
	KickEx(params[0]);
	return 1;
}


ALTX:ck("/characterkill");
CMD:kick(playerid, params[])
{
    if(IsAdmin(playerid, 2)) return 1;
    if(sscanf(params,"ds[116]", params[0], params[1])) return SyntaxCMD(playerid, "/kick [id] [причина]");

	new str[124];
    if(IsPlayerConnected(params[0]))
	{
	    format(str, sizeof(str), "%s(%d) кикнул игрока %s. Причина: %s", player_info[playerid][login], playerid, character_info[params[0]][name], params[1]);
     	AdminMessage(str);
     	format(str, sizeof(str), "был кикнут администратором %s. Причина: %s", player_info[playerid][login], params[1]);
        OOCMSG(params[0], str);
     	KickEx(params[0]);
	 }
    return 1;
}

CMD:pr(playerid, params[])
{
	if(sscanf(params, "s[16]", params[0]))
	{
		new str[512] = "Действие\tАльт. команда\n";
		format(str, sizeof(str), "%s{FFFFFF}Закрыть/Открыть имущество\t{AFAFAF}(/pr lock)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Продать имущество игроку\t{AFAFAF}(/pr sell)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Продать имущество государству\t{AFAFAF}(/pr selltate)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Управление мебелью\t{AFAFAF}(/pr f)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Информация о вашем имуществе\t{AFAFAF}(/pr info)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Деньги\t{AFAFAF}(/pr money)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Инвентарь\t{AFAFAF}(/pr inv)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Название\t{AFAFAF}(/pr name)\n", str);
		format(str, sizeof(str), "%s{FFFFFF}Плата за вход\t{AFAFAF}(/pr price)", str);
		SPD(playerid, 18, DIALOG_STYLE_TABLIST_HEADERS, "Меню имущества", str, "Выбрать", "Закрыть");
		return 1;
	}
	else if(!strcmp(params[0], "furniture", true) || !strcmp(params[0], "f", true))
	{
	    SPD(playerid, 17, DIALOG_STYLE_TABLIST, "Мебель", "{FFFFFF}Покупка мебели\t{AFAFAF}(pr /bf)\n{FFFFFF}Редактирование мебели\t{AFAFAF}(pr /ef)\n{FFFFFF}Удаление мебели\t{AFAFAF}(pr /df)", "Выбрать", "Закрыть");
	}
	else if(!strcmp(params[0], "buyfurniture", true) || !strcmp(params[0], "bf", true))
	{
	    ShowFurniture(playerid);
	}
	else if(!strcmp(params[0], "money", true)) MoneyPropDialog(playerid);
	else if(!strcmp(params[0], "editfurniture", true) || !strcmp(params[0], "ef", true))
	{
	    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200)
    	{
			new str[3000];
			for(new i=0; i<MAX_FURNITURE; i++)
			{
				if(furniture[i][houseid] == character_info[playerid][prop])
					format(str, sizeof(str), "%s%s\n", str, _furniture[furniture_search(furniture[i][model])][name]);
			}
			SPD(playerid, 15, DIALOG_STYLE_TABLIST, "Мебель", str, "Выбрать", "Закрыть");
		}
	}
	else if(!strcmp(params[0], "deletefurniture", true) || !strcmp(params[0], "df", true))
	{
	    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200)
    	{
			new str[3000];
			for(new i=0; i<MAX_FURNITURE; i++)
			{
				if(furniture[i][houseid] == character_info[playerid][prop])
					format(str, sizeof(str), "%s%s\n", str, _furniture[furniture_search(furniture[i][model])][name]);
			}
			SPD(playerid, 16, DIALOG_STYLE_TABLIST, "Удаление мебели", str, "Выбрать", "Закрыть");
		}
	}
	else if(!strcmp(params[0], "lock", true))
	{
	    new propid = OwnerProp(playerid);
		if(propid <= -1) propid = NeighborProp(playerid);
		if(propid > -1)
		{
			if(prop_info[propid][lock])
			{
			    GameTextForPlayer(playerid, "~g~OPEN", 2000, 3);
			    prop_info[propid][lock] = false;
			}
			else
			{
			    GameTextForPlayer(playerid, "~r~CLOSED", 2000, 3);
			    prop_info[propid][lock] = true;
			}
	    }
	}
	else if(!strcmp(params[0], "sellstate", true))
	{
	    new propid = OwnerProp(playerid);
	    if(propid > -1)
	    {
	        new str[128];
	        format(str, sizeof(str), "{FFFFFF}Вы действительно хотите продать свой дом?\nВы получите {FFFF00}%d$", (prop_info[propid][price]/4)*3);
	        ShowPlayerDialog(playerid, 9, DIALOG_STYLE_MSGBOX, "Продажа дома", str, "Продать", "Отменить");
	    }
	}
	else if(!strcmp(params[0], "sell", true))
	{
	    new propid = OwnerProp(playerid);
	    if(propid > -1)
	    {
	        ShowPlayerDialog(playerid, 10, DIALOG_STYLE_INPUT, "Продажа дома", "Введите ID игрока, которому собираетесь продать дом:", "Продать", "Отменить");
	    }
	}
	else if(!strcmp(params[0], "info", true))
	{
	    SCM(playerid, COLOR_SALMON, "Ваше имущество:");
	    new str[128];
	    for(new i=0; i<MAX_PROP; i++)
	    {
	        if(prop_info[i][owner] == character_info[playerid][id])
	        {
				format(str, sizeof(str), "ID: %d | Тип: %s", prop_info[i][id], property[prop_info[i][type]]);
                SCM(playerid, COLOR_SALMON, str);
	        }
	    }
	}
	else if(!strcmp(params[0], "inv", true))
	{	
	    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200 || InFactionId(playerid, LSPD_FACTION) || InFactionId(playerid, SASD_FACTION) || InFactionId(playerid, LSSD_FACTION))
    	{
    	    prop_inv(playerid);
    	}
	}
	else if(!strcmp(params[0], "name", true)) ShowPlayerDialog(playerid, 132, DIALOG_STYLE_INPUT, "Название", "Введите новое название для имущества: ", "Ввод", "Отмена");
	else if(!strcmp(params[0], "price", true)) ShowPlayerDialog(playerid, 148, DIALOG_STYLE_INPUT, "Плата за вход", "Ввведите плату за вход в помещение: ", "Ввод", "Отмена");

	return 1;
}


CMD:siren(playerid)
{
	if(!InFactionType(playerid, FACTIONTYPE_STATE)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете использовать эту команду!");
	if(isPlayerDriver(playerid))
	{
		if(!SirenOn(GetPlayerVehicleID(playerid))) 
		{
			new v = GetPlayerVehicleID(playerid);
			DestroyDynamicObject(veh_info[v][siren]);
			veh_info[v][siren] = 0;
			return SendServerMessage(playerid, "Вы убрали сирены с этого транспорта!");
		}
		SendServerMessage(playerid, "Вы установили сирены!");
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть водителем!");
	return 1;
}
ALTX:inventory("/inv", "/invent", "/inventar");
CMD:inventory(playerid)
{
	if(character_info[playerid][jail_time] > 0 || character_info[playerid][ajail_time] > 0) 
		return 1;
		
	new str[2048] = "{AFAFAF}Предмет\t{AFAFAF}Количество\n", color[128], count_text[128], itemname_text[128];
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    format(itemname_text, sizeof(itemname_text), "%s", senderitems(0));
		format(count_text, sizeof(count_text), "");
		
	 	if(character_info[playerid][inv][count][i] < 1)
		{
			character_info[playerid][inv][id][i] = 0;
	 		character_info[playerid][inv][count][i] = 0;
		}
		
  		if(character_info[playerid][inv][id][i] == 0) 
			color = "{AFAFAF}";
		else 
			color = "{ffffff}";

		if(character_info[playerid][inv][id][i] != 0)
		{
			if(Items[character_info[playerid][inv][id][i]][compound])
			{
				format(itemname_text, sizeof(itemname_text), "%s",  senderitems(character_info[playerid][inv][id][i]));
    			if(character_info[playerid][inv][count][i] > 0)
					format(count_text, sizeof(count_text), "Количество: %d", character_info[playerid][inv][count][i]);
			}
			else
				format(itemname_text, sizeof(itemname_text), "%s (%d)\tКоличество: 1", senderitems(character_info[playerid][inv][id][i]), character_info[playerid][inv][count][i]);
		}

		format(str, sizeof(str), "%s{AFAFAF}%s%s\t%s\n",str, color, itemname_text, count_text);
 	}
	ShowPlayerDialog(playerid, 4, DIALOG_STYLE_TABLIST_HEADERS,"Инвентарь", str, "Выбрать", "Отмена");
	return 1;
}
CMD:carinv(playerid)
{
	new v = 0;
	if(IsPlayerInAnyVehicle(playerid)) v = GetPlayerVehicleID(playerid);
	else
	{
		for(new i=1; i<MAX_VEHICLES; i++)
		{
			new Float:x, Float:y, Float:z;
			GetCoordBootVehicle(i, xyz);
			if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot])
			{
				v = i;
				break;
			}
		}
		if(GetPlayerVehicleID(playerid) != 0 && veh_info[GetPlayerVehicleID(playerid)][owner] == character_info[playerid][id]) v = GetPlayerVehicleID(playerid);
		if(v == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете воспользоваться инвентарем этого транспорта!");
	}

	veh_inv(playerid);
	return 1;
}
CMD:invold(playerid)
{
	if(character_info[playerid][jail_time] > 0 || character_info[playerid][ajail_time] > 0) return 1;
	new v = 0;
	for(new i=1; i<MAX_VEHICLES; i++)
	{
		new Float:x, Float:y, Float:z;
		GetCoordBootVehicle(i, xyz);
		if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot])
		{
			v = i;
			break;
		}
	}
	if(GetPlayerVehicleID(playerid) != 0 && veh_info[GetPlayerVehicleID(playerid)][owner] == character_info[playerid][id]) v = GetPlayerVehicleID(playerid);
	if(v == 0) cmd_inventory(playerid);
	else ShowPlayerDialog(playerid, 89, DIALOG_STYLE_LIST, "Инвентарь", "Инвентарь персонажа\nИнвентарь автомобиля", "Выбрать", "Отмена");
	return 1;
}
CMD:setweather(playerid, params[])
{
    if(IsAdmin(playerid, 5)) return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/setweather [id]");
	weatherid = params[0];
	SetWeather(params[0]);
	return 1;
}
CMD:agiveitem(playerid, params[])
{
    if(IsAdmin(playerid, 7)) 
		return 1;
    if(sscanf(params,"ddd", params[0], params[1], params[2])) return SyntaxCMD(playerid, "/agiveitem [id] [itemid] [count]");

	new str[124];
    if(IsPlayerLoged(params[0]))
	{
	    if(giveitem(params[0], params[1], params[2]))
	    {
			Log_Write("logs/admins_log.txt", "[%s] [A] %s give %s item %s [%d]", ReturnDate(), player_info[playerid][login], character_info[params[0]][name], senderitems(params[1]), params[2]);
	        format(str, sizeof(str), "%s(%d) выдал игроку %s(%d) предмет %s [%d] (Кол-во: %d)", player_info[playerid][login], playerid, character_info[params[0]][name], params[0], senderitems(params[1]), params[1], params[2]);
	        AdminLog(str);
	    }
		else
		    SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У игрока недостаточно места или вы ввели неверный ID предмета");
	}
    return 1;
}

CMD:adelitem(playerid, params[])
{
    if(IsAdmin(playerid, 7)) return 1;
    if(sscanf(params,"ddd", params[0], params[1], params[2])) SyntaxCMD(playerid, "/adelitem [id] [itemid] [count]");

	new str[124];
    if(IsPlayerLoged(params[0]))
	{
	    if(deleteitem(params[0], params[1], params[2]))
	    {
	        format(str, sizeof(str), "%s(%d) отобрал у игрока %s(%d) предмет %s [%d] (Кол-во: %d)", player_info[playerid][login], playerid, character_info[params[0]][name], params[0], senderitems(params[1]), params[1], params[2]);
	        AdminLog(str);
	    }
		else
		    SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У игрока нет данного предмета (или недостаточно).");
	 }
    return 1;
}
CMD:clearinv(playerid, params[])
{
    if(IsAdmin(playerid, 7)) return 1;
    if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/clearinv [id]");
	new str[124];
	wepinv(params[0]);
	for(new i; i<MAX_INV_SLOTS; i++)
   	{
   	    character_info[params[0]][inv][id][i] = 0;
    	character_info[params[0]][inv][count][i] = 0;
   	}
   	format(str, sizeof(str), "%s(%d) обнулил инвентарь %s(%d)", player_info[playerid][login], playerid, character_info[params[0]][name], params[0]);
    AdminLog(str);
	SCM(params[0], COLOR_TOMATO, str);
    return 1;
}
CMD:invwep(playerid)
{
	if(IsDuty(playerid) && InFactionId(playerid, LSPD_FACTION) || IsDuty(playerid) && InFactionId(playerid, SASD_FACTION)) 
		return 1;
    
	wepinv(playerid);
    return 1;
}
CMD:invsilencer(playerid)
{
	if(IsDuty(playerid) && InFactionId(playerid, LSPD_FACTION) || IsDuty(playerid) && InFactionId(playerid, SASD_FACTION)) 
		return 1;
    
	invsilencer(playerid);
    return 1;
}

CMD:slap(playerid, params[])
{
	if(IsAdmin(playerid, 2)) return 1;
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/goto [id]");
    if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
	
	new floatxyz;
	GetPlayerPos(params[0], xyz);
	SetPlayerPos(params[0], x,y,z+3);
	Sound_Fail(params[0]);
	new str[180];
	format(str, sizeof(str), "%s[%d] подкинул %s[%d]", player_info[playerid][login], playerid, sendername(params[0], true), params[0]);
	AdminLog(str);
	format(str, sizeof(str), ">{FFFFFF} Администратор %s[%d] подкинул Вас!", player_info[playerid][login], playerid);
	SCM(params[0], COLOR_MSGSERVER, str);
	return 1;
}

CMD:dgraf(playerid)
{
	if(IsAdmin(playerid, 3)) 
		return 1;
	
	GameTextForPlayer(playerid, "~r~SEARCHING...", 10000, 3);
	for(new i; i<MAX_GRAFF; i++)
	{
		if(PlayerToPoint(5.0, playerid, graff_info[i][gX], graff_info[i][gY], graff_info[i][gZ])) 
		{
			new qu[115+11];
			format(qu, sizeof(qu), "select users.login, characters.name from users join characters on users.id=characters.userid where characters.id=%d", graff_info[i][gOwner]);
			mysql_function_query(dbHandle, qu, true, "OnDgraf", "dd", playerid, i);
			return 1;
		}
	}
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Рядом с вами нет граффити!");
	GameTextForPlayer(playerid, "~r~NULL!", 10000, 3);
	return 1;
}

CMD:editatm(playerid)
{
	if(IsAdmin(playerid, 5)) 
		return 1;
	
	SelectObject(playerid);
	character_info[playerid][type_editobj] = 11;
	SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Выберите банкомат!");
	return 1;
}

CMD:bot(playerid)
{
	return CMDError(playerid);
}
CMD:freeze(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/freeze [id]");
	FreePlayer(params[0], 0);
	new str[128];
	format(str, sizeof(str), "%s(%d) заморозил игрока %s(%d)", player_info[playerid][login], playerid, character_info[params[0]][name], params[0]);
 	AdminLog(str);
	return 1;	
}
CMD:unfreeze(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/unfreeze [id]");
	FreePlayer(params[0], 1);
	new str[128];
	format(str, sizeof(str), "%s(%d) разморозил игрока %s(%d)", player_info[playerid][login], playerid, character_info[params[0]][name], params[0]);
 	AdminLog(str);
	return 1;	
}
CMD:goto(playerid, params[])
{
    if(IsAdmin(playerid, 2)) return 1;
    if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/goto [id]");
    if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
    if(params[0] == playerid) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы указали свой ID!");
	
	new str[124], vw, interior, Float:pos[3];
	GetPlayerPos(params[0], pos[0], pos[1], pos[2]);
	vw = GetPlayerVirtualWorld(params[0]);
	interior = GetPlayerInterior(params[0]);

	SetPlayerPos(playerid, pos[0]+1, pos[1]+1, pos[2]);
	SetPlayerVw(playerid, vw);
	SetPlayerInt(playerid, interior);

	format(str, sizeof(str), "%s(%d) телепортировался к %s(%d)", player_info[playerid][login], playerid, character_info[params[0]][name], params[0]);
 	AdminLog(str);

	return 1;
}

CMD:gethere(playerid, params[])
{
    if(IsAdmin(playerid, 2)) return 1;
    if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/gethere [id]");
    if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");

	new str[124], vw, interior, Float:pos[3];
	GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
	vw = GetPlayerVirtualWorld(playerid);
	interior = GetPlayerInterior(playerid);

	SetPlayerPos(params[0], pos[0], pos[1], pos[2]);
	SetPlayerVw(params[0], vw);
	SetPlayerInt(params[0], interior);

	format(str, sizeof(str), "%s(%d) телепортировал игрока %s(%d) к себе", player_info[playerid][login], playerid, character_info[params[0]][name], params[0]);
 	AdminLog(str);
	return 1;
}
CMD:setskin(playerid, params[])
{
    if(IsAdmin(playerid, 3)) return 1;
    if(sscanf(params,"ddd", params[0], params[1], params[2])) return SyntaxCMD(playerid, "/setskin [id] [id скина] [1 - постоянный, 0 - временный]");
    if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
	if(params[1] < 1 || params[1] > 312) return SyntaxCMD(playerid, "/setskin [id] [id скина] [1 - постоянный, 0 - временный]");
	if(params[2] < 0 || params[2] > 1) return SyntaxCMD(playerid, "/setskin [id] [id скина] [1 - постоянный, 0 - временный]");
	new str[124];
	SetPlayerSkin(params[0], params[1]);
	if(params[2] == 1) character_info[params[0]][skin] = params[1];
	format(str, sizeof(str), "%s(%d) выдал игроку %s(%d) скин %d", player_info[playerid][login], playerid, character_info[params[0]][name], params[0], params[1]);
 	AdminLog(str);
	return 1;
}
CMD:setskin038(playerid, params[])
{
    if(IsAdmin(playerid, 3)) return 1;
    if(sscanf(params,"ddd", params[0], params[1], params[2])) return SyntaxCMD(playerid, "/setskin [id] [id скина] [1 - постоянный, 0 - временный]");
    if(!IsPlayerLoged(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
	if(params[1] < 25000 || params[1] > 30000) return SyntaxCMD(playerid, "/setskin [id] [id скина] [1 - постоянный, 0 - временный]");
	if(params[2] < 0 || params[2] > 1) return SyntaxCMD(playerid, "/setskin [id] [id скина] [1 - постоянный, 0 - временный]");
	new str[124];
	SetPlayerSkin(params[0], params[1]);
	if(params[2] == 1) character_info[params[0]][skin] = params[1];
	format(str, sizeof(str), "%s(%d) выдал игроку %s(%d) скин %d", player_info[playerid][login], playerid, character_info[params[0]][name], params[0], params[1]);
 	AdminLog(str);
	return 1;
}
CMD:hp(playerid)
{
    if(IsAdmin(playerid, 2)) return 1;
    SetPlayerHealth(playerid, 100);
	if(character_info[playerid][wound] != 0) 
	{
		set_wound(playerid, 0);
		UpdateDamages(playerid);
	}
    return 1;
}

CMD:dmdo(playerid, params[])
{
	if(IsAdmin(playerid, 3)) return 1;
	if(sscanf(params,"u", params[0])) return SyntaxCMD(playerid, "/dmdo [id]");
	if(!DeleteMDO(params[0])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У этого игрока нет созданного 3D текста");
	new str[128];
	format(str, sizeof(str), "%s(%s) удаляет 3D текст игрока %s(%s)", CharacterAndPlayerName(playerid), CharacterAndPlayerName(params[0]));
	AdminLog(str);
	SCM(params[0], COLOR_MSGSERVER, ">{FFFFFF} Администратор удалил ваш 3D текст.");
	return 1;
}

CMD:mdo(playerid, params[])
{
    if(DeleteMDO(playerid)) return SCM(playerid, COLOR_GREEN, "3D текст удален!");
    if(sscanf(params,"s[128]", params[0])) return SyntaxCMD(playerid, "/mdo [текст]");
    new Float:x, Float:y, Float:z, interior, virtualworld, str[256];
    format(str, sizeof(str), "(( %s (%s [%d]) ))", params[0], sendername(playerid, true), playerid);
    GetPlayerPos(playerid, xyz);
    interior = GetPlayerInterior(playerid);
    virtualworld = GetPlayerVirtualWorld(playerid);
    MDO[playerid] = CreateDynamic3DTextLabel(str, COLOR_ME, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, virtualworld, interior, -1, 10.0);
	format(str, sizeof(str), "создает 3D текст: %s", params[0]);
	PlayerLog(playerid, str);
	//printf("[debug_3d] create mdo");
    return 1;
}


CMD:getdistance(playerid, params[]) {
	if(sscanf(params,"d", params[0])) return SyntaxCMD(playerid, "/getdistance [1 - save first pos, 2 - save second pos, 3 - get distance]");
	switch(params[0]) {
		case 1: {
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, xyz);
			SetPVarFloat(playerid, "gd_x1", x);
			SetPVarFloat(playerid, "gd_y1", y);
			SetPVarFloat(playerid, "gd_z1", z);
		} case 2: {
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, xyz);
			SetPVarFloat(playerid, "gd_x2", x);
			SetPVarFloat(playerid, "gd_y2", y);
			SetPVarFloat(playerid, "gd_z2", z);
		} case 3: {
			new result = GetDistance(GetPVarFloat(playerid, "gd_x1"), GetPVarFloat(playerid, "gd_y1"), GetPVarFloat(playerid, "gd_z1"), GetPVarFloat(playerid, "gd_x2"), GetPVarFloat(playerid, "gd_y2"), GetPVarFloat(playerid, "gd_z2"));
			SendClientMessageEx(playerid, COLOR_MSGERROR, ">{FFFFFF} first point: %f, %f, %f", GetPVarFloat(playerid, "gd_x1"), GetPVarFloat(playerid, "gd_y1"), GetPVarFloat(playerid, "gd_z1"));
			SendClientMessageEx(playerid, COLOR_MSGERROR, ">{FFFFFF} second point: %f, %f, %f", GetPVarFloat(playerid, "gd_x2"), GetPVarFloat(playerid, "gd_y2"), GetPVarFloat(playerid, "gd_z2"));

			SendClientMessageEx(playerid, COLOR_MSGERROR, ">{FFFFFF} Distance: %d", result);
		}
		
	}

	return 1;
	
}
