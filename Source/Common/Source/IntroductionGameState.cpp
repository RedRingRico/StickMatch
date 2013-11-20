#include <IntroductionGameState.hpp>
#include <MainMenuState.hpp>
#include <System/Debugger.hpp>
#include <System/Memory.hpp>
#include <cstring>

namespace StickMatch
{
	IntroductionGameState *IntroductionGameState::Instance( )
	{
		static IntroductionGameState Instance;

		return &Instance;
	}

	IntroductionGameState::IntroductionGameState( )
	{
		char Name[ ] = "Introduction";
		ZED_MEMSIZE NameLength = strlen( Name );

		m_pName = new ZED_CHAR8[ NameLength + 1 ];
		strncpy( m_pName, Name, NameLength + 1 );
		m_pName[ NameLength ] = '\0';

		m_pEventRouter = ZED_NULL;
	}

	IntroductionGameState::~IntroductionGameState( )
	{
		zedSafeDelete( m_pEventRouter );
		zedSafeDeleteArray( m_pName );
	}

	ZED_UINT32 IntroductionGameState::Enter( GameStateManager *p_pManager,
		const GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;
		m_ElapsedTime = 0ULL;

		m_GameAttributes.pRenderer->ClearColour( 1.0f, 0.0f, 0.0f );

		m_GameAttributes.pKeyboard->AllKeysUp( );

		m_pEventRouter = new ZED::Utility::EventRouter(
			"Introduction events", ZED_TRUE, 2 );

		return ZED_OK;
	}

	void IntroductionGameState::Exit( GameStateManager *p_pManager )
	{
		p_pManager->Pop( );
	}

	void IntroductionGameState::Update( GameStateManager *p_pManager,
		const ZED_UINT64 p_MicroSeconds )
	{
		m_ElapsedTime += p_MicroSeconds;
		m_GameAttributes.pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameAttributes.pRenderer->EndScene( );

		if( ( m_ElapsedTime >= 1000000ULL ) ||
			m_GameAttributes.pKeyboard->IsKeyDown( K_ESCAPE ) )
		{
			zedTrace( "Elapsed: %llu\n", m_ElapsedTime );
			m_ElapsedTime = 0ULL;
			p_pManager->ChangeState( MainMenuState::Instance( ) );
		}
	}

	void IntroductionGameState::SaveState( )
	{
	}

	void IntroductionGameState::RestoreState( )
	{
	}
}

