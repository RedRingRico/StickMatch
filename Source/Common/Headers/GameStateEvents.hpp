#ifndef __STICKMATCH_GAMESTATEEVENTS_HPP__
#define __STICKMATCH_GAMESTATEEVENTS_HPP__

#include <Utility/Event.hpp>

namespace StickMatch
{
	class InputBinder;

	class GameStateInputListener : public ZED::Utility::EventListener
	{
	public:
		GameStateInputListener( );
		virtual ~GameStateInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const
			{ return "Master Game State Input Listener"; }
		
		ZED_UINT32 Binder( InputBinder *p_pInputBinder );

	private:
		InputBinder	*m_pInputBinder;
	};
}

#endif

