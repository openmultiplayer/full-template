/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Required for most of open.mp.
#include <sdk.hpp>

// This is the private implementation of the public interface.  We must know the interface.
#include "interface.hpp"

// This entity holds server data, but must use an external service for weather reporting.
#include "weather-api.hpp"

// Import open.mp structures that aren't ABI safe.
using Impl;

class WeatherRegion final
	// This class is an implementation of the publicly shared `IWeatherRegion` interface.
	: public IWeatherRegion
{
private:
	WeatherAPI api_;
	
	int const id_;
	int currentWeather_;
	String name_;
	String location_;

public:
	// Implementations of the various methods from the public API.
	StringView getName() override
	{
		return name_;
	}

	StringView getLocation() override
	{
		return location_;
	}
	
	bool weatherChanged() override
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
	
	E_WEATHER getWeather() override
	{
		// Get the last weather retreived from the real world weather API.
		return reinterpret_cast<E_WEATHER>(currentWeather_);
	}

	// More methods to be used only in this component (internal methods).  Implementation details.
	WeatherRegion(int id, String name, String location)
		: api_()
		, id_(id)
		, currentWeather_(0)
		, name_(name)
		, location_(location)
	{
	}
	
	int getID() const
	{
		// Get the internal ID for this region, used to reference it in pawn.
		return id_;
	}
};
