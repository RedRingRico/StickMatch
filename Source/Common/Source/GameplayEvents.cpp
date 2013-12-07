#include <GameplayEvents.hpp>
#include <Events.hpp>
#include <System/Memory.hpp>
#include <Utility/EventRouter.hpp>

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
		if( p_Event.Type( ).ID( ) == SemanticInputEventType.ID( ) )
		{
			SemanticInputEventData *pSemanticData =
				p_Event.Data< SemanticInputEventData >( );

			ZED_UINT32	Semantic = 0;
			ZED_FLOAT32	SemanticValue = 0.0f;

			pSemanticData->GetSemantic( Semantic, SemanticValue );

			MoveEventData MoveData;
			MoveData.SetActor( 1 );
			ACTOR_MOVE_DIRECTION Direction = ACTOR_MOVE_DIRECTION_MIN;

			zedTrace( "Semantic from gameplay: %u\n", Semantic );

			switch( Semantic )
			{
				case MOVE_UP:
				{
					Direction = ACTOR_MOVE_DIRECTION_UP;
					break;
				}
			}
			MoveData.SetDirection( Direction );
			MoveData.SetVelocity( SemanticValue );

			MoveEvent Move( &MoveData );

			ZED::Utility::SendEvent( Move );

			return ZED_TRUE;
		}

		if( p_Event.Type( ).ID( ) == MoveEventType.ID( ) )
		{
			return ZED_TRUE;
		}

		return ZED_FALSE;
	}

	MoveEventData::MoveEventData( ) :
		m_ActorID( 0 ), m_Direction( ACTOR_MOVE_DIRECTION_MIN ),
		m_Velocity( 0.0f )
	{
	}

	MoveEventData::~MoveEventData( )
	{
	}

	ZED_UINT32 MoveEventData::SetActor( const ZED_UINT32 p_ActorID )
	{
		// The actor ID should be verified here
		m_ActorID = p_ActorID;

		return ZED_OK;
	}

	ZED_UINT32 MoveEventData::SetDirection(
		const ACTOR_MOVE_DIRECTION p_Direction )
	{
		if( ( p_Direction > ACTOR_MOVE_DIRECTION_MAX ) ||
			( p_Direction < ACTOR_MOVE_DIRECTION_MIN ) )
		{
			zedTrace( "[StickMatch::MoveEventData::SetDirection] <WARN> "
				"Actor direction invalid: %d\n", p_Direction );

			return ZED_FAIL;
		}

		m_Direction = p_Direction;

		return ZED_OK;
	}

	ZED_UINT32 MoveEventData::SetVelocity( const ZED_FLOAT32 p_Velocity )
	{
		// Clamp the velocity
		if( p_Velocity < ACTOR_MOVE_VELOCITY_MIN )
		{
			m_Velocity = ACTOR_MOVE_VELOCITY_MIN;
			return ZED_OK;
		}
		if( p_Velocity > ACTOR_MOVE_VELOCITY_MAX )
		{
			m_Velocity = ACTOR_MOVE_VELOCITY_MAX;
			return ZED_OK;
		}

		m_Velocity = p_Velocity;

		return ZED_OK;
	}

	ZED_UINT32 MoveEventData::GetActor( ) const
	{
		return m_ActorID;
	}

	ACTOR_MOVE_DIRECTION MoveEventData::GetDirection( ) const
	{
		return m_Direction;
	}

	ZED_FLOAT32 MoveEventData::GetVelocity( ) const
	{
		return m_Velocity;
	}

	MoveEvent::MoveEvent( MoveEventData *p_pData, ZED_UINT64 p_DispatchTime ) :
		ZED::Utility::Event( MoveEventType.Name( ), p_pData, p_DispatchTime )
	{
		m_pData = p_pData;
	}

	MoveEvent::~MoveEvent( )
	{
	}
}

