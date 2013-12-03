#ifndef __STICKMATCH_GAMESTATEEVENTS_HPP__
#define __STICKMATCH_GAMESTATEEVENTS_HPP__

#include <Utility/Event.hpp>

namespace StickMatch
{
	class GameStateInputListener : public ZED::Utility::EventListener
	{
	public:
		GameStateInputListener( );
		virtual ~GameStateInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const
			{ return "Master Game State Input Listener"; }
	};
}

#endif

