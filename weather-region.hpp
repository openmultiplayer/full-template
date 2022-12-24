#pragma once

/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Required for most of open.mp.
#include <sdk.hpp>

// Get pool ID information.
#include <Impl/pool_impl.hpp>

// This is the private implementation of the public interface.  We must know the interface.
#include "interface.hpp"

// This entity holds server data, but must use an external service for weather reporting.
#include "api.hpp"


// Import open.mp structures that aren't ABI safe.
using namespace Impl;

class WeatherRegion final
	// This class is an implementation of the publicly shared `IWeatherRegion` interface.
	: public IWeatherRegion
	// This is stored in a pool, so needs a standard pool ID.
	, public PoolIDProvider
	// Ensure this entity can't be copied without our help.
	, public NoCopy
{
private:
	WeatherAPI api_;
	
	int currentWeather_;
	String name_;
	String location_;

public:
	// Implementations of the various methods from the public API.
	StringView getName() override;

	StringView getLocation() override;
	
	bool weatherChanged() override;
	
	E_WEATHER getWeather() override;
	
	int getID() const override;

	// More methods to be used only in this component (internal methods).  Implementation details.
	WeatherRegion(StringView name, StringView location);
};
