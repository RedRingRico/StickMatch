#ifndef __STICKMATCH_GAMEPLAYSTATE_HPP__
#define __STICKMATCH_GAMEPLAYSTATE_HPP__

#include <GameState.hpp>
#include <BaseGameEntity.hpp>
#include <Utility/EventRouter.hpp>
#include <vector>

namespace StickMatch
{
	class InputBinder;
	class GameplayInputListener;

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

		virtual void Render( );

		virtual void SaveState( );
		virtual void RestoreState( );

		static GameplayState *Instance( );
		
		// When at the lobby screen, the characters will be set before the game
		// commences.  The first parameter is the character selected at the
		// selection screen, the second parameter is the type of character (AI,
		// local human, remote human), and the third is whether this character
		// is assigned to slot one or two
		ZED_UINT32 AssignCharacter( const ZED_UINT32 p_CharacterTypeID,
			const ZED_UINT32 p_Type, const ZED_UINT32 p_Slot );

		void Exit( );

	private:
		std::vector< BaseGameEntity * > m_Entities;

		InputBinder	*m_pInputBinder;

		GameplayInputListener	*m_pInputListener;

		ZED_BOOL	m_ExitState;
	};
}

#endif // __STICKMATCH_GAMEPLAYGAMESTATE_HPP__

