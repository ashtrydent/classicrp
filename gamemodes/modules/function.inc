stock ReturnDate()
{
	static
	    nowdate[36];

	getdate(nowdate[2], nowdate[1], nowdate[0]);
	gettime(nowdate[3], nowdate[4], nowdate[5]);

	format(nowdate, sizeof(nowdate), "%02d/%02d/%d, %02d:%02d", nowdate[0], nowdate[1], nowdate[2], nowdate[3], nowdate[4]);
	return nowdate;
}


stock IsMedic(playerid)
{
	if(!InFactionId(playerid, SAHD_FACTION) && !InFactionId(playerid, LSFD_FACTION))
		return 0;
	else
		return 1;
}
stock IsCop(playerid)
{
	if(!InFactionId(playerid, LSPD_FACTION) && !InFactionId(playerid, SASD_FACTION) && !InFactionId(playerid, LSSD_FACTION)) 
		return 0;
	else
		return 1;
}
stock IsMech(playerid)
{
	if(!InFactionId(playerid, MECHANICS_FACTION))
		return 0;
	else
		return 1;
}

stock Log_Write(const path[], const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    File:file,
	    string[1024]
	;
	if ((start = strfind(path, "/")) != -1) {
	    strmid(string, path, 0, start + 1);

	    if (!fexist(string))
	        return printf("** Warning: Directory \"%s\" doesn't exist.", string);
	}
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	file = fopen(path, io_append);

	if (!file)
	    return 0;

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 1024
		#emit PUSH.C string
		#emit PUSH.C args
		#emit SYSREQ.C format

		fwrite(file, string);
		fwrite(file, "\r\n");
		fclose(file);

		#emit LCTRL 5
		#emit SCTRL 4
		#emit RETN
	}
	fwrite(file, str);
	fwrite(file, "\r\n");
	fclose(file);

	return 1;
}

stock SendClientMessageEx(playerid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if (args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args
        #emit SYSREQ.C format

        SendClientMessage(playerid, color, string);

        #emit LCTRL 5
        #emit SCTRL 4
        #emit RETN
    }
    return SendClientMessage(playerid, color, str);
}

stock TaxiOn(v)
{
	if(IsValidDynamicObject(veh_info[v][taxi])) return 0;
	new floatxyz;
	switch(GetVehicleModel(v))
	{
		case 401: x=-0.004999, y=0.000000, z=0.799999;
		case 402: x=-0.004999, y=-0.519999, z=0.769999;
		case 404: x=-0.004999, y=-0.224999, z=0.934999;
		case 405: x=-0.004999, y=-0.224999, z=0.759999;
		case 410: x=0.010000, y=-0.224999, z=0.899999;
		case 409: x=0.000000, y=0.419999, z=0.824999;
		case 411: x=0.000000, y=-0.089999, z=0.719999;
		case 412: x=0.000000, y=-0.089999, z=0.714999;
		case 413: x=0.000000, y=0.704999, z=1.134999;
		case 415: x=0.000000, y=-0.259999, z=0.609999;
		case 418: x=0.000000, y=0.389999, z=1.039999;
		case 419: x=0.000000, y=-0.324999, z=0.694999;
		case 421: x=0.000000, y=-0.174999, z=0.729999;
		case 422: x=0.000000, y=0.044999, z=0.799999;
		case 424: x=0.000000, y=0.044999, z=0.864999;
		case 426: x=0.000000, y=-0.264999, z=0.849999;
		case 428: x=0.000000, y=0.754999, z=1.369998;
		case 431: x=0.020000, y=5.230072, z=2.115000;
		case 434: x=0.020000, y=-0.060000, z=0.729999;
		case 436: x=0.020000, y=-0.259999, z=0.844999;
		case 437: x=0.020000, y=4.630058, z=2.044999;
		case 442: x=0.020000, y=0.009999, z=0.889999;
		case 444: x=0.020000, y=0.234999, z=1.689998;
		case 445: x=0.020000, y=-0.254999, z=0.844999;
		case 451: x=-0.044999, y=-0.534999, z=0.589999;
		case 455: x=-0.044999, y=1.189998, z=1.664998;
		case 458: x=0.000000, y=0.000000, z=0.724999;
		case 459: x=0.000000, y=0.544999, z=1.114999;
		case 466: x=0.000000, y=-0.204999, z=0.849999;
		case 467: x=0.000000, y=-0.004999, z=0.829999;
		case 470: x=0.000000, y=-0.004999, z=1.089999;
		case 474: x=0.000000, y=-0.229999, z=0.794999;
		case 475: x=0.000000, y=-0.229999, z=0.704999;
		case 477: x=0.000000, y=-0.404999, z=0.734999;
		case 478: x=0.000000, y=0.125000, z=0.909999;
		case 479: x=0.000000, y=-0.269999, z=0.984999;
		case 480: x=0.000000, y=-1.024999, z=0.684999;
		case 482: x=0.000000, y=1.074999, z=0.904999;
		case 483: x=0.000000, y=1.499998, z=1.019999;
		case 489: x=0.000000, y=-0.114999, z=1.084999;
		case 490: x=0.000000, y=0.474999, z=1.089999;
		case 491: x=0.000000, y=-0.404999, z=0.679999;
		case 492: x=0.000000, y=-0.279999, z=0.859999;
		case 494: x=0.000000, y=-0.374999, z=0.739999;
		case 495: x=0.000000, y=0.050000, z=0.999999;
		case 496: x=0.000000, y=-0.444999, z=0.809999;
		case 498: x=0.000000, y=1.749998, z=2.014998;
		case 502: x=0.000000, y=-0.469999, z=0.779999;
		case 503: x=0.000000, y=-0.469999, z=0.764999;
		case 504: x=0.000000, y=0.065000, z=0.854999;
		case 505: x=0.000000, y=0.065000, z=1.084999;
		case 506: x=0.000000, y=-0.444999, z=0.574999;
		case 507: x=0.000000, y=-0.339999, z=0.779999;
		case 516: x=0.000000, y=-0.089999, z=0.864999;
		case 517: x=0.000000, y=-0.344999, z=0.839999;
		case 518: x=0.000000, y=-0.119999, z=0.689999;
		case 525: x=0.000000, y=-0.454999, z=1.444998;
		case 528: x=0.000000, y=0.050000, z=1.074999;
		case 527: x=0.000000, y=-0.054999, z=0.874999;
		case 526: x=0.000000, y=-0.234999, z=0.644999;
		case 529: x=0.000000, y=-0.234999, z=0.899999;
		case 534: x=0.000000, y=-0.029999, z=0.604999;
		case 535: x=0.000000, y=0.095000, z=0.804999;
		case 540: x=0.000000, y=-0.259999, z=0.699999;
		case 541: x=0.000000, y=-0.259999, z=0.619999;
		case 542: x=0.000000, y=-0.259999, z=0.829999;
		case 543: x=0.000000, y=0.110000, z=0.874999;
		case 544: x=0.000000, y=2.510010, z=1.459998;
		case 545: x=0.000000, y=-0.384999, z=0.744999;
		case 546: x=0.000000, y=-0.384999, z=0.834999;
		case 547: x=0.000000, y=-0.384999, z=0.889999;
		case 549: x=0.000000, y=0.035000, z=0.719999;
		case 550: x=0.000000, y=-0.089999, z=0.724999;
		case 551: x=0.000000, y=-0.344999, z=0.904999;
		case 552: x=0.000000, y=0.609999, z=1.314998;
		case 554: x=0.000000, y=0.025000, z=1.004999;
		case 556: x=0.000000, y=0.489999, z=1.679998;
		case 557: x=0.000000, y=0.010000, z=1.639998;
		case 558: x=0.000000, y=-0.354999, z=0.824999;
		case 559: x=0.000000, y=-0.354999, z=0.704999;
		case 562: x=0.000000, y=-0.354999, z=0.749999;
		case 561: x=0.000000, y=-0.129999, z=0.829999;
		case 560: x=0.000000, y=-0.074999, z=0.824999;
		case 565: x=0.000000, y=-0.414999, z=0.674999;
		case 566: x=0.000000, y=-0.169999, z=0.844999;
		case 576: x=0.000000, y=-0.169999, z=0.884999;
		case 579: x=0.000000, y=-0.369999, z=0.939999;
		case 580: x=0.000000, y=-0.059999, z=1.034999;
		case 585: x=0.000000, y=-0.259999, z=0.974999;
		case 587: x=0.000000, y=-0.599999, z=0.734999;
		case 589: x=0.000000, y=-0.194999, z=1.049999;
		case 596: x=0.000000, y=-0.264999, z=0.849999;
		case 597: x=0.000000, y=-0.264999, z=0.849999;
		case 598: x=0.000000, y=-0.264999, z=0.849999;
		case 601: x=0.000000, y=1.209999, z=1.499998;
		case 604: x=0.000000, y=-0.159999, z=0.864999;
		case 603: x=0.000000, y=-0.429999, z=0.644999;
		case 602: x=0.000000, y=-0.429999, z=0.679999;
		case 605: x=0.000000, y=0.015000, z=0.884999;
		default: return 0;
	}

	new Float:px, Float:py, Float:pz;
	GetVehiclePos(v, px,py,pz);
	veh_info[v][taxi] = CreateDynamicObject(19308, px,py,pz+1, 0.0,0.0,0.0);
	
	AttachDynamicObjectToVehicle(veh_info[v][taxi], v, x,y,z+0.09, 0.0,0.0,90.0);
	return 1;
}

stock GetMaskID(playerid)
{
	if(!IsPlayerLoged(playerid)) return 0;
	return character_info[playerid][id] * player_info[playerid][id] + 114;
}
stock GetPlayerByMaskId(playerid, maskid)
{
	new qu[146+11];
	format(qu, sizeof(qu), "SELECT characters.name, characters.id FROM characters JOIN users ON characters.userid = users.id WHERE characters.id * users.id+114 = %d", maskid);
	mysql_function_query(dbHandle, qu, true, "OnGetPlayerByMaskId", "ii", playerid, maskid);
}

stock MaskOn(playerid)
{
	if(!IsPlayerLoged(playerid)) return 0;
	SetPVarInt(playerid, "MASKED", 1);
	//if(IsValidDynamic3DTextLabel(character_info[playerid][mask3d])) DestroyDynamic3DTextLabel(character_info[playerid][mask3d]);
	new str[25];
	format(str, sizeof(str), "MASK_%d", GetMaskID(playerid));
	SetPlayerNameEx(playerid, str);
	//character_info[playerid][mask3d] = CreateDynamic3DTextLabel(str, COLOR_TOMATO, 0, 0, 0, 10.0, playerid);
	//for(new i = GetPlayerPoolSize(); i != -1; --i) ShowPlayerNameTagForPlayer(i, playerid, false);
	
	return 1;
}

stock MaskOff(playerid)
{
	//if(IsValidDynamic3DTextLabel(character_info[playerid][mask3d])) DestroyDynamic3DTextLabel(character_info[playerid][mask3d]);
	//for(new i = GetPlayerPoolSize(); i != -1; --i) ShowPlayerNameTagForPlayer(i, playerid, true);
	if(IsPlayerLoged(playerid)) SetPlayerNameEx(playerid, character_info[playerid][name]);
	if(GetPVarInt(playerid, "MASKED")) DeletePVar(playerid, "MASKED");
	else return 0;
	return 1;
}
stock usegun(playerid, gunid, item)
{
	if(character_info[playerid][faction] == 0 && character_info[playerid][lvl] < 5) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Использовать оружие можно с 5 часов игры!");
	if(IsDuty(playerid) && InFactionId(playerid, LSPD_FACTION) || IsDuty(playerid) && InFactionId(playerid, SASD_FACTION) || IsDuty(playerid) && InFactionId(playerid, LSSD_FACTION)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете пользоваться личным оружием на службе!");
	
	new item_slot = player_info[playerid][inv_selected];
    if(character_info[playerid][gun] > 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас в руках уже есть оружие!");
	new str[128];
	if(gunid >= 3 && gunid <= 9)
	{
	    if(deleteitem(playerid, item, 1))
	    {
		    character_info[playerid][gun] = gunid;
			character_info[playerid][ammo] = 1;
			GivePlayerWeapon(playerid, gunid, character_info[playerid][ammo]);
			format(str, sizeof(str), ">{FFFFFF} Вы достали из инвентаря %s.", senderitems(item));
			SCM(playerid, COLOR_MSGSERVER, str);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте команду /invwep, либо нажмите 'N' чтобы убрать оружие из рук.");
		}
	}
	else
	{
	    if(item_slot == -1) return 1;
     	character_info[playerid][gun] = gunid;
     	SetPlayerAttachedObject(playerid, MAX_ATTACH+1, Items[item][Model], 6);
     	if(item >= 34 && item <= 45) character_info[playerid][ammo] = 0;
		else
     	{
	     	character_info[playerid][ammo] = character_info[playerid][inv][count][item_slot];
			if(gunid != 41 && gunid != 42 && gunid != 43) GivePlayerWeapon(playerid, gunid, character_info[playerid][ammo]);
			else GivePlayerWeapon(playerid, gunid, 99999999);
		}

		format(str, sizeof(str), ">{FFFFFF} Вы достали из инвентаря %s.", senderitems(item));
		SCM(playerid, COLOR_MSGSERVER, str);
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте команду /invwep, либо нажмите 'N' чтобы убрать оружие из рук.");
		if(!Items[item][compound]) deleteitemslot(playerid, item_slot);
		else deleteitem(playerid, item, 1);
	}
	return 1;
}
stock usesilencer(playerid)
{
	if(character_info[playerid][gun] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет в руках оружия.");
    if(character_info[playerid][silencer] > 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} На вашем оружии уже есть глушитель.");

	if(character_info[playerid][gun] == 24 && character_info[playerid][gun] == 22)
	{
	    if(deleteitem(playerid, 342, 1))
	    {
		    character_info[playerid][silencer] = 1;
			GivePlayerWeapon(playerid, 23, character_info[playerid][ammo]);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы накрутили на ствол своего оружия глушитель.");
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте команду /invsilencer чтобы снять глушитель.");
		}
	}
	if(character_info[playerid][gun] > 24 && character_info[playerid][gun] < 22)
	{
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} На данный тип оружия нельзя накрутить глушитель.");
	}
	return 1;
}	
	
stock usedrug(playerid, item, Float:health, addiction_power, time_addiction_power)
{
	if(!deleteitem(playerid, item, 1)) return 1;
	new Float:_health, str[128];
	GetPlayerHealth(playerid, _health);
	_health += health;
	if(_health > 100) _health = 100;
	SetPlayerHealth(playerid, _health);
	character_info[playerid][addiction] += addiction_power;
	if(character_info[playerid][addiction] > 100) character_info[playerid][addiction] = 100;
	character_info[playerid][time_addiction] -= time_addiction_power;
	
	format(str, sizeof(str), "Вы употребили %s", senderitems(item));
	SCM(playerid, COLOR_PAPAYA, str);
	format(str, sizeof(str), "употребил %s", senderitems(item));
	SYS_AME(playerid, str);
	character_info[playerid][drug_effect][type] = item;
	character_info[playerid][drug_effect][time_effect] = 120;
	
	if(character_info[playerid][drug_effect][type] == 28) SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
	SetPlayerDrunkLevel(playerid, 0);
	return 1;
}
//------------------------------------------------------------------------------


stock MoneyPropDialog(playerid)
{
	if(OwnerInProp(playerid))
	{
		new str_head[64], propid = GetLocalIdProp(character_info[playerid][prop]);
		format(str_head, sizeof(str_head), "Денег в имуществе: %d$", prop_info[propid][money]);
	    SPD(playerid, 39, DIALOG_STYLE_TABLIST, str_head, "Забрать\nПоложить", "Выбрать", "Отменить");
	}
	else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится в своем доме");
	return 1;
}



stock prop_inv(playerid)
{
    new str[2048] = "{AFAFAF}Предмет\t{AFAFAF}Количество\n", color[128], count_text[128], itemname_text[128], li = GetLocalIdProp(character_info[playerid][prop]);
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    format(itemname_text, sizeof(itemname_text), "%s", senderitems(0)), format(count_text, sizeof(count_text), "");
	 	if(prop_info[li][inv][count][i] < 1)
		{
			prop_info[li][inv][id][i] = 0;
	 		prop_info[li][inv][count][i] = 0;
		}
  		if(prop_info[li][inv][id][i] == 0) color = "{AFAFAF}";
		else color = "{ffffff}";

		if(prop_info[li][inv][id][i] != 0)
		{
			if(Items[prop_info[li][inv][id][i]][compound])
			{
				format(itemname_text, sizeof(itemname_text), "%s",  senderitems(prop_info[li][inv][id][i]));
    			if(prop_info[li][inv][count][i] > 0)
					format(count_text, sizeof(count_text), "Количество: %d", prop_info[li][inv][count][i]);
			}
			else format(itemname_text, sizeof(itemname_text), "%s (%d)\tКоличество: 1", senderitems(prop_info[li][inv][id][i]), prop_info[li][inv][count][i]);
		}

		format(str, sizeof(str), "%s{AFAFAF}%s%s\t%s\n",str, color, itemname_text, count_text);
 	}
    ShowPlayerDialog(playerid, 32, DIALOG_STYLE_TABLIST_HEADERS,"Инвентарь имущества", str, "Выбрать", "Отмена");
}

stock DeleteMDO(playerid)
{
	if(IsValidDynamic3DTextLabel(MDO[playerid]))
	{
		DestroyDynamic3DTextLabel(MDO[playerid]);
		//printf("[debug_3d] delete mdo");
		MDO[playerid] = Text3D:INVALID_3DTEXT_ID;
		return 1;
	}
	return 0;
}


stock linebreak(playerid, param[], Float:radius, col1,col2,col3,col4,col5)
{
	new text[180], string[180];
	if(strlen(param) >= 80)
	{
      	strmid(string,param, 64, 180);
       	strdel(param,64, 180);
		
		format(text, sizeof(text), "%s ...", param);
        ProxDetector( radius, GetPlayerVirtualWorld( playerid ), playerid, text, text, col1,col2,col3,col4,col5);
		format(text, sizeof(text), "... %s", string);
		ProxDetector( radius, GetPlayerVirtualWorld( playerid ), playerid, text, text, col1,col2,col3,col4,col5);
		return 1;
	}
	else
	{
		ProxDetector( radius, GetPlayerVirtualWorld( playerid ), playerid, param, param, col1,col2,col3,col4,col5);
		return 0;
	}
}


stock SYS_AME(playerid, params[])
{
	new string[128];
	if(sscanf(params,"s[124]", params[0])) return 1;
	format( string, 128, "%s %s", sendername(playerid, true), params[0] );
	SetPlayerChatBubble(playerid,string,COLOR_ME,30.0,5000);
    return 1;
}


//
stock ShowFurniture(playerid)
{
    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200)
    {
        new furniture_count = 0;
		for(new i; i<MAX_FURNITURE; i++)
			if(furniture[i][houseid] == character_info[playerid][prop]) furniture_count++;

		new limit_items = 75;
		if(IsPremium(playerid, PREMIUM_GOLD)) limit_items = 200;
		else if(IsPremium(playerid, PREMIUM_SILVER)) limit_items = 150;
		else if(IsPremium(playerid, PREMIUM_BRONZE)) limit_items = 100;
		
		new str_header[32];
		format(str_header, sizeof(str_header), "Лимит: %d/%d", furniture_count, limit_items);
		
		if(furniture_count > limit_items) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Лимит фурнитуры для вашего дома превышен!");

		new str[350];
		format(str, sizeof(str), "%s1. Ванная\n", str);
		format(str, sizeof(str), "%s2. Кухня\n", str);
		format(str, sizeof(str), "%s3. Кровати и тумбочки\n", str);
		format(str, sizeof(str), "%s4. Шкафы\n", str);
		format(str, sizeof(str), "%s5. Декорации\n", str);
		format(str, sizeof(str), "%s6. Электроника\n", str);
		format(str, sizeof(str), "%s7. Ситуативное\n", str);
		format(str, sizeof(str), "%s8. Для бизнеса\n", str);
		format(str, sizeof(str), "%s9. Диваны и кресла\n", str);
		format(str, sizeof(str), "%s10. Игральные автоматы\n", str);
        format(str, sizeof(str), "%s11. Растения\n", str);
		format(str, sizeof(str), "%s12. Двери и стены\n", str);
		format(str, sizeof(str), "%s13. Еда и напитки\n", str);
		format(str, sizeof(str), "%s14. Предметы из бара\n", str);
		format(str, sizeof(str), "%s15. Одежда\n", str);
		format(str, sizeof(str), "%s16. Спортивный инвентарь\n", str);
		format(str, sizeof(str), "%s17. Детали машин\n", str);
		format(str, sizeof(str), "%s18. Эффекты\n", str);
		SPD(playerid, 13, DIALOG_STYLE_TABLIST, str_header, str, "Выбрать", "Закрыть");
	}
	return 1;
}

stock IsBike(v)
{
	new vmodel = GetVehicleModel(v);
	switch(vmodel)
	{
		case 481: return 1;
		case 509..510: return 1;	
	}
	return 0;
}
stock IsMoto(v)
{
	for(new i; i<sizeof(Moto); i++)
	{
		if(GetVehicleModel(v) == Moto[i]) return 1;
	}
	return 0;
}

stock BankSMS(playerid, text[], sum=-1)
{
	if(character_info[playerid][phoneslot] == -1) return 0;
	new str[256];
	if(sum == -1) format(str, sizeof(str), "SMS от BANK LS: %s", text);
	else format(str, sizeof(str), "SMS от BANK LS: %s (Сумма: %d$)", text, sum);
	SCM(playerid, COLOR_YELLOW, str);
	return 1;
}



stock PVarPosSave(playerid)
{
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, xyz);
	SetPVarFloat(playerid, "pos_x", x);
	SetPVarFloat(playerid, "pos_y", y);
	SetPVarFloat(playerid, "pos_z", z);
	SetPVarInt(playerid, "pos_int", GetPlayerInterior(playerid));
	SetPVarInt(playerid, "pos_vw", GetPlayerVirtualWorld(playerid));
}

stock PutInCar(playerid, vehid, seatid)
{
	ACveh[playerid] = vehid;
	PutPlayerInVehicle(playerid, vehid, seatid);
	return 1;
}

stock FixEditBug(playerid)
{
	if(GetPVarInt(playerid, "EditObject"))
	{
		DeletePVar(playerid, "EditObject");
		character_info[playerid][editobject] = 0;
		CancelEdit(playerid);
	}
}

stock SetPlayerInt(playerid, intID)
{
	if(!IsPlayerConnected(playerid))
		return 0;
	
	character_info[playerid][Interior] = intID;
	SetPlayerInterior(playerid, intID);
	
	FixEditBug(playerid);
	return 1;
}

stock IsPlayerNearPlayer(playerid, targetid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetPlayerPos(targetid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

stock SetPlayerToFacePlayer(playerid, targetid)
{
	new
	    Float:x[2],
	    Float:y[2],
	    Float:z[2],
	    Float:angle;

	GetPlayerPos(targetid, x[0], y[0], z[0]);
	GetPlayerPos(playerid, x[1], y[1], z[1]);

	angle = (180.0 - atan2(x[1] - x[0], y[1] - y[0]));
	SetPlayerFacingAngle(playerid, angle + (5.0 * -1));
}


stock SetPlayerVw(playerid, vw)
{
	if(!IsPlayerConnected(playerid))
		return 0;
	
	character_info[playerid][VW]= vw;
	SetPlayerVirtualWorld(playerid, vw);
	
	FixEditBug(playerid);
	return 1;
}

stock PVarPosTeleport(playerid)
{
	
	SetPlayerVw(playerid,GetPVarInt(playerid, "pos_vw"));
	SetPlayerInt(playerid,GetPVarInt(playerid, "pos_int"));
	//SetTimerEx("SetPlayerPosEx", 500, false, "ifffii", playerid, GetPVarFloat(playerid, "pos_x"), GetPVarFloat(playerid, "pos_y"), GetPVarFloat(playerid, "pos_z"), GetPVarInt(playerid, "pos_vw"), GetPVarInt(playerid, "pos_int"));
	DeletePVar(playerid, "pos_x");
	DeletePVar(playerid, "pos_y");
	DeletePVar(playerid, "pos_z");
	DeletePVar(playerid, "pos_int");
	DeletePVar(playerid, "pos_vw");
	DeletePVar(playerid, "SPEC_PLAYER");
	DeletePVar(playerid, "SPEC");
}


stock PVarPosIsset(playerid)
{
	if(GetPVarFloat(playerid, "pos_x") && GetPVarFloat(playerid, "pos_x") && GetPVarFloat(playerid, "pos_x")) 
		return 1;
	else 
		return 0;
}

stock TestMDC(playerid)
{
	if(!IsCop(playerid))
		return 1;
	new v = GetCar(playerid, true);
	if(veh_info[v][owner] >= 0) return 1;
	new fid = ntop(veh_info[v][owner]);
	if(fid != character_info[playerid][faction]) return 1;
	
	return 0;
}

stock devmsg(playerid, text[])
{
	if(!GetPVarInt(playerid, "_dev_")) return 1;
	new str[180];
	format(str, sizeof(str), "(DEV) >{FFFFFF} %s", text);
	SCM(playerid, COLOR_BLUE, str);
	return 1;
}



stock TaxiMsg(text[])
{
	foreach(new p : Player)
	{
		if(!isPlayerDriver(p)) continue;
		new v = GetPlayerVehicleID(p);
		if(IsValidDynamicObject(veh_info[v][taxi])) SCM(p, COLOR_GREEN, text);
	}
}

stock fmsg(playerid, string[], fact = 0)
{
	new str[180];
	format(str, sizeof(str), "** %s %s %s **", faction_ranks[character_info[playerid][faction]][character_info[playerid][rank]], sendername(playerid, true), string);
	
	if(fact == 0)
	{
		foreach(new p : Player)
		{
			if(IsPlayerLoged(p) && character_info[p][faction] == character_info[playerid][faction])
			{
				SCM(p, COLOR_FACTIONCHAT, str);
			}
		}
	}
	else 
	{
		foreach(new p : Player)
		{
			if(IsPlayerLoged(p) && character_info[p][faction] == fact)
			{
				SCM(p, COLOR_FACTIONCHAT, str);
			}
		}
	}
}

stock anyRadio(playerid)
{
	if(checkitem(playerid, 83) >= 0)
		return 1;
	
	for(new i=0; i<MAX_ATTACH; i++)
	{
	    if(attach[playerid][i][iditem] == 83)
			return 1;
	}
	
	return 0;
}

stock IsFixPickup(playerid)
{
	for(new i; i<sizeof(FixPickup); i++)
	{		
		if(PlayerToPoint(6.0, playerid, FixPickup[i][posX], FixPickup[i][posY], FixPickup[i][posZ]) && FixPickup[i][factionid] == 0) 
			return 2;
		
		if(PlayerToPoint(6.0, playerid, FixPickup[i][posX], FixPickup[i][posY], FixPickup[i][posZ]) && InFactionId(playerid, FixPickup[i][factionid]) && GetPlayerVirtualWorld(playerid) == FixPickup[i][VW]) 
			return 1;
	}
	return 0;
}


stock LoadPayphones() {
	for (new i = 0; i < sizeof(Payphone); i++) {
		CreatePickup(1239, 8, Payphone[i][posX],Payphone[i][posY],Payphone[i][posZ]);
		Payphone[i][a3d] = CreateDynamic3DTextLabel("Таксофон\n{FFFFFF}Введите /call чтобы воспользоваться.", COLOR_INFO, Payphone[i][posX],Payphone[i][posY],Payphone[i][posZ], 25.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, -1, 5.5);
	}
}
stock UsePayphone(playerid, payphoneid) {
	if(IsPlayerUsePayphone(playerid) || IsPayphoneUse(payphoneid)) return false;

	Payphone[payphoneid][used] = true;
	SetPayphone(playerid, payphoneid);

	return true;
}
stock UnusePayphone(playerid=INVALID_PLAYER_ID, payphoneid=-1) {
	if(playerid != INVALID_PLAYER_ID) {
		DeletePVar(playerid, "payphone");
	}
	if(payphoneid != -1) {
		Payphone[payphoneid][used] = false;
	}
}
stock IsPlayerUsePayphone(playerid) {
	return ((GetPayphone(playerid) > 0) ? true : false);
}
stock IsPayphoneUse(payphoneid) {
	return ((Payphone[payphoneid][used]) ? true : false);
}
stock IsPlayerAtPayphone(playerid, payphoneid=-1) {
	if(payphoneid == -1) {
		for(new i = 0; i < sizeof(Payphone); i++) {
			if(PlayerToPoint(1.0, playerid, Payphone[i][posX],Payphone[i][posY],Payphone[i][posZ])) return i;
		}
	} else if(payphoneid <= sizeof(Payphone) && PlayerToPoint(1.0, playerid, Payphone[payphoneid][posX],Payphone[payphoneid][posY],Payphone[payphoneid][posZ])) return payphoneid;

	return -1;
}
stock GetPayphone(playerid) {
	return GetPVarInt(playerid, "payphone")-1;
}
stock SetPayphone(playerid, payphoneid) {
	SetPVarInt(playerid, "payphone", payphoneid+1);
	return true;
}
stock GetPhonenumber(playerid) {
	new phonenumber;

	phonenumber = IsPlayerAtPayphone(playerid);
	if(phonenumber == -1) {
		if(character_info[playerid][phoneslot] != -1) {
			phonenumber = character_info[playerid][phoneslot];
		} else return -1;
	}
	else phonenumber += 1000;

    return phonenumber;
}


stock IsDutyPickup(playerid)
{	
	for(new i; i<sizeof(FactionDutyPickup); i++)
	{
		if(PlayerToPoint(3.0, playerid, FactionDutyPickup[i][posX], FactionDutyPickup[i][posY], FactionDutyPickup[i][posZ]) && GetPlayerVirtualWorld(playerid) == FactionDutyPickup[i][VW] && InFactionId(playerid, FactionDutyPickup[i][factionid])) 
			return 1;
	}
	
	new Float:x, Float:y, Float:z;
	for(new i=0; i<MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, xyz);
		if(character_info[playerid][faction] == ntop(veh_info[i][owner]) && PlayerToPoint(3.0, playerid, xyz)) 
		{
			if(GetVehicleModel(i) != 427 && GetVehicleModel(i) != 528 && GetVehicleModel(i) != 490) return 0; 
			return 1;
		}
		
	}
	return 0;
}

stock IsFactionCar(playerid)
{
	new Float:x, Float:y, Float:z;
	for(new i=0; i<MAX_VEHICLES; i++)
	{
	    GetVehiclePos(i, xyz);
		if(character_info[playerid][faction] == ntop(veh_info[i][owner]) && PlayerToPoint(3.0, playerid, xyz)) return i;
	}
	return -1;
}


stock AddTicket(playerid, summ, reason[])
{
	if(!IsPlayerLoged(playerid) || strval(reason) > 32) return 0;
	new qu[76+11+11+32];
	format(qu, sizeof(qu), "INSERT INTO `tickets`(`characterid`, `summ`, `reason`) VALUES (%d, %d, '%s')", character_info[playerid][id], summ, reason);
	mysql_function_query(dbHandle, qu, false, "", "");
	LoadTickets(playerid);
	return 1;
}
stock LoadTickets(playerid)
{
	if(!IsPlayerLoged(playerid)) return 0;
	new qu[62+11];
	format(qu, sizeof(qu), "SELECT id,summ,reason,date FROM `tickets` WHERE characterid=%d", character_info[playerid][id]);
	mysql_function_query(dbHandle, qu, true, "OnLoadTickets", "i", playerid);
	return 1;
}

stock FriskPlayer(playerid, param, bool:sysmsg=true)
{
	new str[512], buff[256];
	format(str, sizeof(str), "{FFFFFF}Оружие в руках: %s", Items[GetItemByGun(character_info[param][gun])][Name]);
	format(str, sizeof(str), "%s\nДенег на руках: %d$", str, character_info[param][money]);
	strcat(str, "\n\n{b1b1b1}ИНВЕНТАРЬ{FFFFFF}");
	for(new i; i<MAX_INV_SLOTS; i++)
	{
		if(character_info[param][inv][id][i] == 0) continue;
		if(Items[character_info[param][inv][id][i]][compound]) 
			format(buff, sizeof(buff), "\n%d. %s {b1b1b1}| Кол-во: %d{ffffff}", i+1, Items[character_info[param][inv][id][i]][Name], character_info[param][inv][count][i]);
		else 
			format(buff, sizeof(buff), "\n%d. %s(%d) {b1b1b1}| Колво: 1{ffffff}", i+1, Items[character_info[param][inv][id][i]][Name], character_info[param][inv][count][i]);
		
		strcat(str, buff);
	}
	new _attach_;
	for(new i; i<MAX_ATTACH; i++) 
	{
		if(attach[param][i][iditem] > 0)
		{
			_attach_ = 1;
			break;
		}
	}
	if(_attach_)
	{
		strcat(str, "\n\n{b1b1b1}ПРИКРЕПЛЕННЫЕ{FFFFFF}");
		for(new i; i<MAX_ATTACH; i++)
		{
			if(attach[param][i][iditem] < 1) continue; 
			format(buff, sizeof(buff), "\n%d. %s", i+1, Items[attach[param][i][iditem]][Name]);
			strcat(str, buff);
		}
	}
	if(sysmsg)
	{
		new strame[64];
		format(strame, sizeof(strame), "обыскивает %s", sendername(param));
		SYS_AME(playerid, strame);
	}
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Инвентарь", str, "Закрыть", "");
	return 1;
}


stock GetCoordBootVehicle(vehicleid, &Float:x, &Float:y, &Float:z)
{
    new Float:angle,Float:distance;
    GetVehicleModelInfo(GetVehicleModel(vehicleid), 1, x, distance, z);
    distance = distance/2 + 0.1;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);
    x += (distance * floatsin(-angle+180, degrees));
    y += (distance * floatcos(-angle+180, degrees));
    return 1;
}
stock GetCoordBonnetVehicle(vehicleid, &Float:x, &Float:y, &Float:z)
{
    new Float:angle,Float:distance;
    GetVehicleModelInfo(GetVehicleModel(vehicleid), 1, x, distance, z);
    distance = distance/2 + 0.1;
    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);
    x -= (distance * floatsin(-angle+180, degrees));
    y -= (distance * floatcos(-angle+180, degrees));
    return 1;
}


stock LoadArecords(playerid, targetid)
{
	if(!IsPlayerLoged(playerid) || !IsPlayerLoged(targetid)) return 1;
	GameTextForPlayer(playerid, "~r~LOADING...", 10000, 3);
	new qu[86+11];
	format(qu, sizeof(qu), "SELECT id, text, time FROM arecord WHERE characterid=%d ORDER BY `arecord`.`id` DESC", character_info[targetid][id]);
	mysql_function_query(dbHandle, qu, true, "OnLoadArecords", "i", playerid);
	return 1;
}


stock InATM(playerid)
{
	for(new i; i<MAX_ATM; i++)
	{
		if(atm_info[i][id] < 1) continue;
		if(PlayerToPoint(1.5, playerid, atm_info[i][posX], atm_info[i][posY], atm_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == atm_info[i][VW]) return 1;
	}
	return 0;
}


stock InServiceStation(playerid)
{
	if(!isPlayerDriver(playerid)) 
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть за рулем автомобиля!");
		return 0;
	}
	new v = GetPlayerVehicleID(playerid);
	
	if(veh_info[v][owner] < 0 && InFactionId(playerid, ntop(veh_info[v][owner]), true) || veh_info[v][owner] > 0 && veh_info[v][owner] == character_info[playerid][id])
	{
		for(new i; i<sizeof(ServiceStation); i++)
		{
			if(PlayerToPoint(5.0, playerid, ServiceStation[i][posX],ServiceStation[i][posY],ServiceStation[i][posZ]) && GetPlayerVirtualWorld(playerid) == ServiceStation[i][VW]) return 1;
		}
	}
	else
	{
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете модернизировать этот транспорт!");
		return 0;
	}
	
	return 0;
}

stock StopPlayerSpec(playerid)
{
	TogglePlayerSpectating(playerid, 0);
	SetCameraBehindPlayer(playerid);
	return 1;
}

stock VKBOT_ACTIVATE()
{
	new activated[4];
	new File:opnfile; // создаём файловую переменную
	opnfile=fopen("vkbot.txt",io_readwrite); /* открываем файл file с возможностью чтения и записываем его идентификатор в opnfile */
	fread(opnfile,activated);
	fclose(opnfile); // закрываем работу с файлом
	//printf(activated);
	if(strfind(activated, "1",true) !=-1) return 1;
	return 0;
}
stock UpdateGameModeText()
{
	new str[32], prefix_servername[12];
	new File:opnfile; // создаём файловую переменную
	opnfile=fopen("server_version.txt",io_readwrite); /* открываем файл file с возможностью чтения и записываем его идентификатор в opnfile */
	fread(opnfile,prefix_servername);
	fclose(opnfile); // закрываем работу с файлом
	
	format(str, sizeof(str), "%s %s", SERVER_NAME_FIRST, prefix_servername);
	SetGameModeText(str);
	
	return 1;
}


stock PickUpBoombox(playerid)
{
    foreach(new i : Player)
	{
 		if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
   		{
     		StopStream(i);
		}
	}
	giveitem(playerid, 142);
	DeletePVar(playerid, "BBArea");
	DestroyDynamicObject(GetPVarInt(playerid, "PlacedBB"));
	DeletePVar(playerid, "PlacedBB");
 	DeletePVar(playerid, "BBX"); DeletePVar(playerid, "BBY"); DeletePVar(playerid, "BBZ");
	DeletePVar(playerid, "BBInt");
	DeletePVar(playerid, "BBVW");
	DeletePVar(playerid, "BBStation");
	return 1;
}

