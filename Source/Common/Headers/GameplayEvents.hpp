#ifndef __STICKMATCH_GAMEPLAYEVENTS_HPP__
#define __STICKMATCH_GAMEPLAYEVENTS_HPP__

#include <Utility/Event.hpp>
#include <System/InputTypes.hpp>

namespace StickMatch
{
	const ZED_UINT32 MOVE_FORWARD	= 1;
	const ZED_UINT32 MOVE_BACKWARD	= 2;
	const ZED_UINT32 MOVE_LEFT		= 3;
	const ZED_UINT32 MOVE_RIGHT		= 4;
	const ZED_UINT32 ACTION_KICK	= 5;
	const ZED_UINT32 ACTION_PUNCH	= 6;
	const ZED_UINT32 ACTION_GUARD	= 7;
	const ZED_UINT32 ACTION_THROW	= 8;
	const ZED_UINT32 STATE_PAUSE	= 9;

	const ZED::Utility::EventType MoveEvent( "StickFighter Move" );
	const ZED::Utility::EventType ActionEvent( "StickFighter Action" );
	const ZED::Utility::EventType StateEvent( "State Change" );

	class GameplayInputListener : public ZED::Utility::EventListener
	{
	public:
		GameplayInputListener( );
		virtual ~GameplayInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const { return "Gameplay Input Listener"; }
	private:
	};

}

#endif

