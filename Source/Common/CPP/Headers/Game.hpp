#ifndef __STICKMATCH_GAME_HPP__
#define __STICKMATCH_GAME_HPP__

#include <DataTypes.hpp>

namespace StickMatch
{
	class Game
	{
	public:
		Game( );
		~Game( );

		uint32 Initialise( );
		uint32 Execute( );

		void Render( );
		void Update( );

	private:
	};
}

#endif