stock PlayStream(playerid, url[], Float:POSX = 0.0, Float:POSY = 0.0, Float:POSZ = 0.0, Float:distance = 50.0, usepos = 0)
{
	if(GetPVarType(playerid, "pAudioStream")) StopAudioStreamForPlayer(playerid);
	else SetPVarInt(playerid, "pAudioStream", 1);
	SendClientMessageEx(playerid, COLOR_GRAY, "%d %s %f %f %f %f %f %d", playerid, url, POSX, POSY, POSZ, distance, usepos);
    PlayAudioStreamForPlayer(playerid, url, POSX, POSY, POSZ, distance, usepos);
}

stock StopStream(playerid)
{
	DeletePVar(playerid, "pAudioStream");
    StopAudioStreamForPlayer(playerid);
}

stock phoneAnim(playerid, ttype)
{
	if(ttype == 1)
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
		SetPlayerAttachedObject(playerid, MAX_ATTACH+3, 330, 6);
	}
	else
	{
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
		RemovePlayerAttachedObject(playerid, MAX_ATTACH+3);
	}
	return 1;
}

stock AddAd(playerid, message[])
{
	for(new i; i<MAX_AD; i++)
	{
		if(ads_info[i][owner] == -1)
		{
			ads_info[i][owner] = playerid;
			format(ads_info[i][msg], 180, "%s", message);
			foreach(new p : Player)
			{
				if(!IsPlayerLoged(p)) continue;
				if(!InFactionId(p, SAN_FACTION)) continue;
				SCM(p, COLOR_MSGSERVER, ">{FFFFFF} На обработку пришло новое объявление! (/admenu)");
			}
			return 1;
		}
	}
	return 0;
}

stock PlayAudioStreamForPlayerEx(playerid, Float:Distancia, url[]) { 
    new Float:Pos[3];
    GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
    if(IsPlayerConnected(playerid)) {
        StopAudioStreamForPlayer(playerid);
        PlayAudioStreamForPlayer(playerid, url, Pos[0], Pos[1], Pos[2]);
		for(new p=0; p<GetMaxPlayers(); p++) 
		{
			if(!IsPlayerConnected(p)) continue;
			if(GetPlayerInterior(p) == GetPlayerInterior(p) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(p)) 
			{
				if(IsPlayerConnected(p) && (p != playerid) && IsPlayerStreamedIn(playerid,p)) 
				{
					if(IsPlayerInRangeOfPoint(p, Distancia, Pos[0], Pos[1], Pos[2])) 
					{
						StopAudioStreamForPlayer(p);
						PlayAudioStreamForPlayer(p, url, Pos[0], Pos[1], Pos[2]);
					}
				}
			}
		}
    }
    return true;
}

stock DestroyCheckpoint(playerid)
{
	if(GetPVarInt(playerid, "buy_purchase")) DeletePVar(playerid, "buy_purchase");
	if(GetPVarInt(playerid, "search_checkpoint")) DeletePVar(playerid, "search_checkpoint");
	DisablePlayerCheckpoint(playerid);
	return 1;
}

stock SirenOn(v)
{
	if(IsValidDynamicObject(veh_info[v][siren])) return 0;
	new floatxyz;
	switch(GetVehicleModel(v))
	{
		case 401: x=-0.004999, y=0.000000, z=0.799999;
		case 402: x=-0.004999, y=-0.519999, z=0.769999;
		case 404: x=-0.004999, y=-0.224999, z=0.934999;
		case 405: x=-0.004999, y=-0.224999, z=0.759999;
		case 410: x=0.010000, y=-0.224999, z=0.899999;
		case 409: x=0.000000, y=0.419999, z=0.824999;
		case 411: x=0.000000, y=-0.089999, z=0.719999;
		case 412: x=0.000000, y=-0.089999, z=0.714999;
		case 413: x=0.000000, y=0.704999, z=1.134999;
		case 415: x=0.000000, y=-0.259999, z=0.609999;
		case 418: x=0.000000, y=0.389999, z=1.039999;
		case 419: x=0.000000, y=-0.324999, z=0.694999;
		case 421: x=0.000000, y=-0.174999, z=0.729999;
		case 422: x=0.000000, y=0.044999, z=0.799999;
		case 424: x=0.000000, y=0.044999, z=0.864999;
		case 426: x=0.000000, y=-0.264999, z=0.849999;
		case 428: x=0.000000, y=0.754999, z=1.369998;
		case 431: x=0.020000, y=5.230072, z=2.115000;
		case 434: x=0.020000, y=-0.060000, z=0.729999;
		case 436: x=0.020000, y=-0.259999, z=0.844999;
		case 437: x=0.020000, y=4.630058, z=2.044999;
		case 442: x=0.020000, y=0.009999, z=0.889999;
		case 444: x=0.020000, y=0.234999, z=1.689998;
		case 445: x=0.020000, y=-0.254999, z=0.844999;
		case 451: x=-0.044999, y=-0.534999, z=0.589999;
		case 455: x=-0.044999, y=1.189998, z=1.664998;
		case 458: x=0.000000, y=0.000000, z=0.724999;
		case 459: x=0.000000, y=0.544999, z=1.114999;
		case 466: x=0.000000, y=-0.204999, z=0.849999;
		case 467: x=0.000000, y=-0.004999, z=0.829999;
		case 470: x=0.000000, y=-0.004999, z=1.089999;
		case 474: x=0.000000, y=-0.229999, z=0.794999;
		case 475: x=0.000000, y=-0.229999, z=0.704999;
		case 477: x=0.000000, y=-0.404999, z=0.734999;
		case 478: x=0.000000, y=0.125000, z=0.909999;
		case 479: x=0.000000, y=-0.269999, z=0.984999;
		case 480: x=0.000000, y=-1.024999, z=0.684999;
		case 482: x=0.000000, y=1.074999, z=0.904999;
		case 483: x=0.000000, y=1.499998, z=1.019999;
		case 489: x=0.000000, y=-0.114999, z=1.084999;
		case 490: x=0.000000, y=0.474999, z=1.089999;
		case 491: x=0.000000, y=-0.404999, z=0.679999;
		case 492: x=0.000000, y=-0.279999, z=0.859999;
		case 494: x=0.000000, y=-0.374999, z=0.739999;
		case 495: x=0.000000, y=0.050000, z=0.999999;
		case 496: x=0.000000, y=-0.444999, z=0.809999;
		case 498: x=0.000000, y=1.749998, z=2.014998;
		case 502: x=0.000000, y=-0.469999, z=0.779999;
		case 503: x=0.000000, y=-0.469999, z=0.764999;
		case 504: x=0.000000, y=0.065000, z=0.854999;
		case 505: x=0.000000, y=0.065000, z=1.084999;
		case 506: x=0.000000, y=-0.444999, z=0.574999;
		case 507: x=0.000000, y=-0.339999, z=0.779999;
		case 516: x=0.000000, y=-0.089999, z=0.864999;
		case 517: x=0.000000, y=-0.344999, z=0.839999;
		case 518: x=0.000000, y=-0.119999, z=0.689999;
		case 525: x=0.000000, y=-0.454999, z=1.444998;
		case 528: x=0.000000, y=0.050000, z=1.074999;
		case 527: x=0.000000, y=-0.054999, z=0.874999;
		case 526: x=0.000000, y=-0.234999, z=0.644999;
		case 529: x=0.000000, y=-0.234999, z=0.899999;
		case 534: x=0.000000, y=-0.029999, z=0.604999;
		case 535: x=0.000000, y=0.095000, z=0.804999;
		case 540: x=0.000000, y=-0.259999, z=0.699999;
		case 541: x=0.000000, y=-0.259999, z=0.619999;
		case 542: x=0.000000, y=-0.259999, z=0.829999;
		case 543: x=0.000000, y=0.110000, z=0.874999;
		case 544: x=0.000000, y=2.510010, z=1.459998;
		case 545: x=0.000000, y=-0.384999, z=0.744999;
		case 546: x=0.000000, y=-0.384999, z=0.834999;
		case 547: x=0.000000, y=-0.384999, z=0.889999;
		case 549: x=0.000000, y=0.035000, z=0.719999;
		case 550: x=0.000000, y=-0.089999, z=0.724999;
		case 551: x=0.000000, y=-0.344999, z=0.904999;
		case 552: x=0.000000, y=0.609999, z=1.314998;
		case 554: x=0.000000, y=0.025000, z=1.004999;
		case 556: x=0.000000, y=0.489999, z=1.679998;
		case 557: x=0.000000, y=0.010000, z=1.639998;
		case 558: x=0.000000, y=-0.354999, z=0.824999;
		case 559: x=0.000000, y=-0.354999, z=0.704999;
		case 562: x=0.000000, y=-0.354999, z=0.749999;
		case 561: x=0.000000, y=-0.129999, z=0.829999;
		case 560: x=0.000000, y=-0.074999, z=0.824999;
		case 565: x=0.000000, y=-0.414999, z=0.674999;
		case 566: x=0.000000, y=-0.169999, z=0.844999;
		case 576: x=0.000000, y=-0.169999, z=0.884999;
		case 579: x=0.000000, y=-0.369999, z=0.939999;
		case 580: x=0.000000, y=-0.059999, z=1.034999;
		case 585: x=0.000000, y=-0.259999, z=0.974999;
		case 587: x=0.000000, y=-0.599999, z=0.734999;
		case 589: x=0.000000, y=-0.194999, z=1.049999;
		case 596: x=0.000000, y=-0.264999, z=0.849999;
		case 597: x=0.000000, y=-0.264999, z=0.849999;
		case 598: x=0.000000, y=-0.264999, z=0.849999;
		case 601: x=0.000000, y=1.209999, z=1.499998;
		case 604: x=0.000000, y=-0.159999, z=0.864999;
		case 603: x=0.000000, y=-0.429999, z=0.644999;
		case 602: x=0.000000, y=-0.429999, z=0.679999;
		case 605: x=0.000000, y=0.015000, z=0.884999;
		default: return 0;
	}

	new Float:px, Float:py, Float:pz;
	GetVehiclePos(v, px,py,pz);
	veh_info[v][siren] = CreateDynamicObject(18646, px,py,pz+1, 0.0,0.0,0.0);
	
	AttachDynamicObjectToVehicle(veh_info[v][siren], v, x,y,z, 0.0,0.0,90.0);
	return 1;
}

stock useitem(playerid, itemslot)
{
	if(GetPVarInt(playerid, "_dev_")) {
		SendClientMessageEx(playerid, COLOR_GRAY, "%d: %d|%d", itemslot, character_info[playerid][inv][id][itemslot], character_info[playerid][inv][count][itemslot]);
	}
	if(itemslot == -1) return 0;
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(character_info[playerid][inv][count][i] < 1) {
  			character_info[playerid][inv][id][i] = 0;
	    	character_info[playerid][inv][count][i] = 0;
		}
	}
	
 	switch(character_info[playerid][inv][id][itemslot])
	{ // _
		case 1:
		{
		    ShowPlayerDialog(playerid, 110, DIALOG_STYLE_INPUT, "Аптечка", "Введите id игрока, которого хотите вылечить:\n{b1b1b1}(Вы можете использовать /heal [id] как альтернативный способ)", "Ввод", "Отмена");
		}
		case 2:		ShowPlayerDialog(playerid, 42, DIALOG_STYLE_INPUT, "Зарядить оружие", "Введите количество патронов:", "Далее", "Отмена");
		case 3:		usegun(playerid, 24, 3);
		case 4:     usegun(playerid, 31, 4);
		case 5:		usegun(playerid, 25, 5);
		case 6: 	usegun(playerid, 30, 6);
		case 7:		usegun(playerid, 28, 7);
		case 8: 	usegun(playerid, 32, 8);
		case 9: 	usegun(playerid, 29, 9);
		case 10: 	usegun(playerid, 26, 10);
		case 11: 	usegun(playerid, 23, 11);
		case 12: 	usegun(playerid, 22, 12);
		case 13: 	usegun(playerid, 34, 13);
		case 14: 	usegun(playerid, 33, 14);
		case 15:
		{
			if(character_info[playerid][phoneslot] != -1) return SCM(playerid, COLOR_GRAY, "У вас уже есть активированный телефон! Используйте /phoneinv чтобы убрать его в инвентарь.");
	    	new str[128];
		   	if(character_info[playerid][inv][id][itemslot] == 15)
		   	{
    			character_info[playerid][phoneslot] = character_info[playerid][inv][count][itemslot];
	    		format(str,sizeof(str), ">{FFFFFF} Телефон %d активирован.", character_info[playerid][phoneslot]);
	    		SCM(playerid, COLOR_MSGSERVER, str);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте /phone и /phoneinv для взаимодействия.");
				WireMsg(playerid, playerid, " включает телефон.");
	    		deleteitemslot(playerid, itemslot);
	    		LoadContacts(playerid, character_info[playerid][phoneslot]);
	    		return 1;
			}
		}
		case 20: 	usegun(playerid, 3, 20);
		case 21: 	usegun(playerid, 4, 21);
		case 22: 	usegun(playerid, 5 ,22);
		case 23: 	usegun(playerid, 6 ,23);
		case 24: 	usegun(playerid, 7 ,24);
		case 25: 	usegun(playerid, 8 ,25);

		case 26: 	usedrug(playerid, 26, 30, 10, 60*30);
		case 27: 	usedrug(playerid, 27, 50, 15, 60*120);
		case 28: 	usedrug(playerid, 28, 50, 1, 60*30);
		case 29: 	usedrug(playerid, 29, 20, 15, 60*60);
		case 30: 	usedrug(playerid, 30, 35, 15, 60*90);
		case 31: 	usedrug(playerid, 31, 30, 25, ADDICTION_MAX_TIME);
        case 32: 	usedrug(playerid, 32, 30, 10, 60*60);
        case 33: 	usedrug(playerid, 33, 30, 10, 60*60);

		case 34:	usegun(playerid, 24, 34);
		case 35:    usegun(playerid, 31, 35);
		case 36:	usegun(playerid, 25, 36);
		case 37: 	usegun(playerid, 30, 37);
		case 38:	usegun(playerid, 28, 38);
		case 39: 	usegun(playerid, 32, 39);
		case 40: 	usegun(playerid, 29, 40);
		case 41: 	usegun(playerid, 26, 41);
		case 42: 	usegun(playerid, 23, 42);
		case 43: 	usegun(playerid, 22, 43);
		case 44: 	usegun(playerid, 34, 44);
		case 45: 	usegun(playerid, 33, 45);
		case 46:
		{
			new newskin = character_info[playerid][inv][count][itemslot];
		    deleteitemslot(playerid, itemslot);
		    giveitem(playerid, 46, character_info[playerid][skin]);
		    character_info[playerid][skin] = newskin;
		    SetPlayerSkin(playerid, character_info[playerid][skin]);
		    return 1;
		}
		case 83:
		{
		    cmd::rinfo(playerid);
		    SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте команду /channel чтобы настроить канал, а команду /slot чтобы настроить подканал.");
		}
		case 84: usegun(playerid, 41, 84);
		case 89:
		{
			new i = GetPlayerVehicleID(playerid);
			if(i > 0)
			{
				if(veh_info[i][owner] < 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете угнать фракционный транспорт!");
				if(veh_info[i][engine]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот транспорт уже заведен!");
							
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы начали попытку завести транспорт с помощью отмычки!");
				SetPVarInt(playerid, "breaking_veh_id", i);
				SetPVarInt(playerid, "breaking_veh_processing", 100);
			}
			else ShowPlayerDialog(playerid, 101, DIALOG_STYLE_LIST, "Отмычка", "Взломать замок двери\nВзломать замок багажника", "Выбрать", "Отмена");
		}
		case 112:
		{
			if(GetPVarInt(playerid, "MASKED")) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже в маске!");
			if(deleteitem(playerid, 112, 1) != 1) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет маски!");
			MaskOn(playerid);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы надели маску.");
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте команду /unmask чтобы снять маску.");
		}
		case 113:
		{
			for(new i=1; i<MAX_VEHICLES; i++)
			{
				new Float:x, Float:y, Float:z;
				GetVehiclePos(i, xyz);
				if(GetPlayerVehicleID(playerid) == i || PlayerToPoint(3.0, playerid, xyz))
				{
					if(deleteitem(playerid, 113, 1) == 1)
					{
						veh_info[i][fuel] = 100;
						giveitem(playerid, 114);
						SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы заправили автомобиль!");
					}
					else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет канистры!");
					break;
				}
			}
		}
		case 115: usegun(playerid, 9, 115);
		case 116: usegun(playerid, 42, 116);
		case 118: usegun(playerid, 6, 118);
		case 119: usegun(playerid, 8, 119);
		case 130:
		{
			cmd_me(playerid, "выпивает виски.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 30.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
			deleteitem(playerid, 130, 1);
		}
		case 131:
		{
			cmd_me(playerid, "выпивает пиво.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_BEER);
			deleteitem(playerid, 131, 1);
		}
		case 132:
		{
			cmd_me(playerid, "выпивает вино.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 30.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
			deleteitem(playerid, 132, 1);
		}
		case 133:
		{
			cmd_me(playerid, "выпивает шампанское.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 20.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_WINE);
			deleteitem(playerid, 133, 1);
		}
		case 134:
		{
			cmd_me(playerid, "подкуривает сигарету.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_SMOKE_CIGGY);
			deleteitem(playerid, 134, 1);
		}
		case 135:
		{
			cmd_me(playerid, "выпивает газировку.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
			deleteitem(playerid, 135, 1);
		}
		case 136:
		{
			cmd_me(playerid, "выпивает стакан воды.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 5.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
			deleteitem(playerid, 136, 1);
		}
		case 137:
		{
			cmd_me(playerid, "выпил кофе.");
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			ApplyAnimation(playerid,"FOOD","EAT_Burger", 4.1,0,0,0,0,0);  
			deleteitem(playerid, 137, 1);
		}
		case 138:
		{
			cmd_me(playerid, "употребил пиццу.");
			ApplyAnimation(playerid,"FOOD","EAT_Burger", 4.1,0,0,0,0,0);  
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			deleteitem(playerid, 138, 1);
		}
		case 139:
		{
			cmd_me(playerid, "употребил бургер.");
			ApplyAnimation(playerid,"FOOD","EAT_Burger", 4.1,0,0,0,0,0);  
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			deleteitem(playerid, 139, 1);
		}
		case 140:
		{
			cmd_me(playerid, "употребил ролл.");
			ApplyAnimation(playerid,"FOOD","EAT_Burger", 4.1,0,0,0,0,0);  
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			deleteitem(playerid, 140, 1);
		}
		case 141:
		{
			cmd_me(playerid, "употребил салат.");
			ApplyAnimation(playerid,"FOOD","EAT_Burger", 4.1,0,0,0,0,0);  
			new Float:health;
			GetPlayerHealth(playerid, health);
			health += 15.0;
			if(health > 100.0) health = 100.0;
			SetPlayerHealth(playerid, health);
			deleteitem(playerid, 141, 1);
		}
		case 142:
		{
			new Float:BBCoord[4];
			new pName[MAX_PLAYER_NAME];
			format(pName, sizeof(pName), "%s", sendername(playerid, true));
			GetPlayerPos(playerid, BBCoord[0], BBCoord[1], BBCoord[2]);
			GetPlayerFacingAngle(playerid, BBCoord[3]);
			SetPVarFloat(playerid, "BBX", BBCoord[0]);
			SetPVarFloat(playerid, "BBY", BBCoord[1]);
			SetPVarFloat(playerid, "BBZ", BBCoord[2]);
			BBCoord[0] += (2 * floatsin(-BBCoord[3], degrees));
			BBCoord[1] += (2 * floatcos(-BBCoord[3], degrees));
			BBCoord[2] -= 1.0;
			//if(Boombox[playerid] == 0) return SCM(playerid, COLOR_WHITE, "You don't have a Boombox - Ask a Admin for one"); // Part of Variable
			if(GetPVarInt(playerid, "PlacedBB")) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже установили бумобкс.");
			foreach(new i : Player)
			{
				if(GetPVarType(i, "PlacedBB"))
				{
					if(IsPlayerInRangeOfPoint(playerid, 100.0, 1905.88, -1645.13, 13.24))
					{
						SendClientMessage(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете разместить здесь бумбокс!");
						return 1;
					}
					
					if(IsPlayerInRangeOfPoint(playerid, 30.0, GetPVarFloat(i, "BBX"), GetPVarFloat(i, "BBY"), GetPVarFloat(i, "BBZ")))
					{
						SendClientMessage(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете разместить здесь бумбокс, так как рядом уже установлен другой бумбокс!");
						return 1;
					}
				}
			}
			deleteitem(playerid, 142, 1);
			SYS_AME(playerid, "установил бумбокс");
			SetPVarInt(playerid, "PlacedBB", CreateDynamicObject(2226, BBCoord[0], BBCoord[1], BBCoord[2], 0.0, 0.0, 0.0, .worldid = GetPlayerVirtualWorld(playerid), .interiorid = GetPlayerInterior(playerid)));
			
			SetPVarInt(playerid, "BBArea", CreateDynamicSphere(BBCoord[0], BBCoord[1], BBCoord[2], 30.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid)));
			
			SetPVarInt(playerid, "BBInt", GetPlayerInterior(playerid));
			SetPVarInt(playerid, "BBVW", GetPlayerVirtualWorld(playerid));
			ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);
			ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0,0,0,0,0);
		}
		
		case 148: SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы можете использовать следующие команды: /pr lock, /pr furniture, /pr inv");
		case 149: SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы можете использовать следующие команды: /lock, /en");
		case 151:
		{
			new special, randitem, itemcount=1;
			switch(random(326))
			{
				case 0..25: randitem = 115;
				case 26..50: randitem = 116;
				case 51..100: randitem = 117;
				case 101..125: randitem = 118;
				case 126..150: randitem = 119;
				case 151..175: randitem = 89, itemcount = 20;
				
				case 176..185: randitem = 26, itemcount = random(10)+1;
				case 186..195: randitem = 27, itemcount = random(10)+1;
				case 196..205: randitem = 28, itemcount = random(10)+1;
				case 206..215: randitem = 29, itemcount = random(10)+1;
				case 216..225: randitem = 30, itemcount = random(10)+1;
				case 226..235: randitem = 31, itemcount = random(10)+1;
				case 236..245: randitem = 32, itemcount = random(10)+1;
				case 246..255: randitem = 33, itemcount = random(10)+1;
				
				case 256..265: randitem = 17;
				case 266..275: randitem = 19;
				
				case 276..280: special = 1;
				case 281..282: special = 2;
				case 283..300: randitem = 21;
				case 301..325: randitem = 22;
				default: SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Критическая ошибка.");
			}
			if(randitem != 0) 
			{
				new str[180];
				format(str, sizeof(str), ">{ffffff} Вы получили: %s [%d] из коробки с секретом!", senderitems(randitem), itemcount);
				giveitem(playerid, randitem, itemcount);
				SCM(playerid, COLOR_MSGSERVER, str);
			}
			else if(special != 0) 
			{
				switch(special)
				{
					case 1:
					{
						if(IsPremium(playerid, PREMIUM_BRONZE)) return useitem(playerid, 151);
						player_info[playerid][vip] = PREMIUM_BRONZE;
						player_info[playerid][vip_time] = gettime() + (60 * 60 * 24)*30;
						SCM(playerid, COLOR_MSGSERVER, ">{ffffff} Поздравляем! Вы получили BRONZE VIP!");
					}
					case 2:
					{
						if(IsPremium(playerid, PREMIUM_SILVER)) return useitem(playerid, 151);
						player_info[playerid][vip] = PREMIUM_SILVER;
						player_info[playerid][vip_time] = gettime() + (60 * 60 * 24)*30;
						SCM(playerid, COLOR_MSGSERVER, ">{ffffff} Поздравляем! Вы получили SILVER VIP!");
					}
				}
			}
			deleteitem(playerid, 151, 1);
			new slot = finditem(playerid, 151);
			if(slot >= 0) ShowPlayerDialog(playerid, 143, DIALOG_STYLE_MSGBOX, "Коробка с секретом", "У вас имеется еще коробка, вы хотите ее использовать сейчас?", "Да", "Нет");
		}
		case 153:
		{
			if(!isPlayerDriver(playerid)) return SCM(playerid, COLOR_GRAY, "Вы должны быть водителем!");
			new v = GetPlayerVehicleID(playerid);
			if(v < 1) return Sound_Fail(playerid);
			if(!TaxiOn(v)) return SCM(playerid, COLOR_GRAY, "На ваш автомобиль уже установлена шашка или ее нельзя установить!");
			Streamer_Update(playerid);
			deleteitem(playerid, 153,1);
			SCM(playerid, COLOR_GREEN, "____________________________________");
			SCM(playerid, COLOR_GREEN, "Вы установили шашку на этот автомобиль!");
			SCM(playerid, COLOR_GRAY, " ");
			SCM(playerid, COLOR_GRAY, "Подсказки: ");
			SCM(playerid, COLOR_PAPAYA, "* Теперь вы будете видеть вызовы такси.");
			SCM(playerid, COLOR_PAPAYA, "* Чтобы принять вызов используйте /accept [id]");
			SCM(playerid, COLOR_PAPAYA, "* Телефонный номер такси: 555");
			SCM(playerid, COLOR_GREEN, "____________________________________");
		}
		case 160: usegun(playerid, 43, 160);
		case 342: usesilencer(playerid);
		case 341: {
			if(character_info[playerid][pager] != -1) return SCM(playerid, COLOR_GRAY, "У вас уже есть пейджер! Используйте /pagerinv чтобы убрать его в инвентарь.");
	    	new str[128];
		   	if(character_info[playerid][inv][id][itemslot] == 341)
		   	{
    			character_info[playerid][pager] = character_info[playerid][inv][count][itemslot];
	    		format(str,sizeof(str), "Пейджеер %d активирован! Используйте /pager и /pagerinv для взаимодействия.", character_info[playerid][pager]);
	    		SCM(playerid, COLOR_RED, str);
	    		deleteitemslot(playerid, itemslot);
	    		LoadPager(playerid, character_info[playerid][pager]);
	    		return 1;
			}
		
		}
		default: SCM(playerid, COLOR_GRAY, "Этот предмет нельзя использовать таким образом!");
	}
	return 1;
}

stock create_phone(playerid)
{
    new qu[128];
	new randphone = 100000 + random(99999);
    format(qu, sizeof(qu), "SELECT `phone` FROM  `phone` WHERE phone=%d", randphone);
    mysql_function_query(dbHandle, qu, true, "OnCreatePhone", "ii", playerid, randphone);
}
stock create_pager(playerid)
{
    new qu[128];
	new randphone = 100000 + random(99999);
    format(qu, sizeof(qu), "SELECT `id` FROM  `pager` WHERE id=%d", randphone);
    mysql_function_query(dbHandle, qu, true, "OnCreatePager", "ii", playerid, randphone);
}

stock deleteitemslot(playerid, slot)
{
	if(character_info[playerid][inv][count][slot] <= 0 || character_info[playerid][inv][id][slot] <= 0) return 0;
	character_info[playerid][inv][count][slot] = 0;
	character_info[playerid][inv][id][slot] = 0;
	return 1;
}
stock deleteitemslotpr(li, slot)
{
	prop_info[li][inv][count][slot] = 0;
	prop_info[li][inv][id][slot] = 0;
	return 1;
}
stock deleteitemslotveh(v, slot)
{
	veh_info[v][inv][count][slot] = 0;
	veh_info[v][inv][id][slot] = 0;
	return 1;
}

stock deleteitem(playerid, itemid, mycount)
{
	if(itemid == 0) return 0;
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
 		if(itemid > MAX_ITEMS-1) break;
 		new temp = checkitem(playerid, itemid);
 		if(mycount < 1) return 0;
 		if(temp > -1)
 		{
 			if(character_info[playerid][inv][count][temp] < mycount)
				return 0;
			else
			{
			    if(!Items[character_info[playerid][inv][id][temp]][compound]) mycount = character_info[playerid][inv][count][temp];
			    character_info[playerid][inv][count][temp] -= mycount;
			    if(character_info[playerid][inv][count][temp] < 0)
			    {
			        character_info[playerid][inv][count][temp] = 0;
			        character_info[playerid][inv][id][temp] = 0;
			    }
				return 1;
			}
 		}
 		else return 0;
	}
	return 1;
}

stock deleteitemveh(v, itemid, mycount)
{
	if(itemid == 0) return 0;
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
 		if(itemid > MAX_ITEMS-1) break;
 		new temp = checkitemveh(v, itemid);
 		if(mycount < 1) return 0;
 		if(temp > -1)
 		{
 			if(veh_info[v][inv][count][temp] < mycount)
				return 0;
			else
			{
			    if(!Items[veh_info[v][inv][id][temp]][compound]) mycount = veh_info[v][inv][count][temp];
			    veh_info[v][inv][count][temp] -= mycount;
			    if(veh_info[v][inv][count][temp] < 0)
			    {
			        veh_info[v][inv][count][temp] = 0;
			        veh_info[v][inv][id][temp] = 0;
			    }
				return 1;
			}
 		}
 		else return 0;
	}
	return 1;
}

stock deleteitempr(propid, itemid, mycount)
{
	if(itemid == 0) return 0;
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
 		if(itemid > MAX_ITEMS-1) break;
 		new temp = checkitempr(propid, itemid);
 		if(mycount < 1) return 0;
 		if(temp > -1)
 		{
 			if(prop_info[propid][inv][count][temp] < mycount)
				return 0;
			else
			{
			    if(!Items[prop_info[propid][inv][id][temp]][compound]) mycount = prop_info[propid][inv][count][temp];
			    prop_info[propid][inv][count][temp] -= mycount;
			    if(prop_info[propid][inv][count][temp] < 0)
			    {
			        prop_info[propid][inv][count][temp] = 0;
			        prop_info[propid][inv][id][temp] = 0;
			    }
				return 1;
			}
 		}
 		else return 0;
	}
	return 1;
}

stock giveitem(playerid, itemid, mycount=1)
{
	/*
	for(new i = 0; i<sizeof(PoliceAttaches); i++) 
		if(PoliceAttaches[i] == itemid) 
			return 1;
		
	for(new i = 0; i<sizeof(LSFDAttaches); i++) 
		if(LSFDAttaches[i] == itemid) 
			return 1;
	*/
	
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(itemid > MAX_ITEMS-1 || itemid < 1) 
			return SendClientMessage(playerid, -1, "Ошибка 1511");
	    
		new temp = checkitem(playerid, itemid);
	    if(temp > -1 && Items[itemid][compound])
	    {
	        character_info[playerid][inv][count][temp] += mycount;
	        return 1;
	    }
	    else if(character_info[playerid][inv][id][i] == 0)
	    {
	        character_info[playerid][inv][id][i] = itemid;
	        character_info[playerid][inv][count][i] = mycount;
	        return 1;
	    }
	    else if(i == MAX_INV_SLOTS-1)
	    {
	        SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно места в инвентаре!");
	        return 0;
     	}
	}
	return 1;
}

stock giveitemveh(vehid, itemid, mycount=1)
{
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(itemid > MAX_ITEMS-1 || itemid < 1) return 0;
	    new temp = checkitemveh(vehid, itemid);
		if(mycount < 1) return 0;
	    else if(temp > -1 && Items[itemid][compound])
	    {
	        veh_info[vehid][inv][count][temp] += mycount;
	        return 1;
	    }
	    else if(veh_info[vehid][inv][id][i] == 0)
	    {
	        veh_info[vehid][inv][id][i] = itemid;
	        veh_info[vehid][inv][count][i] = mycount;
	        return 1;
	    }
	    else if(i == MAX_INV_SLOTS-1)
	    {
	        return 0;
     	}
	}
	return 1;
}

stock giveitempr(propid, itemid, mycount=1)
{
	//printf("[temp debug]: giveitempr(%d, %d, %d)", propid, itemid, mycount);
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(itemid > MAX_ITEMS-1 || itemid < 1) return 0;
	    new temp = checkitempr(propid, itemid);
		if(mycount < 1) return 0;
	    else if(temp > -1 && Items[itemid][compound])
	    {
	        prop_info[propid][inv][count][temp] += mycount;
	        //printf("[temp debug]: giveitempr returning 1, 1 result");
	        return 1;
	    }
	    else if(prop_info[propid][inv][id][i] == 0)
	    {
	        prop_info[propid][inv][id][i] = itemid;
	        prop_info[propid][inv][count][i] = mycount;
	        //printf("[temp debug]: giveitempr returning 1, 2 result");
	        return 1;
	    }
	    else if(i == MAX_INV_SLOTS-1)
	    {
	    	//printf("[temp debug]: giveitempr returning 0, 1 result");
	        return 0;
     	}
	}
	return 1;
}

stock ReconnectMYSQL()
{
	if(mysql_ping(dbHandle) != -1 && dbHandle != 0) 
		return 1;
	
	if(dbHandle != 0)
	{
		mysql_close(dbHandle);
		printf("[DB] MYSQL CONNECTION CLOSED!");
	}

	
	new file = ini_openFile ( "config.ini" );
	new MYSQL_HOST[17], MYSQL_USER[32], MYSQL_BASE[32], MYSQL_PASS[32];

	ini_getString(file, "mysql_host", MYSQL_HOST);
	ini_getString(file, "mysql_user", MYSQL_USER);
	ini_getString(file, "mysql_pass", MYSQL_PASS);
	ini_getString(file, "mysql_base", MYSQL_BASE);
	ini_closeFile(file);
	
	dbHandle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_BASE, MYSQL_PASS);
	printf("[DB] MYSQL CONNECTION OPENED!", dbHandle);
	mysql_debug(MYSQL_DEBUG);
	mysql_function_query( dbHandle, "SET NAMES cp1251", false, "", "" ) ;
	return 1;
}
stock reg_mysql_connect()
{
	printf("[DB] FIRST START MYSQL...", dbHandle);
	ReconnectMYSQL();	
	switch(mysql_ping(dbHandle))
	{
	    case 1: {
			print("mysql connected: [+]");
			SendRconCommand("hostname "SERVER_NAME_SECOND SERVER_NAME_PREFIX);
   			new charset[20]; mysql_get_charset(charset);
			printf(" Кодировка mysql: %s\n",charset);
			
			/*new page = 1;
			new qu[256], playerid=0;
			format(qu, sizeof(qu), "SELECT `id`, `desc`, `violation` FROM  `apb` ORDER BY  `apb`.`id` DESC LIMIT %d,15", (page-1)*15);
			mysql_function_query(dbHandle, qu, true, "OnAPBList", "ii", playerid, page);*/
		}
	    case -1:
		{
			print("mysql connected: [-]");
			SendRconCommand("hostname "SERVER_NAME_SECOND" | safety shutdown!");
			new rand_pass[64];
			format(rand_pass, sizeof(rand_pass), "password %d%d%d%d%d%d%d", random(20),random(20),random(20),random(20),random(20),random(20),random(20));
			SendRconCommand(rand_pass);
		}
	}
}


stock sendername(playerid, bool:IC=false)
{
	new str[MAX_PLAYER_NAME];
	GetPlayerName(playerid, str, sizeof(str));
	if(IC)
	{
		new chname[MAX_PLAYER_NAME], chsurname[MAX_PLAYER_NAME];
		sscanf(str, "p<_>s[24]s[24]", chname, chsurname);
		format(str, sizeof(str), "%s %s", chname, chsurname);
	}
	return str;
}
stock checkitem(playerid, itemid)
{
    for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(character_info[playerid][inv][count][i] < 1)
		{
  			character_info[playerid][inv][id][i] = 0;
	    	character_info[playerid][inv][count][i] = 0;
		}
		if(character_info[playerid][inv][id][i] == itemid)
	        return i;
	}
	return -1;
}

stock checkitempr(propid, itemid)
{
    for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(prop_info[propid][inv][count][i] < 1)
		{
  			prop_info[propid][inv][id][i] = 0;
	    	prop_info[propid][inv][count][i] = 0;
		}

	    if(prop_info[propid][inv][id][i] == itemid)
	        return i;
		else
		    continue;
	}
	return -1;
}
stock checkitemveh(v, itemid)
{
    for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(veh_info[v][inv][count][i] < 1)
		{
  			veh_info[v][inv][id][i] = 0;
	    	veh_info[v][inv][count][i] = 0;
		}

	    if(veh_info[v][inv][id][i] == itemid)
	        return i;
		else
		    continue;
	}
	return -1;
}

stock checkcountitem(playerid, itemid)
{
    for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(character_info[playerid][inv][count][i] < 1)
		{
  			character_info[playerid][inv][id][i] = 0;
	    	character_info[playerid][inv][count][i] = 0;
		}

	    if(character_info[playerid][inv][id][i] == itemid)
	        return character_info[playerid][inv][count][i];
		else
		    continue;
	}
	return -1;
}
stock countitem(playerid, itemid)
{
    for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    if(character_info[playerid][inv][id][i] == itemid)
		{
			return character_info[playerid][inv][count][i];
		}
		else
		    continue;
	}
	return 0;
}

stock finditem(playerid, itemid, mycount=1)
{
    for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
		if(character_info[playerid][inv][count][i] < 1)
		{
  			character_info[playerid][inv][id][i] = 0;
	    	character_info[playerid][inv][count][i] = 0;
		}
	    if(character_info[playerid][inv][id][i] == itemid && character_info[playerid][inv][count][i] >= mycount)
		{
			return i;
		}
		else
		    continue;
	}
	return -1;
}

