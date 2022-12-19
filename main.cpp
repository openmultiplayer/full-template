// Required for most of open.mp.
#include <sdk.hpp>

// Include the pawn component information.
#include <Server/Components/Pawn/pawn.hpp>

// Include the `SCRIPT_API()` macro.
#include <NativeFunc.hpp>

// Include a few function implementations.
#include <NativesMain.hpp>
#include <Server/Components/Pawn/pawn_impl.hpp>

class PawnExtension : public IExtension
{
private:
	int data_ = 0;

public:
	PROVIDE_EXT_UID(/* UID GOES HERE */);

	virtual ~PawnExtension()
	{
	}

	void setData(int value)
	{
		data_ = value;
	}

	int getData() const
	{
		return data_;
	}

	void freeExtension() override
	{
		// Deletes the extension.
		delete this;
	}

	void reset() override
	{
		// Resets data when the mode changes.
		data_ = 0;
	}
};

class PawnTemplate final : public IComponent, public PawnEventHandler, public PlayerEventHandler
{
private:
	ICore* core_ = nullptr;
	IPawnComponent* pawn_ = nullptr;

public:
	// https://open.mp/uid
	PROVIDE_UID(/* UID GOES HERE */);

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
		core_->getPlayers().getEventDispatcher().addEventHandler(this);
		c->printLn("Pawn component template loaded.");
	}

	void onInit(IComponentList* components) override
	{
		// Cache components, add event handlers here.
		pawn_ = components->queryComponent<IPawnComponent>();

		if (pawn_)
		{
			setAmxFunctions(pawn_->getAmxFunctions());
			pawn_->getEventDispatcher().addEventHandler(this);
		}
	}

	void onPlayerConnect(IPlayer& player) override
	{
		player.addExtension(new PawnExtension(), true);
	}

	void onReady() override
	{
		// Fire events here at earliest.
	}

	void onAmxLoad(IPawnScript* script) override
	{
		pawn_natives::AmxLoad(script->GetAMX());
	}

	void onAmxUnload(IPawnScript* script) override
	{
	}

	void onFree(IComponent* component) override
	{
		// Invalidate pawn pointer so it can't be used past this point.
		if (component == pawn_)
		{
			pawn_ = nullptr;
			setAmxFunctions();
		}
	}

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

COMPONENT_ENTRY_POINT()
{
	return new PawnTemplate();
}

SCRIPT_API(SetPawnData, bool(IPlayer& player, int value))
{
	if (auto* data = queryExtension<PawnExtension>(player))
	{
		data->setData(value);
		return true;
	}
	return false;
}

SCRIPT_API(GetPawnData, int(IPlayer& player))
{
	if (auto* data = queryExtension<PawnExtension>(player))
	{
		return data->getData();
	}
	return 0;
}
