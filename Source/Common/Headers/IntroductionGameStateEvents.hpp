#ifndef __STICKMATCH_INTRODUCTIONGAMESTATEEVENTS_HPP__
#define __STICKMATCH_INTRODUCTIONGAMESTATEEVENTS_HPP__

#include <Utility/Event.hpp>

namespace StickMatch
{
	const ZED_UINT32 INTRODUCTION_SKIP	= 9000;

	class IntroductionGameState;

	class IntroductionInputListener : public ZED::Utility::EventListener
	{
	public:
		ZED_EXPLICIT IntroductionInputListener(
			IntroductionGameState *p_pGameState );
		virtual ~IntroductionInputListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const
			{ return "Introduction Input Listener"; }

	private:
		IntroductionGameState *m_pIntroductionGameState;
	};
}

#endif // __STICKMATCH_INTRODUCTIONGAMESTATEEVENTS_HPP__