stock dialog_data_update(playerid)
{
    for(new i=0; i<10; i++)
	    dialog_data[playerid][i] = -1;
}
stock takemoney(playerid, countmoney, where[], bool:inbank=false)
{
    if(countmoney < 1 || countmoney > 1000000) return 0;
	
	if(!inbank)
	{
		if(character_info[playerid][money] < countmoney) return -1;
		else character_info[playerid][money] -= countmoney;
	}
	else 
	{
		if(character_info[playerid][bank] < countmoney) return -1;
		else character_info[playerid][bank] -= countmoney;
	}
	new qu[254];
	format(qu, sizeof(qu), "INSERT INTO `money_logs`(`userid`, `characterid`, `count`, `type`, `reason`) VALUES (%d, %d, %d, %d, '%s')",
	player_info[playerid][id], character_info[playerid][id],
	countmoney, 0, where);
	mysql_function_query(dbHandle, qu, false, "", "");
	if(!inbank)
	{
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, character_info[playerid][money]);
		new str[16];
		format(str, sizeof(str), "~r~-$%d", countmoney);
		GameTextForPlayer(playerid, str, 1000, 1);
	}
	return 1;
}
stock givemoney(playerid, countmoney, from[], bool:inbank=false)
{
	if(countmoney < 1 || countmoney > 1000000) 
		return 0;

	if(!inbank) 
		character_info[playerid][money] += countmoney;
	else 
		character_info[playerid][bank] += countmoney;
    
	new qu[254];
	format(qu, sizeof(qu), "INSERT INTO `money_logs`(`userid`, `characterid`, `count`, `type`, `reason`) VALUES (%d, %d, %d, %d, '%s')",
	player_info[playerid][id], character_info[playerid][id],
	countmoney, 1, from);
	mysql_function_query(dbHandle, qu, false, "", "");
	if(!inbank)
	{
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, character_info[playerid][money]);
		new str[16];
		format(str, sizeof(str), "~g~+$%d", countmoney);
		GameTextForPlayer(playerid, str, 1000, 1);
	}
	return 1;
}

stock transfermoney(playerid, giveplayerid, countmoney, where[], from[])
{

	if(takemoney(playerid, countmoney, where) > 0) {
		givemoney(giveplayerid, countmoney, from);
		return 1;
	}
	else
	    return 0;
}


stock save_prop()
{
	for(new i=0; i<MAX_PROP; i++)
	{
	    if(prop_info[i][id] > 0)
		{
			new qu[546], str_inv[128];
			for(new it=0; it<MAX_INV_SLOTS; it++)
			{
				if(it == MAX_INV_SLOTS-1) 
				format(str_inv, sizeof(str_inv), "%s%d:%d",str_inv, prop_info[i][inv][id][it],prop_info[i][inv][count][it]);
				else 
				format(str_inv, sizeof(str_inv), "%s%d:%d|",str_inv, prop_info[i][inv][id][it],prop_info[i][inv][count][it]);
			}
			
			new escape[140*2];
			mysql_real_escape_string(prop_info[i][Name], escape); 
			format(qu, sizeof(qu), "UPDATE `property` SET `name`='%s', `owner`=%d, `price`=%d, `lock`=%d, `money`=%d, `inv`='%s', `serverint`=%d WHERE `id`=%d",
			escape, prop_info[i][owner],prop_info[i][price],prop_info[i][lock],prop_info[i][money], str_inv, prop_info[i][serverint], GetGlobalIdProp(i)
			);
			mysql_function_query(dbHandle, qu, false, "", "");
		}
	}
	mysql_function_query(dbHandle, "update property AS pr inner join (select max(unix_timestamp(al.date)) AS maxdate, characters.id, characters.userid from auth_log al join characters on al.characterid=characters.id group by characters.id ) t1 on t1.id=pr.owner set pr.owner = 0 where t1.maxdate+3600*24*7 < unix_timestamp(now()) or t1.userid < 0", false, "", "");
	return 1;
}

stock save_veh()
{
	for(new v; v<MAX_VEHICLES; v++) 
		DestroyVehicleEx(v);
}


GetVehicleModelByName(const vname[])
{
	if (IsNumeric(vname) && (strval(vname) >= 400 && strval(vname) <= 611))
	    return strval(vname);

	for (new i = 0; i < sizeof(g_arrVehicleNames); i ++)
	{
	    if (strfind(g_arrVehicleNames[i], vname, true) != -1)
	    {
	        return i + 400;
		}
	}
	return 0;
}

IsNumeric(const str[])
{
	for (new i = 0, l = strlen(str); i != l; i ++)
	{
	    if (i == 0 && str[0] == '-')
			continue;

	    else if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

stock searchitemcount(playerid, itemid, mycount)
{
	for(new i; i<MAX_INV_SLOTS; i++)
	{
		if(character_info[playerid][inv][id][i] == itemid && character_info[playerid][inv][count][i] == mycount) return 1;
	}
	return 0;
}
stock NeighborProp(playerid)
{	
	// 148
	if(searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200) return GetLocalIdProp(character_info[playerid][prop]);
	
	for(new i; i<MAX_PROP; i++)
	{
		if(PlayerToPoint(1.5, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid] && searchitemcount(playerid, 148, prop_info[i][id]))
			return i;
	}
	return -1;
}
stock OwnerProp(playerid)
{
	if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner])
		return GetLocalIdProp(character_info[playerid][prop]);
	else
	{
		for(new i = 0; i<MAX_PROP; i++)
		{
			if(PlayerToPoint(1.5, playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == prop_info[i][vworld] && GetPlayerInterior(playerid) == prop_info[i][intid] && prop_info[i][owner] == character_info[playerid][id])
				return i;
		}
		return -1;
	}
}


stock gotoInt(playerid, myint, world)
{
	SetPlayerPos(playerid, Interiors[myint][posX], Interiors[myint][posY], Interiors[myint][posZ]+0.2);
	SetPlayerVw(playerid, world);
	SetPlayerInt(playerid, Interiors[myint][Interior]);
	if(world > 200) character_info[playerid][prop] = world-200;
    Freeze(playerid, 2000+(GetPlayerPing(playerid)*20));
	

	return 1;
}
stock gotoProp(playerid, propid)
{
    SetPlayerPos(playerid, prop_info[propid][posX], prop_info[propid][posY], prop_info[propid][posZ]+0.1);
    SetPlayerInt(playerid, prop_info[propid][intid]);
	SetPlayerVw(playerid, prop_info[propid][vworld]);
    character_info[playerid][prop] = 0;
	Freeze(playerid, 2000);
	return 1;
}
stock GetLocalIdProp(GlobalID)
{
	for(new i = 0; i<MAX_PROP; i++)
	{
	    if(prop_info[i][id] == GlobalID)
	        return i;
	}
	return -1;
}
stock GetGlobalIdProp(LocalID)
{
	return prop_info[LocalID][id];
}
stock wepinv(playerid)
{
	if(player_info[playerid][perm] == 1)
	{
	    player_info[playerid][perm] = false;
		ResetPlayerWeapons(playerid);
		
		
		if(character_info[playerid][gun] != 0)
		{
			if(GetPlayerState(playerid) == 2 || GetPlayerState(playerid) == 3)
			{
				SetPVarInt(playerid, "invwep_fix_car", GetPlayerVehicleID(playerid));
				SetPVarInt(playerid, "invwep_fix_seat", GetPlayerVehicleSeat(playerid));
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x,y,z);
				SetPlayerPos(playerid, x,y,z+0.5);
			}
		}
		if(character_info[playerid][ammo] > 0)
		{
		 	if(character_info[playerid][gun] == 24) giveitem(playerid, 3, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 31) giveitem(playerid, 4, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 25) giveitem(playerid, 5, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 30) giveitem(playerid, 6, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 28) giveitem(playerid, 7, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 32) giveitem(playerid, 8, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 29) giveitem(playerid, 9, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 26) giveitem(playerid, 10, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 23) giveitem(playerid, 11, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 22) giveitem(playerid, 12, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 34) giveitem(playerid, 13, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 33) giveitem(playerid, 14, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 41) giveitem(playerid, 84, character_info[playerid][ammo]);
        }
		else
		{
		    if(character_info[playerid][gun] == 24) giveitem(playerid, 34, 1);
			if(character_info[playerid][gun] == 31) giveitem(playerid, 35, 1);
			if(character_info[playerid][gun] == 25) giveitem(playerid, 36, 1);
			if(character_info[playerid][gun] == 30) giveitem(playerid, 37, 1);
			if(character_info[playerid][gun] == 28) giveitem(playerid, 38, 1);
			if(character_info[playerid][gun] == 32) giveitem(playerid, 39, 1);
			if(character_info[playerid][gun] == 29) giveitem(playerid, 40, 1);
			if(character_info[playerid][gun] == 26) giveitem(playerid, 41, 1);
	        if(character_info[playerid][gun] == 23) giveitem(playerid, 42, 1);
	        if(character_info[playerid][gun] == 22) giveitem(playerid, 43, 1);
	        if(character_info[playerid][gun] == 34) giveitem(playerid, 44, 1);
	        if(character_info[playerid][gun] == 33) giveitem(playerid, 45, 1);
			if(character_info[playerid][gun] == 41) giveitem(playerid, 85, 1);
		}
		
        if(character_info[playerid][gun] == 3) giveitem(playerid, 20, 1);
        if(character_info[playerid][gun] == 4) giveitem(playerid, 21, 1);
        if(character_info[playerid][gun] == 5) giveitem(playerid, 22, 1);
        if(character_info[playerid][gun] == 7) giveitem(playerid, 24, 1);
		
		if(character_info[playerid][gun] == 9) 	giveitem(playerid, 115);
		if(character_info[playerid][gun] == 42)	giveitem(playerid, 116); 
		if(character_info[playerid][gun] == 6)	giveitem(playerid, 118);
		if(character_info[playerid][gun] == 8) 	giveitem(playerid, 119); 
		if(character_info[playerid][gun] == 43) giveitem(playerid, 160);
		
		SetTimerEx("invwep_fix",500,false, "i", playerid);
	}
	return 1;
}
stock invsilencer(playerid)
{
	if(player_info[playerid][perm] == 1)
	{
	    player_info[playerid][perm] = false;
		
		if(character_info[playerid][silencer] == 1)
		{
			character_info[playerid][silencer] = 0;
			ResetPlayerWeapons(playerid);
			GivePlayerWeapon(playerid, character_info[playerid][gun],character_info[playerid][ammo]);
		}
		else if(character_info[playerid][silencer] == 0)
		{
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} На вашем оружии нет глушителя.");
			return 1;
		}
		SetTimerEx("invwep_fix",500,false, "i", playerid);
	}
	return 1;
}
stock AdminMessage(string[])
{
	new temp[128];
	Log_Write("logs/admins_log.txt", "[%s] [A] %s", ReturnDate(), string);
	//printf("[A] %s", string);
	format(temp, sizeof(temp), ">{FFFFFF} %s", string);
	foreach(new p : Player)
	{
		if(IsAdmin(p, 1, true)) continue;
		SendClientMessage(p, COLOR_MSGADMIN, temp);
	}
}

stock AntiCheat(playerid, string[], code=-1, bool:kick=true)
{
	new temp[128];
	Log_Write("logs/anticheat_log.txt", "[%s] [A] %s %s", ReturnDate(), sendername(playerid), string);
	//printf("[A] %s[%d] %s",sendername(playerid), playerid, string);
	foreach(new p : Player)
	{
		if(!IsAdmin(p, 1, true))
		{
			format(temp, sizeof(temp), ">{FFFFFF} %s(%s) %s (#%d)", CharacterAndPlayerName(playerid), string, code);
			SendClientMessage(p, COLOR_RED, temp);
		}
		if(p == playerid && kick)
		{
		    format(temp, sizeof(temp), ">{FFFFFF} Вы были кикнуты с кодом #%d", code);
		    SCM(playerid, COLOR_RED, temp);
		    KickEx(playerid);
		}
	}
	return 1;
}

stock AdminLog(string[])
{
	new temp[180];
	Log_Write("logs/full_admins_log.txt", "[%s] [A] %s", ReturnDate(), string);
	//printf("[A] %s", string);
	format(temp, sizeof(temp), ">{FFFFFF} %s", string);
	foreach(new p : Player)
	{
		if(IsAdmin(p, 1, true)) continue;
		SendClientMessage(p, COLOR_MSGADMIN, temp);
	}
}

stock PlayerLog(playerid, string[])
{
	new temp[180];
	format(temp, sizeof(temp), ">{FFFFFF} %s(%d) %s", character_info[playerid][name], playerid, string);
	foreach(new p : Player)
	{
		if(IsAdmin(p, 1, true)) continue;
		SendClientMessage(p, COLOR_MSGADMIN, temp);
	}
}

stock IsAdmin(playerid, level=1, bool:_silend_=false, bool:_aduty_=true)
{
	if(IsAduty(playerid) && _aduty_)
	{
		for(new i; i<sizeof(SuperAdmins); i++) 
			if(player_info[playerid][id] == SuperAdmins[i] && IsPlayerLoged(playerid)) 
				return 0;
	}
	if(player_info[playerid][admin] < level)
	{
	    if(!_silend_ && player_info[playerid][admin] == 0) 
			CMDError(playerid);
		else if(!_silend_) 
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточный уровень администратора чтобы использовать эту команду!");
		return 1;
 	}
	else if(IsAduty(playerid) && _aduty_) 
		return 0;
	else if(!_aduty_) 
		return 0;
	else 
		return 1;
}

stock ProxDetector(Float:radius, WorldID, playerid, string[], string2[], col1, col2, col3, col4, col5)
{
	new tempworld;
	new Float:posx, Float:posy, Float:posz;
	new Float:oldposx, Float:oldposy, Float:oldposz;
	new Float:tempposx, Float:tempposy, Float:tempposz;
	GetPlayerPos(playerid, oldposx, oldposy, oldposz);
	foreach(new p : Player)
	{
		if( IsPlayerConnected( p ) )
		{
			GetPlayerPos( p, posx, posy, posz );
			tempworld = GetPlayerVirtualWorld( p );
			tempposx = (oldposx -posx);
			tempposy = (oldposy -posy);
			tempposz = (oldposz -posz);
			if (((tempposx < radius/16) && (tempposx > -radius/16)) && ((tempposy < radius/16) && (tempposy > -radius/16)) && ((tempposz < radius/16) && (tempposz > -radius/16)) && tempworld == WorldID)
			{
				SendClientMessage( p, col1, string );
			}
			else if (((tempposx < radius/8) && (tempposx > -radius/8)) && ((tempposy < radius/8) && (tempposy > -radius/8)) && ((tempposz < radius/8) && (tempposz > -radius/8)) && tempworld == WorldID)
			{
				SendClientMessage( p, col2, string );
			}
			else if (((tempposx < radius/4) && (tempposx > -radius/4)) && ((tempposy < radius/4) && (tempposy > -radius/4)) && ((tempposz < radius/4) && (tempposz > -radius/4)) && tempworld == WorldID)
			{
				SendClientMessage( p, col3, string );
			}
			else if (((tempposx < radius/2) && (tempposx > -radius/2)) && ((tempposy < radius/2) && (tempposy > -radius/2)) && ((tempposz < radius/2) && (tempposz > -radius/2)) && tempworld == WorldID)
			{
				SendClientMessage( p, col4, string );
			}
			else if (((tempposx < radius) && (tempposx > -radius)) && ((tempposy < radius) && (tempposy > -radius)) && ((tempposz < radius) && (tempposz > -radius)) && tempworld == WorldID)
			{
				SendClientMessage( p, col5, string );
			}
			else if (((tempposx < radius*3/2) && (tempposx > -radius*3/2)) && ((tempposy < radius*3/2) && (tempposy > -radius*3/2)) && ((tempposz < radius*3/2) && (tempposz > -radius*3/2)) && tempworld == WorldID)
			{
				SendClientMessage( p, col5, string2 );
			}
		}
	}
	return 1;
}

stock CreateVehicleEx(carid, Float:X, Float:Y, Float:Z, Float:Angle, _vworld_, col1, col2, Float:vfuel, bool:vlock, bool:vengine, bool:vwindows, bool:vlights, vid=-1, vowner=0, vnumber[]="0")
{
	for(new i; i<MAX_VEHICLES; i++) 
		if(veh_info[i][id] == vid && vid != -1) 
			return 0;
		
    new v = CreateVehicle(carid, X, Y, Z, Angle, col1, col2, -1, (vowner == -1 || vowner == -74 || vowner == -75) ? 1 : 0);
	format(veh_info[v][number], 11, "%s", vnumber);
	veh_info[v][id] = vid;
	
	if(strlen(vnumber) < 5) 
		GenerateCarNumber(v);
	
	veh_info[v][VW] = _vworld_;
	SetVehicleVirtualWorld(v, veh_info[v][VW]);
    veh_info[v][lock] = vlock;
	veh_info[v][vcolor1] = col1;
	veh_info[v][vcolor2] = col2;
	if(IsBike(v)) 
		veh_info[v][engine] = true;
	else 
		veh_info[v][engine] = vengine;
    
	veh_info[v][window_1] = vwindows;
	veh_info[v][window_2] = vwindows;
	veh_info[v][window_3] = vwindows;
	veh_info[v][window_4] = vwindows;
    veh_info[v][lights] = vlights;
    veh_info[v][owner] = vowner;
	if(veh_info[v][owner] >= 0) 
		veh_info[v][fuel] = vfuel;
	else 
		veh_info[v][fuel] = 100;
    
	veh_info[v][boonet] = false;
    veh_info[v][boot] = false;
    veh_info[v][posX] = X+3;
	veh_info[v][posY] = Y+3;
	veh_info[v][posZ] = Z+1;
	veh_info[v][destroy_time] = 0;
	veh_info[v][filling] = 0;
	if(IsValidDynamicObject(veh_info[v][taxi])) 
		DestroyDynamicObject(veh_info[v][taxi]);
	
	veh_info[v][taxi] = 0;
	//veh_info[v][timerid] = SetTimerEx("VehTimer",2500,true, "i", v);
	//printf("Created vehicle. ID: %d, OWNER: %d. %f %f %f (%d)", v, veh_info[v][owner], X, Y, Z, veh_info[v][VW]);
    UpdateVehParams(v);
    return v;
}
stock UpdateVehParams(v)
{	
    SetVehicleParamsEx(v, veh_info[v][engine], veh_info[v][lights], veh_info[v][alarm], veh_info[v][lock], veh_info[v][boonet],veh_info[v][boot],0);
	SetVehicleParamsCarWindows(v, veh_info[v][window_1], veh_info[v][window_2], veh_info[v][window_3], veh_info[v][window_4]);
	SetVehicleNumberPlate(v, veh_info[v][number]);
    return 1;
}

stock SpeedVehicle(playerid)
{
    new Float:ST[4];
    if(IsPlayerInAnyVehicle(playerid))
        GetVehicleVelocity(GetPlayerVehicleID(playerid),ST[0],ST[1],ST[2]);
        else GetPlayerVelocity(playerid,ST[0],ST[1],ST[2]);
    ST[3] = floatsqroot(floatpower(floatabs(ST[0]), 2.0) + floatpower(floatabs(ST[1]), 2.0) + floatpower(floatabs(ST[2]), 2.0)) * 100.3;
    return floatround(ST[3]);
}
stock gmx(time)
{
	
	new str[128];
	restart = time;
	format(str, sizeof(str), ">{ffffff} Администратор стартовал рестарт. (До рестарта %d секунд)", restart);
	SendClientMessageToAll(COLOR_PAPAYA, str);
	SetTimer("gmx_timer", 1000, true);
}

//-----------------------------

stock up_player(playerid)
{
    new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, xyz);
	SetPlayerPos(playerid, x,y,z+2);
}
stock down_player(playerid)
{
    new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid, xyz);
	SetPlayerPos(playerid, x,y,z-2);
}

stock phone_menu(playerid, itemid)
{
	new str[16];
    format(str, sizeof(str), "Телефон - %d", character_info[playerid][inv][count][itemid]);
    SPD(playerid, 19, DIALOG_STYLE_LIST, str, "Контакты\nПозвонить\nОтправить СМС", "Выбрать", "Закрыть");
}

stock furniture_search(modelid)
{
	for(new i; i<sizeof(_furniture); i++)
	{
	    if(_furniture[i][id] == modelid)
		return i;
	}
	return -1;
}
stock PlayerDataUpdate(playerid)
{
    TogglePlayerControllable(playerid, 1);
	player_info[playerid][loged] = 0;
	player_info[playerid][fail_input_password] = 0;
	player_info[playerid][id] = -1;
	player_info[playerid][login] = 0;
	player_info[playerid][admin] = 0;
	player_info[playerid][inv_selected] = -1;
	player_info[playerid][perm] = 1;
	player_info[playerid][aduty] = false;

	attachStatus[playerid] = 0;
	character_info[playerid][lock] = 0;
	character_info[playerid][spawned] = 0;
	character_info[playerid][skin] = 0;
	character_info[playerid][money] = 0;
	character_info[playerid][hospital] = -1;
	character_info[playerid][newlife] = -1;
	character_info[playerid][id] = 0;
	character_info[playerid][name] = 0;
	character_info[playerid][faction] = 0;
	character_info[playerid][rank] = 0;
	character_info[playerid][posX] = 0;
	character_info[playerid][posY] = 0;
	character_info[playerid][posZ] = 0;
	character_info[playerid][VW] = 0;
	character_info[playerid][Interior] = 0;
	character_info[playerid][gun] = 0;
	character_info[playerid][ammo] = 0;
	character_info[playerid][drunk_time] = 0;
 	set_wound(playerid, 0);
	character_info[playerid][accept_death] = 0;
	character_info[playerid][accept_death_timer] = 0;
	character_info[playerid][prop] = 0;
	character_info[playerid][editobject] = 0;
	character_info[playerid][type_editobj] = 0;
	character_info[playerid][phoneslot] = -1;
	character_info[playerid][pager] = -1;
    character_info[playerid][addiction] = 0;
    character_info[playerid][time_addiction] = 0;
    character_info[playerid][drug_effect][type] = 0;
    character_info[playerid][drug_effect][time_effect] = 0;
    character_info[playerid][payday] = 0;
    character_info[playerid][lvl] = 0;
	character_info[playerid][duty] = 0;
	character_info[playerid][duty_gun_1] = 0;
	character_info[playerid][duty_gun_2] = 0;
	character_info[playerid][duty_ammo_2] = 0;
	character_info[playerid][duty_gun_3] = 0;
	character_info[playerid][duty_ammo_3] = 0;
	character_info[playerid][duty_gun_special] = 0;
	character_info[playerid][ajail_time] = 0;
	character_info[playerid][jail_time] = 0;
	
	character_info[playerid][su] = 0;
	format(character_info[playerid][su_reason], 32, "");
    SetPlayerScore(playerid, 0);
	SetPVarInt(playerid, "move_player",-1);
	MaskOff(playerid);
	UpdateDamages(playerid);
    for(new i = 0; i<MAX_ATTACH; i++) ResetAttach(playerid, i, false);
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    character_info[playerid][inv][id][i] = 0;
	    character_info[playerid][inv][count][i] = 0;
	}
}
stock ResetAttach(playerid, i, bool:query=true)
{
    attach[playerid][i][bone] = -1;
	attach[playerid][i][iditem] = -1;
	if(query) 
	{
		new qu[128];
		format(qu, sizeof(qu), "DELETE FROM `attachments` WHERE chid=%d AND aindex=%d", character_info[playerid][id], i);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	RemovePlayerAttachedObject(playerid, i);
	UpdatePlayerColor(playerid);
}

stock HideAttach(playerid, slot, bool:query=true)
{
	if(query) 
	{
		new qu[128];
		format(qu, sizeof(qu), "UPDATE `attachments` SET `status`=1 WHERE chid=%d AND aindex=%d", character_info[playerid][id], slot);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	RemovePlayerAttachedObject(playerid, slot);
}


stock GenerateCarNumber(v)
{
	new qu[100], vnumber[11];
	
	format(vnumber, 11, "%s%s%dSA", _RND_(), _RND_(), 10000+random(999999));
	format(qu, sizeof(qu), "SELECT `id` FROM `cars` WHERE number='%s'", vnumber);
	mysql_function_query(dbHandle, qu, true, "OnGenerateCarNumber", "is[11]", v, vnumber);
}

stock UpdateDamages(playerid)
{
	for(new i; i<MAX_DAMAGES; i++)
	{
		character_info[playerid][damages][part][i] = -1;
		character_info[playerid][damages][gun_id][i] = -1;
		character_info[playerid][damages][hour_damages][i] = -1;
		character_info[playerid][damages][minute_damages][i] = -1;
		character_info[playerid][damages][damage_hp][i] = -1;
	}
}

stock IssetTicket(playerid)
{
	for(new i; i<MAX_TICKETS; i++)
	{
		if(ticket_info[playerid][i][tId] > 0) return 1;
	}
	return 0;
}


stock AuthVK(playerid, ip[]="0.0.0.0")
{
	new str[92+16+8];
	new randomcode = 10000 + random(99999);
	SetPVarInt(playerid, "AuthVK_Code", randomcode);
	format(str, sizeof(str), "In%%20your%%20account%%20tried%%20to%%20IP%%20%s.%%20Your%%20code%%20for%%20auth:%%20%d", ip, randomcode);
	VKMSG(playerid, player_info[playerid][vkid], str);
	
	ShowPlayerDialog(playerid, 113, DIALOG_STYLE_INPUT, "Аутентификация вконтакте", "{ffffff}Вам было отправлено сообщение с кодом, укажите код в поле ниже!", "Ввод", "Отмена");
	return 1;
}

//-----------------------------
UseAnim(playerid, animlib[], animname[], Float:Speed, looping, lockx, locky, lockz, lp, time = 0) {
	//if(player_info[playerid][perm] == 1) return 1;
	SetPVarInt(playerid, "UsingAnimation", 1);
    ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, time);
    ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, time);
    ApplyAnimation(playerid, animlib, animname, Speed, looping, lockx, locky, lockz, lp, time);
    //TextDrawShowForPlayer(playerid,txtAnimHelper);
    return 1;
}

PreloadAnimLib(playerid, animlib[]) {
	ApplyAnimation(playerid,animlib,"null",0.0,0,0,0,0,0);
}

stock UpdateDaysProp(playerid=INVALID_PLAYER_ID, propid=-1)
{
	if(propid > -1)
	{
		new qu[49+11+11];
		format(qu, sizeof(qu), "UPDATE property SET owner=%d, last_time=%d WHERE id=%d", character_info[playerid][id],gettime(), propid);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	else if(playerid != INVALID_PLAYER_ID)
	{
		new qu[42+11];
		format(qu, sizeof(qu), "UPDATE property SET last_time=%d WHERE owner=%d", gettime(), character_info[playerid][id]);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	return 1;
}

stock VKMSG(playerid, vk=268469461, message[])
{
	new str[256];
	format(str, sizeof(str), "137.74.50.64/?vk=%d&msg=%s",vk,message);
	//printf(str);
	HTTP(playerid, HTTP_GET, str, "", "MyHttpResponse");
}


stock ChangeVK(playerid)
{
	new str[600];
	format(str, sizeof(str), "{FF6347}Ваш аккаунт не привязан к аккаунту Вконтакте! \n{ffffff}Будучи администратором вы должны иметь привязанный аккаунт вконтакте чтобы проходить аутентификация в случае смены IP!{b1b1b1}\n\nВведите в окно ниже номер вашей страницы(только цифры)\n* Если у вас не изменен адрес страницы просто отбросьте слово Id\n* Если номер страницы изменен, зайдите в настройки аккаунта > общее > Адрес страницы > изменить. \nВ этом окне вы увидите номер страницы.");
	ShowPlayerDialog(playerid, 111, DIALOG_STYLE_INPUT, "Привязка Вконтакте", str, "Ввод", "Отмена");
	return 1;
}

stock CheckPlayer(playerid)
{
	return LogIn[playerid];
}

stock UpdateSettings(playerid)
{
	if(!player_info[playerid][settings][0]) 
		PlayerTextDrawHide(playerid, Areas[playerid]);
	else 
		PlayerTextDrawShow(playerid, Areas[playerid]);
}

stock AuthSucc(playerid)
{
	if(AuthTimeoutTimer[playerid] > 0) KillTimer(AuthTimeoutTimer[playerid]);
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно авторизовались на Classic RolePlay.");
	new str[180], ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	format(str, sizeof(str), "%s авторизован пользователем %s [%s]", character_info[playerid][name], player_info[playerid][login], ip);
	
	player_info[playerid][loged] = true;
	if(player_info[playerid][changename] < 0) player_info[playerid][changename] = 0;
	if(player_info[playerid][vip] > 0 && player_info[playerid][vip] < PREMIUM_OLDGOLD && player_info[playerid][vip_time] > 0)
	{
		new timenow = gettime();
		if(timenow > player_info[playerid][vip_time])
		{
			player_info[playerid][vip_time] = 0;
			SCM(playerid, COLOR_GREEN, "Время премиум аккаунта завершено!");
			if(IsPremium(playerid, PREMIUM_GOLD)) 
			{
				player_info[playerid][vip] = PREMIUM_OLDGOLD;
				SCM(playerid, COLOR_GREEN, "* Так как у вас была GOLD VIP, все бонусы кроме денег во время зарплаты сохранены!");
			}
			else player_info[playerid][vip] = 0;
		}
		else
		{
			new days_vip = (player_info[playerid][vip_time]-timenow) / 60 / 24 / 60;
			if(days_vip <= 5)
			{
				format(str, sizeof(str), "> Осталось %d дней до конца премиум аккуанта!", days_vip+1);
				SCM(playerid, COLOR_TOMATO, str);
			}
		}
	}	
	UserSetOnline(playerid, true);
	PlayerTextDrawShow(playerid, Areas[playerid]);
	for(new v; v<MAX_VEHICLES; v++) if(veh_info[v][owner] == character_info[playerid][id]) veh_info[v][destroy_time] = 0;
	LoadCars(playerid);
	new ipplayer[16];
	GetPlayerIp(playerid, ipplayer, sizeof(ipplayer));
	new qu[512];
	format(qu, sizeof(qu), "INSERT INTO `auth_log`(`userid`, `characterid`, `username`,`charactername`, `ip`, `ingame`) VALUES (%d, %d, '%s', '%s','%s', 1)", player_info[playerid][id], character_info[playerid][id], player_info[playerid][login], character_info[playerid][name], ipplayer);
	mysql_function_query(dbHandle, qu, false, "", "");
	
	UpdateDaysProp(playerid);
	
	format(qu, sizeof(qu), "SELECT * FROM attachments WHERE chid=%d", character_info[playerid][id]);
	mysql_function_query(dbHandle, qu, true, "OnLoadAttachments", "i", playerid);

	/*
	format(qu, sizeof(qu), "SELECT * FROM prison WHERE chid=%d AND days>0", character_info[playerid][id]);
	mysql_function_query(dbHandle, qu, true, "OnLoadPrison", "i", playerid);
	*/
	
	LoadTickets(playerid);
	if(character_info[playerid][posX] == 0.0 && character_info[playerid][posY] == 0.0 && character_info[playerid][posZ] == 0.0)
	{
	    SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Ваши координаты багнулись, вы отправлены на стандартный спавн.");
     	character_info[playerid][posX] = 1777.1, character_info[playerid][posY] = -1939.08, character_info[playerid][posZ] = 13.558;
	}
	if(character_info[playerid][ajail_time] > 0) 
		SetSpawnInfo(playerid, 0, character_info[playerid][skin], AJAIL_POS, 0.0, 0,0, 0,0, 0,0);
	else if(character_info[playerid][jail_time] > 0) 
		SetSpawnInfo(playerid, 0, character_info[playerid][skin], ArrestZone[0][posX],ArrestZone[0][posY],ArrestZone[0][posZ], 0.0, 0,0, 0,0, 0,0);
	else 
		SetSpawnInfo(playerid, 0, character_info[playerid][skin], character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ], 0.0, 0,0, 0,0, 0,0);
	
	SetPlayerHealth(playerid, 100.0);
	if(character_info[playerid][phoneslot] != -1) 
	{
		WireMsg(playerid, playerid, " включает телефон.");
		LoadContacts(playerid, character_info[playerid][phoneslot]);
	}
	UpdateSettings(playerid);
	SetTimerEx("Spawn", 500, false, "i", playerid);
}

stock AlarmActivate(v, playerid)
{
	if(veh_info[v][owner] <= 0 || veh_info[v][alarm_type] <= 0 || veh_info[v][alarm]) return 0;
	
	veh_info[v][alarm] = true;
	UpdateVehParams(v);
	veh_info[v][alarm_timer] = SetTimerEx("AlarmDisactivate", 120000, false, "i", v); 
	cmd_do(playerid, "У автомобиля сработала сигналиация!");
	/*
	if(veh_info[v][alarm_type] == 2) 
		Add911(playerid, "Сработала сигнализация на автомобиле.", "", "", true);
	*/
	foreach(new p : Player)
	{
		if(character_info[playerid][id] == veh_info[v][owner]) SCM(playerid, COLOR_YELLOW, "На вашем автомобиле сработала сигнализация!");
	}
	return 1;
}

stock VehicleBreaking(playerid)
{
	new cctv = CCTVArea(playerid);
	if(cctv > -1 && random(100) == 1)
	{
		new vehicle;
		if(GetPVarInt(playerid, "breaking_veh_id_boot") > 0) vehicle = GetPVarInt(playerid, "breaking_veh_id_boot");
		else vehicle = GetPVarInt(playerid, "breaking_veh_id");
		new str[64];
		if(random(2) == 1) format(str, sizeof(str), "Попытка угона автомобиля %s", VehicleNames[GetVehicleModel(vehicle)-400]);
		else format(str, sizeof(str), "Попытка угона автомобиля %s [%s]", VehicleNames[GetVehicleModel(vehicle)-400], veh_info[vehicle][number]);
		CCTVmsg(cctv, str);
	}
	
	if(GetPVarInt(playerid, "breaking_veh_id_boot") > 0)
	{
		new v = GetPVarInt(playerid, "breaking_veh_id_boot");
		new processing = GetPVarInt(playerid, "breaking_veh_processing");
		new r = random(150);
		if(processing <= 50) GameTextForPlayer(playerid, "~g~SOON", 1500, 3);
		else if(processing > 50 && processing <= 100) GameTextForPlayer(playerid, "~y~WAIT", 1500, 3);
		if(r == 1)
		{
			deleteitem(playerid, 89, 1);
			SCM(playerid, COLOR_TOMATO, "У вас сломалась отмычка!");
			if(checkitem(playerid, 89) != -1) SCM(playerid, COLOR_MSGSERVER, "> {FFFFFF}Так как в инвентаре была дополнительная отмычка, процесс не прервался!");
		}
		else if(checkitem(playerid, 89) == -1) 
		{
			DeletePVar(playerid, "breaking_veh_id_boot");
			DeletePVar(playerid, "breaking_veh_processing");
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нету отмычки!");
		}
		
		new floatxyz;
		GetCoordBootVehicle(v, xyz);
		
		if(!PlayerToPoint(3.5, playerid, xyz) || veh_info[v][boot] == true)
		{
			DeletePVar(playerid, "breaking_veh_id_boot");
			DeletePVar(playerid, "breaking_veh_processing");
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле закрытого багажника!");
		}
		if(processing <= 0)
		{
			DeletePVar(playerid, "breaking_veh_id_boot");
			DeletePVar(playerid, "breaking_veh_processing");
			veh_info[v][boot] = true;
			UpdateVehParams(v);
			return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы взломали багажник транспортного средства!");
		}
		SYS_AME(playerid, "взламывает замок багажника транспортного средства.");
		r = random(5);
		processing -= r;
		SetPVarInt(playerid, "breaking_veh_processing", processing);
		cmd_faim(playerid);
		
		if(veh_info[v][alarm_type] == 1) r = random(100);
		else if(veh_info[v][alarm_type] == 2) r = random(40);
		if(r == 1) AlarmActivate(v, playerid);
	}
	
	else if(GetPVarInt(playerid, "breaking_veh_id") > 0)
	{
		new v = GetPVarInt(playerid, "breaking_veh_id");
		new processing = GetPVarInt(playerid, "breaking_veh_processing");
		new r = random(150);
		if(processing <= 50) GameTextForPlayer(playerid, "~g~SOON", 1500, 3);
		else if(processing > 50 && processing <= 100) GameTextForPlayer(playerid, "~y~WAIT", 1500, 3);
		if(r == 1)
		{
			deleteitem(playerid, 89, 1);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} У вас сломалась отмычка!");
			if(checkitem(playerid, 89) != -1) SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Так как в инвентаре была дополнительная отмычка, процесс не прервался!");
		}
		else if(checkitem(playerid, 89) == -1) 
		{
			DeletePVar(playerid, "breaking_veh_id");
			DeletePVar(playerid, "breaking_veh_processing");
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нету отмычки!");
		}
		
		if(GetPlayerVehicleID(playerid) == v)
		{
			SYS_AME(playerid, "пытается завести транспортное средство с помощью отмычки.");
		}
		else 
		{
			new floatxyz;
			GetVehiclePos(v, xyz);
			if(!PlayerToPoint(3.5, playerid, xyz) || veh_info[v][lock] == false)
			{
				DeletePVar(playerid, "breaking_veh_id");
				DeletePVar(playerid, "breaking_veh_processing");
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле закрытого транспорта!");
			}
			cmd_faim(playerid);
		}
		if(processing <= 0)
		{
			DeletePVar(playerid, "breaking_veh_id");
			DeletePVar(playerid, "breaking_veh_processing");
			if(GetPlayerVehicleID(playerid) == v) veh_info[v][engine] = true;
			else veh_info[v][lock] = false;
			UpdateVehParams(v);
			return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы взломали транспортное средство!");
		}
		SYS_AME(playerid, "взламывает замок транспортного средства.");
		r = random(5);
		processing -= r;
		SetPVarInt(playerid, "breaking_veh_processing", processing);
		
		if(veh_info[v][alarm_type] == 1) r = random(100);
		else if(veh_info[v][alarm_type] == 2) r = random(40);
		if(r == 1) AlarmActivate(v, playerid);
		
	}
	return 1;
}

