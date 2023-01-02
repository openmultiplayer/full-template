#include <open.mp>
#include <real-world-weather>

new RWW:gRegionLV;
new RWW:gRegionLS;
new RWW:gRegionSF;

public OnFilterScriptInit()
{
	gRegionLV = RWW_Create("Las Venturas", "America/Las Vegas");
	if (RWW_IsValid(gRegionLV))
	{
		new name[32], location[32];
		RWW_GetName(gRegionLV, name);
		RWW_GetLocation(gRegionLV, location);
		printf("%d = %s (%s)", _:gRegionLV, name, location);
	}
	else
	{
		printf("Failed to create LV region");
	}
	if (!(gRegionLS = RWW_Create("Los Santos", "America/Los Angeles")))
	{
		printf("Failed to create LV region");
	}
	gRegionSF = RWW_Create("San Fierro", "America/San Fransisco");
	if (gRegionSF == INVALID_RWW_REGION)
	{
		printf("Failed to create SF region");
	}

	return 1;
}

public OnFilterScriptExit()
{
	RWW_Destroy(gRegionLV);
	RWW_Destroy(gRegionLS);
	RWW_Destroy(gRegionSF);
	return 1;
}

SetPlayerRealWeather(playerid, E_WEATHER:weather)
{
	switch (weather)
	{
	case E_WEATHER_SUNNY, E_WEATHER_HOT:
		SetPlayerWeather(playerid, 11);
	case E_WEATHER_RAINING, E_WEATHER_STORMY, E_WEATHER_DRIZZLING:
		SetPlayerWeather(playerid, 8);
	case E_WEATHER_WINDY, E_WEATHER_CLOUDY, E_WEATHER_FOGGY:
		SetPlayerWeather(playerid, 12);
	case E_WEATHER_SNOWING, E_WEATHER_SLEET:
		SetPlayerWeather(playerid, 19);
	default:
		return;
	}
}

DeterminePlayerRegion(playerid)
{
	// Somehow.  Doesn't matter.
	switch (random(3))
	{
	case 0:
		RWW_SetPlayerRegion(playerid, gRegionLV);
	case 1:
		RWW_SetPlayerRegion(playerid, gRegionLS);
	case 2:
		RWW_SetPlayerRegion(playerid, gRegionSF);
	}
}

public OnPlayerSpawn(playerid)
{
	DeterminePlayerRegion(playerid);
	SetPlayerRealWeather(playerid, RWW_GetWeather(RWW_GetPlayerRegion(playerid)));
	return 0;
}

public OnWeatherChange(RWW:region, E_WEATHER:previous, E_WEATHER:current)
{
	new name[32], from[32], to[32];
	RWW_GetName(region, name);
	RWW_GetDescription(previous, from);
	RWW_GetDescription(current, to);
	printf("Region %s changed weather from %s to %s", name, from, to);
	return 1;
}

