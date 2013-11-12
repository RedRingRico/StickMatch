#ifndef __STICKMATCH_GAMESTATEMANAGER_HPP__
#define __STICKMATCH_GAMESTATEMANAGER_HPP__

#include <stack>
#include <GameAttributes.hpp>

namespace StickMatch
{
	class GameState;

	class GameStateManager
	{
	public:
		GameStateManager( );
		~GameStateManager( );

		void Execute( );

		void Push( GameState *p_pState );
		void Pop( );
		
		void ChangeState( GameState *p_pState );

		void ClearStack( );

		void Quit( ){ this->ClearStack( ); m_Running = ZED_FALSE; }

		ZED_BOOL Running( ) const { return m_Running; }

		void GameAttributes( const GameAttributes &p_GameAttributes );

	private:
		std::stack< GameState * > m_GameStates;

		StickMatch::GameAttributes	m_GameAttributes;
		ZED_UINT64	m_StartTime;

		ZED_BOOL	m_Running;
	};
}

#endif

