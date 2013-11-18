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
		const ZED::System::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == g_InputEventID )
		{
		}

		return ZED_OK;
	}
}

