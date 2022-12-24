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
using Impl;

	// Implementations of the various methods from the public API.
StringView WeatherRegion::getName()
{
	return name_;
}

StringView WeatherRegion::getLocation()
{
	return location_;
}
	
bool WeatherRegion::weatherChanged()
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
	
E_WEATHER WeatherRegion::getWeather()
{
	// Get the last weather retreived from the real world weather API.
	return reinterpret_cast<E_WEATHER>(currentWeather_);
}
	
int WeatherRegion::getID() const
{
	// The pool ID is set automatically in `PoolIDProvider`.
	return poolID;
}

// More methods to be used only in this component (internal methods).  Implementation details.
WeatherRegion::WeatherRegion(int id, StringView name, StringView location)
	: api_()
	, id_(id)
	, currentWeather_(0)
	, name_(name)
	, location_(location)
{
}
