#ifndef __STICKMATCH_MAINMENUEVENTS_HPP__
#define __STICKMATCH_MAINMENUEVENTS_HPP__

#include <Utility/Event.hpp>

namespace StickMatch
{
	const ZED_UINT32 MAIN_MENU_START_GAME	= 9001;

	class MainMenuState;

	class MainMenuInputListener : public ZED::Utility::EventListener
	{
	public:
		MainMenuInputListener( );
		virtual ~MainMenuInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const { return "Main Menu Input Listener"; }

		void SetMainMenuState( MainMenuState *p_pMainMenu );

	private:
		MainMenuState	*m_pMainMenu;	
	};
}

#endif

