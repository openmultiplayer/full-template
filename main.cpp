// Required for most of open.mp.
#include <sdk.hpp>

// Include the pawn component information.
#include <Server/Components/Pawn/pawn.hpp>

// Include the `SCRIPT_API()` macro.
#include <NativeFunc.hpp>

// Include a few function implementations.
#include <NativesMain.hpp>
#include <Server/Components/Pawn/pawn_impl.hpp>

class PawnTemplate final : public IComponent, public PawnEventHandler
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
		// Cache core, player pool here
		core_ = c;
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
