#pragma once

/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

#include <string_view>

// This is just a placeholder for some real world weather lookup API.  We aren't going to bother
// with a full implementation as this class merely serves as an example of real-world usage.  It
// isn't important to demonstrating the open.mp component SDK.
class SomeExternalAPI
{
private:
	// 10 possibilities:
	int currentWeather_ = 0;

public:
	// Initialise this API to find the weather in a real-world location.
	SomeExternalAPI(std::string_view location);

	// Not `const` because we may get a new weather.
	int getCurrentWeather();
};
