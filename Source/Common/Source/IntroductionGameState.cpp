#include <IntroductionGameState.hpp>
#include <MainMenuState.hpp>
#include <System/Debugger.hpp>
#include <System/Memory.hpp>
#include <InputBinder.hpp>
#include <Events.hpp>
#include <IntroductionGameStateEvents.hpp>
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
		m_pInputListener = ZED_NULL;
		m_pInputBinder = ZED_NULL;
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

		if( m_pEventRouter == ZED_NULL )
		{
			m_pEventRouter = new ZED::Utility::EventRouter(
				"Introduction events", ZED_TRUE, 2 );
		}

		m_SkipIntroduction = ZED_FALSE;

		if( m_pInputListener == ZED_NULL )
		{
			m_pInputListener = new IntroductionInputListener( this );
			m_pEventRouter->Add( m_pInputListener, SemanticInputEventType );
		}

		if( m_pInputBinder == ZED_NULL )
		{
			m_pInputBinder = new InputBinder( );
			m_pInputBinder->BindKey( K_ESCAPE, INTRODUCTION_SKIP );
			p_pManager->BindInput( m_pInputBinder );
		}

		return ZED_OK;
	}

	void IntroductionGameState::Exit( GameStateManager *p_pManager )
	{
		p_pManager->Pop( );
	}

	void IntroductionGameState::Render( )
	{
	}

	void IntroductionGameState::Update( GameStateManager *p_pManager,
		const ZED_UINT64 p_MicroSeconds )
	{
		m_ElapsedTime += p_MicroSeconds;
		m_GameAttributes.pRenderer->BeginScene( ZED_TRUE, ZED_TRUE, ZED_TRUE );
		m_GameAttributes.pRenderer->EndScene( );

		if( ( m_ElapsedTime >= 1000000ULL ) || m_SkipIntroduction )
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

	void IntroductionGameState::SkipIntroduction( )
	{
		m_SkipIntroduction = ZED_TRUE;
	}
}

