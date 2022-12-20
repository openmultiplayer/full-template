/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Required for most of open.mp.
#include <sdk.hpp>

// Include the pawn component information.
#include <Server/Components/Pawn/pawn.hpp>

// Include pawn-natives macros (`SCRIPT_API`) and lookups (`IPlayer&`).
#include <Server/Components/Pawn/pawn_natives.hpp>

// Include the globally shared definitions for this component.
#include "interface.hpp"

// `SCRIPT_API` is an enhanced wrapper around the old *pawn-natives* system:
//
//   https://github.com/Y-Less/pawn-natives
//
// `IPlayer` is a reference to a player already resolved from a `playerid` in the calling pawn code.
// Many components define lookups to convert from IDs to direct references to their entity
// instances, and players, arrays, strings, and more are all handled by default (including return
// values).  This saves all the old native boilerplate required for converting to and from the
// `params` array.
SCRIPT_API(SetPawnData, bool(IPlayer& player, int value))
{
	// Try get a reference to this player's custom data.
	if (auto* data = queryExtension<IPawnExtension>(player))
	{
		// Call a method on the extension.
		data->setData(value);
		return true;
	}
	// Natives return `0`/`false` by default if parameter lookups fail.
	return false;
}

// Note that `amx` and `params` are still available in these natives via `GetAMX` and `GetParams`
// and may be needed for vararg functions like `format` or `SetTimerEx`.
SCRIPT_API(GetPawnData, int(IPlayer& player))
{
	// Try get a reference to this player's custom data.
	if (auto* data = queryExtension<IPawnExtension>(player))
	{
		// Within this component we can use the private API as well.
		return reinterpret_cast<PawnExtension*>(data)->getData();
	}
	return 0;
}
