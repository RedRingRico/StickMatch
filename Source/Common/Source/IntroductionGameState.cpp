#include <IntroductionGameState.hpp>
#include <System/Debugger.hpp>

namespace StickMatch
{
	IntroductionGameState *IntroductionGameState::Instance( )
	{
		static IntroductionGameState Instance;

		return &Instance;
	}

	IntroductionGameState::IntroductionGameState( )
	{
	}

	IntroductionGameState::~IntroductionGameState( )
	{
	}

	ZED_UINT32 IntroductionGameState::Enter( GameStateManager *p_pManager,
		const GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;
		m_ElapsedTime = 0ULL;

		m_GameAttributes.pRenderer->ClearColour( 1.0f, 0.0f, 0.0f );

		return ZED_OK;
	}

	void IntroductionGameState::Exit( GameStateManager *p_pManager )
	{
	}

	void IntroductionGameState::Update( GameStateManager *p_pManager,
		const ZED_UINT64 p_MicroSeconds )
	{
		m_ElapsedTime += p_MicroSeconds;
		m_GameAttributes.pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameAttributes.pRenderer->EndScene( );

		if( m_ElapsedTime >= 1000000ULL )
		{
			zedTrace( "Elapsed: %llu\n", m_ElapsedTime );
			m_ElapsedTime = 0ULL;
			// p_pManager->ChangeState( MainMenuState::Instance( ) );
		}

		if( m_GameAttributes.pKeyboard->IsKeyDown( 'q' ) ) 
		{
			p_pManager->Quit( );
		}
	}

	void IntroductionGameState::SaveState( )
	{
	}

	void IntroductionGameState::RestoreState( )
	{
	}
}

