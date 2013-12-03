#include <GameStateEvents.hpp>
#include <System/Debugger.hpp>
#include <Events.hpp>

namespace StickMatch
{
	GameStateInputListener::GameStateInputListener( )
	{
	}

	GameStateInputListener::~GameStateInputListener( )
	{
	}

	ZED_BOOL GameStateInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == KeyboardInputEventType.ID( ) )
		{
			KeyboardInputEventData *Data =
				p_Event.Data< KeyboardInputEventData >( );

			ZED_BYTE Key;
			ZED_BOOL KeyState;

			Data->State( Key, KeyState );

			return ZED_TRUE;
		}
		else
		{
			zedTrace( "Did not handle event: %s [%d]\n",
				p_Event.Type( ).Name( ), p_Event.Type( ).ID( ) );
		}

		return ZED_FALSE;
	}
}

