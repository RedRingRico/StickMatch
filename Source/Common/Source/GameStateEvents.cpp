#include <GameStateEvents.hpp>
#include <System/Debugger.hpp>
#include <Events.hpp>
#include <InputBinder.hpp>
#include <Utility/EventRouter.hpp>

namespace StickMatch
{
	GameStateInputListener::GameStateInputListener( )
	{
		m_pInputBinder = ZED_NULL;
	}

	GameStateInputListener::~GameStateInputListener( )
	{
	}

	ZED_BOOL GameStateInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == KeyboardInputEventType.ID( ) )
		{
			if( m_pInputBinder )
			{
				KeyboardInputEventData *pData =
					p_Event.Data< KeyboardInputEventData >( );

				ZED_BYTE Key = 0;
				ZED_BOOL KeyState = ZED_FALSE;

				pData->GetState( Key, KeyState );
				
				ZED_UINT32 SemanticID;
				SemanticID = m_pInputBinder->Key( Key );

				if( SemanticID != 0 )
				{
					ZED_FLOAT32 SemanticValue = KeyState ? 1.0f : 0.0f;
					SemanticInputEventData SemanticData;
					SemanticData.Semantic( SemanticID, SemanticValue );
					SemanticInputEvent Semantic( &SemanticData );

					ZED::Utility::SendEvent( Semantic );

					return ZED_TRUE;
				}
			}

			return ZED_FALSE;
		}
		else
		{
			zedTrace( "Did not handle event: %s [%u]\n",
				p_Event.Type( ).Name( ), p_Event.Type( ).ID( ) );
		}

		return ZED_FALSE;
	}

	ZED_UINT32 GameStateInputListener::Binder( InputBinder *p_pInputBinder )
	{
		m_pInputBinder = p_pInputBinder;

		return ZED_OK;
	}
}

