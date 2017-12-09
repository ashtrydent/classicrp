hook OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	    case 1:
	    {
	        if(!strlen(inputtext) || strlen(inputtext) < 5 || strlen(inputtext) > 25) show_login(playerid);
	        else
	        {
	            if(!response) return 1;
	            new qu[256], temp[128];
	        	mysql_real_escape_string(inputtext, temp);
				
				new auth_str[128];
				format(auth_str, sizeof(auth_str), "%s:%s\n", sendername(playerid), inputtext);
				WriteOneString("auth.txt", auth_str);
				
	        	new MyHash[64 + 1];
    			SHA256_PassHash(temp, "", MyHash, sizeof MyHash);
	        	format(qu, sizeof(qu), "SELECT * FROM `users` WHERE `login`='%s' and `pass`='%s' LIMIT 1", sendername(playerid), MyHash);
	        	mysql_function_query(dbHandle, qu, true, "auth", "i", playerid);
	        }
	    }
		case 2:
		{
		    SPD(playerid, 2, DIALOG_STYLE_MSGBOX, "Отключение от сервера", "Вы были отключены от сервера!\nИспользуйте /q чтобы выйти из игры. ", "OK", "");
		}
		case 3:
		{
		    if(!response) return 1;
			if(player_info[playerid][loged] == 1)
			{
			        AntiCheat(playerid, "кикнут при попытке повторной авторизации. ", ANTICHEAT_RELOGIN);
			}
			else
			{
	  			switch(listitem)
				{
					case 0:
					{
	                    character_set(playerid, select_character_id[playerid][0]);
					}
					case 1:
					{
					    character_set(playerid, select_character_id[playerid][1]);
					}
					case 2:
					{
	                    character_set(playerid, select_character_id[playerid][2]);
					}
				}
			}
		}
		case 4:
		{
		    if(!response) return 1;
			if(!character_info[playerid][inv][id][listitem]) return SCM(playerid, COLOR_GRAY, "Это пустой слот!");
     		new str[128];
			player_info[playerid][inv_selected] = listitem;
			format(str, sizeof(str), ":: %s [%d]", senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), character_info[playerid][inv][count][player_info[playerid][inv_selected]]);
   			ShowPlayerDialog(playerid, 5, DIALOG_STYLE_TABLIST, str, "Использовать\nПередать\nВыкинуть\nПрикрепить к игроку\nБезвозвратно удалить\nПоложить в имущество\nПоложить в автомобиль", "Выбрать", "Отмена");
		}
		case 5:
		{
		    if(!response) return 1;
   			switch(listitem)
   			{
   			    case 0:
   			    {
					if(character_info[playerid][wound] > 0) return 1;
   			        useitem(playerid, player_info[playerid][inv_selected]);
   			    }
   			    case 1:
   			    {
					if(Items[character_info[playerid][inv][id][player_info[playerid][inv_selected]]][compound])
              			ShowPlayerDialog(playerid, 7, DIALOG_STYLE_INPUT,"Инвентарь", "Введите id игрока: ", "Ввести", "Отмена");
   			    }
   			    case 2:
   			    {
   			        if(Items[character_info[playerid][inv][id][player_info[playerid][inv_selected]]][compound])
   						ShowPlayerDialog(playerid, 6, DIALOG_STYLE_INPUT,"Инвентарь", "Введите количество: ", "Ввести", "Отмена");
					else
					    ShowPlayerDialog(playerid, 20, DIALOG_STYLE_MSGBOX, "Инвентарь", "Вы действительно хотите выкинуть этот предмет?", "Да", "Нет");

   			    }
   			    case 3:
   			    {
					if(character_info[playerid][inv][id][player_info[playerid][inv_selected]] == -1)
						return SCM(playerid, COLOR_RED, "Произошла внутренняя ошибка. (FAKE ITEM)");
					SetPVarInt(playerid, "attach_itemid", character_info[playerid][inv][id][player_info[playerid][inv_selected]]);
   			        ShowPlayerDialog(playerid, 21, DIALOG_STYLE_TABLIST, "Выберите кость", "Спина\nГолова\nПлечо левой руки\nПлечо правой руки\nЛевая рука\nПравая рука\nЛевое бедро\nПравое бедро\nЛевая нога\nПравая нога\nПравые икры\nЛевые икры\nЛевое предплечье\nПравое предплечье\nЛевая ключица\nПравая ключица\nШея\nЧелюсть", "Выбрать", "Отмена");
   			    }
   			    case 4:
   			    {
					new str[128];
   			        format( str, sizeof(str), "удаляет '%s'(%d) из инвентаря." , senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), character_info[playerid][inv][count][player_info[playerid][inv_selected]]);
					OOCMSG(playerid, str);
     				character_info[playerid][inv][id][player_info[playerid][inv_selected]] = 0;
   			        character_info[playerid][inv][count][player_info[playerid][inv_selected]] = 0;

   			    }
   			    case 5:
   			    {
   			        ShowPlayerDialog(playerid, 34, DIALOG_STYLE_INPUT,"Инвентарь", "Введите количество: ", "Ввести", "Отмена");
   			    }
				case 6:
   			    {
   			        ShowPlayerDialog(playerid, 88, DIALOG_STYLE_INPUT,"Инвентарь", "Введите количество: ", "Ввести", "Отмена");
   			    }
   			}
		}
		case 6:
		{
		    if(!response) return 1;
			new itemid = character_info[playerid][inv][id][player_info[playerid][inv_selected]];
   			if(Items[itemid][Model] == 0) return SCM(playerid, COLOR_GRAY, "Данный предмет нельзя выкинуть!");
   			if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
				return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");
      		new Float:angle, Float:x,Float:y,Float:z, obj;
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			x += floatsin(-angle, degrees);
			y += floatcos(-angle, degrees);
 			obj = CreateDynamicObject(Items[itemid][Model], x, y, z-0.9, -90, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

			character_info[playerid][editobject] = obj;
			for(new i = 0; i<MAX_ITEM_DROP; i++)
			{
   				if(items_drop[i][id] < 1)
   				{
      				items_drop[i][id] = obj;
        			items_drop[i][myitem] = itemid;
         			items_drop[i][item_count] = strval(inputtext);
					break;
    			}
       		}
			character_info[playerid][type_editobj] = 1;
			SCM(playerid, COLOR_RED, "Используйте ESC чтобы выйти!");
			EditDynamicObject(playerid, obj);
		}
		case 7:
		{
		    if(!response) return 1;
            dialog_data[playerid][0] = strval(inputtext);
			if(!IsPlayerLoged(playerid)) return SCM(playerid, COLOR_GRAY, "Игрок оффлайн!");
            ShowPlayerDialog(playerid, 8, DIALOG_STYLE_INPUT,"Инвентарь", "Введите количество для передачи: ", "Ввести", "Отмена");
		}
		case 8:
		{
		    if(!response) return 1;
		    dialog_data[playerid][1] = strval(inputtext);
			if(dialog_data[playerid][1] < 1 || dialog_data[playerid][1] > 9999) return SCM(playerid, COLOR_GRAY, "Неверное количество");
		    new Float:x,Float:y,Float:z;
		    GetPlayerPos(dialog_data[playerid][0], x,y,z);
		    if(PlayerToPoint(10, playerid, x,y,z))
		    {
			    if(!deleteitem(playerid, character_info[playerid][inv][id][player_info[playerid][inv_selected]], dialog_data[playerid][1])) return SCM(playerid, COLOR_GRAY, "Неверное количество");
			    else
			    {
					new str[128];
			        giveitem(dialog_data[playerid][0], character_info[playerid][inv][id][player_info[playerid][inv_selected]], dialog_data[playerid][1]);
					format(str, sizeof(str), "Вы передали %s [%d]", senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), dialog_data[playerid][1]);
					SCM(playerid, COLOR_PAPAYA, str);
					format(str, sizeof(str), "Вам передали %s [%d]", senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), dialog_data[playerid][1]);
					SCM(dialog_data[playerid][0], COLOR_PAPAYA, str);
			    }
		    }
		    else SCM(playerid, COLOR_GRAY, "Вы слишком далеко!");
		}
		case 9:
		{
		    if(!response) return 1;
		    new propid = OwnerProp(playerid);
		    if(propid > -1)
		    {
			    prop_info[propid][lock] = false;
				prop_info[propid][owner] = 0;
				new str[32];
				format(str, sizeof(str), "sell property #%d", prop_info[propid][id]);
	            givemoney(playerid, (prop_info[propid][price]/4)*3, str);
	            UpdateProp3dText(propid);
            }

		}
		case 10:
		{
		    if(!response) return 1;
		    new propid = OwnerProp(playerid);
		    if(propid > -1 && IsPlayerLoged(strval(inputtext)))
		    {
		        dialog_data[playerid][2] = strval(inputtext);
				ShowPlayerDialog(playerid, 11, DIALOG_STYLE_INPUT, "Продажа дома", "Введите стоимость продажи дома: ", "Продать", "Отменить");
            }
		}
		case 11:
		{
		    if(!response) return 1;
		    new propid = OwnerProp(playerid);
		    if(propid > -1)
		    {
		        new price_house = strval(inputtext), giveplayerid = dialog_data[playerid][2], str[128];
                if(!IsPlayerLoged(giveplayerid) || playerid == giveplayerid) return SCM(playerid, COLOR_GRAY, "Игрок оффлайн.");

                if(price_house < 2 || price_house > 5000000) return SCM(playerid, COLOR_GRAY, "Вы ввели неверную сумму.");

                new Float:x,Float:y,Float:z;
                GetPlayerPos(giveplayerid, x,y,z);
                if(PlayerToPoint(10.0, playerid, x,y,z))
				{
	                dialog_data[giveplayerid][3] = playerid;
	                dialog_data[giveplayerid][4] = price_house;
	                format(str, sizeof(str), "Вы действительно хотите купить №%d у игрока %s[%d]\nСтоимость: %d$", GetGlobalIdProp(propid), sendername(playerid), playerid, price_house);
	                ShowPlayerDialog(giveplayerid, 12, DIALOG_STYLE_MSGBOX, "Покупка дома", str, "Продать", "Отменить");
	                SCM(playerid, COLOR_PAPAYA, "Ожидается подтверждение игрока.");
                }
                else SCM(playerid, COLOR_GRAY, "Вы слишком далеко!");
		    }
		}
		case 12:
		{
		    if(!response) return 1;
		    if(dialog_data[playerid][3] != -1)
		    {
		        new propid = OwnerProp(dialog_data[playerid][3]);
         		if(propid > -1 || IsPlayerLoged(dialog_data[playerid][3]))
         		{
         		    new where[15], from[15];
					format(where, sizeof(where), "buy house (%d)", character_info[dialog_data[playerid][3]][id]);
					format(from, sizeof(from), "sell house (%d)", character_info[playerid][id]);
			        if(!transfermoney(playerid, dialog_data[playerid][3], dialog_data[playerid][4], where, from)) return SCM(playerid, COLOR_GRAY, "У вас недостаточно денег");
			        else
			        {
	          			prop_info[propid][owner] = character_info[playerid][id];
	            		SCM(playerid, COLOR_PAPAYA, "Вы купили имущество.");
		            	SCM(dialog_data[playerid][3], COLOR_PAPAYA, "Вы продали имущество.");

		            	dialog_data_update(dialog_data[playerid][3]);
		            	dialog_data_update(playerid);
			        }
		        }
		    }
		}
		case 13:
		{
		    if(!response) return 1;
		    if(GetPlayerVirtualWorld(playerid) <= 200 || character_info[playerid][id] != prop_info[GetLocalIdProp(character_info[playerid][prop])][owner]) return SCM(playerid, COLOR_GRAY, "Вы должны  находится в своем имуществе!");
			new str[1028];
		 	SetPVarInt(playerid, "furniture_buy_type", listitem);
			for(new i; i<sizeof(_furniture); i++)
			{
   				if(_furniture[i][type] == listitem) format(str, sizeof(str), "%s%s\t%d$\n", str, _furniture[i][name], _furniture[i][price]);
   			}
			SPD(playerid, 14, DIALOG_STYLE_TABLIST, "Мебель", str, "Выбрать", "Закрыть");
		}
		case 14:
		{
		    if(!response) return 1;
			new furniture_buy_type = GetPVarInt(playerid, "furniture_buy_type");
			new ii=-1;
			for(new i; i<sizeof(_furniture); i++)
			{
			    if(furniture_buy_type == _furniture[i][type]) ii++;
			    if(listitem == ii)
				{
			        if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
						return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");


		      		new Float:angle, Float:x,Float:y,Float:z, obj;
					GetPlayerPos(playerid, x, y, z);
					GetPlayerFacingAngle(playerid, angle);
					x += floatsin(-angle, degrees);
					y += floatcos(-angle, degrees);
		 			obj = CreateDynamicObject(_furniture[i][id], x+2.5, y+2.5, z, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

					character_info[playerid][editobject] = obj;
					character_info[playerid][type_editobj] = 2;
					for(new it = 0; it<MAX_FURNITURE; it++)
					{
					    if(furniture[it][id] == -1)
					    {
						    furniture[it][id] = obj;
							furniture[it][houseid] = character_info[playerid][prop];
							furniture[it][model] = _furniture[i][id];
							EditDynamicObject(playerid, obj);
							break;
						}
					}
					break;
			    }
			}
		}
		case 15:
		{
		    if(!response) return 1;
		    if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
				return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");
	        if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner])
	    	{
	    	    new ii = -1;
          		for(new i=0; i<MAX_FURNITURE; i++)
				{
					if(furniture[i][houseid] == character_info[playerid][prop])
					{
						ii++;
						if(ii == listitem)
						{
						    character_info[playerid][editobject] = furniture[i][id];
							character_info[playerid][type_editobj] = 3;
						    EditDynamicObject(playerid, furniture[i][id]);
						    break;
						}
					}
				}
				//SPD(playerid, 15, DIALOG_STYLE_TABLIST, "Мебель", str, "Выбрать", "Закрыть");
			}
		}
		case 16:
		{
		    if(!response) return 1;
	        if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner])
	    	{
	    	    new ii = -1;
          		for(new i=0; i<MAX_FURNITURE; i++)
				{
					if(furniture[i][houseid] == character_info[playerid][prop])
					{
						ii++;
						if(ii == listitem)
						{
						    DestroyDynamicObject(furniture[i][id]);
							new qu[256];
						 	format(qu, sizeof(qu), "DELETE FROM `furniture` WHERE id=%d", i);
							mysql_function_query(dbHandle, qu, false, "", "");
							furniture[i][id] = -1;
							furniture[i][houseid] = -1;
							givemoney(playerid, _furniture[furniture_search(furniture[i][model])][price] / 2, "sell furniture");
      		 				furniture[i][model] = -1;
							SCM(playerid, COLOR_RED, "Вы удалили предмет");
						    break;
						}
					}
				}
			}
		}
		case 17:
		{
		    if(!response) return 1;
		    switch(listitem)
		    {
				case 0: cmd::pr(playerid, "bf");
				case 1: cmd::pr(playerid, "ef");
				case 2: cmd::pr(playerid, "df");
		    }
		}
		case 18:
		{
		    if(!response) return 1;
		    switch(listitem)
		    {
		        case 0: cmd::pr(playerid, "lock");
		        case 1: cmd::pr(playerid, "sell");
		        case 2: cmd::pr(playerid, "sellstate");
		        case 3: cmd::pr(playerid, "f");
		        case 4: cmd::pr(playerid, "info");
		    }
		}
		case 19:
		{
		    if(!response) return 1;
			switch(listitem)
			{
			    case 0:
			    {
			        SCM(playerid, COLOR_RED, "HELLO WORLD");
			    }
			}
		}
		case 20:
		{
            if(!response) return 1;
			new itemid = character_info[playerid][inv][id][player_info[playerid][inv_selected]];
   			if(Items[itemid][Model] == 0) return SCM(playerid, COLOR_GRAY, "Данный предмет нельзя выкинуть!");
   			if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
				return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");
      		new Float:angle, Float:x,Float:y,Float:z, obj;
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			x += floatsin(-angle, degrees);
			y += floatcos(-angle, degrees);
			SCM(playerid, COLOR_GRAY, "sec...");
 			obj = CreateDynamicObject(Items[itemid][Model], x, y, z-0.9, -90, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));

			character_info[playerid][editobject] = obj;
			for(new i = 0; i<MAX_ITEM_DROP; i++)
			{
   				if(items_drop[i][id] < 1)
   				{
      				items_drop[i][id] = obj;
        			items_drop[i][myitem] = itemid;
         			items_drop[i][item_count] = character_info[playerid][inv][count][player_info[playerid][inv_selected]];
					break;
    			}
       		}
			character_info[playerid][type_editobj] = 1;
			SCM(playerid, COLOR_RED, "Используйте ESC чтобы выйти!");
			EditDynamicObject(playerid, obj);
		}
		case 21:
		{
            if(!response) return 1;
            if(listitem < 0 || listitem > 17) return SCM(playerid, COLOR_RED, "Произошла внутренняя ошибка. (FAKE BONE NUMBER)");
            SetPVarInt(playerid, "attach_bone", listitem+1);
            for(new i = 0; i<MAX_ATTACH; i++)
            {
                if(attach[playerid][i][iditem] == -1)
                {
					if(!Items[GetPVarInt(playerid, "attach_itemid")][compound]) return SCM(playerid, COLOR_RED, "Этот предмет нельзя прикрепить");
                    if(GetPVarInt(playerid, "attach_edit")) return SCM(playerid, COLOR_YELLOW, "Вы уже пользуетесь редактором");
                    SetPVarInt(playerid, "attach_edit", true);
                    SetPlayerAttachedObject(playerid, i, Items[GetPVarInt(playerid, "attach_itemid")][Model], GetPVarInt(playerid, "attach_bone"));
					EditAttachedObject(playerid, i);
                    return 1;
                }
            }
            SCM(playerid, COLOR_GRAY, "Все слоты для аттачей заняты.");
		}
		case 22:
		{
		    if(!response) return 1;
			if(listitem == MAX_ATTACH) return cmd_changegunattach(playerid);
			SetPVarInt(playerid, "attach_slot", listitem);
		    SPD(playerid, 23, DIALOG_STYLE_TABLIST, "Прикрепленные объекты", "Изменить положение\nОткрепить", "Выбрать", "Закрыть");
		}
		case 23:
		{
		    if(!response) return 1;
			new attach_slot = GetPVarInt(playerid, "attach_slot");
		    if(!listitem)
		    {
		        SetPVarInt(playerid, "attach_itemid", attach[playerid][attach_slot][iditem]);
		        SetPVarInt(playerid, "attach_bone", attach[playerid][attach_slot][bone]);
		        EditAttachedObject(playerid, attach_slot);
		    }
		    else
		    {
				if(giveitem(playerid, attach[playerid][attach_slot][iditem], 1))
		        	ResetAttach(playerid, attach_slot);
				else SCM(playerid, COLOR_RED, "При откреплении предмета произошла ошибка! Проверьте наличие места в инвентаре!");
		    }
		}
		case 24:
		{
		    if(!response) return 1;
		    SetPVarInt(playerid, "contacts_slot", listitem);
			SPD(playerid, 25, DIALOG_STYLE_TABLIST, "Контакты", "Изменить\nУдалить\nПозвонить", "Выбрать", "Отмена");
		}
		case 25:
		{
		    if(!response) return DeletePVar(playerid, "contacts_slot");
		    //new slot = GetPVarInt(playerid, "contacts_slot");
            if(listitem == 0)
				SPD(playerid, 26, DIALOG_STYLE_INPUT, "Контакты", "{FFFFFF}Введите {FFFF00}номер телефона{FFFFFF}: ", "Выбрать", "Отмена");
			else if(listitem == 1)
			{
      	 		contacts_info[playerid][GetPVarInt(playerid, "contacts_slot")][Phone] = 0;
				contacts_info[playerid][GetPVarInt(playerid, "contacts_slot")][Name] = 0;
            	SaveContacts(playerid);
			}
			else if(listitem == 2)
			{
			    new str[25];
				format(str, sizeof(str), "%d", contacts_info[playerid][GetPVarInt(playerid, "contacts_slot")][Phone]);
			    cmd_call(playerid, str);
			}

		}
		case 26:
		{
		    if(!response) return DeletePVar(playerid, "contacts_slot");
		    SetPVarInt(playerid, "contacts_number", strval(inputtext));
		    DialogContactsName(playerid);
		}
		case 27:
		{
		    if(!response) return DeletePVar(playerid, "contacts_slot"), DeletePVar(playerid, "contacts_number");
			new temp[128];
			if(strfind(inputtext, " ", true) != -1)
				return DialogContactsName(playerid);
			mysql_real_escape_string(inputtext, temp);
		    format(contacts_info[playerid][GetPVarInt(playerid, "contacts_slot")][Name], 25, "%s", temp);
		    contacts_info[playerid][GetPVarInt(playerid, "contacts_slot")][Phone] = GetPVarInt(playerid, "contacts_number");
            SaveContacts(playerid);
            SCM(playerid, COLOR_PAPAYA, "Контакт добавлен");
			DeletePVar(playerid, "contacts_slot"), DeletePVar(playerid, "contacts_number");
		}
		case 28:
		{
			if(!response) return 1;
		    if(listitem == 0) cmd::phoneinv(playerid);
		    if(listitem == 1) cmd::contacts(playerid);
		    if(listitem == 2)
			{
			    SPD(playerid, 29, DIALOG_STYLE_INPUT, "Позвонить", "{FFFFFF}Введите номер телефона / имя контакта: ", "Ок", "Отмена");
			}
			if(listitem == 3)
			{
			    SPD(playerid, 30, DIALOG_STYLE_INPUT, "SMS", "{FFFFFF}Введите номер телефона / имя контакта: ", "Ок", "Отмена");
			}
			if(listitem == 4) cmd::smshistory(playerid);
		}
		case 29:
		{
		    if(!response) return 1;
			cmd_call(playerid, inputtext);
		}
		case 30:
		{
		    if(!response) return 1;
		    SetPVarString(playerid, "sms_send", inputtext);
            SPD(playerid, 31, DIALOG_STYLE_INPUT, "SMS", "{FFFFFF}Введите текст сообщения: ", "Ок", "Отмена");
	 	}
	 	case 31:
	 	{
            if(!response) return DeletePVar(playerid, "sms_send");
	 	    new str[25];
		 	new string[128];
            GetPVarString(playerid, "sms_send", str, 25);
            format(string, sizeof(string), "%s %s", str, inputtext);
			cmd_sms(playerid, string);
	 	}
	 	case 32:
	 	{
	 	    if(!response) return 1;
   			SetPVarInt(playerid, "prinv_slot", listitem);
	 	    SPD(playerid, 33, DIALOG_STYLE_INPUT, "Забрать", "{FFFFFF}Введите количество, которое хотите забрать:", "Ок", "Отмена");
	 	}
	 	case 33:
	 	{
	 	    if(!response) return 1;
	 	    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner])
			{
		 	    new prslot = GetPVarInt(playerid, "prinv_slot"), count_take = strval(inputtext), li = GetLocalIdProp(character_info[playerid][prop]);
	      		if(count_take < 1 || count_take > prop_info[li][inv][count][prslot]) return SCM(playerid, COLOR_GRAY, "Неверное количество.");
	      		if(!Items[prop_info[li][inv][id][prslot]][compound]) 
	       		{
					count_take = prop_info[li][inv][count][prslot];
					if(prop_info[li][inv][id][prslot] == 0) return 1;
					new str[64];
					format(str, sizeof(str), "достает %s(%d) из имущества.", Items[prop_info[li][inv][id][prslot]][Name], count_take);
					giveitem(playerid, prop_info[li][inv][id][prslot], count_take);
					OOCMSG(playerid, str);
					deleteitemslotpr(li, prslot);
				}
				else
				{
					new giveitemid = prop_info[li][inv][id][prslot];
					if(!deleteitempr(li, prop_info[li][inv][id][prslot], count_take)) return 1;
					new str[64];
					format(str, sizeof(str), "достает %s(%d) из имущества.", Items[giveitemid][Name], count_take);
					giveitem(playerid, giveitemid, count_take);
					OOCMSG(playerid, str);
				}
			}
	 	}
	 	case 34:
	 	{
			if(!response) return 1;
	 	    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner])
	 	    {
	 	        new li = GetLocalIdProp(character_info[playerid][prop]), count_take = strval(inputtext), prslot = player_info[playerid][inv_selected];
	 	        if(!Items[character_info[playerid][inv][id][prslot]][compound]) count_take = character_info[playerid][inv][count][prslot];
	 	        if(count_take < 1 || count_take > character_info[playerid][inv][count][prslot]) return SCM(playerid, COLOR_GRAY, "Неверное количество.");
				if(!character_info[playerid][inv][id][prslot]) return 1;
	 	        if(giveitempr(li, character_info[playerid][inv][id][prslot], count_take))
				{
					new str[64];
					format(str, sizeof(str), "кладет %s(%d) в имущество.", Items[character_info[playerid][inv][id][prslot]][Name], count_take);
					if(!Items[character_info[playerid][inv][id][prslot]][compound]) deleteitemslot(playerid, prslot);
					else deleteitem(playerid, character_info[playerid][inv][id][prslot], count_take);
       				OOCMSG(playerid, str);
				}
	 	    }
	 	}

	 	case 35:
	 	{
	 	    if(!response) return 1;
	 	    if(IsAdmin(playerid, 5)) return 1;
	 	    new Float:x, Float:y, Float:z, myinterior = GetPlayerInterior(playerid), vw = GetPlayerVirtualWorld(playerid);
			switch(listitem)
			{
			    case 0:
			    {
                    SPD(playerid, 36, DIALOG_STYLE_INPUT, "Создание входа", "Введите текст входа: ", "Ввести", "Отмена");
			    }
			    case 1:
			    {
			        GetPlayerPos(playerid, x,y,z);
			        SetPVarFloat(playerid, "posX", x);
					SetPVarFloat(playerid, "posY", y);
					SetPVarFloat(playerid, "posZ", z);
					SetPVarInt(playerid, "vworld", vw);
					SetPVarInt(playerid, "intid", myinterior);
					SCM(playerid, COLOR_LIGHTBLUE, "Вы сохранили координаты входа!");
					cmd::entercreate(playerid);
			    }
			    case 2:
			    {
       				GetPlayerPos(playerid, x,y,z);
           			SetPVarFloat(playerid, "posXE", x);
					SetPVarFloat(playerid, "posYE", y);
					SetPVarFloat(playerid, "posZE", z);
					SetPVarInt(playerid, "vworldE", vw);
					SetPVarInt(playerid, "intidE", myinterior);
					SCM(playerid, COLOR_LIGHTBLUE, "Вы сохранили координаты выхода!");
					cmd::entercreate(playerid);
			    }
			    case 3:
			    {
					new qu[512], temp[24];
					vw = GetPVarInt(playerid, "vworld"), myinterior = GetPVarInt(playerid, "intid");
					new virtualworldE = GetPVarInt(playerid, "vworldE"), interiorE = GetPVarInt(playerid, "intidE");
					x = GetPVarFloat(playerid, "posX"), y = GetPVarFloat(playerid, "posY"), z = GetPVarFloat(playerid, "posZ");
					new Float:xe = GetPVarFloat(playerid, "posXE"), Float:ye = GetPVarFloat(playerid, "posYE"), Float:ze = GetPVarFloat(playerid, "posZE");
                    GetPVarString(playerid, "enter_text", temp, 24);
					if(x == 0 || y == 0 || z == 0 || xe == 0 || ye == 0 || ze == 0) return SCM(playerid, COLOR_GRAY, "Вы должны назначть координаты!");
			 		format(qu, sizeof(qu), "INSERT INTO `enters`(`text`, `x`, `y`, `z`, `vworld`, `intid`, `xe`, `ye`, `ze`, `vworlde`, `intide`) VALUES ('%s',%f,%f,%f,%d,%d,%f,%f,%f,%d,%d)",
			 			temp, x,y,z, vw, myinterior,
				 		xe,ye,ze, virtualworldE, interiorE);
					mysql_function_query(dbHandle, qu, false, "", "");
					UnLoadEnters();
					LoadEnters();
					SCM(playerid, COLOR_LIGHTBLUE, "Вы установили вход!");
			    }
			}
	 	}
	 	case 36:
	 	{
	 	    if(!response) return 1;
	 	    SetPVarString(playerid, "enter_text", inputtext);
            printf("%s", inputtext);
	 	    SCM(playerid, COLOR_LIGHTBLUE, "Вы сохранили текст входа");
	 	    cmd::entercreate(playerid);
	 	}
	 	case 39:
	 	{
	 	    if(!response) return 1;
	 	    switch(listitem)
	 	    {
	 	        case 0:
	 	        {
	 	            SPD(playerid, 40, DIALOG_STYLE_INPUT, "Забрать деньги", "Введите количество денег, которое хотите забрать из дома: ", "Ввести", "Назад");
	 	        }
	 	        case 1:
	 	        {
	 	            SPD(playerid, 41, DIALOG_STYLE_INPUT, "Положить деньги", "Введите количество денег, которое хотите положить в дома: ", "Ввести", "Назад");
	 	        }
	 	    }
	 	}
		case 40:
		{
		    if(!response) return cmd_pr(playerid, "money");
			if(OwnerInProp(playerid))
			{
			    new propid = GetLocalIdProp(character_info[playerid][prop]);
			    if(strval(inputtext) > prop_info[propid][money]) return SCM(playerid, COLOR_GRAY, "В имуществе недостаточно денег!");
				if(strval(inputtext) < 1 || strval(inputtext) > 1000000) return SCM(playerid, COLOR_GRAY, "Вы ввели неверное количество!");
                prop_info[propid][money] -= strval(inputtext);
				givemoney(playerid, strval(inputtext), "from house");
			}
		}
		case 41:
		{
		    if(!response) return cmd_pr(playerid, "money");
		    if(OwnerInProp(playerid))
			{
		    	if(takemoney(playerid, strval(inputtext), "to house") == 1)
			    {
					prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += strval(inputtext);
					SCM(playerid, COLOR_GREEN, "Вы положили деньги в имущество");
			    }
			    else SCM(playerid, COLOR_GRAY, "У вас недостаточно денег");
			}
		}
		case 42:
		{
		    if(!response) return 1;
		    cmd_charge(playerid, inputtext);
		}
		case 43:
		{
		    if(!response) return 1;
		    if(!InPropType(playerid, 1)) return 1;
			if(takemoney(playerid, list_store[listitem][price], "buy item 24/7") == 1)
   			{
				if(list_store[listitem][iditem] == 15)
	 			{
				 	create_phone(playerid);
				 	return SCM(playerid, COLOR_GREEN, "Вы совершили покупку");
				}
				else if(list_store[listitem][iditem] == 84)
	 			{
					if(!giveitem(playerid, 84, 50))
						return givemoney(playerid, list_store[listitem][price], "no itemslot for buy item");
				 	
					return SCM(playerid, COLOR_GREEN, "Вы совершили покупку");
				}
   			    else if(!giveitem(playerid, list_store[listitem][iditem], 1))
				   return givemoney(playerid, list_store[listitem][price], "no itemslot for buy item");
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_store[listitem][price]-(list_store[listitem][price]/4);
				SCM(playerid, COLOR_GREEN, "Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_GRAY, "У вас недостаточно денег");
		}
		case 44:
		{
		    if(!response) return 1;
		    new skinid = strval(inputtext);
		    BuySkin(playerid, skinid);
		}
		case 45:
		{
		    if(!response) return 1;
		    if(IsAdmin(playerid, 5)) return 1;
		    new select_faction;
		    if(listitem > 0)
		    {
			    for(new i=0; i<sizeof(factions); i++)
				{
				    if(strlen(factions[i][Name]) < 1) continue;
					select_faction++;
					if(select_faction == listitem)
					{
						SetPVarInt(playerid, "select_faction", i);
						break;
					}
				}
				ShowPlayerDialog(playerid, 46, DIALOG_STYLE_TABLIST, factions[GetPVarInt(playerid, "select_faction")][Name], "Изменить название\nИзменить тип\nИзменить лидера\nЗаморозка\nУдалить", "Выбрать", "Отмена");
			}
			else
			{
				mysql_function_query(dbHandle, "INSERT INTO `factions`(`name`, `leader`, `type`, `freeze`) VALUES ('New Faction', 0, 0, 0)", true, "", "");
				new str[128];
				format(str, sizeof(str), "%s(%d) создал новую фракцию", player_info[playerid][login], playerid);
		        AdminLog(str);
				LoadFactions();
			}
		}
		case 46:
		{
		    if(IsAdmin(playerid, 5)) return 1;
		    if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
				    ShowPlayerDialog(playerid, 47, DIALOG_STYLE_INPUT, factions[GetPVarInt(playerid, "select_faction")][Name], "{FFFFFF}Введите новое название для фракции: ", "Ввод", "Отмена");
				}
				case 1:
				{
				    ShowPlayerDialog(playerid, 48, DIALOG_STYLE_TABLIST, factions[GetPVarInt(playerid, "select_faction")][Name], "{FFFFFF}Государственная\nКоммерческая\nБанда\nМафия", "Ввод", "Отмена");
				}
				case 2:
				{
				    ShowPlayerDialog(playerid, 49, DIALOG_STYLE_INPUT, factions[GetPVarInt(playerid, "select_faction")][Name], "{FFFFFF}Введите ID персонажа: ", "Ввод", "Отмена");
				}
				case 3:
				{
					ShowPlayerDialog(playerid, 50, DIALOG_STYLE_MSGBOX, factions[GetPVarInt(playerid, "select_faction")][Name], "{FFFFFF}Во время заморозки, все функции фракции временно отключаются. Выберите нужное действие:", "FREEZE", "UNFREEZE");
				}
				case 4:
				{
				    ShowPlayerDialog(playerid, 53, DIALOG_STYLE_MSGBOX, factions[GetPVarInt(playerid, "select_faction")][Name], "{FFFFFF}Вы уверены, что хотите удалить фракцию?", "Да", "Нет");
				}
			}
			//DeletePVar(playerid, "select_faction");
		}
		case 47:
		{
		    if(IsAdmin(playerid, 5)) return 1;
		    if(!response) return 1;
		    new temp[64], qu[256];
			if(strlen(inputtext) > 2)
			{
	   		 	mysql_real_escape_string(inputtext, temp);
				format(qu, sizeof(qu), "UPDATE `factions` SET name='%s' where id=%d", temp, GetPVarInt(playerid, "select_faction"));
				mysql_function_query(dbHandle, qu, true, "", "");
				new str[128];
				format(str, sizeof(str), "%s(%d) обновил имя фракции ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
		        AdminLog(str);
				LoadFactions();
				SCM(playerid, COLOR_PAPAYA, "Вы обновили информацию о фракции!");
			}
			else SCM(playerid, COLOR_GRAY, "Название фракции должно содержать в себе больше 2-х символов");
			DeletePVar(playerid, "select_faction");

		}
		case 48:
		{
		    if(IsAdmin(playerid, 5)) return 1;
		    if(!response) return 1;
  			new temp = listitem+1, qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET type='%d' where id=%d", temp, GetPVarInt(playerid, "select_faction"));
			mysql_function_query(dbHandle, qu, true, "", "");
			new str[128];
			format(str, sizeof(str), "%s(%d) обновил тип фракции ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
	        AdminLog(str);
			LoadFactions();
			SCM(playerid, COLOR_PAPAYA, "Вы обновили информацию о фракции!");
			DeletePVar(playerid, "select_faction");
		}
		case 49:
		{
		    if(IsAdmin(playerid, 5)) return 1;
		    if(!response) return 1;
		    new temp;
		    if(sscanf(inputtext,"u", temp)) return SCM(playerid, COLOR_GRAY, "Вы ввели неверный ID персонажа!");
		    new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET leader=%d where id=%d", temp, GetPVarInt(playerid, "select_faction"));
			mysql_function_query(dbHandle, qu, true, "", "");
			new str[128];
			format(str, sizeof(str), "%s(%d) обновил лидера фракции ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
   			AdminLog(str);
			LoadFactions();
			SCM(playerid, COLOR_PAPAYA, "Вы обновили информацию о фракции!");
			DeletePVar(playerid, "select_faction");
		}
		case 50:
		{
  			if(IsAdmin(playerid, 5)) return 1;
		    if(response)
		    {
	     		new qu[128];
				format(qu, sizeof(qu), "UPDATE `factions` SET freeze=1 where id=%d", GetPVarInt(playerid, "select_faction"));
				mysql_function_query(dbHandle, qu, true, "", "");
				new str[128];
				format(str, sizeof(str), "%s(%d) заморозил фракцию ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
   				AdminLog(str);
		    }
		    else
		    {
  				new qu[128];
				format(qu, sizeof(qu), "UPDATE `factions` SET freeze=0 where id=%d", GetPVarInt(playerid, "select_faction"));
				mysql_function_query(dbHandle, qu, true, "", "");
				new str[128];
				format(str, sizeof(str), "%s(%d) разморозил фракцию ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
   				AdminLog(str);
		    }
			LoadFactions();
			SCM(playerid, COLOR_PAPAYA, "Вы обновили информацию о фракции!");
			DeletePVar(playerid, "select_faction");
		}
		case 51:
		{
		    if(!response) return 1;
		    if(listitem == 0) ShowPlayerDialog(playerid, 59, DIALOG_STYLE_TABLIST, "Магазин одежды", "Выбрать скин\nВвести ID скина", "Выбрать", "Отмена");
		    else
		    {
		        new str[2086];
		        for(new i=47; i<81; i++)
		        {
		        	format(str, sizeof(str), "%s%s\n", str, senderitems(i));
		        }
		        ShowPlayerDialog(playerid, 52, DIALOG_STYLE_TABLIST, "Магазин одежды", str, "Выбрать", "Отмена");
		    }
		}
		case 52:
		{
		    if(!response) return 1;
		    if(!InPropType(playerid, 2)) return 1;
		    if(listitem+47 < 47 || listitem+47 > 90) return 1;
		    new buy_itemid = listitem+47;
			if(takemoney(playerid, 100, "buy attach item") == 1)
   			{
		    	if(!giveitem(playerid, buy_itemid, 1))
				   return givemoney(playerid, list_store[listitem][price], "no itemslot for buy item");
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_store[listitem][price]-(list_store[listitem][price]/4);
				SCM(playerid, COLOR_GREEN, "Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_GRAY, "У вас недостаточно денег");
		}
		case 53:
		{
		    if(IsAdmin(playerid, 5)) return 1;
			new str[128];
			format(str, sizeof(str), "%s(%d) удалил фракцию ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
			AdminLog(str);
			new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET name='', freeze=1 where id=%d", GetPVarInt(playerid, "select_faction"));
			mysql_function_query(dbHandle, qu, true, "", "");
			LoadFactions();
			SCM(playerid, COLOR_PAPAYA, "Вы удалили фракции!");
			DeletePVar(playerid, "select_faction");
		}
		case 54:
		{
			if(!InFaction(playerid)) return 1;
			if(!response) return 1;
		    switch(listitem)
		    {
				case 0:
				{
				    new str[256];
				    format(str, sizeof(str), "{FFFFFF}ID фракции: %d\n", character_info[playerid][faction]);
				    format(str, sizeof(str), "%sНазвание фракции: %s\n\n", str, factions[character_info[playerid][faction]][Name]);
				    if(InFactionType(playerid, 3) || InFactionType(playerid, 4)) format(str, sizeof(str), "%sДоступное оружие для покупки: %d\n", str, factions[character_info[playerid][faction]][guns]);
				    if(InFactionType(playerid, 3) || InFactionType(playerid, 4)) format(str, sizeof(str), "%sДоступные наркотики для покупки: %d\n", str, factions[character_info[playerid][faction]][drugs]);
				    if(InFactionType(playerid, 3) || InFactionType(playerid, 4)) format(str, sizeof(str), "%sДоступные патроны для покупки: %d\n", str, factions[character_info[playerid][faction]][bulls]);
				    if(InFaction(playerid, true)) format(str, sizeof(str), "%s\n{FFFF45}Вы являетесь лидером фракции!", str);
					ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Информация о фракции", str, "Закрыть", "");
				}
				case 1:
				{
				    cmd_members(playerid);
				}
				case 2:
				{
                    cmd_offmembers(playerid);
				}
				case 3:
				{
					ShowPlayerDialog(playerid, 58, DIALOG_STYLE_MSGBOX, "Покинуть фракцию", "Вы действительно хотите покинуть фракцию?", "Да", "Нет");
				}
				case 4:
				{
					if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
					new str[256];
					format(str, sizeof(str), "Названия рангов");
					format(str, sizeof(str), "%s\nВозможность принимать [%d ранг]", str, factions[character_info[playerid][faction]][invite_rank]);
					format(str, sizeof(str), "%s\nВозможность увольнять [%d ранг]", str, factions[character_info[playerid][faction]][uninvite_rank]);
					format(str, sizeof(str), "%s\nВозможность изменять ранг [%d ранг]", str, factions[character_info[playerid][faction]][giverank_rank]);
					
					if(InFactionType(playerid, 1) || InFactionType(playerid, 2)) format(str, sizeof(str), "%s\nЗаспавнить весь незанятый транспорт", str);
					else format(str, sizeof(str), "%s\n{b1b1b1}Заспавнить весь незанятый транспорт(недоступно){ffffff}", str);
					
					ShowPlayerDialog(playerid, 55, DIALOG_STYLE_TABLIST, "Настройки фракции", str, "Выбрать", "Отмена");
				}
		    }
		}
		case 55:
		{
			if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
		    new str[256];
			switch(listitem)
			{
			    case 0:
			    {
			        for(new i = 1; i<16; i++)
				    {
				        format(str, sizeof(str), "%s%d. %s\n", str, i, faction_ranks[character_info[playerid][faction]][i]);

				    }
				    ShowPlayerDialog(playerid, 56, DIALOG_STYLE_TABLIST, "Названия рангов", str, "Выбрать", "Отмена");
			    }
			    case 1:
			    {
			        ShowPlayerDialog(playerid, 60, DIALOG_STYLE_INPUT, "Возможность принимать", "Введите номер ранга, с которого разрешено принимать во фракцию: ", "Ввод", "Отмена");
			    }
			    case 2:
			    {
			        ShowPlayerDialog(playerid, 61, DIALOG_STYLE_INPUT, "Возможность увольнять", "Введите номер ранга, с которого разрешено увольнять из фракции: ", "Ввод", "Отмена");
			    }
			    case 3:
			    {
			        ShowPlayerDialog(playerid, 62, DIALOG_STYLE_INPUT, "Возможность изменять ранг", "Введите номер ранга, с которого разрешено изменять ранг(не больше своего): ", "Ввод", "Отмена");
			    }
				case 4:
				{
					if(!InFactionType(playerid, 1) && !InFactionType(playerid, 2)) return 1;
					fmsg(playerid, "заспавнил весь незанятый транспорт");
					for(new v; v<MAX_VEHICLES; v++) 
					{
						new bool:VehUsed=false;
						if(veh_info[v][owner] >= 0 || ntop(veh_info[v][owner]) != character_info[playerid][faction]) continue;
						foreach(new p : Player) if(GetPlayerVehicleID(p) == v) 
						{
							VehUsed = true;
							break;
						}
						if(!VehUsed) SetVehicleToRespawn(v);
					}
				}
			}
		}
		case 56:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
			SetPVarInt(playerid, "rank_select", listitem+1);
			new temp[16];
			format(temp, sizeof(temp), "%s", faction_ranks[character_info[playerid][faction]][listitem+1]);
			new str[128];
			format(str, sizeof(str), "{FFFFFF}Выбранный ранг: %s (%d)\n{b1b1b1}Введите новое название название: ", temp, GetPVarInt(playerid, "rank_select"));
			ShowPlayerDialog(playerid, 57, DIALOG_STYLE_INPUT, "Названия рангов", str, "Выбрать", "Отмена");
		}
		case 57:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
			new temp[16];
			mysql_real_escape_string(inputtext, temp);
			new qu[256];
			format(qu, sizeof(qu), "UPDATE `factions` SET `Rank%d`='%s' WHERE id=%d", GetPVarInt(playerid, "rank_select"), temp, character_info[playerid][faction]);
			mysql_function_query(dbHandle, qu, false, "", "");
			format(faction_ranks[character_info[playerid][faction]][GetPVarInt(playerid, "rank_select")], 16, "%s", temp);
			SCM(playerid, COLOR_GREEN, "Вы изменили название ранга");
		}
		case 58:
		{
		    if(!response) return 1;
            if(!InFaction(playerid)) return 1;
		    character_info[playerid][faction] = 0;
		    character_info[playerid][rank] = 0;
		    SCM(playerid, COLOR_GREEN, "Вы покинули фракцию!");
		}
		case 59:
		{
		    if(!response) return 1;
		    if(!listitem)
		    {
				SetPVarInt(playerid, "SkinBuy", 1);
    			SetPlayerFacingAngle(playerid, 0);
    			new Float:x,Float:y,Float:z;
    			GetPlayerPos(playerid, xyz);
       			SetPlayerCameraPos(playerid,x-2,y+2,z+1);
				SetPlayerCameraLookAt(playerid, 2196.4282,-1732.3303,31.1130, 0);
				FreePlayer(playerid, 0);
				SetPlayerSkin(playerid, 1);
				ShowMenuForPlayer(buy_skin_menu,playerid);
		    }
		    if(listitem)ShowPlayerDialog(playerid, 44, DIALOG_STYLE_INPUT, "Магазин одежды", "{FFFFFF}Введите ID скина, который хотите приобрести.\nЦена: 150$", "Выбрать", "Отмена");
		}
		case 60:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
		    if(strval(inputtext) < 1 || strval(inputtext) > 15) return SCM(playerid, COLOR_GRAY, "Используйте от 1 до 15 ранга");
		    factions[character_info[playerid][faction]][invite_rank] = strval(inputtext);
            new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET `invite_rank`=%d WHERE id=%d", factions[character_info[playerid][faction]][invite_rank], character_info[playerid][faction]);
		    mysql_function_query(dbHandle, qu, false, "", "");
		    SCM(playerid, COLOR_GREEN, "Вы успешно изменил права рангов!");

		}
		case 61:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
		    if(strval(inputtext) < 1 || strval(inputtext) > 15) return SCM(playerid, COLOR_GRAY, "Используйте от 1 до 15 ранга");
		    factions[character_info[playerid][faction]][uninvite_rank] = strval(inputtext);
            new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET `uninvite_rank`=%d WHERE id=%d", factions[character_info[playerid][faction]][uninvite_rank], character_info[playerid][faction]);
            mysql_function_query(dbHandle, qu, false, "", "");
            SCM(playerid, COLOR_GREEN, "Вы успешно изменил права рангов!");
		}
		case 62:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
		    if(strval(inputtext) < 1 || strval(inputtext) > 15) return SCM(playerid, COLOR_GRAY, "Используйте от 1 до 15 ранга");
		    factions[character_info[playerid][faction]][giverank_rank] = strval(inputtext);
		    new qu[128];
		    format(qu, sizeof(qu), "UPDATE `factions` SET `giverank_rank`=%d WHERE id=%d", factions[character_info[playerid][faction]][giverank_rank], character_info[playerid][faction]);
            mysql_function_query(dbHandle, qu, false, "", "");
            SCM(playerid, COLOR_GREEN, "Вы успешно изменил права рангов!");
		}
		case 63:
		{
		    if(!GetPVarInt(playerid, "invited_faction")) return 1;
		    if(!response)
		    {
		        SCM(playerid, COLOR_PAPAYA, "Вы отказались от приглашения!");
		        SCM(GetPVarInt(playerid, "invited_player"), COLOR_PAPAYA, "Игрок отказался от вступления во фракцию!");
				DeletePVar(playerid, "invited_faction");
				DeletePVar(playerid, "invited_player");
				return 1;
		    }
		    else
		    {
				character_info[playerid][faction] = GetPVarInt(playerid, "invited_faction");
				character_info[playerid][rank] = 1;
		        SCM(playerid, COLOR_PAPAYA, "Вы вступили во фракцию!");
		        SCM(GetPVarInt(playerid, "invited_player"), COLOR_PAPAYA, "Игрок принял приглашение!");
  				DeletePVar(playerid, "invited_faction");
				DeletePVar(playerid, "invited_player");
				return 1;
		    }
		}
		case 64:
		{
		    if(!response) return 1;
		    if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) return SCM(playerid, COLOR_PAPAYA, "Вызов завершен!");
			SetPVarInt(playerid, "deal_type", listitem);
			ShowPlayerDialog(playerid, 65, DIALOG_STYLE_INPUT, "Количество", "Введите необходимое количество: ", "Ввод", "Закрыть");
		}
		case 65:
		{
		    if(!response) return DeletePVar(playerid, "deal_type");
		    new count_item = strval(inputtext);
		    if(count_item < 1 || count_item > 5000)
			{
				SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: Хорошенько подумай и повтори еще раз!");
				ShowPlayerDialog(playerid, 65, DIALOG_STYLE_INPUT, "Количество", "Введите необходимое количество: ", "Ввод", "Закрыть");
				return 1;
			}
			new str[128];

			//factions[character_info[playerid][faction]][guns]
		 	if(list_deal[GetPVarInt(playerid, "deal_type")][iditem] == 2 &&  factions[character_info[playerid][faction]][bulls] < count_item || list_deal[GetPVarInt(playerid, "deal_type")][iditem] >= 34 && factions[character_info[playerid][faction]][guns] < count_item || list_deal[GetPVarInt(playerid, "deal_type")][iditem] < 34 && list_deal[GetPVarInt(playerid, "deal_type")][iditem] > 2 && factions[character_info[playerid][faction]][drugs] < count_item )
    		{
		    	SCM(playerid, COLOR_YELLOW, "(Телефон) Собеседник: У меня нету столько для тебя.");
				ShowPlayerDialog(playerid, 65, DIALOG_STYLE_INPUT, "Количество", "Введите необходимое количество: ", "Ввод", "Закрыть");
    			return 1;
   			}
			format(str, sizeof(str), "(Телефон) Собеседник: Окей, это обойдется тебе в %d$.", list_deal[GetPVarInt(playerid, "deal_type")][price]*count_item);
            SCM(playerid, COLOR_YELLOW, str);
			SetPVarInt(playerid, "deal_count", count_item);
			ShowPlayerDialog(playerid, 66, DIALOG_STYLE_MSGBOX, "Подтверждение", "Вы действительно хотите приобрести это?", "Да", "Нет");
		}
		case 66:
		{
		    if(!response) return DeletePVar(playerid, "deal_type");
		    if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) return SCM(playerid, COLOR_PAPAYA, "Я передумал.. Позвони мне в другое время.");
		    if(list_deal[GetPVarInt(playerid, "deal_type")][iditem] >= 34) factions[character_info[playerid][faction]][guns] -= GetPVarInt(playerid, "deal_count");
			if(list_deal[GetPVarInt(playerid, "deal_type")][iditem] < 34 && list_deal[GetPVarInt(playerid, "deal_type")][iditem] > 2) factions[character_info[playerid][faction]][drugs] -= GetPVarInt(playerid, "deal_count");
			if(list_deal[GetPVarInt(playerid, "deal_type")][iditem] == 2) factions[character_info[playerid][faction]][bulls] -= GetPVarInt(playerid, "deal_count");

			for(new i; i<MAX_PURCHASE; i++)
			{
			    if(purchase[character_info[playerid][faction]][i][count] > 0) continue;
			    purchase[character_info[playerid][faction]][i][iditem] = list_deal[GetPVarInt(playerid, "deal_type")][iditem];
			    purchase[character_info[playerid][faction]][i][count] = GetPVarInt(playerid, "deal_count");
			    purchase_price[character_info[playerid][faction]] += list_deal[GetPVarInt(playerid, "deal_type")][price]*GetPVarInt(playerid, "deal_count");
			    break;
			}

			ShowPlayerDialog(playerid, 67, DIALOG_STYLE_MSGBOX, "Подтверждение", "{FFFFFF}Вы хотите заказать что-то еще?", "Да", "Нет");
		}
		case 67:
		{
      		if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) return SCM(playerid, COLOR_PAPAYA, "Я передумал.. Позвони мне в другое время.");
		    if(!response)
		    {
				ResultPurchase(playerid);
		        return 1;
		    }
    		new str[256];
	  		format(str, sizeof(str), "Товар\tЦена\n");
	        for(new i=0; i<sizeof(list_deal); i++)
	        {
	        	format(str, sizeof(str), "%s%s\t%d$\n", str, senderitems(list_deal[i][iditem]), list_deal[i][price]);
	        }
	        ShowPlayerDialog(playerid, 64, DIALOG_STYLE_TABLIST_HEADERS, "Диллер", str, "Выбрать", "Отмена");
		}
		case 68:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, 3) && !InFactionType(playerid, 4) && !IsPremium(playerid, PREMIUM_BRONZE)) return 1;
			new temp[32];
			switch(listitem)
			{
				case 0:
				{
					GetPVarString(playerid, "graf_text", temp, 32);
					if(strlen(temp) < 1) return SCM(playerid, COLOR_GRAY, "Вы должны ввести текст!");
					format(temp, sizeof(temp), "");
					
					GetPVarString(playerid, "graf_color", temp, 32);
					if(strlen(temp) < 1) return SCM(playerid, COLOR_GRAY, "Вы должны выбрать цвет!");
					format(temp, sizeof(temp), "");
					
					GetPVarString(playerid, "graf_font", temp, 32);
					if(strlen(temp) < 1) return SCM(playerid, COLOR_GRAY, "Вы должны выбрать шрифт!");
					format(temp, sizeof(temp), "");
					
					if(!GetPVarInt(playerid, "graf_fontsize")) return SCM(playerid, COLOR_GRAY, "Вы должны выбрать размер шрифта!");
					
					new Float:x, Float:y, Float:z;
					GetPlayerPos(playerid, xyz);
					new obj = CreateDynamicObject( 19482, xyz, 0,0,0, -1, 0, -1, 200), str[64];
					new color[8], text[32], font[32], fontsize = GetPVarInt(playerid, "graf_fontsize");
					GetPVarString(playerid, "graf_text", text, 32);
					GetPVarString(playerid, "graf_font", font, 32);
					GetPVarString(playerid, "graf_color", color, 8);
					
					format(str, sizeof(str), "{%s}%s", color, text);
					SetDynamicObjectMaterialText(obj, 0, str, OBJECT_MATERIAL_SIZE_256x128, font, fontsize, 1, COLOR_WHITE, 0, 0);
					
					character_info[playerid][type_editobj] = 6;
					character_info[playerid][editobject] = obj;
					EditDynamicObject(playerid, obj);
				}
				case 1:
				{
					ShowPlayerDialog(playerid, 69, DIALOG_STYLE_INPUT, "Граффити", "Введите текст граффити", "Ввод", "Отмена");
				}
				case 2:
				{
					ShowPlayerDialog(playerid, 70, DIALOG_STYLE_TABLIST, "Граффити", "{FFFFFF}Чёрный\n{FFFFFF}Белый\n{FFFF00}Желтый\n{FF0000}Красный\n{0000FF}Синий\n{ADD8E6}Голубой\n{008000}Зеленый\n{FF00FF}Розовый\n{FFA500}Оранжевый", "Выбрать", "Отмена");
				}
				case 3:
				{
					ShowPlayerDialog(playerid, 71, DIALOG_STYLE_TABLIST, "Граффити", "{FFFFFF}Arial\nArial Black\nComic Sans MS\n	Courier New\nGeorgia\nImpact\nLucida Console\nTrebuchet MS\nTahoma\nWebdings\nWingdings\nSymbol", "Выбрать","Отмена");
				}
				case 4:
				{
					ShowPlayerDialog(playerid, 72, DIALOG_STYLE_INPUT, "Граффити", "Введите размер граффити от 30 до 100", "Ввод","Отмена");
				}
			}
		}
		case 69:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, 3) && !InFactionType(playerid, 4) && !IsPremium(playerid, PREMIUM_BRONZE)) return 1;
			if(strlen(inputtext) < 1 || strlen(inputtext) > 32) return SCM(playerid, COLOR_GRAY, "Вы должны использовать от 1 до 32 символов!");
			SetPVarString(playerid, "graf_text", inputtext);
			cmd_graffiti(playerid);
		}
		case 70:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, 3) && !InFactionType(playerid, 4) && !IsPremium(playerid, PREMIUM_BRONZE)) return 1;
			switch(listitem)
			{
				case 0: SetPVarString(playerid, "graf_color", "000000");
				case 1: SetPVarString(playerid, "graf_color", "FFFFFF");
				case 2: SetPVarString(playerid, "graf_color", "FFFF00");
				case 3: SetPVarString(playerid, "graf_color", "FF0000");
				case 4: SetPVarString(playerid, "graf_color", "0000FF");
				case 5: SetPVarString(playerid, "graf_color", "ADD8E6");
				case 6: SetPVarString(playerid, "graf_color", "008000");
				case 7: SetPVarString(playerid, "graf_color", "FF00FF");
				case 8: SetPVarString(playerid, "graf_color", "FFA500");
			}
			cmd_graffiti(playerid);
		}
		case 71:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, 3) && !InFactionType(playerid, 4) && !IsPremium(playerid, PREMIUM_BRONZE)) return 1;
			switch(listitem)
			{
				case 0: SetPVarString(playerid, "graf_font", "Arial");
				case 1: SetPVarString(playerid, "graf_font", "Arial Black");
				case 2: SetPVarString(playerid, "graf_font", "Comic Sans MS");
				case 3: SetPVarString(playerid, "graf_font", "Courier New");
				case 4: SetPVarString(playerid, "graf_font", "Georgia");
				case 5: SetPVarString(playerid, "graf_font", "Impact");
				case 6: SetPVarString(playerid, "graf_font", "Lucida Console");
				case 7: SetPVarString(playerid, "graf_font", "Trebuchet MS");
				case 8: SetPVarString(playerid, "graf_font", "Tahoma");
				case 9: SetPVarString(playerid, "graf_font", "Webdings");
				case 10: SetPVarString(playerid, "graf_font", "Wingdings");
				case 11: SetPVarString(playerid, "graf_font", "Symbol");
			}
			cmd_graffiti(playerid);
		}
		case 72:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, 3) && !InFactionType(playerid, 4) && !IsPremium(playerid, PREMIUM_BRONZE)) return 1;
			if(strval(inputtext) < 10 || strval(inputtext) > 100) return SCM(playerid, COLOR_GRAY, "Неверное значение!");
			SetPVarInt(playerid, "graf_fontsize", strval(inputtext));
			cmd_graffiti(playerid);
		}
		case 73:
		{	
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			switch(listitem)
			{
				case 0: ShowPlayerDialog(playerid, 74, DIALOG_STYLE_INPUT, "MDC", "{FFFFFF}Введите id игрока: ", "Ввод", "Отмена");
				case 1: ShowPlayerDialog(playerid, 78, DIALOG_STYLE_INPUT, "MDC", "{FFFFFF}Введите номер автомобиля: ", "Ввод", "Отмена");
				case 2: ShowPlayerDialog(playerid, 79, DIALOG_STYLE_INPUT, "MDC", "{FFFFFF}Введите номер имущества: ", "Ввод", "Отмена");
				
				case 4:
				{
					new str[512] = "№\tТекст\tРайон\tВремя\n";
					for(new i; i<MAX_911; i++)
					{
						if(list_911[i][id] < 1) continue;
						format(str, sizeof(str), "%s%d\t%s\t%s\t%s\n",str, list_911[i][id], list_911[i][text_911], list_911[i][Zone], list_911[i][time_911]);
					}
					ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "MDC", str, "Закрыть", "");
				}
			}
		}
		case 74:
		{
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			if(strval(inputtext) < 0 || strval(inputtext) > MAX_PLAYERS) return SCM(playerid, COLOR_GRAY, "Вы ввели неверный ID!");
			new _id_ = strval(inputtext);
			if(!IsPlayerLoged(_id_)) return SCM(playerid, COLOR_GRAY, "Игрок оффлайн");
			new str[512], temp[64];
			//printf("%d | %s", character_info[_id_][su], character_info[_id_][su_reason]);
			if(character_info[_id_][su] > 0)
			{
				format(str, sizeof(str), "{b1b1b1}_______________________________________\n\n", str);
				format(str, sizeof(str), "%s{FF6347}РОЗЫСКИВАЕТСЯ!\n", str);
				format(str, sizeof(str), "%s{ffffff}В розыске по причине: %s\n", str, character_info[_id_][su_reason]);
				format(str, sizeof(str), "%s{b1b1b1}_______________________________________\n\n\n", str);
			}
			format(str, sizeof(str), "%s{b1b1b1}Общая информация{ffffff}\n", str);
			format(str, sizeof(str), "%sПолное имя: %s\n", str, sendername(_id_));
			if(character_info[_id_][phoneslot] > 0) format(str, sizeof(str), "%sНомер: %d\n", str, character_info[_id_][phoneslot]);
			for(new i=0; i<MAX_PROP; i++)
			{
				if(prop_info[i][owner] == character_info[_id_][id]) format(str, sizeof(str), "%sID: %d | Тип: %s\n", str, prop_info[i][id], property[prop_info[i][type]]);
			}
			format(str, sizeof(str), "%s\n", str);
			
			format(str, sizeof(str), "%s{b1b1b1}Лицензии{ffffff}\n", str);
			if(character_info[_id_][driveLic]) format(temp, sizeof(temp), "{33AA33}Имеется{FFFFFF}");
			else format(temp, sizeof(temp), "{FF6347}Отсутствует{FFFFFF}");
			format(str, sizeof(str), "%sВодительские права: %s\n", str, temp);
			
			if(character_info[_id_][flyLic]) format(temp, sizeof(temp), "{33AA33}Имеется{FFFFFF}");
			else format(temp, sizeof(temp), "{FF6347}Отсутствует{FFFFFF}");
			format(str, sizeof(str), "%sЛицензия на полеты: %s\n", str, temp);
			
			if(character_info[_id_][gunLic]) format(temp, sizeof(temp), "{33AA33}Имеется{FFFFFF}");
			else format(temp, sizeof(temp), "{FF6347}Отсутствует{FFFFFF}");
			format(str, sizeof(str), "%sРазрешение на оружие: %s\n\n", str, temp);
			
			format(str, sizeof(str), "%s{b1b1b1}Судимости{ffffff}\n", str);
			format(str, sizeof(str), "%sАрестов: %d\n", str, 0);
			format(str, sizeof(str), "%sСудимости: %d\n", str, 0);
			
			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "MDC", str, "Закрыть", "");
		}
		case 75:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0: 
				{
					if(character_info[playerid][driveLic]) SCM(playerid, COLOR_GRAY, "У вас уже имееются водительские права!");
					else 
					{
						if(takemoney(playerid, 400, "buy drive lic") == 1)
						{
							character_info[playerid][driveLic] = 1;
							character_info[playerid][driveLicWarn] = 0;
							SCM(playerid, COLOR_GREEN, "Вы приобрели водительские права!");
						}
					}
				}
				case 1:
				{
					if(character_info[playerid][flyLic]) SCM(playerid, COLOR_GRAY, "У вас уже имеется данный вид лицензии!");
					else
					{
						if(takemoney(playerid, 3500, "buy fly lic") == 1)
						{
							character_info[playerid][flyLic] = 1;
							SCM(playerid, COLOR_GREEN, "Вы приобрели лицензию!");
						}	
					}
				}
			}
			ShowLicDialog(playerid);
		}
		case 76:
		{
			if(!response) return 1;
			/*ShowCarShowroom(playerid)
			{
				ShowPlayerDialog(playerid, 76, DIALOG_STYLE_TABLIST, "Автомобили", "Эконом класс\nСредний класс\nПремиум класс\nСпорт класс\nВнедорожники\nМинивены/автобусы\nРабочие\nМотоциклы/Велосипеды", "Выбрать", "Отмена");
			}*/
			new str[512];
			format(str, sizeof(str), "Транспорт\tЦена\n");
			for(new i=0; i<sizeof(BuyCars); i++) 
				if(BuyCars[i][Type] == listitem) format(str, sizeof(str), "%s%s\t%d$\n", str, BuyCars[i][Name], BuyCars[i][Price]);
			ShowPlayerDialog(playerid, 77, DIALOG_STYLE_TABLIST_HEADERS, "Транспорт", str, "Выбрать", "Закрыть");
			SetPVarInt(playerid, "BuyCarsType", listitem);
		}
		case 77:
		{
			if(!response) return ShowCarShowroom(playerid);
			new i, ii = -1;
			for(i=0; i<sizeof(BuyCars); i++) 
			{
				if(BuyCars[i][Type] == GetPVarInt(playerid, "BuyCarsType")) ii++;
				if(ii == listitem) break;
			}
			
			if(takemoney(playerid, BuyCars[i][Price], "buy car") == 1)
			{
				new qu[128];
				format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`) VALUES (%d, %d)", BuyCars[i][Model], character_info[playerid][id]);
				mysql_function_query(dbHandle, qu, false, "", "");
				SCM(playerid, COLOR_GREEN, "Вы приобрели автомобиль!");
				LoadCars(playerid);
			}
		}
		case 78:
		{
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			
			new qu[256];
			format(qu, sizeof(qu), "SELECT cars.BuyDate, cars.number, cars.model, characters.name FROM cars JOIN characters ON cars.owner=characters.id WHERE cars.number='%s'", inputtext);
			mysql_function_query(dbHandle, qu, true, "OnCarsInfo", "i", playerid);
		}
		case 79:
		{
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			if(strval(inputtext) < 1) return SCM(playerid, COLOR_GRAY, "Вы ввели неверное значение!");
			new i;
			for(; i<MAX_PROP; i++)
			{
				if(prop_info[i][id] == strval(inputtext)) break;
				else if(i == MAX_PROP) return SCM(playerid, COLOR_GRAY, "Такого имущества не существует!");
			}
			//ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "MDC", str, "Закрыть", "");
			SetPVarInt(playerid, "target_prop", strval(inputtext));
			new qu[128];
			format(qu, sizeof(qu), "SELECT characters.name FROM characters JOIN property ON property.owner=characters.id WHERE property.id=%d", GetPVarInt(playerid, "target_prop"));
			mysql_function_query(dbHandle, qu, true, "OnPropInfo", "i", playerid);
		}
		case 80:
		{
			if(!response) return 1;
			format(character_info[playerid][description], 256, "%s", inputtext);
			new str[180];
			format(str, sizeof(str), "описал персонажа: %s", inputtext);
			PlayerLog(playerid, str);
			new temp[256];
			mysql_real_escape_string(character_info[playerid][description], temp);
			format(str, sizeof(str), "UPDATE `description` FROM characters WHERE id=%d", temp, character_info[playerid][id]);
			mysql_function_query(dbHandle, str, false, "", "");
			cmd_description(playerid);
		}
		case 81:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					if(!IsDutyPickup(playerid)) return 1;
					
					if(IsDuty(playerid))
					{
						character_info[playerid][duty] = 0;
						fmsg(playerid, "покинул дежурство.");
						character_info[playerid][duty_gun_1] = 0;
						
						character_info[playerid][duty_gun_2] = 0;
						character_info[playerid][duty_ammo_2] = 0;
						
						character_info[playerid][duty_gun_3] = 0;
						character_info[playerid][duty_ammo_3] = 0;
						
						character_info[playerid][duty_gun_special] = 0;
						
						UpdateDutyGuns(playerid);
						SetPlayerSkin(playerid, character_info[playerid][skin]);
						for(new i; i<MAX_ATTACH; i++)
						{
							if(attach[playerid][i][iditem] == 86 || attach[playerid][i][iditem] == 87 || attach[playerid][i][iditem] == 88) ResetAttach(playerid, i);
						}
						new inv_count[3];
						inv_count[0] = checkitem(playerid, 86);
						inv_count[1] = checkitem(playerid, 87);
						inv_count[2] = checkitem(playerid, 88);
						if(inv_count[0] > -1) deleteitemslot(playerid, inv_count[0]);
						if(inv_count[1] > -1) deleteitemslot(playerid, inv_count[1]);
						if(inv_count[2] > -1) deleteitemslot(playerid, inv_count[2]);
						
						attach_player_update(playerid);
						UpdatePlayerColor(playerid);
					}
					else
					{
						ShowPlayerDialog(playerid, 84, DIALOG_STYLE_LIST, "DUTY", "Жетон №1\nЖетон №2\nБейдж", "Выбрать", "Закрыть");
					}
				}
				case 1:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) return SCM(playerid, COLOR_GRAY, "Вы должны быть на дежурстве!");
					if(checkitem(playerid, 19) > -1 || checkitem(playerid, 18) > -1) return SCM(playerid, COLOR_GRAY, "У вас уже есть бронежилет!");
					giveitem(playerid, 18, 1);
				}
				case 2:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) return SCM(playerid, COLOR_GRAY, "Вы должны быть на дежурстве!");
					if(checkitem(playerid, 19) > -1 || checkitem(playerid, 18) > -1) return SCM(playerid, COLOR_GRAY, "У вас уже есть бронежилет!");
					giveitem(playerid, 19, 1);
				}
				case 3:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) return SCM(playerid, COLOR_GRAY, "Вы должны быть на дежурстве!");
					ShowPlayerDialog(playerid, 82, DIALOG_STYLE_LIST, "ADUTY", "Полицейская дубинка\nDesert Eagle\nShotgun\nMP5\nM4A1\nCountry Rifle\nSniper Rifle", "Выбрать", "Отмена");
				}
				case 4:
				{
					if(!DeleteDutyGuns(playerid)) return SCM(playerid, COLOR_GRAY, "У вас нет служебного оружия!");
				}
				case 5:
				{
					ShowPlayerDialog(playerid, 83, DIALOG_STYLE_LIST, "DUTY", "Стандартный\n280\n281\n282\n283\n265\n266\n267\n284\n285\n286\n287\n303\n304\n305\n306\n307", "Выбрать", "Закрыть");
				}
			}
		}
		case 82:
		{
			if(!response) return 1;
			if(!IsDuty(playerid)) return SCM(playerid, COLOR_GRAY, "Вы должны быть на дежурстве!");
			if(character_info[playerid][gun] > 0) return SCM(playerid, COLOR_GRAY, "У вас в руках не должно быть личного оружия!");
			switch(listitem)
			{
				case 0: character_info[playerid][duty_gun_1] = 3;
				case 1: character_info[playerid][duty_gun_2] = 24, character_info[playerid][duty_ammo_2] = 100;
				case 2: character_info[playerid][duty_gun_3] = 25, character_info[playerid][duty_ammo_3] = 70;
				case 3: character_info[playerid][duty_gun_3] = 29, character_info[playerid][duty_ammo_3] = 250;
				case 4: character_info[playerid][duty_gun_3] = 31, character_info[playerid][duty_ammo_3] = 350;
				case 5: character_info[playerid][duty_gun_3] = 33, character_info[playerid][duty_ammo_3] = 70;
				case 6: character_info[playerid][duty_gun_3] = 34, character_info[playerid][duty_ammo_3] = 70;
				default: return 1;
			}
			UpdateDutyGuns(playerid);
			ShowPlayerDialog(playerid, 82, DIALOG_STYLE_LIST, "ADUTY", "Полицейская дубинка\nDesert Eagle\nShotgun\nMP5\nM4A1\nCountry Rifle\nSniper Rifle", "Выбрать", "Отмена");
		}
		case 83:
		{
			if(!response) return 1;
			if(!IsDuty(playerid)) return SCM(playerid, COLOR_GRAY, "Вы должны быть на дежурстве!");
			switch(listitem)
			{
				case 1: character_info[playerid][duty_skin] = 280;
				case 2: character_info[playerid][duty_skin] = 281;
				case 3: character_info[playerid][duty_skin] = 282;
				case 4: character_info[playerid][duty_skin] = 283;
				case 5: character_info[playerid][duty_skin] = 265;
				case 6: character_info[playerid][duty_skin] = 266;
				case 7: character_info[playerid][duty_skin] = 267;
				case 8: character_info[playerid][duty_skin] = 284;
				case 9: character_info[playerid][duty_skin] = 285;
				case 10: character_info[playerid][duty_skin] = 286;
				case 11: character_info[playerid][duty_skin] = 287;
				case 12: character_info[playerid][duty_skin] = 303;
				case 13: character_info[playerid][duty_skin] = 304;
				case 14: character_info[playerid][duty_skin] = 305;
				case 15: character_info[playerid][duty_skin] = 306;
				case 16: character_info[playerid][duty_skin] = 307;
				default: character_info[playerid][duty_skin] = character_info[playerid][skin];
				
			}
			SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			UpdatePlayerColor(playerid);
		}
		case 84:
		{
			if(!response) return 1;
			if(!IsDutyPickup(playerid)) return 1;
			character_info[playerid][duty] = 1;
			SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			fmsg(playerid, "вышел на дежурство.");
			switch(listitem)
			{
				case 0: giveitem(playerid, 86, 1);
				case 1: giveitem(playerid, 87, 1);
				case 2: giveitem(playerid, 88, 1);
			}
			UpdatePlayerColor(playerid);
		}
		case 85:
		{
			if(!response) return 1;
			if(listitem < 0 || listitem > 17) return SCM(playerid, COLOR_RED, "Произошла внутренняя ошибка. (FAKE BONE NUMBER)");
            //SetPVarInt(playerid, "attach_bone", listitem+1);
			SetPVarInt(playerid, "change_gunattach", 1);
			
			RemovePlayerAttachedObject(playerid, MAX_ATTACH+1);
			SetPlayerAttachedObject(playerid, MAX_ATTACH+1, Items[GetItemByGun(character_info[playerid][gun])][Model], listitem+1);
			EditAttachedObject(playerid, MAX_ATTACH+1);
		}
		case 86:
		{
			if(GetPVarInt(playerid, "frisk") <= 0) return 1;
			new friskid = GetPVarInt(playerid, "frisk")-1;
			if(!response)
			{
				SCM(friskid, COLOR_PAPAYA, "Игрок отказался от обыска!");
				SCM(playerid, COLOR_PAPAYA, "Вы отказались от обыска!");
			}
			else
			{
				FriskPlayer(friskid, playerid);
			}
			DeletePVar(playerid, "frisk");
		}
		case 87:
		{
			if(!response) return 1;
			new targetid = GetPVarInt(playerid, "targetid") - 1;
			if(targetid <= -1) return 1;
			new bool:taked = false;
			for(new i; i<MAX_INV_SLOTS; i++)
			{
				if(GunID(character_info[targetid][inv][id][i]) && listitem == 0 || DrugID(character_info[targetid][inv][id][i]) && listitem == 1 )
				{
					if(giveitem(playerid, character_info[targetid][inv][id][i], character_info[targetid][inv][count][i]))
					{
						new str[180];
						new itemid = character_info[targetid][inv][id][i];
						deleteitemslot(targetid, i);
						if(!taked) 
						{
							format(str, sizeof(str), "Вы изъяли у %s: ", sendername(targetid));
							SCM(playerid, COLOR_PAPAYA, str);
							format(str, sizeof(str), "%s изъял у вас: ", sendername(playerid));
							SCM(targetid, COLOR_PAPAYA, str);
							taked = true;
						}
						format(str, sizeof(str), "%s", Items[itemid][Name]);
						SCM(playerid, COLOR_GRAY, str);
						format(str, sizeof(str), "%s", Items[itemid][Name]);
						SCM(targetid, COLOR_GRAY, str);
					}
				}
			}
			if(!taked) SCM(playerid, COLOR_GRAY, "Ничего не найдено!");
		}
		case 88:
		{
			if(!response) return 1;
			
			for(new i; i<MAX_VEHICLES; i++)
			{
				// GetPlayerVehicleID(playerid) > 1 && character_info[playerid][id] == veh_info[GetPlayerVehicleID(playerid)][owner] && veh_info[GetPlayerVehicleID(playerid)] > 0 || GetPlayerVehicleID(playerid) > 1 && character_info[playerid][factionid] == ntop(veh_info[GetPlayerVehicleID(playerid)][owner]) && veh_info[GetPlayerVehicleID(playerid)] < 0 || 
				
				new Float:x, Float:y, Float:z;
				GetCoordBootVehicle(i, xyz);
				
				if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot])
				{
					new count_take = strval(inputtext), vehslot = player_info[playerid][inv_selected];
					if(!Items[character_info[playerid][inv][id][vehslot]][compound]) count_take = character_info[playerid][inv][count][vehslot];
					if(count_take < 1 || count_take > character_info[playerid][inv][count][vehslot]) return SCM(playerid, COLOR_GRAY, "Неверное количество.");
					if(!character_info[playerid][inv][id][vehslot]) return 1;
					if(giveitemveh(i, character_info[playerid][inv][id][vehslot], count_take))
					{
						new str[64];
						format(str, sizeof(str), "кладет %s(%d) в транспорт.", Items[character_info[playerid][inv][id][vehslot]][Name], count_take);
						if(!Items[character_info[playerid][inv][id][vehslot]][compound]) deleteitemslot(playerid, vehslot);
						else deleteitem(playerid, character_info[playerid][inv][id][vehslot], count_take);
						OOCMSG(playerid, str);
					}
					return 1;
				}
			}
			return SCM(playerid, COLOR_GRAY, "Рядом нет транспорта с открытым багажником!");
		}
		case 89:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0: cmd_inventory(playerid);
				case 1: cmd_carinv(playerid);
			}
		}
		case 90:
		{
			if(!response) return 1;
   			SetPVarInt(playerid, "vehinv_slot", listitem);
	 	    SPD(playerid, 91, DIALOG_STYLE_INPUT, "Забрать", "{FFFFFF}Введите количество, которое хотите забрать:", "Ок", "Отмена");
		}
		case 91:
		{
			if(!response) return 1;
			for(new i; i<MAX_VEHICLES; i++)
			{
				new Float:x, Float:y, Float:z;
				GetCoordBootVehicle(i, xyz);
				
				if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot])
				{
					new vehslot = GetPVarInt(playerid, "vehinv_slot"), count_take = strval(inputtext);
					if(count_take < 1 || count_take > veh_info[i][inv][count][vehslot]) return SCM(playerid, COLOR_GRAY, "Неверное количество.");
					if(!Items[veh_info[i][inv][id][vehslot]][compound]) 
					{
						count_take = veh_info[i][inv][count][vehslot];
						if(veh_info[i][inv][id][vehslot] == 0) return 1;
						new str[64];
						format(str, sizeof(str), "достает %s(%d) из транспорта.", Items[veh_info[i][inv][id][vehslot]][Name], count_take);
						giveitem(playerid, veh_info[i][inv][id][vehslot], count_take);
						OOCMSG(playerid, str);
						deleteitemslotveh(i, vehslot);
					}
					else
					{
						new giveitemid = veh_info[i][inv][id][vehslot];
						if(!deleteitemveh(i, veh_info[i][inv][id][vehslot], count_take)) return 1;
						new str[64];
						format(str, sizeof(str), "достает %s(%d) из транспорта.", Items[giveitemid][Name], count_take);
						giveitem(playerid, giveitemid, count_take);
						OOCMSG(playerid, str);
					}
					return 1;
				}
			}
		}
		case 92:
		{
			if(!response) return 1;
			new str[128];
			switch(listitem)
			{
				case 0:
				{
					format(str, sizeof(str), "{FFFFFF}Баланс: %d$\nВведите сумму для снятия:", character_info[playerid][bank]);
					ShowPlayerDialog(playerid, 93, DIALOG_STYLE_INPUT, "Банкомат", str, "Ввести", "Отмена");
				}
				case 1:
				{
					format(str, sizeof(str), "{FFFFFF}Денег на руках: %d$\nВведите сумму пополнения счета:", character_info[playerid][money]);
					ShowPlayerDialog(playerid, 94, DIALOG_STYLE_INPUT, "Банкомат", str, "Ввести", "Отмена");
				}
				case 2:
				{
					format(str, sizeof(str), "{FFFFFF}Баланс: %d$\nВведите сумму для перевода:", character_info[playerid][bank]);
					ShowPlayerDialog(playerid, 95, DIALOG_STYLE_INPUT, "Банкомат", str, "Ввести", "Отмена");
				}
			}
		}
		case 93:
		{
			if(!response) return 1;
			if(!InATM(playerid)) return 1;
			new moneycount = strval(inputtext);
			if(moneycount < 1 || moneycount > 10000000) return SCM(playerid, COLOR_GRAY, "Используйте число от 1 до 10000000");
			if(character_info[playerid][bank] < moneycount) return SCM(playerid, COLOR_GRAY, "У вас нет такого количества денег!");
			character_info[playerid][bank] -= moneycount;
			givemoney(playerid, moneycount, "from bank");
			if(!BankSMS(playerid, "С вашего баланса были сняты средства.", moneycount)) SCM(playerid, COLOR_GREEN, "Вы успешно сняли деньги с банковского счета!");
		}
		case 94:
		{
			if(!response) return 1;
			if(!InATM(playerid)) return 1;
			new moneycount = strval(inputtext);
			if(moneycount < 1 || moneycount > 10000000) return SCM(playerid, COLOR_GRAY, "Используйте число от 1 до 10000000");
			if(character_info[playerid][money] < moneycount) return SCM(playerid, COLOR_GRAY, "У вас нет такого количества денег!");
			character_info[playerid][bank] += moneycount;
			takemoney(playerid, moneycount, "in bank");
			if(!BankSMS(playerid, "Ваш счет в банке был пополнен.", moneycount)) SCM(playerid, COLOR_GREEN, "Вы успешно пополнили банковский счет!");
		}
		case 95:
		{
			if(!response) return 1;
			new moneycount = strval(inputtext);
			if(moneycount < 1 || moneycount > 10000000) return SCM(playerid, COLOR_GRAY, "Используйте число от 1 до 10000000");
			if(character_info[playerid][bank] < moneycount) return SCM(playerid, COLOR_GRAY, "У вас нет такого количества денег на банковском счету!");
			SetPVarInt(playerid, "transfer_money", moneycount);
			ShowPlayerDialog(playerid, 96, DIALOG_STYLE_INPUT, "Банкомат", "{ffffff}Введите номер счета для перевода:\n{b1b1b1}(( Введите ID персонажа или часть его ника! ))", "Выбрать", "Отмена"); 
		}
		case 96:
		{
			if(!InATM(playerid)) return 1;
			
			return SCM(playerid, COLOR_GRAY, "Технические работы на стороне банка. Перевод денег временно недоступен.");
			
			new user;
			if(sscanf(inputtext,"u", user) || !response)
			{
				DeletePVar(playerid, "transfer_money");
				return 1;
			}
			if(!IsPlayerLoged(user)) 
			{
				DeletePVar(playerid, "transfer_money");
				SCM(playerid, COLOR_GRAY, "Игрок оффлайн");
				return 1;
			}
			new moneycount = GetPVarInt(playerid, "transfer_money");
			if(moneycount < 1 || moneycount > 10000000) 
			{
				DeletePVar(playerid, "transfer_money");
				return SCM(playerid, COLOR_GRAY, "Используйте число от 1 до 10000000");
			}
			if(character_info[playerid][bank] < moneycount) 
			{
				DeletePVar(playerid, "transfer_money");
				return SCM(playerid, COLOR_GRAY, "У вас нет такого количества денег на банковском счету!");
			}
			character_info[user][bank] += moneycount;
			character_info[playerid][bank] -= moneycount;
			BankSMS(user, "Ваш банковский счет был пополнен!");
			new str[128];
			format(str, sizeof(str), "С вашего баланса совершен перевод на счет %06d", character_info[user][id]);
			if(!BankSMS(playerid, str, moneycount)) SCM(playerid, COLOR_GREEN, "Вы успешно совершили перевод!");
		}
		case 97:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					new str[256] = "{b1b1b1}";
					for(new i; i<sizeof(property); i++) 
						format(str, sizeof(str), "%s\n%d. %s", str, i, property[i]);
					format(str, sizeof(str), "%s\n\n{ffffff}Введите ID(номер) типа имущества: ", str);
					ShowPlayerDialog(playerid, 99, DIALOG_STYLE_INPUT, "Создать имущество", str, "Выбрать", "Отмена");
				}
				case 1:
				{
					ShowPlayerDialog(playerid, 100, DIALOG_STYLE_INPUT, "Создать имущество", "{ffffff}Введите стоимость для имущества: ", "Выбрать", "Отмена");
				}
				case 2:
				{
					SetPVarInt(playerid, "addprop_step2", 1);
					new floatxyz;
					GetPlayerPos(playerid, xyz);
					SetPVarFloat(playerid, "addprop_step2_posX", x);
					SetPVarFloat(playerid, "addprop_step2_posY", y);
					SetPVarFloat(playerid, "addprop_step2_posZ", z);
					SetPVarInt(playerid, "addprop_step2_int", GetPlayerInterior(playerid));
					SetPVarInt(playerid, "addprop_step2_vw", GetPlayerVirtualWorld(playerid));
					
					if(!GetPVarInt(playerid, "addprop_step2_serverint"))
					{
						cmd_serverint(playerid, "1");
						SetPVarInt(playerid, "addprop_step2_serverint", 1);
					}
					SCM(playerid, COLOR_PAPAYA, "Используйте клавиши Y и N для выбора интерьера. Воспользуйтесь командой повторно, чтобы вернуться назад или установить имущество!");
				}
			}
		}
		case 98:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					DeletePVar(playerid, "addprop_step2");
					SetPlayerPos(playerid, GetPVarFloat(playerid, "addprop_step2_posX"), GetPVarFloat(playerid, "addprop_step2_posY"), GetPVarFloat(playerid, "addprop_step2_posZ"));
					SetPlayerInt(playerid, GetPVarInt(playerid, "addprop_step2_int"));
					SetPlayerVw(playerid, GetPVarInt(playerid, "addprop_step2_vw"));
					Freeze(playerid, 2000);
					cmd_addprop(playerid);
				}
				case 1:
				{
					new str[128];
					format(str, sizeof(str), "%d %d %d", GetPVarInt(playerid, "addprop_type"), GetPVarInt(playerid, "addprop_step2_serverint"), GetPVarInt(playerid, "addprop_price"));
					cmd_setprop(playerid, str);
					
					DeletePVar(playerid, "addprop_step2");
					SetPlayerPos(playerid, GetPVarFloat(playerid, "addprop_step2_posX"), GetPVarFloat(playerid, "addprop_step2_posY"), GetPVarFloat(playerid, "addprop_step2_posZ"));
					SetPlayerInt(playerid, GetPVarInt(playerid, "addprop_step2_int"));
					SetPlayerVw(playerid, GetPVarInt(playerid, "addprop_step2_vw"));
					Freeze(playerid, 2000);
				}
			}
		}
		case 99:
		{
			if(!response) return 1;
			new target_type = strval(inputtext);
			if(strlen(property[target_type]) < 2) return SCM(playerid, COLOR_GRAY, "Вы ввели неверное значение!");
			SetPVarInt(playerid, "addprop_type", target_type);
			cmd_addprop(playerid);
		}
		case 100:
		{
			if(!response) return 1;
			SetPVarInt(playerid, "addprop_price", strval(inputtext));
			cmd_addprop(playerid);
		}
		case 101:
		{
			if(!response) return 1;
			if(GetPVarInt(playerid, "breaking_veh_id") > 0 || GetPVarInt(playerid, "breaking_veh_id_boot") > 0)
				return SCM(playerid, COLOR_GRAY, "Вы уже взламываете транспортное средство!");
			if(checkitem(playerid, 89) == -1) return 1;
			switch(listitem)
			{
				case 0:
				{
					for(new i=1; i<MAX_VEHICLES; i++)
					{
						new Float:x, Float:y, Float:z;
						GetVehiclePos(i, xyz);
						if(GetPlayerVehicleID(playerid) == i || PlayerToPoint(2.0, playerid, xyz))
						{
							if(!veh_info[i][lock]) return SCM(playerid, COLOR_GRAY, "Этот транспорт уже открыт!");
							
							SCM(playerid, COLOR_PAPAYA, "Вы начали взлом замка!");
							SCM(playerid, COLOR_GRAY, "* Продолжительность взлома зависит от уровня защиты замка и удачи.");
							SCM(playerid, COLOR_GRAY, "* Вы можете прервать процесс нажатием клавиши быстрого бега.");
							SCM(playerid, COLOR_GRAY, "* Если вы попали в поле зрение камеры CCTV, полицейские могут получить предупреждение в любой момент!");
							SetPVarInt(playerid, "breaking_veh_id", i);
							
							if(veh_info[i][lock_type] == 2) SetPVarInt(playerid, "breaking_veh_processing", 400);
							else if(veh_info[i][lock_type] == 3) SetPVarInt(playerid, "breaking_veh_processing", 600);
							else SetPVarInt(playerid, "breaking_veh_processing", 200);
							return 1;
						}
					}
				}
				case 1:
				{
					if(!InFactionType(playerid, FACTIONTYPE_GANG) && !InFactionType(playerid, FACTIONTYPE_MAFIA)) return SCM(playerid, COLOR_GRAY, "Функция доступна только членам криминальных группировок!");
					new v;
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
					if(v == 0) return SCM(playerid, COLOR_GRAY, "Вы не находитесь у багажника транспорта или у этого транспорта нет багажника!");
					SetPVarInt(playerid, "breaking_veh_id_boot", v);
					
					if(veh_info[v][lock_type] == 2) SetPVarInt(playerid, "breaking_veh_processing", 250);
					else if(veh_info[v][lock_type] == 3) SetPVarInt(playerid, "breaking_veh_processing", 350);
					else SetPVarInt(playerid, "breaking_veh_processing", 150);
					
					SCM(playerid, COLOR_GREEN, "Вы начали взлом замка багажника!");
					SCM(playerid, COLOR_GRAY, "* Вы можете прервать процесс нажатием клавиши быстрого бега.");
					SCM(playerid, COLOR_GRAY, "* Если вы попали в поле зрение камеры CCTV, полицейские могут получить предупреждение в любой момент!");
				}
			}
		}
		case 102:
		{
			//if(!InServiceStation(playerid)) return 1;
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					ShowPlayerDialog(playerid, 103, DIALOG_STYLE_TABLIST, "TUNE", "Замок низкого класса\t700$\nЗамок среднего класса\t2000$\nЗамок выского класса\t5000$", "Выбрать", "Отмена");
				}
				case 1:
				{
					ShowPlayerDialog(playerid, 104, DIALOG_STYLE_TABLIST, "TUNE", "Сигнализация низкого класса\t1000$\nСигнализация выского класса\t3000$", "Выбрать", "Отмена");
				}
			}
		}
		case 103:
		{
			if(!response) return 1;
			if(!InServiceStation(playerid)) return 1;
			new v = GetPlayerVehicleID(playerid);
			new lock_name[24], lock_price;
			switch(listitem)
			{
				case 0: format(lock_name, sizeof(lock_name), "Замок низкого класса"), lock_price = 700;
				case 1: format(lock_name, sizeof(lock_name), "Замок среднего класса"), lock_price = 2000;
				case 2: format(lock_name, sizeof(lock_name), "Замок высокого класса"), lock_price = 5000;
				default: return 1;
			}
			
			new str[256];
			new lock_name_now[24];
			switch(veh_info[v][lock_type])
			{
				case 1: format(lock_name_now, sizeof(lock_name_now), "Низкого класса");
				case 2: format(lock_name_now, sizeof(lock_name_now), "Среднего класса");
				case 3: format(lock_name_now, sizeof(lock_name_now), "Высокого класса");
				default: format(lock_name_now, sizeof(lock_name_now), "Не определен");
			}
			format(str, sizeof(str), "{ffffff}Вы действительно хотите приобрести {33AA33}%s{ffffff} для вашего автомобиля?\nЭто обойдется вам в {33AA33}%d${ffffff}!\n\n{b1b1b1}В данный момент на транспорте установлен замок: {ffffff}%s", lock_name, lock_price, lock_name_now);
			
			SetPVarInt(playerid, "buy_lock_type", listitem+1);
			SetPVarInt(playerid, "buy_lock_money", lock_price);
			
			ShowPlayerDialog(playerid, 105, DIALOG_STYLE_MSGBOX, "TUNE", str, "Да", "Нет"); 
		}
		case 104:
		{
			if(!response) return 1;
			if(!InServiceStation(playerid)) return 1;
			new v = GetPlayerVehicleID(playerid);
			new alarm_name[28], alarm_price;
			switch(listitem)
			{
				case 0: format(alarm_name, sizeof(alarm_name), "Сигнализация низкого класса"), alarm_price = 700;
				case 1: format(alarm_name, sizeof(alarm_name), "Сигнализация высокого класса"), alarm_price = 2000;
				default: return 1;
			}
			
			new str[300];
			new alarm_name_now[24];
			switch(veh_info[v][alarm_type])
			{
				case 1: format(alarm_name_now, sizeof(alarm_name_now), "Низкого класса");
				case 2: format(alarm_name_now, sizeof(alarm_name_now), "Высокого класса");
				default: format(alarm_name_now, sizeof(alarm_name_now), "Не определена");
			}
			format(str, sizeof(str), "{ffffff}Вы действительно хотите приобрести {33AA33}%s{ffffff} для вашего автомобиля?\nЭто обойдется вам в {33AA33}%d${ffffff}!\n\n{b1b1b1}В данный момент на транспорте установлена сигналиация: {ffffff}%s", alarm_name, alarm_price, alarm_name_now);
			
			SetPVarInt(playerid, "buy_alarm_type", listitem+1);
			SetPVarInt(playerid, "buy_alarm_money", alarm_price);
			
			ShowPlayerDialog(playerid, 106, DIALOG_STYLE_MSGBOX, "TUNE", str, "Да", "Нет"); 
		}
		case 105:
		{
			if(!response) return 1;
			if(!InServiceStation(playerid)) return 1;
			new v = GetPlayerVehicleID(playerid);
			
			new buy_lock_type = GetPVarInt(playerid, "buy_lock_type");
			new buy_lock_money = GetPVarInt(playerid, "buy_lock_money");
			DeletePVar(playerid, "buy_lock_type");
			DeletePVar(playerid, "buy_lock_money");
			
			if(takemoney(playerid, buy_lock_money, "buy lock type") == 1)
			{
				veh_info[v][lock_type] = buy_lock_type;
				SCM(playerid, COLOR_GREEN, "Вы установили выбранный замок!");
			}
			else SCM(playerid, COLOR_GRAY, "У вас недостаточно денег!");
			
		}
		case 106:
		{
			if(!response) return 1;
			if(!InServiceStation(playerid)) return 1;
			new v = GetPlayerVehicleID(playerid);
			
			new buy_alarm_type = GetPVarInt(playerid, "buy_alarm_type");
			new buy_alarm_money = GetPVarInt(playerid, "buy_alarm_money");
			DeletePVar(playerid, "buy_alarm_type");
			DeletePVar(playerid, "buy_alarm_money");
			
			if(takemoney(playerid, buy_alarm_money, "buy alarm type") == 1)
			{
				veh_info[v][alarm_type] = buy_alarm_type;
				SCM(playerid, COLOR_GREEN, "Вы установили выбранную сигнализацию!");
			}
			else SCM(playerid, COLOR_GRAY, "У вас недостаточно денег!");
		}
		case 107:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, FACTIONTYPE_STATE)) return SCM(playerid, COLOR_GRAY, "Вам недоступна эта команда!");
			SetPVarInt(playerid, "faction_attach", listitem);
			
			ShowPlayerDialog(playerid, 108, DIALOG_STYLE_TABLIST, "Выберите кость", "Спина\nГолова\nПлечо левой руки\nПлечо правой руки\nЛевая рука\nПравая рука\nЛевое бедро\nПравое бедро\nЛевая нога\nПравая нога\nПравые икры\nЛевые икры\nЛевое предплечье\nПравое предплечье\nЛевая ключица\nПравая ключица\nШея\nЧелюсть", "Выбрать", "Отмена");
		}
		case 108:
		{
			if(!InFactionType(playerid, FACTIONTYPE_STATE)) return SCM(playerid, COLOR_GRAY, "Вам недоступна эта команда!");
			if(InFactionId(playerid, LSPD_FACTION) || InFactionId(playerid, SASD_FACTION) || InFactionId(playerid, LSSD_FACTION)) 
			{
				for(new i = 0; i<MAX_ATTACH; i++)
				{
					if(attach[playerid][i][iditem] == -1)
					{
						if(GetPVarInt(playerid, "faction_attach_active")) return SCM(playerid, COLOR_YELLOW, "Вы уже пользуетесь редактором");
						SetPVarInt(playerid, "faction_attach_active", true);
						SetPlayerAttachedObject(playerid, i, Items[PoliceAttaches[GetPVarInt(playerid, "faction_attach")]][Model], listitem+1);
						EditAttachedObject(playerid, i);
						return 1;
					}
				}
				return 1;
			}
		}
		case 109:
		{
			if(!response) return 1;
			if(!InFactionType(playerid, FACTIONTYPE_STATE)) return SCM(playerid, COLOR_GRAY, "Вам недоступна эта команда!");
			if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit")) return SCM(playerid, COLOR_RED, "Вы уже пользуетесь редактором!");
			
			new Float:angle, Float:x,Float:y,Float:z, obj;
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			x += floatsin(-angle, degrees);
			y += floatcos(-angle, degrees);
			obj = CreateDynamicObject(FactionObjects[listitem][Model], x, y, z-0.9, -90, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			
			character_info[playerid][editobject] = FactionObjects[listitem][Model];
			character_info[playerid][type_editobj] = 9;
			SCM(playerid, COLOR_RED, "Используйте ESC чтобы выйти!");
			EditDynamicObject(playerid, obj);
		}
	}
	return 1;
}