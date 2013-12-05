#ifndef __STICKMATCH_GAMESTATEMANAGER_HPP__
#define __STICKMATCH_GAMESTATEMANAGER_HPP__

#include <stack>
#include <GameAttributes.hpp>
#include <Utility/EventRouter.hpp>

namespace StickMatch
{
	class GameState;
	class GameStateInputListener;
	class InputBinder;

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

		ZED::Utility::EventRouter *EventRouter( ) { return m_pEventRouter; }

		ZED_UINT32 BindInput( const InputBinder *p_pInputBinder );

	private:
		std::stack< GameState * > m_GameStates;

		StickMatch::GameAttributes	m_GameAttributes;
		ZED_UINT64	m_StartTime;

		ZED_BOOL	m_Running;

		ZED::Utility::EventRouter		*m_pEventRouter;
		GameStateInputListener			*m_pInputListener;
		InputBinder						*m_pInputBinder;
	};
}

#endif

