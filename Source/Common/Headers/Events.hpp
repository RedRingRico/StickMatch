#ifndef __STICKMATCH_EVENTS_HPP__
#define __STICKMATCH_EVENTS_HPP__

#include <Utility/Event.hpp>

namespace StickMatch
{
	const ZED::Utility::EventType g_InputEvent( "InputEvent" );

	class InputEventData : public ZED::Utility::EventData
	{
	public:
		InputEventData( );
		virtual ~InputEventData( );

		ZED_UINT32	Type;
		void		*Value;
	};

	class InputEventListener : public ZED::Utility::EventListener
	{
	public:
		InputEventListener( );
		virtual ~InputEventListener( );

		virtual ZED_BOOL HandleEvent( const ZED::Utility::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const { return "a";}//g_InputEventName; }
	};
}

#endif

