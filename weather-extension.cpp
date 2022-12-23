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

// If this data is to be used in other components only share an ABI stable base class.
class WeatherExtension final
	// This class is an implementation of the publicly shared `IWeatherExtension` interface.
	: public IWeatherExtension
{
private:
	IWeatherRegion* region_;

public:
	// Implementations of the various methods from the public API.
	IWeatherRegion* getWeatherRegion() override
	{
		// Get the player's current weather region.
		return region_;
	}
	
	void setWeatherRegion(IWeatherRegion* region) override
	{
		// Get the player's current weather region.
		region_ = region;
	}

	// Required extension methods.
	void freeExtension() override
	{
		// Delete this extension.
		delete this;
	}

	void reset() override
	{
		// Reset data when the main mode changes.
		region_ = nullptr;
	}

	// Component-private methods (internal methods) go here.
};
