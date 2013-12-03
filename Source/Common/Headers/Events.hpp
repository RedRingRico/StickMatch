#ifndef __STICKMATCH_EVENTS_HPP__
#define __STICKMATCH_EVENTS_HPP__

#include <Utility/Event.hpp>
#include <System/InputTypes.hpp>

namespace StickMatch
{
	const ZED::Utility::EventType KeyboardInputEventType( "Keyboard Input" );
	const ZED::Utility::EventType SemanticInputEventType( "Semantic Input" );

	class KeyboardInputEventData : public ZED::Utility::EventData
	{
	public:
		KeyboardInputEventData( );
		virtual ~KeyboardInputEventData( );

		ZED_UINT32 State( ZED_BYTE p_Key, ZED_BOOL p_State ) const
			{ p_Key = m_Key; p_State = m_State; return ZED_OK; }

		void State( const ZED_BYTE p_Key, const ZED_BOOL p_State )
			{ m_Key = p_Key; m_State = p_State; }

	private:
		ZED_BYTE	m_Key;
		ZED_BOOL	m_State;
	};

	class KeyboardEvent : public ZED::Utility::Event
	{
	public:
		ZED_EXPLICIT KeyboardEvent(
			KeyboardInputEventData *p_pData = ZED_NULL,
			ZED_UINT64 p_DispatchTime = ZED::System::GetTimeMiS( ) );
		virtual ~KeyboardEvent( );

		void State( const ZED_BYTE p_Key, const ZED_BOOL p_Status );

	private:
		KeyboardInputEventData	m_Keyboard;
	};

	class SemanticInputEventData : public ZED::Utility::EventData
	{
	public:
		SemanticInputEventData( );
		virtual ~SemanticInputEventData( );

		ZED_UINT32 Semantic( const ZED_UINT32 p_Semantic,
			const ZED_FLOAT32 p_Value );

		void Semantic( ZED_UINT32 p_Semantic, ZED_FLOAT32 p_Value ) const;

	private:
		ZED_UINT32	m_Semantic;
		ZED_FLOAT32	m_Value;
	};

	class SemanticInputEvent : public ZED::Utility::Event
	{
	public:
		ZED_EXPLICIT SemanticInputEvent(
			SemanticInputEventData *p_pData = ZED_NULL,
			ZED_UINT64 p_DispatchTime = ZED::System::GetTimeMiS( ) );

		virtual ~SemanticInputEvent( );

		void Semantic( const ZED_UINT32 p_Semantic,
			const ZED_FLOAT32 p_Value );

	private:
		SemanticInputEventData	m_Semantic;
	};
}

#endif

