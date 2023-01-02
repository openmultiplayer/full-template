#pragma once

/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Include pawn-natives macros (`SCRIPT_API`) and lookups (`IPlayer&`).
#include <Server/Components/Pawn/pawn_natives.hpp>

// To get the component.
#include "weather-component.hpp"

// Various methods of lookup up a parameter by ID to return a pointer to the native.
namespace pawn_natives
{
template <>
struct ParamLookup<IWeatherRegion>
{
	static IWeatherRegion& ValReq(cell ref)
	{
		if (auto pool = WeatherComponent::getInstance())
		{
			auto ptr = pool->getWeatherRegion(ref);
			if (ptr)
			{
				return *ptr;
			}
		}
		throw pawn_natives::ParamCastFailure();
	}

	static IWeatherRegion* Val(cell ref) noexcept
	{
		if (auto pool = WeatherComponent::getInstance())
		{
			return pool->getWeatherRegion(ref);
		}
		return nullptr;
	}
};

template <>
class ParamCast<IWeatherRegion*>
{
public:
	ParamCast(AMX* amx, cell* params, int idx) noexcept
	{
		value_ = ParamLookup<IWeatherRegion>::Val(params[idx]);
	}

	~ParamCast()
	{
	}

	ParamCast(ParamCast<IWeatherRegion*> const&) = delete;
	ParamCast(ParamCast<IWeatherRegion*>&&) = delete;

	operator IWeatherRegion* ()
	{
		return value_;
	}

	static constexpr int Size = 1;

private:
	IWeatherRegion* value_;
};

template <>
class ParamCast<IWeatherRegion&>
{
public:
	ParamCast(AMX* amx, cell* params, int idx)
		: value_(ParamLookup<IWeatherRegion>::ValReq(params[idx]))
	{
	}

	~ParamCast()
	{
	}

	ParamCast(ParamCast<IWeatherRegion&> const&) = delete;
	ParamCast(ParamCast<IWeatherRegion&>&&) = delete;

	operator IWeatherRegion& ()
	{
		return value_;
	}

	static constexpr int Size = 1;

private:
	IWeatherRegion& value_;
};

template <>
class ParamCast<const IWeatherRegion&>
{
public:
	ParamCast(AMX*, cell*, int) = delete;
	ParamCast() = delete;
};
}

