#include <a_samp>
#include <streamer>


public OnFilterScriptInit()
{
	DestroyObject(196);
	DestroyObject(198);
	DestroyObject(201);
	DestroyObject(206);
	DestroyObject(204);
	DestroyObject(192);
	return 1;
}

public OnFilterScriptExit()
{
	return 1;
}
