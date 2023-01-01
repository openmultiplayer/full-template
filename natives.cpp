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

// To get the component.
#include "weather-component.hpp"

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
