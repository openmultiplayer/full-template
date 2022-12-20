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

// Include a few function implementations.  Should only be included once.
#include <Server/Components/Pawn/pawn_impl.hpp>

// If this data is to be used in other components only share an ABI stable base class.
struct IPawnExtension : IExtension
{
	// Visit https://open.mp/uid to generate a new unique ID (different to the component UID).
	PROVIDE_EXT_UID(2/* UID GOES HERE */);

	// Just one example public method.
	virtual void setData(int value) = 0;
}

// This is a player data extension.  It is created when a player connects and destroyed when they
// disconnect.  Like a component it also needs a UID, also get from https://open.mp/uid
class PawnExtension final : public IExtension
{
private:
	// Any data, this is just a normal class.
	int data_ = 0;

public:
	// Implement the public API.
	void setData(int value) override
	{
		data_ = value;
	}

	// Add a function to this local instantiation of the public interface.
	int getData() const
	{
		return data_;
	}

	// Implement the core of the extensions API.
	void freeExtension() override
	{
		// Delete this extension.
		delete this;
	}

	void reset() override
	{
		// Optionally reset data when the main mode changes.
		data_ = 0;
	}
};

// As with the extension this should use an abstract interface if it is to be passed to other
// components.  Like the files in `<Server/Components/>` you would share only this base class and
// keep the implementation private.
class PawnTemplate final : public IComponent, public PawnEventHandler, public PlayerEventHandler
{
private:
	// Hold a reference to the main server core.
	ICore* core_ = nullptr;

	// Hold a reference to the pawn component so methods in it can be called.
	IPawnComponent* pawn_ = nullptr;

public:
	// Visit https://open.mp/uid to generate a new unique ID (different to the extension UID).
	PROVIDE_UID(3/* UID GOES HERE */);

	// When this component is destroyed we need to tell any linked components this it is gone.
	~PawnTemplate()
	{
		// Clean up what you did above.
		if (pawn_)
		{
			pawn_->getEventDispatcher().removeEventHandler(this);
		}
		if (core_)
		{
			core_->getPlayers().getEventDispatcher().removeEventHandler(this);
		}
	}

	// Implement the pawn script listener API.
	void onAmxLoad(IPawnScript* script) override
	{
		// Because we're using `SCRIPT_API` this call automatically registers the declared natives.
		pawn_natives::AmxLoad(script->GetAMX());
	}

	void onAmxUnload(IPawnScript* script) override
	{
	}

	// Implement the player connection events API.
	void onPlayerConnect(IPlayer& player) override
	{
		// Allocate a new copy of the extension and register it for `queryExtension` lookups.
		player.addExtension(new PawnExtension(), true);
	}

	// Implement the main component API.
	StringView componentName() const override
	{
		return "Pawn Template";
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
		core_->getPlayers().getEventDispatcher().addEventHandler(this);
		core_->printLn("Pawn component template loaded.");
		setAmxLookups(core_);
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
			pawn_ = nullptr;
			setAmxFunctions();
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
};

// Automatically called when the compiled binary is loaded.
COMPONENT_ENTRY_POINT()
{
	return new PawnTemplate();
}

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
