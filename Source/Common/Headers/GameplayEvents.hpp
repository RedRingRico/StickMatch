#ifndef __STICKMATCH_GAMEPLAYEVENTS_HPP__
#define __STICKMATCH_GAMEPLAYEVENTS_HPP__

#include <Utility/Event.hpp>
#include <System/InputTypes.hpp>
#include <Actor.hpp>

namespace StickMatch
{
	const ZED_UINT32 MOVE_UP		= 1;
	const ZED_UINT32 MOVE_DOWN		= 2;
	const ZED_UINT32 MOVE_LEFT		= 3;
	const ZED_UINT32 MOVE_RIGHT		= 4;
	const ZED_UINT32 ACTION_KICK	= 5;
	const ZED_UINT32 ACTION_PUNCH	= 6;
	const ZED_UINT32 ACTION_GUARD	= 7;
	const ZED_UINT32 ACTION_THROW	= 8;
	const ZED_UINT32 STATE_PAUSE	= 9;

	const ZED::Utility::EventType MoveEventType( "StickFighter Move" );
	const ZED::Utility::EventType ActionEventType( "StickFighter Action" );
	const ZED::Utility::EventType StateEventType( "State Change" );

	class GameplayInputListener : public ZED::Utility::EventListener
	{
	public:
		GameplayInputListener( );
		virtual ~GameplayInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const { return "Gameplay Input Listener"; }
	private:
	};

	class MoveEventData : public ZED::Utility::EventData
	{
	public:
		MoveEventData( );
		virtual ~MoveEventData( );

		ZED_UINT32 SetActor( const ZED_UINT32 p_ActorID );
		ZED_UINT32 SetDirection( const ACTOR_MOVE_DIRECTION p_Direction );
		ZED_UINT32 SetVelocity( const ZED_FLOAT32 p_Velocity );

		ZED_UINT32				GetActor( ) const;
		ACTOR_MOVE_DIRECTION	GetDirection( ) const;
		ZED_FLOAT32				GetVelocity( ) const;
		
	private:
		ZED_UINT32				m_ActorID;
		ACTOR_MOVE_DIRECTION	m_Direction;
		ZED_FLOAT32				m_Velocity;
	};

	class MoveEvent : public ZED::Utility::Event
	{
	public:
		ZED_EXPLICIT MoveEvent( MoveEventData *p_pData = ZED_NULL,
			ZED_UINT64 p_DispatchTime = ZED::System::GetTimeMiS( ) );
		virtual ~MoveEvent( );

	private:
		MoveEventData	m_MoveData;
	};
}

#endif

