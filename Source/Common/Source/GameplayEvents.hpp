#ifndef __STICKMATCH_EVENTS_HPP__
#define __STICKMATCH_EVENTS_HPP__

#include <Utility/Event.hpp>
#include <System/InputTypes.hpp>

namespace StickMatch
{
	const ZED::Utility::EventType KeyboardInputEvent( "Keyboard Input" );

	class KeyboardInputEventData : public ZED::Utility::EventData
	{
	public:
		KeyboardInputEventData( );
		virtual ~KeyboardInputEventData( );

		ZED_KEYBOARDSTATE State( ) const
			{ return m_State; }

		void State( const ZED_KEYBOARDSTATE *p_pState )
			{ m_State = ( *p_pState ); }

	private:
		ZED_KEYBOARDSTATE	m_State;
	};

	class KeyboardEvent : public ZED::Utility::Event
	{
	public:
		ZED_EXPLICIT KeyboardEvent(
			KeyboardInputEventData *p_pData = ZED_NULL,
			ZED_FLOAT32 p_DispatchTiem = ZED::System::GetTimeMiS( ) );
		virtual ~KeyboardEvent( );

		void State( const ZED_KEYBOARDSTATE *p_pData );

	private:
		KeyboardInputEventData	m_Keyboard;
	};
}

#endif

