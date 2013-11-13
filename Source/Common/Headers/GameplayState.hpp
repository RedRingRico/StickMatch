#ifndef __STICKMATCH_GAMEPLAYSTATE_HPP__
#define __STICKMATCH_GAMEPLAYSTATE_HPP__

#include <GameState.hpp>

namespace StickMatch
{
	class GameplayState : public GameState
	{
	public:
		GameplayState( );
		virtual ~GameplayState( );

		virtual ZED_UINT32 Enter( GameStateManager *p_pManager,
			const GameAttributes &p_GameAttributes );
		virtual void Exit( GameStateManager *p_pManager );

		virtual void Update( GameStateManager *p_pManager,
			const ZED_UINT64 p_MicroSeconds );

		virtual void SaveState( );
		virtual void RestoreState( );

		static GameplayState *Instance( );
	
	private:
	};
}

#endif // __STICKMATCH_GAMEPLAYGAMESTATE_HPP__

