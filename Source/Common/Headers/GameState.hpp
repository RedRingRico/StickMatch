#ifndef __STICKMATCH_GAMESTATE_HPP__
#define __STICKMATCH_GAMESTATE_HPP__

#include <System/DataTypes.hpp>

namespace StickMatch
{
	class GameState
	{
	public:
		virtual ~GameState( );

		virtual ZED_UINT32 Enter( ) = 0;
		virtual void Exit( ) = 0;

		virtual void Update( const ZED_UINT64 p_MicroSeconds ) = 0;

		virtual void SaveState( ) = 0;
		virtual void RestoreState( ) = 0;
	};
}

#endif // __STICKMATCH_GAMESTATE_HPP__

