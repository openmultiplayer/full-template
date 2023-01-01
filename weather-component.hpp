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

// Import the pawn event.
#include <Server/Components/Pawn/pawn.hpp>

// The code to manage a "pool" (array/collection) of "entities" (things).
#include <Impl/pool_impl.hpp>

// Include the entity's definition.
#include "weather-region.hpp"

// Import open.mp structures that aren't ABI safe.
using namespace Impl;

// `final` so we don't need virtual destructors.  Also because we know it isn't inherited.
class WeatherComponent final
	// This class is an implementation of the publicly shared `IWeatherComponent` interface.
	: public IWeatherComponent
	// The implementation includes player connection events to know when new players join.
	, public PlayerConnectEventHandler
	// The implementation includes pawn script events to know when new scripts load.
	, public PawnEventHandler
	// The implementation includes server tick events to periodically check for weather updates.
	, public CoreEventHandler
{
private:
	// Hold a reference to the main server core.
	ICore* core_ = nullptr;

	// We use the pawn componet to add and remove script load listeners.
	IPawnComponent* pawn_;

	// This is a "pool" - it holds a list of "entities".
	MarkedPoolStorage<WeatherRegion, IWeatherRegion, 1, 1000> pool_;

	// The next time to update region's weather.
	TimePoint nextUpdate_ = TimePoint::min();

public:
	// Implementations of the various methods from the public API.
	IWeatherRegion* createWeatherRegion(StringView name, StringView location) override;
	
	bool destroyWeatherRegion(IWeatherRegion* region) override;
	
	IWeatherRegion* getWeatherRegion(StringView name) override;

	IWeatherRegion* getWeatherRegion(int id) override;

	// Required component methods.
	StringView componentName() const override;

	SemanticVersion componentVersion() const override;

	void onLoad(ICore* c) override;

	void onInit(IComponentList* components) override;

	void onReady() override;

	void onFree(IComponent* component) override;

	void free() override;

	void reset() override;
	
	// Connect event methods.
	void onPlayerConnect(IPlayer& player) override;
	
	// Pawn event methods.
	void onAmxLoad(IPawnScript& script) override;

	void onAmxUnload(IPawnScript& script) override;

	// Update event methods.
	void onTick(Microseconds elapsed, TimePoint now) override;
	
	// More methods to be used only in this component, with more implementation details knowledge.

	// When this component is destroyed we need to tell any linked components this it is gone.
	~WeatherComponent();
};
