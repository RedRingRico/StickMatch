#include <MainMenuEvents.hpp>

namespace StickMatch
{
	InputListener::InputListener( )
	{
	}

	InputListener::~InputListener( )
	{
	}

	ZED_BOOL InputListener::HandleEvent( const ZED::Utility::Event &p_Event )
	{
		return ZED_TRUE;
	}
}

