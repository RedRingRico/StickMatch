#include <GameplayState.hpp>
#include <MainMenuState.hpp>
#include <System/Memory.hpp>
#include <cstring>

namespace StickMatch
{
	GameplayState *GameplayState::Instance( )
	{
		static GameplayState Instance;

		return &Instance;
	}

	GameplayState::GameplayState( )
	{
		char Name[ ] = "Gameplay";
		ZED_MEMSIZE NameLength = strlen( Name );

		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, Name, NameLength + 1 );
		m_pName[ NameLength ] = '\0';

		m_ElapsedTime = 0ULL;
	}

	GameplayState::~GameplayState( )
	{
		zedSafeDeleteArray( m_pName );
	}

	ZED_UINT32 GameplayState::Enter( GameStateManager *p_pManager,
		const GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;

		m_GameAttributes.pRenderer->ClearColour( 0.14f, 0.0f, 0.14f );

		m_GameAttributes.pKeyboard->AllKeysUp( );

		return ZED_OK;
	}

	void GameplayState::Exit( GameStateManager *p_pManager )
	{
		p_pManager->Pop( );
	}

	void GameplayState::Update( GameStateManager *p_pManager,
		const ZED_UINT64 p_MicroSeconds )
	{
		static ZED_UINT32 Counter = 0;
		m_ElapsedTime += p_MicroSeconds;

		m_GameAttributes.pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameAttributes.pRenderer->EndScene( );
		++Counter;

		if( m_GameAttributes.pKeyboard->IsKeyDown( K_ESCAPE ) )
		{
			p_pManager->ChangeState( MainMenuState::Instance( ) );
		}

		if( m_ElapsedTime > 1000000ULL )
		{
			zedTrace( "Updated: %d times\n", Counter );

			m_ElapsedTime = 0ULL;
			Counter = 0;
		}
	}

	void GameplayState::SaveState( )
	{
	}

	void GameplayState::RestoreState( )
	{
	}
}

