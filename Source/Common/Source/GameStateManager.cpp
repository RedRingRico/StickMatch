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
		ZED_UINT64 Current = ZED::System::GetTimeMiS( );
		ZED_UINT64 Difference = Current - m_StartTime;
		m_StartTime = Current;
		m_GameStates.top( )->Update( this, Difference );
	}

	void GameStateManager::Push( GameState *p_pState )
	{
		if( !m_GameStates.empty( ) )
		{
			m_GameStates.top( )->SaveState( );
		}
		m_GameStates.push( p_pState );
		m_GameStates.top( )->Enter( this, m_GameAttributes );
	}

	void GameStateManager::Pop( )
	{
		if( !m_GameStates.empty( ) )
		{
			m_GameStates.pop( );
			if( !m_GameStates.empty( ) )
			{
				m_GameStates.top( )->RestoreState( );
			}
		}
	}

	void GameStateManager::ChangeState( GameState *p_pState )
	{
		// Get the top-most state and swap it
		if( !m_GameStates.empty( ) )
		{
			m_GameStates.pop( );
		}

		m_GameStates.push( p_pState );
		m_GameStates.top( )->Enter( this, m_GameAttributes );
	}

	void GameStateManager::ClearStack( )
	{
		while( !m_GameStates.empty( ) )
		{
			m_GameStates.pop( );
		}
	}

	void GameStateManager::GameAttributes(
		const StickMatch::GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;
	}
}

