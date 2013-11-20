#include <Events.hpp>

namespace StickMatch
{
	InputEventListener::InputEventListener( )
	{
	}

	InputEventListener::~InputEventListener( )
	{
	}

	ZED_BOOL InputEventListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		return ZED_OK;
	}
}

