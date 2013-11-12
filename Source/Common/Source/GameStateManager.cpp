#include <GameStateManager.hpp>
#include <GameState.hpp>
#include <System/DataTypes.hpp>

namespace StickMatch
{
	GameStateManager::GameStateManager( ) 
	{
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
		m_GameStates.top( )->Update( this, 0 );
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
			m_GameStates.top( )->RestoreState( );
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

	void GameStateManager::GameAttributes(
		const StickMatch::GameAttributes &p_GameAttributes )
	{
		m_GameAttributes = p_GameAttributes;
	}
}

