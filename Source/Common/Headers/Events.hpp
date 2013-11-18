#ifndef __STICKMATCH_EVENTS_HPP__
#define __STICKMATCH_EVENTS_HPP__

#include <System/Event.hpp>

namespace StickMatch
{
	const ZED_CHAR8 g_InputEventName[ ] = "Input Event";
	const ZED_UINT32 g_InputEventID =
		ZED::System::EventType::HashName( g_InputEventName );
	const ZED::System::EventType g_InputEvent( g_InputEventName );

	class InputEventType : public ZED::System::EventType
	{
	public:
	};

	class InputEventData : public ZED::System::EventData
	{
	public:
		InputEventData( );
		virtual ~InputEventData( );

		ZED_UINT32	Type;
		void		*Value;
	};

	class InputEvent : public ZED::System::Event
	{
	public:
		InputEvent( );
		virtual ~InputEvent( );
	};

	class InputEventListener : public ZED::System::EventListener
	{
	public:
		InputEventListener( );
		virtual ~InputEventListener( );

		virtual ZED_BOOL HandleEvent( const ZED::System::Event &p_Event );

		virtual ZED_CHAR8 *Name( ) const { return "a";}//g_InputEventName; }
	};
}

#endif

