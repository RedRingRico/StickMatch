#ifndef __STICKMATCH_INTRODUCTIONGAMESTATE_HPP__
#define __STICKMATCH_INTRODUCTIONGAMESTATE_HPP__

#include <GameState.hpp>

namespace StickMatch
{
	class IntroductionGameState : public GameState
	{
	public:
		IntroductionGameState( );
		virtual ~IntroductionGameState( );

		virtual ZED_UINT32 Enter( GameStateManager *p_pManager,
			const GameAttributes &p_GameAttributes );
		virtual void Exit( GameStateManager *p_pManager );

		virtual void Render( );
		
		virtual void Update( GameStateManager *p_pManager,
			const ZED_UINT64 p_MicroSeconds );

		virtual void SaveState( );
		virtual void RestoreState( );

		static IntroductionGameState *Instance( );

	private:
	};
}

#endif // __STICKMATCH_INTRODUCTIONGAMESTATE_HPP__

