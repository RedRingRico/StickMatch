#include <GameplayEvents.hpp>
#include <System/Memory.hpp>

namespace StickMatch
{
	GameplayInputListener::GameplayInputListener( )
	{
	}

	GameplayInputListener::~GameplayInputListener( )
	{
	}

	ZED_BOOL GameplayInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		return ZED_FALSE;
	}
}

