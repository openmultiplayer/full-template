/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// This is the private implementation of the public interface.  We must know the interface.
#include "weather-extension.hpp"

// Implementations of the various methods from the public API.
IWeatherRegion* WeatherExtension::getWeatherRegion()
{
	// Get the player's current weather region.
	return region_;
}
	
void WeatherExtension::setWeatherRegion(IWeatherRegion* region)
{
	// Get the player's current weather region.
	region_ = region;
}

// Required extension methods.
void WeatherExtension::freeExtension()
{
	// Delete this extension.
	delete this;
}

void WeatherExtension::reset()
{
	// Reset data when the main mode changes.
	region_ = nullptr;
}

