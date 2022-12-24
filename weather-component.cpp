/*
 *  This Source Code Form is subject to the terms of the Mozilla Public License,
 *  v. 2.0. If a copy of the MPL was not distributed with this file, You can
 *  obtain one at http://mozilla.org/MPL/2.0/.
 *
 *  The original code is copyright (c) 2022, open.mp team and contributors.
 */

// Include pawn-natives macros (`SCRIPT_API`) and lookups (`IPlayer&`).
#include <Server/Components/Pawn/pawn_natives.hpp>

// Include a few function implementations.  Should only be included once.
#include <Server/Components/Pawn/pawn_impl.hpp>

// Include the component's definition.
#include "weather-component.hpp"

// Include the entity's definition.
#include "weather-region.hpp"

// Include the player data's definition.
#include "weather-extension.hpp"

// Implementations of the various methods from the public API.
IWeatherRegion* WeatherComponent::createWeatherRegion(StringView name, StringView location)
{
	return nullptr;
}
	
void WeatherComponent::destroyWeatherRegion(IWeatherRegion*)
{
		
}
	
IWeatherRegion* WeatherComponent::getWeatherRegion(StringView name)
{
	return nullptr;
}

// Required component methods.
StringView WeatherComponent::componentName() const
{
	return "Full Template";
}

SemanticVersion WeatherComponent::componentVersion() const
{
	return SemanticVersion(0, 0, 1, 0);
}

void WeatherComponent::onLoad(ICore* c)
{
	// Cache core, listen to player events.
	core_ = c;
	// Register this component as wanting to be informed when a player (dis)connects.
	core_->getPlayers().getPlayerConnectDispatcher().addEventHandler(this);
	// Register this component as wanting to be informed when a tick happens.
	core_->getEventDispatcher().addEventHandler(this);
	// Record the reference to `ICore` used by *pawn-natives*.
	setAmxLookups(core_);
	// Done.
	core_->printLn("Full component template loaded.");
}

void WeatherComponent::onInit(IComponentList* components)
{
	// Cache components, add event handlers here.
	pawn_ = components->queryComponent<IPawnComponent>();

	if (pawn_)
	{
		// For the legacy `amx_` C API this call sets the correct pointers so that pawn
		// function calls call the original versions within the server.
		setAmxFunctions(pawn_->getAmxFunctions());
		// For the pawn-natives system this call sets the various component references used for
		// parameter value lookups.
		setAmxLookups(components);
		// Register this component as wanting to be informed when a script is loaded.
		pawn_->getEventDispatcher().addEventHandler(this);
	}
}

void WeatherComponent::onReady()
{
	// Fire events here at earliest.
}

void WeatherComponent::onFree(IComponent* component)
{
	// Invalidate pawn pointer so it can't be used past this point.
	if (component == pawn_)
	{
		// Remove the internal pointer.
		pawn_ = nullptr;
		// Remove the pointers to the various `amx_` function implementations.
		setAmxFunctions();
		// Remove all pool lookup pointers.
		setAmxLookups();
	}
}

void WeatherComponent::free()
{
	// Deletes the component.
	delete this;
}

void WeatherComponent::reset()
{
	// Resets data when the mode changes.
}
	
// Connect event methods.
void WeatherComponent::onPlayerConnect(IPlayer& player)
{
	// Allocate a new copy of the extension and register it for `queryExtension` lookups.
	player.addExtension(new WeatherExtension(), true);
}
	
// Pawn event methods.
void WeatherComponent::onAmxLoad(IPawnScript& script)
{
	// Because we're using `SCRIPT_API` this call automatically registers the declared natives.
	pawn_natives::AmxLoad(script.GetAMX());
}

void WeatherComponent::onAmxUnload(IPawnScript& script)
{
}

// Update event methods.
void WeatherComponent::onTick(Microseconds elapsed, TimePoint now)
{
		
}
	
// More methods to be used only in this component, with more implementation details knowledge.

// When this component is destroyed we need to tell any linked components this it is gone.
WeatherComponent::~WeatherComponent()
{
	// Clean up what you did above.
	if (pawn_)
	{
		pawn_->getEventDispatcher().removeEventHandler(this);
	}
	if (core_)
	{
		core_->getPlayers().getPlayerConnectDispatcher().removeEventHandler(this);
		core_->getEventDispatcher().removeEventHandler(this);
	}
}
