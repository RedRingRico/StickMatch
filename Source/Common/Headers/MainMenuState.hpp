#ifndef __STICKMATCH_MAINMENUSTATE_HPP__
#define __STICKMATCH_MAINMENUSTATE_HPP__

#include <GameState.hpp>

namespace StickMatch
{
	class MainMenuState : public GameState
	{
	public:
		MainMenuState( );
		virtual ~MainMenuState( );

		virtual ZED_UINT32 Enter( GameStateManager *p_pManager,
			const GameAttributes &p_GameAttributes );
		virtual void Exit( GameStateManager *p_pManager );

		virtual void Render( );

		virtual void Update( GameStateManager *p_pManager,
			const ZED_UINT64 p_MicroSeconds );

		virtual void SaveState( );
		virtual void RestoreState( );

		static MainMenuState *Instance( );

	private:
	};
}

#endif // __STICKMATCH_MAINMENUSTATE_HPP__

