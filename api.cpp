/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include <cstdlib>

#include "api.hpp"

SomeExternalAPI::SomeExternalAPI(std::string)
{
	// We don't actually care about the location for this example...
}

 // This is just a placeholder for some real world weather lookup API.  We aren't going to bother
 // with a full implementation as this class merely serves as an example of real-world usage.  It
 // isn't important to demonstrating the open.mp component SDK.
int SomeExternalAPI::getCurrentWeather()
{
	// 1% chance of randomly selecting a new weather.
	if (rand() % 100 == 0)
	{
		// I'm not using `<random>`...
		currentWeather_ = rand() % 10;
	}
	return currentWeather_;
}
