/*****************************************************************************
*****Extra Iters for FOREACH[vehicles,objects....and more]********************
******************* And some Useful Functions*********************************


Current version--  1.0  [First version]


So this script contans extra iterates for foreach made by Y_Less

The name Iters Added thorugh this include are--

Objects                  ||| Contains all objects id's create via function CreateObject
DynamicObjects           ||| Contains all objects id's create via function CreateDynamicObject
Vehicles                 ||| Contains all vehicle id's create via function CreateVehicle/AddStaticVehicle/AddStaticVehicleEx
StaticVehicle            ||| Contains all vehicle id's create via function AddStaticVehicle/AddStaticVehicleEx

These can be easily used in foreach like the follwoing examples--

foreach(new i : Vehicles){}
foreach(new o: Objects){}
........and so on for hte others

====================NATIVES [ FUNCTIONS ]=====================
GetTotalObjects()  -- Returns the total number of objects in server

GetTotalVehicles()  -- Return the total number of vehicles in server

GetTotalStaticVehicles()  -- Return the total number of static vehicle in server @@ Note this is same as the number of vehicle models created that apper on server console when server is started

GetTotalDynamicObjects()  -- Returns the total number of Dynamic objects in server

IsStaticVehicle(vehicleid)  -- Retruns true if vehicleid was created via function AddStaticVehicle/AddStaticVehicleEx on GameModeInit and false if it was not


CREDTS---

SAMP TEAM for creating SAMP,
Y_Less for foreach include,
and guess me too?

************************************************************************************/


#if defined _extra_iter_included
    #endinput
#endif

#define _extra_iter_included

#include <a_samp>
#include <foreach>
#include <streamer>

#define MAX_DYNAMIC 20000


new
    Iterator:Objects<MAX_OBJECTS>,
    Iterator:DynamicObjects<MAX_DYNAMIC>,
    Iterator:Vehicles<MAX_VEHICLES>,
    Iterator:StaticVehicle<MAX_VEHICLES>;
    

    

stock ffCreateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0)
{
new id;
id = CreateObject(modelid, X, Y, Z, rX, rY, rZ, DrawDistance);
Iter_Add(Objects, id);
return id;
}


stock ffCreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, respawn_delay)
{
new id;
id = CreateVehicle(modelid, x, y, z, angle, color1, color2, respawn_delay);
if(id != INVALID_VEHICLE_ID)
Iter_Add(Vehicles, id);
return id;
}


stock ffAddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2)
{
new id;
id = AddStaticVehicle(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2);
if(id != INVALID_VEHICLE_ID)
  {
   Iter_Add(Vehicles, id);
   Iter_Add(StaticVehicle, id);
  }
return id;
}




stock ffAddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:angle, color1, color2, respawn_delay)
{
new id;
id = AddStaticVehicleEx(modelid, spawn_x, spawn_y, spawn_z, angle, color1, color2, respawn_delay);
if(id != INVALID_VEHICLE_ID)
  {
   Iter_Add(Vehicles, id);
   Iter_Add(StaticVehicle, id);
  }
return id;
}



stock ffDestroyVehicle(vehicleid)
{
new id = DestroyVehicle(vehicleid);
if(id == 1)
Iter_remove(Vehicles, vehicleid);
if(Iter_Contains(StaticVehicle, vehicleid))Iter_Remove(StaticVehicle, vehicleid)
return id;
}


stock ffDestroyObject(objectid)
{
new id = DestroyObject(objectid);
if(Iter_Contains(Objects, objectid))
Iter_Remove(Objects, objectid);
return id;
}

stock ffCreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = 200.0, Float:drawdistance = 0.0)
{
new id;
id = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, interiorid ,playerid, streamdistanc, drawdistance);
IterAdd(DynamicObjects, id);
return id;
}

stock ffDestroyDynamicObject(objectid)
{
if(Iter_Contains(DynamicObjects, objectid))Iter_Remove(DynamicObjects, objectid);
return DestroyDynamicObject(objectid);
}


//=======================ADDITIONAL FUNCTIONS=================
//************************************************************
/*
native GetTotalObjects();
native GetTotalVehicles();
native GetTotalStaticVehicles();
native GetTotalDynamicObjects();
native IsStaticVehicle(vehicleid);
*/


stock IsStaticVehicle(vehicleid)
{
return Iter_Contains(StaticVehicle, vehicleid);
}

stock GetTotalVehicles()
{
return Iter_Count(Vehicles);
}


stock GetTotalDynamicObjects()
{
return Iter_Count(DynamicObjects);
}



stock GetTotalObjects()
{
return Iter_Count(Objects);
}


stock GetTotalStaticVehicles()
{
return Iter_Count(StaticVehicle);
}



#if defined _ALS_CreateObject
  #undef CreateObject
#else
#define _ALS_CreateObject
#endif


#if defined _ALS_DestroyObject
  #undef DestroyObject
#else
#define _ALS_DestroyObject
#endif


#if defined _ALS_AddStaticVehicle
  #undef AddStaticVehicle
#else
#define _ALS_AddStaticVehicle
#endif


#if defined _ALS_AddStaticVehicleEx
  #undef AddStaticVehicleEx
#else
#define _ALS_AddStaticVehicleEx
#endif



#if defined _ALS_DestroyVehicle
  #undef DestroyVehicle
#else
#define _ALS_DestroyVehicle
#endif


#if defined _ALS_DestroyDynamicObject
  #undef DestroyDynamicObject
#else
#define _ALS_DestroyDynamicObject
#endif


#if defined _ALS_CreateDynamicObject
  #undef CreateDynamicObject
#else
#define _ALS_CreateDynamicObject
#endif


#if defined _ALS_CreateVehicle
  #undef CreateVehicle
#else
#define _ALS_CreateVehicle
#endif








#define CreateObject ffCreateObject
#define CreateDynamicObject ffCreateDynamicObject
#define CreateVehicle ffCreateVehicle
#define AddStaticVehicle ffAddStaticVehicle
#define AddStaticVehicleEx ffAddStaticVehicleEx
#define DestroyVehicle ffDestroyVehicle
#define DestroyDynamicObject ffDestroyDynamicObject
#define DestroyVehicle ffDestroyVehicle