stock GunTest(playerid)
{
	new _gunid_ = GetPlayerWeapon(playerid);
	if(_gunid_ == 46) return 0;
	if(_gunid_ != character_info[playerid][gun] && _gunid_ != character_info[playerid][duty_gun_1] && _gunid_ != character_info[playerid][duty_gun_special] && _gunid_ != character_info[playerid][duty_gun_2] && _gunid_ != character_info[playerid][duty_gun_3] && _gunid_ != 0) 
	{
		return 1;
	}
	
	return 0;
}

stock IsPlayerLoged(playerid)
{
    if(!IsPlayerConnected(playerid) || !player_info[playerid][loged])		return 0;
	else																	return 1;
}
stock DestroyVehicleEx(v, bool:mysql=true)
{
	if(mysql)
	{
		new qu[256], str_inv[128];
		for(new it=0; it<MAX_INV_SLOTS; it++)
		{
			if(v == MAX_INV_SLOTS-1) format(str_inv, sizeof(str_inv), "%s%d:%d",str_inv, veh_info[v][inv][id][it], veh_info[v][inv][count][it]);
			else format(str_inv, sizeof(str_inv), "%s%d:%d|",str_inv, veh_info[v][inv][id][it], veh_info[v][inv][count][it]);
		}
		new istaxi;
		if(IsValidDynamicObject(veh_info[v][taxi])) istaxi = 1;
		if(veh_info[v][id] != 0) 
		{
			format(qu, sizeof(qu), "UPDATE cars SET inv='%s', col1='%d', col2='%d', fuel='%f', owner='%d', number='%s', alarm_type=%d, lock_type=%d, taxi=%d, wheels=%d WHERE id='%d'", str_inv, veh_info[v][vcolor1], veh_info[v][vcolor2], veh_info[v][fuel], veh_info[v][owner], veh_info[v][number], veh_info[v][alarm_type], veh_info[v][lock_type], istaxi, veh_info[v][wheels], veh_info[v][id]);
			mysql_function_query(dbHandle, qu, false, "", "");
		}
	}
	if(IsValidDynamicObject(veh_info[v][siren])) DestroyDynamicObject(veh_info[v][siren]);
	veh_info[v][siren] = 0;
	veh_info[v][id] = 0;
	veh_info[v][owner] = 0;
	//printf("[debug_3d] callsign remove vehdel");
	Delete3DTextLabel(veh_info[v][callsign]);
	veh_info[v][callsign] = Text3D:INVALID_3DTEXT_ID;
	veh_info[v][towing] = 0;
	DestroyVehicle(v);
	KillTimer(veh_info[v][timerid]);
	//printf("vehicle %d deleted.", v);
	return 1;
}

stock UnLoadEnters()
{
    for(new i=0; i<MAX_ENTERS; i++)
	{
	    enter_info[i][posX] = 0;
	    enter_info[i][posY] = 0;
	    enter_info[i][posZ] = 0;
	    enter_info[i][posXE] = 0;
	    enter_info[i][posYE] = 0;
	    enter_info[i][posZE] = 0;
	    enter_info[i][vworld] = 0;
	    enter_info[i][intid] = 0;
	    enter_info[i][vworldE] = 0;
        enter_info[i][intidE] = 0;
        DestroyDynamic3DTextLabel(enter_info[i][id3dtext]);
		//printf("[debug_3d] delete unload enters #1");
        DestroyDynamic3DTextLabel(enter_info[i][id3dtexte]);
        //printf("[debug_3d] delete unload enters #1");
        enter_info[i][id3dtext] = Text3D:INVALID_3DTEXT_ID;
        enter_info[i][id3dtexte] = Text3D:INVALID_3DTEXT_ID;
		//printf("Enter %d removed.", i);
	}
}

stock LoadEnters()
{
    new qu[64];
    format(qu, sizeof(qu), "SELECT * FROM `enters` WHERE 1");
    mysql_function_query(dbHandle, qu, true, "onloadenters", "i", 0);
}


stock AdminStatsUpdate(playerid)
{
	if(player_info[playerid][admin] > 0 && player_info[playerid][atime] > 0)
	{
		new qu[110+33];
		new admin_time = player_info[playerid][atime];
		format(qu, sizeof(qu), "insert into admins_stats values (%d, %d) on duplicate key update time=time+%d", player_info[playerid][id], admin_time, admin_time);
		mysql_function_query(dbHandle, qu, false, "", "");
		player_info[playerid][atime] = 0;
	}
	
	return 1;
}

stock attach_player_update(playerid)
{
	for(new i = 0; i<MAX_ATTACH; i++)
	{
		if(attach[playerid][i][iditem] > 0) 
			SetPlayerAttachedObject(playerid, i, Items[attach[playerid][i][iditem]][Model], attach[playerid][i][bone], attach[playerid][i][posX], attach[playerid][i][posY], attach[playerid][i][posZ], attach[playerid][i][posRX], attach[playerid][i][posRY], attach[playerid][i][posRZ], attach[playerid][i][posSX], attach[playerid][i][posSY], attach[playerid][i][posSZ]);
	}
}

stock attach_player(playerid, i, ITEM, BONE, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ, bool:sys_param=false, bool:mysql_save=false)
{
	new qu[256];
	
	if(!attachStatus[playerid])
	{
		if(!sys_param && !deleteitem(playerid, ITEM, 1)) 
			return 0;
	}

	attachStatus[playerid] = 0;
	
	if(!sys_param || mysql_save)
	{
		format(qu, sizeof(qu), "DELETE FROM `attachments` WHERE chid=%d AND aindex=%d", character_info[playerid][id], i);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	
	attach[playerid][i][iditem] = ITEM;
	attach[playerid][i][bone] = BONE;
	attach[playerid][i][posX] = fOffsetX;
	attach[playerid][i][posY] = fOffsetY;
	attach[playerid][i][posZ] = fOffsetZ;
	attach[playerid][i][posRX] = fRotX;
	attach[playerid][i][posRY] = fRotY;
	attach[playerid][i][posRZ] = fRotZ;
	attach[playerid][i][posSX] = fScaleX;
	attach[playerid][i][posSY] = fScaleY;
	attach[playerid][i][posSZ] = fScaleZ;
	
	if(!sys_param || mysql_save)
	{
		format(qu, sizeof(qu), "INSERT INTO `attachments`(chid, iditem, bone, aindex, X,Y,Z,RX,RY,RZ,SX,SY,SZ) VALUES (%d, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f)", character_info[playerid][id], attach[playerid][i][iditem], attach[playerid][i][bone], i, fOffsetX, fOffsetY, fOffsetZ, fRotX,fRotY,fRotZ, fScaleX, fScaleY, fScaleZ);
		mysql_function_query(dbHandle, qu, false, "", "");
	}
	
	SetPlayerAttachedObject(playerid, i, Items[ITEM][Model], BONE, fOffsetX, fOffsetY, fOffsetZ, fRotX,fRotY,fRotZ, fScaleX, fScaleY, fScaleZ);
	SetPVarInt(playerid, "attach_itemid", -1);
    SetPVarInt(playerid, "attach_bone", -1);
    return 1;
}
stock ntop(_number_)
{
	if(_number_ >= 0) return _number_;
	else return _number_ * -1;
}

stock CreateGraff(text[], grafid, color[], font[], fontsize, ownergraf, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	for(new i; i<MAX_GRAFF; i++)
	{
		if(graff_info[i][gID] > 0) continue;
		format(graff_info[i][gText], 32, "%s", text);
		format(graff_info[i][gFont], 32, "%s", font);
		format(graff_info[i][gColor], 32, "%s", color);
		graff_info[i][gID] = grafid;
		graff_info[i][gFontsize] = fontsize;
		graff_info[i][gOwner] = ownergraf;
		graff_info[i][gX] = x;
		graff_info[i][gY] = y;
		graff_info[i][gZ] = z;
		graff_info[i][gRX] = rx;
		graff_info[i][gRY] = ry;
		graff_info[i][gRZ] = rz;
		new str[36];
		graff_info[i][gObj] = CreateDynamicObject(19482, graff_info[i][gX], graff_info[i][gY], graff_info[i][gZ], graff_info[i][gRX], graff_info[i][gRY], graff_info[i][gRZ], -1, 0, -1, 200);
		
		format(str, sizeof(str), "{%s}%s", graff_info[i][gColor], graff_info[i][gText]);
		SetDynamicObjectMaterialText(graff_info[i][gObj], 0, str, OBJECT_MATERIAL_SIZE_256x128, graff_info[i][gFont], graff_info[i][gFontsize], 1, COLOR_WHITE, 0, 0);
		return 1;
	}
	return 1;
}

stock KillMsg(playerid, damagedid, weaponid, _msg_[])
{
	if(GetPVarInt(playerid, "KILLMSG_BLOCK")) return 1;
	SetPVarInt(playerid, "KILLMSG_BLOCK", 1);
	new weaponname[24];
	GetWeaponName(weaponid, weaponname, sizeof (weaponname));
	new str[180];
	format(str, sizeof(str), "%s игрока %s(%d) [%s]", _msg_, sendername(damagedid), damagedid, weaponname);
	PlayerLog(playerid, str);
	SetTimerEx("killmsg_unblock", 2000, false, "d", playerid);
	return 1;
}

stock IsPlayerAttachItem(playerid, itemid)
{
	for(new i=0; i<MAX_ATTACH; i++)
	    if(attach[playerid][i][iditem] == itemid) return 1;

	return 0;
}

stock GetNameNumber(playerid, phonenumber[])
{
	new str[64], slot = search_phonename(playerid, phonenumber);
	if(slot < 0) format(str, sizeof(str), "%d", strval(phonenumber));
	else format(str, sizeof(str), "%s", contacts_info[phonenumber][slot][Name]);
	return str;
}
stock search_phonename(playerid, phonenumber)
{
	for(new i=0; i<12; i++)
	{
	    if(contacts_info[playerid][i][Phone] == phonenumber) return i;
	}
	return -1;
}
stock search_phonenumber(playerid, phonename[])
{
	for(new i=0; i<12; i++)
	{
	    if(!strcmp(contacts_info[playerid][i][Name], phonename, true, 10 ))
			return contacts_info[playerid][i][Phone];
	}
	return -1;
}
stock LoadContacts(playerid, phonenumber)
{
	new qu[36+11];
	format(qu, sizeof(qu), "SELECT * FROM `phone` WHERE phone=%d", phonenumber);
	mysql_function_query(dbHandle, qu, true, "OnLoadContacts", "ii", playerid, phonenumber);
	return 1;
}
stock LoadPager(playerid, phonenumber)
{
	new qu[36+11];
	format(qu, sizeof(qu), "SELECT * FROM `pager` WHERE id=%d", phonenumber);
	mysql_function_query(dbHandle, qu, true, "OnLoadPager", "ii", playerid, phonenumber);
	return 1;
}
stock SaveContacts(playerid)
{
	new qu[512], str_contacts[12][64];
	for(new i=0; i<12; i++)
	{
 		format(str_contacts[i],
 		64,
 		"%d|%s",
		contacts_info[playerid][i][Phone],
		contacts_info[playerid][i][Name]);
		//printf("%d/%s| %s", contacts_info[phonenumber][i][Phone], contacts_info[phonenumber][i][Name], str_contacts[i]);
	}

	format(qu, sizeof(qu), "UPDATE `phone` SET `slot1`='%s',`slot2`='%s',`slot3`='%s',`slot4`='%s',`slot5`='%s',`slot6`='%s',`slot7`='%s',`slot8`='%s',`slot9`='%s',`slot10`='%s',`slot11`='%s',`slot12`='%s' WHERE `phone`=%d",
	str_contacts[0],str_contacts[1],str_contacts[2],
	str_contacts[3],str_contacts[4],str_contacts[5],
	str_contacts[6],str_contacts[7],str_contacts[8],
	str_contacts[9],str_contacts[10],str_contacts[11],
	character_info[playerid][phoneslot]);
	mysql_function_query(dbHandle, qu, false, "", "");
	return 1;
}

stock CCTVmsg(c, text[])
{
	if(cctvoff) return 1;
	if(cctv_info[c][destroyed] > 0 || cctv_info[c][id] == 0) return 1; 
	if(cctv_info[c][timeout] > 0) return 1;
	new i, Float:x, Float:y;
	x = cctv_info[c][posX];
	y = cctv_info[c][posY];
	for(; i != sizeof(gSAZones); i++ )
	{
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) break;
	}
	
	
	new str[180];
	cctv_info[c][timeout] = 15;
	format(str, sizeof(str), "(%s) CAM #%d: %s", gSAZones[i][SAZONE_NAME],cctv_info[c][id], text);
	foreach(new p : Player)
	{
		if(!InFactionType(p, FACTIONTYPE_STATE) || !IsDuty(p)) continue;
		SCM(p, COLOR_YELLOW_GREEN, str);
	}
	return 1;
}

stock CCTVArea(playerid)
{
	for(new i=0; i<MAX_CCTV; i++)
	{
		if(PlayerToPoint(30.0, playerid, cctv_info[i][posX], cctv_info[i][posY], cctv_info[i][posZ]) && GetPlayerVirtualWorld(playerid) == cctv_info[i][VW] && GetPlayerInterior(playerid) == cctv_info[i][Interior]) return i;
	}
	return -1;
}
stock CCTVdestroy(c, time=600)
{
	if(cctv_info[c][id] == 0) return 0;
	cctv_info[c][destroyed] = time;
	new str[32];
	//if(cctv_info[c][destroyed] > 0) format(str, sizeof(str), "CAM #%d [destroyed]", cctv_info[c][id]);
	//else format(str, sizeof(str), "CAM #%d", cctv_info[c][id]);
	
	if(cctv_info[c][destroyed] > 0) format(str, sizeof(str), "DESTROYED");
	
	UpdateDynamic3DTextLabelText(cctv_info[c][a3d], COLOR_GRAY_EE, str);
	return 1;
}

stock BuyAttach(playerid, attachid)
{
	if(!InPropType(playerid, 2)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в магазине одежды");
	
	if(takemoney(playerid, 70, "buy attach item") == 1)
	{
		for(new i = 0; i<sizeof(Items); i++)
		{
			if(Items[i][Model] == attachid)
			{		
				if(!giveitem(playerid, i, 1)) 
					return givemoney(playerid, 70, "no itemslot for buy item");
				
				return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
			}		
		}
		givemoney(playerid, 70, "wrong item");
		return 1;
	}
	else 
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
	return 1;
}

stock BuySkin(playerid, skinid)
{
	if(!InPropType(playerid, 2)) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь в магазине одежды");
	
	/*
	if(skinid < 1 || skinid == 74 || skinid >= 265 && skinid <= 267 || skinid >= 300 && skinid <= 311 || skinid >= 274 && skinid <= 288) 
		return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот скин нельзя купить");
	*/
	
	if(takemoney(playerid, 150, "buy item clothes") == 1)
	{
		if(!giveitem(playerid, 46, skinid)) 
			return givemoney(playerid, 150, "no itemslot for buy item");
		
		prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += 150-(150/4);
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
	}
	else 
		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
	return 1;
}
stock InFaction(playerid, bool:fleader=false)
{
	if(character_info[playerid][faction] == 0) return 0;
	if(factions[character_info[playerid][faction]][FactionFreeze] == 1) return 0;
	if(!fleader && InFactionType(playerid, 1) || !fleader && InFactionType(playerid, 2) || !fleader && InFactionType(playerid, 3) || !fleader && InFactionType(playerid, 4)) return 1;
	if(fleader && InFactionType(playerid, 1, true) || fleader && InFactionType(playerid, 2, true) || fleader && InFactionType(playerid, 3, true) || fleader && InFactionType(playerid, 4, true)) return 1;
    else return 0;
}
stock InFactionType(playerid, ftype, bool:fleader=false)
{
	if(character_info[playerid][faction] == 0) 
		return 0;
    
	if(factions[character_info[playerid][faction]][FactionFreeze] == 1) 
		return 0;
	
	if(character_info[playerid][faction] <= 0) 
		return 0;
	
	if(fleader && factions[character_info[playerid][faction]][Type] == ftype && factions[character_info[playerid][faction]][Leader] == character_info[playerid][id]) 
		return 1;
	
	if(!fleader && factions[character_info[playerid][faction]][Type] == ftype) 
		return 1;
	return 0;
}
stock InFactionId(playerid, fid, bool:fleader=false)
{
	if(character_info[playerid][faction] == 0) return 0;
    if(factions[character_info[playerid][faction]][FactionFreeze] == 1) return 0;
	if(character_info[playerid][faction] <= 0) return 0;
	if(!fleader && character_info[playerid][faction] == fid) return 1;
	if(fleader && character_info[playerid][faction] == fid && factions[character_info[playerid][faction]][Leader] == character_info[playerid][id]) return 1;
	return 0;
}
stock DialogContactsName(playerid)
{
    SPD(playerid, 27, DIALOG_STYLE_INPUT, "Контакты", "{FFFFFF}Введите {FF0000}имя{FFFFFF} контакта: ", "Выбрать", "Отмена");
    return 1;
}

stock ResultPurchase(playerid)
{
    if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) return 1;
    if(!purchase_price[character_info[playerid][faction]]) return 1;
    if(GetPVarInt(playerid, "buy_purchase")) return 1;
    if(GetPVarInt(playerid, "local_obj"))
    {
        DestroyDynamicObject(GetPVarInt(playerid, "local_obj"));
        DeletePVar(playerid, "local_obj");
    }
    new str[128];
	for(new i; i<MAX_PURCHASE; i++)
	{
		if(purchase[character_info[playerid][faction]][i][count] < 1) continue;
		format(str, sizeof(str), "%s:%d", senderitems(purchase[character_info[playerid][faction]][i][iditem]), purchase[character_info[playerid][faction]][i][count]);
		SCM(playerid, COLOR_GREEN, str);
	}
	format(str, sizeof(str), "Стоимость полного заказа: %d$", purchase_price[character_info[playerid][faction]]);
	SCM(playerid, COLOR_RED, str);
	new r = random(41), Float:x, Float:y, Float:z;
	switch(r)
	{
		case 0: x= 1845.2484, y = -1707.5891, z = 13.5300;
		case 1: x= 2099.1553, y = -1555.0452, z = 13.3462;
		case 2: x= 2420.6296, y = -1691.6927, z = 13.7938;
		case 3: x= 2514.0847, y = -1774.2213, z = 13.5469;
		case 4: x= 2467.2900, y = -1900.3849, z = 13.5469;
		case 5: x= 2440.7532, y = -1975.4645, z = 13.5469;
		case 6: x= 2200.4561, y = -1970.3157, z = 13.7841;
		case 7: x= 2009.6393, y = -1878.5328, z = 13.5469;
		case 8: x= 2034.2810, y = -1824.1860, z = 13.5469;
		case 9: x= 1793.2074, y = -2015.6537, z = 13.4974;
		case 10: x= 1909.8533, y = -2096.4607, z = 13.4366; 
		case 11: x= 1615.1475, y = -1782.9808, z = 13.5094;
		case 12: x= 1630.3265, y = -1510.3756, z = 13.5938;
		case 13: x= 1721.6927, y = -1116.5304, z = 24.0859;
		case 14: x= 1788.4204, y = -1227.6129, z = 16.9369;
		case 15: x= 1968.9398, y = -1233.7673, z = 20.0469;
		case 16: x= 2122.6365, y = -1195.3083, z = 23.9172;
		case 17: x= 1917.5229, y = -1091.7549, z = 24.5841;
		case 18: x= 1285.2450, y = -1269.7719, z = 25.5343;
		case 19: x= 1272.3190, y = -1879.0349, z = 13.5525;
		case 20: x= 843.6091, y = -1854.1276, z = 8.4659;
		case 21: x= 390.0942, y = -1892.3821, z = 1.3868;
		case 22: x= 447.3110, y = -1287.1790, z = 15.2765; 
		case 23: x= 715.4333, y = -1625.9789, z = 2.4297;
		case 24: x= 857.2903, y = -1553.3741, z = 13.5231; 
		case 25: x= 854.0478, y = -1361.7123, z = 14.1941;
		case 26: x= 938.7497, y = -1056.7313, z = 24.9001;
		case 27: x= 1015.2957, y = -1005.2026, z = 32.1016; 
		case 28: x= 1390.2568, y = -1534.5957, z = 12.1464;
		case 29: x= 1354.8760, y = -1664.6528, z = 13.6110;
		case 30: x= 1347.7424, y = -1771.4872, z = 13.4910;
		case 31: x= 2129.2493, y = -1726.8722, z = 13.5447;
		case 32: x= 2190.8953, y = -1831.7463, z = 16.1406;
		case 33: x= 2316.3770, y = -1799.5824, z = 13.7255;
		case 34: x= 2443.3069, y = -1557.2841, z = 24.0000;
		case 35: x= 2613.5051, y = -1393.0468, z = 34.8871;
		case 36: x= 2819.7725, y = -1426.5002, z = 40.0625;
		case 37: x= 2623.3242, y = -1489.5348, z = 16.4773;
		case 38: x= 2545.9888, y = -1128.5851, z = 62.7248;
		case 39: x= 2260.5955, y = -1097.5822, z = 37.9766;
		case 40: x= 2413.4146, y = -1328.8361, z = 24.9192;
		case 41: x= 2413.4146, y = -1328.8361, z = 24.9192;
	}
	new obj = CreateDynamicObject(11745, x,y,z-0.8, 0,0,0, 0, 0);
	SetPVarInt(playerid, "local_obj", obj);

	SetPlayerCheckpoint(playerid, x,y,z, 1.0);
	SetPVarInt(playerid, "buy_purchase", 1);
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Перед тем, как встать на маркер, убедитесь, что в инвентаре достаточно места!");
	return 1;
}

stock GoToVehEnter(playerid)
{
	if(GetPVarInt(playerid, "Freezed")) 
		return 1;
	
	new v = GetPlayerVehicleID(playerid);
	for(new i; i<sizeof(VehEnter); i++)
	{
		if(PlayerToPoint(6.0, playerid, VehEnter[i][PosX], VehEnter[i][PosY], VehEnter[i][PosZ]) && GetPlayerVirtualWorld(playerid) == VehEnter[i][VW] && VehEnter[i][factionid] == character_info[playerid][faction])
		{
			SetVehiclePos(v, VehEnter[i][PosRX], VehEnter[i][PosRY], VehEnter[i][PosRZ]);
			SetVehicleZAngle(v, VehEnter[i][PosRR]);
			SetVehicleVirtualWorld(v, VehEnter[i][RVW]);
			SetPlayerVw(playerid, VehEnter[i][RVW]);
			foreach(new p : Player)
			{
				if(!IsPlayerLoged(p)) 
					continue;
				if(GetPlayerVehicleID(p) == v && p != playerid)
					SetPlayerVw(p, VehEnter[i][RVW]);
			}
			Freeze(playerid, 500);
			return 1;
		}
		else if(PlayerToPoint(6.0, playerid, VehEnter[i][PosRX], VehEnter[i][PosRY], VehEnter[i][PosRZ]) && GetPlayerVirtualWorld(playerid) == VehEnter[i][RVW])
		{
			SetVehiclePos(v, VehEnter[i][PosX], VehEnter[i][PosY], VehEnter[i][PosZ]);
			SetVehicleZAngle(v, VehEnter[i][PosR]);
			SetVehicleVirtualWorld(v, VehEnter[i][VW]);
			SetPlayerVw(playerid, VehEnter[i][VW]);
			foreach(new p : Player)
			{
				if(!IsPlayerLoged(p)) 
					continue;
				if(GetPlayerVehicleID(p) == v && p != playerid)
					SetPlayerVw(p, VehEnter[i][VW]);
			}
			Freeze(playerid, 500);
			return 1;
		}
	}
	return 1;
}

ShowCarShowroom(playerid)
{
	if(!PlayerToPoint(15.0, playerid, 536.8356, -1293.9266, 17.2422)) return 0;
	if(!IsPremium(playerid, PREMIUM_SILVER)) ShowPlayerDialog(playerid, 76, DIALOG_STYLE_TABLIST, "Автомобили","Дешевые\nВнедорожники\nСпортивные\nСпециальные\nОбычные\nГрузовые\n{b1b1b1}Для премиумов\n{ffffff}Мото", "Выбрать", "Отмена");
	else ShowPlayerDialog(playerid, 76, DIALOG_STYLE_TABLIST, "Автомобили","Дешевые\nВнедорожники\nСпортивные\nСпециальные\nОбычные\nГрузовые\nДля премиумов\nМото", "Выбрать", "Отмена");
	return 1;
}
ShowLicDialog(playerid)
{
	ShowPlayerDialog(playerid, 75, DIALOG_STYLE_TABLIST_HEADERS, "Лицензии", "Лицензия\tЦена\nНа вождение\t400$\nНа полёт\t3500$", "Выбрать", "Отмена");
}


stock WireMsg(playerid, p, text[])
{
	//printf("%d->%d: %s", playerid, p, text);
	new wire_str[180];
	format(wire_str, sizeof(wire_str), "(Прослушка) %d%s", character_info[playerid][phoneslot], text);
	
	foreach(new pw : Player)
	{
		if(!IsPlayerLoged(pw) || !InFactionId(pw, LSPD_FACTION) && !InFactionId(pw, SASD_FACTION)) continue;
		if(GetPVarInt(pw, "wire_phone") == character_info[playerid][phoneslot] || GetPVarInt(pw, "wire_phone") == character_info[p][phoneslot]) SCM(pw, COLOR_GRAY, wire_str);
	}
	return 1;
}


stock Add911(playerid, text[],text2[],text3[],bool:autocall=false)
{
	new str[180];
	new Float:x, Float:y, Float:z, i = 0;
	
	if(character_info[playerid][prop] > 0)
	{
		new propid = GetLocalIdProp(character_info[playerid][prop]);
		x = prop_info[propid][posX], y = prop_info[propid][posY], z = prop_info[propid][posZ];
	}
	else GetPlayerPos(playerid, x, y, z);

	for(; i != sizeof(gSAZones); i++ )
	{
		if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4]) break;
	}
	// gSAZones[i][SAZONE_NAME]
	count_911++;
	foreach(new p : Player)
	{
		if(IsPlayerLoged(p) && InFactionType(p, 1))
		{
			SCM(p, COLOR_GREEN, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			if(autocall == false) format(str, sizeof(str), "911 ВЫЗОВ #%d: {FFFFFF}%02d:%02d{00BFFF}", count_911, hour, minute);
			else format(str, sizeof(str), "911 СИСТЕМНЫЙ ВЫЗОВ #%d: вызов поступил в {FFFFFF}%02d:%02d{00BFFF}", count_911, hour, minute);
			SCM(p, COLOR_GREEN, str);
						
			format(str, sizeof(str), "ОПИСАНИЕ: {FFFFFF}%s", text);
			SCM(p, COLOR_GREEN, str);
			
			format(str, sizeof(str), "МЕСТО: {FFFFFF}%s", text2);
			SCM(p, COLOR_GREEN, str);
			
			format(str, sizeof(str), "ТРЕБУЕМЫЕ СЛУЖБЫ: {FFFFFF}%s", text3);
			SCM(p, COLOR_GREEN, str);
			
			if(autocall == false)
			{
				format(str, sizeof(str), "ВЫЗОВ ПОСТУПИЛ С НОМЕРА: {FFFFFF}%d", GetPhonenumber(playerid));
				SCM(p, COLOR_GREEN, str);
			}
			
			format(str, sizeof(str), "ЛОКАЦИЯ: {FFFFFF}%s", gSAZones[i][SAZONE_NAME]);
			SCM(p, COLOR_GREEN, str);
			
			SCM(p, COLOR_GREEN, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
			//
		}
	}
	
	for(new it = MAX_911; it>-1; it--)
	{
		if(it < MAX_911 && it != 0)
		{
			format(list_911[it][owner], 25, "%s", list_911[it-1][owner]);
			format(list_911[it][time_911], 6, "%s", list_911[it-1][time_911]);
			format(list_911[it][text_911], 128, "%s", list_911[it-1][text_911]);
			format(list_911[it][Zone], 32, "%s", list_911[it-1][Zone]);	
		}
		if(it == 0)
		{
			GetPlayerPos(playerid, list_911[it][posX], list_911[it][posY], list_911[it][posZ]);
			format(list_911[it][text_911], 128, "%s", text);
			if(autocall == false) format(list_911[it][owner], 25, "%s", character_info[playerid][name]);
			else format(list_911[it][owner], 25, "АВТОМАТИЧЕСКИЙ ВЫЗОВ");
			format(list_911[it][time_911], 6, "%02d:%02d", hour, minute);
			format(list_911[it][Zone], 32, "%s", gSAZones[i][SAZONE_NAME]);
			list_911[it][id] = count_911;
		}
	}
	DeletePVar(playerid, "called_911");
	return 1;
}

stock UpdateTune(vehicleid)
{
	if(veh_info[vehicleid][wheels] != 0) AddVehicleComponent(vehicleid, veh_info[vehicleid][wheels]);
}

stock InPropType(playerid, typeid_)
{
	if(GetPlayerVirtualWorld(playerid) > 200 && prop_info[GetLocalIdProp(character_info[playerid][prop])][type] == typeid_)
	    return 1;
	else return 0;
}

stock OOCMSG(playerid, text[])
{
	GetPlayerPos(playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]);
	
    new string[128];
	format( string, sizeof(string), "(( %s (%s) %s ))" , character_info[playerid][name], player_info[playerid][login], text);
    ProxDetector( 10.0, GetPlayerVirtualWorld( playerid ), playerid, string, string, COLOR_GRAY,COLOR_GRAY,COLOR_GRAY,COLOR_GRAY,COLOR_GRAY );
}

stock HideDrugEffect(playerid)
{
	PlayerTextDrawHide(playerid, DrugEffect[playerid][0]);
	PlayerTextDrawHide(playerid, DrugEffect[playerid][1]);
	PlayerTextDrawHide(playerid, DrugEffect[playerid][2]);
	PlayerTextDrawHide(playerid, DrugEffect[playerid][3]);
	PlayerTextDrawHide(playerid, DrugEffect[playerid][4]);
}

stock EditDrugEffect(playerid, COLOR_1, COLOR_2, COLOR_3, COLOR_4, COLOR_5)
{
	PlayerTextDrawBoxColor(playerid, DrugEffect[playerid][0], COLOR_1);
	PlayerTextDrawBoxColor(playerid, DrugEffect[playerid][1], COLOR_2);
	PlayerTextDrawBoxColor(playerid, DrugEffect[playerid][2], COLOR_3);
	PlayerTextDrawBoxColor(playerid, DrugEffect[playerid][3], COLOR_4);
	PlayerTextDrawBoxColor(playerid, DrugEffect[playerid][4], COLOR_5);
}

stock ShowDrugEffect(playerid)
{
	PlayerTextDrawShow(playerid, DrugEffect[playerid][0]);
	PlayerTextDrawShow(playerid, DrugEffect[playerid][1]);
	PlayerTextDrawShow(playerid, DrugEffect[playerid][2]);
	PlayerTextDrawShow(playerid, DrugEffect[playerid][3]);
	PlayerTextDrawShow(playerid, DrugEffect[playerid][4]);
}

stock LoadFactions()
{
	new qu[64];
	format(qu, sizeof(qu), "SELECT * FROM factions WHERE 1");
	mysql_function_query(dbHandle, qu, true, "OnLoadFactions", "");
}


stock UpdateAchat()
{
	for(new i; i<MAX_ACHAT; i++)
	{
		new str[16], prefix[11];
		
		if(achat_info[i][New] == true) prefix = "~p~";
		else if(achat_info[i][Playerid] != -1) prefix = "~b~";

		format(str, sizeof(str), "%s%d:%d", prefix, achat_info[i][Playerid], achat_info[i][Code]);
		TextDrawSetString(ACHAT[i], str);
	}
}
stock LoadDoors()
{
	new qu[64];
	format(qu, sizeof(qu), "SELECT * FROM doors WHERE 1");
	mysql_function_query(dbHandle, qu, true, "OnLoadDoors", "");
}

stock AddAchat(playerid, code)
{	
	for(new i = MAX_ACHAT; i>-1; i--)
	{
	    if(i < MAX_ACHAT && i != 0)
	    {
			achat_info[i][Playerid] = achat_info[i-1][Playerid];
			achat_info[i][Code] = achat_info[i-1][Code];
			achat_info[i][New] = achat_info[i-1][New];
	    }
		if(i == 0)
		{
		    achat_info[i][Playerid] = playerid;
    		achat_info[i][Code] = code;
			achat_info[i][New] = true;
			new str[26];
			format(str, sizeof(str), "~r~%d:%d", playerid, code);
			foreach(new p : Player)
			{
				if(!IsPlayerLoged(p) || IsAdmin(p, 2, true)) continue;
				GameTextForPlayer(p, str, 3000, 6);
				Sound_Fail(p);
			}
			SetTimerEx("AchatOld", 4000, false, "dd", playerid, code);
		}
	}
	UpdateAchat();
}

stock LoadCars(playerid)
{
	new qu[128];
	format(qu, sizeof(qu), "SELECT * FROM `cars` WHERE owner='%d'", character_info[playerid][id]);
	mysql_function_query(dbHandle, qu, true, "OnLoadCars", "d", -1);
	return 1;
}
stock IsPremium(playerid, prem_lvl)
{
	if(player_info[playerid][vip] >= prem_lvl) return 1; 
	else return 0;
}

stock SearchGraffId(graffid)
{
	for(new i; i < MAX_GRAFF; i++)
	{
		if(graff_info[i][gID] == graffid) 
			return 1;
	}
	return 0;
}

stock CompareStrings(string[], string2[])
{
	if(!strcmp(string, string2, true))
		return true;
	else
		return false;
}

stock UserSetOnline(playerid, bool:online)
{
	new qu[128];
	format(qu, sizeof(qu), "UPDATE `users` SET `online`=%d WHERE id=%d", online, player_info[playerid][id]);
	//SCM(playerid, COLOR_GRAY, qu);
	mysql_function_query(dbHandle, qu, false, "", "");	
}

stock UpdateServerInt()
{
	mysql_function_query(dbHandle, "SELECT * FROM `serverint`", true, "OnLoadServerint", "");
	return 1;
}

stock WriteOneString(tofile[],string[])
{
	new File:opnfile;
	opnfile=fopen(tofile,io_append); 
	fwrite(opnfile,string);
	fclose(opnfile);
	return 1;
}

stock _RND_()
{
        new RND[2], i = random(26);
		format(RND, sizeof(RND), "-FAIL-");
        switch(i)
        {
            case 0: format(RND, sizeof(RND), "Q");
			case 1: format(RND, sizeof(RND), "W");
			case 2: format(RND, sizeof(RND), "E");
			case 3: format(RND, sizeof(RND), "R");
			case 4: format(RND, sizeof(RND), "T");
			case 5: format(RND, sizeof(RND), "Y");
			case 6: format(RND, sizeof(RND), "U");
			case 7: format(RND, sizeof(RND), "I");
			case 8: format(RND, sizeof(RND), "O");
			case 9: format(RND, sizeof(RND), "P");
			case 10: format(RND, sizeof(RND), "A");
			case 11: format(RND, sizeof(RND), "S");
			case 12: format(RND, sizeof(RND), "D");
			case 13: format(RND, sizeof(RND), "F");
			case 14: format(RND, sizeof(RND), "G");
			case 15: format(RND, sizeof(RND), "H");
			case 16: format(RND, sizeof(RND), "J");
			case 17: format(RND, sizeof(RND), "K");
			case 18: format(RND, sizeof(RND), "L");
			case 19: format(RND, sizeof(RND), "Z");
			case 20: format(RND, sizeof(RND), "X");
			case 21: format(RND, sizeof(RND), "C");
			case 22: format(RND, sizeof(RND), "V");
			case 23: format(RND, sizeof(RND), "B");
			case 24: format(RND, sizeof(RND), "N");
			case 25: format(RND, sizeof(RND), "M");
        }
        return RND;
}





stock PlayerPlaySoundEx(playerid, sound)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(playerid, x, y, z);

	foreach (new i : Player) if (IsPlayerInRangeOfPoint(i, 20.0, x, y, z) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)) {
	    PlayerPlaySound(i, sound, x, y, z);
	}
	return 1;
}


