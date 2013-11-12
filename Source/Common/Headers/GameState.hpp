#ifndef __STICKMATCH_GAMESTATE_HPP__
#define __STICKMATCH_GAMESTATE_HPP__

#include <GameStateManager.hpp>
#include <GameAttributes.hpp>
#include <System/DataTypes.hpp>

namespace StickMatch
{
	class GameState
	{
	public:
		virtual ~GameState( ) { }

		virtual ZED_UINT32 Enter( GameStateManager *p_pManager,
			const GameAttributes &p_GameAttributes ) = 0;
		virtual void Exit( GameStateManager *p_pManager ) = 0;

		virtual void Update( GameStateManager *p_pManager,
			const ZED_UINT64 p_MicroSeconds ) = 0;

		virtual void SaveState( ) = 0;
		virtual void RestoreState( ) = 0;

	protected:
		GameAttributes	m_GameAttributes;
		ZED_UINT64		m_ElapsedTime;
	};
}

#endif // __STICKMATCH_GAMESTATE_HPP__

