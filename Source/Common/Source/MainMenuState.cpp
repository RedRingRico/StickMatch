#include <MainMenuState.hpp>
#include <GameplayState.hpp>
#include <System/Memory.hpp>
#include <Events.hpp>
#include <MainMenuEvents.hpp>
#include <cstring>

namespace StickMatch
{
	MainMenuState::MainMenuState( )
	{
		char Name[ ] = "Main Menu";
		ZED_MEMSIZE NameLength = strlen( Name );

		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, Name, NameLength + 1 );
		m_pName[ NameLength ] = '\0';

		m_pEventRouter = ZED_NULL;
	}

	MainMenuState::~MainMenuState( )
	{
		zedSafeDelete( m_pEventRouter );
		zedSafeDeleteArray( m_pName );
	}

	ZED_UINT32 MainMenuState::Enter( GameStateManager *p_pManager,
		const GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;

		m_GameAttributes.pRenderer->ClearColour( 0.0f, 1.0f, 0.0f );

		m_GameAttributes.pKeyboard->AllKeysUp( );

		m_pEventRouter = new ZED::Utility::EventRouter( "Main Menu Events",
			ZED_TRUE, 2 );

		m_pEventRouter->Add( new InputListener( ), KeyboardInputEventType );

		return ZED_OK;
	}

	void MainMenuState::Exit( GameStateManager *p_pManager )
	{
		p_pManager->Pop( );
	}

	void MainMenuState::Render( )
	{
	}

	void MainMenuState::Update( GameStateManager *p_pManager,
		const ZED_UINT64 p_MicroSeconds )
	{
		m_GameAttributes.pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameAttributes.pRenderer->EndScene( );

		if( m_GameAttributes.pKeyboard->IsKeyDown( K_ESCAPE ) )
		{
			this->Exit( p_pManager );
		}

		if( m_GameAttributes.pKeyboard->IsKeyDown( K_ENTER ) )
		{
			p_pManager->ChangeState( GameplayState::Instance( ) );
		}
	}

	void MainMenuState::SaveState( )
	{
	}

	void MainMenuState::RestoreState( )
	{
	}

	MainMenuState *MainMenuState::Instance( )
	{
		static MainMenuState Instance;
		return &Instance;
	}
}