stock UpdateDutyGuns(playerid)
{
	if(character_info[playerid][faction] == 0 && (character_info[playerid][duty_gun_1] != 0 || character_info[playerid][duty_gun_2] != 0 || character_info[playerid][duty_gun_3] != 3))
	{
		character_info[playerid][duty_gun_1] = 0;
		character_info[playerid][duty_gun_2] = 0, character_info[playerid][duty_ammo_2] = 0;
		character_info[playerid][duty_gun_3] = 0, character_info[playerid][duty_ammo_3] = 0;
		character_info[playerid][duty_gun_special] = 0;
	}
	if(!IsDuty(playerid))
	{
		character_info[playerid][duty_gun_1] = 0;
		character_info[playerid][duty_gun_2] = 0, character_info[playerid][duty_ammo_2] = 0;
		character_info[playerid][duty_gun_3] = 0, character_info[playerid][duty_ammo_3] = 0;
		character_info[playerid][duty_gun_special] = 0;
		ResetPlayerWeapons(playerid);
		return 1;
	}
	if(character_info[playerid][gun] > 0) 
		return wepinv(playerid);
	
	ResetPlayerWeapons(playerid);
	
	if(character_info[playerid][duty_gun_special] > 0) 
		GivePlayerWeapon(playerid, character_info[playerid][duty_gun_special], 999999);
	else 
	{
		if(character_info[playerid][duty_ammo_2] <= 0) 
			character_info[playerid][duty_gun_2] = 0;
		
		if(character_info[playerid][duty_ammo_3] <= 0) 
			character_info[playerid][duty_gun_3] = 0;
		
		if(character_info[playerid][duty_gun_2] > 0) 
			GivePlayerWeapon(playerid, character_info[playerid][duty_gun_2], character_info[playerid][duty_ammo_2]);
		
		if(character_info[playerid][duty_gun_3] > 0) 
			GivePlayerWeapon(playerid, character_info[playerid][duty_gun_3], character_info[playerid][duty_ammo_3]);
		
		if(character_info[playerid][duty_gun_1] > 0) 
			GivePlayerWeapon(playerid, character_info[playerid][duty_gun_1], 999999999);
	}
	return 1;
}

stock CopSkin(sk)
{
	if(sk == 280 || sk == 281 || sk == 282 || sk == 283 || sk == 265 || sk == 266 || sk == 267 || sk == 284 || sk == 285 || sk == 286 || sk == 287 || sk == 306 || sk == 307) return 1;
	else return 0;
}

stock SyntaxCMD(playerid, text[])
{
	new _str_[180];
	format(_str_, sizeof(_str_), ">{FFFFFF} %s", text);
	SCM(playerid, COLOR_MSGDESC, _str_);
	return 1;
}
stock PropertyInventory(playerid) {

	new i = GetLocalIdProp(character_info[playerid][prop]);
	if ((InFactionId(playerid, LSPD_FACTION) || InFactionId(playerid, SASD_FACTION) || InFactionId(playerid, LSSD_FACTION)) && GetPlayerVirtualWorld(playerid) > 200) return i;
	else if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[i][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200) return i;
	else return -1;
}

stock VehicleInventory(playerid) {
	new v = GetPVarInt(playerid, "LastVehicleInventory");

	if(v != 0) {
		new Float:x, Float:y, Float:z;
		GetCoordBootVehicle(v, xyz);
		if(PlayerToPoint(2.0, playerid, xyz) && veh_info[v][boot] || GetPlayerVehicleID(playerid) == v && veh_info[v][owner] == character_info[playerid][id]) return v; 
	}
	v = 0;
	for(new i; i<MAX_VEHICLES; i++) {
		new Float:x, Float:y, Float:z;
		GetCoordBootVehicle(i, xyz);
				
		if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot])
		{
			v = i;
			break;
		}
	}
	if(GetPlayerVehicleID(playerid) != 0 && veh_info[GetPlayerVehicleID(playerid)][owner] == character_info[playerid][id]) v = GetPlayerVehicleID(playerid);

	SetPVarInt(playerid, "LastVehicleInventory", v);
	return v;
}
stock veh_inv(playerid)
{
	new v = VehicleInventory(playerid);
	if(v == 0) return 1;
    new str[2048] = "{AFAFAF}Предмет\t{AFAFAF}Количество\n", color[128], count_text[128], itemname_text[128];
	for(new i = 0; i<MAX_INV_SLOTS; i++)
	{
	    format(itemname_text, sizeof(itemname_text), "%s", senderitems(0)), format(count_text, sizeof(count_text), "");
	 	if(veh_info[v][inv][count][i] < 1)
		{
			veh_info[v][inv][id][i] = 0;
	 		veh_info[v][inv][count][i] = 0;
		}
  		if(veh_info[v][inv][id][i] == 0) color = "{AFAFAF}";
		else color = "{ffffff}";

		if(veh_info[v][inv][id][i] != 0)
		{
			if(Items[veh_info[v][inv][id][i]][compound])
			{
				format(itemname_text, sizeof(itemname_text), "%s",  senderitems(veh_info[v][inv][id][i]));
    			if(veh_info[v][inv][count][i] > 0)
					format(count_text, sizeof(count_text), "Количество: %d", veh_info[v][inv][count][i]);
			}
			else format(itemname_text, sizeof(itemname_text), "%s (%d)\tКоличество: 1", senderitems(veh_info[v][inv][id][i]), veh_info[v][inv][count][i]);
		}

		format(str, sizeof(str), "%s{AFAFAF}%s%s\t%s\n",str, color, itemname_text, count_text);
 	}
    ShowPlayerDialog(playerid, 90, DIALOG_STYLE_TABLIST_HEADERS,"Инвентарь автомобиля", str, "Выбрать", "Отмена");
	return 1;
}
stock IsMaximumProp(playerid)
{
	new count_prop, max_count_prop = 2;
	for(new pr=0; pr<MAX_PROP; pr++)
	{
		if(prop_info[pr][owner] == character_info[playerid][id] && prop_info[pr][owner] > 0)
			count_prop++;
	}
	if(IsPremium(playerid, PREMIUM_GOLD)) max_count_prop = 7;
	else if(IsPremium(playerid, PREMIUM_SILVER)) max_count_prop = 5;
	else if(IsPremium(playerid, PREMIUM_BRONZE)) max_count_prop = 3;
	if(count_prop >= max_count_prop) return 1;
	else return 0;
}
stock IsMaximumCars(playerid)
{
	new count_cars;
	new MAX_COUNT_CARS = 2;
	if(IsPremium(playerid, PREMIUM_GOLD)) MAX_COUNT_CARS += 6;
	else if(IsPremium(playerid, PREMIUM_SILVER)) MAX_COUNT_CARS += 3;
	else if(IsPremium(playerid, PREMIUM_BRONZE)) MAX_COUNT_CARS += 1;
	for(new v; v<MAX_VEHICLES; v++)
	{
		if(veh_info[v][owner] > 0 && veh_info[v][owner] == character_info[playerid][id])
		{
			count_cars++;
			if(count_cars >= MAX_COUNT_CARS) return 1;
		}
	}	
	return 0;
}
stock GunID(itemid)
{
	switch(itemid)
	{
		case 2..14: return 1;
		case 22: return 1;
		case 25: return 1;
		case 34..45: return 1;
	}
	return 0;
}
stock DrugID(itemid)
{
	switch(itemid)
	{
		case 26..33: return 1;
	}
	return 0;
}
stock GetItemByGun(gunid)
{
	if(gunid == 24) return 3;
	if(gunid == 31) return 4;
	if(gunid == 25) return 5;
	if(gunid == 30) return 6;
	if(gunid == 28) return 7;
	if(gunid == 32) return 8;
	if(gunid == 29) return 9;
	if(gunid == 26) return 10;
    if(gunid == 23) return 11;
	if(gunid == 22) return 12;
	if(gunid == 34) return 13;
	if(gunid == 33) return 14;
	if(gunid == 41) return 84;
	if(gunid == 3) return 20;
	if(gunid == 4) return 21;
	if(gunid == 5) return 22;
	if(gunid == 6) return 118;
	if(gunid == 7) return 24;
	if(gunid == 8) return 119;
	if(gunid == 9) return 115;
	if(gunid == 42) return 116;
	if(gunid == 43) return 160;
	
	return 0;
}
stock DeleteDutyGuns(playerid)
{
	if(character_info[playerid][duty_gun_1] > 0 || character_info[playerid][duty_gun_2] > 0 || character_info[playerid][duty_gun_special] > 0 || character_info[playerid][duty_gun_3] > 0)
	{
		character_info[playerid][duty_gun_1] = 0;
		character_info[playerid][duty_gun_2] = 0;
		character_info[playerid][duty_ammo_2] = 0;
		character_info[playerid][duty_gun_3] = 0;
		character_info[playerid][duty_ammo_3] = 0;
		character_info[playerid][duty_gun_special] = 0;
		if(GetPlayerState(playerid) == 2 || GetPlayerState(playerid) == 3)
		{
			SetPVarInt(playerid, "invwep_fix_car", GetPlayerVehicleID(playerid));
			SetPVarInt(playerid, "invwep_fix_seat", GetPlayerVehicleSeat(playerid));
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x,y,z);
			SetPlayerPos(playerid, x,y,z+0.5);
			UpdateDutyGuns(playerid);
			SetTimerEx("invwep_fix",500,false, "i", playerid);
		}
		else UpdateDutyGuns(playerid);
		SCM(playerid, COLOR_GREEN, "Вы убрали служебное оружие!");
		return 1;
	}
	return 0;
}

stock UpdatePlayerColor(playerid)
{
	if(!IsPlayerLoged(playerid)) 		
		return SetPlayerColor(playerid, COLOR_GRAY);
	
	if(IsAduty(playerid) && player_info[playerid][admin] > 1) 
		return SetPlayerColor(playerid, COLOR_MSGSERVER);
	
	if(IsDuty(playerid))
	{
		if(InFactionId(playerid, LSPD_FACTION) && !GetPVarInt(playerid, "OFF_COLOR")) 
			return SetPlayerColor(playerid, COLOR_LSPD);
		
		if(InFactionId(playerid, SASD_FACTION) && !GetPVarInt(playerid, "OFF_COLOR")) 
			return SetPlayerColor(playerid, COLOR_RCSD);
		
		if(InFactionId(playerid, LSSD_FACTION) && !GetPVarInt(playerid, "OFF_COLOR")) 
			return SetPlayerColor(playerid, COLOR_LSSD);
		
		if(InFactionId(playerid, LSFD_FACTION) && !GetPVarInt(playerid, "OFF_COLOR") || InFactionId(playerid, SAHD_FACTION) && !GetPVarInt(playerid, "OFF_COLOR")) 
			return SetPlayerColor(playerid, COLOR_LSFD);
	}
	if(IsPlayerLoged(playerid)) 		
		return SetPlayerColor(playerid, COLOR_WHITE);
	
	return 1;
}

stock FindCraftItem(playerid, itemid, mycount)
{
	for(new i; i<MAX_CRAFT; i++) if(craft_info[playerid][cItem][i] == itemid && craft_info[playerid][cCount][i] >= mycount) return 1;
	return 0;
}
stock updateCraftInfo(playerid)
{
	for(new i; i<MAX_CRAFT; i++) 
	{
		craft_info[playerid][cItem][i] = 0;
		craft_info[playerid][cCount][i] = 0;
	}
	return 1;
}

SANMSG(text[]/*, bool:ForAll=true*/, COLOR=COLOR_GREEN)
{
	foreach(new p : Player)
	{
		new userid = GetPVarInt(p, "san_off");
		
		if(IsPlayerLoged(p) && !userid)
		{
			SCM(p, COLOR, text);
		}
	}
	return 1;
}

stock Ad_Approved(playerid, msg_id)
{
	if(ads_info[msg_id][owner] == -1) 
		return SCM(playerid, COLOR_TOMATO, "При одобрении объявления произошла ошибка!");
	
	new str[180];
	format(str, sizeof(str), "[Объявление]: %s", ads_info[msg_id][msg]);
	SANMSG(str);
	format(str, sizeof(str), "Редактор: %s Отправитель: %d", sendername(playerid, true), character_info[ads_info[msg_id][owner]][phoneslot]);
	
	SANMSG(str);
	
	ads_info[msg_id][owner] = -1;
	return 1;
}

stock Ad_Reject(playerid, a)
{
	if(ads_info[a][owner] == -1) 
		return SCM(playerid, COLOR_TOMATO, "При отклонении объявления произошла ошибка!");
	
	ads_info[a][owner] = -1;
	return 1;
}



public SetPlayerNameEx(playerid, const __string__[])
{
	if(strlen(__string__) < 3) Kick(playerid);
	else SetPlayerName(playerid, __string__);
}

public OnGetName(playerid)
{
	new rows, _rows, temp[26], str[180]; 
	cache_get_data(rows, _rows);

	if(rows)
	{
		SCM(playerid, COLOR_GREEN, "База данных вернула следующий результат: ");
		cache_get_field_content(0, "login", temp);
		format(str, sizeof(str), "Ник персонажа: {b1b1b1}%s", temp);
		SCM(playerid, COLOR_PAPAYA, str);
		for(new i; i<rows; i++)
		{
			cache_get_field_content(i, "name", temp);
			format(str, sizeof(str), " * %s", temp);
			SCM(playerid, COLOR_PAPAYA, str);
		}
	}
	else SCM(playerid, COLOR_GRAY, "База данных не вернула результата!");
	return 1;
}

public SetToCamera(playerid, objectid)
{
	TogglePlayerSpectating(playerid, 1);
	AttachCameraToDynamicObject(playerid, objectid);
	return 1;
}

public OnLoadTickets(playerid)
{
	new rows, _rows, temp[32]; 
	cache_get_data(rows, _rows);
	for(new i; i<MAX_TICKETS; i++) ticket_info[playerid][i][tId] = 0;
	if(rows)
	{
		for(new i; i<rows; i++)
		{
			cache_get_field_content(i, "id", temp), ticket_info[playerid][i][tId] = strval(temp);
			cache_get_field_content(i, "summ", temp), ticket_info[playerid][i][tSumm] = strval(temp);
			cache_get_field_content(i, "reason", ticket_info[playerid][i][tReason]);
			cache_get_field_content(i, "date", ticket_info[playerid][i][tDate]);
			
			if(i+1 == MAX_TICKETS) break;
		}
	}
}

public OnOffMembers(playerid)
{
    new rows, chname[25], chrank[16], temp[16], _rows, str[64];
	cache_get_data(rows, _rows);
	for(new i; i<rows; i++)
	{
	    cache_get_field_content(i, "name", chname);
	    cache_get_field_content(i, "rank", temp), format(chrank, sizeof(chrank), "%s", faction_ranks[character_info[playerid][faction]][strval(temp)]);
	    format(str, sizeof(str), "%s - %s", chname, chrank);
    	SCM(playerid, COLOR_WHITE, str);
	}
}

public enter_unblock(playerid)
{
	DeletePVar(playerid, "enter_block");
}

public OnDgraf(playerid, i)
{
	new rows, userlogin[26], chname[26], _rows;
	cache_get_data(rows, _rows);
	
	cache_get_field_content(0, "name", chname);
	cache_get_field_content(0, "login", userlogin);
	new str[121+11+64+25+25];
	format(str, sizeof(str), "{ffffff}Номер граффити: %d\nТекст граффити: %s\nСоздал: %s(%s)\n\nВы уверены, что хотите удалить его?", i, graff_info[i][gText], chname, userlogin);
	SetPVarInt(playerid, "graf_i", i);
	GameTextForPlayer(playerid, "~g~OK!", 500, 3);
	ShowPlayerDialog(playerid, 142, DIALOG_STYLE_MSGBOX, "Удалить граффити", str, "Удалить", "Отмена");
	return 1;
}

public OnGetPlayerByMaskId(playerid, maskid)
{
	new rows, _rows, str[64], temp[25];
	cache_get_data(rows, _rows);
	if(rows > 0) 
	{
		format(str, sizeof(str), "MASK_%d:", maskid);
		SCM(playerid, COLOR_GREEN, str);
	}
	else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Маска не найдена!");
	for(new i; i<rows; i++)
	{
		new chid;
		cache_get_field_content(i, "id", temp), chid = strval(temp);
	    cache_get_field_content(i, "name", temp);
		new online = -1;
		foreach(new p : Player) if(character_info[p][id] == chid) online = p; 
		
		if(online > -1) format(str, sizeof(str), "%s (%d)", temp, online);
		else format(str, sizeof(str), "%s (offline)", temp);
		SCM(playerid, COLOR_GRAY, str);
	}
}

public OnCreatePhone(playerid, phonenumber)
{
    new rows[2];
	cache_get_data(rows[0], rows[1]);
	if(!rows[0])
	{
		if(giveitem(playerid, 15, phonenumber))
			LoadContacts(playerid, phonenumber);
	}
	else create_phone(playerid); 
}
public OnCreatePager(playerid, phonenumber)
{
    new rows[2];
	cache_get_data(rows[0], rows[1]);
	if(!rows[0])
	{
		if(giveitem(playerid, 341, phonenumber))
			LoadPager(playerid, phonenumber);
	}
	else create_pager(playerid); 
}

public show_login(playerid)
{
	if(!IsPlayerConnected(playerid)) return printf("  BLOCKED.");
	new str[512], _username_[12];
	GetPVarString(playerid, "_username_", _username_, sizeof(_username_));
	format(str, sizeof(str), "{FFFFFF}Приветствуем вас на {3C8DBC}Classic RolePlay.\n{FFFFFF}Введите пароль от данного аккаунта, чтобы зайти в игру.\n\n{AFAFAF}Внимание! Количество попыток авторизации ограничено.");
	SPD(playerid, 1, DIALOG_STYLE_PASSWORD, "{AFAFAF}Авторизация", str, "Войти", "");
	return 1;
}
public ActorVWFix(playerid)
{
	SetPlayerVw(playerid, 0);
	SetTimerEx("ActorVWFixContinue", 500, false, "i", playerid);
}

public ActorVWFixContinue(playerid)
{
	SetPlayerVw(playerid, -1);
	SetTimerEx("ActorVWFixContinueEx", 500, false, "i", playerid);
}
public ActorVWFixContinueEx(playerid)
{
	SetPVarInt(playerid, "loaded", 1);
	show_login(playerid);
}

public gmx_timer()
{
	if(restart == -60)
	{
		SendRconCommand("gmx");
		return 1;
	}
	else if(restart == -15)
	{
		save_prop();
		save_veh();
		mysql_function_query(dbHandle, "UPDATE characters SET hours_today=0, payday=0", false, "", "");		
		restart--;
	}
	else if(restart == -1)
	{
		for(new p; p<MAX_PLAYERS; p++)
		{
			if(!IsPlayerConnected(p)) continue;
			Kick(p);
			return 1;
		}	  	  
		restart--;
	}
	else if(restart == 0)
	{
		SendRconCommand("hostname "SERVER_NAME_SECOND" | restarting...");
		restart--;
	}
	else
	{
		new str[32];
		if(restart < 0)
		{
			foreach(new p : Player) Kick(p);
		}
		format(str, sizeof(str), "RESTARTING IN %d SECONDS", restart);
		TextDrawSetString(restartingtd[1], str);
		TextDrawShowForAll(restartingtd[0]);
		TextDrawShowForAll(restartingtd[1]);
	    /*foreach(new p : Player)
	  	  GameTextForPlayer(p, str, 1500, 3);*/
	    restart--;
	}
	return 1;
}

public OnGenerateCarNumber(v, vnumber[])
{
	new rows, _rows, qu[128];
	cache_get_data(rows, _rows);
	if(!rows) 
	{
		format(veh_info[v][number], 11, "%s", vnumber);
		format(qu, sizeof(qu), "UPDATE `cars` SET `number`='%s' WHERE id=%d", veh_info[v][number], veh_info[v][id]);
		mysql_function_query(dbHandle, qu, false, "", "");
		UpdateVehParams(v);
	}
	else 		
		GenerateCarNumber(v);
}

public StopUsingAnim(playerid) {
	DeletePVar(playerid, "UsingAnimation");
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
}

public knockout(playerid, time)
{
	if(character_info[playerid][wound] != 1 && character_info[playerid][wound] != 5) return 1;
	else
	{
		
		
		
		set_wound(playerid, 0);
	 	StopUsingAnim(playerid);
	}
 	return 1;
}

public set_wound_free(playerid)
{
	DeletePVar(playerid, "set_wound_block");
}

public set_wound(playerid, mycount)
{
	if(GetPVarInt(playerid, "set_wound_block")) 
		return 0;
	GetPlayerPos(playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]);
    
    character_info[playerid][wound] = mycount;
    
	if(character_info[playerid][wound] == 0)
	{
	    character_info[playerid][accept_death_timer] = 0;
		cmd_sa(playerid);
		
		if(GetPVarInt(playerid, "Flashed"))
		{
			DeletePVar(playerid, "Flashed");
			PlayerTextDrawHide(playerid,FullMonitor[playerid]);
			PlayerTextDrawBoxColor(playerid, FullMonitor[playerid], COLOR_BLACK);
			PlayerTextDrawBackgroundColor(playerid, FullMonitor[playerid], COLOR_BLACK);
		}
	}
	
	if(mycount == 1)
	{
		new Float:health;
		GetPlayerHealth(playerid, health);
		SetPVarFloat(playerid, "knockout_hp", health);
	}
	SetPVarInt(playerid, "set_wound_block", 1);
	SetTimerEx("set_wound_free", 1500, false, "i", playerid);
	return 1;
}

public invwep_fix(playerid)
{
    RemovePlayerAttachedObject(playerid, MAX_ATTACH+1);
	DeletePVar(playerid, "gunpos_bone");
	DeletePVar(playerid, "gunpos_1");
	DeletePVar(playerid, "gunpos_2");
	DeletePVar(playerid, "gunpos_3");
	DeletePVar(playerid, "gunpos_4");
	DeletePVar(playerid, "gunpos_5");
	DeletePVar(playerid, "gunpos_6");

    character_info[playerid][gun] = 0;
    character_info[playerid][ammo] = 0;
	if(GetPVarInt(playerid, "invwep_fix_car") > 0)
	{
		PutInCar(playerid, GetPVarInt(playerid, "invwep_fix_car"), GetPVarInt(playerid, "invwep_fix_seat"));
		DeletePVar(playerid, "invwep_fix_car");
		DeletePVar(playerid, "invwep_fix_seat");
	}
    player_info[playerid][perm] = true;
    return 1;
}

public Spawn(playerid) 
{
	//printf(">>>> %s", character_info[playerid][name]);
	SetPlayerNameEx(playerid, character_info[playerid][name]);
	FreePlayer(playerid, true);
	UpdatePlayerColor(playerid);
	
	PlayerTextDrawHide(playerid, FullMonitor[playerid]);
	if(IssetTicket(playerid)) 
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Внимание! У вас есть неоплаченные штрафы, зарплата уменьшена в два раза!");
	
	if(character_info[playerid][duty] == 1) 
		fmsg(playerid, "вернулся на службу");
	
	SpawnPlayer(playerid);
	player_info[playerid][loged] = true;
	if(player_info[playerid][admin] > 0) 
		ShowPlayerDialog(playerid, 149, DIALOG_STYLE_MSGBOX, "Дежурство", "{ffffff}Вы авторизовались как администратор.\nХотите ли вы выйти на дежурство?\n\n{b1b1b1}Подсказка: Вы сможете покинуть его в любой момент.", "Да", "Нет");
	return 1;
}

public BannedTest(playerid)
{
	new rows[2];
	cache_get_data(rows[0], rows[1]);
	if(!rows[0])
	{
		if(!IsAdmin(playerid, 1, true, false))
		{
			new ipplayer[16];
			GetPlayerIp(playerid, ipplayer, sizeof(ipplayer));
			new lastip[16];
			GetPVarString(playerid, "LastIP", lastip, 16);
			new VKBOT_STATUS = VKBOT_ACTIVATE();
			
			if(player_info[playerid][vkid] <= 0 && VKBOT_STATUS) 
				ChangeVK(playerid);
			
			else if (!CompareStrings(ipplayer, lastip) && VKBOT_STATUS) 
				AuthVK(playerid, ipplayer);
			
			else 
				AuthSucc(playerid);
		}
		else
		{
			AuthSucc(playerid);
		}
	}
	else
	{
	    new bid, time, reason_ban[64], temp[64], count_rows = rows[0];
		for(new i=0; i < count_rows; i++)
		{
		    cache_get_field_content(i, "reason", temp), strmid(reason_ban, temp, 0, strlen(temp), 64);
			cache_get_field_content(i, "time", temp), time = strval(temp);
			cache_get_field_content(i, "id", temp), bid = strval(temp);
        	new str[128];
			if(time > gettime() || time == 0)
			{
				if(time != 0)
				{
					if((time - gettime()) / 86400 > 0)
						format(str, sizeof(str), "> Ваш аккаунт заблокирован. До разблокировки осталось: %d дней", (time - gettime()) / 86400);
					else if((time - gettime()) / 3600 > 0)
					    format(str, sizeof(str), "> Ваш аккаунт заблокирован. До разблокировки осталось: %d часов", (time - gettime()) / 3600);
					else
					    format(str, sizeof(str), "> Ваш аккаунт заблокирован. До разблокировки осталось: %d минут(-ы)!", (time - gettime()) / 60);
				}
				else 
					format(str, sizeof(str), "> Ваш аккаунт заблокирован!");
				
				SCM(playerid, COLOR_TOMATO, str);
				format(str, sizeof(str), "Причина блокировки аккаунта: %s", reason_ban);
				SCM(playerid, COLOR_TOMATO, str);
				SetPVarInt(playerid, "kicked", 1);
				KickEx(playerid);
			}
			else
			{
				new qu[128];
				format(qu, sizeof(qu), "DELETE FROM `ban` WHERE id=%d", bid);
				mysql_function_query(dbHandle, qu, false, "", "");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Ваш аккаунт разблокирован, приятной игры!");
			}
		}
		if(!GetPVarInt(playerid, "kicked")) 
			AuthSucc(playerid);
	}
}

public OnLoadAttachments(playerid)
{
	new rows[2], temp[256]; 
	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
		for(new i; i<rows[0]; i++)
		{
			new aindex, itemid, boneid, Float:X, Float:Y, Float:Z, Float:RX, Float:RY, Float:RZ, Float:SX, Float:SY, Float:SZ,attstatus;
			cache_get_field_content(i, "aindex", temp), aindex = strval(temp);
			cache_get_field_content(i, "iditem", temp), itemid = strval(temp);
			cache_get_field_content(i, "bone", temp), boneid = strval(temp);
			
			cache_get_field_content(i, "X", temp), X = floatstr(temp);
			cache_get_field_content(i, "Y", temp), Y = floatstr(temp);
			cache_get_field_content(i, "Z", temp), Z = floatstr(temp);
			cache_get_field_content(i, "RX", temp), RX = floatstr(temp);
			cache_get_field_content(i, "RY", temp), RY = floatstr(temp);
			cache_get_field_content(i, "RZ", temp), RZ = floatstr(temp);
			cache_get_field_content(i, "SX", temp), SX = floatstr(temp);
			cache_get_field_content(i, "SY", temp), SY = floatstr(temp);
			cache_get_field_content(i, "SZ", temp), SZ = floatstr(temp);
			cache_get_field_content(i, "attstatus", temp), attstatus = strval(temp);
			printf("%d, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f %f", playerid, aindex, itemid, boneid, X, Y, Z, RX, RY, RZ, SX, SY, SZ, attstatus);

			attach_player(playerid, aindex, itemid, boneid, X, Y, Z, RX, RY, RZ, SX, SY, SZ, true);
		}
	}
	attach_player_update(playerid);
}

public OnLoadPrison(playerid)
{
	new rows[2], temp[64]; 
	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
		cache_get_field_content(0, "id", temp), prison_info[playerid][id] = strval(temp);
		cache_get_field_content(0, "chid_officer", temp), prison_info[playerid][chid_officer] = strval(temp);	
		cache_get_field_content(0, "name_officer", prison_info[playerid][name_officer]);
		cache_get_field_content(0, "reason", prison_info[playerid][Reason]);
	}
}

public MyHttpResponse(index, response_code, data[])
{
    new buffer[ 128 ];
    if(response_code == 200) //Запрос успешен?
    { 
        SendClientMessage(index, COLOR_GREEN, "Запрос отправлен!");
    }
    else
    {
        format(buffer, sizeof(buffer), "Сбой в запросе,код ответа: %d", response_code);
		SendClientMessage(index, COLOR_TOMATO, buffer);
    }
} 

public character_check(playerid, userid)
{
	new qu[128];
    format(qu, sizeof(qu), "SELECT * FROM `characters` WHERE `userid`='%i' AND status=2 LIMIT 3", player_info[playerid][id]);
   	mysql_function_query(dbHandle, qu, true, "characters_checkEx", "i", playerid);
}

public character_set(playerid, ch_id)
{
    new qu[211+11+11];
    format(qu, sizeof(qu), "SELECT characters.*, auth_log.ip FROM `characters` JOIN `auth_log` ON auth_log.userid=characters.userid WHERE characters.id='%d' AND auth_log.ingame=1 OR characters.id='%d' ORDER BY  `auth_log`.`id` DESC LIMIT 1", ch_id, ch_id);
   	mysql_function_query(dbHandle, qu, true, "character_setEx", "i", playerid);
}

public character_setEx(playerid)
{
	new temp[256], data_inv[MAX_INV_SLOTS][16], rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
	{
		cache_get_field_content(0, "name", temp), strmid(character_info[playerid][name], temp, 0, strlen(temp), 32);
		cache_get_field_content(0, "skin", temp), character_info[playerid][skin] = strval(temp);
	    cache_get_field_content(0, "id", temp), character_info[playerid][id] = strval(temp);
		cache_get_field_content(0, "sex", temp), character_info[playerid][sex] = strval(temp);
		cache_get_field_content(0, "hospital", temp), character_info[playerid][hospital] = strval(temp);
		cache_get_field_content(0, "newlife", temp), character_info[playerid][newlife] = strval(temp);
	    cache_get_field_content(0, "money", temp), character_info[playerid][money] = strval(temp), GivePlayerMoney(playerid, strval(temp));
		cache_get_field_content(0, "bank", temp), character_info[playerid][bank] = strval(temp);
	    cache_get_field_content(0, "faction", temp), character_info[playerid][faction] = strval(temp);
	    cache_get_field_content(0, "rank", temp), character_info[playerid][rank] = strval(temp);
	    cache_get_field_content(0, "posX", temp), character_info[playerid][posX] = floatstr(temp);
	    cache_get_field_content(0, "posY", temp), character_info[playerid][posY] = floatstr(temp);
	    cache_get_field_content(0, "posZ", temp), character_info[playerid][posZ] = floatstr(temp);
	    cache_get_field_content(0, "VW", temp), character_info[playerid][VW] = strval(temp);
	    cache_get_field_content(0, "Interior", temp), character_info[playerid][Interior] = strval(temp);
	    cache_get_field_content(0, "phoneslot", temp), character_info[playerid][phoneslot] = strval(temp);
	    cache_get_field_content(0, "pager", temp), character_info[playerid][pager] = strval(temp);
	    cache_get_field_content(0, "addiction", temp), character_info[playerid][addiction] = strval(temp);
	    cache_get_field_content(0, "time_addiction", temp), character_info[playerid][time_addiction] = strval(temp);
	    cache_get_field_content(0, "payday", temp), character_info[playerid][payday] = strval(temp);
		cache_get_field_content(0, "hours_today", temp), character_info[playerid][hours_today] = strval(temp);
	    cache_get_field_content(0, "level", temp), character_info[playerid][lvl] = strval(temp);
		cache_get_field_content(0, "driveLic", temp), character_info[playerid][driveLic] = strval(temp);
		cache_get_field_content(0, "driveLicWarn", temp), character_info[playerid][driveLicWarn] = strval(temp);
		cache_get_field_content(0, "gunLic", temp), character_info[playerid][gunLic] = strval(temp);
		cache_get_field_content(0, "flyLic", temp), character_info[playerid][flyLic] = strval(temp);
		if(character_info[playerid][faction]) 
		{
			new count_frac;
			for(new i=0; i<sizeof(factions); i++)
			{
				if(strlen(factions[i][Name]) < 1) 
					continue;
				
				if(i == character_info[playerid][faction])
					count_frac = 1;
			}
			
			if(!count_frac)
			{
				character_info[playerid][duty] = 0;
				character_info[playerid][faction] = 0;
				character_info[playerid][rank] = 0;
				character_info[playerid][duty_gun_1] = 0;
				character_info[playerid][duty_gun_2] = 0;
				character_info[playerid][duty_gun_3] = 0;
				character_info[playerid][duty_ammo_2] = 0;
				character_info[playerid][duty_ammo_3] = 0;
				character_info[playerid][duty_skin] = 1;
			}else{
				cache_get_field_content(0, "duty", temp), character_info[playerid][duty] = strval(temp);
				cache_get_field_content(0, "duty_gun_1", temp), character_info[playerid][duty_gun_1] = strval(temp);
				cache_get_field_content(0, "duty_gun_2", temp), character_info[playerid][duty_gun_2] = strval(temp);
				cache_get_field_content(0, "duty_gun_3", temp), character_info[playerid][duty_gun_3] = strval(temp);
				cache_get_field_content(0, "duty_ammo_2", temp), character_info[playerid][duty_ammo_2] = strval(temp);
				cache_get_field_content(0, "duty_ammo_3", temp), character_info[playerid][duty_ammo_3] = strval(temp);
				cache_get_field_content(0, "duty_skin", temp), character_info[playerid][duty_skin] = strval(temp);
			}
			
			if(character_info[playerid][rank] > 20 || character_info[playerid][rank] < 1)
				character_info[playerid][rank] = 1;
		}

		cache_get_field_content(0, "jail_time", temp), character_info[playerid][jail_time] = strval(temp);
		cache_get_field_content(0, "ajail_time", temp), character_info[playerid][ajail_time] = strval(temp);
		cache_get_field_content(0, "description", temp), format(character_info[playerid][description], 256, "%s", temp);
		cache_get_field_content(0, "date", temp), format(character_info[playerid][birthDate], 18, "%s", temp);
		cache_get_field_content(0, "health", temp), SetPVarFloat(playerid, "hp_resp", floatstr(temp));
		cache_get_field_content(0, "armor", temp), SetPVarFloat(playerid, "arrmor", floatstr(temp));
		cache_get_field_content(0, "su", temp), character_info[playerid][su] = strval(temp);
		cache_get_field_content(0, "su_reason", character_info[playerid][su_reason]);
		cache_get_field_content(0, "ip", temp), SetPVarString(playerid, "LastIP", temp);
	    cache_get_field_content(0, "radio", temp);
		sscanf(temp, "p<|>dd", character_info[playerid][r_channel], character_info[playerid][r_slot]);
	    
		cache_get_field_content(0, "inv", temp);
		cache_get_field_content(0, "voice", character_info[playerid][voice]);
		
		sscanf(temp, "p<|>s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]", data_inv[0], data_inv[1], data_inv[2], data_inv[3], data_inv[4], data_inv[5], data_inv[6], data_inv[7], data_inv[8], data_inv[9], data_inv[10], data_inv[11], data_inv[12], data_inv[13], data_inv[14]);
	    
		for(new i=0; i<MAX_INV_SLOTS; i++) {
	        sscanf(data_inv[i], "p<:>dd",
			character_info[playerid][inv][id][i],
			character_info[playerid][inv][count][i]);
		}
		
		new qu[128];
		
		format(qu, sizeof(qu), "SELECT * FROM ban WHERE userid=%d", player_info[playerid][id]);
		mysql_function_query(dbHandle, qu, true, "BannedTest", "d", playerid);
	}
	else
	{
	    Kick(playerid);
	}
}

public AlarmDisactivate(v)
{
	if(veh_info[v][alarm_timer] > 0) KillTimer(veh_info[v][alarm_timer]);
	veh_info[v][alarm] = false;
	UpdateVehParams(v);
}

public characters_checkEx(playerid, userid) {
	new rows[2], temp[64];
	new str[1024] = "{AFAFAF}Имя персонажа\t{AFAFAF}Статус\n";
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
	{
     	for(new i = 0; i < 3; i++)
     	{
     	    cache_get_field_content(i, "id", temp);
     	    select_character_id[playerid][i] = strval(temp);
     	    if(i == 0 && select_character_id[playerid][i] == 0)
     	    {
     	        KickEx(playerid);
     	        break;
     	    }
     	    if(select_character_id[playerid][i] != 0)
     	    {
     	    	cache_get_field_content(i, "name", temp);
     	    	format(temp, sizeof(temp),"{FFFFFF}%s", temp);
				format(str, sizeof(str), "{FFFFFF}%s%s\t{50A350}Активирован\n", str, temp);
				//strmid(select_character_name[playerid][i], temp, 0, sizeof(temp), sizeof(temp));
			}
			else
			{
				//strmid(select_character_name[playerid][i], "{A9A9A9}Нет персонажа", 0, sizeof(temp), sizeof(temp));
				format(str, sizeof(str), "%s{A9A9A9}Нет персонажа\n", str);
			}
     	}
		//format(str, sizeof(str), "%s\n%s\n%s", select_character_name[playerid][0], select_character_name[playerid][1], select_character_name[playerid][2]);
		SPD(playerid, 3, DIALOG_STYLE_TABLIST_HEADERS, "{AFAFAF}Выбор персонажа", str, "Выбрать", "");
	}
	else
	{
	    SCM(playerid, COLOR_RED, ">{fFFFFF} У вас нет персонажей!");
	    KickEx(playerid);
	}
	return 1;
}

public GunReTest(playerid)
{
	if(GunTest(playerid) && player_info[playerid][admin] < 6) 
		AntiCheat(playerid, "попытался начитерить оружие", ANTICHEAT_DGUN);
}


