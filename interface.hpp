#pragma once

/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// This file should go somewhere like `<SDK>`, where other components can see it.

// Required for most of open.mp.
#include <sdk.hpp>

enum class E_WEATHER
{
	SUNNY,
	RAINING,
	WINDY,
	SNOWING,
	SLEET,
	CLOUDY,
	HOT,
	FOGGY,
	STORMY,
	DRIZZLING,
};

// This is just a generic container, it doesn't inherit from anything.  For most components this
// represents the most important part - the entity that the component manages.  Be it objects,
// checkpoints, text draws, or weather regions.
struct IWeatherRegion
{
	virtual StringView getName() = 0;

	virtual StringView getLocation() = 0;

	virtual bool weatherChanged() = 0;

	virtual E_WEATHER getWeather() = 0;

	virtual int getID() const = 0;
};

// If this data is to be used in other components only share an ABI stable base class.
struct IWeatherExtension : IExtension
{
	// Visit https://open.mp/uid to generate a new unique ID (different to the component UID).
	PROVIDE_EXT_UID(5/* UID GOES HERE */);

	// Public methods to get and set this player's weather region.
	virtual IWeatherRegion* getWeatherRegion() = 0;

	virtual void setWeatherRegion(IWeatherRegion*) = 0;
};

// If this data is to be used in other components only share an ABI stable base class.
struct IWeatherComponent : IComponent
{
	// Visit https://open.mp/uid to generate a new unique ID (different to the extension UID).
	PROVIDE_UID(6/* UID GOES HERE */);

	// Public methods to get and set this player's weather region.
	virtual IWeatherRegion* createWeatherRegion(StringView name, StringView location) = 0;

	// Public methods to get and set this player's weather region.
	virtual bool destroyWeatherRegion(IWeatherRegion* region) = 0;

	// Look up a region by name.
	virtual IWeatherRegion* getWeatherRegion(StringView name) = 0;

	// Look up a region by name.
	virtual IWeatherRegion* getWeatherRegion(int id) = 0;
};

// If other components want to subscribe to our weather event they must implement this interface.
struct WeatherEventHandler
{
	// There's only one event - that triggered when the weather in a region changes.
	virtual void onWeatherChange(IWeatherRegion* where, E_WEATHER oldWeather, E_WEATHER newWeather) = 0;
};
