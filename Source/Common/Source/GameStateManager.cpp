#include <GameStateManager.hpp>
#include <GameState.hpp>
#include <System/DataTypes.hpp>
#include <System/Time.hpp>

namespace StickMatch
{
	GameStateManager::GameStateManager( ) 
	{
		ZED::System::StartTime( );
		m_StartTime = ZED::System::GetTimeMiS( );
		m_Running = ZED_TRUE;
		m_pEventRouter = ZED_NULL;
	}

	GameStateManager::~GameStateManager( )
	{
		while( !m_GameStates.empty( ) )
		{
			this->Pop( );
		}
	}

	void GameStateManager::Execute( )
	{
		if( m_GameStates.empty( ) )
		{
			zedTrace( "[StickMatch::GameStateManager] "
				"Game state stack is empty.  Quitting...\n" );
			this->Quit( );
		}
		else
		{
			ZED_UINT64 Current = ZED::System::GetTimeMiS( );
			ZED_UINT64 Difference = Current - m_StartTime;
			m_StartTime = Current;
			m_GameStates.top( )->Update( this, Difference );
		}
	}

	void GameStateManager::Push( GameState *p_pState )
	{
		if( !m_GameStates.empty( ) )
		{
			zedTrace( "[StickMatch::GameStateManager] Saving state for [%s]\n",
				m_GameStates.top( )->Name( ) );

			m_GameStates.top( )->SaveState( );
		}

		zedTrace( "[StickMatch::GameStateManager] Pushing [%s] onto the "
			"stack\n", p_pState->Name( ) );

		m_GameStates.push( p_pState );

		m_GameStates.top( )->Enter( this, m_GameAttributes );
		m_pEventRouter = m_GameStates.top( )->EventRouter( );
	}

	void GameStateManager::Pop( )
	{
		if( !m_GameStates.empty( ) )
		{
			zedTrace( "[StickMatch::GameStateManager] Popping [%s] from the "
				"stack\n", m_GameStates.top( )->Name( ) );

			m_GameStates.pop( );

			if( !m_GameStates.empty( ) )
			{
				zedTrace( "[StickMatch::GameStateManager] Restoring [%s]'s "
					"state", m_GameStates.top( )->Name( ) );

				m_GameStates.top( )->RestoreState( );
				m_pEventRouter = m_GameStates.top( )->EventRouter( );
			}
		}
	}

	void GameStateManager::ChangeState( GameState *p_pState )
	{
		// Get the top-most state and swap it
		if( !m_GameStates.empty( ) )
		{
			this->Pop( );
		}

		this->Push( p_pState );
	}

	void GameStateManager::ClearStack( )
	{
		while( !m_GameStates.empty( ) )
		{
			this->Pop( );
		}
	}

	void GameStateManager::GameAttributes(
		const StickMatch::GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;
	}
}

