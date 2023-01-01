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

// Include the binary-local implementation for this component.
#include "weather-component.hpp"

// Automatically called when the compiled binary is loaded.
COMPONENT_ENTRY_POINT()
{
	return WeatherComponent::getInstance();
}