stock UpdateCrimeLimit(fid=-1) {
	new qu[128], where[8+11]; 
	if(fid == -1) {
	    format(where, sizeof(where), " and id=%d", fid);
	} 

	format(qu, sizeof(qu), "UPDATE factions SET drugs='%d', guns='%d', bulls='%d' WHERE type=3%s", FLIMIT_GANG_DRUGS,FLIMIT_GANG_GUNS,FLIMIT_GANG_BULLS, where);
	mysql_function_query(dbHandle, qu, false, "", "");
		
	format(qu, sizeof(qu), "UPDATE factions SET drugs='%d', guns='%d', bulls='%d' WHERE type=4%s", FLIMIT_MAFIA_DRUGS,FLIMIT_MAFIA_GUNS,FLIMIT_MAFIA_BULLS, where);
	mysql_function_query(dbHandle, qu, false, "", "");
}
public SecondTimerServer()
{
	Anticheat();
	gettime(hour,minute,second);
	
	for(new i; i < MAX_VEHICLES; i ++)
	{
		VehTimer(i);
	}
	
	if(hour == 0 && minute == 0 && second == 0) {
		getdate(year, month, day);

		if(day == 1 || day == 8 || day == 15 || day == 22 || day == 28) {
			UpdateCrimeLimit(-1);
		}
		
	}
	
	if(minute == 0 && second == 0)  {
		SaveMoneyStat();
		SetWorldTime(hour+3);
	}
	
	if(hour == 4 && minute == 0 && second == 0) 
	{
		mysql_function_query(dbHandle, "DELETE FROM admins_stats", false, "", "");
		gmx(90);
	}
	
	for(new i; i<MAX_CCTV; i++)
	{
		if(cctv_info[i][destroyed] > 1) cctv_info[i][destroyed]--;
		if(cctv_info[i][destroyed] == 1) CCTVdestroy(i, 0);
		if(cctv_info[i][timeout] > 0) cctv_info[i][timeout]--;
	}
	
	foreach(new playerid : Player)
	{
		if(!IsPlayerLoged(playerid)) 
			continue;
		
		new payphoneid = GetPayphone(playerid);
		if(payphoneid != -1) {
			if(IsPlayerAtPayphone(playerid, payphoneid) == -1) {
				cmd_h(playerid);
			}
		}		
		if(GetPVarInt(playerid, "InTaxi"))
		{
			if(SpeedVehicle(playerid) > 10)
			{
				if(GetPVarInt(playerid, "InTaxi_Money")+2 > character_info[playerid][money])
				{
					if(!GetPVarInt(playerid, "InTaxi_NoMoney"))
					{
						SetPVarInt(playerid, "InTaxi_NoMoney", 1);
						foreach(new p : Player)
						{
							if(!IsPlayerLoged(p)) continue;
							new v = GetPlayerVehicleID(p);
							if(v > 0 && isPlayerDriver(p) && GetPlayerVehicleID(p) == GetPlayerVehicleID(playerid))
							{
								SCM(p, COLOR_TOMATO, ">{FFFFFF} У пассажира недостаточно денег для оплаты проезда!");
								break;
							}
						}
					}
				}
				else 
					SetPVarInt(playerid, "InTaxi_Money", GetPVarInt(playerid, "InTaxi_Money")+1+random(2));
				
				new str[15];
				format(str, sizeof(str), "~g~%d$", GetPVarInt(playerid, "InTaxi_Money"));
				GameTextForPlayer(playerid, str, 1100, 3);
			}
		}
		if(player_info[playerid][mute] > 0)
		{
			player_info[playerid][mute]--;
			if(player_info[playerid][mute] == 0)
				SCM(playerid, COLOR_GREEN, ">{FFFFFF} Истекло время блокировки чата!");
		}
		
		if(character_info[playerid][VW] != GetPlayerVirtualWorld(playerid))
			SetPlayerVw(playerid,character_info[playerid][VW]);
		
		if(character_info[playerid][Interior] != GetPlayerInterior(playerid))
			SetPlayerInt(playerid,character_info[playerid][Interior]);
		
		if(character_info[playerid][ajail_time] > 0)
		{
			character_info[playerid][ajail_time]--;
			if(character_info[playerid][ajail_time] == 0)
			{
				SetPlayerPos(playerid, 1777.1, -1939.08, 13.558);
				SetPlayerVw(playerid, 0);
				SetPlayerInt(playerid, 0);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы были выпущены из админ тюрьмы!");
			}
		}
		
		if(character_info[playerid][jail_time] > 0)
		{
			character_info[playerid][jail_time]--;
			if(character_info[playerid][jail_time] == 0)
			{
				SetPlayerPosEx(playerid, 1545.9125, -1675.6523, 13.5613, 0, 0);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы были выпущены из тюрьмы!");
			}
		}
		
		if(GetPlayerVirtualWorld(playerid) <= 0 && player_info[playerid][settings][0])
		{
			new Float:x, Float:y, Float:z;
			GetPlayerPos(playerid, x, y, z);
			for(new i = 0; i != sizeof(gSAZones); i++ )
			{
				if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
				{
					new str[21];
					format(str, sizeof(str), "%s", gSAZones[i][SAZONE_NAME]);
					PlayerTextDrawSetString(playerid, Areas[playerid], str);
					break;
				}
			}
		}
		
		character_info[playerid][AFK]++;
		if(GetPVarInt(playerid, "ANTICHEAT_WARNING") >= 1) 
			SetPVarInt(playerid, "ANTICHEAT_WARNING", GetPVarInt(playerid, "ANTICHEAT_WARNING")-1);
		
		if(GetPVarInt(playerid, "SPRINT_PRESSED"))
		{
			if(GetPVarInt(playerid, "breaking_veh_id") > 0 || GetPVarInt(playerid, "breaking_veh_id_boot") > 0) 
			{
				DeletePVar(playerid, "breaking_veh_id");
				DeletePVar(playerid, "breaking_veh_id_boot");
				DeletePVar(playerid, "breaking_veh_processing");
				SCM(playerid, COLOR_TOMATO, ">{FFFFFF} Вы прервали процесс взлома!");
			}
			if(character_info[playerid][drug_effect][type] == 31 || GetPVarInt(playerid, "not_sprint") > 1 || GetPVarInt(playerid, "cuffed"))
			{
				UseAnim(playerid, "PED", "getup_front", 4.0, 0, 0, 0,0,0);
			}	
		}
		
		if(GetPVarInt(playerid, "not_sprint") > 1) 
			SetPVarInt(playerid, "not_sprint", GetPVarInt(playerid, "not_sprint")-1);
		else if(GetPVarInt(playerid, "not_sprint") == 1) 
			DeletePVar(playerid, "not_sprint");
		
		//if(GetPlayerWeapon(playerid) != 0 && GunTest(playerid)) SetTimerEx("GunReTest", 500, false, "i", playerid);

		if(GetPVarInt(playerid, "breaking_veh_id_boot") > 0 || GetPVarInt(playerid, "breaking_veh_id") > 0) 
			VehicleBreaking(playerid);
		
		if(character_info[playerid][drunk_time] > 0)
		{
			SetPlayerDrunkLevel(playerid, 10000);
			character_info[playerid][drunk_time]--;
			if(character_info[playerid][drunk_time] == 0)
				SetPlayerDrunkLevel(playerid, 0);
		}
		
		if(character_info[playerid][wound] == 3 || character_info[playerid][wound] == 1 || character_info[playerid][wound] == 4 || character_info[playerid][wound] == 5)
		{
			if(!PlayerToPoint(2.0, playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ])) 
			{
				SetPlayerPos(playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]);
				if(character_info[playerid][wound] == 1)
				{
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				}
			}
		}
		
		if(character_info[playerid][hospital] > 0)
		{
			character_info[playerid][hospital] --;
		}
		else if(character_info[playerid][hospital] == 0)
		{
			character_info[playerid][hospital] = -1;
			SCM(playerid,COLOR_GREEN,">{ffffff} Ваше время пребывания в госпитале закончилось.");
			
			
			SetPlayerPosEx(playerid,1182.7191,-1323.7123,13.5787,0,0);
			
			
			
			if(GetPVarInt(playerid,"ChangeState_Time") != -1)
			{
				KillTimer(GetPVarInt(playerid,"ChangeState_Time"));
				SetPVarInt(playerid,"ChangeState_Time",-1);
			
			}

			if(GetPVarInt(playerid,"Ranen_") != -1)
			{
				KillTimer(GetPVarInt(playerid,"Ranen_"));
				SetPVarInt(playerid,"Ranen_",-1);
			
			}
		}

		if(character_info[playerid][newlife] > 0)
		{
			new str[24];
			format(str,sizeof(str),"%d",character_info[playerid][newlife]);
			GameTextForPlayer(playerid,str,1000,3);
			character_info[playerid][newlife] --;
		}
		else if(character_info[playerid][newlife] == 0)
		{
			character_info[playerid][newlife] = -1;
			if(character_info[playerid][wound] == 3)
			{
				SetPlayerPosEx(playerid,1091.8773,1927.6952,-77.7611,1,9);
				Dialog_Show(playerid,dSelectDied,DIALOG_STYLE_MSGBOX,"Выберите новую жизнь","{FFFFFF}Вы умерли и через некоторое время оказались в морге. Вам необходимо выбрать судьбу вашего персонажа:\n> CK - ваш персонаж удаляется, и все его имущества тоже.\n> ПК - вам будет необходимо провести в морге 30 минут, после этого вы можете продолжить игру","ПК","CK");
				
			}
			if(character_info[playerid][wound] == 4)
			{
				new rand = random(5);
				switch(rand)
				{
					case 0:
					{
						SetPlayerPosEx(playerid,-2053.9329,-413.9269,1117.0486,0,9);
						SetPlayerFacingAngle(playerid,0.0);
						UseAnim(playerid,"INT_HOUSE","BED_Out_L",4.0,0,1,1,1,1);
					}
					case 1:
					{
						SetPlayerPosEx(playerid,-2053.8438,-406.2692,1117.0486,0,9);
						SetPlayerFacingAngle(playerid,360.0);
						UseAnim(playerid,"INT_HOUSE","BED_Out_L",4.0,0,1,1,1,1);
					}
					case 2:
					{
						SetPlayerPosEx(playerid,-2061.8269,-406.2625,1117.0486,0,9);
						SetPlayerFacingAngle(playerid,360.0);
						UseAnim(playerid,"INT_HOUSE","BED_Out_L",4.0,0,1,1,1,1);
					}
					case 3:
					{
						SetPlayerPosEx(playerid,-2061.5632,-405.0749,1117.0486,0,9);
						SetPlayerFacingAngle(playerid,177.0);
						UseAnim(playerid,"INT_HOUSE","BED_Out_R",4.0,0,1,1,1,1);
					}
					case 4:
					{
						SetPlayerPosEx(playerid,-2047.9225,-405.0458,1117.0486,0,9);
						SetPlayerFacingAngle(playerid,177.0);
						UseAnim(playerid,"INT_HOUSE","BED_Out_R",4.0,0,1,1,1,1);
					}
				
				}
				character_info[playerid][hospital] = 1800;
				
				if(GetPVarInt(playerid,"Ranen_") == -1) SetPVarInt(playerid,"Ranen_",SetTimerEx("Ranen",3000,true,"i",playerid));
			}
			
			
			
			if(GetPVarInt(playerid,"ChangeState_Time") != -1)
			{
				KillTimer(GetPVarInt(playerid,"ChangeState_Time"));
				SetPVarInt(playerid,"ChangeState_Time",-1);
			
			}
			set_wound(playerid, 0);
		}
		if(character_info[playerid][wound] == 1)
		{
			SetPlayerChatBubble(playerid,"(( ПЕРСОНАЖ ОГЛУШЕН! ))",COLOR_TOMATO,10.0,5000);
	
			if(!GetPVarInt(playerid, "UsingAnimation"))
			{
				UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
			}
		}
		
		if(character_info[playerid][wound] == 2)
		{
			new str[200];
			
			format(str, sizeof(str), "(( ДАННЫЙ ПЕРСОНАЖ РАНЕН! Используйте /damages %d для того, чтобы получить информацию. ))", playerid);
			SetPlayerChatBubble(playerid, str,COLOR_TOMATO,10.0,5000);
			
		}
		
		if(character_info[playerid][wound] == 4)
		{
			new str[200];
			
			
			if(character_info[playerid][newlife] == -1)
			{
				format(str, sizeof(str), "(( ПЕРСОНАЖ ТЯЖЕЛО РАНЕН! Используйте /damages %d для того, чтобы получить информацию. ))",playerid);
			}
			else
			{
				format(str, sizeof(str), "(( ПЕРСОНАЖ ТЯЖЕЛО РАНЕН! (%d) Используйте /damages %d для того, чтобы получить информацию. ))",character_info[playerid][newlife],playerid);
			}
			
			SetPlayerChatBubble(playerid, str,COLOR_TOMATO,10.0,5000);
			
			
			
			UseAnim(playerid,"CRACK","crckidle2",3.0,0,1,1,1,0);
			
		}
		
		
		if(character_info[playerid][wound] == 3)
		{
			new str[64];
			if(character_info[playerid][newlife] == -1)
			{
				format(str, sizeof(str), "(( ДАННЫЙ ПЕРСОНАЖ МЕРТВ! ))");
			}
			else
			{
				format(str, sizeof(str), "(( ДАННЫЙ ПЕРСОНАЖ МЕРТВ! (%d) ))", character_info[playerid][newlife]);
			}
			
			SetPlayerChatBubble(playerid,str,COLOR_TOMATO,10.0,5000);
			UseAnim(playerid,"WUZI","CS_Dead_Guy",4.1,0,0,0,1,0);
		}
		
		if(character_info[playerid][wound] == 5)
		{
			SetPlayerChatBubble(playerid,"(( ДАННЫЙ ПЕРСОНАЖ НОКАУТИРОВАН! ))",COLOR_TOMATO,10.0,5000);
	
			if(!GetPVarInt(playerid, "UsingAnimation"))
			{
				UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
			}
		}

		if(GetPVarInt(playerid, "flood") > 0) 
			SetPVarInt(playerid, "flood", GetPVarInt(playerid, "flood")-1);
		//DeletePVar(playerid, "_TimerTest_");
		if(character_info[playerid][AFK] > 5)
		{
			new string[16];
			format( string, 128, "* AFK: %d" ,character_info[playerid][AFK]);
			SetPlayerChatBubble(playerid,string,COLOR_PAPAYA,10.0,1000);
			continue;
		}
		
		if(isPlayerDriver(playerid) && !IsBike(GetPlayerVehicleID(playerid)))
		{
			new speed = SpeedVehicle(playerid);
				
			if(!veh_info[GetPlayerVehicleID(playerid)][fuel]) 
			{ 
				new str[64];
				format(str, sizeof(str), "Fuel: %d",veh_info[GetPlayerVehicleID(playerid)][fuel]); 
				PlayerTextDrawSetString(playerid, Textdraw[playerid][1], str); 
			}			
			
			if(!veh_info[GetPlayerVehicleID(playerid)][lock])
			{
				PlayerTextDrawHide(playerid,Textdraw[playerid][2]);
				PlayerTextDrawColor(playerid, Textdraw[playerid][2], COLOR_TOMATO);
				PlayerTextDrawShow(playerid,Textdraw[playerid][2]);
			}
			else
			{
				PlayerTextDrawHide(playerid, Textdraw[playerid][2]);
				PlayerTextDrawColor(playerid, Textdraw[playerid][2], COLOR_GREEN);
				PlayerTextDrawShow(playerid, Textdraw[playerid][2]);
			}

			if(!veh_info[GetPlayerVehicleID(playerid)][engine])
			{
				PlayerTextDrawHide(playerid,Textdraw[playerid][3]);
				PlayerTextDrawColor(playerid, Textdraw[playerid][3], COLOR_TOMATO);
				PlayerTextDrawShow(playerid, Textdraw[playerid][3]);
			}
			else
			{
				PlayerTextDrawHide(playerid, Textdraw[playerid][3]);
				PlayerTextDrawColor(playerid, Textdraw[playerid][3], COLOR_GREEN);
				PlayerTextDrawShow(playerid, Textdraw[playerid][3]);
			}
			if(veh_info[GetPlayerVehicleID(playerid)][engine])
			{
				if(speed >= 10 && speed < 30) veh_info[GetPlayerVehicleID(playerid)][fuel] -= 0.003;
				if(speed >= 30 && speed < 50) veh_info[GetPlayerVehicleID(playerid)][fuel] -= 0.006;
				if(speed >= 50 && speed < 70) veh_info[GetPlayerVehicleID(playerid)][fuel] -= 0.012;
				if(speed >= 70 && speed < 100) veh_info[GetPlayerVehicleID(playerid)][fuel] -= 0.015;
				if(speed > 100) veh_info[GetPlayerVehicleID(playerid)][fuel] -= 0.018;
			}
		}
		if(isPlayerDriver(playerid))
		{
			new str[64], speed = SpeedVehicle(playerid);
			format(str, sizeof(str), "%d mp/h", speed);
			if(speed > 100)
			{
				new c = CCTVArea(playerid);
				if(c > -1)
				{
					if(random(20) == 1)
					{
						new cctv_str[180];
						new vehicle = GetPlayerVehicleID(playerid);
						format(cctv_str, sizeof(cctv_str), "Зафиксировано превышение скорости %s [%s] (%d mp/h)", VehicleNames[GetVehicleModel(vehicle)-400], veh_info[vehicle][number], speed);
						CCTVmsg(c, cctv_str);
					}
				}
			}
			PlayerTextDrawSetString(playerid, Textdraw[playerid][0], str);
			new Float:health;
			GetVehicleHealth(GetPlayerVehicleID(playerid), health);
			if(health < 999.0) SetPVarFloat(playerid, "OnVehicleRespray_health", health);
		}
		//printf(":: %d", GetPlayerWeapon(playerid));
		if(player_info[playerid][loged] == 0 && GetPlayerAnimationIndex(playerid) == 1231) 
			Kick(playerid);
		if(GetPlayerWeapon(playerid) != 0) 
		{
			if(IsPlayerAttachedObjectSlotUsed(playerid, MAX_ATTACH+1) && !GetPVarInt(playerid, "change_gunattach")) 
				RemovePlayerAttachedObject(playerid, MAX_ATTACH+1);
		}
		else
		{
			if(!IsPlayerAttachedObjectSlotUsed(playerid, MAX_ATTACH+1)) 
			{
				new modelid = Items[GetItemByGun(character_info[playerid][gun])][Model];
				if(GetPVarInt(playerid, "gunpos_bone")) 
					SetPlayerAttachedObject(playerid, MAX_ATTACH+1, modelid, GetPVarInt(playerid, "gunpos_bone"), GetPVarFloat(playerid, "gunpos_1"), GetPVarFloat(playerid, "gunpos_2"), GetPVarFloat(playerid, "gunpos_3"), GetPVarFloat(playerid, "gunpos_4"), GetPVarFloat(playerid, "gunpos_5"), GetPVarFloat(playerid, "gunpos_6"));
				else 
					SetPlayerAttachedObject(playerid, MAX_ATTACH+1, modelid, 6);
			}
		}
		if(character_info[playerid][wound] == 5 || character_info[playerid][wound] == 3 || character_info[playerid][wound] == 4)
		{
			if(!PlayerToPoint(2.0, playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ])) 
			{
				SetPlayerPos(playerid,character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]);
				if(character_info[playerid][wound] == 1)
				{
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				}
			}
		}
		// -------------------------------------- наркотики ---------------------------------------------------------------
		if(character_info[playerid][addiction] < 0) 
			character_info[playerid][addiction] = 0;
		if(character_info[playerid][time_addiction] < 0) 
			character_info[playerid][time_addiction] = 0;
		if(character_info[playerid][time_addiction] > ADDICTION_MAX_TIME) 
			character_info[playerid][time_addiction] = ADDICTION_MAX_TIME;

		if(character_info[playerid][drug_effect][time_effect] > 0)
		{
			/*
			#define 		DRUG_COLOR_RED 				0xFFFF4511
			#define 		DRUG_COLOR_BLUE 			0x1273FF11
			#define 		DRUG_COLOR_LIGHTBLUE 		0x00BFFF11
			#define 		DRUG_COLOR_GREEN 			0x33AA3311
			#define 		DRUG_COLOR_PURPLE			0x8080FF11
			#define 		DRUG_COLOR_DEEP_BLUE 		0x54BDFC11
			#define 		DRUG_COLOR_ORANGE			0xFF800011
			#define 		DRUG_COLOR_YELLOW_GREEN		0x33AA3311
			#define 		DRUG_COLOR_LEMON			0xFFFACD11
			#define			DRUG_COLOR_PAPAYA 			0xF5DEB311			
			*/
			if(character_info[playerid][drug_effect][time_effect] == 1) 
				HideDrugEffect(playerid);
			else 
			{
				HideDrugEffect(playerid);
				switch(character_info[playerid][drug_effect][type])
				{
					case 27: EditDrugEffect(playerid,DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE);
					case 29: EditDrugEffect(playerid,DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE);
					case 31: EditDrugEffect(playerid, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE, DRUG_COLOR_WHITE);
					case 32: EditDrugEffect(playerid, DRUG_COLOR_RED,DRUG_COLOR_RED,DRUG_COLOR_RED,DRUG_COLOR_RED,DRUG_COLOR_RED);
					case 28: EditDrugEffect(playerid, DRUG_COLOR_GREEN,DRUG_COLOR_GREEN,DRUG_COLOR_GREEN,DRUG_COLOR_GREEN,DRUG_COLOR_GREEN);
					case 26:
					{
						new colors[5];
						for(new i; i < 5; i++)
						{
							new r = random(10);
							switch(r)
							{
								case 0: colors[i] = DRUG_COLOR_RED;
								case 1: colors[i] = DRUG_COLOR_BLUE;
								case 2: colors[i] = DRUG_COLOR_LIGHTBLUE;
								case 3: colors[i] = DRUG_COLOR_PURPLE;
								case 4: colors[i] = DRUG_COLOR_DEEP_BLUE;
								case 5: colors[i] = DRUG_COLOR_ORANGE;
								case 6: colors[i] = DRUG_COLOR_YELLOW_GREEN;
								case 7: colors[i] = DRUG_COLOR_LEMON;
								case 8: colors[i] = DRUG_COLOR_PAPAYA;
								case 9: colors[i] = DRUG_COLOR_GREEN;
								default: colors[i] = DRUG_COLOR_WHITE;
							}
						}
						EditDrugEffect(playerid, colors[0], colors[1], colors[2], colors[3], colors[4]);
					}
					case 33:
					{
						new colors[5];
						for(new i; i < 5; i++)
						{
							new r = random(10);
							switch(r)
							{
								case 0: colors[i] = DRUG_COLOR_RED;
								case 1: colors[i] = DRUG_COLOR_BLUE;
								case 2: colors[i] = DRUG_COLOR_LIGHTBLUE;
								case 3: colors[i] = DRUG_COLOR_PURPLE;
								case 4: colors[i] = DRUG_COLOR_DEEP_BLUE;
								case 5: colors[i] = DRUG_COLOR_ORANGE;
								case 6: colors[i] = DRUG_COLOR_YELLOW_GREEN;
								case 7: colors[i] = DRUG_COLOR_LEMON;
								case 8: colors[i] = DRUG_COLOR_PAPAYA;
								case 9: colors[i] = DRUG_COLOR_GREEN;
								default: colors[i] = DRUG_COLOR_WHITE;
							}
						}
						EditDrugEffect(playerid, colors[0], colors[1], colors[2], colors[3], colors[4]);
					}
				}
				ShowDrugEffect(playerid);
			}
			
			character_info[playerid][drug_effect][time_effect]--;
			if(character_info[playerid][drug_effect][time_effect] == 0)
				character_info[playerid][drug_effect][type] = 0;
		}
		if(GetPVarInt(playerid, "_dev_"))
		{
			new string_[64];
			//format(string_, sizeof(string_), "~y~%d / %d", GetPVarInt(playerid, "breaking_veh_id"), GetPVarInt(playerid, "breaking_veh_processing")); 
			format(string_, sizeof(string_), "~y~%f %f %f", character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]);
			GameTextForPlayer(playerid, string_, 1200, 3);
		}
		if(character_info[playerid][wound] == 2 || character_info[playerid][wound] == 3 || character_info[playerid][wound] == 1)
		{
			if(!PlayerToPoint(2.0, playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ])) 
			{
				SetPlayerPos(playerid,character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]);
				if(character_info[playerid][wound] == 1)
				{
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
					UseAnim(playerid,"PED","KD_left",3.0,0,1,1,1,0);
				}
			}
		}
		/*new string_[64];
		format(string_, sizeof(string_), "~y~%d", GetPVarInt(playerid, "ANTICHEAT_WARNING"));
		GameTextForPlayer(playerid, string_, 1200, 3);*/

		if(character_info[playerid][addiction] > ADDICTION_LOW && character_info[playerid][time_addiction] < ADDICTION_MAX_TIME) 
			character_info[playerid][time_addiction]++;
		if(character_info[playerid][time_addiction] == ADDICTION_MAX_TIME-1) 
			SCM(playerid, COLOR_RED, "У вас началась ломка!");
		if(character_info[playerid][time_addiction] == ADDICTION_MAX_TIME)
		{
			if(character_info[playerid][addiction] > ADDICTION_HIGHT)
			{
				if(random(60) == 1 && !GetPVarInt(playerid, "Freezed")) 
					character_info[playerid][drunk_time] = 10;
			}
			if(character_info[playerid][drunk_time] == 0) 
				SetPlayerDrunkLevel(playerid, 3000);
		}
		// -------------------------------------- наркотики ---------------------------------------------------------------
		if(!IsAdmin(playerid, 1, true)) 
			player_info[playerid][atime]++;
		
		if(character_info[playerid][payday] < 3600)
			character_info[playerid][payday]++;
		
		else if(character_info[playerid][payday] >= 3600)
		{
			character_info[playerid][payday] = 0;
			character_info[playerid][lvl]++;
			character_info[playerid][hours_today]++;
			SetPlayerScore(playerid, character_info[playerid][lvl]);

			if(character_info[playerid][lvl] == 5) {
				givemoney(playerid, 6500, "5 hours");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы получили $6500 в качестве стартового капитала!");
			}

			if(character_info[playerid][addiction] > 0) 
				character_info[playerid][addiction] -= 5;
			
			if(character_info[playerid][time_addiction] > 0) 
				character_info[playerid][time_addiction] -= 30;
			
			AdminStatsUpdate(playerid);

			new payday_money = 150+random(101), str[128];

			if(IsPremium(playerid, PREMIUM_OLDGOLD)) 
				payday_money += 0;
			else if(IsPremium(playerid, PREMIUM_GOLD)) 
				payday_money += 500;
			else if(IsPremium(playerid, PREMIUM_SILVER)) 
				payday_money += 250;
			else if(IsPremium(playerid, PREMIUM_BRONZE)) 
				payday_money += 80;
			
			if(InFactionType(playerid, FACTIONTYPE_STATE) || InFactionId(playerid, SAN_FACTION)) 
				payday_money += 100 + (10*character_info[playerid][rank]);
			if(IssetTicket(playerid)) 
				payday_money = payday_money / 2;
			
			// payday_money = payday_money*8;
			
			
			givemoney(playerid, payday_money, "payday", true);

			format(str, sizeof(str), ">{FFFFFF} Вы получили $%d в качестве зарплаты!", payday_money);		
			SCM(playerid, COLOR_MSGSERVER, str);
		}
	}
	return 1;
}

public VehTimer(v)
{
	new Float:vhealth;
	GetVehicleHealth(v, vhealth);
	if(vhealth <= 350) 
	{
		if(veh_info[v][engine] == true) 
			veh_info[v][engine] = false;

		SetVehicleHealth(v, 350);
		UpdateVehParams(v);
	}
	if(veh_info[v][engine] && !IsBike(v)) 
		veh_info[v][fuel] -= (0.01)*2;
	
	if(veh_info[v][destroy_time] > 0) 
	{
		veh_info[v][destroy_time]--;
		if(veh_info[v][destroy_time] == 0) 
		{
			new test_owneronline;
			for(new p; p<MAX_PLAYERS; p++) 
			{
				if(IsPlayerLoged(p) && veh_info[v][owner] == character_info[p][id]) 
				{
					test_owneronline = 1;
					break;
				}
			}
			if(!test_owneronline) 
				DestroyVehicleEx(v);
		}
	}
	if(veh_info[v][fuel] <= 0)
	{
	    veh_info[v][engine] = false;
	    veh_info[v][fuel] = 0;
	    UpdateVehParams(v);
	}
	if(veh_info[v][filling] > 0)
	{
		if(veh_info[v][filling] > 10) veh_info[v][fuel] += 10.0;
		else veh_info[v][fuel] += veh_info[v][filling];
		
		veh_info[v][filling] -= 10.0;
		if(veh_info[v][filling] < 0) veh_info[v][filling] = 0;
	}
}
 
public TimerKickEx(playerid) {
    Kick(playerid);
	return 1;
}

 
public KickEx(playerid) {
	SetPVarInt(playerid, "kicking", 1);
	FreePlayer(playerid, 0);
	PlayerTextDrawShow(playerid, FullMonitor[playerid]);
	SetPlayerChatBubble(playerid, "KICKED", COLOR_RED, 30, 1000);
    SPD(playerid, 2, DIALOG_STYLE_MSGBOX, "Отключение от сервера", "Вы были отключены от сервера!\nИспользуйте /q чтобы выйти из игры. ", "OK", "");
	SetTimerEx("TimerKickEx",1500,false, "i", playerid);
	return 1;
}
 
public player_check(playerid)
{
	new rows[2], temp[32];

 	cache_get_data(rows[0], rows[1]);
	if(rows[0]) {
   		cache_get_field_content(0, "login", temp);
        SetPlayerNameEx(playerid, temp);
		SetPVarString(playerid, "_username_", temp);
		SetPVarInt(playerid, "account_searched", 1);
		show_login(playerid);

	} else {
		
		if(GetPVarInt(playerid, "attempt_auth")) 
			Kick(playerid);
		
		SetPVarInt(playerid, "attempt_auth", 1);
		new str[256];
		format(str, sizeof(str), "{ffffff}Мы не нашли аккаунт/персонажа с данным именем.\n Попробуйте ввести ник еще раз в поле ниже:\n\n{b1b1b1}Для регистрации аккаунта перейдите на %s", SERVER_URL);
		ShowPlayerDialog(playerid, 127, DIALOG_STYLE_INPUT, "{FF6347}Аккаунт не найден!", str, "Ввод", "Отмена");
	}
	AuthorizeCamera(playerid);
	return 1;
}
 
public auth(playerid)
{
	new rows[2], temp[32];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
	  	cache_get_field_content(0, "login", temp), strmid(player_info[playerid][login], temp, 0, strlen(temp), 32);
		cache_get_field_content(0, "id", temp), player_info[playerid][id] = strval(temp);
		//printf("settings string: %s", temp);
		cache_get_field_content(0, "settings", temp);
		sscanf(temp, "p<|>dd", player_info[playerid][settings][0], player_info[playerid][settings][1]);
		foreach(new p : Player)
		{
			if(IsPlayerConnected(p))
			{
				if(player_info[p][id] == player_info[playerid][id] && playerid != p)
				{
				    //printf("Аккаунт уже используется: %d | %d", player_info[p][id], player_info[p][id]);
					SCM(p, COLOR_MSGERROR, ">{FFFFFF} В ваш аккаунт только что попытались войти. (Рекомендуем изменить пароль)");
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Аккаунт уже используется.");
					KickEx(playerid);
					return 1;
				}
			}
		}
		cache_get_field_content(0, "mute", temp), player_info[playerid][mute] = strval(temp);
		cache_get_field_content(0, "vip", temp), player_info[playerid][vip] = strval(temp);
		cache_get_field_content(0, "vip_time", temp), player_info[playerid][vip_time] = strval(temp);
		cache_get_field_content(0, "changename", temp), player_info[playerid][changename] = strval(temp);
		cache_get_field_content(0, "donate", temp), player_info[playerid][donate] = strval(temp);
		cache_get_field_content(0, "admin", temp), player_info[playerid][admin] = strval(temp);
		cache_get_field_content(0, "vkid", temp), player_info[playerid][vkid] = strval(temp);
		cache_get_field_content(0, "passchanged", temp), player_info[playerid][passchanged] = strval(temp);
		if(player_info[playerid][passchanged] == 0) ShowPlayerDialog(playerid, 144, DIALOG_STYLE_PASSWORD, "Смена пароля", "{ffffff}В целях безопасности измените свой пароль, длина пароля должна быть от 8 символов\nВведите новый пароль:", "Ввод", "");
		else character_check(playerid, player_info[playerid][id]);
    }
    else
    {
		if(player_info[playerid][fail_input_password] == 3)
		{
		    SCM(playerid, COLOR_RED, ">{FFFFFF} Вы были кикнуты в целях безопасности аккаунта!");
			KickEx(playerid);
		}
		else
		{
	   		SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Пароль введен неверно!");
	    	player_info[playerid][fail_input_password]++;
	        show_login(playerid);
        }
    }
    return 1;
}
 
public onloadenters()
{
    new rows[2], temp[24];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        for(new i=0; i<rows[0]; i++)
		{
			cache_get_field_content(i, "text", temp),
				format(enter_info[i][Text], sizeof(temp), "%s", temp);
			cache_get_field_content(i, "id", temp), enter_info[i][id] = strval(temp);
			cache_get_field_content(i, "x", temp), enter_info[i][posX] = floatstr(temp);
			cache_get_field_content(i, "y", temp), enter_info[i][posY] = floatstr(temp);
			cache_get_field_content(i, "z", temp), enter_info[i][posZ] = floatstr(temp);
			cache_get_field_content(i, "xe", temp), enter_info[i][posXE] = floatstr(temp);
			cache_get_field_content(i, "ye", temp), enter_info[i][posYE] = floatstr(temp);
			cache_get_field_content(i, "ze", temp), enter_info[i][posZE] = floatstr(temp);
			cache_get_field_content(i, "vworld", temp), enter_info[i][vworld] = strval(temp);
			cache_get_field_content(i, "vworlde", temp), enter_info[i][vworldE] = strval(temp);
			cache_get_field_content(i, "intid", temp), enter_info[i][intid] = strval(temp);
			cache_get_field_content(i, "intide", temp), enter_info[i][intidE] = strval(temp);
			enter_info[i][id3dtext] = CreateDynamic3DTextLabel(enter_info[i][Text], COLOR_GRAY, enter_info[i][posX], enter_info[i][posY], enter_info[i][posZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, enter_info[i][vworld], enter_info[i][intid], -1, 5.5);
			
			//printf("[debug_3d] create enter");
			//enter_info[i][id3dtexte] = CreateDynamic3DTextLabel("Выход", COLOR_LIGHTBLUE, enter_info[i][posXE], enter_info[i][posYE], enter_info[i][posZE], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, enter_info[i][vworldE], enter_info[i][intidE], -1, 5.5);
		}
    }
}
 
public load_furniture()
{

    new rows[2], temp[16];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        new ii;
        for(new i = 0; i < MAX_FURNITURE; i++)
		{
		    cache_get_field_content(i, "id", temp), ii = strval(temp);
			if(furniture[ii][id] == -1)
		    {
			    cache_get_field_content(i, "houseid", temp), furniture[ii][houseid] = strval(temp);
	      		cache_get_field_content(i, "model", temp), furniture[ii][model] = strval(temp);
			    cache_get_field_content(i, "posX", temp), furniture[ii][cordX] = floatstr(temp);
			    cache_get_field_content(i, "posY", temp), furniture[ii][cordY] = floatstr(temp);
			    cache_get_field_content(i, "posZ", temp), furniture[ii][cordZ] = floatstr(temp);
			    cache_get_field_content(i, "posRX", temp), furniture[ii][cordRX] = floatstr(temp);
			    cache_get_field_content(i, "posRY", temp), furniture[ii][cordRY] = floatstr(temp);
			    cache_get_field_content(i, "posRZ", temp), furniture[ii][cordRZ] = floatstr(temp);
				new propid = GetLocalIdProp(furniture[ii][houseid]);
				if(propid <= -1) 
				{
					new qu[128];
					format(qu, sizeof(qu), "DELETE FROM furniture WHERE id=%d", ii);
					mysql_function_query(dbHandle, qu, false, "", "");
					continue;
				}
				furniture[ii][id] = CreateDynamicObject(furniture[ii][model], furniture[ii][cordX],furniture[ii][cordY],furniture[ii][cordZ], furniture[ii][cordRX],furniture[ii][cordRY],furniture[ii][cordRZ] , prop_info[propid][id]+200, Interiors[prop_info[propid][serverint]][Interior]);
				//printf("[Furniture]: %d", Fur_debug++);
   			}
		}
    }
	return 1;
}
 
