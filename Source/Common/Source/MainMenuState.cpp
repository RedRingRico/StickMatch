#include <MainMenuState.hpp>
#include <System/Memory.hpp>
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
	}

	MainMenuState::~MainMenuState( )
	{
		zedSafeDeleteArray( m_pName );
	}

	ZED_UINT32 MainMenuState::Enter( GameStateManager *p_pManager,
		const GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;

		m_GameAttributes.pRenderer->ClearColour( 0.0f, 1.0f, 0.0f );

		return ZED_OK;
	}

	void MainMenuState::Exit( GameStateManager *p_pManager )
	{
	}

	void MainMenuState::Update( GameStateManager *p_pManager,
		const ZED_UINT64 p_MicroSeconds )
	{
		m_GameAttributes.pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameAttributes.pRenderer->EndScene( );

		if( m_GameAttributes.pKeyboard->IsKeyDown( K_ESCAPE ) )
		{
			p_pManager->Quit( );
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

