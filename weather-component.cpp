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

// If this data is to be used in other components only share an ABI stable base class.
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

public:
	// Implementations of the various methods from the public API.
	IWeatherRegion* createWeatherRegion(StringView name, StringView location) override
	{
		
	}
	
	void destroyWeatherRegion(IWeatherRegion*) override
	{
		
	}
	
	IWeatherRegion* getWeatherRegion(StringView name) override
	{
		
	}

	// Required component methods.
	StringView componentName() const override
	{
		return "Full Template";
	}

	SemanticVersion componentVersion() const override
	{
		return SemanticVersion(0, 0, 1, 0);
	}

	void onLoad(ICore* c) override
	{
		// Cache core, listen to player events.
		core_ = c;
		// Register this component as wanting to be informed when a player (dis)connects.
		core_->getPlayers().getPlayerConnectDispatcher().addEventHandler(this);
		// Register this component as wanting to be informed when a tick happens.
		core_->.getCoreDispatcher().addEventHandler(this);
		// Record the reference to `ICore` used by *pawn-natives*.
		setAmxLookups(core_);
		// Done.
		core_->printLn("Full component template loaded.");
	}

	void onInit(IComponentList* components) override
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

	void onReady() override
	{
		// Fire events here at earliest.
	}

	void onFree(IComponent* component) override
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

	void free() override
	{
		// Deletes the component.
		delete this;
	}

	void reset() override
	{
		// Resets data when the mode changes.
	}
	
	// Connect event methods.
	void onPlayerConnect(IPlayer& player) override
	{
		// Allocate a new copy of the extension and register it for `queryExtension` lookups.
		player.addExtension(new WeatherExtension(), true);
	}
	
	// Pawn event methods.
	void onAmxLoad(IPawnScript& script) override
	{
		// Because we're using `SCRIPT_API` this call automatically registers the declared natives.
		pawn_natives::AmxLoad(script.GetAMX());
	}

	void onAmxUnload(IPawnScript& script) override
	{
	}

	// Update event methods.
	void onTick(Microseconds elapsed, TimePoint now) override
	{
		
	}
	
	// More methods to be used only in this component, with more implementation details knowledge.

	// When this component is destroyed we need to tell any linked components this it is gone.
	~WeatherComponent()
	{
		// Clean up what you did above.
		if (pawn_)
		{
			pawn_->getEventDispatcher().removeEventHandler(this);
		}
		if (core_)
		{
			core_->getPlayers().getPlayerConnectDispatcher().removeEventHandler(this);
			core_->getCoreDispatcher().removeEventHandler(this);
		}
	}
};
