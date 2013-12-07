#include <MainMenuEvents.hpp>
#include <MainMenuState.hpp>
#include <Events.hpp>
#include <Semantics.hpp>
#include <Arithmetic/Arithmetic.hpp>

namespace StickMatch
{
	MainMenuInputListener::MainMenuInputListener( )
	{
	}

	MainMenuInputListener::~MainMenuInputListener( )
	{
	}

	ZED_BOOL MainMenuInputListener::HandleEvent(
		const ZED::Utility::Event &p_Event )
	{
		if( p_Event.Type( ).ID( ) == SemanticInputEventType.ID( ) )
		{
			SemanticInputEventData *pSemanticData =
				p_Event.Data< SemanticInputEventData >( );
			
			ZED_UINT32	Semantic = 0;
			ZED_UINT32	SemanticID = 0;
			ZED_FLOAT32	SemanticValue = 0.0f;

			pSemanticData->GetSemantic( Semantic, SemanticValue );

			switch( Semantic )
			{
				case STATE_EXIT:
				{
					if( ZED::Arithmetic::Equal( SemanticValue, 1.0f ) )
					{
						m_pMainMenu->Exit( );
					}
					break;
				}
				case MAIN_MENU_START_GAME:
				{
					if( ZED::Arithmetic::Equal( SemanticValue, 1.0f ) )
					{
						m_pMainMenu->StartGame( );
					}
					break;
				}
				default:
				{
					return ZED_FALSE;
				}
			}

			return ZED_TRUE;
		}

		return ZED_FALSE;
	}

	void MainMenuInputListener::SetMainMenuState( MainMenuState *p_pMainMenu )
	{
		m_pMainMenu = p_pMainMenu;
	}
}

