#include <GameplayState.hpp>
#include <MainMenuState.hpp>
#include <System/Memory.hpp>
#include <StickFighter.hpp>
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

	ZED_UINT32 GameplayState::AssignCharacter(
		const ZED_UINT32 p_CharacterTypeID,
		const ZED_UINT32 p_Type, const ZED_UINT32 p_Slot )
	{
		if( ( p_Slot < 1 ) || ( p_Slot > 2 ) )
		{
			return ZED_FAIL;
		}

		std::vector< BaseGameEntity * >::iterator Fighter =
			m_Entities.begin( );

		ZED_UINT32 FighterID = GenerateGameEntityID( g_pStickFighterName );
		ZED_BOOL FoundCorrectFighter = ZED_FALSE;
		StickFighter *pFighter = ZED_NULL;

		// Player is a rudimentary way of keeping track of the player being
		// assigned.  There is a better way to do this.
		ZED_UINT32 Player = 1;

		for( ; Fighter != m_Entities.end( ); ++Fighter )
		{
			if( ( *Fighter )->ID( ) == FighterID )
			{
				if( p_Slot != Player )
				{
					++Player;
					continue;
				}

				pFighter = dynamic_cast< StickFighter * >( *Fighter );
				FoundCorrectFighter = ZED_TRUE;
				break;
			}
		}

		if( !FoundCorrectFighter )
		{
			m_Entities.push_back( new StickFighter( ) );
			pFighter = dynamic_cast< StickFighter * >( m_Entities.back( ) );
		}

		pFighter->Character( p_CharacterTypeID );
		pFighter->Type( p_Type );

		pFighter->Initialise( );

		return ZED_OK;
	}
}