public load_property(bool:furniture_load)
{
    new rows[2], temp[128], data_inv[MAX_INV_SLOTS][16];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
    {
        new prop_count = 0;
        for(new i = 0; i < MAX_PROP; i++)
		{
			//
			//prop_info[i][PropZone] = -1;	
			if(IsValidDynamicArea(prop_info[i][PropZone])) continue;
		    DestroyDynamicArea(prop_info[i][PropZone]);
		    cache_get_field_content(i, "id", temp);
			if(strval(temp) < 1) continue;
			prop_info[i][id] = strval(temp);
			cache_get_field_content(i, "owner", temp), prop_info[i][owner] = strval(temp);
			cache_get_field_content(i, "days", temp), prop_info[i][Days] = strval(temp);
			if(prop_info[i][Days] <= 0 && prop_info[i][owner] != 0)
			{
				//prop_info[i][Days] = 0;
				//prop_info[i][owner] = 0;
				//printf("house %d droped.", prop_info[i][id]);
			}
			cache_get_field_content(i, "name", prop_info[i][Name]);
			cache_get_field_content(i, "posX", temp), prop_info[i][posX] = floatstr(temp);
			cache_get_field_content(i, "posY", temp), prop_info[i][posY] = floatstr(temp);
			cache_get_field_content(i, "posZ", temp), prop_info[i][posZ] = floatstr(temp);
			cache_get_field_content(i, "price", temp), prop_info[i][price] = strval(temp);
			cache_get_field_content(i, "lock", temp), prop_info[i][lock] = strval(temp);
	  		cache_get_field_content(i, "serverint", temp), prop_info[i][serverint] = strval(temp);
	  		cache_get_field_content(i, "vw", temp), prop_info[i][vworld] = strval(temp);
	  		cache_get_field_content(i, "intid", temp), prop_info[i][intid] = strval(temp);
	  		cache_get_field_content(i, "money", temp), prop_info[i][money] = strval(temp);
	  		cache_get_field_content(i, "type", temp), prop_info[i][type] = strval(temp);
	  		cache_get_field_content(i, "inv", temp);
			//printf("%s", temp);
		    sscanf(temp, "p<|>s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]", data_inv[0], data_inv[1], data_inv[2], data_inv[3], data_inv[4], data_inv[5], data_inv[6], data_inv[7], data_inv[8], data_inv[9], data_inv[10], data_inv[11], data_inv[12], data_inv[13], data_inv[14]);
		    for(new it=0; it<MAX_INV_SLOTS; it++) 
		    {
		        sscanf(data_inv[it], "p<:>dd",
				prop_info[i][inv][id][it],
				prop_info[i][inv][count][it]);
				//printf("[%d] %d:%d | %s\n\n---", prop_info[i][id], prop_info[i][inv][id][it], prop_info[i][inv][count][it], data_inv[it]);
			}
			prop_count++;
	  		//CreateDynamic3DTextLabel(temp, COLOR_WHITE, prop_info[i][posX], prop_info[i][posY], prop_info[i][posZ], 5.0, prop_info[i][vworld], prop_info[i][intid]);
	  		prop_info[i][PropZone] = CreateDynamicSphere(prop_info[i][posX], prop_info[i][posY], prop_info[i][posZ], 1.0, prop_info[i][vworld], prop_info[i][intid]);
	  		//UpdateProp3dText(i);
			for(new gs; gs<sizeof(GasStations); gs++)
			{
				if(GasStations[gs][idprop] != prop_info[i][id]) continue;
				new str[256];
				format(str, sizeof(str), "АЗС #%d\nЧтобы заправиться используйте /fill\nЧтобы купить канистру(%d$) используйте /buyfill\nСтоимость 1 литра: %d$ (Полный бак: %d$)", prop_info[i][id], FILL_PRICE*110, FILL_PRICE, FILL_PRICE*100);
				CreateDynamic3DTextLabel(str, COLOR_GRAY, GasStations[gs][posX], GasStations[gs][posY], GasStations[gs][posZ], 5.0);
				//printf("[debug_3d] create fill");
				break;
			}
			//printf("%d house loaded! (%d)", i, prop_info[i][id]);
  		}
  		//printf("[+] Загружено имущества: %d.", prop_count);
    }
    //else print("[-] Нет имущества для загрузки!");
	
    if(furniture_load)
	{
		new fur_query[512];
		format(fur_query, sizeof(fur_query), "DELETE t1 \
								FROM furniture t1 \
								LEFT JOIN property t2 \
								ON t1.houseid = t2.id \
								WHERE t2.owner = '0'");
		mysql_function_query(dbHandle, fur_query, false, "", "");
		
		
		new house_stat[512];
		format(house_stat, sizeof(house_stat), "UPDATE `property` SET \
												`lock` = '0', \
												`money` = '0', \
												`inv` = '0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|0:0|', \
												`last_time` = '0', \
												`days` = '0' \
												WHERE `owner` = '0'");
		mysql_function_query(dbHandle, house_stat, false, "", "");
		
		new qu[128];
		format(qu, sizeof(qu), "SELECT * FROM `furniture`");
		
		
		
		mysql_function_query(dbHandle, qu, true, "load_furniture", "");
	}
}
 
public PointToPoint(Float:radi, Float:oldposx, Float:oldposy, Float:oldposz, Float:x, Float:y, Float:z)
{
	new Float:tempposx, Float:tempposy, Float:tempposz;
	tempposx = (oldposx -x);
	tempposy = (oldposy -y);
	tempposz = (oldposz -z);
	if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) &&
	((tempposz < radi) && (tempposz > -radi)))
	{
		return 1;
	}
	return 0;

}
 
public PlayerToPoint(Float:radi, playerid, Float:x, Float:y, Float:z)
{
	if(IsPlayerConnected(playerid))
	{
		new Float:oldposx, Float:oldposy, Float:oldposz;
		new Float:tempposx, Float:tempposy, Float:tempposz;
		GetPlayerPos(playerid, oldposx, oldposy, oldposz);
		tempposx = (oldposx -x);
		tempposy = (oldposy -y);
		tempposz = (oldposz -z);
		if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) &&
		((tempposz < radi) && (tempposz > -radi)))
		{
			return 1;
		}
	}
	return 0;

}
 
public save_player(playerid, bool:relog)
{
	new qu[256], settings_str[32], userid = player_info[playerid][id];
	format(settings_str, sizeof(settings_str), "%d|%d", player_info[playerid][settings][0], player_info[playerid][settings][1]);
	format(qu, sizeof(qu), "UPDATE `users` SET `admin`=%d,`vkid`=%d , `settings`='%s', `changename`=%d, `vip_time`=%d, `vip`=%d, `donate`=%d, `mute`=%d WHERE `id`=%d",
	player_info[playerid][admin], player_info[playerid][vkid],
	settings_str,
	player_info[playerid][changename],
	player_info[playerid][vip_time],
	player_info[playerid][vip],
	player_info[playerid][donate],
	player_info[playerid][mute],
	player_info[playerid][id]
	);
	mysql_function_query(dbHandle, qu, false, "", "");
	AdminStatsUpdate(playerid);
	if(relog) 
	{
		ResetPlayerMoney(playerid);
		DeletePVar(playerid, "loaded");
		format(qu, sizeof(qu), "SELECT id, login FROM users WHERE id=%d", userid);
		mysql_function_query(dbHandle, qu, true, "player_check", "i", playerid);
	}
	PlayerDataUpdate(playerid);
}
 
public Freeze(playerid, time)
{
    TogglePlayerControllable(playerid, 0);
    SetPVarInt(playerid, "Freezed", true);
	
	character_info[playerid][lock] = 1;
	SetTimerEx("Unfreeze", time, false, "i", playerid);
}
 
public Unfreeze(playerid)
{
	character_info[playerid][lock] = 0;
	TogglePlayerControllable(playerid, 1);
	DeletePVar(playerid, "Freezed");
}
 
public killmsg_unblock(playerid)
{
	DeletePVar(playerid, "KILLMSG_BLOCK");
}

 
public OnLoadContacts(playerid, phonenumber)
{
    new rows[2], temp[64];
 	cache_get_data(rows[0], rows[1]);
	if(!rows[0])
	{
	    new qu[128];
	    format(qu, sizeof(qu), "INSERT INTO `phone`(`phone`) VALUES (%d)", phonenumber);
		mysql_function_query(dbHandle, qu, true, "", "");

		for(new i=0; i<12; i++)
		{
		    contacts_info[playerid][i][Phone] = 0;
		    contacts_info[playerid][i][Name] = 0;
		}
	}
	else
	{
    	cache_get_field_content(0, "slot1", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][0][Phone], contacts_info[playerid][0][Name]);

    	cache_get_field_content(0, "slot2", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][1][Phone], contacts_info[playerid][1][Name]);

    	cache_get_field_content(0, "slot3", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][2][Phone], contacts_info[playerid][2][Name]);

    	cache_get_field_content(0, "slot4", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][3][Phone], contacts_info[playerid][3][Name]);

    	cache_get_field_content(0, "slot5", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][4][Phone], contacts_info[playerid][4][Name]);

    	cache_get_field_content(0, "slot6", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][5][Phone], contacts_info[playerid][5][Name]);

    	cache_get_field_content(0, "slot7", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][6][Phone], contacts_info[playerid][6][Name]);

    	cache_get_field_content(0, "slot8", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][7][Phone], contacts_info[playerid][7][Name]);

    	cache_get_field_content(0, "slot9", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][8][Phone], contacts_info[playerid][8][Name]);

        cache_get_field_content(0, "slot10", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][9][Phone], contacts_info[playerid][9][Name]);

    	cache_get_field_content(0, "slot11", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][10][Phone], contacts_info[playerid][10][Name]);

    	cache_get_field_content(0, "slot12", temp);
    	sscanf(temp, "p<|>ds[25]", contacts_info[playerid][11][Phone], contacts_info[playerid][11][Name]);
	}
	return 1;
}

public OnLoadPager(playerid, phonenumber)
{
    new rows[2];

 	cache_get_data(rows[0], rows[1]);
	if(!rows[0])
	{
	    new qu[128];
	    format(qu, sizeof(qu), "INSERT INTO `pager`(`id`) VALUES (%d)", phonenumber);
		mysql_function_query(dbHandle, qu, true, "", "");

	}
	return 1;
}

 
public OnSmsHistory(playerid, phonenumber)
{
    if(character_info[playerid][phoneslot] == -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет телфона в слоте!");
	new rows[2], temp[128], str[1028] = "Получатель\tОтправитель\tТекст\tВремя\n";
 	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
	    for(new i=0; i<15; i++)
	    {
	    	cache_get_field_content(i, "phone", temp);
	    	if(!strval(temp)) continue;
	    	format(str, sizeof(str), "%s%s", str, temp);

	    	cache_get_field_content(i, "from", temp),
				format(str, sizeof(str), "%s\t%s", str, temp);
	    	cache_get_field_content(i, "text", temp),
				format(str, sizeof(str), "%s\t%s", str, temp);
	    	cache_get_field_content(i, "time", temp),
				format(str, sizeof(str), "%s\t%s\n", str, temp);
	    }
	    //printf("-- SMS HISTORY --\n\n%s\n-----------------", str);
	    //SPD(playerid, 2, DIALOG_STYLE_MSGBOX, "Отключение от сервера", "Вы были отключены от сервера!\nИспользуйте /q чтобы выйти из игры. ", "OK", "");
	    ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "СМС", str, "Закрыть", "");
	}
	return 1;
}
 
public OnCarsInfoByPlayerid(playerid)
{
	if(TestMDC(playerid)) return 1;
	new rows[2], v_number[11], v_chname[25], temp[64], v_model, v_owner, v_buydate[32];
 	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
		cache_get_field_content(0, "number", temp), format(v_number, sizeof(v_number), "%s", temp);
		cache_get_field_content(0, "model", temp), v_model = strval(temp);
		cache_get_field_content(0, "owner", temp), v_owner = strval(temp);
		cache_get_field_content(0, "name", temp), format(v_chname, sizeof(v_chname), "%s", temp);
		cache_get_field_content(0, "BuyDate", temp), format(v_buydate, sizeof(v_buydate), "%s", temp);
		new str[256];
		format(str, sizeof(str), "{b1b1b1}Информация об автомобиле{FFFFFF}\n");
		format(str, sizeof(str), "%sНомер автомобиля: %s\n", str, v_number);
		format(str, sizeof(str), "%sМарка автомобиля: %s\n", str, VehicleNames[v_model-400]);
		if(v_owner > 0) format(str, sizeof(str), "%sВладелец: %s\n", str, v_chname);
		format(str, sizeof(str), "%sДата покупки: %s\n", str, v_buydate);
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Police MDC System", str, "Закрыть", "");
	}
	else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный номер автомобиля не найден!");
	
	return 1;
}
 
public OnCarsInfo(playerid)
{
	if(TestMDC(playerid)) return 1;
	new rows[2], v_number[11], v_chname[25], temp[64], v_model, v_buydate[32];
 	cache_get_data(rows[0], rows[1]);
	if(rows[0])
	{
		cache_get_field_content(0, "number", temp), format(v_number, sizeof(v_number), "%s", temp);
		cache_get_field_content(0, "model", temp), v_model = strval(temp);
		cache_get_field_content(0, "name", temp), format(v_chname, sizeof(v_chname), "%s", temp);
		cache_get_field_content(0, "BuyDate", temp), format(v_buydate, sizeof(v_buydate), "%s", temp);
		new str[256];
		format(str, sizeof(str), "{b1b1b1}Информация об автомобиле{FFFFFF}\n");
		format(str, sizeof(str), "%sНомер автомобиля: %s\n", str, v_number);
		format(str, sizeof(str), "%sМарка автомобиля: %s\n", str, VehicleNames[v_model-400]);
		format(str, sizeof(str), "%sВладелец: %s\n", str, v_chname);
		format(str, sizeof(str), "%sДата покупки: %s\n", str, v_buydate);
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Police MDC System", str, "Закрыть", "");
	}
	else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный номер автомобиля не найден!");
	
	return 1;
}
 
public OnPropInfo(playerid)
{
	if(TestMDC(playerid)) return 1;
	new rows[2], temp[64], str[256];
 	cache_get_data(rows[0], rows[1]);
	
	if(rows[0])
	{
		format(str, sizeof(str), "{b1b1b1}Информация об имуществе{FFFFFF}\n");
		cache_get_field_content(0, "name", temp);
		new l = GetLocalIdProp(GetPVarInt(playerid, "target_prop"));
		new Float:x = prop_info[l][posX], Float:y = prop_info[l][posY], Float:z = prop_info[l][posZ];
	 	for(new i = 0; i != sizeof(gSAZones); i++ )
	 	{
			if(x >= gSAZones[i][SAZONE_AREA][0] && x <= gSAZones[i][SAZONE_AREA][3] && y >= gSAZones[i][SAZONE_AREA][1] && y <= gSAZones[i][SAZONE_AREA][4])
			{
					
				format(str, sizeof(str), "%sАдрес: %s, %d\n", str, gSAZones[i][SAZONE_NAME], prop_info[l][id]);
				DestroyCheckpoint(playerid);
				SetPVarInt(playerid, "search_checkpoint", 1);
				SetPlayerCheckpoint(playerid, xyz, 3.0);
				break;
			}
		}
		
		format(str, sizeof(str), "%sВладелец: %s\n", str, temp);
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Police MDC System", str, "Закрыть", "");
	}
	else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данное имущество не найдено или оно никому не принадлежит!");
	return 1;
}
 
public timeout_door_null(playerid)
{
	DeletePVar(playerid, "timeout_door");
}
 
public BuySkinMenu(playerid)
{
    ShowMenuForPlayer(buy_skin_menu, playerid);
}
 
public ChatOff(playerid)
{
	cmd_sa(playerid);
	return 1;
}
 
public OnPreload(playerid)
{
	if(character_info[playerid][VW] > 200) 
		character_info[playerid][prop] = character_info[playerid][VW]-200;
	DeletePVar(playerid, "spawning");
    
	PreloadAnimLib(playerid,"BOMBER");
	PreloadAnimLib(playerid,"RAPPING");
	PreloadAnimLib(playerid,"SHOP");
	PreloadAnimLib(playerid,"BEACH");
	PreloadAnimLib(playerid,"SMOKING");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"ON_LOOKERS");
	PreloadAnimLib(playerid,"DEALER");
	PreloadAnimLib(playerid,"CRACK");
	PreloadAnimLib(playerid,"CARRY");
	PreloadAnimLib(playerid,"COP_AMBIENT");
	PreloadAnimLib(playerid,"PARK");
	PreloadAnimLib(playerid,"INT_HOUSE");
	PreloadAnimLib(playerid,"FOOD");
	PreloadAnimLib(playerid,"GHANDS");
	PreloadAnimLib(playerid,"GANGS");
	PreloadAnimLib(playerid,"PED");
	PreloadAnimLib(playerid,"RIOT");
	PreloadAnimLib(playerid,"PAULNMAC");
	PreloadAnimLib(playerid,"FIGHT_B");
	PreloadAnimLib(playerid,"FIGHT_D");
	PreloadAnimLib(playerid,"SPRAYCAN");
	PreloadAnimLib(playerid,"MISC");
	PreloadAnimLib(playerid,"GRAVEYARD");
	PreloadAnimLib(playerid,"POLICE");
	PreloadAnimLib(playerid,"CAR_CHAT");
	PreloadAnimLib(playerid,"SWEET");
	PreloadAnimLib(playerid,"SUNBATHE");
	PreloadAnimLib(playerid,"CRIB");
	PreloadAnimLib(playerid,"BAR");
	PreloadAnimLib(playerid,"DANCING");
	PreloadAnimLib(playerid,"VENDING");
	PreloadAnimLib(playerid,"BSKTBALL");
	PreloadAnimLib(playerid,"BD_FIRE");
	PreloadAnimLib(playerid,"COLT45");
	PreloadAnimLib(playerid,"SILENCED");
	PreloadAnimLib(playerid,"TEC");
	PreloadAnimLib(playerid,"UZI");
	PreloadAnimLib(playerid,"OTB");
	PreloadAnimLib(playerid,"CAR");
	PreloadAnimLib(playerid,"MEDIC");
	PreloadAnimLib(playerid,"WUZI");
	PreloadAnimLib(playerid,"BLOWJOBZ");
	PreloadAnimLib(playerid,"LOWRIDER");
	PreloadAnimLib(playerid,"FINALE");
	PreloadAnimLib(playerid,"CLOTHES");
	character_info[playerid][spawned] = 1;
}
 
public SetPlayerPosAntiCheatEx(playerid, Float:x, Float:y, Float:z, virtualworld, interiorid)
{
	if(!PlayerToPoint(20.0, playerid, x,y,z) || GetPlayerVirtualWorld(playerid) != virtualworld || GetPlayerInterior(playerid) != interiorid)
		AntiCheat(playerid, "был кикнут при несовпадении координат!", ANTICHEAT_COORD);
}
 
public SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, virtualworld, interiorid)
{
	SetPlayerPos(playerid, x,y,z);
	SetPlayerVw(playerid, virtualworld);
	SetPlayerInt(playerid, interiorid);
	return 1;
}
 
public OnPlayerDisconnectEx(playerid, reason)
{
	
	if(character_info[playerid][editobject] > 0 && character_info[playerid][type_editobj] != 3)
	DestroyDynamicObject(character_info[playerid][editobject]);
	
	if(GetPVarType(playerid, "PlacedBB"))
	{
		giveitem(playerid, 142);
		DestroyDynamicObject(GetPVarInt(playerid, "PlacedBB"));
		if(GetPVarType(playerid, "BBArea"))
		{
			foreach(new i : Player)
			{
				if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
				{
					StopAudioStreamForPlayer(i);
					SendClientMessage(i, COLOR_GREEN, ">{FFFFFF} Владелец бумбокса отключился от сервера!");
				}
			}
		}
	}
	
	for(new i; i<10; i++)
	{
		fobj_info[playerid][Model][i] = 0;
		if(IsValidDynamic3DTextLabel(fobj_info[playerid][f3d][i])) 
		{
			//printf("[debug_3d] delete fobj disconnect");
			DestroyDynamic3DTextLabel(fobj_info[playerid][f3d][i]);
			fobj_info[playerid][f3d][i] = Text3D:INVALID_3DTEXT_ID;
		}
		DestroyDynamicObject(fobj_info[playerid][fObj][i]);
		fobj_info[playerid][fObj][i] = 0;
	}
	
	SetPVarInt(playerid, "not_anticheat", 1);
	cmd_unmask(playerid);
	
	if(GetPVarInt(playerid, "local_obj"))
	{
		DestroyDynamicObject(GetPVarInt(playerid, "local_obj"));
		DeletePVar(playerid, "local_obj");
	}
	
	for(new v; v<MAX_VEHICLES; v++) 
	if(veh_info[v][owner] == character_info[playerid][id]) 
	veh_info[v][destroy_time] = 3600;
	
	DeleteMDO(playerid); 
	dialog_data_update(playerid); 
	if(player_info[playerid][loged] == 1)
	{
		new qu[1056], str_inv[128];
		UserSetOnline(playerid, false);
		invwep(playerid);
		new _reason[16];
		new str[128];
		
		if(reason == 0) 
		_reason = "Вылет";
		else if(reason == 1) 
		_reason = "Выход";
		else if(reason == 2) 
		_reason = "Кик/Бан";
		else if(reason == 999) 
		_reason = "Смена персонажа";
		
		format(str, sizeof(str), "отключился от сервера. (%s)", _reason);
		OOCMSG(playerid, str);
		
		if(GetPVarInt(playerid, "cuffed"))
		{
			format(str, sizeof(str), "отключился от сервера в наручниках. (%s)", _reason);
			PlayerLog(playerid, str);
			RemovePlayerAttachedObject(playerid, MAX_ATTACH+2);
		}
		if(GetPVarInt(playerid, "Flashed"))
		{
			format(str, sizeof(str), "отключился от сервера будучи ослеплен. (%s)", _reason);
			PlayerLog(playerid, str);
		}
  		for(new i=0; i<MAX_INV_SLOTS; i++) {
			if(i == MAX_INV_SLOTS-1) 
			format(str_inv, sizeof(str_inv), "%s%d:%d",str_inv, character_info[playerid][inv][id][i],character_info[playerid][inv][count][i]);
			else 
			format(str_inv, sizeof(str_inv), "%s%d:%d|",str_inv, character_info[playerid][inv][id][i],character_info[playerid][inv][count][i]);
		}
		
		format(qu, sizeof(qu), "UPDATE characters SET hospital=%d,newlife=%d,skin=%d, money=%d,bank=%d,faction=%d,rank=%d,phoneslot=%d,posX=%f,posY=%f,posZ=%f,VW=%d,Interior=%d,inv='%s',addiction='%d', time_addiction='%d', payday='%d', hours_today='%d', level='%d', radio='%d|%d', driveLic=%d, driveLicWarn=%d, gunLic=%d, flyLic=%d, duty=%d, duty_gun_1=%d, duty_gun_2=%d, duty_ammo_2=%d,duty_gun_3=%d, duty_ammo_3=%d,duty_skin=%d, ajail_time=%d, jail_time=%d, health=%f, armor=%f WHERE id=%d",
		character_info[playerid][hospital],
		character_info[playerid][newlife],
		character_info[playerid][skin],
		character_info[playerid][money],
		character_info[playerid][bank],
		character_info[playerid][faction],
		character_info[playerid][rank],
		character_info[playerid][phoneslot],
		character_info[playerid][posX],
		character_info[playerid][posY],
		character_info[playerid][posZ],
		character_info[playerid][VW], 
		character_info[playerid][Interior],
		str_inv,
		character_info[playerid][addiction],
		character_info[playerid][time_addiction],
		character_info[playerid][payday],
		character_info[playerid][hours_today],
  		character_info[playerid][lvl],
  		character_info[playerid][r_channel],character_info[playerid][r_slot],
		
		character_info[playerid][driveLic],character_info[playerid][driveLicWarn],
		character_info[playerid][gunLic],character_info[playerid][flyLic],
		character_info[playerid][duty],
		character_info[playerid][duty_gun_1], character_info[playerid][duty_gun_2], character_info[playerid][duty_ammo_2], character_info[playerid][duty_gun_3], character_info[playerid][duty_ammo_3], character_info[playerid][duty_skin],
		character_info[playerid][ajail_time],character_info[playerid][jail_time], character_info[playerid][Health], GetPVarFloat(playerid, "arrmor"),
		character_info[playerid][id]
		);
		mysql_function_query(dbHandle, qu, true, "", "");	
		if(reason == 999) 
		save_player(playerid, true);
		else 
		save_player(playerid, true);
	}
	else 
	PlayerDataUpdate(playerid);
}

 
public AuthTimeout(playerid)
{
	if(!IsPlayerLoged(playerid) && !GetPVarInt(playerid, "bot"))
	{
		SCM(playerid, COLOR_MSGSERVER, "> {FFFFFF}Вы должны авторизоваться в течении четырех минут!");
		KickEx(playerid);
	}
}
 
public OnLoadFactions()
{
	new rows[2], temp[64], f_id;
 	cache_get_data(rows[0], rows[1]);
	new max_factions = rows[0];
	for(new i; i<MAX_FACTIONS; i++) format(factions[f_id][Name], 25, "");
	if(rows[0])
	{
	    for(new i=0; i<max_factions; i++)
	    {
	        cache_get_field_content(i, "id", temp), f_id = strval(temp);
	        if(f_id <= 0) continue;
	    	cache_get_field_content(i, "name", temp), format(factions[f_id][Name], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "leader", temp), factions[f_id][Leader] = strval(temp);
	    	cache_get_field_content(i, "type", temp), factions[f_id][Type] = strval(temp);
	    	cache_get_field_content(i, "drugs", temp), factions[f_id][drugs] = strval(temp);
	    	cache_get_field_content(i, "guns", temp), factions[f_id][guns] = strval(temp);
	    	cache_get_field_content(i, "freeze", temp), factions[f_id][FactionFreeze] = strval(temp);
			cache_get_field_content(i, "bank", temp), factions[f_id][bank] = strval(temp);
	    	cache_get_field_content(i, "Rank1", temp), format(faction_ranks[f_id][1], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank2", temp), format(faction_ranks[f_id][2], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank3", temp), format(faction_ranks[f_id][3], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank4", temp), format(faction_ranks[f_id][4], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank5", temp), format(faction_ranks[f_id][5], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank6", temp), format(faction_ranks[f_id][6], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank7", temp), format(faction_ranks[f_id][7], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank8", temp), format(faction_ranks[f_id][8], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank9", temp), format(faction_ranks[f_id][9], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank10", temp), format(faction_ranks[f_id][10], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank11", temp), format(faction_ranks[f_id][11], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank12", temp), format(faction_ranks[f_id][12], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank13", temp), format(faction_ranks[f_id][13], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank14", temp), format(faction_ranks[f_id][14], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "Rank15", temp), format(faction_ranks[f_id][15], sizeof(temp), "%s", temp);
			cache_get_field_content(i, "Rank16", temp), format(faction_ranks[f_id][16], sizeof(temp), "%s", temp);
			cache_get_field_content(i, "Rank17", temp), format(faction_ranks[f_id][17], sizeof(temp), "%s", temp);
			cache_get_field_content(i, "Rank18", temp), format(faction_ranks[f_id][18], sizeof(temp), "%s", temp);
			cache_get_field_content(i, "Rank19", temp), format(faction_ranks[f_id][19], sizeof(temp), "%s", temp);
			cache_get_field_content(i, "Rank20", temp), format(faction_ranks[f_id][20], sizeof(temp), "%s", temp);
	    	cache_get_field_content(i, "invite_rank", temp), factions[f_id][invite_rank] = strval(temp);
	    	cache_get_field_content(i, "uninvite_rank", temp), factions[f_id][uninvite_rank] = strval(temp);
	    	cache_get_field_content(i, "giverank_rank", temp), factions[f_id][giverank_rank] = strval(temp);
	    	cache_get_field_content(i, "bulls", temp), factions[f_id][bulls] = strval(temp);
			printf("FACTION LOADED: %s", factions[f_id][Name]);
		}
	}
}
 
public OnLoadDoors()
{
	new rows[2], temp[64], f_id;
	cache_get_data(rows[0], rows[1]);
	new max_doors = rows[0];
	if(rows[0])
	{
	    for(new i=0; i<max_doors; i++)
		{
  			cache_get_field_content(i, "id", temp), f_id = strval(temp);
	        if(f_id <= 0) continue;
	        if(door[f_id][Model] > 0) DestroyDynamicObject(door[f_id][Model]);
	        cache_get_field_content(i, "posX", temp), door[f_id][posX] = floatstr(temp);
			cache_get_field_content(i, "posY", temp), door[f_id][posY] = floatstr(temp);
			cache_get_field_content(i, "posZ", temp), door[f_id][posZ] = floatstr(temp);
			cache_get_field_content(i, "posRX", temp), door[f_id][posRX] = floatstr(temp);
			cache_get_field_content(i, "posRY", temp), door[f_id][posRY] = floatstr(temp);
			cache_get_field_content(i, "posRZ", temp), door[f_id][posRZ] = floatstr(temp);

	        cache_get_field_content(i, "posXS", temp), door[f_id][posXS] = floatstr(temp);
			cache_get_field_content(i, "posYS", temp), door[f_id][posYS] = floatstr(temp);
			cache_get_field_content(i, "posZS", temp), door[f_id][posZS] = floatstr(temp);
			cache_get_field_content(i, "posRXS", temp), door[f_id][posRXS] = floatstr(temp);
			cache_get_field_content(i, "posRYS", temp), door[f_id][posRYS] = floatstr(temp);
			cache_get_field_content(i, "posRZS", temp), door[f_id][posRZS] = floatstr(temp);

			cache_get_field_content(i, "interior", temp), door[f_id][intid] = strval(temp);
			cache_get_field_content(i, "virtualworld", temp), door[f_id][vworld] = strval(temp);
			cache_get_field_content(i, "faction", temp), door[f_id][factionid] = strval(temp);
			cache_get_field_content(i, "objectid", temp);

			door[f_id][Model] = CreateDynamicObject(strval(temp), door[f_id][posX],door[f_id][posY],door[f_id][posZ], door[f_id][posRX], door[f_id][posRY], door[f_id][posRZ], door[f_id][vworld], door[f_id][intid]);
		}
	}
}
 
public AchatOld(playerid, code)
{
	for(new i; i<MAX_ACHAT; i++)
	{
		if(achat_info[i][Playerid] == playerid && achat_info[i][Code] == code)
		{
			achat_info[i][New] = false;
		}
	}
	UpdateAchat();
}
 
public OnCheatDetected(playerid, ip_address[], ttype, code)
{
	if(GetPVarInt(playerid, "spawning"))
	{
		if(code == 2 && GetPlayerInterior(playerid) > 0) 
			return print("SPAWNING...");
		else if(code == 5) 
			return print("SPAWNING...");
	}
	
	if(player_info[playerid][loged] != 1) 
		return 0;
	if(GetPVarInt(playerid, "kicking")) 
		return 1;
	/*if(player_info[playerid][id] == 1 || player_info[playerid][id] == 2) return 1;
	if(code != 034)	SetPVarInt(playerid, "ANTICHEAT_WARNING", GetPVarInt(playerid, "ANTICHEAT_WARNING")+20);
	if(GetPVarInt(playerid, "ANTICHEAT_WARNING") > 40 || code == 031 || code == 008 || code == 021 || code == 039)
	{
		AntiCheat(playerid, "был кикнут по подозрению в читерстве", code);
		return 1;
	}
	else if(code == 002) AntiCheat(playerid, "подозревается в чите на перемещение!", 002, false);
	else if(code == 011) AntiCheat(playerid, "подозревается в чите на починку автомобилей!", 011, false);
	else if(code == 049) SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF}Замечена подозрительная активность вашего аккаунта! Если вы будете продолжать, вы будете кикнуты!");*/
	new warning_level;
	switch(code)
	{
		case 4:
		{
			new floatxyz;
			GetPlayerPos(playerid, xyz);
			SetPlayerPos(playerid, x,y,z+2);
		}
		case 15: warning_level = 45;
		case 39: warning_level = 45;
		case 59: warning_level = 10;
		default: warning_level = 18;
	}
	SetPVarInt(playerid, "ANTICHEAT_WARNING", GetPVarInt(playerid, "ANTICHEAT_WARNING")+warning_level);
	if(!GetPVarInt(playerid, "not_anticheat"))
	{
		if(GetPVarInt(playerid, "ANTICHEAT_WARNING") >= 40) 
			AntiCheat(playerid, "был кикнут по подозрению в читерстве", code);
		else 
		{
			AddAchat(playerid, code);
			//AntiCheat(playerid, "подозревается в читерстве", code, false);
		}
	}
	return 1;
}
 
public OnLoadCars(playerid)
{
	//CreateVehicleEx(carid, Float:X, Float:Y, Float:Z, Float:Angle, col1, col2, Float:vfuel, bool:vlock, bool:vengine, bool:vwindows, bool:vlights, vid=-1, vowner=-1)
	new rows, _rows, temp[256], v_modelid, v_id, v_owner, v_color1, v_color2, Float:v_posX, Float:v_posY, Float:v_posZ, Float:v_Angle, Float:v_fuel, Float:v_health, v_vworld, v_number[11], data_inv[MAX_INV_SLOTS][16];
	cache_get_data(rows, _rows);
	if(rows)
	{
		for(new i; i<rows; i++)
		{
			cache_get_field_content(i, "id", temp), v_id = strval(temp);
			for(new it; it<MAX_VEHICLES; it++) if(veh_info[it][id] == v_id) continue;
			cache_get_field_content(i, "model", temp), v_modelid = strval(temp);
			cache_get_field_content(i, "number", temp), format(v_number, sizeof(v_number), "%s", temp);
			cache_get_field_content(i, "owner", temp), v_owner = strval(temp);
			cache_get_field_content(i, "col1", temp), v_color1 = strval(temp);
			cache_get_field_content(i, "col2", temp), v_color2 = strval(temp);
			cache_get_field_content(i, "posX", temp), v_posX = floatstr(temp);
			cache_get_field_content(i, "posY", temp), v_posY = floatstr(temp);
			cache_get_field_content(i, "posZ", temp), v_posZ = floatstr(temp);
			cache_get_field_content(i, "Angle", temp), v_Angle = floatstr(temp);
			cache_get_field_content(i, "health", temp), v_health = floatstr(temp);
			cache_get_field_content(i, "fuel", temp), v_fuel = floatstr(temp);
			cache_get_field_content(i, "virtualworld", temp), v_vworld = strval(temp);
			cache_get_field_content(i, "inv", temp);
			sscanf(temp, "p<|>s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]s[16]", data_inv[0], data_inv[1], data_inv[2], data_inv[3], data_inv[4], data_inv[5], data_inv[6], data_inv[7], data_inv[8], data_inv[9], data_inv[10], data_inv[11], data_inv[12], data_inv[13], data_inv[14]);
			if(v_owner == -1)
			{
				
			}
			new v = CreateVehicleEx(v_modelid, 
									v_posX, 
									v_posY, 
									v_posZ, 
									v_Angle, 
									v_vworld, 
									v_color1,  
									v_color2, 
									v_fuel, 
									true, 
									false, 
									true, 
									false, 
									v_id, 
									v_owner, 
									v_number);
									
			
			for(new s=0; s<MAX_INV_SLOTS; s++) 
			{
				veh_info[v][inv][id][s] = 0;
				veh_info[v][inv][count][s] = 0;
				sscanf(data_inv[s], "p<:>dd",
				veh_info[v][inv][id][s],
				veh_info[v][inv][count][s]);
				//printf("%d > %d > %d > %d:%d", v, i, s, veh_info[i][inv][id][s], veh_info[i][inv][count][s]);
			}
			
			if(playerid >= 0)
			{
				PutInCar(playerid, v, 0);
			}
			
			cache_get_field_content(i, "alarm_type", temp), veh_info[v][alarm_type] = strval(temp);
			cache_get_field_content(i, "lock_type", temp), veh_info[v][lock_type] = strval(temp);
			new istaxi;
			cache_get_field_content(i, "taxi", temp), istaxi = strval(temp);
			cache_get_field_content(i, "wheels", temp), veh_info[v][wheels] = strval(temp);
			if(istaxi) TaxiOn(v);
			SetVehicleHealth(v, v_health);
			UpdateTune(v);
		}
	}
	return 1;
}
 
public OnLoadGraff()
{
	new rows, _rows, temp[32];
	new text[32], color[8], font[32], fontsize, chid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
	cache_get_data(rows, _rows);
	for(new i; i<rows; i++)
	{
		cache_get_field_content(i, "text", temp), format(text, 32, "%s", temp);
		cache_get_field_content(i, "color", temp), format(color, 8, "%s", temp);
		cache_get_field_content(i, "font", temp), format(font, 32, "%s", temp);
		cache_get_field_content(i, "fontsize", temp), fontsize = strval(temp);
		cache_get_field_content(i, "owner", temp), chid = strval(temp);
		
		cache_get_field_content(i, "posX", temp), x = floatstr(temp);
		cache_get_field_content(i, "posY", temp), y = floatstr(temp);
		cache_get_field_content(i, "posZ", temp), z = floatstr(temp);
		cache_get_field_content(i, "posRX", temp), rx = floatstr(temp);
		cache_get_field_content(i, "posRY", temp), ry = floatstr(temp);
		cache_get_field_content(i, "posRZ", temp), rz = floatstr(temp);
		cache_get_field_content(i, "id", temp);
		
		if(!SearchGraffId(strval(temp))) 
			CreateGraff(text, strval(temp), color, font, fontsize, chid, x,y,z,rx,ry,rz); 
	}
	return 1;
}
 
public OnAPBList(playerid, page)
{
	new rows, _rows, temp[24], str[180];
	cache_get_data(rows, _rows);
	if(!rows) 
	{
		GameTextForPlayer(playerid, "~g~EMPTY!", 1000, 3);
		return SCM(playerid, COLOR_GRAY, "Пустая страница");
	}
	SCM(playerid, COLOR_GRAY, "_________________ APB _________________");
	
    new apb_id, apb_desc[64], apb_violation[64];
	for(new i=rows-1; i>=0; i--)
	{
		cache_get_field_content(i, "id", temp), apb_id = strval(temp);
		cache_get_field_content(i, "desc", apb_desc);
		cache_get_field_content(i, "violation", apb_violation);
		format(str, sizeof(str), "[%d]: %s | %s", apb_id, apb_desc, apb_violation);
		SCM(playerid, COLOR_WHITE, str);
	}
	GameTextForPlayer(playerid, "~g~LOADED", 1000, 3);
	format(str, sizeof(str), "____________________________[%d]__", page);
	SCM(playerid, COLOR_GRAY, str);
	return 1;
}
 
public OnAPBShow(playerid, apb_number)
{
	new rows, _rows, str[180];
	cache_get_data(rows, _rows);
	if(!rows) 
	{
		format(str, sizeof(str), ">{FFFFFF} Запись не найдена.", apb_number);
		return SCM(playerid, COLOR_MSGERROR, str);
	}
	new apb_name[25], apb_desc[64], apb_violation[64], apb_date[24];
	cache_get_field_content(0, "desc", apb_desc);
	cache_get_field_content(0, "violation", apb_violation);
	cache_get_field_content(0, "date", apb_date);
	cache_get_field_content(0, "name", apb_name);
	format(str, sizeof(str), "_________________ All Points Bulletins #%d _________________", apb_number);
	SCM(playerid, COLOR_GRAY, str);
	format(str, sizeof(str), "Описание: {ffffff}%s", apb_desc);
	SCM(playerid, COLOR_GRAY, str);
	format(str, sizeof(str), "Преступление: {ffffff}%s", apb_violation);
	SCM(playerid, COLOR_GRAY, str);
	format(str, sizeof(str), "Дата: {ffffff}%s", apb_date);
	SCM(playerid, COLOR_GRAY, str);
	format(str, sizeof(str), "_________________ СОЗДАЛ: {ffffff}%s{b1b1b1} _________________", apb_name);
	SCM(playerid, COLOR_GRAY, str);
	return 1;
}
 
public OnAPBDelete(playerid, apb_number)
{
	new rows, _rows;
	cache_get_data(rows, _rows);
	if(!rows) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Такой записи не существует!");
	
	new qu[128], str[128];
	format(str, sizeof(str), "удаляет APB #%d", apb_number);
	fmsg(playerid, str);
	format(qu, sizeof(qu), "DELETE FROM `apb` WHERE id=%d", apb_number);
	mysql_function_query(dbHandle, qu, false, "", "");
	SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} ы удалили запись!");
	return 1;
}
 
