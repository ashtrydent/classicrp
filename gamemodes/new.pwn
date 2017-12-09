/*
	> Classic Roleplay 
	* classic-rp.com 
	* vk.com/clrp_samp 
	* 2017-2018
*/

#include <a_samp>
#include <amx>
#include <asm>
#include <mxINI>
#include <codescan>
#include <heap_alloc>
#include <os>
#include <profiler>
#include <stack_dump>
#include <stack_trace>

#include <YSI\y_hooks>
#include <streamer>
#include <crashdetect>
#include <nex-ac>
#include <sscanf2>
#include <YSI_Data\y_foreach>
#include <a_mysql>
#include <a_actor>
#include <dc_cmd>
#include <a_http>
#include <easyDialog>

#include <ArrayList>
 
#include <..\..\gamemodes\modules\main_headers>
#include <..\..\gamemodes\modules\payspray_fix>

#pragma dynamic 35000

new out_id, out_id_i, out_price;

#include "..\..\gamemodes\modules\new"
#include "..\..\gamemodes\modules\fixpickups"
#include "..\..\gamemodes\modules\gate"
#include "..\..\gamemodes\modules\anticheat"
#include "..\..\gamemodes\modules\forward"
#include "..\..\gamemodes\modules\function"
#include "..\..\gamemodes\modules\cmd" 
#include "..\..\gamemodes\modules\shop"
#include "..\..\gamemodes\modules\microphone"
#include "..\..\gamemodes\modules\dialog"
//------------------------------------------------------------------------------
main()
{

}
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(strfind(inputtext,"%",true)!=-1)
	{
		new str[128];
		format(str, sizeof(str), "Вызов диалога заблокирован в целях безопасности! (%s)", inputtext);
		return ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Оповещение", str, "Закрыть", "");
	}
	if(!response) 	Sound_Fail(playerid);
	else		 	Sound_Succ(playerid);	
	switch(dialogid)
	{
	    case 1:
	    {
	        if(!strlen(inputtext) || strlen(inputtext) < 5 || strlen(inputtext) > 64) show_login(playerid);
	        else
	        {
	            if(!response) return 1;
	            new qu[256], temp[128];
	        	mysql_real_escape_string(inputtext, temp);
				
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
			if(!character_info[playerid][inv][id][listitem]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Это пустой слот!");
     		new str[128];
			player_info[playerid][inv_selected] = listitem;
			format(str, sizeof(str), "%s (%d)", senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), character_info[playerid][inv][count][player_info[playerid][inv_selected]]);
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
						return SCM(playerid, COLOR_RED, ">{FFFFFF} Произошла внутренняя ошибка. (FAKE ITEM)");
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
   			if(Items[itemid][Model] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный предмет нельзя выкинуть!");
   			if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
				return SCM(playerid, COLOR_RED, ">{FFFFFF} Вы уже пользуетесь редактором!");
      		new Float:angle, Float:x,Float:y,Float:z, obj;
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			x += floatsin(-angle, degrees);
			y += floatcos(-angle, degrees);
 			obj = CreateDynamicObject(Items[itemid][Model], x, y, z-0.9, -90, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
		
			if(obj != 0) {
				
				new slot_isset;
				for(new i = 0; i<MAX_ITEM_DROP; i++)
				{
					if(items_drop[i][id] < 1)
					{
						items_drop[i][id] = obj;
						items_drop[i][myitem] = itemid;
						items_drop[i][item_count] = strval(inputtext);
						slot_isset = 1;
						break;
					}
				}
				if(slot_isset == 1) {
					if(EditDynamicObject(playerid, obj)) {
						character_info[playerid][editobject] = obj;
						character_info[playerid][type_editobj] = 1;
						SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте ESC чтобы выйти!");
					} else {
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При выкидывании объекта произошла ошибка! Попробуйте еще раз! #3");
					}
				} else {
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При выкидывании объекта произошла ошибка! Попробуйте еще раз! #2");
				}
			} else {
				SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При выкидывании объекта произошла ошибка! Попробуйте еще раз! #1");
			}
		}
		case 7:
		{
			if(!response) return 1;
			dialog_data[playerid][0] = strval(inputtext);
			if(!IsPlayerLoged(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн!");
			if(Items[character_info[playerid][inv][id][player_info[playerid][inv_selected]]][compound])
			ShowPlayerDialog(playerid, 8, DIALOG_STYLE_INPUT,"Инвентарь", "Введите количество для передачи: ", "Ввести", "Отмена");
			else
			{
				new Float:x,Float:y,Float:z;
				GetPlayerPos(dialog_data[playerid][0], x,y,z);
				if(PlayerToPoint(10, playerid, x,y,z))
				{
					new itemid = character_info[playerid][inv][id][player_info[playerid][inv_selected]];
					new mycount = character_info[playerid][inv][count][player_info[playerid][inv_selected]];
					if(!deleteitemslot(playerid, player_info[playerid][inv_selected])) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Произошла ошибка!");
					new str[128];
					giveitem(dialog_data[playerid][0], itemid, mycount);
					format(str, sizeof(str), ">{FFFFFF} Вы передали %s", senderitems(itemid));
					SCM(playerid, COLOR_PAPAYA, str);
					format(str, sizeof(str), ">{FFFFFF} Вам передали %s", senderitems(itemid));
					//printf("%s giving %s %s(%d)", sendername(playerid), sendername(dialog_data[playerid][0]), senderitems(itemid), mycount);
					Log_Write("logs/give_log.txt", "[%s] %s передал %s %s(%d)", ReturnDate(), sendername(playerid), sendername(dialog_data[playerid][0]), senderitems(itemid), mycount);
					SCM(dialog_data[playerid][0], COLOR_PAPAYA, str);
				}
				else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");
			}
		}
		case 8:
		{
			if(!response) return 1;
			dialog_data[playerid][1] = strval(inputtext);
			if(dialog_data[playerid][1] < 1 || dialog_data[playerid][1] > 9999) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество");
			new Float:x,Float:y,Float:z;
			GetPlayerPos(dialog_data[playerid][0], x,y,z);
			if(PlayerToPoint(10, playerid, x,y,z))
			{
				if(!deleteitem(playerid, character_info[playerid][inv][id][player_info[playerid][inv_selected]], dialog_data[playerid][1])) return SCM(playerid, COLOR_GRAY, "Неверное количество");
				else
				{
					new str[128];
					giveitem(dialog_data[playerid][0], character_info[playerid][inv][id][player_info[playerid][inv_selected]], dialog_data[playerid][1]);
					format(str, sizeof(str), ">{FFFFFF} Вы передали %s (%d)", senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), dialog_data[playerid][1]);
					SCM(playerid, COLOR_PAPAYA, str);
					format(str, sizeof(str), ">{FFFFFF} Вам передали %s (%d)", senderitems(character_info[playerid][inv][id][player_info[playerid][inv_selected]]), dialog_data[playerid][1]);
					SCM(dialog_data[playerid][0], COLOR_PAPAYA, str);
				}
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");
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
            }

		}
		case 10:
		{
		    if(!response) return 1;
		    new propid = OwnerProp(playerid);
		    if(propid > -1 && IsPlayerLoged(strval(inputtext)))
		    {
				if(IsMaximumProp(strval(inputtext))) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок имеет максимальное количество имущества!");
		        dialog_data[playerid][2] = strval(inputtext);
				ShowPlayerDialog(playerid, 11, DIALOG_STYLE_INPUT, "Продажа имущества", "Введите стоимость продажи имущества: ", "Продать", "Отменить");
            }
		}
		case 11:
		{
		    if(!response) return 1;
		    new propid = OwnerProp(playerid);
		    if(propid > -1)
		    {
		        new price_house = strval(inputtext), giveplayerid = dialog_data[playerid][2], str[128];
                if(!IsPlayerLoged(giveplayerid) || playerid == giveplayerid) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн.");

                if(price_house < 2 || price_house > 5000000) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверную сумму.");

                new Float:x,Float:y,Float:z;
                GetPlayerPos(giveplayerid, x,y,z);
                if(PlayerToPoint(10.0, playerid, x,y,z))
				{
	                dialog_data[giveplayerid][3] = playerid;
	                dialog_data[giveplayerid][4] = price_house;
	                format(str, sizeof(str), "Вы действительно хотите купить №%d у игрока %s(%d)\nСтоимость: %d$", GetGlobalIdProp(propid), sendername(playerid), playerid, price_house);
	                ShowPlayerDialog(giveplayerid, 12, DIALOG_STYLE_MSGBOX, "Покупка дома", str, "Продать", "Отменить");
	                SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Ожидается подтверждение игрока.");
                }
                else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");
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
         		    new where[30], from[30], str[128];
					format(where, sizeof(where), "buy house (%d)", character_info[dialog_data[playerid][3]][id]);
					format(from, sizeof(from), "sell house (%d)", character_info[playerid][id]);
			        if(!transfermoney(playerid, dialog_data[playerid][3], dialog_data[playerid][4], where, from)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
			        else
			        {
	          			prop_info[propid][owner] = character_info[playerid][id];
	            		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы купили имущество.");
		            	SCM(dialog_data[playerid][3], COLOR_MSGSERVER, ">{FFFFFF} Вы продали имущество.");
						format(str, sizeof(str), "приобрел имущество №%d за %d$ (Продавец: %s)", propid, dialog_data[playerid][3], character_info[dialog_data[playerid][3]][name]);
						PlayerLog(playerid, str);
		            	dialog_data_update(dialog_data[playerid][3]);
		            	dialog_data_update(playerid);
			        }
		        }
		    }
		}
		case 13:
		{
		    if(!response) return 1;
		    if(GetPlayerVirtualWorld(playerid) <= 200 || character_info[playerid][id] != prop_info[GetLocalIdProp(character_info[playerid][prop])][owner]) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится в своем имуществе!");
			
			new str[5000];
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
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже пользуетесь редактором!");

					if(GetPlayerVirtualWorld(playerid) == 0) return Sound_Fail(playerid);
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
					    	//printf("[furniture_debug:%d] определен свободный слот, id=%d", it, obj);
						    furniture[it][id] = obj;
							furniture[it][houseid] = character_info[playerid][prop];
							furniture[it][model] = _furniture[i][id];
							SetPVarInt(playerid, "furniture_it", it);
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
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже пользуетесь редактором!");
	        if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200)
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
	        if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200)
	    	{
	    	    new ii = -1;
          		for(new i=0; i<MAX_FURNITURE; i++)
				{
					if(furniture[i][houseid] == character_info[playerid][prop])
					{
						ii++;
						if(ii == listitem)
						{
							if(furniture[i][cordX] == 0.0 || furniture[i][cordY] == 0.0) return 1;
						    DestroyDynamicObject(furniture[i][id]);
							new qu[256];
						 	format(qu, sizeof(qu), "DELETE FROM `furniture` WHERE id=%d", i);
							mysql_function_query(dbHandle, qu, false, "", "");
							furniture[i][id] = -1;
							furniture[i][houseid] = -1;
							// givemoney(playerid, _furniture[furniture_search(furniture[i][model])][price] / 2, "sell furniture");
      		 				furniture[i][model] = -1;
							furniture[i][cordX] = 0.0;
							furniture[i][cordY] = 0.0;
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы удалили предмет");
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
				case 5: cmd::pr(playerid, "money");
				case 6: cmd::pr(playerid, "inv");
				case 7: cmd::pr(playerid, "name");
				case 8: cmd::pr(playerid, "price");
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
            if(!response) 
				return 1;
			
			new itemid = character_info[playerid][inv][id][player_info[playerid][inv_selected]];
   			
			if(Items[itemid][Model] == 0) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Данный предмет нельзя выкинуть!");
   			
			if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit"))
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже пользуетесь редактором!");
      		
			new Float:angle, Float:x,Float:y,Float:z, obj;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			x += floatsin(-angle, degrees);
			y += floatcos(-angle, degrees);
 			
			obj = CreateDynamicObject(Items[itemid][Model], x, y, z-0.9, -90, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			if(obj != 0) {
				
				new slot_isset;
				for(new i = 0; i<MAX_ITEM_DROP; i++)
				{
					if(items_drop[i][id] < 1)
					{
						items_drop[i][id] = obj;
						items_drop[i][myitem] = itemid;
						items_drop[i][item_count] = character_info[playerid][inv][count][player_info[playerid][inv_selected]];
						slot_isset = 1;
						break;
					}
				}
				if(slot_isset == 1) {
					if(EditDynamicObject(playerid, obj)) {
						character_info[playerid][editobject] = obj;
						character_info[playerid][type_editobj] = 1;
						SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте ESC чтобы выйти!");
					} else {
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При выкидывании объекта произошла ошибка! Попробуйте еще раз! #3");
					}
				} else {
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При выкидывании объекта произошла ошибка! Попробуйте еще раз! #2");
				}
			} else {
				SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При выкидывании объекта произошла ошибка! Попробуйте еще раз! #1");
			}
		}
		case 21:
		{
            if(!response) return 1;
            if(listitem < 0 || listitem > 17) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Произошла внутренняя ошибка. (FAKE BONE NUMBER)");
            SetPVarInt(playerid, "attach_bone", listitem+1);
            for(new i = 0; i<MAX_ATTACH; i++)
            {
                if(attach[playerid][i][iditem] == -1)
                {
					if(!Items[GetPVarInt(playerid, "attach_itemid")][compound]) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот предмет нельзя прикрепить");
                    
					if(GetPVarInt(playerid, "attach_edit")) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже пользуетесь редактором");
                    
					SetPVarInt(playerid, "attach_edit", true);
                    SetPlayerAttachedObject(playerid, i, Items[GetPVarInt(playerid, "attach_itemid")][Model], GetPVarInt(playerid, "attach_bone"));
					EditAttachedObject(playerid, i);
                    return 1;
                }
            }
            SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Все слоты для аттачей заняты.");
		}
		case 22:
		{
		    if(!response) 
				return 1;
			if(listitem == MAX_ATTACH) 
				return cmd_changegunattach(playerid);
			
			SetPVarInt(playerid, "attach_slot", listitem);
		    SPD(playerid, 23, DIALOG_STYLE_TABLIST, "Прикрепленные объекты", "Изменить положение\nОткрепить", "Выбрать", "Закрыть");
		}
		case 23:
		{
		    if(!response) 
				return 1;
			new attach_slot = GetPVarInt(playerid, "attach_slot");
		    
			switch(listitem)
			{
				case 0:
				{	
				
					SetPVarInt(playerid, "attach_itemid", attach[playerid][attach_slot][iditem]);
					SetPVarInt(playerid, "attach_bone", attach[playerid][attach_slot][bone]);
					attachStatus[playerid] = 1;
					EditAttachedObject(playerid, attach_slot);
				}
				
				case 1:
				{
					if(giveitem(playerid, attach[playerid][attach_slot][iditem], 1))
						ResetAttach(playerid, attach_slot);
					else 
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При откреплении предмета произошла ошибка! Проверьте наличие места в инвентаре!");
				}
			}
			if(!listitem)
		    {

		    }
		    else
		    {

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
            SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Контакт добавлен");
			DeletePVar(playerid, "contacts_slot"), DeletePVar(playerid, "contacts_number");
		}
		case 28:
		{
			if(!response) return 1;
		    if(listitem == 0) cmd::phoneinv(playerid);
		    if(listitem == 1) cmd::contacts(playerid);
		    if(listitem == 2)
			{
			    SPD(playerid, 29, DIALOG_STYLE_INPUT, "Позвонить", "{FFFFFF}Введите номер телефона / имя контакта: \n\n{b1b1b1}911 - экстренная служба\n555 - такси", "Ок", "Отмена");
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
			if(strlen(inputtext) > 35) return 0;
	 	    new str[26];
		 	new string[180];
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
	 	    if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner] || searchitemcount(playerid, 148, character_info[playerid][prop]) && GetPlayerVirtualWorld(playerid) > 200 || GetPlayerVirtualWorld(playerid) > 200 && InFactionId(playerid, LSPD_FACTION) || GetPlayerVirtualWorld(playerid) > 200 && InFactionId(playerid, SASD_FACTION) || GetPlayerVirtualWorld(playerid) > 200 && InFactionId(playerid, LSSD_FACTION))
			{
		 	    new prslot = GetPVarInt(playerid, "prinv_slot"), count_take = strval(inputtext), li = GetLocalIdProp(character_info[playerid][prop]);
	      		if(count_take < 1 || count_take > prop_info[li][inv][count][prslot]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество.");
	      		if(!Items[prop_info[li][inv][id][prslot]][compound]) 
	       		{
					count_take = prop_info[li][inv][count][prslot];
					if(prop_info[li][inv][id][prslot] == 0) return 1;
					new str[64];
					format(str, sizeof(str), "достает %s(%d) из имущества.", Items[prop_info[li][inv][id][prslot]][Name], count_take);
					Log_Write("logs/propInv_log.txt", "[%s] %s take %s(%d) from prop (%d)", ReturnDate(), sendername(playerid), Items[prop_info[li][inv][id][prslot]][Name], count_take, character_info[playerid][prop]);
					giveitem(playerid, prop_info[li][inv][id][prslot], count_take);
					OOCMSG(playerid, str);
					deleteitemslotpr(li, prslot);
				}
				else
				{
					new giveitemid = prop_info[li][inv][id][prslot];
					if(!deleteitempr(li, prop_info[li][inv][id][prslot], count_take)) return 1;
					new str[64];
					Log_Write("logs/propInv_log.txt", "[%s] %s take %s(%d) from prop(%d)", ReturnDate(), sendername(playerid), Items[prop_info[li][inv][id][prslot]][Name], count_take, character_info[playerid][prop]);
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
	 	        if(count_take < 1 || count_take > character_info[playerid][inv][count][prslot]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество.");
				if(!character_info[playerid][inv][id][prslot]) return 1;
	 	        if(giveitempr(li, character_info[playerid][inv][id][prslot], count_take))
				{
					new str[64];
					Log_Write("logs/propInv_log.txt", "[%s] %s put %s(%d) in prop(%d)", ReturnDate(), sendername(playerid), Items[character_info[playerid][inv][id][prslot]][Name], count_take, prop_info[li][id]);
					//printf("%s put %s(%d) in prop %d", sendername(playerid), Items[character_info[playerid][inv][id][prslot]][Name], count_take, prop_info[li][id]);
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
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы сохранили координаты входа!");
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
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы сохранили координаты выхода!");
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
					if(x == 0 || y == 0 || z == 0 || xe == 0 || ye == 0 || ze == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны назначть координаты!");
			 		format(qu, sizeof(qu), "INSERT INTO `enters`(`text`, `x`, `y`, `z`, `vworld`, `intid`, `xe`, `ye`, `ze`, `vworlde`, `intide`) VALUES ('%s',%f,%f,%f,%d,%d,%f,%f,%f,%d,%d)",
			 			temp, x,y,z, vw, myinterior,
				 		xe,ye,ze, virtualworldE, interiorE);
					mysql_function_query(dbHandle, qu, false, "", "");
					UnLoadEnters();
					LoadEnters();
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы установили вход!");
			    }
			}
	 	}
	 	case 36:
	 	{
	 	    if(!response) return 1;
	 	    SetPVarString(playerid, "enter_text", inputtext);
            //printf("%s", inputtext);
	 	    SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы сохранили текст входа");
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
			    if(strval(inputtext) > prop_info[propid][money]) return SCM(playerid, COLOR_MSGERROR, "> {FFFFFF}В имуществе недостаточно денег!");
				if(strval(inputtext) < 1 || strval(inputtext) > 1000000) return SCM(playerid, COLOR_MSGERROR, "> {FFFFFF}Вы ввели неверное количество!");
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
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы положили деньги в имущество");
			    }
			    else SCM(playerid, COLOR_MSGERROR, "> {FFFFFF}У вас недостаточно денег");
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
				if(list_store[listitem][iditem] == 134)
				{
					giveitem(playerid, 134, 20);
					return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
				}
				if(list_store[listitem][iditem] == 15)
	 			{
				 	create_phone(playerid);
				 	return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
				} else if(list_store[listitem][iditem] == 341) {
				 	create_pager(playerid);
				 	return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
				
				}
				else if(list_store[listitem][iditem] == 84)
	 			{
					if(!giveitem(playerid, 84, 50))
						return givemoney(playerid, list_store[listitem][price], "no itemslot for buy item");
				 	
					return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
				}
   			    else if(!giveitem(playerid, list_store[listitem][iditem], 1))
				   return givemoney(playerid, list_store[listitem][price], "no itemslot for buy item");
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_store[listitem][price]-(list_store[listitem][price]/4);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
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
				    ShowPlayerDialog(playerid, 49, DIALOG_STYLE_INPUT, factions[GetPVarInt(playerid, "select_faction")][Name], "{FFFFFF}Введите ID персонажа(глобальный): \n{b1b1b1}Вы должны указать глобальный ID персонажа, чтобы его узнать воспользуйтесь командой /id, в поле необходимо указать так называемый CHID(CharacterID).", "Ввод", "Отмена");
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
				SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы обновили информацию о фракции!");
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Название фракции должно содержать в себе больше 2-х символов");
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
			SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы обновили информацию о фракции!");
			DeletePVar(playerid, "select_faction");
		}
		case 49:
		{
		    if(IsAdmin(playerid, 5)) return 1;
		    if(!response) return 1;
		    new temp = strval(inputtext), qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET leader=%d where id=%d", temp, GetPVarInt(playerid, "select_faction"));
			mysql_function_query(dbHandle, qu, true, "", "");
			new str[128];
			format(str, sizeof(str), "%s(%d) обновил лидера фракции ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
   			AdminLog(str);
			LoadFactions();
			SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы обновили информацию о фракции!");
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
			SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы обновили информацию о фракции!");
			DeletePVar(playerid, "select_faction");
		}
		case 1001:
		{
			if(!response) 
				return 1;
			
			new itemid = GetPVarInt(playerid, "Itemid");
			new shopid = GetPVarInt(playerid, "Shopid");
						
			if(shopid == 2)
				BuyAttach(playerid, itemid);
			
			if(shopid == 0 || shopid == 1)
				BuySkin(playerid, itemid);
		}
		case 51:
		{
		    if(!response) 
				return 1;
			switch(listitem)
			{
				case 0: 
				{
					if(character_info[playerid][sex] == 1)
						ShopMenu(playerid, 0, 0);
					
					if(character_info[playerid][sex] == 2)
						ShopMenu(playerid, 0, 1);
				}
				
				case 1:
				{
					ShopMenu(playerid, 0, 2);
				}
			}
			
			/*
		    if(listitem == 0) 
				ShowPlayerDialog(playerid, 59, DIALOG_STYLE_TABLIST, "Магазин одежды", "Выбрать скин\nВвести ID скина", "Выбрать", "Отмена");
		    else
		    {
		        new str[2086];
		        for(new i=47; i<81; i++)
		        {
		        	format(str, sizeof(str), "%s%s\n", str, senderitems(i));
		        }
		        ShowPlayerDialog(playerid, 52, DIALOG_STYLE_TABLIST, "Магазин одежды", str, "Выбрать", "Отмена");
		    }
			*/
		}
		case 52:
		{
		    if(!response) 
				return 1;
		    
			if(!InPropType(playerid, 2)) 
				return 1;
		    
			if(listitem+47 < 47 || listitem+47 > 90) 
				return 1;
		    
			new buy_itemid = listitem+47;
			if(takemoney(playerid, 70, "buy attach item") == 1)
   			{
		    	if(!giveitem(playerid, buy_itemid, 1))
				   return givemoney(playerid, list_store[listitem][price], "no itemslot for buy item");
			   
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_store[listitem][price]-(list_store[listitem][price]/4);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
		}
		case 53:
		{
			if(!response) return 1;
		    if(IsAdmin(playerid, 5)) return 1;
			new str[128];
			format(str, sizeof(str), "%s(%d) удалил фракцию ID %d: %s", player_info[playerid][login], playerid, GetPVarInt(playerid, "select_faction"), factions[GetPVarInt(playerid, "select_faction")][Name]);
			AdminLog(str);
			new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET name='', freeze=1 where id=%d", GetPVarInt(playerid, "select_faction"));
			mysql_function_query(dbHandle, qu, true, "", "");
			LoadFactions();
			SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Вы удалили фракции!");
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
					
				    if(InFactionType(playerid, 3) || InFactionType(playerid, 4)) 
						format(str, sizeof(str), "%sДоступное оружие для покупки: %d\n", str, factions[character_info[playerid][faction]][guns]);
				    
					if(InFactionType(playerid, 3) || InFactionType(playerid, 4)) 
						format(str, sizeof(str), "%sДоступные наркотики для покупки: %d\n", str, factions[character_info[playerid][faction]][drugs]);
				    
					if(InFactionType(playerid, 3) || InFactionType(playerid, 4)) 
						format(str, sizeof(str), "%sДоступные патроны для покупки: %d\n", str, factions[character_info[playerid][faction]][bulls]);
				    
					if(InFaction(playerid, true)) 
						format(str, sizeof(str), "%s\n{FFFF45}Вы являетесь лидером фракции!", str);
					
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
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_MSGERROR, ">{FFFFFF} Вы должны быть лидером фракции для доступа в этот раздел!");
		    new str[512];
			switch(listitem)
			{
			    case 0:
			    {
			        for(new i = 1; i<21; i++)
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
						if(!VehUsed) 
						{
							SetVehicleVirtualWorld(v, veh_info[v][VW]);
							SetVehicleToRespawn(v);
						}
					}
				}
			}
		}
		case 56:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid,COLOR_RED, "Вы должны быть лидером фракции для доступа в этот раздел!");
			SetPVarInt(playerid, "rank_select", listitem+1);
			if(listitem < 0 || listitem > 20) return 1;
			new temp[16];
			format(temp, sizeof(temp), "%s", faction_ranks[character_info[playerid][faction]][listitem+1]);
			new str[128];
			format(str, sizeof(str), "{FFFFFF}Выбранный ранг: %s (%d)\n{b1b1b1}Введите новое название название: ", temp, GetPVarInt(playerid, "rank_select"));
			ShowPlayerDialog(playerid, 57, DIALOG_STYLE_INPUT, "Названия рангов", str, "Выбрать", "Отмена");
		}
		case 57:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть лидером фракции для доступа в этот раздел!");
			if(strlen(inputtext) > 31) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте название ранга до 32 символов!");
			new qu[256];
			format(qu, sizeof(qu), "UPDATE `factions` SET `Rank%d`='%s' WHERE id=%d", GetPVarInt(playerid, "rank_select"), inputtext, character_info[playerid][faction]);
			mysql_function_query(dbHandle, qu, false, "", "");
			format(faction_ranks[character_info[playerid][faction]][GetPVarInt(playerid, "rank_select")], 31, "%s", inputtext);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы изменили название ранга");
		}
		case 58:
		{
		    if(!response) return 1;
            if(!InFaction(playerid)) return 1;
		    character_info[playerid][faction] = 0;
		    character_info[playerid][rank] = 0;
		    SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы покинули фракцию!");
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
		    if(!InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть лидером фракции для доступа в этот раздел!");
		    if(strval(inputtext) < 1 || strval(inputtext) > 15) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте от 1 до 15 ранга");
		    factions[character_info[playerid][faction]][invite_rank] = strval(inputtext);
            new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET `invite_rank`=%d WHERE id=%d", factions[character_info[playerid][faction]][invite_rank], character_info[playerid][faction]);
		    mysql_function_query(dbHandle, qu, false, "", "");
		    SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно изменил права рангов!");

		}
		case 61:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть лидером фракции для доступа в этот раздел!");
		    if(strval(inputtext) < 1 || strval(inputtext) > 15) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте от 1 до 15 ранга");
		    factions[character_info[playerid][faction]][uninvite_rank] = strval(inputtext);
            new qu[128];
			format(qu, sizeof(qu), "UPDATE `factions` SET `uninvite_rank`=%d WHERE id=%d", factions[character_info[playerid][faction]][uninvite_rank], character_info[playerid][faction]);
            mysql_function_query(dbHandle, qu, false, "", "");
            SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно изменил права рангов!");
		}
		case 62:
		{
		    if(!response) return 1;
		    if(!InFaction(playerid, true)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть лидером фракции для доступа в этот раздел!");
		    if(strval(inputtext) < 1 || strval(inputtext) > 15) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте от 1 до 15 ранга");
		    factions[character_info[playerid][faction]][giverank_rank] = strval(inputtext);
		    new qu[128];
		    format(qu, sizeof(qu), "UPDATE `factions` SET `giverank_rank`=%d WHERE id=%d", factions[character_info[playerid][faction]][giverank_rank], character_info[playerid][faction]);
            mysql_function_query(dbHandle, qu, false, "", "");
            SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно изменил права рангов!");
		}
		case 63:
		{
		    if(!GetPVarInt(playerid, "invited_faction")) return 1;
		    if(!response)
		    {
		        SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы отказались от приглашения!");
		        SCM(GetPVarInt(playerid, "invited_player"), COLOR_MSGSERVER, ">{FFFFFF} Игрок отказался от вступления во фракцию!");
				DeletePVar(playerid, "invited_faction");
				DeletePVar(playerid, "invited_player");
				return 1;
		    }
		    else
		    {
				character_info[playerid][faction] = GetPVarInt(playerid, "invited_faction");
				character_info[playerid][rank] = 1;
		        SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы вступили во фракцию!");
		        SCM(GetPVarInt(playerid, "invited_player"), COLOR_MSGSERVER, ">{FFFFFF} Игрок принял приглашение!");
  				DeletePVar(playerid, "invited_faction");
				DeletePVar(playerid, "invited_player");
				return 1;
		    }
		}
		case 64:
		{
		    if(!response) return 1;
		    if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вызов завершен!");
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
			else if(list_deal[GetPVarInt(playerid, "deal_type")][iditem] < 34 && list_deal[GetPVarInt(playerid, "deal_type")][iditem] > 2) factions[character_info[playerid][faction]][drugs] -= GetPVarInt(playerid, "deal_count");
			else if(list_deal[GetPVarInt(playerid, "deal_type")][iditem] == 2) factions[character_info[playerid][faction]][bulls] -= GetPVarInt(playerid, "deal_count");
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Произошла внутренняя ошибка!");

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
			if(!response) 
				return 1;
			if(!InFactionType(playerid, 3) && !InFactionType(playerid, 4) && !IsPremium(playerid, PREMIUM_BRONZE)) 
				return 1;
			new temp[32];
			switch(listitem)
			{
				case 0:
				{
					new graff_count = 0;
					for(new i; i<MAX_GRAFF; i++) 
						if(PlayerToPoint(50.0, playerid, graff_info[i][gX], graff_info[i][gY], graff_info[i][gZ])) 
							graff_count++;

					if(graff_count >= 7) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} В этой области слишком много граффити, попробуйте установить его в другом месте!");

					GetPVarString(playerid, "graf_text", temp, 32);
					if(strlen(temp) < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны ввести текст!");
					format(temp, sizeof(temp), "");
					
					GetPVarString(playerid, "graf_color", temp, 32);
					if(strlen(temp) < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны выбрать цвет!");
					format(temp, sizeof(temp), "");
					
					GetPVarString(playerid, "graf_font", temp, 32);
					if(strlen(temp) < 1) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны выбрать шрифт!");
					format(temp, sizeof(temp), "");
					
					if(!GetPVarInt(playerid, "graf_fontsize")) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны выбрать размер шрифта!");
					
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
			if(strlen(inputtext) < 1 || strlen(inputtext) > 32) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны использовать от 1 до 32 символов!");
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
			if(strval(inputtext) < 10 || strval(inputtext) > 100) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное значение!");
			SetPVarInt(playerid, "graf_fontsize", strval(inputtext));
			cmd_graffiti(playerid);
		}
		case 73:
		{	
			if(!response) 
				return 1;
			if(TestMDC(playerid)) 
				return 1;
			
			switch(listitem)
			{
				case 0: ShowPlayerDialog(playerid, 74, DIALOG_STYLE_INPUT, "Police MDC System", "{FFFFFF}Введите id игрока или часть ника: ", "Ввод", "Отмена");
				case 1: ShowPlayerDialog(playerid, 78, DIALOG_STYLE_INPUT, "Police MDC System", "{FFFFFF}Введите номер автомобиля или ID игрока: ", "Ввод", "Отмена");
				case 2: ShowPlayerDialog(playerid, 79, DIALOG_STYLE_INPUT, "Police MDC System", "{FFFFFF}Введите номер имущества: ", "Ввод", "Отмена");
				
				case 4:
				{
					new str[512] = "№\tТекст\tРайон\tВремя\n";
					for(new i; i<MAX_911; i++)
					{
						if(list_911[i][id] < 1) continue;
						format(str, sizeof(str), "%s%d\t%s\t%s\t%s\n",str, list_911[i][id], list_911[i][text_911], list_911[i][Zone], list_911[i][time_911]);
					}
					ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "Police MDC System", str, "Закрыть", "");
				}
			}
		}
		case 74:
		{
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			new _id_;
			if(sscanf(inputtext,"u", _id_)) 
			{
				new username[25];
				if(sscanf(inputtext, "s[25]", username))
				{
					new qu[65];
					format(qu, sizeof(qu), "select * from characters where name='%s'", username);
					mysql_function_query(dbHandle, qu, true, "SearchCharacterMDC", "%d", playerid);
				}
			}
			if(!IsPlayerLoged(_id_)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
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
			format(str, sizeof(str), "%sДата рождения: %s\n", str, character_info[_id_][birthDate]);
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
			
			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Police MDC System", str, "Закрыть", "");
		}
		case 75:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0: 
				{
					if(character_info[playerid][driveLic]) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас уже имееются водительские права!");
					else 
					{
						if(takemoney(playerid, 400, "buy drive lic") == 1)
						{
							character_info[playerid][driveLic] = 1;
							character_info[playerid][driveLicWarn] = 0;
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы приобрели водительские права!");
						}
					}
				}
				case 1:
				{
					if(character_info[playerid][flyLic]) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас уже имеется данный вид лицензии!");
					else
					{
						if(takemoney(playerid, 3500, "buy fly lic") == 1)
						{
							character_info[playerid][flyLic] = 1;
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы приобрели лицензию!");
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
			
			if(IsMaximumCars(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы имеете максимальное количество автомобилей!");	
			new i, ii = -1;
			for(i=0; i<sizeof(BuyCars); i++) 
			{
				if(BuyCars[i][Type] == GetPVarInt(playerid, "BuyCarsType")) ii++;
				if(ii == listitem) break;
			}
			if(BuyCars[i][Type] == 6 && !IsPremium(playerid, PREMIUM_SILVER)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет доступа к покупке этого транспорта!");
			if(takemoney(playerid, BuyCars[i][Price], "buy car") == 1)
			{
				// lodki - 446,454,473,484 || vertoleti - 447,460,469,511
				new qu[256];
				switch(BuyCars[i][Model])
				{
					case 446: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 294.7389,-1913.3849,3.8186,177.2006);
					case 454: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 294.7389,-1913.3849,3.8186,177.2006);
					case 473: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 294.7389,-1913.3849,3.8186,177.2006);
					case 484: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 294.7389,-1913.3849,3.8186,177.2006);
					case 460: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 294.7389,-1913.3849,3.8186,177.2006);
					
					case 447: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 1888.0580,-2291.5359,13.5469,260.5846);
					case 469: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 1888.0580,-2291.5359,13.5469,260.5846);
					case 511: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`, `posX`,`posY`,`posZ`, `Angle`) VALUES (%d, %d, %f, %f, %f, %f)", BuyCars[i][Model], character_info[playerid][id], 1888.0580,-2291.5359,13.5469,260.5846);
					
					default: format(qu, sizeof(qu), "INSERT INTO `cars`(`model`, `owner`) VALUES (%d, %d)", BuyCars[i][Model], character_info[playerid][id]);
				}
				
				mysql_function_query(dbHandle, qu, false, "", "");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы приобрели автомобиль.");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте команды /park чтобы припарковать его и /getcar чтобы найти.");
				LoadCars(playerid);
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
		}
		case 78:
		{
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			new carnumber;
			if(sscanf(inputtext,"d", carnumber))
			{
				new qu[138+12];
				format(qu, sizeof(qu), "SELECT cars.BuyDate, cars.number, cars.model, characters.name FROM cars JOIN characters ON cars.owner=characters.id WHERE cars.number='%s'", inputtext);
				mysql_function_query(dbHandle, qu, true, "OnCarsInfo", "i", playerid);
				return 1;
			}
			new qu[146+12];
			new v = GetPlayerVehicleID(carnumber);
			if(v <= 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок не в автомобиле!");
			format(qu, sizeof(qu), "SELECT cars.owner, cars.BuyDate, cars.number, cars.model, characters.name FROM cars JOIN characters ON cars.owner=characters.id WHERE cars.id='%d'", veh_info[v][id]);
			mysql_function_query(dbHandle, qu, true, "OnCarsInfoByPlayerid", "i", playerid);
			return 1;
		}
		case 79:
		{
			if(!response) return 1;
			if(TestMDC(playerid)) return 1;
			if(strval(inputtext) < 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверное значение!");
			/*new i;
			for(; i<MAX_PROP; i++)
			{
				if(prop_info[i][id] == strval(inputtext)) break;
				else if(i == MAX_PROP) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Такого имущества не существует!");
			}
			//ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "MDC", str, "Закрыть", "");*/
			SetPVarInt(playerid, "target_prop", strval(inputtext));
			new qu[128];
			format(qu, sizeof(qu), "SELECT characters.name FROM characters JOIN property ON property.owner=characters.id WHERE property.id=%d", GetPVarInt(playerid, "target_prop"));
			mysql_function_query(dbHandle, qu, true, "OnPropInfo", "i", playerid);
		}
		case 80:
		{
			if(!response) return 1;
			format(character_info[playerid][description], 256, "%s", inputtext);
			new str[53+11+256];
			format(str, sizeof(str), "описал персонажа: %s", inputtext);
			PlayerLog(playerid, str);
			new temp[256];
			mysql_real_escape_string(character_info[playerid][description], temp);
			format(str, sizeof(str), "UPDATE `characters` SET `description`='%s' WHERE id=%d", temp, character_info[playerid][id]);
			mysql_function_query(dbHandle, str, false, "", "");
			cmd_description(playerid);
		}
		case 81:
		{
			if(!response) 
				return 1;
			switch(listitem)
			{
				case 0:
				{
					if(!IsDutyPickup(playerid)) 
						return 1;
					
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
						
						SetPVarFloat(playerid, "arrmor", 0);
						UpdateArm(playerid);
					
						attach_player_update(playerid);
						UpdatePlayerColor(playerid);
					}
					else
					{
						character_info[playerid][duty] = 1;	
						fmsg(playerid, "вышел на дежурство.");
						if(character_info[playerid][gun] > 0) 
							return cmd_invwep(playerid);
						
						UpdatePlayerColor(playerid);
					}
				}
				case 1:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					if(checkitem(playerid, 83) > -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас уже есть рация!");
					giveitem(playerid, 83, 1);
				}
				case 2:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					SetPVarFloat(playerid, "arrmor", 99.89);
					SetPlayerHealth(playerid, 99.89);
					UpdateArm(playerid);
				}
				case 3:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					ShowPlayerDialog(playerid, 82, DIALOG_STYLE_LIST, "DUTY", "Полицейская дубинка\nDesert Eagle\nShotgun\nMP5\nM4A1\nCountry Rifle\nSniper Rifle\nПерцовый балончик", "Выбрать", "Отмена");
				}
				case 4:
				{
					if(!DeleteDutyGuns(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет служебного оружия!");
				}
				case 5:
				{
					if(InFactionId(playerid, MAYOR_FACTION)) 
						ShowPlayerDialog(playerid, 138, DIALOG_STYLE_LIST, "DUTY", "Стандартный\n303\n304\n305\n285\n286\n255\n61\n71\n150\n253\n163\n164", "Выбрать", "Закрыть");
					else if(InFactionId(playerid, LSPD_FACTION)) 
						ShowPlayerDialog(playerid, 83, DIALOG_STYLE_LIST, "DUTY", "Стандартный\n280\n281\n265\n266\n267\n284\n285\n286\n287\n303\n304\n305\n306\n307\n71", "Выбрать", "Закрыть");
					else 
						ShowPlayerDialog(playerid, 83, DIALOG_STYLE_LIST, "DUTY", "Стандартный\n282\n283\n284\n285\n287\n288\n302\n304\n311\n310\n309", "Выбрать", "Закрыть");
				}
			}
		}
		case 82:
		{
			if(!response) return 1;
			if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
			if(character_info[playerid][gun] > 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас в руках не должно быть личного оружия!");
			switch(listitem)
			{
				case 0: character_info[playerid][duty_gun_1] = 3;
				case 1: character_info[playerid][duty_gun_2] = 24, character_info[playerid][duty_ammo_2] = 100;
				case 2: character_info[playerid][duty_gun_3] = 25, character_info[playerid][duty_ammo_3] = 70;
				case 3: character_info[playerid][duty_gun_3] = 29, character_info[playerid][duty_ammo_3] = 250;
				case 4: character_info[playerid][duty_gun_3] = 31, character_info[playerid][duty_ammo_3] = 350;
				case 5: character_info[playerid][duty_gun_3] = 33, character_info[playerid][duty_ammo_3] = 70;
				case 6: character_info[playerid][duty_gun_3] = 34, character_info[playerid][duty_ammo_3] = 70;
				case 7: character_info[playerid][duty_gun_1] = 41;
				default: return 1;
			}
			UpdateDutyGuns(playerid);
			ShowPlayerDialog(playerid, 82, DIALOG_STYLE_LIST, "DUTY", "Полицейская дубинка\nDesert Eagle\nShotgun\nMP5\nM4A1\nCountry Rifle\nSniper Rifle\nПерцовый балончик", "Выбрать", "Отмена");
		}
		case 83:
		{
			if(!response) return 1;
			if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
			if(InFactionId(playerid, LSPD_FACTION))
			{
				switch(listitem)
				{
					case 1: character_info[playerid][duty_skin] = 280;
					case 2: character_info[playerid][duty_skin] = 281;
					case 3: character_info[playerid][duty_skin] = 265;
					case 4: character_info[playerid][duty_skin] = 266;
					case 5: character_info[playerid][duty_skin] = 267;
					case 6: character_info[playerid][duty_skin] = 284;
					case 7: character_info[playerid][duty_skin] = 285;
					case 8: character_info[playerid][duty_skin] = 286;
					case 9: character_info[playerid][duty_skin] = 287;
					case 10: character_info[playerid][duty_skin] = 303;
					case 11: character_info[playerid][duty_skin] = 304;
					case 12: character_info[playerid][duty_skin] = 305;
					case 13: character_info[playerid][duty_skin] = 306;
					case 14: character_info[playerid][duty_skin] = 307;
					case 15: character_info[playerid][duty_skin] = 71;
					default: character_info[playerid][duty_skin] = character_info[playerid][skin];
				}
			}
			else
			{
				switch(listitem)
				{
					case 1: character_info[playerid][duty_skin] = 282;
					case 2: character_info[playerid][duty_skin] = 283;
					case 3: character_info[playerid][duty_skin] = 284;
					case 4: character_info[playerid][duty_skin] = 285;
					case 5: character_info[playerid][duty_skin] = 287;
					case 6: character_info[playerid][duty_skin] = 288;
					case 7: character_info[playerid][duty_skin] = 302;
					case 8: character_info[playerid][duty_skin] = 304;
					case 9: character_info[playerid][duty_skin] = 311;
					case 10: character_info[playerid][duty_skin] = 310;
					case 11: character_info[playerid][duty_skin] = 309;
					default: character_info[playerid][duty_skin] = character_info[playerid][skin];
				}
			}
			if(IsDuty(playerid)) SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			UpdatePlayerColor(playerid);
		}
		case 85:
		{
			if(!response) return 1;
			if(listitem < 0 || listitem > 17) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Произошла внутренняя ошибка. (FAKE BONE NUMBER)");
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
				SCM(friskid, COLOR_MSGSERVER, ">{FFFFFF} Игрок отказался от обыска. Администраторы уже оповещены об этом.");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы отказались от обыска.");
				PlayerLog(playerid, "отказался от обыска!");
			}
			else 
				FriskPlayer(friskid, playerid);
			DeletePVar(playerid, "frisk");
		}
		case 87:
		{
			if(!response) return 1;
			new targetid = GetPVarInt(playerid, "targetid") - 1;
			if(targetid <= -1) return 1;
			if(listitem == 2)
			{
				if(character_info[targetid][driveLic] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У игрока уже нет прав!");
				character_info[targetid][driveLic] = 0; 
				new str[180];
				format(str, sizeof(str), "отобрал права у %s", sendername(targetid, true));
				cmd_me(playerid, str);
				format(str, sizeof(str), ">{FFFFFF} %s отобрал ваши водительские права!");
				SCM(targetid, COLOR_MSGSERVER, str);
				return 1;
			}
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
							format(str, sizeof(str), ">{FFFFFF} Вы изъяли у %s: ", sendername(targetid));
							SCM(playerid, COLOR_MSGSERVER, str);
							format(str, sizeof(str), ">{FFFFFF} %s изъял у вас: ", sendername(playerid));
							SCM(targetid, COLOR_MSGSERVER, str);
							taked = true;
						}
						format(str, sizeof(str), "%s", Items[itemid][Name]);
						SCM(playerid, COLOR_GRAY, str);
						format(str, sizeof(str), "%s", Items[itemid][Name]);
						SCM(targetid, COLOR_GRAY, str);
					}
				}
			}
			if(!taked) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Ничего не найдено!");
		}
		case 88:
		{
			if(!response) return 1;
			
			for(new i; i<MAX_VEHICLES; i++)
			{
				// GetPlayerVehicleID(playerid) > 1 && character_info[playerid][id] == veh_info[GetPlayerVehicleID(playerid)][owner] && veh_info[GetPlayerVehicleID(playerid)] > 0 || GetPlayerVehicleID(playerid) > 1 && character_info[playerid][factionid] == ntop(veh_info[GetPlayerVehicleID(playerid)][owner]) && veh_info[GetPlayerVehicleID(playerid)] < 0 || 
				
				new Float:x, Float:y, Float:z;
				GetCoordBootVehicle(i, xyz);
				
				if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot] || i==GetPlayerVehicleID(playerid) && GetPlayerVehicleID(playerid) != 0 && veh_info[GetPlayerVehicleID(playerid)][owner] == character_info[playerid][id])
				{
					new count_take = strval(inputtext), vehslot = player_info[playerid][inv_selected];
					if(!Items[character_info[playerid][inv][id][vehslot]][compound]) count_take = character_info[playerid][inv][count][vehslot];
					if(count_take < 1 || count_take > character_info[playerid][inv][count][vehslot]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество.");
					if(!character_info[playerid][inv][id][vehslot]) return 1;
					if(giveitemveh(i, character_info[playerid][inv][id][vehslot], count_take))
					{
						new str[64];
						Log_Write("logs/vehInv_log.txt", "[%s] %s put %s(%d) in car (%d)", ReturnDate(), sendername(playerid), Items[character_info[playerid][inv][id][vehslot]][Name], count_take, veh_info[i][id]);
						//printf("%s put %s(%d) in auto %d", sendername(playerid), Items[character_info[playerid][inv][id][vehslot]][Name], count_take, veh_info[i][id]);
						format(str, sizeof(str), "кладет %s(%d) в транспорт.", Items[character_info[playerid][inv][id][vehslot]][Name], count_take);
						if(!Items[character_info[playerid][inv][id][vehslot]][compound]) deleteitemslot(playerid, vehslot);
						else deleteitem(playerid, character_info[playerid][inv][id][vehslot], count_take);
						OOCMSG(playerid, str);
					}
					return 1;
				}
			}
			return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Рядом нет транспорта с открытым багажником!");
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
				if(PlayerToPoint(2.0, playerid, xyz) && veh_info[i][boot] || i==GetPlayerVehicleID(playerid) && GetPlayerVehicleID(playerid) != 0 && veh_info[GetPlayerVehicleID(playerid)][owner] == character_info[playerid][id])
				{
					new vehslot = GetPVarInt(playerid, "vehinv_slot"), count_take = strval(inputtext);
					if(count_take < 1 || count_take > veh_info[i][inv][count][vehslot]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Неверное количество.");
					if(!Items[veh_info[i][inv][id][vehslot]][compound]) 
					{
						count_take = veh_info[i][inv][count][vehslot];
						if(veh_info[i][inv][id][vehslot] == 0) return 1;
						new str[64];
						Log_Write("logs/vehInv_log.txt", "[%s] %s take %s(%d) from car (%d)", ReturnDate(), sendername(playerid), Items[veh_info[i][inv][id][vehslot]][Name], count_take, veh_info[i][id]);
						//printf("%s take %s(%d) from auto %d", sendername(playerid), Items[veh_info[i][inv][id][vehslot]][Name], count_take, veh_info[i][id]);
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
						Log_Write("logs/vehInv_log.txt", "[%s] %s take %s(%d) from car (%d)", ReturnDate(), Items[giveitemid][Name], count_take, veh_info[i][id]);
						//printf("%s take %s(%d) from auto %d", sendername(playerid), Items[giveitemid][Name], count_take, veh_info[i][id]);
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
			switch(listitem)
			{
				case 0:
				{
					new str[128];
					format(str, sizeof(str), "{FFFFFF}Баланс: %d$\nВведите сумму для снятия:", character_info[playerid][bank]);
					ShowPlayerDialog(playerid, 93, DIALOG_STYLE_INPUT, "Банкомат", str, "Ввести", "Отмена");
				}
				case 1:
				{
					new str[128];
					format(str, sizeof(str), "{FFFFFF}Денег на руках: %d$\nВведите сумму пополнения счета:", character_info[playerid][money]);
					ShowPlayerDialog(playerid, 94, DIALOG_STYLE_INPUT, "Банкомат", str, "Ввести", "Отмена");
				}
				case 2:
				{
					new str[128];
					format(str, sizeof(str), "{FFFFFF}Баланс: %d$\nВведите сумму для перевода:", character_info[playerid][bank]);
					ShowPlayerDialog(playerid, 95, DIALOG_STYLE_INPUT, "Банкомат", str, "Ввести", "Отмена");
				}
				case 3:
				{
					new bool:isset=false, str[(32+18+11)*MAX_TICKETS] = "Сумма\tПричина\tДата\n";
					for(new i; i<MAX_TICKETS; i++)
					{
						if(ticket_info[playerid][i][tId] <= 0) continue;
						if(!isset) isset=true;
						format(str, sizeof(str), "%s$%d\t%s\t%s\n", str, ticket_info[playerid][i][tSumm], ticket_info[playerid][i][tReason], ticket_info[playerid][i][tDate]);
					}
					if(!isset) SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет неоплаченных штрафов!");
					else ShowPlayerDialog(playerid, 115, DIALOG_STYLE_TABLIST_HEADERS, "Неоплаченные штрафы", str, "Выбрать", "Отмена");
				}
			}
		}
		case 93:
		{
			if(!response) return 1;
			if(!InATM(playerid)) return 1;
			new moneycount = strval(inputtext);
			if(moneycount < 1 || moneycount > 10000000) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте число от 1$ до 10000000$.");
			if(character_info[playerid][bank] < moneycount) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет такого количества денег.");
			character_info[playerid][bank] -= moneycount;
			givemoney(playerid, moneycount, "from bank");
			if(!BankSMS(playerid, "С вашего баланса были сняты средства.", moneycount)) SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно сняли деньги со своего банковского счета.");
		}
		case 94:
		{
			if(!response) return 1;
			if(!InATM(playerid)) return 1;
			new moneycount = strval(inputtext);
			if(moneycount < 1 || moneycount > 10000000) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте число от 1$ до 10000000$.");
			if(character_info[playerid][money] < moneycount) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет такого количества денег.");
			character_info[playerid][bank] += moneycount;
			takemoney(playerid, moneycount, "in bank");
			if(!BankSMS(playerid, "Ваш счет в банке был пополнен.", moneycount)) SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно пополнили свой банковский счет.");
		}
		case 95:
		{
			if(!response) return 1;
			new moneycount = strval(inputtext);
			if(moneycount < 1 || moneycount > 10000000) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте число от 1$ до 10000000$.");
			if(character_info[playerid][bank] < moneycount) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет такой суммы на банковском счету.");
			SetPVarInt(playerid, "transfer_money", moneycount);
			ShowPlayerDialog(playerid, 96, DIALOG_STYLE_INPUT, "Банкомат", "{ffffff}Введите номер счета для перевода:\n{b1b1b1}(( Введите ID персонажа или часть его ника! ))", "Выбрать", "Отмена"); 
		}
		case 96:
		{
			if(!InATM(playerid)) return 1;
			
			//return SCM(playerid,COLOR_MSGERROR, ">{FFFFFF} Технические работы на стороне банка. Перевод денег временно недоступен.");
			
			new user;
			if(sscanf(inputtext,"u", user) || !response)
			{
				DeletePVar(playerid, "transfer_money");
				return 1;
			}
			if(!IsPlayerLoged(user)) 
			{
				DeletePVar(playerid, "transfer_money");
				SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Игрок оффлайн");
				return 1;
			}
			new moneycount = GetPVarInt(playerid, "transfer_money");
			if(moneycount < 1 || moneycount > 10000000) 
			{
				DeletePVar(playerid, "transfer_money");
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Используйте число от 1$ до 10000000$.");
			}
			if(character_info[playerid][bank] < moneycount) 
			{
				DeletePVar(playerid, "transfer_money");
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет такой суммы на банковском счету!");
			}
			character_info[user][bank] += moneycount;
			character_info[playerid][bank] -= moneycount;
			BankSMS(user, "Ваш банковский счет был пополнен!");
			new str[128];
			format(str, sizeof(str), "С вашего баланса совершен перевод на счет %06d", character_info[user][id]);
			if(!BankSMS(playerid, str, moneycount)) SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно совершили перевод!");
			
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
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте клавиши Y и N для выбора интерьера.");
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Воспользуйтесь командой повторно, чтобы вернуться назад или установить имущество.");
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
			if(strlen(property[target_type]) < 2) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ввели неверное значение!");
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
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже взламываете транспортное средство!");
			
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
							if(veh_info[i][owner] < 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете угнать фракционный транспорт!");
							if(!veh_info[i][lock]) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот транспорт уже открыт!");
							
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы начали взлом замка!");
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Продолжительность взлома зависит от уровня защиты замка и удачи.");
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы можете прервать процесс нажатием клавиши быстрого бега.");
							SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Если вы попали в поле зрение камеры CCTV, полицейские могут получить предупреждение в любой момент!");
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
					if(!InFactionType(playerid, FACTIONTYPE_GANG) && !InFactionType(playerid, FACTIONTYPE_MAFIA)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Функция доступна только членам криминальных группировок.");
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
					if(v == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не находитесь у багажника транспорта или у этого транспорта нет багажника.");
					SetPVarInt(playerid, "breaking_veh_id_boot", v);
					
					if(veh_info[v][lock_type] == 2) SetPVarInt(playerid, "breaking_veh_processing", 250);
					else if(veh_info[v][lock_type] == 3) SetPVarInt(playerid, "breaking_veh_processing", 350);
					else SetPVarInt(playerid, "breaking_veh_processing", 150);
					
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы начали взлом замка багажника!");
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы можете прервать процесс нажатием клавиши быстрого бега.");
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Если вы попали в поле зрение камеры CCTV, полицейские могут получить предупреждение в любой момент!");
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
				case 2:
				{
					new str[512];
					for(new i; i<sizeof(Tune_Wheels); i++) 
						format(str, sizeof(str), "%s%s\t%d$\n", str, Tune_Wheels[i][name], Tune_Wheels[i][price]);
					ShowPlayerDialog(playerid, 145, DIALOG_STYLE_TABLIST, "TUNE", str, "Выбрать", "Отмена");
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
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы установили выбранный замок!");
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
			
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
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы установили выбранную сигнализацию!");
			}
			else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
		}
		case 107:
		{
			if(!response) 
				return 1;
			
			if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
			
			SetPVarInt(playerid, "faction_attach", listitem);
			ShowPlayerDialog(playerid, 108, DIALOG_STYLE_TABLIST, "Выберите кость", 
			"Спина\nГолова\nПлечо левой руки\nПлечо правой руки\nЛевая рука\nПравая рука\nЛевое бедро\nПравое бедро\nЛевая нога\nПравая нога\nПравые икры\nЛевые икры\n\
			Левое предплечье\nПравое предплечье\nЛевая ключица\nПравая ключица\nШея\nЧелюсть", "Выбрать", "Отмена");
		}
		case 108:
		{
			if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
			
			for(new i = 0; i<MAX_ATTACH; i++)
			{
				if(attach[playerid][i][iditem] == -1)
				{
					if(GetPVarInt(playerid, "faction_attach_active")) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже пользуетесь редактором");
					
					SetPVarInt(playerid, "faction_attach_active", true);
					
					if(IsCop(playerid))
						SetPlayerAttachedObject(playerid, i, Items[PoliceAttaches[GetPVarInt(playerid, "faction_attach")]][Model], listitem+1);
					else if(IsMedic(playerid)) 
						SetPlayerAttachedObject(playerid, i, Items[LSFDAttaches[GetPVarInt(playerid, "faction_attach")]][Model], listitem+1);
					
					EditAttachedObject(playerid, i);
					return 1;
				}
			}
			return 1;
		}
		case 109:
		{
			if(!response) 
				return 1;
			if(!InFactionType(playerid, FACTIONTYPE_STATE)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вам недоступна эта команда!");
			
			if(character_info[playerid][editobject] > 0 || GetPVarInt(playerid, "attach_edit")) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы уже пользуетесь редактором!");
			
			new Float:angle, Float:x,Float:y,Float:z, obj;
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			x += floatsin(-angle, degrees);
			y += floatcos(-angle, degrees);
			obj = CreateDynamicObject(FactionObjects[listitem][Model], x, y, z-0.9, 0.0, 0.0, 0.0, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
			
			character_info[playerid][editobject] = obj;
			character_info[playerid][type_editobj] = 9;
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Используйте ESC чтобы выйти!");
			EditDynamicObject(playerid, obj);
		}
		case 110:
		{
			if(!response) return 1;
			new chid = strval(inputtext);
			new str[11];
			format(str, sizeof(str), "%d", chid);
			cmd_heal(playerid, str);
		}
		case 111:
		{
			if(!response) return KickEx(playerid);
			for(new Index = strlen(inputtext)-1; Index != -1; Index--)
			{
				switch(inputtext[Index])
				{
					case '0'..'9': continue;
					default: 
					{
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны ввести только цифры!");
						return ChangeVK(playerid);
					}				
				}
			}
			new inputvk = strval(inputtext);
			new randomcode = 10000 + random(99999);
			SetPVarInt(playerid, "ChangeVK_Code", randomcode);
			SetPVarInt(playerid, "ChangeVK_Id", inputvk);
			
			new str[128];
			format(str, sizeof(str), "Your%%20code%%20for%%20account%%20%s:%%20%d%%20(Classic%%20RP)", player_info[playerid][login], GetPVarInt(playerid, "ChangeVK_Code"));
			VKMSG(playerid, inputvk, str);
			ShowPlayerDialog(playerid, 112, DIALOG_STYLE_INPUT, "Подтвердите отправленный код", "На указанную страницу было отправлено сообщение, если сообщение не пришло убедитесь, что у вас открыты личные сообщения!", "Ввод", "Выход");
		}
		case 112:
		{
			if(!response) return KickEx(playerid);
			for(new Index = strlen(inputtext)-1; Index != -1; Index--)
			{
				switch(inputtext[Index])
				{
					case '0'..'9': continue;
					default: 
					{
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны ввести только цифры!");
						return ChangeVK(playerid);
					}				
				}
			}
			if(GetPVarInt(playerid, "ChangeVK_Code") == strval(inputtext) && GetPVarInt(playerid, "ChangeVK_Code") != 0)
			{
				player_info[playerid][vkid] = GetPVarInt(playerid, "ChangeVK_Id");
				AuthSucc(playerid);
			}
			else 
			{
				SCM(playerid, COLOR_TOMATO, "Вы ввели неверный код!");
				return KickEx(playerid);
			}
		}
		case 113:
		{
			if(!response) return KickEx(playerid);
			for(new Index = strlen(inputtext)-1; Index != -1; Index--)
			{
				switch(inputtext[Index])
				{
					case '0'..'9': continue;
					default: 
					{
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны ввести только цифры!");
						return KickEx(playerid);
					}				
				}
			}
			if(GetPVarInt(playerid, "AuthVK_Code") == strval(inputtext) && GetPVarInt(playerid, "AuthVK_Code") != 0)
			{
				AuthSucc(playerid);
			}
			else 
			{
				SCM(playerid, COLOR_TOMATO, "Вы ввели неверный код!");
				return KickEx(playerid);
			}
		}
		case 114:
		{
			if(!response) DeletePVar(playerid, "target_elevator");
			if(GetPVarInt(playerid, "target_elevator") == -1 || !GetPVarInt(playerid, "target_elevator")) return 1;
			new elevator = GetPVarInt(playerid, "target_elevator");
			DeletePVar(playerid, "target_elevator");
			new ii = 0;
			for(new i; i<MAX_ELEVATORS; i++)
			{
				if(elevator_info[i][elevatorid] == elevator)
				{
					if(listitem == ii)
					{
						SetPlayerPos(playerid, elevator_info[i][posX], elevator_info[i][posY], elevator_info[i][posZ]);
						SetPlayerVw(playerid, elevator_info[i][VW]);
						SetPlayerInt(playerid, elevator_info[i][Interior]);
						Freeze(playerid, 1000); 
						return 1;
					}
					else ii++;
				}		
			}
		}
		case 115:
		{
			if(!response) return 1;
			new ticket_target;
			for(new i; i<MAX_TICKETS; i++)
			{
				if(ticket_info[playerid][i][tId] <= 0) continue;
				if(ticket_target == listitem)
				{
					if(takemoney(playerid, ticket_info[playerid][i][tSumm], "ticket", true) != 1) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
					new qu[33+11];
					format(qu, sizeof(qu), "DELETE FROM `tickets` WHERE id=%d", ticket_info[playerid][i][tId]);
					mysql_function_query(dbHandle, qu, false, "", "");
					LoadTickets(playerid);
				}
				else ticket_target++;
			}
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Штраф оплачен!");
		}
		case 116:
		{
			if(!response) 
				return 1;
			if(!IsDutyPickup(playerid)) 
				return 1;
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
						
						attach_player_update(playerid);
						UpdatePlayerColor(playerid);
					}
					else
					{
						character_info[playerid][duty] = 1;
						fmsg(playerid, "вышел на дежурство.");
						if(character_info[playerid][gun] > 0) return cmd_invwep(playerid);
						UpdatePlayerColor(playerid);
					}
				}
				case 1:
				{
					ShowPlayerDialog(playerid, 118, DIALOG_STYLE_LIST, "DUTY", "Свой скин\n70\n274\n275\n276\n277\n278\n279\n303\n304\n305\n306\n307\n308", "Выбрать", "Отмена");
				}
				case 2:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					SetPVarFloat(playerid, "arrmor", 99.89);
					SetPlayerHealth(playerid, 99.89);
					UpdateArm(playerid);
				}
				case 3:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					if(checkitem(playerid, 83) > -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас уже есть рация!");
					giveitem(playerid, 83, 1);
				}
				case 4:
				{
					ShowPlayerDialog(playerid, 117, DIALOG_STYLE_LIST, "DUTY", "Бензопила\nОгнетушитель\nЛом\nЛопата\nТопор", "Выбрать", "Отмена");
				}
			}
		}
		case 117:
		{
			if(!response) return 1;
			if(!IsDutyPickup(playerid)) return 1;
			switch(listitem)
			{
				case 0: giveitem(playerid, 115); // Бензопила
				case 1: giveitem(playerid, 116); // Огнетушитель
				case 2: giveitem(playerid, 117); // Лом
				case 3: giveitem(playerid, 118); // Лопата
				case 4: giveitem(playerid, 119); // Топор
				default: SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} ОШИБКА!");
			}
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы взяли выбранный предмет!");
		}
		case 118:
		{
			if(!response) return 1;
			if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
			switch(listitem)
			{
				case 1: character_info[playerid][duty_skin] = 70;
				case 2: character_info[playerid][duty_skin] = 274;
				case 3: character_info[playerid][duty_skin] = 275;
				case 4: character_info[playerid][duty_skin] = 276;
				case 5: character_info[playerid][duty_skin] = 277;
				case 6: character_info[playerid][duty_skin] = 278;
				case 7: character_info[playerid][duty_skin] = 279;
				case 8: character_info[playerid][duty_skin] = 303;
				case 9: character_info[playerid][duty_skin] = 304;
				case 10: character_info[playerid][duty_skin] = 305;
				case 11: character_info[playerid][duty_skin] = 306;
				case 12: character_info[playerid][duty_skin] = 307;
				case 13: character_info[playerid][duty_skin] = 308;
				default: character_info[playerid][duty_skin] = character_info[playerid][skin];
				
			}
			if(IsDuty(playerid)) SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			UpdatePlayerColor(playerid);
		}
		case 119:
		{
			if(!response) 
				return 1;
			if(player_info[playerid][settings][listitem]) 
				player_info[playerid][settings][listitem] = 0;
			else 
				player_info[playerid][settings][listitem] = 1;
			
			UpdateSettings(playerid);
			cmd_settings(playerid);
		}
		case 120:
		{
			if(!response) return 1;
			new str[1200] = "Команда\tОписание\n{ffffff}";
			new new_str[64+25];
			for(new i; i<sizeof(HelpInfo); i++)
			{
				if(HelpInfo[i][TYPE] == listitem || listitem == 5 && HelpInfo[i][TYPE] == -1 && InFactionType(playerid,LSPD_FACTION) || listitem == 5 && HelpInfo[i][TYPE] == -1 && InFactionType(playerid,SASD_FACTION) || listitem == 5 && HelpInfo[i][TYPE] == -2 && InFactionType(playerid,SAN_FACTION))
				{
					format(new_str, sizeof(new_str), "%s\t%s\n", HelpInfo[i][CMDTEXT], HelpInfo[i][CMDDESC]);
					strcat(str, new_str);
				}
			}
			ShowPlayerDialog(playerid, 0, DIALOG_STYLE_TABLIST_HEADERS, "HELP", str, "Закрыть", "");
		}
		case 121:
		{
			if(!response) return 1;
			for(new i; i<sizeof(Donate); i++)
			{
				if(listitem == i)
				{
					if(player_info[playerid][donate] < Donate[i][Price]) SCM(playerid, COLOR_TOMATO, ">{ffffff} У вас недостаточно денег на счету.");
					else
					{				
						switch(Donate[i][Key])
						{
							case DONATEKEY_BRONZEPREMIUM:
							{
								player_info[playerid][donate] -= Donate[i][Price];
								player_info[playerid][vip] = PREMIUM_BRONZE;
								player_info[playerid][vip_time] = gettime() + (60 * 60 * 24)*30;
								player_info[playerid][changename] += 2;
							}
							case DONATEKEY_SILVERPREMIUM:
							{
								player_info[playerid][donate] -= Donate[i][Price];
								player_info[playerid][vip] = PREMIUM_SILVER;
								player_info[playerid][vip_time] = gettime() + (60 * 60 * 24)*30;
								player_info[playerid][changename] += 4;
							}
							case DONATEKEY_GOLDPREMIUM:
							{
								player_info[playerid][donate] -= Donate[i][Price];
								player_info[playerid][vip] = PREMIUM_GOLD;
								player_info[playerid][vip_time] = gettime() + (60 * 60 * 24)*30;
								
							}
							case DONATEKEY_CHANGENAME: 
							{
								player_info[playerid][donate] -= Donate[i][Price];
								player_info[playerid][changename]++;
							}
							case DONATEKEY_BOX: 
							{
								player_info[playerid][donate] -= Donate[i][Price];
								giveitem(playerid, 151);
							}
							case DONATEKEY_HOURSRESET:
							{
								player_info[playerid][donate] -= Donate[i][Price];
								character_info[playerid][hours_today] = 0;
								SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Теперь вы снова можете получить зарплату!");
							}
							case DONATEKEY_CHANGEUCP:
							{
								cmd_changeucp(playerid);
								return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} /changeucp");
							}
							case DONATEKEY_CHANGESEX:
							{
								cmd_changesex(playerid);
								return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} /changesex");
							}
							case DONATEKEY_CHANGEBD:
							{
								cmd_changebd(playerid);
								return SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} /changebd");
							}
						}
						new str[128];
						format(str, sizeof(str), "(%d) uid: %d, chid: %d | key: %d, %d\n", gettime(), player_info[playerid][id], character_info[playerid][id], Donate[i][Key], player_info[playerid][vip_time]);
						WriteOneString("donate.txt", str);
						SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы сделали покупку!");
					}
					return cmd_donate(playerid);
				}
			}
		}
		case 122:
		{
			new v = GetPVarInt(playerid, "veh_id");
			if(!response || GetPVarInt(playerid, "veh_price") < 0 || v <= 0 || veh_info[v][owner] != character_info[playerid][id]) 
				return 1;
			
			new veh_price = GetPVarInt(playerid, "veh_price");
			
			DeletePVar(playerid, "veh_price");
			DeletePVar(playerid, "veh_id");
			
			new qu[28+11];
			format(qu, sizeof(qu), "DELETE FROM `cars` WHERE id=%d", veh_info[v][id]);
			mysql_function_query(dbHandle, qu, false, "", "");
			givemoney(playerid, veh_price, "sellcar");
			DestroyVehicleEx(v, false);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы продали автомобиль!");
		}
		case 123:
		{
			new seller = GetPVarInt(playerid, "sellcar_playerid")-1;
			new seller_vehid = GetPVarInt(playerid, "sellcar_vehid");
			new seller_price = GetPVarInt(playerid, "sellcar_price");
			new v = GetPlayerVehicleID(seller);
			DeletePVar(playerid, "sellcar_playerid"),DeletePVar(playerid, "sellcar_vehid"),DeletePVar(playerid, "sellcar_price");
			if(v != seller_vehid) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Владелец автомобиля покинул транспорт!");
			if(!response || seller_vehid <= 0 || seller <= -1 || seller_price <= 0 || !IsPlayerLoged(seller)) return 1;
			new floatxyz;
			GetPlayerPos(playerid, xyz);
			if(!PlayerToPoint(5.0, seller, xyz)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");
			
			new str[124];
			format(str, sizeof(str), "buy car by %d", character_info[seller][id]); 
			if(takemoney(playerid, seller_price, str) == 1)
			{
				format(str, sizeof(str), "sell car in %d", character_info[playerid][id]); 
				givemoney(seller, seller_price, str);
				veh_info[seller_vehid][owner] = character_info[playerid][id];
				veh_info[seller_vehid][lock] = true;
				veh_info[seller_vehid][engine] = false;
				UpdateVehParams(seller_vehid);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы приобрели автомобиль!");
				SCM(seller, COLOR_MSGSERVER, ">{FFFFFF} Вы продали автомобиль!");
				format(str, sizeof(str), "купил автомобиль %d за %d$ (Продавец: %s)", seller_vehid, seller_price, character_info[seller][name]);
				PlayerLog(playerid, str);
			}
			else
			{
				SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
				SCM(seller, COLOR_MSGERROR, ">{FFFFFF} У покупателя недостаточно денег!");
			}
		}
		case 124:
		{
			if(!response) return 1;
		    if(!InPropType(playerid, 3)) return 1;
			if(takemoney(playerid, list_bar[listitem][price], "buy item bar") == 1)
   			{
				if(!giveitem(playerid, list_bar[listitem][iditem], 1))
				   return givemoney(playerid, list_bar[listitem][price], "no itemslot for buy item");
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_bar[listitem][price]-(list_bar[listitem][price]/4);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
		}
		case 125:
		{
			if(!response) return 1;
		    if(!InPropType(playerid, 4)) return 1;
			if(takemoney(playerid, list_club[listitem][price], "buy item club") == 1)
   			{
				if(!giveitem(playerid, list_club[listitem][iditem], 1))
				   return givemoney(playerid, list_club[listitem][price], "no itemslot for buy item");
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_club[listitem][price]-(list_club[listitem][price]/4);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
		}
		case 126:
		{
			if(!response) return 1;
		    if(!InPropType(playerid, 5)) return 1;
			if(takemoney(playerid, list_eatery[listitem][price], "buy item eatery") == 1)
   			{
				if(!giveitem(playerid, list_eatery[listitem][iditem], 1))
				   return givemoney(playerid, list_eatery[listitem][price], "no itemslot for buy item");
				prop_info[GetLocalIdProp(character_info[playerid][prop])][money] += list_eatery[listitem][price]-(list_eatery[listitem][price]/4);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку");
    		}
    		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег");
		}
		case 127:
		{
			if(!response) 
				return Kick(playerid);
			
			new qu[256+50];
			mysql_real_escape_string(inputtext, inputtext);
			format(qu, sizeof(qu), "SELECT users.id, users.login FROM users JOIN characters ON users.id=characters.userid WHERE users.login='%s' OR characters.name = '%s'", inputtext, inputtext);
			mysql_function_query(dbHandle, qu, true, "player_check", "i", playerid);
			return 1;
		}
		case 128:
		{
			switch(listitem)
			{
				case 0:
				{
					if(PlayerToPoint(3.0, playerid, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ")))
					{
						PickUpBoombox(playerid);
						SendClientMessage(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы успешно подняли бумбокс!");
					}
					else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны находится возле бумбокса!");
				}
				case 1:
				{
					new str[512] = "{FFFFFF}Ввести URL\nОтключить бумбокс\n{b1b1b1}";
					for(new i; i<MAX_RADIO_STATION; i++)
					{
						if(strlen(radio_station[i][Name]) < 3) continue;
						format(str, sizeof(str), "%s%s\n", str, radio_station[i][Name]);
					}
					ShowPlayerDialog(playerid,130,DIALOG_STYLE_LIST,"Бумбокс",str,"Select", "Cancel");
				}
			}
		}
		case 129:
		{
			if(!response)
			{
				phoneAnim(playerid, 0);
				return 1;
			}

			format(Call911[playerid][msg_1], 90, "%s", inputtext);
				
			ShowPlayerDialog(playerid, 1291, DIALOG_STYLE_INPUT, "Вызвать 911", "Хорошо, где Вы находитесь?", "Ввод", "Отмена");
			return 1;
		}
		case 1291:
		{
			if(!response)
			{
				phoneAnim(playerid, 0);
				return 1;
			}
			
			format(Call911[playerid][msg_2], 90, "%s", inputtext);
			ShowPlayerDialog(playerid, 1292, DIALOG_STYLE_INPUT, "Вызвать 911", "Какие службы Вам требуются?", "Ввод", "Отмена");
		}
		
		case 1292:
		{
			if(!response)
			{
				phoneAnim(playerid, 0);
				return 1;
			}
			format(Call911[playerid][msg_3], 90, "%s", inputtext);
			phoneAnim(playerid, 0);
			
			Add911(playerid, Call911[playerid][msg_1], Call911[playerid][msg_2], Call911[playerid][msg_3]);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили звонок в 911!");
		}
		
		case 130:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					ShowPlayerDialog(playerid,131,DIALOG_STYLE_INPUT, "URL", "{ffffff}Пожалуйста введите ссылку на аудиозапись в поле ниже:", "Play", "Cancel");
				}
				case 1:
				{
					if(GetPVarType(playerid, "BBArea"))
					{
						foreach(new i : Player)
						{
							if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
							{
								StopStream(i);
							}
						}
						DeletePVar(playerid, "BBStation");
					}
					SendClientMessage(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы отключили бумбокс!");
				}
				default:
				{
					if(GetPVarType(playerid, "PlacedBB"))
					{
						new r;
						for(; r<MAX_RADIO_STATION; r++)
						{
							if(strlen(radio_station[r][Name]) < 3) continue;
							if(listitem-2 == r) break;
						}
						foreach(new i : Player)
						{
							if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
							{
								PlayStream(i, radio_station[r][URL], GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ"), 30.0, 1);
							}
						}
						SetPVarString(playerid, "BBStation", radio_station[r][URL]);
					}
				}
			}
			return 1;
		}
		case 131:
		{
			if(response == 1)
			{
				if(isnull(inputtext))
				{
					SendClientMessage(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы ничего не ввели!" );
					return 1;
				}
				if(strlen(inputtext))
				{
					if(GetPVarType(playerid, "PlacedBB"))
					{
						foreach(new i : Player)
						{
							if(IsPlayerInDynamicArea(i, GetPVarInt(playerid, "BBArea")))
							{
								PlayStream(i, inputtext, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ"), 30.0, 1);
							}
						}
						SetPVarString(playerid, "BBStation", inputtext);
					}
				}
			}
			return 1;
		}
		case 132:
		{
			new propid = OwnerProp(playerid);
			if(propid <= -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не владелец этого помещения!");
			format(prop_info[propid][Name], 25, "%s", inputtext);
			return 1;
		}
		case 133:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					ShowPlayerDialog(playerid, 134, DIALOG_STYLE_INPUT, "Ключ для имущества", "{ffffff}Стоимость ключа: {b1b1b1}200$\n{ffffff}Введите номер вашего имущества: \n{b1b1b1}(Подсказка: Используйте /pr info)", "Ввод", "Отмена");
				}
				case 1:
				{
					ShowPlayerDialog(playerid, 135, DIALOG_STYLE_INPUT, "Ключ для автомобиля", "{ffffff}Стоимость ключа: {b1b1b1}200$\n{ffffff}Введите номер вашего автомобиля: \n{b1b1b1}(Подсказка: Используйте /carlist)", "Ввод", "Отмена");
				}
			}
		}
		case 134..135:
		{
			if(!response) return 1;
			new targetid;
			if(sscanf(inputtext,"d", targetid)) 
				return 1;
			if(dialogid == 134)
			{
				new p = GetLocalIdProp(targetid);
				if(prop_info[p][owner] != character_info[playerid][id])
				{
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не владелец!");
					return cmd_buy(playerid);
				}
				if(takemoney(playerid, 200, "buy key prop") != 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!"); 
				giveitem(playerid, 148, prop_info[p][id]);
			}
			else 
			{
				if(veh_info[targetid][owner] != character_info[playerid][id])
				{
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не владелец!");
					return cmd_buy(playerid);
				}
				if(takemoney(playerid, 200, "buy key car") != 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!"); 
				giveitem(playerid, 149, veh_info[targetid][id]);
			}
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы совершили покупку!");
		}
		case 1361:
		{
			if(!response) 
				return 1;
			
			if(!InFactionId(playerid, SAN_FACTION)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет доступа к этой команде!");
			
			new msg_id = GetPVarInt(playerid, "ad_target");			
			switch(listitem)
			{
				case 0: format(ads_info[msg_id][msg], 180, "Транспорт | %s", ads_info[msg_id][msg]);
				case 1: format(ads_info[msg_id][msg], 180, "Недвижимость | %s", ads_info[msg_id][msg]);
				case 2: format(ads_info[msg_id][msg], 180, "Работа | %s", ads_info[msg_id][msg]);
				case 3: format(ads_info[msg_id][msg], 180, "Услуги | %s", ads_info[msg_id][msg]);
				case 4: format(ads_info[msg_id][msg], 180, "Реклама | %s", ads_info[msg_id][msg]);
				case 5: format(ads_info[msg_id][msg], 180, "Рынок | %s", ads_info[msg_id][msg]);
				case 6: format(ads_info[msg_id][msg], 180, "Поиск | %s", ads_info[msg_id][msg]);
			}
			
			Ad_Approved(playerid, msg_id);
		}
		case 136:
		{
			if(!response) 
				return 1;
			if(!InFactionId(playerid, SAN_FACTION)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет доступа к этой команде!");
		
			SetPVarInt(playerid, "ad_target", listitem);
			new msg_id = GetPVarInt(playerid, "ad_target");	
			
			if(ads_info[msg_id][owner] == -1) 
				return cmd_admenu(playerid);
		
			SendClientMessageEx(playerid, -1, "Сообщение: %s", ads_info[msg_id][msg]);
			
			
			ShowPlayerDialog(playerid, 146, DIALOG_STYLE_LIST, "ADMENu", "Отправить\nРедактировать\nУдалить", "Выбрать", "Отмена");
		}
		case 137:
		{
			if(!response) return 1;
			DestroyCheckpoint(playerid);
			SetPVarInt(playerid, "search_checkpoint", 1);
			SetPlayerCheckpoint(playerid, gps_data[listitem][posX], gps_data[listitem][posY], gps_data[listitem][posZ], 5.0);
		}
		case 138:
		{
			if(!response) return 1;
			if(!IsDuty(playerid)) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
			switch(listitem)
			{
				case 1: character_info[playerid][duty_skin] = 303;
				case 2: character_info[playerid][duty_skin] = 304;
				case 3: character_info[playerid][duty_skin] = 305;
				case 4: character_info[playerid][duty_skin] = 285;
				case 5: character_info[playerid][duty_skin] = 286;
				case 6: character_info[playerid][duty_skin] = 255;
				case 7: character_info[playerid][duty_skin] = 61;
				case 8: character_info[playerid][duty_skin] = 71;
				case 9: character_info[playerid][duty_skin] = 150;
				case 10: character_info[playerid][duty_skin] = 253;
				case 11: character_info[playerid][duty_skin] = 163;
				case 12: character_info[playerid][duty_skin] = 164;
				default: character_info[playerid][duty_skin] = character_info[playerid][skin];
				
			}
			if(IsDuty(playerid)) SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			UpdatePlayerColor(playerid);
		}
		case 139:
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0: 
				{
					new str[11];
					format(str, sizeof(str), "%d", playerid);
					cmd_stats(playerid, str);
				}
				case 1: cmd_inventory(playerid);
				case 2: cmd_help(playerid);
				case 3: 
				{
					ShowPlayerDialog(playerid, 140, DIALOG_STYLE_INPUT, "Подать жалобу", "{ffffff}Введите содержимое вашей жалобы: ", "Ввод", "Отмена");
				}
				case 4:
				{
					ShowPlayerDialog(playerid, 141, DIALOG_STYLE_INPUT, "Задать вопрос", "{ffffff}Введите содержимое вашего вопроса: ", "Ввод", "Отмена");
				}
				case 5: cmd_changecharacter(playerid);
				case 6: cmd_description(playerid);
				case 7: cmd_settings(playerid);
			}
		}
		case 140:
		{
			if(!response) return 1;
			cmd_report(playerid, inputtext);
		}
		case 141:
		{
			if(!response) return 1;
			cmd_ask(playerid, inputtext);
		}
		case 142:
		{
			new i = GetPVarInt(playerid, "graf_i");
			DeletePVar(playerid, "graf_i");
			if(!response) return 1;
			graff_info[i][gOwner] = 0;
			graff_info[i][gX]= 0.0;
			graff_info[i][gY]= 0.0;
			graff_info[i][gZ]= 0.0;
			DestroyDynamicObject(graff_info[i][gObj]);
			new qu[29+11];
			format(qu, sizeof(qu), "delete from graff where id=%d", graff_info[i][gID]);
			mysql_function_query(dbHandle, qu, false, "", "");
			//printf("%s delete graff %s", player_info[playerid][login], graff_info[i][gText]);
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Граффити удалено!");
			return 1;
		}
		case 143:
		{
			if(!response) return 1;
			new slot = finditem(playerid, 151);
			if(slot >= 0) useitem(playerid, slot);
		}
		case 144:
		{
			if(!response) return Kick(playerid);
			if(strlen(inputtext) < 8 || strlen(inputtext) > 30) return ShowPlayerDialog(playerid, 144, DIALOG_STYLE_PASSWORD, "Смена пароля","{ffffff}В целях безопасности измените свой пароль, длина пароля должна быть от 8 символов\nВведите новый пароль:", "Ввод", "");
			new temp[128];
	        mysql_real_escape_string(inputtext, temp);
			new MyHash[64 + 1];
    		SHA256_PassHash(temp, "", MyHash, sizeof MyHash);
			new qu[52+128];
			format(qu, sizeof(qu), "update users set pass='%s',passchanged=1 where id=%d", MyHash, player_info[playerid][id]);
			mysql_function_query(dbHandle, qu, false, "", "");
			new str[180];
			format(str, sizeof(str), ">{FFFFFF} Ваш новый пароль: %s", inputtext);
			SCM(playerid, COLOR_GREEN, str);
			character_check(playerid, player_info[playerid][id]);
		}
		case 145:
		{
			if(!response) return 1;
			new i;
			for(; i<sizeof(Tune_Wheels); i++) if(listitem == i) break;
			if(!InServiceStation(playerid)) return 1;
			new v = GetPlayerVehicleID(playerid);
			if(takemoney(playerid, Tune_Wheels[i][price], "tuning wheels") == 1	)
			{
				veh_info[v][wheels] = Tune_Wheels[i][component];
				AddVehicleComponent(v, Tune_Wheels[i][component]);
			}
		}
		case 146:
		{
			if(!response) 
				return 1;

			new msg_id = GetPVarInt(playerid, "ad_target");
			switch(listitem)
			{
				case 0: ShowPlayerDialog(playerid, 1361, DIALOG_STYLE_LIST, "ADMENU", "Транспорт |\nНедвижимость |\nРабота |\nУслуги |\nРеклама |\nРынок |\nПоиск |", "Принять", "Отмена");
				case 1:
				{
					new str[27+16+180];
					format(str, sizeof(str), "{ffffff}%s\n{b1b1b1}Введите новое объявление:", ads_info[msg_id][msg]);
					ShowPlayerDialog(playerid, 147, DIALOG_STYLE_INPUT, "ADMENU", str, "Принять", "Отмена");
				}
				case 2: Ad_Reject(playerid, msg_id);
			}
		}
		case 147:
		{
			if(!response) 
				return 1;
			
			new msg_id = GetPVarInt(playerid, "ad_target");
			
			if(strlen(inputtext) > 0) 
				format(ads_info[msg_id][msg], 180, "%s", inputtext);
			else
				return cmd_admenu(playerid);
					
			ShowPlayerDialog(playerid, 1361, DIALOG_STYLE_LIST, "ADMENU", "Транспорт |\nНедвижимость |\nРабота |\nУслуги |\nРеклама |\nРынок |\nПоиск |", "Принять", "Отмена");
		}
		case 148:
		{
			if(!response) return 1;
			new propid = OwnerProp(playerid);
			if(propid <= -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не владелец этого помещения!");
			if(prop_info[propid][type] == 0) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} К сожалению, эта функция отключена для домов!");
			new input_price = strval(inputtext);
			if(input_price < 0 || input_price > 150) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Стоимость должна быть от 0 до 150!");
			prop_info[propid][enter_price] = input_price;
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы установили цену за вход!");
		}
		case 149:
		{
			if(!response) 
				return 1;
				
			if(IsAdmin(playerid, 1, false, false)) 
				return 1;
			
			cmd::aduty(playerid);
		}
		/*	
		case 150: 
		{
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					new str[1028], color[16], count_text[16], itemname_text[34];
					for(new i = 0; i<MAX_INV_SLOTS; i++)
					{
					    format(itemname_text, sizeof(itemname_text), "%s", senderitems(0)), format(count_text, sizeof(count_text), "");
					 	if(character_info[playerid][inv][count][i] < 1)
						{
							character_info[playerid][inv][id][i] = 0;
					 		character_info[playerid][inv][count][i] = 0;
						}
				  		if(character_info[playerid][inv][id][i] == 0) color = "{AFAFAF}";
						else color = "{ffffff}";

						if(character_info[playerid][inv][id][i] != 0)
						{
							if(Items[character_info[playerid][inv][id][i]][compound])
							{
								format(itemname_text, sizeof(itemname_text), "%s",  senderitems(character_info[playerid][inv][id][i]));
				    			if(character_info[playerid][inv][count][i] > 1)
									format(count_text, sizeof(count_text), "Кол-во: %d", character_info[playerid][inv][count][i]);
							}
							else format(itemname_text, sizeof(itemname_text), "{b1b1b1}%s (%d)", senderitems(character_info[playerid][inv][id][i]), character_info[playerid][inv][count][i]);
						}

						format(str, sizeof(str), "%s{AFAFAF}%d. %s%s\t%s\n",str, i+1, color, itemname_text, count_text);
				 	}
				 	ShowPlayerDialog(playerid, 151, DIALOG_STYLE_TABLIST, "CRAFT", str, "Добавить", "Отмена");
				}
				case 1:
				{
					// Крафт
					new count_craft;
					for(new i; i<MAX_CRAFT; i++) if(craft_info[playerid][cItem][i] != 0) count_craft++;
					if(count_craft < 2) // если выбрано менее двух предметов  
					{
						cmd_craft(playerid);
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете совместить меньше двух предметов!");
					}
					for(new c; c<sizeof(craft); c++) // цикл каждого рецепта, поиск рецепта
					{
						new succ_craft_item, craft_count, bug_str[100];

						while(craft_count < 1000) // Расчитываем на сколько комбинаций по рецепту нам хватит выбранных предметов
						{
							//printf("[while debug] user %d(%d). While %d", playerid, player_info[playerid][id], craft_count);
							for(new i; i<MAX_CRAFT; i++) 
							{
								if(craft[c][craftitem][i] == 0 || FindCraftItem(playerid,craft[c][craftitem][i],craft[c][craftcount][i]*(craft_count+1))) succ_craft_item++;
							}
							if(succ_craft_item == MAX_CRAFT)  
							{
								craft_count++; 
								succ_craft_item = 0;
							}
							else break; // с каждым циклом craft_count всё больше и как только количество одно из ингридиентов превысит указанное количество - завершаем цикл
						}
						if(craft_count >= 1) // если мы можем сделать хоть что-то
						{
							new succ_craft_item_delete; 
							for(new i; i<MAX_CRAFT; i++) if(craft_info[playerid][cItem][i] != 0 && finditem(playerid, craft[c][craftitem][i], craft[c][craftcount][i]*(craft_count)) == -1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет всех ингридиентов!"); // перед удалением перепроверяем наличие предметов! Выше проверялось только указанное в /craft значение
							for(new i; i<MAX_CRAFT; i++)
							{
								if(craft_info[playerid][cItem][i] == 0 || deleteitem(playerid, craft[c][craftitem][i], craft[c][craftcount][i]*craft_count)) 
								{
									// пытаемся удалить выбранные предметы
									format(bug_str, sizeof(bug_str), "%s->%d:%d ", bug_str, craft[c][craftitem][i], craft[c][craftcount][i]*craft_count); // на случай если что-то пойдет не так
									succ_craft_item_delete++;
								}
								// else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет всех ингридиентов!");						
							}
							if(succ_craft_item_delete == MAX_CRAFT) // если всё удалено успешно
							{
								giveitem(playerid, craft[c][resultitem], craft[c][resultitemcount]*craft_count);
								updateCraftInfo(playerid);
								new str[128];
								format(str, sizeof(str), "Благодаря комбинации предметов вы получили: %s (%d)", senderitems(craft[c][resultitem]), craft[c][resultitemcount]);
								SCM(playerid, COLOR_GREEN, str);
								return 1;
							}
							else printf("%s bugged craft. [%s]", sendername(playerid), bug_str); // если что-то пошло не так
							return 1;
						}
						else
						{
							SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете совместить эти предметы!");
							cmd_craft(playerid);
						}
					}
				}
				case MAX_CRAFT+2: 
				{
					updateCraftInfo(playerid);
					cmd_craft(playerid);
				}
				default:
				{
					new slot = listitem-2;		
					craft_info[playerid][cItem][slot] = 0;
					craft_info[playerid][cCount][slot] = 0;
					cmd_craft(playerid); 
				}
			}

		}
		
		case 151:
		{
			if(!response) return cmd_craft(playerid);
			SetPVarInt(playerid, "target_craftitem", character_info[playerid][inv][id][listitem]);
			new str[78+9];
			format(str, sizeof(str), "{ffffff}Вы имеете %dшт. выбранного предмета!\nВведите необходимое количество: ", character_info[playerid][inv][count][listitem]);
			ShowPlayerDialog(playerid, 152, DIALOG_STYLE_INPUT, "CRAFT", str, "Добавить", "Отмена");
		}
		
		case 152:
		{
			new target_craftitem = GetPVarInt(playerid, "target_craftitem"), target_craftcount = strval(inputtext);
			DeletePVar(playerid, "target_craftitem");
			if(!response && target_craftcount < 0) return cmd_craft(playerid);
			if(target_craftitem == 0) 
			{
				cmd_craft(playerid);
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы выбрали пустой слот!");
			}
			if(!Items[target_craftitem][compound]) 
			{
				cmd_craft(playerid);
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы не можете выбрать этот предмет!");
			}

			for(new i; i < MAX_CRAFT; i++) 
			{
				if(craft_info[playerid][cItem][i] == target_craftitem) 
				{
					cmd_craft(playerid);
					return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Этот предмет уже выбран!");
				}
			}

			for(new i; i < MAX_CRAFT; i++)
			{
				if(craft_info[playerid][cItem][i] == 0)
				{
					craft_info[playerid][cItem][i] = target_craftitem;
					craft_info[playerid][cCount][i] = target_craftcount;
					GameTextForPlayer(playerid, "~g~Added", 1000, 3);
					return cmd_craft(playerid);
				}
			}
			SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы выбрали слишком много предметов для совмешения!");
		}
		*/
		case 153:
		{
			if(!response) 
				return 1;
			if(!IsDutyPickup(playerid)) 
				return 1;
			
			switch(listitem)
			{
				case 0:
				{	
					if(IsDuty(playerid))
					{
						character_info[playerid][duty] = 0;
						fmsg(playerid, "покинул дежурство.");
						character_info[playerid][duty_gun_1] = 0;
						
						UpdateDutyGuns(playerid);
						
						attach_player_update(playerid);
						UpdatePlayerColor(playerid);
						
						SetPlayerSkin(playerid, character_info[playerid][skin]);
					}
					else
					{
						character_info[playerid][duty] = 1;
						fmsg(playerid, "вышел на дежурство.");
						if(character_info[playerid][gun] > 0) return cmd_invwep(playerid);
						UpdatePlayerColor(playerid);
					}
				}
				case 1:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					
					if(checkitem(playerid, 83) > -1) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас уже есть рация!");
					giveitem(playerid, 83, 1);
				}
				case 2:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					
					character_info[playerid][duty_gun_1] = 43;
					UpdateDutyGuns(playerid);
				}
				case 3:
				{
					if(!IsDuty(playerid) || !IsDutyPickup(playerid)) 
						return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
					
					if(character_info[playerid][sex] == 1)
						ShowPlayerDialog(playerid, 154, DIALOG_STYLE_LIST, "DUTY", "Свой скин\n59\n72\n96\n101\n163\n164\n240\n250\n295\n296", "Выбрать", "Отмена");
					
					if(character_info[playerid][sex] == 2)
						ShowPlayerDialog(playerid, 155, DIALOG_STYLE_LIST, "DUTY", "Свой скин\n40\n76\n141\n148\n150\n192\n211\n219\n233\n263", "Выбрать", "Отмена");
				}
				
			}
		}
		case 154:
		{
			if(!response) 
				return 1;
			if(!IsDuty(playerid)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");
			
			switch(listitem)
			{
				case 1: character_info[playerid][duty_skin] = 59;
				case 2: character_info[playerid][duty_skin] = 72;
				case 3: character_info[playerid][duty_skin] = 96;
				case 4: character_info[playerid][duty_skin] = 101;
				case 5: character_info[playerid][duty_skin] = 163;
				case 6: character_info[playerid][duty_skin] = 164;
				case 7: character_info[playerid][duty_skin] = 240;
				case 8: character_info[playerid][duty_skin] = 250;
				case 9: character_info[playerid][duty_skin] = 295;
				case 10: character_info[playerid][duty_skin] = 296;
				default: character_info[playerid][duty_skin] = character_info[playerid][skin];
				
			}
			if(IsDuty(playerid)) SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			UpdatePlayerColor(playerid);
		}
		case 155:
		{
			if(!response) 
				return 1;
			if(!IsDuty(playerid)) 
				return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы должны быть на дежурстве!");

			switch(listitem)
			{
				case 1: character_info[playerid][duty_skin] = 40;
				case 2: character_info[playerid][duty_skin] = 76;
				case 3: character_info[playerid][duty_skin] = 141;
				case 4: character_info[playerid][duty_skin] = 148;
				case 5: character_info[playerid][duty_skin] = 150;
				case 6: character_info[playerid][duty_skin] = 192;
				case 7: character_info[playerid][duty_skin] = 211;
				case 8: character_info[playerid][duty_skin] = 219;
				case 9: character_info[playerid][duty_skin] = 233;
				case 10: character_info[playerid][duty_skin] = 263;
				default: character_info[playerid][duty_skin] = character_info[playerid][skin];
			}
			if(IsDuty(playerid)) SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
			UpdatePlayerColor(playerid);
		}
		case 156:
		{
			if(!response)
			{
				new f_str[60];
				format(f_str, sizeof(f_str), "%s отказался от покупки лицензии.", sendername(out_id));
				SCM(out_id_i, COLOR_MSGSERVER, f_str);
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы отказались от покупки!");
			}
			else
			{
			    new f_str[60];
				character_info[out_id][gunLic] = 1;
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы купили лицензию на оружие!");
				takemoney(playerid, out_price, "giveweaponlc");
				format(f_str, sizeof(f_str), "%s купил у вас лицензию.", sendername(playerid));
				SCM(out_id_i, COLOR_MSGSERVER, f_str);
			}
			return true;
		}
	}
	return 1; // :END_DIALOGS
}

public OnGameModeInit()
{

	// таксофоны
	CreateDynamicObject(1216, 1921.049194, -1765.919555, 13.196882, 0.000000, 0.000000, 179.500076, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2423.058105, -1749.095581, 13.216875, 0.000000, 0.000000, -90.899955, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2423.049316, -1749.666137, 13.216875, 0.000000, 0.000000, -90.899955, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2423.039550, -1750.226684, 13.216875, 0.000000, 0.000000, -90.899955, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2760.098144, -1984.154174, 13.170480, 0.000000, 0.000000, 91.899955, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2760.079345, -1983.573730, 13.170480, 0.000000, 0.000000, 91.899955, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2404.333496, -2026.497802, 13.178833, 0.000000, 0.000000, 87.500106, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2404.359375, -2025.928100, 13.178833, 0.000000, 0.000000, 87.500106, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2103.007812, -1437.296997, 23.660015, 0.000000, 0.000000, 91.100044, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2102.993652, -1436.716430, 23.660015, 0.000000, 0.000000, 91.100044, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2102.981445, -1436.145874, 23.660015, 0.000000, 0.000000, 91.100044, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2361.377929, -1370.577636, 23.632286, 0.000000, 0.000000, 88.100013, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2361.396240, -1370.007080, 23.632286, 0.000000, 0.000000, 88.100013, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2361.412353, -1369.436889, 23.632286, 0.000000, 0.000000, 88.100013, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2493.295654, -1494.975341, 23.660009, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2493.866210, -1494.975341, 23.660009, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2494.436767, -1494.975341, 23.660009, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2154.105957, -1022.304870, 62.346069, 0.000000, 0.000000, 88.800010, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2154.119873, -1021.734497, 62.346069, 0.000000, 0.000000, 88.800010, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2154.133544, -1021.164367, 62.346069, 0.000000, 0.000000, 88.800010, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2001.048095, -1270.668945, 23.590320, 0.000000, 0.000000, 179.399963, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2000.477539, -1270.662109, 23.590320, 0.000000, 0.000000, 179.399963, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1999.906982, -1270.655151, 23.590320, 0.000000, 0.000000, 179.399963, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1609.671020, -1151.182617, 23.689590, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1610.229003, -1151.182617, 23.689590, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1610.799560, -1151.182617, 23.689590, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1074.782470, -1134.782470, 23.446256, 0.000000, 0.000000, -147.200057, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1075.270996, -1134.468627, 23.446256, 0.000000, 0.000000, -140.999847, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1075.714355, -1134.109375, 23.446256, 0.000000, 0.000000, -137.899765, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1015.299987, -1303.381958, 13.162815, 0.000000, 0.000000, -90.199951, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1015.302490, -1302.821411, 13.162815, 0.000000, 0.000000, -90.199951, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1015.305297, -1302.250854, 13.162815, 0.000000, 0.000000, -90.199951, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 541.584106, -1261.094482, 16.378831, 0.000000, 0.000000, 37.099994, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 542.038757, -1260.751342, 16.378831, 0.000000, 0.000000, 37.099994, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 542.493469, -1260.408325, 16.378831, 0.000000, 0.000000, 37.099994, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1068.343872, -1836.534667, 13.203355, 0.000000, 0.000000, -67.600044, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1068.560791, -1837.061523, 13.203355, 0.000000, 0.000000, -67.600044, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1068.777343, -1837.587768, 13.203355, 0.000000, 0.000000, -67.600044, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1538.752197, -1706.185668, 13.166886, 0.000000, 0.000000, -89.899993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1538.752075, -1705.615112, 13.166886, 0.000000, 0.000000, -89.899993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1538.752075, -1705.044555, 13.166886, 0.000000, 0.000000, -89.899993, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2290.668212, -2066.012207, 13.135283, 0.000000, 0.000000, -134.499847, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2290.255859, -2066.431152, 13.135283, 0.000000, 0.000000, -134.499847, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 2289.843261, -2066.849121, 13.135283, 0.000000, 0.000000, -134.499847, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1003.088623, -953.340698, 41.673377, 0.000000, 0.000000, -174.099853, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1002.521545, -953.399841, 41.673377, 0.000000, 0.000000, -174.099853, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1216, 1001.954467, -953.458984, 41.673377, 0.000000, 0.000000, -174.099853, -1, -1, -1, 300.00, 300.00);


	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, 1000);
	/*new v;
	v = AddStaticVehicle(596,2166.0613,-1256.5570,23.6131,163.6247,0,1); // copcar
	//SetVehicleVirtualWorld(v, -1);
	v = AddStaticVehicle(402,2173.3105,-1274.6027,23.7301,358.3811,1,1); // buffalo
	//SetVehicleVirtualWorld(v, -1);
	
	
	chat - UseAnim(playerid,"PED","IDLE_CHAT",4.0,1,0,0,1,1);
	crossarms - UseAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	
	*/
	ChangeColor[0] = TextDrawCreate(17.0, 138.0, "box");
    TextDrawLetterSize(ChangeColor[0], 0.0, 17.0);
    TextDrawTextSize(ChangeColor[0], 171.0, 0.0);TextDrawAlignment(ChangeColor[0], 1);
    TextDrawColor(ChangeColor[0], -1);TextDrawUseBox(ChangeColor[0], 1);
    TextDrawBoxColor(ChangeColor[0], 102);TextDrawSetOutline(ChangeColor[0], 0);
    TextDrawBackgroundColor(ChangeColor[0], 255);TextDrawFont(ChangeColor[0], 1);
    TextDrawSetProportional(ChangeColor[0], 1);TextDrawSetShadow(ChangeColor[0], 0);

    ChangeColor[1] = TextDrawCreate(138.667617, 298.116699, "Close");
    TextDrawLetterSize(ChangeColor[1], 0.400000, 1.600000);
    TextDrawTextSize(ChangeColor[1], 17.0, 62.327926);TextDrawAlignment(ChangeColor[1], 2);
    TextDrawColor(ChangeColor[1], -1);TextDrawUseBox(ChangeColor[1], 1);
    TextDrawBoxColor(ChangeColor[1], 102);TextDrawSetOutline(ChangeColor[1], 0);
    TextDrawBackgroundColor(ChangeColor[1], 255);TextDrawFont(ChangeColor[1], 2);
    TextDrawSetProportional(ChangeColor[1], 1);TextDrawSetShadow(ChangeColor[1], 0);
    TextDrawSetSelectable(ChangeColor[1], 1);

    new Float:X=19.0,Float:Y=139.0,countz = 1;
    for(new i=2; i < sizeof(ChangeColor); i++)
    {
        ChangeColor[i] = TextDrawCreate(X, Y, "box");
        TextDrawBackgroundColor(ChangeColor[i], AllCarColors[ColorsAvailable[i-2]]);
        TextDrawLetterSize(ChangeColor[i], 0.0, 18.0);TextDrawTextSize(ChangeColor[i], 18.0, 18.0);
        TextDrawAlignment(ChangeColor[i], 1);TextDrawColor(ChangeColor[i], -1);
        TextDrawUseBox(ChangeColor[i], 1);TextDrawBoxColor(ChangeColor[i], 0);
        TextDrawSetOutline(ChangeColor[i], 0);TextDrawFont(ChangeColor[i], 5);
        TextDrawSetProportional(ChangeColor[i], 1);TextDrawSetShadow(ChangeColor[i], 1);
        TextDrawSetPreviewModel(ChangeColor[i], 19349);
        TextDrawSetPreviewRot(ChangeColor[i], -16.0, 0.0, -180.0, 0.7);
        TextDrawSetSelectable(ChangeColor[i], 1);

        X+=19.0;
        countz++;
        if(countz == 9)
        {
            Y+=19.0;
            X = 19.0;
            countz = 1;
        }
    }
	

	
	restartingtd[0] = TextDrawCreate(1.000175, 1.259251, "box");
	TextDrawLetterSize(restartingtd[0], 0.000000, 1.000003);
	TextDrawTextSize(restartingtd[0], 640.000000, 0.000000);
	TextDrawAlignment(restartingtd[0], 1);
	TextDrawColor(restartingtd[0], -1);
	TextDrawUseBox(restartingtd[0], 1);
	TextDrawBoxColor(restartingtd[0], -1523963292);
	TextDrawSetShadow(restartingtd[0], 0);
	TextDrawSetOutline(restartingtd[0], 0);
	TextDrawBackgroundColor(restartingtd[0], 255);
	TextDrawFont(restartingtd[0], 1);
	TextDrawSetProportional(restartingtd[0], 1);
	TextDrawSetShadow(restartingtd[0], 0);

	restartingtd[1] = TextDrawCreate(319.999969, 2.088916, "RESTARTING_IN_60_SECONDS");
	TextDrawLetterSize(restartingtd[1], 0.150000, 0.800000);
	TextDrawAlignment(restartingtd[1], 2);
	TextDrawColor(restartingtd[1], -1);
	TextDrawSetShadow(restartingtd[1], 0);
	TextDrawSetOutline(restartingtd[1], 0);
	TextDrawBackgroundColor(restartingtd[1], 255);
	TextDrawFont(restartingtd[1], 2);
	TextDrawSetProportional(restartingtd[1], 1);
	TextDrawSetShadow(restartingtd[1], 0);

	/*textdraw_loc = TextDrawCreate(592.000000, 4.000000, "classic-rp.com");
	TextDrawAlignment(textdraw_loc, 2);
	TextDrawBackgroundColor(textdraw_loc, 255);
	TextDrawFont(textdraw_loc, 1);
	TextDrawLetterSize(textdraw_loc, 0.300000, 1.400000);
	TextDrawColor(textdraw_loc, -1);
	TextDrawSetOutline(textdraw_loc, 1);
	TextDrawSetProportional(textdraw_loc, 1);*/

	Logo[0] = TextDrawCreate(537.904907, 4.693341, "classic-rp.com");
	TextDrawLetterSize(Logo[0], 0.229047, 1.096533);
	TextDrawAlignment(Logo[0], 1);
	TextDrawColor(Logo[0], -1);
	TextDrawSetShadow(Logo[0], 0);
	TextDrawSetOutline(Logo[0], 255);
	TextDrawBackgroundColor(Logo[0], 255);
	TextDrawFont(Logo[0], 2);
	TextDrawSetProportional(Logo[0], 1);

	Logo[1] = TextDrawCreate(584.000000, 15.000013, "2017 year");
	TextDrawLetterSize(Logo[1], 0.180500, 0.769333);
	TextDrawAlignment(Logo[1], 1);
	TextDrawColor(Logo[1], -1);
	TextDrawSetShadow(Logo[1], 0);
	TextDrawSetOutline(Logo[1], 0);
	TextDrawBackgroundColor(Logo[1], 51);
	TextDrawFont(Logo[1], 2);
	TextDrawSetProportional(Logo[1], 1);
	

	
	for(new i; i<MAX_ACHAT; i++)
	{
		ACHAT[i] = TextDrawCreate(404.571380, 422.399932, "-1:-1");
		TextDrawLetterSize(ACHAT[i], 0.284285, 1.194666);
		TextDrawAlignment(ACHAT[i], 1);
		TextDrawColor(ACHAT[i], -1);
		TextDrawSetShadow(ACHAT[i], 0);
		TextDrawSetOutline(ACHAT[i], 1);
		TextDrawBackgroundColor(ACHAT[i], 51);
		TextDrawFont(ACHAT[i], 2);
		TextDrawSetProportional(ACHAT[i], 1);
		achat_info[i][Playerid] = -1;
		achat_info[i][Code] = -1;
	}
	
	Streamer_VisibleItems(STREAMER_TYPE_OBJECT, OBJECTS_STREAM_SETTINGS);
	Streamer_SetCellDistance(250.0);	
		
	new a;	
	a = CreateActor(106, 2173.8826,-1281.7078,23.9766,176.6924); // groove skin
	ApplyActorAnimation(a, "PED","IDLE_CHAT",4.0,1,0,0,1,1); 
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(281, 2173.7969,-1283.2126,23.9766,356.6924); // cop
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 1, 1, 1, -1);
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 1, 1, 1, -1);
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(24, 2160.1995,-1258.7111,23.9902,179.4679); // lean 1 gangster
	ApplyActorAnimation(a, "GANGS","leanIDLE",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(5, 2159.1392,-1259.7540,23.9902,304.6573); // gangster 2
	SetActorVirtualWorld(a, -1);
	
	// el corona
	
	a = CreateActor(116, 1892.109252,-2029.423217,13.546875,82.883934); // 0 gsign
	ApplyActorAnimation(a, "GHANDS","gsign2LH",10.0,1,0,0,1,1); 
	ApplyActorAnimation(a, "GHANDS","gsign2LH",10.0,1,0,0,1,1); 
	ApplyActorAnimation(a, "GHANDS","gsign2LH",10.0,1,0,0,1,1); 
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(4, 1877.074462,-2030.649658,13.539081,268.233947); // 1 (nigger)
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(114, 1894.977416,-2036.307983,13.546875,72.468948); // 2
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(110, 1894.551757,-2025.945434,13.546875,92.354103); // 3
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(48, 1893.309204,-2030.708740,13.546875,86.552055); // 4 gign
	ApplyActorAnimation(a, "GHANDS","gsign3",10.0,1,0,0,1,1); 
	ApplyActorAnimation(a, "GHANDS","gsign3",10.0,1,0,0,1,1); 
	ApplyActorAnimation(a, "GHANDS","gsign3",10.0,1,0,0,1,1); 
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(23, 1893.844116,-2025.938354,13.546875,270.497497); // 5
	ApplyActorAnimation(a, "PED","IDLE_CHAT",4.0,1,0,0,1,1);
	ApplyActorAnimation(a, "PED","IDLE_CHAT",4.0,1,0,0,1,1);
	ApplyActorAnimation(a, "PED","IDLE_CHAT",4.0,1,0,0,1,1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(115, 1895.573364,-2028.698486,13.546875,183.831298); // 6
	ApplyActorAnimation(a, "GANGS","leanIDLE",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "GANGS","leanIDLE",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "GANGS","leanIDLE",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(152, 1910.738403,-2033.571044,13.546875,359.705261); // 7
	SetActorVirtualWorld(a, -1);
	
	// ----------------------
	
	// --------------- bar
	a = CreateActor(11, 1215.151489, -15.262866, 1000.921875, 2.709205);// 0
	ApplyActorAnimation(a, "BAR","Barserve_bottle",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "BAR","Barserve_bottle",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "BAR","Barserve_bottle",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(29, 1215.155151, -13.352720, 1000.921875, 177.339797);// 1
	ApplyActorAnimation(a, "CAR_CHAT","car_talkm_loop",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "CAR_CHAT","car_talkm_loop",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "CAR_CHAT","car_talkm_loop",4.0,1,0,1,1,0);
	
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(46, 1210.660888, -7.275247, 1000.921875, 98.378883);// 2
	ApplyActorAnimation(a, "STRIP","PUN_CASH",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "STRIP","PUN_CASH",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "STRIP","PUN_CASH",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(59, 1210.457641, -6.193979, 1000.921875, 119.811088);// 3
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(63, 1208.479492, -6.624103, 1001.328125, 272.421905);// 4
	ApplyActorAnimation(a, "DANCING","dnce_M_a",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "DANCING","dnce_M_a",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "DANCING","dnce_M_a",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(64, 1216.180175, -6.477980, 1001.328125, 96.490287);// 5
	ApplyActorAnimation(a, "DANCING","DAN_Up_A",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(67, 1212.540039, -6.636723, 1000.921875, 279.768646);// 6
	ApplyActorAnimation(a, "DANCING","DAN_Loop_A",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "DANCING","DAN_Loop_A",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "DANCING","DAN_Loop_A",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(72, 1212.714965, -7.315714, 1000.921875, 279.768646);// 7
	ApplyActorAnimation(a, "STRIP","PUN_CASH",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "STRIP","PUN_CASH",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "STRIP","PUN_CASH",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(98, 1212.816528, -8.008468, 1000.921875, 286.912750);// 8
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(164, 1206.077270, -13.495964, 1000.921875, 3.511678);// 9
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(170, 1202.168334, -5.474297, 1000.921875, 272.730255);// 10
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// sit
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(217, 1203.850708, -4.823649, 1000.921875, 136.029693);// 11
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// sit
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(223, 1202.184204, -2.876317, 1000.921875, 272.119720);// 12
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// /sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// /sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);// /sit
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(237, 1202.372192, -2.041013, 1000.921875, 150.024230);// 13
	ApplyActorAnimation(a, "INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
	ApplyActorAnimation(a, "INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
	ApplyActorAnimation(a, "INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(128, 1209.460083, -12.983877, 1000.921875, 343.161010);// 14
	ApplyActorAnimation(a, "CRACK","crckdeth2",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "CRACK","crckdeth2",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "CRACK","crckdeth2",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(166, 1208.812988, -12.160014, 1000.921875, 207.717391);// 15
	ApplyActorAnimation(a, "FAT","IDLE_tired",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "FAT","IDLE_tired",4.0,1,0,1,1,0);
	ApplyActorAnimation(a, "FAT","IDLE_tired",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	//-------------
		//-----------beach
	a = CreateActor(45, 233.008056, -1880.082885, 1.646674, 182.173660);// 0
	// lay 1
	ApplyActorAnimation(a, "BEACH", "bather",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(97, 202.621414, -1873.350585, 3.708220, 259.959716);// 1
	// looksky
	ApplyActorAnimation(a, "ON_LOOKERS","lkup_loop",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(18, 224.044158, -1879.303955, 1.797980, 178.178970);// 2
	// lay 4
	ApplyActorAnimation(a, "BEACH","SitnWait_loop_W",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(138, 223.108062, -1879.488159, 1.793363, 213.335235);// 3
	// lay 3
	ApplyActorAnimation(a, "BEACH","ParkSit_W_loop",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(139, 225.591934, -1870.236328, 3.025932, 195.016738);// 4
	// lay 2
	ApplyActorAnimation(a, "SUNBATHE","Lay_Bac_in",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(140, 228.013687, -1870.598510, 2.989552, 195.768798);// 5
	// lay 1
	ApplyActorAnimation(a, "BEACH", "bather",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(90, 230.113311, -1870.676757, 2.960752, 189.188720);// 6
	// lay 4
	ApplyActorAnimation(a, "BEACH","SitnWait_loop_W",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(190, 231.956466, -1871.352661, 2.358967, 110.468887);// 7
	// sit
	ApplyActorAnimation(a, "PED","SEAT_down",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(88, 224.184158, -1866.308227, 2.850230, 60.044082);// 8
	// lean 1
	ApplyActorAnimation(a, "GANGS","leanIDLE",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(146, 223.678802, -1871.764160, 2.413392, 10.682127);// 9
	// seat
	ApplyActorAnimation(a, "INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(154, 221.110000, -1869.802612, 3.112282, 190.682205);// 10
	// gro
	ApplyActorAnimation(a, "BEACH", "ParkSit_M_loop",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(251, 213.714935, -1875.595092, 2.212593, 289.125305);// 11
	// lean 1
	ApplyActorAnimation(a, "GANGS","leanIDLE",4.0,0,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(252, 214.853454, -1889.979980, 0.939083, 235.867950);// 12
	// bomb while
	ApplyActorAnimation(a, "BOMBER","BOM_Plant",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(210, 235.547210, -1843.475463, 3.417598, 197.486251);// 13
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(214, 236.594253, -1846.467407, 3.337354, 22.644641);// 14
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(145, 237.260803, -1847.647827, 3.305201, 29.600601);// 15
	// crossarms
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(129, 236.845169, -1849.156250, 3.266589, 353.128295);// 16
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(108, 214.727325, -1836.278564, 3.711639, 105.365287);// 17
	// lose (while)
	ApplyActorAnimation(a, "OTB","wtchrace_lose",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(90, 203.650604, -1840.191894, 3.652003, 288.291046);// 18
	// win (while)
	ApplyActorAnimation(a, "OTB","wtchrace_win",4.0,1,0,1,1,0);
	SetActorVirtualWorld(a, -1);

	//----------------
	//------------rap
	a = CreateActor(180, 2377.417236, -1475.314819, 23.828344, 92.700988);// 0
	SetActorVirtualWorld(a, -1);
	a = CreateActor(107, 2375.379394, -1475.468383, 23.836055, 273.317810);// 1
	ApplyActorAnimation(a, "RAPPING","RAP_C_Loop", 4.0, 1, 1, 1, 1, -1);
	ApplyActorAnimation(a, "RAPPING","RAP_C_Loop", 4.0, 1, 1, 1, 1, -1);
	ApplyActorAnimation(a, "RAPPING","RAP_C_Loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(106, 2379.250976, -1475.227416, 23.822967, 88.676757);// 2
	ApplyActorAnimation(a, "OTB","wtchrace_win", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(56, 2378.955566, -1474.399291, 23.818626, 126.089111);// 3
	ApplyActorAnimation(a, "OTB","wtchrace_lose", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(101, 2375.690917, -1477.789794, 23.928295, 341.064025);// 4
	ApplyActorAnimation(a, "OTB","wtchrace_win", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(90, 2378.414794, -1473.948730, 23.837013, 134.549194);// 5
	ApplyActorAnimation(a, "OTB","wtchrace_lose", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(108, 2373.607421, -1476.852294, 23.890033, 302.210357);// 6
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(105, 2373.004150, -1474.406250, 23.818342, 248.943206);// 7
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(198, 2373.989501, -1472.819335, 23.883106, 205.076110);// 8
	SetActorVirtualWorld(a, -1);
	a = CreateActor(109, 2376.225830, -1472.853637, 23.881706, 183.053588);// 9
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(102, 2378.250732, -1477.428833, 23.913562, 33.051563);// 10
	ApplyActorAnimation(a, "ON_LOOKERS","shout_in", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(103, 2377.061279, -1477.879882, 23.931972, 10.867341);// 11
	ApplyActorAnimation(a, "OTB","wtchrace_win", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(13, 2374.550048, -1477.492187, 23.916149, 336.063629);// 12
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(42, 2375.046386, -1472.519042, 23.895362, 196.566329);// 13
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 5.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(47, 2377.257324, -1473.183349, 23.868249, 156.897994);// 14
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(211, 2373.280273, -1475.672607, 23.845418, 289.700439);// 15
	ApplyActorAnimation(a, "OTB","wtchrace_win", 5.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(26, 2373.504638, -1473.383666, 23.860074, 232.986572);// 16
	ApplyActorAnimation(a, "ON_LOOKERS","shout_in", 8.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(60, 2379.092285, -1476.420654, 23.872419, 67.056602);// 17
	ApplyActorAnimation(a, "OTB","wtchrace_lose", 5.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(28, 2379.857910, -1475.975097, 23.854234, 70.388351);// 18
	ApplyActorAnimation(a, "OTB","wtchrace_win", 1.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(73, 2379.968994, -1474.334106, 23.821285, 114.550537);// 19
	ApplyActorAnimation(a, "STRIP","PUN_CASH", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(110, 2380.065429, -1475.027709, 23.815628, 97.254379);// 20
	ApplyActorAnimation(a, "GHANDS","gsign1LH", 8.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(48, 2372.372070, -1475.082641, 23.828592, 278.106842);// 21
	ApplyActorAnimation(a, "GHANDS","gsign1LH", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(60, 2375.813720, -1472.047973, 23.914587, 167.812484);// 22
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(124, 2379.497070, -1477.617187, 23.921251, 51.758010);// 23
	ApplyActorAnimation(a, "ON_LOOKERS","shout_in", 9.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(69, 2372.849121, -1476.218017, 23.862836, 287.193603);// 24
	ApplyActorAnimation(a, "GHANDS","gsign1LH", 5.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(142, 2376.405761, -1478.730102, 23.966670, 346.709411);// 25
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER", 7.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(102, 2378.138916, -1473.033691, 23.874359, 147.132308);// 26
	ApplyActorAnimation(a, "OTB","wtchrace_win", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(151, 2374.147216, -1472.034667, 23.915130, 206.972137);// 27
	ApplyActorAnimation(a, "GHANDS","gsign1LH", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(170, 2372.461669, -1473.625854, 23.850191, 249.648590);// 28
	ApplyActorAnimation(a, "DANCING","DAN_Loop_A", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(174, 2371.550781, -1476.010009, 23.858337, 286.496887);// 29
	ApplyActorAnimation(a, "DANCING","DAN_Loop_A", 5.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(176, 2371.824951, -1474.347900, 23.820724, 262.620697);// 30
	ApplyActorAnimation(a, "OTB","wtchrace_win", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(25, 2373.765380, -1477.774902, 23.927686, 324.793945);// 31
	ApplyActorAnimation(a, "ON_LOOKERS","shout_in", 3.5, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(22, 2372.234375, -1477.145507, 23.902000, 304.113830);// 32
	ApplyActorAnimation(a, "STRIP","PUN_CASH", 5.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(19, 2372.890625, -1472.425903, 23.899162, 224.213134);// 33
	ApplyActorAnimation(a, "OTB","wtchrace_lose", 7.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(190, 2368.307617, -1470.458251, 23.975639, 182.396865);// 34
	ApplyActorAnimation(a, "GANGS","leanIDLE", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(18, 2368.334472, -1470.649658, 23.928594, 353.242218);// 35
	ApplyActorAnimation(a, "PED","gang_gunstand", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(247, 2378.364013, -1478.539550, 23.958892, 34.041263);// 36
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER", 3.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(79, 2358.378417, -1470.160522, 23.987571, 180.151962);// 37
	ApplyActorAnimation(a, "CRACK","crckdeth2", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(250, 2380.150146, -1476.854614, 23.890129, 71.328262);// 38
	ApplyActorAnimation(a, "STRIP","PUN_HOLLER", 2.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(271, 2382.675048, -1479.295532, 23.989746, 83.627723);// 39
	ApplyActorAnimation(a, "MISC","Plyrlean_loop", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(270, 2382.158203, -1470.818359, 23.964769, 89.215019);// 40
	ApplyActorAnimation(a, "STRIP","PUN_CASH", 8.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(269, 2381.212402, -1470.897949, 23.961521, 273.298156);// 41
	ApplyActorAnimation(a, "PED","IDLE_CHAT", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(293, 2368.278076, -1479.138061, 23.983320, 8.156682);// 42
	ApplyActorAnimation(a, "CRACK","crckidle1", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(298, 2367.456542, -1478.365722, 23.951799, 231.961120);// 43
	ApplyActorAnimation(a, "FAT","IDLE_tired", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(299, 2364.766845, -1470.857788, 23.959625, 2.011588);// 44
	ApplyActorAnimation(a, "FOOD", "EAT_Vomit_P", 4.0, 1, 1, 1, 1, -1);
	ApplyActorAnimation(a, "FOOD", "EAT_Vomit_P", 4.0, 1, 1, 1, 1, -1);
	ApplyActorAnimation(a, "FOOD", "EAT_Vomit_P", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	a = CreateActor(297, 2361.428466, -1478.575927, 23.960378, 145.809616);// 45
	ApplyActorAnimation(a, "PAULNMAC","Piss_in", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);

	//---------------
	// basket
	a = CreateActor(105, 2533.389404, -1667.632446, 15.165104, 288.799774);// 0
	// basket 6
	ApplyActorAnimation(a, "BSKTBALL","BBALL_Dnk", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(67, 2532.180664, -1666.065307, 15.167704, 225.766723);// 1
	// basket 5
	ApplyActorAnimation(a, "BSKTBALL","BBALL_def_loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(48, 2522.569335, -1667.165161, 15.038581, 258.320465);// 2
	// crossarms
	ApplyActorAnimation(a, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(103, 2523.869628, -1662.852905, 15.493547, 191.315750);// 3
	// gro
	ApplyActorAnimation(a, "BEACH", "ParkSit_M_loop", 4.0, 0, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(65, 2525.014648, -1663.817016, 15.147157, 241.888183);// 4
	// lean 2
	ApplyActorAnimation(a, "MISC","Plyrlean_loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(176, 2522.663330, -1665.430541, 15.094547, 93.930786);// 5
	// fail
	ApplyActorAnimation(a, "CASINO","Slot_lose_out", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	
	a = CreateActor(297, 2533.938964, -1665.940917, 15.163441, 152.563980);// 6
	// basket 5
	ApplyActorAnimation(a, "BSKTBALL","BBALL_def_loop", 4.0, 1, 1, 1, 1, -1);
	SetActorVirtualWorld(a, -1);
	//--------------
	
	new v = AddStaticVehicle(596,2166.0613,-1256.5570,23.6131,163.6247,0,1); //copcar
	SetVehicleVirtualWorld(v, -1);
	
	v = AddStaticVehicle(467,1887.7798,-2037.9078,13.1742,359.6706,1,12);
	SetVehicleVirtualWorld(v, -1);
	
	ManualVehicleEngineAndLights();
	ASP = CreatePickup(1239, 22, -2033.4318,-117.4664,1035.1719, 6);
	CSP = CreatePickup(1239, 22, 536.8356, -1293.9266, 17.2422, 0);

	CreateDynamic3DTextLabel("Автосалон\n{FFFFFF}Введите /buycar чтобы воспользоваться.", COLOR_INFO, 536.8356, -1293.9266, 17.2422, 15.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, 0, -1, -1, 15.0);
	//printf("[debug_3d] create /buycar");		
	
	for(new i; i<sizeof(FixPickup); i++)
	{
		CreatePickup(1239, 22, FixPickup[i][posX], FixPickup[i][posY], FixPickup[i][posZ], FixPickup[i][VW]);
		CreateDynamic3DTextLabel("{AFAFAF}Pay 'n Spray\n{FFFFFF}Цена: $150\nВведите /carfix чтобы воспользоваться.", COLOR_INFO, FixPickup[i][posX], FixPickup[i][posY], FixPickup[i][posZ], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, FixPickup[i][VW]);
	}

	CreatePickup(1239, 22, 1154.7264,-1440.3060,15.7969, 0);
	CreateDynamic3DTextLabel("Дубликат ключей\n{FFFFFF}Введите /buy чтобы воспользоваться.", COLOR_INFO, 1154.7264,-1440.3060,15.7969, 15.0);
	
	
	//printf("[debug_3d] create /buy");
	for(new i; i<sizeof(FactionDutyPickup); i++)
	{
		CreatePickup(1239, 23, FactionDutyPickup[i][posX],FactionDutyPickup[i][posY],FactionDutyPickup[i][posZ], FactionDutyPickup[i][VW]);
		CreateDynamic3DTextLabel("Раздевалка\n{FFFFFF}Введите /duty чтобы воспользоваться.", COLOR_INFO, FactionDutyPickup[i][posX],FactionDutyPickup[i][posY],FactionDutyPickup[i][posZ], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, FactionDutyPickup[i][VW], FactionDutyPickup[i][Interior], -1, 5.5);
	}

	for(new i; i<MAX_AD; i++) ads_info[i][owner] = -1;
	/*EnableAntiCheat(16, false);
	//EnableAntiCheat(52, false);
	EnableAntiCheat(27, false);
	EnableAntiCheat(17, false);
	EnableAntiCheat(34, false);
	EnableAntiCheat(38, false);
	EnableAntiCheat(49, false);*/
	
	gettime(hour, minute, second);
    getdate(year, month, day);
	/*for(new i; i<sizeof(area_city); i++)
	{
		area_city[i][aId] = CreateDynamicCube(area_city[i][aPos][0], area_city[i][aPos][1], area_city[i][aPos][2], area_city[i][aPos][3], area_city[i][aPos][4], area_city[i][aPos][5]);  
	}*/
	
    buy_skin_menu = CreateMenu("Buy Skin", 1, 20.0, 175.0, 150.0, 150.0);
	
	AddMenuItem(buy_skin_menu, 0, ">>>");
	AddMenuItem(buy_skin_menu, 0, "<<<");
	AddMenuItem(buy_skin_menu, 0, "buy");
	AddMenuItem(buy_skin_menu, 0, "cancel");
    
	SetTimer("SecondTimerServer",1000,true);
 	reg_mysql_connect();
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
	ShowPlayerMarkers(0);
	UpdateGameModeText();
	SendRconCommand("weburl "SERVER_URL);
    SetNameTagDrawDistance(20.0);
    SetWorldTime(hour+3);

	//EnableAntiCheat(49, false);
	EnableAntiCheat(52, false);
	EnableAntiCheat(5, false);

	
	for(new i; i<sizeof(ArrestZone); i++) 
	{
		//printf("[debug_3d] create arrest zone");
		CreateDynamic3DTextLabel("Камеры\n{ffffff}Введите /arrest чтобы воспользоваться.", COLOR_INFO, ArrestZone[i][posX],ArrestZone[i][posY],ArrestZone[i][posZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, ArrestZone[i][VW], ArrestZone[i][Interior]);
	}
    for(new i; i<MAX_FURNITURE; i++)
	{
	    furniture[i][id] = -1;
	    furniture[i][houseid] = -1;
	    furniture[i][model] = -1;
    }
 	
	//mysql_function_query(dbHandle, "SELECT * FROM arecord WHERE characterid=20", true, "OnLoadArecords", "i", 0);
	
	mysql_function_query(dbHandle, "UPDATE `users` SET `online`=0 WHERE online=1", false, "", "");	
	mysql_function_query(dbHandle, "SELECT * FROM `graff` WHERE 1", true, "OnLoadGraff", "");
	mysql_function_query(dbHandle, "SELECT * FROM `cars` WHERE owner<0", true, "OnLoadCars", "d", -1);
	mysql_function_query(dbHandle, "SELECT * FROM `property` WHERE 1", true, "load_property", "d", true);
	
	mysql_function_query(dbHandle, "SELECT * FROM `propinv`", true, "load_propinv", "d", true);
	
	mysql_function_query(dbHandle, "SELECT * FROM `atm`", true, "OnLoadATM", "");
	mysql_function_query(dbHandle, "SELECT * FROM `cctv`", true, "OnLoadCCTV", "");
	mysql_function_query(dbHandle, "SELECT * FROM `elevators`", true, "OnLoadElevators", "");
	mysql_function_query(dbHandle, "SELECT * FROM  `radio_stations` ", true, "OnLoadRadioStations", "");
	LoadEnters();
	UpdateServerInt();
	LoadFactions();
    LoadDoors();
	CreateGate();
	LoadPayphones();
	new itemcount[sizeof(Shop)];
	for(new i = 0; i < sizeof(Shop); i++)
	{
		if(Shop[i][id])
		{	
			ShopSize[Shop[i][id]-1]++;
			
			ShopList[ Shop[i][id]-1 ][ itemcount[Shop[i][id]-1]++ ] = i;			
		}
	}
	return 1;
}

public OnGameModeExit()
{
	print("GAME MODE RESTARTED");
	return 1;
}

public OnPlayerConnect(playerid)
{	
	if(restart < 0) {
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} На сервере происходит рестарт!");
		KickEx(playerid);
	}
	AuthorizeCamera(playerid);
	LogIn[playerid] = 1;
	for(new i; i<5; i++)
	{
		DrugEffect[playerid][i] = CreatePlayerTextDraw(playerid, 0.000000, 0.000000+(96.0*i), "_");
		PlayerTextDrawBackgroundColor(playerid, DrugEffect[playerid][i], 255);
		PlayerTextDrawFont(playerid, DrugEffect[playerid][i], 1);
		PlayerTextDrawLetterSize(playerid, DrugEffect[playerid][i], 0.00000, 10.16);
		PlayerTextDrawColor(playerid, DrugEffect[playerid][i], -1);
		PlayerTextDrawSetOutline(playerid, DrugEffect[playerid][i], 0);
		PlayerTextDrawSetProportional(playerid, DrugEffect[playerid][i], 1);
		PlayerTextDrawSetShadow(playerid, DrugEffect[playerid][i], 1);
		PlayerTextDrawUseBox(playerid, DrugEffect[playerid][i], 1);
		PlayerTextDrawBoxColor(playerid, DrugEffect[playerid][i], 255);
		PlayerTextDrawTextSize(playerid, DrugEffect[playerid][i],640.0,0.0);
	}
	
	
	FullMonitor[playerid] = CreatePlayerTextDraw(playerid, 0.000000, 0.000000, "_");
	PlayerTextDrawBackgroundColor(playerid, FullMonitor[playerid], 255);
	PlayerTextDrawFont(playerid, FullMonitor[playerid], 1);
	PlayerTextDrawLetterSize(playerid, FullMonitor[playerid], 0.500000, 49.799957);
	PlayerTextDrawColor(playerid, FullMonitor[playerid], -1);
	PlayerTextDrawSetOutline(playerid, FullMonitor[playerid], 0);
	PlayerTextDrawSetProportional(playerid, FullMonitor[playerid], 1);
	PlayerTextDrawSetShadow(playerid, FullMonitor[playerid], 1);
	PlayerTextDrawUseBox(playerid, FullMonitor[playerid], 1);
	PlayerTextDrawBoxColor(playerid, FullMonitor[playerid], 255);
	PlayerTextDrawTextSize(playerid, FullMonitor[playerid],640.000000,0.000000);
	PlayerTextDrawHide(playerid, FullMonitor[playerid]);
	
	if(restart <= 0) 
		Kick(playerid); 
	
	if(AuthTimeoutTimer[playerid] > 0) 
		KillTimer(AuthTimeoutTimer[playerid]);
	
	AuthTimeoutTimer[playerid] = SetTimerEx("AuthTimeout", 60000*4, false, "i", playerid);
	
	new qu[256];
	PlayerDataUpdate(playerid);
 	UpdatePlayerColor(playerid);
	
	//format(qu, sizeof(qu), "SELECT `id` FROM `users` WHERE `login`='%s' LIMIT 1", sendername(playerid));
	SetPlayerHealth(playerid, 100);
    FreePlayer(playerid, false);
	
	// interiors
	//RemoveBuildingForPlayer(playerid, 14718, 220.1250, 1291.6250, 1081.1328, 0.25);
	
	Areas[playerid] = CreatePlayerTextDraw(playerid,88.000000, 320.000000, " ");
	PlayerTextDrawAlignment(playerid,Areas[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid,Areas[playerid], 255);
	PlayerTextDrawFont(playerid,Areas[playerid], 1);
	PlayerTextDrawLetterSize(playerid,Areas[playerid], 0.350000, 2.000000);
	PlayerTextDrawColor(playerid,Areas[playerid], -1);
	PlayerTextDrawSetOutline(playerid,Areas[playerid], 0);
	PlayerTextDrawSetProportional(playerid,Areas[playerid], 1);
	PlayerTextDrawSetShadow(playerid,Areas[playerid], 1);
	
	// Спидометр
	
	TDEditor_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 530.332824, 333.941162, "box");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][0], 0.000000, 6.000001);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][0], 635.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][0], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][0], 150);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][0], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][0], 0);

	TDEditor_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 534.000000, 336.000000, "SPEED");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][1], 0.300000, 1.149999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][1], COLOR_LIGHT_CYAN);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][1], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][1], 0);

	TDEditor_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 534.000000, 351.000000, "FUEL");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][2], 0.300000, 1.149999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][2], COLOR_LIGHT_CYAN);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][2], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][2], 0);

	TDEditor_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 534.000000, 376.000000, "ENGINE");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][3], 0.300000, 1.149999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][3], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][3], COLOR_LIGHT_CYAN);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][3], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][3], 0);

	TDEditor_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 569.000000, 376.000000, "LIGHTS");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][4], 0.300000, 1.149999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][4], COLOR_LIGHT_CYAN);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][4], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][4], 0);

	TDEditor_PTD[playerid][5] = CreatePlayerTextDraw(playerid, 605.000000, 376.000000, "LOCK");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][5], 0.300000, 1.149999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][5], COLOR_LIGHT_CYAN);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][5], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][5], 0);

	TDEditor_PTD[playerid][7] = CreatePlayerTextDraw(playerid, 633.000000, 336.000000, "0 MPH");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][7], 0.300000, 1.149999);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][7], 3);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][7], COLOR_LIGHT_CYAN);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][7], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][7], 0);


	// Fuel
	TDEditor_PTD[playerid][8] = CreatePlayerTextDraw(playerid, 594.999267, 355.926696, "box");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][8], 0.000000, 0.300003);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][8], 630.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][8], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][8], -2139062017);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][8], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][8], 0);

	// Fuel 2
	TDEditor_PTD[playerid][9] = CreatePlayerTextDraw(playerid, 594.999267, 355.926696, "box");
	PlayerTextDrawLetterSize(playerid, TDEditor_PTD[playerid][9], 0.000000, 0.300003);
	PlayerTextDrawTextSize(playerid, TDEditor_PTD[playerid][9], 630.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TDEditor_PTD[playerid][9], 1);
	PlayerTextDrawColor(playerid, TDEditor_PTD[playerid][9], -1);
	PlayerTextDrawUseBox(playerid, TDEditor_PTD[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, TDEditor_PTD[playerid][9], -1061109505);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TDEditor_PTD[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TDEditor_PTD[playerid][9], 255);
	PlayerTextDrawFont(playerid, TDEditor_PTD[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, TDEditor_PTD[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, TDEditor_PTD[playerid][9], 0);
	
	
 	Textdraw[playerid][0] = CreatePlayerTextDraw(playerid, 480.000000, 350.000000, "0 mp/h");
	PlayerTextDrawBackgroundColor(playerid, Textdraw[playerid][0], 255);
	PlayerTextDrawFont(playerid, Textdraw[playerid][0], 3);
	PlayerTextDrawLetterSize(playerid, Textdraw[playerid][0], 0.450000, 1.799999);
	PlayerTextDrawColor(playerid, Textdraw[playerid][0], -1);
	PlayerTextDrawSetOutline(playerid, Textdraw[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, Textdraw[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, Textdraw[playerid][0], 1);

	Textdraw[playerid][1]  = CreatePlayerTextDraw(playerid, 480.000000, 365.000000, "Fuel: 0%");
	PlayerTextDrawBackgroundColor(playerid, Textdraw[playerid][1] , 255);
	PlayerTextDrawFont(playerid, Textdraw[playerid][1] , 3);
	PlayerTextDrawLetterSize(playerid, Textdraw[playerid][1] , 0.450000, 1.799999);
	PlayerTextDrawColor(playerid, Textdraw[playerid][1] , -1);
	PlayerTextDrawSetOutline(playerid, Textdraw[playerid][1] , 1);
	PlayerTextDrawSetProportional(playerid, Textdraw[playerid][1] , 1);
	PlayerTextDrawSetShadow(playerid, Textdraw[playerid][1] , 1);

	Textdraw[playerid][2] = CreatePlayerTextDraw(playerid, 480.000000, 381.000000, "lock");
	PlayerTextDrawBackgroundColor(playerid, Textdraw[playerid][2], 255);
	PlayerTextDrawFont(playerid, Textdraw[playerid][2], 3);
	PlayerTextDrawLetterSize(playerid, Textdraw[playerid][2], 0.270000, 1.399999);
	PlayerTextDrawColor(playerid, Textdraw[playerid][2], COLOR_TOMATO);
	PlayerTextDrawSetOutline(playerid, Textdraw[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, Textdraw[playerid][2], 1);
	
	
	
	Textdraw[playerid][3] = CreatePlayerTextDraw(playerid, 504.0, 381.0, "engine");
	PlayerTextDrawBackgroundColor(playerid, Textdraw[playerid][3], 255);
	PlayerTextDrawFont(playerid, Textdraw[playerid][3], 3);
	PlayerTextDrawLetterSize(playerid, Textdraw[playerid][3], 0.270000, 1.399999);
	PlayerTextDrawColor(playerid, Textdraw[playerid][3], COLOR_TOMATO);
	PlayerTextDrawSetOutline(playerid, Textdraw[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, Textdraw[playerid][3], 1);
	

	InventoryText[playerid][0] = CreatePlayerTextDraw(playerid, 657.500000, -0.833297, "0 0 0 175");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][0], 0.000000, 19.340728);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][0], -5.500000, 0.000000);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][0], 0);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][0], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][0], 135);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][0], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][0], 0);
	
	InventoryText[playerid][1] = CreatePlayerTextDraw(playerid, 134.000000, 123.00000, "usebox");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][1], 0.000000, 1.187037);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][1], 79.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][1], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][1], 0);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][1], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][1], 1097465700);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][1], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][1], 0);

	InventoryText[playerid][2] = CreatePlayerTextDraw(playerid, 87.500000, 123.666656, "Player");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][2], 0.239499, 0.927999);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][2], 125.500000, 14.466668);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][2], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][2], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][2], -256);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][2], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][2], true);

	InventoryText[playerid][3] = CreatePlayerTextDraw(playerid, 342.500000, 124.599990, "LD_BEAT:cross");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][3], 14.000000, 11.666671);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][3], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][3], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][3], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][3], true);

	InventoryText[playerid][4] = CreatePlayerTextDraw(playerid, 407.000000, 124.199989, "LD_BEAT:circle");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][4], 14.000000, 11.666671);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][4], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][4], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][4], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][4], true);

	InventoryText[playerid][5] = CreatePlayerTextDraw(playerid, 477.500000, 125.599990, "LD_BEAT:triang");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][5], 14.000000, 11.666671);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][5], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][5], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][5], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][5], true);

	InventoryText[playerid][6] = CreatePlayerTextDraw(playerid, 367.500000, 126.933387, "use");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][6], 0.345499, 0.797330);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][6], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][6], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][6], 1);

	InventoryText[playerid][7] = CreatePlayerTextDraw(playerid, 282.000000, 328.533386, "fast_access");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][7], 0.317499, 0.979333);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][7], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][7], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][7], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][7], 1);

	InventoryText[playerid][8] = CreatePlayerTextDraw(playerid, 176.000000, 346.800170, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][8], 96.000000, 53.666671);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][8], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][8], 1347440740);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][8], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][8], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][8], true);

	InventoryText[playerid][9] = CreatePlayerTextDraw(playerid, 273.500000, 346.800170, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][9], 96.000000, 53.666671);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][9], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][9], 1347440740);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][9], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][9], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][9], true);

	InventoryText[playerid][10] = CreatePlayerTextDraw(playerid, 371.000000, 346.800170, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][10], 96.000000, 53.666671);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][10], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][10], 1347440740);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][10], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][10], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][10], true);

	InventoryText[playerid][11] = CreatePlayerTextDraw(playerid, 206.000000, 368.866760, "menu");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][11], 0.317499, 0.979333);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][11], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][11], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][11], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][11], 1);

	InventoryText[playerid][12] = CreatePlayerTextDraw(playerid, 402.500000, 368.866760, "help");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][12], 0.317499, 0.979333);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][12], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][12], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][12], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][12], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][12], 1);

	InventoryText[playerid][13] = CreatePlayerTextDraw(playerid, 291.500000, 368.866760, "settings");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][13], 0.304000, 0.970000);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][13], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][13], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][13], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][13], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][13], 1);


	InventoryText[playerid][14] = CreatePlayerTextDraw(playerid, 187.000000, 123.300010, "usebox");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][14], 0.000000, 1.187036);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][14], 132.500000, 0.000000);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][14], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][14], 0);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][14], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][14], 1097465700);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][14], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][14], 0);

	InventoryText[playerid][15] = CreatePlayerTextDraw(playerid, 140.000000, 123.733322, "Vehicle");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][15], 0.236498, 0.923332);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][15], 179.000000, 12.600003);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][15], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][15], -1);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][15], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][15], -256);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][15], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][15], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][15], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][15], 1);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][15], true);

	InventoryText[playerid][16] = CreatePlayerTextDraw(playerid, 274.000000, 124.666656, "LD_BEAT:square");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][16], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][16], 14.000000, 11.666666);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][16], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][16], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][16], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][16], 4);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][16], true);

	InventoryText[playerid][17] = CreatePlayerTextDraw(playerid, 297.000000, 127.000053, "give");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][17], 0.345499, 0.797330);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][17], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][17], -1);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][17], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][17], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][17], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][17], 1);
	
	InventoryText[playerid][18] = CreatePlayerTextDraw(playerid,431.000000, 127.000053, "drop");
	PlayerTextDrawLetterSize(playerid,InventoryText[playerid][18], 0.321999, 0.815996);
	PlayerTextDrawAlignment(playerid,InventoryText[playerid][18], 1);
	PlayerTextDrawColor(playerid,InventoryText[playerid][18], -1);
	PlayerTextDrawSetShadow(playerid,InventoryText[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid,InventoryText[playerid][18], 1);
	PlayerTextDrawBackgroundColor(playerid,InventoryText[playerid][18], 51);
	PlayerTextDrawFont(playerid,InventoryText[playerid][18], 2);
	PlayerTextDrawSetProportional(playerid,InventoryText[playerid][18], 1);

	InventoryText[playerid][19] = CreatePlayerTextDraw(playerid,498.500000, 127.066726, "attach");
	PlayerTextDrawLetterSize(playerid,InventoryText[playerid][19], 0.321999, 0.815996);
	PlayerTextDrawAlignment(playerid,InventoryText[playerid][19], 1);
	PlayerTextDrawColor(playerid,InventoryText[playerid][19], -1);
	PlayerTextDrawSetShadow(playerid,InventoryText[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid,InventoryText[playerid][19], 1);
	PlayerTextDrawBackgroundColor(playerid,InventoryText[playerid][19], 51);
	PlayerTextDrawFont(playerid,InventoryText[playerid][19], 2);
	PlayerTextDrawSetProportional(playerid,InventoryText[playerid][19], 1);

	InventoryText[playerid][20] = CreatePlayerTextDraw(playerid, 240.000000, 123.300010, "usebox");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][20], 0.000000, 1.187036);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][20], 185.500000, 0.000000);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][20], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][20], 0);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][20], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][20], 1097465700);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][20], 0);
	PlayerTextDrawFont(playerid, InventoryText[playerid][20], 0);

	InventoryText[playerid][21] = CreatePlayerTextDraw(playerid, 197.500000, 123.733322, "House");
	PlayerTextDrawLetterSize(playerid, InventoryText[playerid][21], 0.236498, 0.923332);
	PlayerTextDrawTextSize(playerid, InventoryText[playerid][21], 240.000000, 12.600003);
	PlayerTextDrawAlignment(playerid, InventoryText[playerid][21], 1);
	PlayerTextDrawColor(playerid, InventoryText[playerid][21], -1);
	PlayerTextDrawUseBox(playerid, InventoryText[playerid][21], true);
	PlayerTextDrawBoxColor(playerid, InventoryText[playerid][21], -256);
	PlayerTextDrawSetShadow(playerid, InventoryText[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, InventoryText[playerid][21], 1);
	PlayerTextDrawBackgroundColor(playerid, InventoryText[playerid][21], 51);
	PlayerTextDrawFont(playerid, InventoryText[playerid][21], 2);
	PlayerTextDrawSetProportional(playerid, InventoryText[playerid][21], 1);
	PlayerTextDrawSetSelectable(playerid, InventoryText[playerid][21], true);

	InventorySlots[playerid][0] = CreatePlayerTextDraw(playerid, 78.000000, 142.800033, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][0], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][0], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][0], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][0], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][0], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][0], 2881);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][0], 223.000000, 0.000000, -60.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][0], true);

	InventorySlots[playerid][1] = CreatePlayerTextDraw(playerid, 176.000000, 142.400039, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][1], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][1], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][1], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][1], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][1], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][1], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][1], 18635);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][1], 0.000000, 0.000000, 0.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][1], true);


	InventorySlots[playerid][2] = CreatePlayerTextDraw(playerid, 274.000000, 142.466735, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][2], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][2], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][2], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][2], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][2], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][2], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][2], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][2], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][2], true);

	InventorySlots[playerid][3] = CreatePlayerTextDraw(playerid, 372.000000, 142.533416, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][3], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][3], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][3], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][3], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][3], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][3], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][3], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][3], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][3], true);

	InventorySlots[playerid][4] = CreatePlayerTextDraw(playerid, 470.000000, 142.600112, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][4], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][4], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][4], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][4], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][4], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][4], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][4], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][4], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][4], true);

	InventorySlots[playerid][5] = CreatePlayerTextDraw(playerid, 78.000000, 197.733474, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][5], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][5], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][5], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][5], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][5], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][5], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][5], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][5], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][5], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][5], true);

	InventorySlots[playerid][6] = CreatePlayerTextDraw(playerid, 176.000000, 197.800170, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][6], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][6], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][6], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][6], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][6], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][6], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][6], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][6], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][6], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][6], true);

	InventorySlots[playerid][7] = CreatePlayerTextDraw(playerid, 274.000000, 197.866821, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][7], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][7], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][7], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][7], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][7], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][7], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][7], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][7], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][7], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][7], true);

	InventorySlots[playerid][8] = CreatePlayerTextDraw(playerid, 372.000000, 197.466812, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][8], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][8], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][8], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][8], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][8], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][8], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][8], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][8], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][8], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][8], true);

	InventorySlots[playerid][9] = CreatePlayerTextDraw(playerid, 470.000000, 197.533447, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][9], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][9], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][9], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][9], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][9], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][9], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][9], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][9], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][9], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][9], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][9], true);

	InventorySlots[playerid][10] = CreatePlayerTextDraw(playerid, 78.000000, 252.666778, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][10], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][10], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][10], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][10], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][10], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][10], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][10], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][10], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][10], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][10], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][10], true);

	InventorySlots[playerid][11] = CreatePlayerTextDraw(playerid, 176.000000, 252.733428, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][11], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][11], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][11], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][11], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][11], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][11], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][11], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][11], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][11], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][11], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][11], true);

	InventorySlots[playerid][12] = CreatePlayerTextDraw(playerid, 274.000000, 252.800094, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][12], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][12], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][12], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][12], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][12], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][12], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][12], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][12], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][12], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][12], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][12], true);

	InventorySlots[playerid][13] = CreatePlayerTextDraw(playerid, 372.000000, 252.866775, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][13], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][13], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][13], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][13], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][13], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][13], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][13], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][13], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][13], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][13], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][13], true);

	InventorySlots[playerid][14] = CreatePlayerTextDraw(playerid, 470.000000, 252.933456, "New Textdraw");
	PlayerTextDrawLetterSize(playerid, InventorySlots[playerid][14], 0.449999, 1.600000);
	PlayerTextDrawTextSize(playerid, InventorySlots[playerid][14], 96.500000, 53.666679);
	PlayerTextDrawAlignment(playerid, InventorySlots[playerid][14], 1);
	PlayerTextDrawColor(playerid, InventorySlots[playerid][14], -1);
	PlayerTextDrawUseBox(playerid, InventorySlots[playerid][14], true);
	PlayerTextDrawBoxColor(playerid, InventorySlots[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, InventorySlots[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlots[playerid][14], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][14], 1246382692);
	PlayerTextDrawFont(playerid, InventorySlots[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, InventorySlots[playerid][14], 1);
	PlayerTextDrawSetPreviewModel(playerid, InventorySlots[playerid][14], 1649);
	PlayerTextDrawSetPreviewRot(playerid, InventorySlots[playerid][14], 0.000000, 0.000000, 90.000000, 1.000000);
	PlayerTextDrawSetSelectable(playerid, InventorySlots[playerid][14], true);
	
	for(new i = 0; i < 15; i++) {
        PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][i], 1347440740);
    }
    
    InventorySlotsKol[playerid][0] = CreatePlayerTextDraw(playerid, 80.500000, 186.666610, "CkВњВ®_(2)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][0], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][0], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][0], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][0], 1);

	InventorySlotsKol[playerid][1] = CreatePlayerTextDraw(playerid, 178.000000, 187.199966, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][1], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][1], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][1], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][1], 1);

	InventorySlotsKol[playerid][2] = CreatePlayerTextDraw(playerid, 276.000000, 187.266632, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][2], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][2], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][2], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][2], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][2], 1);

	InventorySlotsKol[playerid][3] = CreatePlayerTextDraw(playerid, 374.000000, 187.333251, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][3], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][3], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][3], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][3], 1);

	InventorySlotsKol[playerid][4] = CreatePlayerTextDraw(playerid, 472.500000, 187.399887, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][4], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][4], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][4], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][4], 1);

	InventorySlotsKol[playerid][5] = CreatePlayerTextDraw(playerid, 80.500000, 241.133255, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][5], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][5], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][5], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][5], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][5], 1);

	InventorySlotsKol[playerid][6] = CreatePlayerTextDraw(playerid, 178.500000, 242.133270, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][6], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][6], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][6], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][6], 1);

	InventorySlotsKol[playerid][7] = CreatePlayerTextDraw(playerid, 277.000000, 242.637451, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][7], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][7], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][7], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][7], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][7], 1);

	InventorySlotsKol[playerid][8] = CreatePlayerTextDraw(playerid, 375.000000, 242.237457, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][8], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][8], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][8], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][8], 1);

	InventorySlotsKol[playerid][9] = CreatePlayerTextDraw(playerid, 472.000000, 242.304122, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][9], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][9], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][9], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][9], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][9], 1);

	InventorySlotsKol[playerid][10] = CreatePlayerTextDraw(playerid, 81.000000, 296.037384, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][10], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][10], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][10], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][10], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][10], 1);

	InventorySlotsKol[playerid][11] = CreatePlayerTextDraw(playerid, 178.500000, 297.504028, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][11], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][11], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][11], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][11], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][11], 1);

	InventorySlotsKol[playerid][12] = CreatePlayerTextDraw(playerid, 276.500000, 297.570678, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][12], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][12], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][12], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][12], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][12], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][12], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][12], 1);

	InventorySlotsKol[playerid][13] = CreatePlayerTextDraw(playerid, 374.500000, 297.170654, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][13], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][13], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][13], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][13], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][13], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][13], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][13], 1);

	InventorySlotsKol[playerid][14] = CreatePlayerTextDraw(playerid, 473.000000, 296.770690, "MoВћoВ¦ok_(1)");
	PlayerTextDrawLetterSize(playerid, InventorySlotsKol[playerid][14], 0.208499, 0.736666);
	PlayerTextDrawAlignment(playerid, InventorySlotsKol[playerid][14], 1);
	PlayerTextDrawColor(playerid, InventorySlotsKol[playerid][14], -1);
	PlayerTextDrawSetShadow(playerid, InventorySlotsKol[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, InventorySlotsKol[playerid][14], 1);
	PlayerTextDrawBackgroundColor(playerid, InventorySlotsKol[playerid][14], 51);
	PlayerTextDrawFont(playerid, InventorySlotsKol[playerid][14], 2);
	PlayerTextDrawSetProportional(playerid, InventorySlotsKol[playerid][14], 1);

    SetTimerEx("set_wound", 2000, false, "ii", playerid, 0);
	PlayerTextDrawSetString(playerid, Loading[playerid], "~g~L~w~oading...");
	

	format(qu, sizeof(qu), "SELECT users.id, users.login FROM users JOIN characters ON users.id=characters.userid WHERE users.login='%s' OR characters.name = '%s'", sendername(playerid), sendername(playerid));
	ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "Загрузка", "Связываемся с базой данных и пытаемся найти Ваш аккаунт...", "Скрыть", "");
	mysql_function_query(dbHandle, qu, true, "player_check", "i", playerid);
	
	ShopTXD(playerid);
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) {


	if(playertextid == InventoryText[playerid][8]) {
		cmd_menu(playerid);
	} else if(playertextid == InventoryText[playerid][10]) {
		cmd_help(playerid);
	} else if(playertextid == InventoryText[playerid][9]) {
		cmd_settings(playerid);
	}
	else if(playertextid == InventoryText[playerid][2]) {
		InvTDChangeType(playerid, 0);
	} else if (playertextid == InventoryText[playerid][15]) {
		InvTDChangeType(playerid, 1);
	} else if (playertextid == InventoryText[playerid][21]) {
		InvTDChangeType(playerid, 2);
	} else if(player_info[playerid][inv_selected] > -1) {
		if(GetPVarInt(playerid, "inv_type_selected") == 0) {
			if(playertextid == InventoryText[playerid][16]) {
				/*if(Items[character_info[playerid][inv][id][player_info[playerid][inv_selected]]][compound])
	              */
				ShowPlayerDialog(playerid, 7, DIALOG_STYLE_INPUT,"Инвентарь", "Введите id игрока: ", "Ввести", "Отмена");
			}
			else if(playertextid == InventoryText[playerid][3]) {
				// SendClientMessageEx(playerid, COLOR_RED, "> %d, %d", character_info[playerid][wound], player_info[playerid][inv_selected]);
				if(character_info[playerid][wound] > 0) return 1;
				if(GetPVarInt(playerid, "_dev_")) {
					SendClientMessageEx(playerid, COLOR_GRAY, "%d", player_info[playerid][inv_selected]);
				}
		   		useitem(playerid, player_info[playerid][inv_selected]);
		   		InvTDSlotUpdate(playerid, player_info[playerid][inv_selected]);
			}
			else if(playertextid == InventoryText[playerid][4]) {
				if(Items[character_info[playerid][inv][id][player_info[playerid][inv_selected]]][compound])
					ShowPlayerDialog(playerid, 6, DIALOG_STYLE_INPUT,"Инвентарь", "Введите количество: ", "Ввести", "Отмена");
				else
				    ShowPlayerDialog(playerid, 20, DIALOG_STYLE_MSGBOX, "Инвентарь", "Вы действительно хотите выкинуть этот предмет?", "Да", "Нет");
			}
			else if(playertextid == InventoryText[playerid][5]) {
				if(character_info[playerid][inv][id][player_info[playerid][inv_selected]] == -1) return SCM(playerid, COLOR_RED, "Произошла внутренняя ошибка. (FAKE ITEM)");
				SetPVarInt(playerid, "attach_itemid", character_info[playerid][inv][id][player_info[playerid][inv_selected]]);
				HideInvt(playerid);
				CancelSelectTextDraw(playerid);
	   			ShowPlayerDialog(playerid, 21, DIALOG_STYLE_TABLIST, "Выберите кость", "Спина\nГолова\nПлечо левой руки\nПлечо правой руки\nЛевая рука\nПравая рука\nЛевое бедро\nПравое бедро\nЛевая нога\nПравая нога\nПравые икры\nЛевые икры\nЛевое предплечье\nПравое предплечье\nЛевая ключица\nПравая ключица\nШея\nЧелюсть", "Выбрать", "Отмена");
			}
		} else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы можете использовать предметы только из инвентаря!");
	}

	new p = PropertyInventory(playerid);
	new v = GetPVarInt(playerid, "inv_type_veh");
	if(v != 0) {
		new floatxyz;
		GetVehiclePos(v, xyz);
		if(!PlayerToPoint(5.0, playerid, xyz)) {
			v = 0;
			DeletePVar(playerid, "inv_type_veh");
			if(GetPVarInt(playerid, "inv_type") == 1 || GetPVarInt(playerid, "inv_type_selected") == 1) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Похоже транспорт больше не находится рядом с Вами...");
			
		}
	}

	for(new j = 0; j < 15; j++)
    {
        if(playertextid == InventorySlots[playerid][j])
        {
        	if(player_info[playerid][inv_selected] >= 0) {
	         	if(player_info[playerid][inv_selected] == j && GetPVarInt(playerid, "inv_type") == GetPVarInt(playerid, "inv_type_selected")) {
	        		InvTDUnselect(playerid);	
	        	}  else {
	        		new itemid = 0, itemcount = 0;
	        		switch(GetPVarInt(playerid, "inv_type_selected")) {
	        			case 0: {
	        				itemid = character_info[playerid][inv][id][player_info[playerid][inv_selected]];
	        				itemcount = character_info[playerid][inv][count][player_info[playerid][inv_selected]];
	        			}
	        			case 1: {
	        				itemid = veh_info[v][inv][id][player_info[playerid][inv_selected]];
	        				itemcount = veh_info[v][inv][count][player_info[playerid][inv_selected]];
	        			}
	        			case 2: {
	        				itemid = prop_info[p][inv][id][player_info[playerid][inv_selected]];
	        				itemcount = prop_info[p][inv][count][player_info[playerid][inv_selected]];
	        			}
	        		}
	            	if(!Items[itemid][compound] || GetPVarInt(playerid, "inv_type") == GetPVarInt(playerid, "inv_type_selected")) InvTDMoveItem(playerid, j, itemcount);
	            	else {
	            		SetPVarInt(playerid, "InvMoveItem_slot", j);
	            		Dialog_Show(playerid, InvMoveItem, DIALOG_STYLE_INPUT, "Перемещение", "Введите количество предмета: ", "Ввод", "Отмена");
	            	}
	            }
        	} else if(	character_info[playerid][inv][id][j] != 0 && GetPVarInt(playerid, "inv_type") == 0 || 
        				v != 0 && veh_info[v][inv][id][j] != 0 && GetPVarInt(playerid, "inv_type") == 1 ||
        				p != -1 && prop_info[p][inv][id][j] != 0 && GetPVarInt(playerid, "inv_type") == 2 ) {

                player_info[playerid][inv_selected] = j;
	            
                SetPVarInt(playerid, "inv_type_selected", GetPVarInt(playerid, "inv_type"));
                PlayerTextDrawHide(playerid,InventorySlots[playerid][j]); 
                PlayerTextDrawBackgroundColor(playerid, InventorySlots[playerid][j], 1097465700);
                PlayerTextDrawShow(playerid,InventorySlots[playerid][j]); 
                
            } 
        }
    }
	return 1;
}
public OnPlayerClickTextDraw(playerid, Text:clickedid) {
	if(_:clickedid == INVALID_TEXT_DRAW) {
		InvTDUnselect(playerid);
		HideInvt(playerid);
	}
	return 1;
}
public OnPlayerDisconnect(playerid, reason)
{
	if(GetPayphone(playerid) != -1) {
		UnusePayphone(playerid, GetPayphone(playerid));
	} 

	LogIn[playerid] = 0;
	character_info[playerid][spawned] = 0;
	for(new i; i < 9; i++)
	{
		PlayerTextDrawDestroy(playerid, TDEditor_PTD[playerid][i]);
		PlayerTextDrawDestroy(playerid, Areas[playerid]); 
	}
	PlayerTextDrawDestroy(playerid, FullMonitor[playerid]); 
	for(new i; i<MAX_ACHAT; i++) 
	{
		if(achat_info[i][Playerid] == playerid) 
		{
			if(achat_info[i][New]) achat_info[i][New] = false;
			achat_info[i][Playerid] = -1; 
		}
	}
	
	UpdateAchat();
	OnPlayerDisconnectEx(playerid, reason);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if(player_info[playerid][loged] == 0)
	{
		PlayerTextDrawSetString(playerid, Loading[playerid], "~g~Load~w~ing...");
		if(!GetPVarInt(playerid, "account_searched"))
		return 1;

		new r = random(12);
		SetPlayerVw(playerid, -1);
		SetPlayerWeather(playerid, 1);
		SetPlayerInt(playerid, 0);
		switch(r)
		{
			case 0..2:
			{
				SetPlayerTime(playerid, 20, 0);
				SetPlayerPos(playerid, 2170.9851, -1287.5259, 41.6403);
				SetPlayerCameraPos(playerid, 2170.9851, -1287.5259, 24.6403);
				SetPlayerCameraLookAt(playerid, 2171.0427, -1286.5289, 24.5453);
				//PlayAudioStreamForPlayer(playerid, "http://pacific-coast.ru/music/intro.mp3");
			}
			case 3..4:
			{
				SetPlayerTime(playerid, 14, 0);
				SetPlayerPos(playerid, 1874.7676, -2029.3385, 34);
				SetPlayerCameraPos(playerid, 1874.7676, -2029.3385, 12.8244);
				SetPlayerCameraLookAt(playerid, 1875.7517, -2029.5167, 12.8994);
				//PlayAudioStreamForPlayer(playerid, "http://pacific-coast.ru/music/Mexico_Malandro.mp3");
			}
			case 5:
			{
				SetPlayerTime(playerid, 23, 0);
				SetPlayerInt(playerid, 2);
				SetPlayerPos(playerid, 1224.4785, -3.8078, 1012.3168);
				SetPlayerCameraPos(playerid, 1224.4785, -3.8078, 1002.3168);
				SetPlayerCameraLookAt(playerid, 1223.5636, -4.2074, 1002.2169);
			}
			case 6:
			{
				SetPlayerTime(playerid, 14, 0);
				SetPlayerPos(playerid, 265.1496, -1904.0142, 50.1450);
				SetPlayerCameraPos(playerid, 268.0593, -1889.8549, 8.0496);
				SetPlayerCameraLookAt(playerid, 267.1671, -1889.4052, 7.8597);
			}
			case 7..10:
			{
				SetPlayerTime(playerid, 23, 0);
				SetPlayerPos(playerid, 2394.7107, -1472.2285, 42.1223);
				SetPlayerCameraPos(playerid, 2393.4805, -1473.2576, 30.9729);
				SetPlayerCameraLookAt(playerid, 2392.4893, -1473.1534, 30.4380);
			//	PlayAudioStreamForPlayer(playerid, "http://cdndl.zaycev.net/39412/1461781/eazy-e_-_ole_school_(zaycev.net).mp3");
			}
			case 11:
			{
				SetPlayerTime(playerid, 14, 0);
				SetPlayerPos(playerid, 2517.0986, -1670.9409, 28.1038);
				SetPlayerCameraPos(playerid, 2517.0986, -1670.9409, 18.1038);
				SetPlayerCameraLookAt(playerid, 2517.9941, -1670.4998, 17.8188);
			}
		}
		for(new i; i<20; i++)
		SCM(playerid, COLOR_GRAY, "");

		FreePlayer(playerid, false);
		SetTimerEx("ActorVWFix", 4000, false, "i", playerid);
		return 1;
	}
	
	SetPlayerWeather(playerid, weatherid);
	SetPVarInt(playerid, "spawning", 1);
	DeletePVar(playerid, "account_searched");
	
	StopAudioStreamForPlayer(playerid);
	wepinv(playerid);
	
	if(character_info[playerid][VW] > 200) 
		character_info[playerid][prop] = character_info[playerid][VW]-200;
	
	if(character_info[playerid][VW] == -1) 
		character_info[playerid][VW] = 0;
	
	Freeze(playerid, 1000);
	
	if(character_info[playerid][ajail_time] > 0) 
		SetPlayerPosEx(playerid, AJAIL_POS, AJAIL_VW, AJAIL_INT);
	else if(GetPVarInt(playerid, "SPEC"))
		PVarPosTeleport(playerid);
	else if(character_info[playerid][jail_time] > 0) 
		SetPlayerPosEx(playerid, ArrestZone[0][posRX], ArrestZone[0][posRY], ArrestZone[0][posRZ], ArrestZone[0][VW], ArrestZone[0][Interior]);
	else 
		SetPlayerPosEx(playerid, character_info[playerid][posX], character_info[playerid][posY], character_info[playerid][posZ]+0.01, character_info[playerid][VW], character_info[playerid][Interior]);
	
	//SetTimerEx("SetPlayerPosEx", 1000, false, "ifffii", );
	SetPlayerFacingAngle(playerid, 353.6436);
	SetPlayerSkin(playerid, character_info[playerid][skin]);	
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_SAWNOFF_SHOTGUN , 0);
    SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
	SetPlayerTeam(playerid, 1) ;
    SetPlayerScore(playerid, character_info[playerid][lvl]);
	SetPlayerTime(playerid, hour, 0);
	
	if(IsDuty(playerid)) 
	{
		UpdateDutyGuns(playerid);
		SetPlayerSkin(playerid, character_info[playerid][duty_skin]);
	}
	if(GetPVarFloat(playerid, "hp_resp")) 
	{
		SetPlayerHealth(playerid, GetPVarFloat(playerid, "hp_resp"));
		DeletePVar(playerid, "hp_resp");
	}
	UpdateArm(playerid);
	
	UpdatePlayerColor(playerid);
	UpdateDutyGuns(playerid);
    attach_player_update(playerid);
	 
	if(!character_info[playerid][spawned])
		SetTimerEx("OnPreload", 3000, false, "d", playerid);
	
	//Freeze(playerid, 2000);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_SPAWNED) {
	    new Float:posx, Float:posy, Float:posz;
		new posvw = GetPlayerVirtualWorld(playerid), interior = GetPlayerInterior(playerid);
	    GetPlayerPos(playerid, posx, posy, posz);
		character_info[playerid][posX] = posx;
		character_info[playerid][posY] = posy;
		character_info[playerid][posZ] = posz;
		character_info[playerid][VW] = posvw;
		character_info[playerid][Interior] = interior;
	} else {
		SpawnPlayer(playerid);
	}
	if(killerid == INVALID_PLAYER_ID || reason > 0 && character_info[playerid][wound] == 0) set_wound(playerid, 2);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	//printf("[debug_3d] callsign remove vehspawn");
	
	veh_info[vehicleid][Radio] = 0;
	veh_info[vehicleid][engine] = bool:0;
	veh_info[vehicleid][lights] = bool:0;
	veh_info[vehicleid][window_1] = bool:1;
	veh_info[vehicleid][window_2] = bool:1;
	veh_info[vehicleid][window_3] = bool:1;
	veh_info[vehicleid][window_4] = bool:1;
	veh_info[vehicleid][boonet] = bool:0;
	veh_info[vehicleid][boot] = bool:0;
	veh_info[vehicleid][alarm] = bool:0;
	
	if(veh_info[vehicleid][owner] < 0)
	{
		if(IsValidDynamic3DTextLabel(veh_info[vehicleid][callsign]))
			Delete3DTextLabel(veh_info[vehicleid][callsign]);
			
		RepairVehicle(vehicleid);
	}
	
	UpdateVehParams(vehicleid);
	UpdateTune(vehicleid);
	return 1;
}


public OnVehicleDeath(vehicleid, killerid)
{
	//printf("[debug_3d] callsign remove vehdeath");
	Delete3DTextLabel(veh_info[vehicleid][callsign]);
	veh_info[vehicleid][callsign] = Text3D:INVALID_3DTEXT_ID;
	return 1;
}

public OnPlayerText(playerid, text[])
{
	if(player_info[playerid][loged] == 0) return 0;
	if(!IsAdmin(playerid, 2, true, true)) {
		cmd_b(playerid, text);
		return false;
	}
	new string[ 180 ];
	if(GetPVarInt(playerid, "in_ether"))
	{
		format(string, sizeof(string), "[SAN] %s: %s", sendername(playerid, true), text);
		foreach(new p : Player)
		{
			if(!IsPlayerLoged(p) || GetPVarInt(p, "san_off")) continue;
			SCM(p, COLOR_LIGHTBLUE, string);
		}
		return false;
	}
	new str_voice[33];
	if(!CompareStrings(character_info[playerid][voice], "off")) format(str_voice, sizeof(str_voice), " %s", character_info[playerid][voice]);
	if(GetPVarInt(playerid, "call") || GetPVarInt(playerid, "called_911"))
	{
		format( string, 180, "(Телефон) %s говорит%s: %s" ,sendername( playerid,true ),str_voice, text );
		Log_Write("logs/chat_log.txt", "[%s] (Телефон) %s говорит%s: %s", ReturnDate(), sendername(playerid,true),str_voice, text);
		
		if(GetPVarInt(playerid, "call"))
		{
			new p = GetPVarInt(playerid, "call")-1, string_phone[ 180 ];
			format( string_phone, sizeof(string_phone), "(Телефон) Собеседник: %s", text );
			SCM(p, COLOR_YELLOW, string_phone);
			
			new str[180];
			format(str, sizeof(str), ": %s", text);
			WireMsg(playerid, p, str);
			
			if(GetPVarInt(p, "call") == 0)
			{
				SCM(playerid, COLOR_GRAY, "(( Игрок отключился от сервера, вызов завершен! ))");
				DeletePVar(playerid, "call");
			}
		}
	}
	else if(IsPlayerInAnyVehicle(playerid))
	{
		if(veh_info[GetPlayerVehicleID(playerid)][window_1] && veh_info[GetPlayerVehicleID(playerid)][window_2] && veh_info[GetPlayerVehicleID(playerid)][window_3] && veh_info[GetPlayerVehicleID(playerid)][window_4] && !IsMoto(GetPlayerVehicleID(playerid)) && !IsBike(GetPlayerVehicleID(playerid)))
		{
			format( string, 180, "(Транспорт) %s говорит%s: %s" ,sendername( playerid,true ),str_voice, text );
			Log_Write("logs/chat_log.txt", "[%s] (Транспорт) %s говорит%s: %s", ReturnDate(), sendername( playerid,true ),str_voice, text);
			foreach(new p : Player) if(GetPlayerVehicleID(p) == GetPlayerVehicleID(playerid)) SCM(p, COLOR_WHITE, string); 
			return 0;
		}
		else format( string, 180, "%s говорит%s: %s" ,sendername( playerid,true ), str_voice, text );
	}
	else 
	{
		format( string, 180, "%s говорит%s: %s" ,sendername( playerid,true ), str_voice,text );
	}
	
	if(character_info[playerid][wound] == 0 && !GetPVarInt(playerid, "UsingAnimation") && !GetPVarInt(playerid, "CAOFF") && !GetPVarInt(playerid, "call")) 
	{
		ApplyAnimation(playerid,"GANGS","prtial_gngtlkG",4.1,1,1,1,1,1);
		SetTimerEx("ChatOff", strlen(string) * 100, 0, "d", playerid);
	}
	
	linebreak(playerid, string, 10.0, 0xe4e4e4AA, 0xe4e4e4AA, 0xcbcbcbAA, 0xb0b0b0AA, 0x8c8c8cAA);
	return false;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 0;
}

public OnPlayerEnterCheckpoint(playerid)
{

	if(GetPVarInt(playerid, "search_checkpoint")) DestroyCheckpoint(playerid);
	else if(GetPVarInt(playerid, "buy_purchase"))
	{
		if(!InFactionType(playerid, 3, true) && !InFactionType(playerid, 4, true)) return 1;
		if(takemoney(playerid, purchase_price[character_info[playerid][faction]], "purchase") == 1)
		{
			for(new i; i<MAX_PURCHASE; i++)
			{
			    if(purchase[character_info[playerid][faction]][i][count] < 1) continue;
			    giveitem(playerid, purchase[character_info[playerid][faction]][i][iditem], purchase[character_info[playerid][faction]][i][count]);
			    purchase[character_info[playerid][faction]][i][iditem] = 0;
			    purchase[character_info[playerid][faction]][i][count] = 0;
			}
			purchase_price[character_info[playerid][faction]] = 0;
			DisablePlayerCheckpoint(playerid);
			DeletePVar(playerid, "buy_purchase");
			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы подняли сумку со своим заказом!");
			new qu[128], f_id = character_info[playerid][faction];
			format(qu, sizeof(qu), "UPDATE factions SET drugs='%d', guns='%d', bulls='%d' WHERE id=%d",
			factions[f_id][drugs],factions[f_id][guns],
			factions[f_id][bulls],character_info[playerid][faction]
			);
			mysql_function_query(dbHandle, qu, false, "", "");
			if(GetPVarInt(playerid, "local_obj"))
		    {
		        DestroyDynamicObject(GetPVarInt(playerid, "local_obj"));
		        DeletePVar(playerid, "local_obj");
		    }
		}
		else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(pickupid == ASP) ShowLicDialog(playerid);
	else if(pickupid == CSP) ShowCarShowroom(playerid);
	return 1;
}


public OnVehicleMod(playerid, vehicleid, componentid)
{	
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	if(isPlayerDriver(playerid))
	{
		SetVehicleHealth(vehicleid, 350);	
	}
	return 0;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	new Menu:CurrentMenu = GetPlayerMenu(playerid);
	if(CurrentMenu == buy_skin_menu)
	{
	    if(!GetPVarInt(playerid, "SkinBuy")) return 1;
		switch(row)
		{
			case 0:
			{
			    SetTimerEx("BuySkinMenu", 200, false, "i", playerid);
                new playerskin = GetPlayerSkin(playerid), i = 1;
				for(; i<311;)
			    {
			        if(ErrorSkin)
					{
						i++;
					}
					else break;
			    }
			    if(GetPlayerSkin(playerid)+i < 312) SetPlayerSkin(playerid, GetPlayerSkin(playerid)+i);
			    else SetPlayerSkin(playerid, 1);
			}
			case 1:
			{
			    SetTimerEx("BuySkinMenu", 200, false, "i", playerid);
   				new playerskin = GetPlayerSkin(playerid), i = 1;
				for(; i<311;)
			    {
			        if(ErrorSkin)
					{
						i++;
					}
					else break;
			    }
				if(GetPlayerSkin(playerid)-i > 0) SetPlayerSkin(playerid, GetPlayerSkin(playerid)-i);
				else SetPlayerSkin(playerid, 299);
			}
			case 2:
			{
			    BuySkin(playerid, GetPlayerSkin(playerid));
			    SetCameraBehindPlayer(playerid);
                FreePlayer(playerid, 1);
			    SetPVarInt(playerid, "SkinBuy", false);
			    SetPlayerSkin(playerid, character_info[playerid][skin]);
			}
			case 3:
			{
			    SetCameraBehindPlayer(playerid);
			    FreePlayer(playerid, 1);
			    SetPVarInt(playerid, "SkinBuy", false);
       			SetPlayerSkin(playerid, character_info[playerid][skin]);
			}
		}
	}
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    
	if (PRESSED(KEY_SECONDARY_ATTACK) && !isPlayerDriver(playerid))
	{
		for(new i = 0; i<MAX_DOORS; i++)
		{
		    if(door[i][Model] < 1) continue;
		    if(PlayerToPoint(2.0, playerid, door[i][posX],door[i][posY],door[i][posZ]) && GetPlayerVirtualWorld(playerid) == door[i][vworld] && GetPlayerInterior(playerid) == door[i][intid])
			{
			    if(GetPVarInt(playerid, "timeout_door")) return 1;
				if(devTest(playerid))
				{
					new str[128];
					format(str, sizeof(str), "DOOR: %d. FACTIONID: %d", i, door[i][factionid]);
					devmsg(playerid, str);
				}
			    if(!InFactionId(playerid, door[i][factionid]) && door[i][factionid]) return 1;
                if(!door[i][open])
                {
                    SetDynamicObjectPos(door[i][Model], door[i][posXS], door[i][posYS], door[i][posZS]);
					SetDynamicObjectRot(door[i][Model], door[i][posRXS], door[i][posRYS], door[i][posRZS]);
					SYS_AME(playerid, "открывает дверь");
					door[i][open] = true;
                }
                else
                {
                    SetDynamicObjectPos(door[i][Model], door[i][posX], door[i][posY], door[i][posZ]);
					SetDynamicObjectRot(door[i][Model], door[i][posRX], door[i][posRY], door[i][posRZ]);
					SYS_AME(playerid, "закрывает дверь");
                    door[i][open] = false;
                }
				SetPVarInt(playerid, "timeout_door", 1);
				SetTimerEx("timeout_door_null", 500, false, "i", playerid);
			}
		}
		cmd_enter(playerid);
	}
	
	if(PRESSED(KEY_WALK))
	{
		cmd_atm(playerid);
	}
	
	if (PRESSED(KEY_NO))
	{
		if(GetPVarInt(playerid, "addprop_step2"))
		{
			if(GetPVarInt(playerid, "addprop_step2_serverint")-1 <= 0) return 1; 
			SetPVarInt(playerid, "addprop_step2_serverint", GetPVarInt(playerid, "addprop_step2_serverint")-1);
			new str[11];
			valstr(str, GetPVarInt(playerid, "addprop_step2_serverint"));
			cmd_serverint(playerid, str);
			return 1;
		}
	    for(new i=0; i<MAX_ITEM_DROP; i++)
	    {
            if(PlayerToPoint(1.5, playerid, items_drop[i][posX],items_drop[i][posY],items_drop[i][posZ]) && GetPlayerVirtualWorld(playerid) == items_drop[i][vworld] && GetPlayerInterior(playerid) == items_drop[i][inter] && items_drop[i][id] > 0)
			{
			    new str[64];
			    format(str, sizeof(str), ">{ffffff} Вы подняли %s (%d)", senderitems(items_drop[i][myitem]), items_drop[i][item_count]);
			    SCM(playerid, COLOR_GREEN, str);
			    DestroyDynamicObject(items_drop[i][id]);
				Log_Write("logs/drop_log.txt", "[%s] %s поднял %s(%d) [ID: %d]", ReturnDate(), CharacterAndPlayerName(playerid), items_drop[i][myitem], items_drop[i][item_count], items_drop[i][id]);
			    //printf("(%d) %s(%s) getting %d(%d)[ID: %d]",player_info[playerid][id], , items_drop[i][myitem], items_drop[i][item_count], items_drop[i][id]);
				giveitem(playerid, items_drop[i][myitem], items_drop[i][item_count]);
				items_drop[i][id] = 0;
				items_drop[i][myitem] = 0;
				items_drop[i][item_count] = 0;
				items_drop[i][posX] = 0;
				items_drop[i][posY] = 0;
				items_drop[i][posZ] = 0;
				items_drop[i][posRX] = 0;
				items_drop[i][posRY] = 0;
				items_drop[i][posRZ] = 0;
				items_drop[i][vworld] = 0;
				items_drop[i][inter] = 0;
				format(items_drop[i][charactername], 25, "");
				break;
			}
	    }
		if(character_info[playerid][gun] > 0) return cmd_invwep(playerid);
	}
	if (PRESSED(KEY_YES)) 
	{
		if(GetPVarInt(playerid, "addprop_step2"))
		{
			if(GetPVarInt(playerid, "addprop_step2_serverint")-1 > sizeof(Interiors)) return 1;
			SetPVarInt(playerid, "addprop_step2_serverint", GetPVarInt(playerid, "addprop_step2_serverint")+1);
			new str[11];
			valstr(str, GetPVarInt(playerid, "addprop_step2_serverint"));
			cmd_serverint(playerid, str);
			return 1;
		}
		
		if(GetPVarInt(playerid, "AcceptType"))
		{

			
			new ply = GetPVarInt(playerid, "AcceptPlayer")-1, atype = GetPVarInt(playerid, "AcceptType");		
			
			if (!IsPlayerNearPlayer(playerid, ply, 2.0))
				return SendErrorMessage(playerid, "Вы не находитесь поблизости с этим игроком.");

	
			
			if(atype < 1 || atype > 4) 
				return DeletePVar(playerid, "AcceptType");
			
			SetPlayerToFacePlayer(playerid, ply);
			SetPlayerToFacePlayer(ply, playerid);	
			
			if(atype == 1)
			{

				UseAnim(playerid,"GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0, 1);
				UseAnim(ply,"GANGS", "hndshkfa", 4.0, 0, 0, 0, 0, 0, 1);
				DeletePVar(playerid, "AcceptType");
				return 1;
			}
			else if(atype == 2)
			{
				UseAnim(playerid,"GANGS","hndshkaa",4.0, 0, 0, 0, 0, 0, 1);
				UseAnim(ply,"GANGS","hndshkaa",4.0, 0, 0, 0, 0, 0, 1);
				DeletePVar(playerid, "AcceptType");
				return 1;
			}
			else if(atype == 3)
			{
				UseAnim(playerid,"BD_FIRE","GRLFRD_KISS_03",4.0,0,0,0,0,0,1);
				UseAnim(ply,"BD_FIRE","PLAYA_KISS_03",4.0,0,0,0,0,0,1);
				DeletePVar(playerid, "AcceptType");
				return 1;
			}
			else if(atype == 4)
			{
				switch(GetPVarInt(playerid, "AcceptAnimType")) 
				{
					case 1 : {
						UseAnim(ply,"GANGS","hndshkba",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","hndshkba",4.0,0,0,0,0,0);
					}
					case 2 : {
						UseAnim(ply,"GANGS","hndshkda",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","hndshkda",4.0,0,0,0,0,0);
					}
					case 3 : {
						UseAnim(ply,"GANGS","hndshkfa_swt",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","hndshkfa_swt",4.0,0,0,0,0,0);
					}
					case 4 : {
						UseAnim(ply,"GANGS","DEALER_DEAL",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","DEALER_DEAL",4.0,0,0,0,0,0);
					}
					case 5 : {
						UseAnim(ply,"GANGS","DRUGS_BUY",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","DRUGS_BUY",4.0,0,0,0,0,0);
					}
					case 6 : {
						UseAnim(ply,"GANGS","hndshkaa",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","hndshkaa",4.0,0,0,0,0,0);
					}
					case 7 : {
						UseAnim(ply,"GANGS","hndshkca",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","hndshkca",4.0,0,0,0,0,0);
					}
					case 8 : {
						UseAnim(ply,"GANGS","hndshkea",4.0,0,0,0,0,0);
						UseAnim(playerid,"GANGS","hndshkea",4.0,0,0,0,0,0);
					}
					case 9 : {
						UseAnim(ply,"KISSING","Playa_Kiss_02",4.0,0,0,0,0,0);
						UseAnim(playerid,"KISSING","Playa_Kiss_02",4.0,0,0,0,0,0);
					}
				}
				DeletePVar(playerid, "AcceptType");
				return 1;
			}
		}
		cmd_inventory(playerid);
	}
	if (PRESSED(KEY_SPRINT) && GetPVarInt(playerid, "move_player") > -1) up_player(GetPVarInt(playerid, "move_player"));
	if (PRESSED(KEY_SPRINT) && GetPVarInt(playerid, "SPEC"))
	{
		new str[11];
		format(str, sizeof(str), "%d", GetPVarInt(playerid, "SPEC_PLAYER")); 
		cmd_sp(playerid, str);
	}
	if (PRESSED(KEY_JUMP) && GetPVarInt(playerid, "move_player") > -1) 
		down_player(GetPVarInt(playerid, "move_player"));
	
	if (PRESSED(KEY_SPRINT) && GetPlayerVehicleID(playerid) < 1) 
		SetPVarInt(playerid, "SPRINT_PRESSED", true);
	
	if (PRESSED(KEY_SECONDARY_ATTACK) && GetPVarInt(playerid, "UsingAnimation")) 
		cmd_sa(playerid);
	
	if (RELEASED(KEY_SPRINT) && GetPVarInt(playerid, "SPRINT_PRESSED")) 
		DeletePVar(playerid, "SPRINT_PRESSED");
	
	if(PRESSED(KEY_CTRL_BACK))
	{
		new targetplayer = GetPlayerTargetPlayer(playerid), str[4];
		format(str, sizeof(str), "%d", targetplayer);
		cmd_look(playerid, str);
	}
	
	if(PRESSED(2) && isPlayerDriver(playerid))
	{
		if(character_info[playerid][faction] != 0)
			GoToVehEnter(playerid);
	}
	
	if(isPlayerDriver(playerid) && PRESSED(KEY_FIRE))
		cmd_li(playerid);
	
	if(isPlayerDriver(playerid) && PRESSED(KEY_ACTION)) 
		cmd_en(playerid);

	if(isPlayerDriver(playerid) && PRESSED(KEY_ANALOG_UP)) 
		cmd_li(playerid);
	
	if(isPlayerDriver(playerid) && PRESSED(KEY_ANALOG_DOWN)) 
		cmd_en(playerid);
	
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
  	if(newstate == PLAYER_STATE_DRIVER)
	{
		if(IsBike(GetPlayerVehicleID(playerid))) 
			return 1;
		
		if(!veh_info[GetPlayerVehicleID(playerid)][fuel])
		{
			new str[64];
			PlayerTextDrawHide(playerid,Textdraw[playerid][0] );
			format(str, sizeof(str), "Fuel: %d", veh_info[GetPlayerVehicleID(playerid)][fuel]);
			PlayerTextDrawSetString(playerid, Textdraw[playerid][0] , str);
			PlayerTextDrawShow(playerid,Textdraw[playerid][0] );
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
	  	ShowSpeed(playerid);
	}
    else   
		HideSpeed(playerid);
	
	if(IsPlayerInAnyVehicle(playerid) && veh_info[GetPlayerVehicleID(playerid)][owner] < 0)
	{

		
		if(ntop(veh_info[GetPlayerVehicleID(playerid)][owner]) == LSPD_FACTION || ntop(veh_info[GetPlayerVehicleID(playerid)][owner]) == SASD_FACTION) 
		{
			SetPVarInt(playerid, "PD_STREAM", 1);
			PlayAudioStreamForPlayer(playerid, "http://relay.radioreference.com:80/615491319");
			if(character_info[playerid][faction] != LSPD_FACTION && character_info[playerid][faction] != SASD_FACTION) 
			{
				if(isPlayerDriver(playerid))
				{
					veh_info[GetPlayerVehicleID(playerid)][engine] = false;
					UpdateVehParams(GetPlayerVehicleID(playerid));
				}
			}
		}
	}
	else if(GetPVarInt(playerid, "PD_STREAM"))
	{
		DeletePVar(playerid, "PD_STREAM");
		StopAudioStreamForPlayer(playerid);
	}
	else if(GetPVarInt(playerid, "CAR_MUSIC"))
	{
		DeletePVar(playerid, "CAR_MUSIC");
		StopAudioStreamForPlayer(playerid);
	}
	
	if(IsPlayerInAnyVehicle(playerid) && veh_info[GetPlayerVehicleID(playerid)][Radio] == 1)
	{
		SetPVarInt(playerid, "CAR_MUSIC", 1);
		PlayAudioStreamForPlayer(playerid, Music[veh_info[GetPlayerVehicleID(playerid)][Station]][URL]);
	}
		
	if(IsPlayerInAnyVehicle(playerid) && IsValidDynamicObject(veh_info[GetPlayerVehicleID(playerid)][taxi]) && GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
	{
		SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы сели в такси!");
		foreach(new p : Player)
		{
			if(!IsPlayerLoged(p)) continue;
			new v = GetPlayerVehicleID(p);
			if(v > 0 && isPlayerDriver(p) && GetPlayerVehicleID(p) == GetPlayerVehicleID(playerid))
			{
				SetPVarInt(playerid, "Taxist", p);
				break;
			}
		}
		SetPVarInt(playerid, "InTaxi", 1);
	}
	else if(GetPVarInt(playerid, "InTaxi"))
	{
		if(takemoney(playerid, GetPVarInt(playerid, "InTaxi_Money"), "taxi") == 1) givemoney(GetPVarInt(playerid, "taxist"), GetPVarInt(playerid, "InTaxi_Money"), "taxi_job");
		
		DeletePVar(playerid, "InTaxi");
		DeletePVar(playerid, "Taxist");
		DeletePVar(playerid, "InTaxi_Money");
		DeletePVar(playerid, "InTaxi_NoMoney");
	}
    return 1;
}

public OnPlayerUpdate(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
		new vehicle = GetPlayerVehicleID(playerid);
	
		if(ACveh[playerid] != vehicle)
			return Kick(playerid);
	}
	
	character_info[playerid][AFK] = 0;
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnPlayerCommandReceived(playerid, cmdtext[])
{
	if(CompareStrings(cmdtext, "/bot"))
	{
		SetPlayerColor(playerid, COLOR_WHITE);
		SetPlayerScore(playerid, random(5));
		SetPVarInt(playerid, "bot", 1);
	}
    if(player_info[playerid][loged] == 0 || GetPVarInt(playerid, "kicking")) return 0;
    if(GetPVarInt(playerid, "flood") > 3)
	{
		SCM(playerid, COLOR_TOMATO, ">{ffffff} Использование команд временно заблокировано!");
		return 0;
	}
	if(GetPVarInt(playerid, "edit_obj")) return 0;
    return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
    if(success == -1) CMDError(playerid);
    if(success == 1)
	{
		if(GetPVarInt(playerid, "flood") < 4)SetPVarInt(playerid, "flood", GetPVarInt(playerid, "flood")+1);
	}
    return 1;
}


public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	return 1;
}


public OnPlayerShootDynamicObject(playerid, weaponid, objectid, Float:x, Float:y, Float:z)
{
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	if(GetPVarInt(playerid, "_dev_")) SCM(playerid, COLOR_RED, "Shot!");
	if(weaponid != 0) {
		
		
		if(weaponid != character_info[playerid][gun] && weaponid != character_info[playerid][duty_gun_1] && weaponid != character_info[playerid][duty_gun_2] && weaponid != character_info[playerid][duty_gun_3] && weaponid != character_info[playerid][duty_gun_special])
		{
			AntiCheat(playerid, "попытался начитерить оружие", ANTICHEAT_DGUN);
		}
	}
	
	if(character_info[playerid][duty_gun_special] == 23 && GetPlayerWeapon(playerid) == 23) UseAnim(playerid, "COLT45", "COLT45_RELOAD", 4.0, 0, 0, 0,0,0);
	
	if(weaponid > 15 && character_info[playerid][ammo] > 0) character_info[playerid][ammo]--;
	else if(weaponid == character_info[playerid][duty_gun_2])
	{
		character_info[playerid][duty_ammo_2]--;
		if(character_info[playerid][duty_ammo_2] < 1) UpdateDutyGuns(playerid);
	}
	else if(weaponid == character_info[playerid][duty_gun_3])
	{
		character_info[playerid][duty_ammo_3]--;
		if(character_info[playerid][duty_ammo_3] < 1) UpdateDutyGuns(playerid);
	}
	if(GetPVarInt(playerid, "_dev_"))
	{
		new str[128];
		format(str, sizeof(str), "%d | %d | %f %f %f", hittype, hitid, fX, fY, fZ);
		SCM(playerid, COLOR_GRAY, str);
	}
	if(hittype == 0)
	{
		for(new i=0; i<MAX_CCTV; i++)
		{
			if(PointToPoint(0.5, fX, fY, fZ, cctv_info[i][posX], cctv_info[i][posY], cctv_info[i][posZ]) && cctv_info[i][id] > 0)
			{
				CCTVmsg(i, "Камера выведена из строя");
				GameTextForPlayer(playerid, "~g~DESTROYED", 2000, 3);
				//PlayerPlaySound(playerid, 1141, 0.0,0.0,1.0);
				CCTVdestroy(i);
				break;
			}
		}
	}
	new i = CCTVArea(playerid);
	if(i > -1 && weaponid >= 22)
	{
		new str[64];
		format(str, sizeof(str), "Зафиксирована стрельба из %s", Items[GetItemByGun(weaponid)][Name]);
		CCTVmsg(i, str);
	}
	if(weaponid != 23 && character_info[playerid][prop] > 0 && !GetPVarInt(playerid, "ShotInProp") && random(5) == 1)
	{
		SetPVarInt(playerid, "ShotInProp", 1);
		
		new propid = GetLocalIdProp(character_info[playerid][prop]);
		new str_msg_1[180], str_msg_2[180];
		format(str_msg_1, sizeof(str_msg_1), "Слышны выстрелы из %s.", Items[GetItemByGun(weaponid)][Name]);
		format(str_msg_2, sizeof(str_msg_2), "Имущество %d.", GetGlobalIdProp(propid));

		if(random(2) == 1) Add911(playerid, str_msg_1, str_msg_2, "Полиция", true);
	}
   	//if(weaponid > 15 && character_info[playerid][ammo] <= 0) invwep(playerid);
    return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	return 0;
}

/*public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
	return 0;
}*/

public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
	new g = GetPlayerWeapon(playerid);
	if(g != weaponid) return 1;
	if(character_info[damagedid][ajail_time] > 0) return 1;
	
	if(character_info[damagedid][AFK] > 5 || GetPVarInt(damagedid, "Freezed")) return 0;
	


	if(bodypart == 3)
	{

		if(GetPVarFloat(damagedid, "arrmor") > 0.0)
		{
			if(GetPVarFloat(damagedid, "arrmor") <= 0.0) DeletePVar(damagedid, "arrmor");
			SetPVarFloat(damagedid,"arrmor",GetPVarFloat(damagedid,"arrmor") - 20.0);
			UpdateArm(damagedid);
			return 1;
		}
	}
	new Float:health, Float:damage;
    GetPlayerHealth(damagedid,health);
	if(weaponid == 22 && bodypart == 9) damage = 100;
	else if(weaponid == 23 && bodypart == 9) damage = 100;
	else if(weaponid == 24 && bodypart == 9) damage = 100;
	else if(weaponid == 25 && bodypart == 9) damage = 100;
	else if(weaponid == 26 && bodypart == 9) damage = 100;
	else if(weaponid == 27 && bodypart == 9) damage = 100;
	else if(weaponid == 28 && bodypart == 9) damage = 100;
	else if(weaponid == 29 && bodypart == 9) damage = 100;
	else if(weaponid == 30 && bodypart == 9) damage = 100;
	else if(weaponid == 31 && bodypart == 9) damage = 100;
	else if(weaponid == 24) damage = 20+random(30);
 	else if(weaponid == 31) damage = 30+random(60);
  	else if(weaponid == 30) damage = 20+random(60);
 	else if(weaponid == 25) 
	{
		if(character_info[playerid][duty_gun_special] == 25)
		{
			if(character_info[damagedid][wound] == 0)
			{
				GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
				set_wound(damagedid, 1);
				SetTimerEx("knockout", 35000, false, "i", damagedid);
				GameTextForPlayer(playerid, "~g~TAZERED", 1000, 3);
			}
			damage = 0;
			return 0;
		}
		else damage = 20+random(60);
	}
	else if(weaponid == 23) 
	{
		if(character_info[playerid][duty_gun_special] == 23)
		{
			if(character_info[damagedid][wound] == 0)
			{
				GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
				new Float:px, Float:py, Float:pz;
				GetPlayerPos(playerid, px, py, pz);
				if(PlayerToPoint(15.0, playerid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]))
				{
					set_wound(damagedid, 1);
					SetTimerEx("knockout", 20000, false, "i", damagedid);
					GameTextForPlayer(playerid, "~g~TAZERED", 1000, 3);
				}
			}

			return 0;
		}

	}
	else if(weaponid == 26) damage = 20+random(40);
	else if(weaponid == 28 || weaponid == 32) damage = 15+random(30);
	else if(weaponid == 29) damage = 20+random(30);
	else if(weaponid == 22) damage = 15+random(30);
	else if(weaponid == 33) damage = 90+random(11);
	else if(weaponid == 34) damage = 100;
	else if(weaponid == 0) {
		damage = 5+random(10);
		if(DrugEffect(26) || DrugEffect(27) || DrugEffect(30) || DrugEffect(33)) damage += 5;
	}
	else if(weaponid == 3) damage = 5+random(10), Freeze(damagedid, 200);
	else if(weaponid == 4) damage = 5+random(10);
	else if(weaponid == 5) damage = 5+random(10);
	else if(weaponid == 6) damage = 10+random(10);
	else if(weaponid == 7) damage = 5+random(10);
	else if(weaponid == 8) damage = 10+random(15);
	else if(weaponid == 9) damage = 1;
	else damage = 0;
	if((bodypart == 9 && weaponid == 24 || bodypart == 9 && weaponid == 23 || bodypart == 9 && weaponid == 33 || bodypart == 9 && weaponid == 31 || bodypart == 9 && weaponid == 30 || bodypart == 9 && weaponid == 29 || bodypart == 9 && weaponid == 25) && character_info[damagedid][wound] == 0)
	{
		if(!IsPlayerAttachItem(damagedid, 16) && !IsPlayerAttachItem(damagedid, 17))
		{
  			SCM(damagedid, COLOR_RED, ">{FFFFFF} Вы получили критический урон в голову.");


			KillMsg(playerid, damagedid, weaponid, "убивает");

			GameTextForPlayer(damagedid, "~r~You were heavy injured", 1000, 3);
			GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
			set_wound(damagedid, 3);

			character_info[damagedid][newlife] = 120;
						
			if(GetPVarInt(damagedid,"Ranen_") != -1)
			{
				KillTimer(GetPVarInt(damagedid,"Ranen_"));
				SetPVarInt(damagedid,"Ranen_",-1);
			
			}
			if(GetPVarInt(damagedid,"ChangeState_Time") != -1)
			{
				KillTimer(GetPVarInt(damagedid,"ChangeState_Time"));
				SetPVarInt(damagedid,"ChangeState_Time",-1);
			
			}

			
		}
	}

	

	
	if(bodypart == 5 || bodypart == 6)
	{
		new rand = random(2);
		if(rand == 1 && character_info[damagedid][gun] > 0)
		{
			if(!IsPlayerAttachItem(damagedid, 19))
			{
				invwep(damagedid);
				SCM(damagedid, COLOR_RED, ">{FFFFFF} Вас обезоружили.");
			}
		}
	}
	if(character_info[playerid][duty_gun_special] != 23 && character_info[playerid][duty_gun_special] != 25)
	{
		if(bodypart == 3 && random(20) == 1 && character_info[damagedid][drunk_time] <= 3 && weaponid != 0)
		{
			if(!IsPlayerAttachItem(damagedid, 19))
			{
				SCM(damagedid, COLOR_RED, ">{FFFFFF} Вы получили ранение в торс, ваши навыки стрельбы ухудшены.");
				character_info[damagedid][drunk_time] = 15;
			}
		}	
		if(character_info[damagedid][wound] == 0 && IsWeaponKnock(weaponid))
		{
		    new rand = random(8);
		    if(rand == 4)
		    {
     			KillMsg(playerid, damagedid, weaponid, "оглушает");

				GameTextForPlayer(damagedid, "~y~You were knocked out", 1000, 3);
				SPD(damagedid, 0, DIALOG_STYLE_MSGBOX, "Предупреждение", "Вы были нокаутированы! Вы сможете двигаться через 20 секунд.\nПо правилам ролевой игры вы больше не можете вступать в драку, отыгрывайте увечья либо попытайтесь уйти.", "Закрыть", "");
				GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
				set_wound(damagedid, 1);
				SetTimerEx("knockout", 20000, false, "i", damagedid);
		    }
		}
		if((character_info[damagedid][wound] == 1 && IsWeaponKill(weaponid)) || (character_info[damagedid][wound] == 0 && IsWeaponKill(weaponid)))
		{
		    
		    KillMsg(playerid, damagedid, weaponid, "ранит");
			
			GameTextForPlayer(damagedid, "~g~You were injured.", 1000, 3);
			set_wound(damagedid, 2);
			
   			if(GetPVarInt(damagedid,"Ranen_") == -1) SetPVarInt(damagedid,"Ranen_",SetTimerEx("Ranen",3000,true,"i",damagedid));
			if(GetPVarInt(damagedid,"ChangeState_Time") == -1) SetPVarInt(damagedid,"ChangeState_Time",SetTimerEx("ChangeState",5000,true,"i",damagedid));

		}
		if(character_info[damagedid][wound] == 2 && IsWeaponKill(weaponid))
		{
			new rand = random(4);
		    if(rand == 2)
		    {
				KillMsg(playerid, damagedid, weaponid, "тяжело ранит");
			
				GameTextForPlayer(damagedid, "~r~You were heavy injured.", 1000, 3);
				GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
				set_wound(damagedid, 4);
				
				character_info[damagedid][newlife] = 300;
			}
			/*SetPVarInt(damagedid,"cmytimer",SetTimerEx("MyTimer",1000,true,"iis",damagedid,900,"New life"));
			SetPVarInt(damagedid,"cdeath",SetTimerEx("CDeath", 900000, false, "i", damagedid));*/
		
		}
		if(character_info[damagedid][wound] == 4 && IsWeaponKill(weaponid))
		{
		    KillMsg(playerid, damagedid, weaponid, "убивает");
	    	
	    	GameTextForPlayer(damagedid, "~r~You died.", 1000, 3);
	    	GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
			set_wound(damagedid, 3);

			character_info[damagedid][newlife] = 120;
			
			
			if(GetPVarInt(damagedid,"Ranen_") != -1)
			{
				KillTimer(GetPVarInt(damagedid,"Ranen_"));
				SetPVarInt(damagedid,"Ranen_",-1);
			
			}
			if(GetPVarInt(damagedid,"ChangeState_Time") != -1)
			{
				KillTimer(GetPVarInt(damagedid,"ChangeState_Time"));
				SetPVarInt(damagedid,"ChangeState_Time",-1);
			
			}
			
			/*KillTimer(GetPVarInt(damagedid,"cmytimer"));
			KillTimer(GetPVarInt(damagedid,"cdeath"));
			
			SetPVarInt(damagedid,"cmytimer",-1);
			SetPVarInt(damagedid,"cdeath",-1);
			
			MyTimerEnd(damagedid);*/
		}
		if(character_info[damagedid][wound] == 3)
		{
			GetPlayerPos(damagedid, character_info[damagedid][posX],character_info[damagedid][posY],character_info[damagedid][posZ]);
			set_wound(damagedid, 3);
		}
		
		if(bodypart == 7 || bodypart == 8)
		{
			//UseAnim(damagedid, "PED", "getup_front", 4.0, 0, 0, 0,0,0);
			SetPVarInt(damagedid, "not_sprint", 120);
			SCM(damagedid, COLOR_RED, ">{FFFFFF} Вы получили ранение в ногу!");
		}
	}
	if(damagedid != INVALID_PLAYER_ID)
	{
		new string[128], victim[MAX_PLAYER_NAME], attacker[MAX_PLAYER_NAME];
		new weaponname[24];
		GetPlayerName(playerid, attacker, sizeof (attacker));
		GetPlayerName(damagedid, victim, sizeof (victim));
		
		GetWeaponName(weaponid, weaponname, sizeof (weaponname));
		format(string, sizeof(string), "%s выстрелил в %s из %s", attacker, victim, weaponname);
		if(GetPVarInt(playerid, "_dev_")) SCM(playerid, COLOR_GRAY, string);
		if(GetPVarInt(damagedid, "_dev_")) SCM(damagedid, COLOR_GRAY, string);
	}
	
	
	for(new i = MAX_DAMAGES; i>-1; i--)
	{
		if(i < MAX_DAMAGES && i != 0)
		{
			character_info[damagedid][damages][part][i] = character_info[damagedid][damages][part][i-1];
			character_info[damagedid][damages][gun_id][i] = character_info[damagedid][damages][gun_id][i-1];
			character_info[damagedid][damages][hour_damages][i] = character_info[damagedid][damages][hour_damages][i-1];
			character_info[damagedid][damages][minute_damages][i] = character_info[damagedid][damages][minute_damages][i-1];
			character_info[damagedid][damages][damage_hp][i] = character_info[damagedid][damages][damage_hp][i-1];
		}
		if(i == 0)
		{
			character_info[damagedid][damages][part][i] = bodypart;
			character_info[damagedid][damages][gun_id][i] = weaponid;
			character_info[damagedid][damages][hour_damages][i] = hour;
			character_info[damagedid][damages][minute_damages][i] = minute;
			character_info[damagedid][damages][damage_hp][i] = damage;
		}
	}
	
	
	return 0;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float:x, Float:y, Float:z)
{
	if(IsAdmin(playerid, 5)) 
		return 1;
	
	EditDynamicObject(playerid, objectid);	
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
    new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;
	
	if(character_info[playerid][type_editobj] == 11)
	{
		if(response == EDIT_RESPONSE_FINAL)
		{
			for(new i; i<MAX_ATM; i++)
			{
				if(atm_info[i][aObj] == objectid)
				{
					new qu[500];
					
					format(qu, sizeof(qu), "UPDATE `atm` SET posX='%f', posY='%f', posZ='%f', posRX='%f', posRY='%f', posRZ='%f' where id=%d", x,y,z,rx,ry,rz,atm_info[i][id]);
					mysql_function_query(dbHandle, qu, true, "", "");
					
					atm_info[i][posX] = x;
					atm_info[i][posY] = y;
					atm_info[i][posZ] = z;
					
					SetObjectPos(objectid, x, y, z);
					SetObjectRot(objectid, rx, ry, rz);
					
					DestroyDynamic3DTextLabel(atm_info[i][a3d]);
					atm_info[i][a3d] = CreateDynamic3DTextLabel("ATM банкомат\n{FFFFFF}Для использования ATM сервисов нажмите 'ALT'.", COLOR_INFO, atm_info[i][posX],atm_info[i][posY],atm_info[i][posZ], 1.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, atm_info[i][VW]);
					
					character_info[playerid][type_editobj] = 0;
					return SendClientMessageEx(playerid, COLOR_MSGADMIN, ">{FFFFFF} Установленны новые координаты для банкомата! [ID %d]", atm_info[i][id]);
				}
			}
		}
		if(response == EDIT_RESPONSE_CANCEL)
		{
			for(new i; i<MAX_ATM; i++)
			{
				if(atm_info[i][aObj] == objectid)
				{
					new qu[115+11];
					
					format(qu, sizeof(qu), "DELETE FROM `atm` where id=%d", atm_info[i][id]);
					mysql_function_query(dbHandle, qu, true, "", "");
					
					atm_info[i][id] = -1;
					
					DestroyDynamic3DTextLabel(atm_info[i][a3d]);
					DestroyDynamicObject(objectid);
					
					character_info[playerid][type_editobj] = 0;
					return SCM(playerid, COLOR_MSGADMIN, ">{FFFFFF} Банкомат удален!");
				}
			}
		}
	}
	
	if(GetPVarInt(playerid, "EditDynamicObject_Tick") >= 10)
	{
		SetPVarInt(playerid, "EditDynamicObject_Tick", 0);
		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, rx, ry, rz);
	}
	else SetPVarInt(playerid, "EditDynamicObject_Tick", GetPVarInt(playerid, "EditDynamicObject_Tick")+1);

	if(character_info[playerid][type_editobj] == 9)
	{
		if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	    {
			if(response == EDIT_RESPONSE_FINAL)
			{
				for(new i; i<20; i++)
				{
					if(fobj_info[playerid][fObj][i] > 0) continue;
					if(!GetPVarInt(playerid, "fobj_3d_off"))
					{
						new str[24];
						format(str, sizeof(str), "#%d", i+1);
						fobj_info[playerid][f3d][i] = CreateDynamic3DTextLabel(str, COLOR_GRAY_EE, xyz, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1, playerid);
						//printf("[debug_3d] create fobj");
					}
					fobj_info[playerid][Model][i] = character_info[playerid][editobject];
					fobj_info[playerid][fObj][i] = objectid;
					SetDynamicObjectPos(objectid, x, y, z);
					SetDynamicObjectRot(objectid, rx, ry, rz);
					SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы создали объект!");
					break;
				}
			}
			else DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
		}
	}
	
	if(character_info[playerid][type_editobj] == 8)
	{
		if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	    {
			if(response == EDIT_RESPONSE_FINAL)
			{
				new qu[256];
				new info[25];
				GetPVarString(playerid, "cctv_create_desc", info, sizeof(info)); 
				mysql_real_escape_string(info, info);
				format(qu, sizeof(qu), "INSERT INTO `cctv`(`posX`, `posY`, `posZ`, `posRX`, `posRY`, `posRZ`, `VW`, `Interior`, `desc`) VALUES (%f, %f, %f, %f, %f, %f, %d, %d, '%s')", x,y,z,rx,ry,rz, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), info);
				mysql_function_query(dbHandle, qu, false, "", "");
				mysql_function_query(dbHandle, "SELECT * FROM `cctv`", true, "OnLoadCCTV", "");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы добавили CCTV камеру!");
			}
			DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
		}
	}
	
	if(character_info[playerid][type_editobj] == 7)
	{
		if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	    {
			if(response == EDIT_RESPONSE_FINAL)
			{
				new qu[256];
				format(qu, sizeof(qu), "INSERT INTO `atm`(`posX`, `posY`, `posZ`, `posRX`, `posRY`, `posRZ`, `vworld`) VALUES (%f, %f, %f, %f, %f, %f, %d)", x,y,z,rx,ry,rz, GetPlayerVirtualWorld(playerid));
				mysql_function_query(dbHandle, qu, false, "", "");
				mysql_function_query(dbHandle, "SELECT * FROM `atm`", true, "OnLoadATM", "");
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы добавили банкомат!");
			}
			DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
		}
	}
	
	if(character_info[playerid][type_editobj] == 6)
	{
		if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	    {
			if(response == EDIT_RESPONSE_FINAL)
			{
				new color[8], text[32], font[32], fontsize = GetPVarInt(playerid, "graf_fontsize");
				GetPVarString(playerid, "graf_text", text, 32);
				GetPVarString(playerid, "graf_font", font, 32);
				GetPVarString(playerid, "graf_color", color, 8);
				if(character_info[playerid][gun] == 41) 
				{
					if(character_info[playerid][ammo] >= strlen(text))
					{
						character_info[playerid][ammo] = character_info[playerid][ammo]-strlen(text);
						//CreateGraff(text, color, font, fontsize, character_info[playerid][id], x,y,z,rx,ry,rz);
						new str[256];
						format(str, sizeof(str), "INSERT INTO `graff`(`text`, `color`, `font`, `fontsize`, `owner`, `posX`, `posY`, `posZ`, `posRX`, `posRY`, `posRZ`) VALUES ('%s', '%s', '%s', %d, %d, %f, %f, %f, %f, %f, %f)",
						text, color, font, fontsize, character_info[playerid][id],
						x,y,z,rx,ry,rz	
						);
						mysql_function_query(dbHandle, str, false, "", "");
						mysql_function_query(dbHandle, "SELECT * FROM `graff` WHERE 1", true, "OnLoadGraff", "");
					}
					else SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} В вашем балончике недостаточно краски!");
				}
			}
			DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
		}
	}
	if(character_info[playerid][type_editobj] == 5)
	{
	    if(response == EDIT_RESPONSE_FINAL)
	    {
	        new Float:door_x = GetPVarFloat(playerid, "door_x"),Float:door_y = GetPVarFloat(playerid, "door_y"),Float:door_z = GetPVarFloat(playerid, "door_z"),Float:door_rx = GetPVarFloat(playerid, "door_rx"),Float:door_ry = GetPVarFloat(playerid, "door_ry"),Float:door_rz = GetPVarFloat(playerid, "door_rz");
			new Float:door_xs = x,Float:door_ys = y,Float:door_zs = z,Float:door_rxs = rx,Float:door_rys = ry,Float:door_rzs = rz;
            //INSERT INTO `doors`(`objectid`, `posX`, `posY`, `posZ`, `posRX`, `posRY`, `posRZ`, `posXS`, `posYS`, `posZS`, `posRXS`, `posRYS`, `posRZS`, `interior`, `virtualworld`, `faction`) VALUES ()
           	new qu[512];
			format(qu, sizeof(qu), "INSERT INTO `doors`(`objectid`, `posX`, `posY`, `posZ`, `posRX`, `posRY`, `posRZ`, `posXS`, `posYS`, `posZS`, `posRXS`, `posRYS`, `posRZS`, `interior`, `virtualworld`, `faction`) VALUES (%d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, %d)",
			GetPVarInt(playerid, "createdoor_objectid"), door_x, door_y, door_z, door_rx, door_ry, door_rz,
			door_xs, door_ys, door_zs, door_rxs, door_rys, door_rzs,
			GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid), GetPVarInt(playerid, "createdoor_factionid")
			);
			mysql_function_query(dbHandle, qu, true, "", "");
			DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
   			SetPVarInt(playerid, "attach_edit", false);
   			SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы добавили дверь!");
   			LoadDoors();
	    }
	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	        DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
	    }
	}
	if(character_info[playerid][type_editobj] == 4)
	{
	    if(response == EDIT_RESPONSE_FINAL)
	    {
			SetPVarFloat(playerid, "door_x", x);
			SetPVarFloat(playerid, "door_y", y);
			SetPVarFloat(playerid, "door_z", z);
			SetPVarFloat(playerid, "door_rx", rx);
			SetPVarFloat(playerid, "door_ry", ry);
			SetPVarFloat(playerid, "door_rz", rz);
			SCM(playerid, COLOR_YELLOW, ">{ffffff} Выберите позицию открытой двери");
			character_info[playerid][type_editobj] = 5;
			EditDynamicObject(playerid, objectid);
	    }
		if(response == EDIT_RESPONSE_CANCEL)
	    {
	        DestroyDynamicObject(objectid);
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
	    }
	}
    if(character_info[playerid][type_editobj] == 3)
    {
        if(response == EDIT_RESPONSE_FINAL)
        {
            new i = 0;
			for(; i<MAX_FURNITURE; i++)
			{
			    if(character_info[playerid][editobject] == furniture[i][id])
			    	break;
			}
            SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);
            furniture[i][cordX] = x, furniture[i][cordY] = y, furniture[i][cordZ] = z;
   			furniture[i][cordRX] = rx, furniture[i][cordRY] = ry, furniture[i][cordRZ] = rz;
			new qu[256];
		 	format(qu, sizeof(qu), "UPDATE `furniture` SET `posX`=%f,`posY`=%f,`posZ`=%f,`posRX`=%f,`posRY`=%f,`posRZ`=%f WHERE id=%d",
			 x, y, z, rx, ry, rz, i
			);
			mysql_function_query(dbHandle, qu, false, "", "");
			character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
        }
    	if(response == EDIT_RESPONSE_CANCEL)
	    {
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
	    }
    }
	if(character_info[playerid][type_editobj] == 2)
	{
	    if(response == EDIT_RESPONSE_FINAL)
	    {
	    	new fid = GetPVarInt(playerid, "furniture_it");
			DeletePVar(playerid, "furniture_it");
	        if(furniture[fid][id] != objectid) return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} При установке мебели произошла ошибка, попробуйте еще раз.");
	        if(GetPlayerVirtualWorld(playerid) > 200 && character_info[playerid][id] == prop_info[GetLocalIdProp(character_info[playerid][prop])][owner])
			{
		     	if(takemoney(playerid, _furniture[furniture_search(furniture[fid][model])][price], "buy furniture") == 1)
				{
					furniture[fid][cordX] = x, furniture[fid][cordY] = y, furniture[fid][cordZ] = z;
					furniture[fid][cordRX] = rx, furniture[fid][cordRY] = ry, furniture[fid][cordRZ] = rz;
					SetDynamicObjectPos(objectid, x, y, z);
					SetDynamicObjectRot(objectid, rx, ry, rz);
					character_info[playerid][editobject] = 0;
					character_info[playerid][type_editobj] = 0;
					new qu[512];
					format(qu, sizeof(qu), "INSERT INTO `furniture`(`id`, `houseid`, `model`, `posX`, `posY`, `posZ`, `posRX`, `posRY`, `posRZ`) VALUES (%d, %d, %d, %f, %f, %f, %f, %f, %f)",
					fid, furniture[fid][houseid], furniture[fid][model],
					furniture[fid][cordX], furniture[fid][cordY], furniture[fid][cordZ],
					furniture[fid][cordRX], furniture[fid][cordRY], furniture[fid][cordRZ]
					);
					//printf("%s", qu);
					//printf("[furniture_debug:%d] запрос к базе: %s", fid, qu);

					mysql_function_query(dbHandle, qu, false, "", "");
					return 1;
				}
				else 
				{
					DestroyDynamicObject(objectid);
					furniture[fid][id] = -1;
					furniture[fid][model] = -1;
					furniture[fid][houseid] = -1;

					character_info[playerid][editobject] = 0;
					character_info[playerid][type_editobj] = 0;
					if(GetPlayerVirtualWorld(playerid) <= 200 || character_info[playerid][id] != prop_info[GetLocalIdProp(character_info[playerid][prop])][owner]) return 1;
					SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас недостаточно денег!");
					//printf("[furniture_debug:%d] Недостаточно денег. id:%d ", fid, furniture[fid][id]);
				}
		    }
	    }
	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	    	new fid = GetPVarInt(playerid, "furniture_it");
			DeletePVar(playerid, "furniture_it");
	    	DestroyDynamicObject(objectid);
			furniture[fid][id] = -1;
			furniture[fid][model] = -1;
			furniture[fid][houseid] = -1;
	    	character_info[playerid][editobject] = 0;
   			character_info[playerid][type_editobj] = 0;
   			if(GetPlayerVirtualWorld(playerid) <= 200 || character_info[playerid][id] != prop_info[GetLocalIdProp(character_info[playerid][prop])][owner]) return 1;
   			//printf("[furniture_debug:%d] Отмена. id:%d ", fid, furniture[fid][id]);
			cmd_pr(playerid, "bf");
	    }
    }
	if(character_info[playerid][type_editobj] == 1)
	{
	    GetObjectPos(objectid, oldX, oldY, oldZ);
	    GetObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
	    if(response == EDIT_RESPONSE_FINAL)
	    {
	        SetDynamicObjectPos(objectid, x, y, z);
	        SetDynamicObjectRot(objectid, rx, ry, rz);
			if(!PlayerToPoint(10.0, playerid, x,y,z))
			{
				for(new i=0; i<MAX_ITEM_DROP; i++)
				{
					if(items_drop[i][id] == objectid)
					{
						items_drop[i][id] = 0;
						items_drop[i][myitem] = 0;
						DestroyDynamicObject(objectid);
						character_info[playerid][editobject] = 0;
						SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} Вы слишком далеко!");
						return 1;
					}
				}
			}
			for(new i=0; i<MAX_ITEM_DROP; i++)
			{
			    if(items_drop[i][id] == objectid)
			    {
					if(!deleteitem(playerid, items_drop[i][myitem], items_drop[i][item_count]))
					{
					   	DestroyDynamicObject(objectid);
					   	character_info[playerid][editobject] = 0;
					   	items_drop[i][myitem] = 0;
					   	items_drop[i][item_count] = 0;
					   	items_drop[i][id] = 0;
					    return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} У вас нет такого количества предмета!");
					}
			        items_drop[i][posX] = x;
			        items_drop[i][posY] = y;
			        items_drop[i][posZ] = z;
			        items_drop[i][posRX] = rx;
			        items_drop[i][posRY] = ry;
			        items_drop[i][posRZ] = rz;
			        items_drop[i][vworld] = GetPlayerVirtualWorld(playerid);
			        items_drop[i][inter] = GetPlayerInterior(playerid);
					format(items_drop[i][charactername], 25, "%s", character_info[playerid][name]);
		         	Log_Write("logs/drop_log.txt", "[%s] %s drop %s(%d) [ID: %d]", ReturnDate(), CharacterAndPlayerName(playerid), items_drop[i][myitem], items_drop[i][item_count], items_drop[i][id]);
					//printf("(%d) %s(%s) dropping %d(%d)[ID: %d]",player_info[playerid][id], CharacterAndPlayerName(playerid), items_drop[i][myitem], items_drop[i][item_count], items_drop[i][id]);
					character_info[playerid][editobject] = 0;
					cmd::bomb(playerid);
					SYS_AME(playerid, "выкидывает что-то");
					return 1;
			    }
			    else if(items_drop[i][id] == MAX_ITEM_DROP-1)
				{
				    DestroyDynamicObject(objectid);
				   	character_info[playerid][editobject] = 0;
				    return SCM(playerid, COLOR_MSGERROR, ">{FFFFFF} На сервере превышен лимит предметов на земле!");
				}
	  		}
	    }
	    if(response == EDIT_RESPONSE_CANCEL)
	    {
	    	for(new i=0; i<MAX_ITEM_DROP; i++)
			{
			    if(items_drop[i][id] == objectid)
			    {
			        items_drop[i][id] = 0;
			        items_drop[i][myitem] = 0;
			        DestroyDynamicObject(objectid);
			        character_info[playerid][editobject] = 0;
			        return 1;
		        }
	        }
	    }
    }
    return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	DeletePVar(playerid, "edit_obj");
	
	if(GetPVarInt(playerid, "faction_attach_active"))
	{
		if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
		{
			if(response == EDIT_RESPONSE_FINAL)
			{
				if(IsCop(playerid))
					attach_player(playerid, index, PoliceAttaches[GetPVarInt(playerid, "faction_attach")] , boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, true, true);
				
				if(IsMedic(playerid)) 
					attach_player(playerid, index, LSFDAttaches[GetPVarInt(playerid, "faction_attach")] , boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, true, true);
			}
			else 
				ResetAttach(playerid, index);
			
			DeletePVar(playerid, "faction_attach");
			DeletePVar(playerid, "faction_attach_active");
			return 1;
		}
	}
	else if(GetPVarInt(playerid, "change_gunattach"))
	{
		if(response == EDIT_RESPONSE_FINAL)
		{
			SetPlayerAttachedObject(playerid, index, modelid, boneid, fOffsetX, fOffsetY, fOffsetZ, fRotX,fRotY,fRotZ);
		
			SetPVarInt(playerid, "gunpos_bone", boneid);
			
			SetPVarFloat(playerid, "gunpos_1", fOffsetX);
			SetPVarFloat(playerid, "gunpos_2", fOffsetY);
			SetPVarFloat(playerid, "gunpos_3", fOffsetZ);
			
			SetPVarFloat(playerid, "gunpos_4", fRotX);
			SetPVarFloat(playerid, "gunpos_5", fRotY);
			SetPVarFloat(playerid, "gunpos_6", fRotZ);

			//DeletePVar(playerid, "attach_bone");
			DeletePVar(playerid, "change_gunattach");
			return 1;
		}
		else if(response == EDIT_RESPONSE_CANCEL)
		{
			//DeletePVar(playerid, "attach_bone");
			DeletePVar(playerid, "change_gunattach");
			SetPlayerAttachedObject(playerid, MAX_ATTACH+1, modelid, 6);
			return 1;
		}
	}
	else
	{
		if(response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
		{
			if(attach_player(playerid, index, GetPVarInt(playerid, "attach_itemid"), GetPVarInt(playerid, "attach_bone"), fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ))
			{
				if(index == 0) 
				SCM(playerid, COLOR_MSGSERVER, ">{FFFFFF} Вы прикрепили предмет к персонажу.");
				
				UpdatePlayerColor(playerid);
			}
			DeletePVar(playerid, "attach_edit");
		}
	}
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ) {
	if(IsAdmin(playerid, 2, true)) return 1;
    SetPlayerPos(playerid, fX, fY, fZ);
	SetPlayerVw(playerid, 0);
	SetPlayerInt(playerid, 0);
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{	

	SetPVarInt(playerid, "AREAID", areaid);	
	for(new i; i<MAX_PROP; i++)
	{
		if(prop_info[i][PropZone] == areaid)
		{
			new str[180];
			if(strlen(prop_info[i][Name]) > 1) 
			{
				format(str, sizeof(str), "> %s", prop_info[i][Name]);
				SCM(playerid, COLOR_GREEN, str);
			}

			format(str, sizeof(str), "%s №%d",property[prop_info[i][type]], prop_info[i][id]);

			if(prop_info[i][owner] == 0 && prop_info[i][type] != 7) format(str, sizeof(str), "%s. Стоимость: %d$. Введите /buyprop для покупки!",str, prop_info[i][price]);
			else format(str, sizeof(str), "%s. Нажмите 'F' чтобы войти!",str);

			//if(prop_info[i][enter_price] > 0 && prop_info[i][owner] != 0) format(str, sizeof(str), "%s. Стоимость входа: %d$",str, prop_info[i][enter_price]);

			SCM(playerid, COLOR_GREEN, str);
			DestroyCheckpoint(playerid);
			SetPlayerCheckpoint(playerid, prop_info[i][posX],prop_info[i][posY],prop_info[i][posZ], 1.0);
			SetPVarInt(playerid, "checkpoint_prop", 1);
			return 1;
		}
	}

	foreach(new i : Player)
	{
	    if(GetPVarType(i, "BBArea"))
	    {
	        if(areaid == GetPVarInt(i, "BBArea"))
	        {
	            new station[256];
	            GetPVarString(i, "BBStation", station, sizeof(station));
	            if(!isnull(station))
				{
					PlayStream(playerid, station, GetPVarFloat(i, "BBX"), GetPVarFloat(i, "BBY"), GetPVarFloat(i, "BBZ"), 30.0, 1);
	            }
				return 1;
	        }
	    }
	}
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{			
	if(GetPVarInt(playerid, "checkpoint_prop")) DestroyCheckpoint(playerid);
    foreach(new i : Player)
	{
	    if(GetPVarType(i, "BBArea"))
	    {
	        if(areaid == GetPVarInt(i, "BBArea"))
	        {
	            StopStream(playerid);
				return 1;
	        }
	    }
	}
	return 1;
}

stock IsWeapon(itemid)
{
	switch(itemid)
	{
		case 2..14, 19..24, 34..45: return true;
	}
	return false;
}

stock IsWeaponKill(itemid)
{
    switch(itemid)
	{
		case 4, 8, 9,15, 22..38: return true;
	}
	return false;
}

stock IsWeaponKnock(itemid)
{
    switch(itemid)
	{
		case 0..3,5..7,10..14: return true;
	}
	return false;
}