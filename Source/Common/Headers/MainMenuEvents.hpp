#ifndef __STICKMATCH_MAINMENUEVENTS_HPP__
#define __STICKMATCH_MAINMENUEVENTS_HPP__

#include <Utility/Event.hpp>

namespace StickMatch
{
	class InputListener : public ZED::Utility::EventListener
	{
	public:
		InputListener( );
		virtual ~InputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const { return "Main Menu Input Listener"; }
	};
}

#endif

