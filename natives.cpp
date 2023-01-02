/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Required for most of open.mp.
#include <sdk.hpp>

// Include the globally shared definitions for this component.
#include "interface.hpp"

// Contains wrappers for pool lookups from IDs.
#include "natives.hpp"

// `SCRIPT_API` is an enhanced wrapper around the old *pawn-natives* system:
//
//   https://github.com/Y-Less/pawn-natives
//
SCRIPT_API(RWW_Create, int(String const& name, String const& location))
{
	// Try get a reference to the controlling component.
	if (auto rww = WeatherComponent::getInstance())
	{
		// Call a method on the component.
		if (auto ret = rww->createWeatherRegion(name, location))
		{
			// Pawn wants the ID, not the pointer.
			return ret->getID();
		}
	}
	// Natives return `0`/`false` by default if parameter lookups fail.
	return 0;
}

SCRIPT_API(RWW_Destroy, bool(IWeatherRegion& region))
{
	// Try get a reference to the controlling component.
	if (auto rww = WeatherComponent::getInstance())
	{
		rww->destroyWeatherRegion(&region);
		// Using the region here is use-after-free.
		return true;
	}
	return false;
}

// `IWeatherRegion&` calls the parameter lookup from ID and can auto-fail.
SCRIPT_API(RWW_GetName, bool(IWeatherRegion& region, OutputOnlyString& name))
{
	name = region.getName();
	// Natives return `0`/`false` by default if parameter lookups fail.
	return true;
}

// `OutputOnlyString` translates in pawn to a `string/length` pair.
SCRIPT_API(RWW_GetLocation, bool(IWeatherRegion& region, OutputOnlyString& name))
{
	name = region.getLocation();
	// Natives return `0`/`false` by default if parameter lookups fail.
	return true;
}

// Look up the ID, if it doesn't fail the function will be called.
SCRIPT_API(RWW_IsValid, bool(IWeatherRegion&))
{
	// Merely calling this function is enough to validate the region ID exists.
	return true;
}

SCRIPT_API(RWW_GetWeather, int(IWeatherRegion& region))
{
	return static_cast<int>(region.getWeather());
}

// `IPlayer&` lookup is in-built.
SCRIPT_API(RWW_SetPlayerRegion, bool(IPlayer& player, IWeatherRegion& region))
{
	// Get the extension data for this player, created when they connected.
	if (auto data = queryExtension<IWeatherExtension>(player))
	{
		data->setWeatherRegion(&region);
		// Player, extension data, and region all exist.
		return true;
	}
	// Extension data doesn't exist, failed to set the region.
	return false;
}

// Most SDK functions return pointers/references.  Here we convert it to an ID.
SCRIPT_API(RWW_GetPlayerRegion, int(IPlayer& player))
{
	// Get the extension data for this player, created when they connected.
	if (auto data = queryExtension<IWeatherExtension>(player))
	{
		// Get their region if they are in one.
		if (auto region = data->getWeatherRegion())
		{
			return region->getID();
		}
	}
	return 0;
}
