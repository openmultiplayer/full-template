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

// This is the private implementation of the public interface.  We must know the interface.
#include "interface.hpp"

// Import open.mp structures that aren't ABI safe.
using namespace Impl;

// If this data is to be used in other components only share an ABI stable base class.
class WeatherExtension final
	// This class is an implementation of the publicly shared `IWeatherExtension` interface.
	: public IWeatherExtension
{
private:
	IWeatherRegion* region_;

public:
	// Implementations of the various methods from the public API.
	IWeatherRegion* getWeatherRegion() override;
	
	void setWeatherRegion(IWeatherRegion* region) override;

	// Required extension methods.
	void freeExtension() override;

	void reset() override;

	// Component-private methods (internal methods) go here.
};
