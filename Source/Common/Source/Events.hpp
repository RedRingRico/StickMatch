#include <Events.hpp>

namespace StickMatch
{
	InputEventListener::InputEventListener( )
	{
	}

	InputEventListener::~InputEventListener( )
	{
	}

	ZED_BOOL InputEventListener::HandleEvent( const Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == g_InputEventID )
		{
			InputEventData *pData = < InputEventData * >p_Event.Data( );
		}

		return ZED_OK;
	}
}

