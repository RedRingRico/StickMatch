#include <MainMenuState.hpp>
#include <GameplayState.hpp>
#include <System/Memory.hpp>
#include <Events.hpp>
#include <MainMenuEvents.hpp>
#include <cstring>
#include <InputBinder.hpp>
#include <Semantics.hpp>

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
		m_pInputBinder = new InputBinder( );
		m_ExitState = ZED_FALSE;

		m_pInputListener = new MainMenuInputListener( );
	}

	MainMenuState::~MainMenuState( )
	{
		zedSafeDelete( m_pInputBinder );
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

		m_pEventRouter->Add( m_pInputListener, SemanticInputEventType );

		m_pInputBinder->BindKey( K_ESCAPE, STATE_EXIT );
		m_pInputBinder->BindKey( 'y', STATE_EXIT_CONFIRM );
		m_pInputBinder->BindKey( 'n', STATE_EXIT_CANCEL );

		p_pManager->BindInput( m_pInputBinder );
		zedTrace( "Main menu input binder: %p\n", m_pInputBinder );

		m_pInputListener->SetMainMenuState( this );

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

		if( m_ExitState == ZED_TRUE )
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

	void MainMenuState::Exit( )
	{
		m_ExitState = ZED_TRUE;
	}
}

