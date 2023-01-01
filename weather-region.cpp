/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// This is the private implementation of the public interface.  We must know the interface.
#include "weather-region.hpp"

// Import open.mp structures that aren't ABI safe.
using namespace Impl;

	// Implementations of the various methods from the public API.
StringView WeatherRegion::getName() const
{
	return name_;
}

StringView WeatherRegion::getLocation() const
{
	return location_;
}

bool WeatherRegion::updateWeather()
{
	// Call the API to get the latest weather in this region.
	int weather = api_.getCurrentWeather();

	// Has the weather changed?
	if (weather != currentWeather_)
	{
		// Yes, record the new one.
		currentWeather_ = weather;
		return true;
	}
	return false;
}
	
E_WEATHER WeatherRegion::getWeather() const
{
	// Convert the weather type retreived from the real world weather API.
	switch (currentWeather_)
	{
	case 0:
		return E_WEATHER::SUNNY;
	case 1:
		return E_WEATHER::WINDY;
	case 2:
		return E_WEATHER::STORMY;
	case 3:
		return E_WEATHER::SNOWING;
	case 4:
		return E_WEATHER::HOT;
	case 5:
		return E_WEATHER::SLEET;
	case 6:
		return E_WEATHER::CLOUDY;
	case 7:
		return E_WEATHER::RAINING;
	case 8:
		return E_WEATHER::DRIZZLING;
	case 9:
		return E_WEATHER::FOGGY;
	}
	return E_WEATHER::UNKNOWN;
}
	
int WeatherRegion::getID() const
{
	// The pool ID is set automatically in `PoolIDProvider`.
	return poolID;
}

// More methods to be used only in this component (internal methods).  Implementation details.
WeatherRegion::WeatherRegion(StringView name, StringView location)
	: api_()
	, currentWeather_(0)
	, name_(name)
	, location_(location)
{
}
