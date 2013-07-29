#ifndef __STICKMATCH_GAME_HPP__
#define __STICKMATCH_GAME_HPP__

#include <System/DataTypes.hpp>
#include <System/Window.hpp>
#include <Renderer/Renderer.hpp>

namespace StickMatch
{
	class Game
	{
	public:
		Game( );
		~Game( );

		ZED_UINT32 Initialise( );
		ZED_UINT32 Execute( );

		void Render( );
		void Update( );

	private:
	};
}

#endif

