/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include <cstdlib>

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
