#include <IntroductionGameStateEvents.hpp>
#include <IntroductionGameState.hpp>
#include <Events.hpp>
#include <Arithmetic/Arithmetic.hpp>

namespace StickMatch
{
	IntroductionInputListener::IntroductionInputListener(
		IntroductionGameState *p_pGameState ) :
		m_pIntroductionGameState( p_pGameState )
	{
	}

	IntroductionInputListener::~IntroductionInputListener( )
	{
	}

	ZED_BOOL IntroductionInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == SemanticInputEventType.ID( ) )
		{
			SemanticInputEventData *pSemanticData =
				p_Event.Data< SemanticInputEventData >( );
			
			ZED_UINT32 SemanticID = 0;
			ZED_FLOAT32 SemanticValue = 0.0f;

			pSemanticData->GetSemantic( SemanticID, SemanticValue );

			switch( SemanticID )
			{
				case INTRODUCTION_SKIP:
				{
					if( ZED::Arithmetic::Equal( SemanticValue, 1.0f ) )
					{
						m_pIntroductionGameState->SkipIntroduction( );
					}
					break;
				}
				default:
				{
					zedTrace(
						"[StickMatch::IntroductionInputListener::HandleEvent]"
						" <WARN> Did not handle semantic event: %d\n",
						SemanticID );
					return ZED_FALSE;
				}
			}

			return ZED_TRUE;
		}

		return ZED_FALSE;
	}
}

