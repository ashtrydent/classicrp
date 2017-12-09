Dialog:dSelectDied(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		character_info[playerid][hospital] = 1800;
		SCM(playerid,COLOR_MSGSERVER,">{FFFFFF} Вы выбрали ПК, помните что вы должны забыть что было ранее и жить новой жизнью.");
	}
	else
	{
		new qu[96];
		format(qu, sizeof(qu), "update characters set userid=-%d where id=%d", player_info[playerid][id], character_info[playerid][id]);
		mysql_function_query(dbHandle, qu, false, "", "");
		SCM(playerid,COLOR_MSGSERVER,">{FFFFFF} Вы выбрали CK, ваш персонаж удален.");
		KickEx(playerid);
	}
	return 1;
}
Dialog:dFixxx(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new v = GetPlayerVehicleID(playerid);
		SetVehicleHealth(v, 999);
		RepairVehicle(v);
		veh_info[v][fuel] = 100;
	}
}

Dialog:InvMoveItem(playerid, response, listitem, inputtext[]) {
	new j = GetPVarInt(playerid, "InvMoveItem_slot");
	DeletePVar(playerid, "InvMoveItem_slot");
	if(!response) return 1;
	InvTDMoveItem(playerid, j, strval(inputtext));

	return 1;
}
Dialog:ucpaccept(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		DeletePVar(playerid, "changeucp");
		DeletePVar(playerid, "changeucp_timer");
		return 1;
	}
	
	if(GetPVarInt(playerid, "changeucp_timer") < gettime())
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Вышло время на подтверждение операции!");
	
	if(player_info[playerid][donate] < Donate[6][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены UCP логина нехватает %d р.", Donate[6][Price] - player_info[playerid][donate]);
	
	new change_ucp[24];
	GetPVarString(playerid, "changeucp", change_ucp, 24);
	
	player_info[playerid][donate] -= Donate[6][Price];
	format(player_info[playerid][login], 24, "%s", change_ucp);
	
	new str[256];
	
	format(str, sizeof(str), "UPDATE `users` SET `login`='%s' WHERE id=%d", player_info[playerid][login], player_info[playerid][id]);
	mysql_function_query(dbHandle, str, false, "", "");
	
	SendClientMessageEx(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно сменили UCP логин на - %s!", player_info[playerid][login]);
	DeletePVar(playerid, "changeucp");
	DeletePVar(playerid, "changeucp_timer");
	DeletePVar(playerid, "antiflood");
	return 1;
}

Dialog:changeucp(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;
	
	if(player_info[playerid][donate] < Donate[6][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены UCP логина нехватает %d р.", Donate[6][Price] - player_info[playerid][donate]);
	
	new str[23];
	if(sscanf(inputtext,"s[23]", str))
		return Dialog_Show(playerid, changeucp, DIALOG_STYLE_INPUT, "Смена UCP логина.", "Логин не может быть пустым.\nВведите желаемый логин.", "Продолжить", "Отмена");
	
	if(strlen(str) < 3 || strlen(str) > 24)
		return Dialog_Show(playerid, changeucp, DIALOG_STYLE_INPUT, "Смена UCP логина.", "Логин не может быть короче 3 и длинее 24 символов\nВведите желаемый логин.", "Продолжить", "Отмена");
	
	for(new i = 0; i < strlen(str); i++)
	{
		switch(str[i])
		{
			case 'A'..'Z', 'a'..'z', '_', '-', '0'..'9': continue;
			default: return Dialog_Show(playerid, changeucp, DIALOG_STYLE_INPUT, "Смена UCP логина.", "Вы используете запрещенные символы.\nДоступные символы ( A-z 0-9 - _ ).", "Продолжить", "Отмена");
		}
	}
	
	if(GetPVarInt(playerid, "antiflood") > gettime())
	{
		SetPVarInt(playerid, "antiflood", gettime()+3);
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Каждый раз когда вы флудите сменой логина, в мире страдает одна MySQL.");
	}
	
	SetPVarInt(playerid, "antiflood", gettime()+3);
	SetPVarString(playerid, "changeucp", str);
	
	new qu[128];
	
	format(qu, sizeof(qu), "SELECT `login` FROM `users` WHERE `login`='%s'", str);
	mysql_function_query(dbHandle, qu, true, "ChangeUCPLogin", "d", playerid);
	return 1;
}

Dialog:RADIO_STATION(playerid, response, listitem)
{	
	if(!IsPlayerInAnyVehicle(playerid))
		return SyntaxCMD(playerid, "Дступно в транспорте!");
	
	new vehid;
	vehid = GetPlayerVehicleID(playerid);	
	
	if(!response)
	{
		veh_info[vehid][Radio] = 0;
		for(new i;i<MAX_PLAYERS;i++)
			if(IsPlayerInVehicle(i, vehid))
				StopAudioStreamForPlayer(i);
		return 0;
	}
	
	if(listitem>sizeof(Music))
		return 0;
	
	veh_info[vehid][Radio] = 1;
	veh_info[vehid][Station] = listitem;
	
	for(new i;i<MAX_PLAYERS;i++)
	{
		if(IsPlayerInVehicle(i, vehid))
		{
			SetPVarInt(i, "CAR_MUSIC", 1);
			PlayAudioStreamForPlayer(i, Music[veh_info[vehid][Station]][URL]);
		}
	}
	return 1;
}

Dialog:changebirthday(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;

	if(player_info[playerid][donate] < Donate[7][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены пола нехватает %d р.", Donate[7][Price] - player_info[playerid][donate]);
	
	new change_day, change_month, change_year;
	if(sscanf(inputtext, "p</>ddd", change_day, change_month, change_year))
		return Dialog_Show(playerid, changebirthday, DIALOG_STYLE_INPUT, "Смена даты рождения.", "Ошибка!\nВведите дату нового дня рождения.\nФормат: день/месяц/год", "Продолжить", "Отмена");
	
	if(change_day > 31 || change_day < 1 || change_month > 12 || change_month < 1 || change_year < 1900 || change_year > 2017)
		return Dialog_Show(playerid, changebirthday, DIALOG_STYLE_INPUT, "Смена даты рождения.", "Ошибка!\nВведите дату нового дня рождения.\nФормат: день/месяц/год", "Продолжить", "Отмена");
	
	new str[18];
	format(str, sizeof(str), "%d/%d/%d", change_day, change_month, change_year);
	
	player_info[playerid][donate] -= Donate[7][Price];
	character_info[playerid][birthDate] = str;
	
	new qu[128];
	format(qu, sizeof(qu), "UPDATE `characters` SET `date`='%s' WHERE id='%d'", str, character_info[playerid][id]);
	mysql_function_query(dbHandle, qu, false, "", "");	
	SendClientMessageEx(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно сменили дату рождения персонажа на %s!", str);
	return 1;
}

Dialog:SexChange(playerid, response, listitem, inputtext[])
{
	if(!response)
		return 1;
	
	if(player_info[playerid][donate] < Donate[6][Price])
		return SendClientMessageEx(playerid, -1, "{FF0000}>{FFFFFF} Для смены пола нехватает %d р.", Donate[6][Price] - player_info[playerid][donate]);
	
	new qu[128];
	if(character_info[playerid][sex] == 1)
	{
		format(qu, sizeof(qu), "UPDATE `characters` SET `sex`='2' WHERE id='%d'", character_info[playerid][id]);
		character_info[playerid][sex] = 2;
	}
	else
	{
		format(qu, sizeof(qu), "UPDATE `characters` SET `sex`='1' WHERE id='%d'", character_info[playerid][id]);
		character_info[playerid][sex] = 1;
	}

	mysql_function_query(dbHandle, qu, false, "", "");	
	player_info[playerid][donate] -= Donate[6][Price];
	SendClientMessage(playerid, COLOR_MSGSERVER, ">{ffffff} Вы успешно сменили пол персонажа!");
	return 1;
}
