/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#if defined _INC_real_world_weather
	#endinput
#endif
#define _INC_real_world_weather

/**
 * <library name="real-world-weather" summary="Include for the real world weather example component">
 *   <license>
 *     (c) Copyright 2022, open.mp team.
 *   </license>
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#pragma tabsize 4

/// <p/>
/**
 * <library>real-world-weather</library>
 * <summary>Weather types</summary>
 */
enum E_WEATHER:E_WEATHER__
{
	E_WEATHER_UNKNOWN,
	E_WEATHER_SUNNY,
	E_WEATHER_RAINING,
	E_WEATHER_WINDY,
	E_WEATHER_SNOWING,
	E_WEATHER_SLEET,
	E_WEATHER_CLOUDY,
	E_WEATHER_HOT,
	E_WEATHER_FOGGY,
	E_WEATHER_STORMY,
	E_WEATHER_DRIZZLING
}
static stock E_WEATHER:_@E_WEATHER() { return E_WEATHER__; }

/**
 * <library>real-world-weather</library>
 * <summary>Create a region for real-world weather.</summary>
 * <param name="name">The name of the region.</param>
 * <param name="location">The real-world location this region mirrors.</param>
 * <remarks>Creates a weather region whose weather matches that of a given real-world location.</remarks>
 * <returns>
 *   <b><c>0</c></b> - The region was not created.<br />
 *   <b><c>n</c></b> - The ID of the created region.
 * </returns>
 */
native RWW:RWW_Create(const name[], const location[]);

/**
 * <library>real-world-weather</library>
 * <summary>Destroy a region for real-world weather.</summary>
 * <param name="region">The ID of the region to destroy.</param>
 * <returns>Did this region exist?</returns>
 */
native bool:RWW_Destroy(RWW:region);

/**
 * <library>real-world-weather</library>
 * <summary>Get the real-world weather.</summary>
 * <param name="region">The ID of the region to check.</param>
 * <returns>Does this region exist?</returns>
 */
native bool:RWW_IsValid(RWW:region);

/**
 * <library>real-world-weather</library>
 * <summary>Get the real-world weather.</summary>
 * <param name="region">The ID of the region to get the weather of.</param>
 * <returns>The weather currently in this region.</returns>
 */
native E_WEATHER:RWW_GetWeather(RWW:region);

/**
 * <library>real-world-weather</library>
 * <summary>Get the name of a real-world weather.</summary>
 * <param name="region">The ID of the region to get the name of.</param>
 * <param name="name">The return value for the name of the region.</param>
 * <param name="size">The size of the return array.</param>
 * <returns>Does this region exist?</returns>
 */
native bool:RWW_GetName(RWW:region, name[], size = sizeof (name));

/**
 * <library>real-world-weather</library>
 * <summary>Get the location of a real-world weather.</summary>
 * <param name="region">The ID of the region to get the location of.</param>
 * <param name="location">The return value for the real-world location this region mirrors.</param>
 * <param name="size">The size of the return array.</param>
 * <returns>Does this region exist?</returns>
 */
native bool:RWW_GetLocation(RWW:region, location[], size = sizeof (location));

/**
 * <library>real-world-weather</library>
 * <param name="region">The ID of the region that changed.</param>
 * <param name="previous">The old weather in this region.</param>
 * <param name="current">The new weather in this region.</param>
 * <summary>This callback is triggered when the weather changes.</summary>
 * <remarks>This is called every time the weather in a real-world location changes.  It can be
 * used to update the in-game weather for players.</remarks>
 */
forward OnWeatherChange(RWW:region, E_WEATHER:previous, E_WEATHER:current);