public OnLoadCCTV()
{
	for(new i; i<MAX_CCTV; i++)
	{
		if(IsValidDynamic3DTextLabel(cctv_info[i][a3d])) 
		{
			//printf("[debug_3d] delete cctv");
			DestroyDynamic3DTextLabel(cctv_info[i][a3d]);
			cctv_info[i][a3d] = Text3D:INVALID_3DTEXT_ID;
		}
		if(cctv_info[i][aObj] > 0)
		{
			DestroyDynamicObject(cctv_info[i][aObj]);
			cctv_info[i][aObj] = 0;
			
			cctv_info[i][id] = 0;
			cctv_info[i][posX] = 0.0;
			cctv_info[i][posY] = 0.0;
			cctv_info[i][posZ] = 0.0;
			cctv_info[i][posRX] = 0.0;
			cctv_info[i][posRY] = 0.0;
			cctv_info[i][posRZ] = 0.0;
			cctv_info[i][VW] = 0;
			cctv_info[i][Interior] = 0;
		}
	}
	new rows, _rows, temp[24];
	cache_get_data(rows, _rows);
	if(!rows) return 1;
	for(new i; i<rows; i++)
	{
		cache_get_field_content(i, "id", temp), cctv_info[i][id] = strval(temp);
		cache_get_field_content(i, "desc", cctv_info[i][description]);
		cache_get_field_content(i, "posX", temp), cctv_info[i][posX] = floatstr(temp);
		cache_get_field_content(i, "posY", temp), cctv_info[i][posY] = floatstr(temp);
		cache_get_field_content(i, "posZ", temp), cctv_info[i][posZ] = floatstr(temp);
		cache_get_field_content(i, "posRX", temp), cctv_info[i][posRX] = floatstr(temp);
		cache_get_field_content(i, "posRY", temp), cctv_info[i][posRY] = floatstr(temp);
		cache_get_field_content(i, "posRZ", temp), cctv_info[i][posRZ] = floatstr(temp);
		cache_get_field_content(i, "VW", temp), cctv_info[i][VW] = strval(temp);
		cache_get_field_content(i, "Interior", temp), cctv_info[i][Interior] = strval(temp);
		cctv_info[i][a3d] = CreateDynamic3DTextLabel("CAM", COLOR_GRAY_EE, cctv_info[i][posX],cctv_info[i][posY],cctv_info[i][posZ], 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, cctv_info[i][VW]);
		//printf("[debug_3d] create cctv");
		cctv_info[i][aObj] = CreateDynamicObject(CCTV_OBJ, cctv_info[i][posX],cctv_info[i][posY],cctv_info[i][posZ], cctv_info[i][posRX],cctv_info[i][posRY],cctv_info[i][posRZ], cctv_info[i][VW], cctv_info[i][Interior]);
		CCTVdestroy(i, 0);
	}
	return 1;
}
 
public OnLoadATM()
{
	new rows, _rows, temp[24];
	cache_get_data(rows, _rows);
	if(!rows) return 1;
	for(new i; i<rows; i++)
	{
		if(IsValidDynamic3DTextLabel(atm_info[i][a3d])) 
		{
			//printf("[debug_3d] delete atm");			
			DestroyDynamic3DTextLabel(atm_info[i][a3d]);
			atm_info[i][a3d] = Text3D:INVALID_3DTEXT_ID;
		}
		if(atm_info[i][aObj] > 0)
		{
			DestroyDynamicObject(atm_info[i][aObj]);
			atm_info[i][aObj] = 0;
		}
		cache_get_field_content(i, "id", temp), atm_info[i][id] = strval(temp);
		cache_get_field_content(i, "posX", temp), atm_info[i][posX] = floatstr(temp);
		cache_get_field_content(i, "posY", temp), atm_info[i][posY] = floatstr(temp);
		cache_get_field_content(i, "posZ", temp), atm_info[i][posZ] = floatstr(temp);
		cache_get_field_content(i, "posRX", temp), atm_info[i][posRX] = floatstr(temp);
		cache_get_field_content(i, "posRY", temp), atm_info[i][posRY] = floatstr(temp);
		cache_get_field_content(i, "posRZ", temp), atm_info[i][posRZ] = floatstr(temp);
		cache_get_field_content(i, "vworld", temp), atm_info[i][VW] = strval(temp);
		atm_info[i][a3d] = CreateDynamic3DTextLabel("ATM банкомат\n{FFFFFF}Нажмите 'ALT' чтобы воспользоваться ATM сервисами.", COLOR_INFO, atm_info[i][posX],atm_info[i][posY],atm_info[i][posZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, atm_info[i][VW]);
		//printf("[debug_3d] create atm");
		atm_info[i][aObj] = CreateDynamicObject(ATM_OBJ, atm_info[i][posX],atm_info[i][posY],atm_info[i][posZ], atm_info[i][posRX],atm_info[i][posRY],atm_info[i][posRZ], atm_info[i][VW]);
	}
	return 1;
}
 
public OnLoadArecords(playerid)
{
	new rows, _rows, temp[64]; 
	new Id, String[64], Date[24], str[64+18+11+5];
	cache_get_data(rows, _rows);
	
	if(rows)
	{
		//printf("MAX: %d", rows);
		SCM(playerid, COLOR_GRAY, "__________________________________");
		for(new i; i<rows; i++)
		{		
			cache_get_field_content(i, "id", temp), Id = strval(temp);
			cache_get_field_content(i, "time", Date);
			cache_get_field_content(i, "text", String);
			
			format(str, sizeof(str), "%d: %s {b1b1b1}(%s)", Id, String, Date);
			SCM(playerid, COLOR_WHITE, str);
		}
		SCM(playerid, COLOR_GRAY, "__________________________________");
		GameTextForPlayer(playerid, "~g~LOADED", 1000, 3);
		return 1;
	}
	else GameTextForPlayer(playerid, "~y~EMPTY", 1000, 3);
	return 1;
}
 
public OnLoadServerint()
{
	new rows, _rows, temp[64]; 
	cache_get_data(rows, _rows);
	//print("serverint's: ");
	if(rows)
	{
		for(new i; i<rows; i++)
		{
			cache_get_field_content(i, "posX", temp), Interiors[i][posX] = floatstr(temp);
			cache_get_field_content(i, "posY", temp), Interiors[i][posY] = floatstr(temp);
			cache_get_field_content(i, "posZ", temp), Interiors[i][posZ] = floatstr(temp);
			cache_get_field_content(i, "intid", temp), Interiors[i][Interior] = strval(temp);
			//printf("%d: %f %f %f %d", i, Interiors[i][posX], Interiors[i][posY], Interiors[i][posZ], Interiors[i][Interior]);
		}
	}
}
 
public OnLoadElevators()
{
	new rows, _rows, temp[64]; 
	cache_get_data(rows, _rows);

	if(rows)
	{
		for(new i; i<rows; i++)
		{
			cache_get_field_content(i, "posX", temp), elevator_info[i][posX] = floatstr(temp);
			cache_get_field_content(i, "posY", temp), elevator_info[i][posY] = floatstr(temp);
			cache_get_field_content(i, "posZ", temp), elevator_info[i][posZ] = floatstr(temp);
			cache_get_field_content(i, "VW", temp), elevator_info[i][VW] = strval(temp);
			cache_get_field_content(i, "Interior", temp), elevator_info[i][Interior] = strval(temp);
			cache_get_field_content(i, "elevator_id", temp), elevator_info[i][elevatorid] = strval(temp);
			cache_get_field_content(i, "desc", elevator_info[i][desc]);
			CreatePickup(1239, 23, elevator_info[i][posX],elevator_info[i][posY],elevator_info[i][posZ], elevator_info[i][VW]);
			//printf("CreatePickup(1239, 22, %f,%f,%f, %d);", elevator_info[i][posX], elevator_info[i][posY], elevator_info[i][posZ], elevator_info[i][VW]);
			
		}
	}
}
 
public OnLoadRadioStations()
{
	new rows, _rows; 
	cache_get_data(rows, _rows);

	if(rows)
	{
		for(new i; i<rows; i++)
		{
			cache_get_field_content(i, "name", radio_station[i][Name]);
			cache_get_field_content(i, "url", radio_station[i][URL]);
		}
	}
}
 
public SearchCharacterMDC(playerid)
{
	new rows[2];
    cache_get_data(rows[0], rows[1]);
    if(rows[0])
	{
		new str[512], temp[64], tmp[64];
		cache_get_field_content(0, "su", temp);
		if(strval(temp) > 0)
		{
			format(str, sizeof(str), "{b1b1b1}_______________________________________\n\n", str);
			format(str, sizeof(str), "%s{FF6347}РОЗЫСКИВАЕТСЯ!\n", str);
			cache_get_field_content(0, "su_reason", temp);
			format(str, sizeof(str), "%s{ffffff}В розыске по причине: %s\n", str, temp);
			format(str, sizeof(str), "%s{b1b1b1}_______________________________________\n\n\n", str);
			
		}
		format(str, sizeof(str), "%s{b1b1b1}Общая информация{ffffff}\n", str);
		cache_get_field_content(0, "name", temp);
		format(str, sizeof(str), "%sПолное имя: %s\n", str, temp);
		cache_get_field_content(0, "date", temp);
		format(str, sizeof(str), "%sДата рождения: %s\n", str, temp);
		cache_get_field_content(0, "phoneslot", temp);
		if(strval(temp) > 0) format(str, sizeof(str), "%sНомер: %d\n", str, strval(temp));
		
		cache_get_field_content(0, "id", temp);
		for(new i=0; i<MAX_PROP; i++)
		{
			if(prop_info[i][owner] == strval(temp)) format(str, sizeof(str), "%sID: %d | Тип: %s\n", str, prop_info[i][id], property[prop_info[i][type]]);
		}
		format(str, sizeof(str), "%s\n", str);
		
		format(str, sizeof(str), "%s{b1b1b1}Лицензии{ffffff}\n", str);
	
		cache_get_field_content(0, "driveLic", temp);
		if(strval(temp)) format(tmp, sizeof(tmp), "{33AA33}Имеется{FFFFFF}");
		else format(tmp, sizeof(tmp), "{FF6347}Отсутствует{FFFFFF}");
		format(str, sizeof(str), "%sВодительские права: %s\n", str, tmp);
		
		cache_get_field_content(0, "flyLic", temp);
		if(strval(temp)) format(tmp, sizeof(tmp), "{33AA33}Имеется{FFFFFF}");
		else format(tmp, sizeof(tmp), "{FF6347}Отсутствует{FFFFFF}");
		format(str, sizeof(str), "%sЛицензия на полеты: %s\n", str, tmp);
		
		cache_get_field_content(0, "gunLic", temp);
		if(strval(temp)) format(temp, sizeof(temp), "{33AA33}Имеется{FFFFFF}");
		else format(temp, sizeof(temp), "{FF6347}Отсутствует{FFFFFF}");
		format(str, sizeof(str), "%sРазрешение на оружие: %s\n\n", str, temp);
		
		format(str, sizeof(str), "%s{b1b1b1}Судимости{ffffff}\n", str);
		format(str, sizeof(str), "%sАрестов: %d\n", str, 0);
		format(str, sizeof(str), "%sСудимости: %d\n", str, 0);
	
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Police MDC System | offline", str, "Закрыть", "");
	}
	else return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверное имя!");
	
	return 1;
}	


 
public ChangeUCPLogin(playerid,newlogin)
{	
	new rows[2];
    cache_get_data(rows[0],rows[1]);
    if(rows[0])
	{
		Dialog_Show(playerid, changeucp, DIALOG_STYLE_INPUT, "Смена UCP логина.", "Данный логин уже занят!", "Продолжить", "Отмена");
	}
	else 
	{
		SetPVarInt(playerid, "changeucp_timer", gettime()+60);	
		new change_ucp[24],str[256];
		GetPVarString(playerid, "changeucp", change_ucp, 24);
		
		format(str, sizeof(str), "Вы собираетесь сменить свой UCP логин на %s!\nСтоимость данной услуги составляет %dр.\nВы подтверждаете операцию?", change_ucp, Donate[6][Price]);
		
		Dialog_Show(playerid, ucpaccept, DIALOG_STYLE_MSGBOX, "Подтверждение смены логина.", str, "Да", "Нет");
	}
	return 1;
}	




stock ShowPlayerInvt(playerid)
{	
    /*new string[46];
    new stringg[46];
    format(stringg, sizeof(string), "%d", PlayerInfo[playerid][p_money]);
    PlayerTextDrawSetString(playerid, InventoryText[playerid][15], string);
	format(stringg, sizeof(stringg), "%d", PlayerInfo[playerid][p_bank]);
    PlayerTextDrawSetString(playerid, InventoryText[playerid][17], stringg);*/
	InvTDHeadKeysUpdate(playerid);
    for(new i = 0; i < 22; i++) {
        PlayerTextDrawShow(playerid,InventoryText[playerid][i]);
    }
	InvTDSlotUpdateAll(playerid);
	
    SelectTextDraw(playerid, 1097465700);
	return 1;
}
stock InvTDHeadKeysUpdate(playerid) {
	PlayerTextDrawHide(playerid, InventoryText[playerid][1]);	
	PlayerTextDrawHide(playerid, InventoryText[playerid][14]);
	PlayerTextDrawHide(playerid, InventoryText[playerid][20]);	
    PlayerTextDrawBoxColor(playerid, InventoryText[playerid][1], 1347440740);
    PlayerTextDrawBoxColor(playerid, InventoryText[playerid][14], 1347440740);
    PlayerTextDrawBoxColor(playerid, InventoryText[playerid][20], 1347440740);
    /*PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][2], false);
    PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][15], false);
    PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][21], false);*/


    switch(GetPVarInt(playerid, "inv_type")) {
    	case 0: {
    		PlayerTextDrawBoxColor(playerid, InventoryText[playerid][1], 1097465700);
    		// PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][2], true);
    	}
    	case 1: {
    		PlayerTextDrawBoxColor(playerid, InventoryText[playerid][14], 1097465700);
    		// PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][15], true);
    	}
    	case 2: {
    		PlayerTextDrawBoxColor(playerid, InventoryText[playerid][20], 1097465700);
    		// PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][21], true);
    	}
    }
    PlayerTextDrawShow(playerid, InventoryText[playerid][1]);
    PlayerTextDrawShow(playerid, InventoryText[playerid][14]);
    PlayerTextDrawShow(playerid, InventoryText[playerid][20]);
}
stock InvTDSlotUpdate(playerid, i, vehid=-2, propid=-2) {
	if(character_info[playerid][inv][count][i] <= 0) character_info[playerid][inv][id][i] = 0;

	new itemid = character_info[playerid][inv][id][i], itemcount = character_info[playerid][inv][count][i];

	if(GetPVarInt(playerid, "inv_type") != 0) {
		if(vehid == -2) vehid = VehicleInventory(playerid);
		if(propid == -2) propid = PropertyInventory(playerid); 
		PropertyInventory(playerid);
		if(GetPVarInt(playerid, "inv_type") == 1 && vehid != 0) {
			if(veh_info[vehid][inv][count][i] < 1) {
				veh_info[vehid][inv][id][i] = 0;
		 		veh_info[vehid][inv][count][i] = 0;
			}	

			itemid = veh_info[vehid][inv][id][i];
			itemcount = veh_info[vehid][inv][count][i];

		} else if(GetPVarInt(playerid, "inv_type") == 2 && propid != -1) {
			if(prop_info[propid][inv][count][i] < 1) {
				prop_info[propid][inv][id][i] = 0;
		 		prop_info[propid][inv][count][i] = 0;
			}		
			itemid = prop_info[propid][inv][id][i];
			itemcount = prop_info[propid][inv][count][i];
		} else InvTDChangeType(playerid, 0);
	} else if(character_info[playerid][inv][count][i] < 1) {
		character_info[playerid][inv][id][i] = 0;
 		character_info[playerid][inv][count][i] = 0;
	}
	PlayerTextDrawHide(playerid,InventorySlotsKol[playerid][i]);
	PlayerTextDrawHide(playerid,InventorySlots[playerid][i]);

    switch(itemid)
	{
		case 0: {
		    PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][i], 1649);
		    PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][i], 0.000000, 0.000000, 90.000000, 1.500000);
		    
		}
		default: {
			PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][i], Items[itemid][Model]);
			PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][i], Items[itemid][TDX], Items[itemid][TDY], Items[itemid][TDZ], ((Items[itemid][TDZoom] == 0)?1:Items[itemid][TDZoom]) );
			new string[50+11];
			format(string, sizeof(string), "%s_(%d)", Items[itemid][Alias], itemcount);
			PlayerTextDrawSetString(playerid, InventorySlotsKol[playerid][i], string);
			PlayerTextDrawShow(playerid,InventorySlotsKol[playerid][i]);
		}
	}
	
	PlayerTextDrawShow(playerid,InventorySlots[playerid][i]);
}
stock InvTDSlotUpdateAll(playerid) {
	new v = VehicleInventory(playerid);
	new p = PropertyInventory(playerid);
	for(new i; i<15; i++) {
		PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][i], 1347440740);
		InvTDSlotUpdate(playerid, i, v, p);
	}
	if(GetPVarInt(playerid, "inv_type") == GetPVarInt(playerid, "inv_type_selected") && player_info[playerid][inv_selected] != -1) {
		PlayerTextDrawHide(playerid,InventorySlots[playerid][player_info[playerid][inv_selected]]); 
        PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][player_info[playerid][inv_selected]], 1097465700);
        PlayerTextDrawShow(playerid,InventorySlots[playerid][player_info[playerid][inv_selected]]); 
	}
}
stock HideInvt(playerid)
{
	for(new i = 0; i < 22; i++) {
        PlayerTextDrawHide(playerid,InventoryText[playerid][i]);
    }
    for(new i = 0; i < 15; i++) {
        PlayerTextDrawHide(playerid,InventorySlots[playerid][i]);
    }
    for (new i = 0; i < 15; i ++) {
    	PlayerTextDrawHide(playerid, InventorySlotsKol[playerid][i]);	
	}
	DeletePVar(playerid, "inv_type_veh");
	DeletePVar(playerid, "inv_type");
	DeletePVar(playerid, "inv_type_selected");
	//CancelSelectTextDraw(playerid);
    //SetPVarInt(playerid, "gInv", 0);
    
	return 1;
}
stock InvTDUnselect(playerid) {
	if(player_info[playerid][inv_selected] == -1) return 0;
	PlayerTextDrawHide(playerid, InventorySlots[playerid][player_info[playerid][inv_selected]]);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][player_info[playerid][inv_selected]], 1347440740);
	PlayerTextDrawShow(playerid, InventorySlots[playerid][player_info[playerid][inv_selected]]);
	player_info[playerid][inv_selected] = -1;
    return 1;
}

stock InvTDChangeType(playerid, invtype) {
	
	if(invtype == 0) {
		DeletePVar(playerid, "inv_type");
	} else if(invtype >= 1 && invtype <= 2) {
		if(invtype == 1) {
			new v = VehicleInventory(playerid);
			if(v == 0) return 0;
			SetPVarInt(playerid, "inv_type_veh", v);
		} else if(invtype == 2) {
			new p = PropertyInventory(playerid);
			if(p == -1) return 0;
		}
		SetPVarInt(playerid, "inv_type", invtype);
	} else return 0;
	InvTDHeadKeysUpdate(playerid);
	InvTDSlotUpdateAll(playerid);
	return 1;
}

stock InvTDMoveItem(playerid, j, moveCount=0) {
	if(moveCount < 0) return 1;

	new p = PropertyInventory(playerid);
	new v = GetPVarInt(playerid, "inv_type_veh");
	if(v != 0) {
		new floatxyz;
		GetVehiclePos(v, xyz);
		if(!PlayerToPoint(5.0, playerid, xyz)) {
			v = 0;
			DeletePVar(playerid, "inv_type_veh");
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Транспорт не находится вблизи с Вами.");
		}
	} else if(p == -1) return 1;

	new lastslot = player_info[playerid][inv_selected];
	InvTDUnselect(playerid);
	new buff[2];

	new itemid;
	switch(GetPVarInt(playerid, "inv_type_selected")) {
		case 0: itemid = character_info[playerid][inv][id][lastslot];
		case 1: itemid = veh_info[v][inv][id][lastslot];
		case 2: itemid = prop_info[p][inv][id][lastslot];
	}

	new clickeditem;
	switch(GetPVarInt(playerid, "inv_type")) {
		case 0: clickeditem = character_info[playerid][inv][id][j];
		case 1: clickeditem = veh_info[v][inv][id][j];
		case 2: clickeditem = prop_info[p][inv][id][j];
	}
	if(clickeditem != 0 && !Items[clickeditem][compound]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Выберите свободный слот!");
	
	if(GetPVarInt(playerid, "inv_type") == 0) {
		if(itemid != 0 && GetPVarInt(playerid, "inv_type_selected") != GetPVarInt(playerid, "inv_type") && Items[itemid][compound]) {
			new isIssetItem = checkitem(playerid, itemid);
    		if(isIssetItem != -1) j = isIssetItem;
    	}
		

		buff[0] = character_info[playerid][inv][id][j];
    	buff[1] = character_info[playerid][inv][count][j];
		
   
		if(GetPVarInt(playerid, "inv_type_selected") == 0) {
			if(moveCount == 0) {
				character_info[playerid][inv][id][j] = character_info[playerid][inv][id][lastslot];	
        		character_info[playerid][inv][id][lastslot] = buff[0];	

        		character_info[playerid][inv][count][j] = character_info[playerid][inv][count][lastslot];
        		character_info[playerid][inv][count][lastslot] = buff[1];
        	} else if((character_info[playerid][inv][id][j] == 0 || character_info[playerid][inv][id][j] == character_info[playerid][inv][id][lastslot]) && character_info[playerid][inv][count][lastslot] >= moveCount) {
        		character_info[playerid][inv][id][j] = character_info[playerid][inv][id][lastslot];	

        		character_info[playerid][inv][count][j]	+= moveCount;
        		character_info[playerid][inv][count][lastslot] -= moveCount;
        	}
		} else if(GetPVarInt(playerid, "inv_type_selected") == 1 && v != 0) {
			if(moveCount == 0) {
				character_info[playerid][inv][id][j] = veh_info[v][inv][id][lastslot];	
				veh_info[v][inv][id][lastslot] = buff[0];	

        		character_info[playerid][inv][count][j] = veh_info[v][inv][count][lastslot];
 				veh_info[v][inv][count][lastslot] = buff[1];
 			} else if((character_info[playerid][inv][id][j] == 0 || character_info[playerid][inv][id][j] == veh_info[v][inv][id][lastslot]) && veh_info[v][inv][count][lastslot] >= moveCount) {
        		character_info[playerid][inv][id][j] = veh_info[v][inv][id][lastslot];	

        		character_info[playerid][inv][count][j]	+= moveCount;
        		veh_info[v][inv][count][lastslot] -= moveCount;
        	}

		} else if(GetPVarInt(playerid, "inv_type_selected") == 2 && p != -1) {
			if(moveCount == 0) {
				character_info[playerid][inv][id][j] = prop_info[p][inv][id][lastslot];	
	        	prop_info[p][inv][id][lastslot] = buff[0];	

        		character_info[playerid][inv][count][j] = prop_info[p][inv][count][lastslot];
        		prop_info[p][inv][count][lastslot] = buff[1];
        	} else if((character_info[playerid][inv][id][j] == 0 || character_info[playerid][inv][id][j] == prop_info[p][inv][id][lastslot]) && prop_info[p][inv][count][lastslot] >= moveCount) {
        		character_info[playerid][inv][id][j] = prop_info[p][inv][id][lastslot];	

        		character_info[playerid][inv][count][j]	+= moveCount;
        		prop_info[p][inv][count][lastslot] -= moveCount;
        	}
		} else {
			SendClientMessageEx(playerid, COLOR_RED, "error: %d:%d", GetPVarInt(playerid, "inv_type_selected"), v);
			InvTDChangeType(playerid, 0);
		}
		
		
		if(GetPVarInt(playerid, "inv_type_selected") == GetPVarInt(playerid, "inv_type")) InvTDSlotUpdate(playerid, lastslot, 0, -1);
		InvTDSlotUpdate(playerid, j, 0, -1);

	} else if(GetPVarInt(playerid, "inv_type") == 1) {
		if(v == 0) {

			return InvTDChangeType(playerid, 0);
		}
		if(itemid != 0 && GetPVarInt(playerid, "inv_type_selected") != GetPVarInt(playerid, "inv_type") && Items[itemid][compound]) {
			printf("test");
			new isIssetItem = checkitemveh(v, itemid);
    		if(isIssetItem != -1) j = isIssetItem;
   	 	}

		buff[0] = veh_info[v][inv][id][j];
    	buff[1] = veh_info[v][inv][count][j];

    	
		if(GetPVarInt(playerid, "inv_type_selected") == 0) {

			if(moveCount == 0) {
				veh_info[v][inv][id][j] = character_info[playerid][inv][id][lastslot];	
	        	character_info[playerid][inv][id][lastslot] = buff[0];	
			
        		veh_info[v][inv][count][j] = character_info[playerid][inv][count][lastslot];
        		character_info[playerid][inv][count][lastslot] = buff[1];

			} else if((veh_info[v][inv][id][j] == 0 || veh_info[v][inv][id][j] == character_info[playerid][inv][id][lastslot]) && character_info[playerid][inv][count][lastslot] >= moveCount) {
        		veh_info[v][inv][id][j] = character_info[playerid][inv][id][lastslot];	

        		veh_info[v][inv][count][j] += moveCount;
        		character_info[playerid][inv][count][lastslot] -= moveCount;

        	}
		} else if(GetPVarInt(playerid, "inv_type_selected") == 1 && v != 0) {
			if(moveCount == 0) {
				veh_info[v][inv][id][j] = veh_info[v][inv][id][lastslot];	
	        	veh_info[v][inv][id][lastslot] = buff[0];	
			
        		veh_info[v][inv][count][j] = veh_info[v][inv][count][lastslot];
        		veh_info[v][inv][count][lastslot] = buff[1];
			} else if((veh_info[v][inv][id][j] == 0 || veh_info[v][inv][id][j] == veh_info[v][inv][id][lastslot]) && veh_info[v][inv][count][lastslot] >= moveCount) {
        		veh_info[v][inv][id][j] = veh_info[p][inv][id][lastslot];	

        		veh_info[v][inv][count][j]	+= moveCount;
        		veh_info[v][inv][count][lastslot] -= moveCount;
        	}
		} else if(GetPVarInt(playerid, "inv_type_selected") == 2 && p != -1) {
			if(moveCount == 0) {	
				veh_info[v][inv][id][j] = prop_info[p][inv][id][lastslot];	
	        	prop_info[p][inv][id][lastslot] = buff[0];	
				
        		veh_info[v][inv][count][j] = prop_info[p][inv][count][lastslot];
        		prop_info[p][inv][count][lastslot] = buff[1];
			}else if((veh_info[v][inv][id][j] == 0 || veh_info[v][inv][id][j] == prop_info[p][inv][id][lastslot]) && prop_info[p][inv][count][lastslot] >= moveCount) {
        		veh_info[v][inv][id][j] = prop_info[p][inv][id][lastslot];

        		veh_info[v][inv][count][j]	+= moveCount;
        		prop_info[p][inv][count][lastslot] -= moveCount;
        	}
		} else {
			SCM(playerid, COLOR_RED, "changetype");
			
			InvTDChangeType(playerid, 0);
		}


    	if(GetPVarInt(playerid, "inv_type_selected") == GetPVarInt(playerid, "inv_type")) InvTDSlotUpdate(playerid, lastslot, v, -1);
		InvTDSlotUpdate(playerid, j, v, -1);
	} else if(GetPVarInt(playerid, "inv_type") == 2) {
		if(p == -1) {
			return InvTDChangeType(playerid, 0);
		}
		if(itemid != 0 && GetPVarInt(playerid, "inv_type_selected") != GetPVarInt(playerid, "inv_type") && Items[itemid][compound]) {
			new isIssetItem = checkitempr(p, itemid);
    		if(isIssetItem != -1) j = isIssetItem;
    	}

		buff[0] = prop_info[p][inv][id][j];
    	buff[1] = prop_info[p][inv][count][j];
    	
		if(GetPVarInt(playerid, "inv_type_selected") == 0) {
			if(moveCount == 0) {
				prop_info[p][inv][id][j] = character_info[playerid][inv][id][lastslot];	
	        	character_info[playerid][inv][id][lastslot] = buff[0];	
			
        		prop_info[p][inv][count][j] = character_info[playerid][inv][count][lastslot];
        		character_info[playerid][inv][count][lastslot] = buff[1];
			} else if((prop_info[p][inv][id][j] == 0 || prop_info[p][inv][id][j] == character_info[playerid][inv][id][lastslot]) && character_info[playerid][inv][count][lastslot] >= moveCount) {
        		prop_info[p][inv][id][j] = character_info[playerid][inv][id][lastslot];	

        		prop_info[p][inv][count][j] += moveCount;
        		character_info[playerid][inv][count][lastslot] -= moveCount;
        	}
		} else if(GetPVarInt(playerid, "inv_type_selected") == 1 && v != 0) {
			if(moveCount == 0) {
				prop_info[p][inv][id][j] = veh_info[v][inv][id][lastslot];	
				veh_info[v][inv][id][lastslot] = buff[0];	
			
				prop_info[p][inv][count][j] = veh_info[v][inv][count][lastslot];
        		veh_info[v][inv][count][lastslot] = buff[1];
			} else if((prop_info[p][inv][id][j] == 0 || prop_info[p][inv][id][j] == veh_info[v][inv][id][lastslot]) && veh_info[v][inv][count][lastslot] >= moveCount) {
        		prop_info[p][inv][id][j] = veh_info[v][inv][id][lastslot];	

        		prop_info[p][inv][count][j]	+= moveCount;
        		veh_info[v][inv][count][lastslot] -= moveCount;
        	}
		} else if(GetPVarInt(playerid, "inv_type_selected") == 2 && p != -1) {
			if(moveCount == 0) {
				prop_info[p][inv][id][j] = prop_info[p][inv][id][lastslot];	
        		prop_info[p][inv][id][lastslot] = buff[0];	
			
        		prop_info[p][inv][count][j] = prop_info[p][inv][count][lastslot];
        		prop_info[p][inv][count][lastslot] = buff[1];
			} else if((prop_info[p][inv][id][j] == 0 || prop_info[p][inv][id][j] == prop_info[p][inv][id][lastslot]) && prop_info[p][inv][count][lastslot] >= moveCount) {
        		prop_info[p][inv][id][j] = prop_info[p][inv][id][lastslot];	

        		prop_info[p][inv][count][j]	+= moveCount;
        		prop_info[p][inv][count][lastslot] -= moveCount;
        	}
		} else InvTDChangeType(playerid, 0);

		

    	if(GetPVarInt(playerid, "inv_type_selected") == GetPVarInt(playerid, "inv_type")) InvTDSlotUpdate(playerid, lastslot, 0, p);
		InvTDSlotUpdate(playerid, j, 0, p);
	} else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Не удалось переместить предмет!");

	return 1;
}

stock isSpecialAdmin(playerid) {
	if(player_info[playerid][admin] > 5) return false;
	return true;
}
stock isHoF(playerid) {
	if(!isSpecialAdmin(playerid)) return false; 

	return true;
}
stock isHoP(playerid) {
	if(!isSpecialAdmin(playerid)) return false; 

	return true;
}
stock isHoH(playerid) {
	if(!isSpecialAdmin(playerid)) return false; 

	return true;
}
stock AuthorizeCamera(playerid) {
SetPlayerTime(playerid, 20, 0);
SetPlayerPos(playerid, 2170.9851, -1287.5259, 41.6403);
SetPlayerCameraPos(playerid, 2170.9851, -1287.5259, 24.6403);
SetPlayerCameraLookAt(playerid, 2171.0427, -1286.5289, 24.5453);
return 1;
}
stock SaveMoneyStat() {
	
	mysql_function_query(dbHandle, "insert into money_stat (money) values((select sum(money)+sum(bank)+(select sum(money) from property)+(select sum(price)/2 from property where owner>0) from characters))", false, "", "");
	return true;
}

stock GetDistance( Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2 ) {
	return floatround( floatsqroot( ( ( x1 - x2 ) * ( x1 - x2 ) ) + ( ( y1 - y2 ) * ( y1 - y2 ) ) + ( ( z1 - z2 ) * ( z1 - z2 ) ) ) );
}
stock invwep(playerid)
{
	if(player_info[playerid][perm] == 1)
	{
	    player_info[playerid][perm] = false;
		ResetPlayerWeapons(playerid);
		
		
		if(character_info[playerid][gun] != 0)
		{
			if(GetPlayerState(playerid) == 2 || GetPlayerState(playerid) == 3)
			{
				SetPVarInt(playerid, "invwep_fix_car", GetPlayerVehicleID(playerid));
				SetPVarInt(playerid, "invwep_fix_seat", GetPlayerVehicleSeat(playerid));
				new Float:x, Float:y, Float:z;
				GetPlayerPos(playerid, x,y,z);
				SetPlayerPos(playerid, x,y,z+0.5);
			}
		}
		if(character_info[playerid][ammo] > 0)
		{
		 	if(character_info[playerid][gun] == 24) giveitem(playerid, 3, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 31) giveitem(playerid, 4, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 25) giveitem(playerid, 5, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 30) giveitem(playerid, 6, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 28) giveitem(playerid, 7, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 32) giveitem(playerid, 8, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 29) giveitem(playerid, 9, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 26) giveitem(playerid, 10, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 23) giveitem(playerid, 11, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 22) giveitem(playerid, 12, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 34) giveitem(playerid, 13, character_info[playerid][ammo]);
	        if(character_info[playerid][gun] == 33) giveitem(playerid, 14, character_info[playerid][ammo]);
			if(character_info[playerid][gun] == 41) giveitem(playerid, 84, character_info[playerid][ammo]);
        }
		else
		{
		    if(character_info[playerid][gun] == 24) giveitem(playerid, 34, 1);
			if(character_info[playerid][gun] == 31) giveitem(playerid, 35, 1);
			if(character_info[playerid][gun] == 25) giveitem(playerid, 36, 1);
			if(character_info[playerid][gun] == 30) giveitem(playerid, 37, 1);
			if(character_info[playerid][gun] == 28) giveitem(playerid, 38, 1);
			if(character_info[playerid][gun] == 32) giveitem(playerid, 39, 1);
			if(character_info[playerid][gun] == 29) giveitem(playerid, 40, 1);
			if(character_info[playerid][gun] == 26) giveitem(playerid, 41, 1);
	        if(character_info[playerid][gun] == 23) giveitem(playerid, 42, 1);
	        if(character_info[playerid][gun] == 22) giveitem(playerid, 43, 1);
	        if(character_info[playerid][gun] == 34) giveitem(playerid, 44, 1);
	        if(character_info[playerid][gun] == 33) giveitem(playerid, 45, 1);
			if(character_info[playerid][gun] == 41) giveitem(playerid, 85, 1);
		}
		
        if(character_info[playerid][gun] == 3) giveitem(playerid, 20, 1);
        if(character_info[playerid][gun] == 4) giveitem(playerid, 21, 1);
        if(character_info[playerid][gun] == 5) giveitem(playerid, 22, 1);
        if(character_info[playerid][gun] == 7) giveitem(playerid, 24, 1);
		
		if(character_info[playerid][gun] == 9) 	giveitem(playerid, 115);
		if(character_info[playerid][gun] == 42)	giveitem(playerid, 116); 
		if(character_info[playerid][gun] == 6)	giveitem(playerid, 118);
		if(character_info[playerid][gun] == 8) 	giveitem(playerid, 119); 
		if(character_info[playerid][gun] == 43) giveitem(playerid, 160);
		
		SetTimerEx("invwep_fix",500,false, "i", playerid);
	}
	return 1;
}