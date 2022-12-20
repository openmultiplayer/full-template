/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Required for most of open.mp.
#include <sdk.hpp>

// If this data is to be used in other components only share an ABI stable base class.
struct IPawnExtension : IExtension
{
	// Visit https://open.mp/uid to generate a new unique ID (different to the component UID).
	PROVIDE_EXT_UID(/* UID GOES HERE */);

	// Just one example public method.
	virtual void setData(int value) = 0;
};
