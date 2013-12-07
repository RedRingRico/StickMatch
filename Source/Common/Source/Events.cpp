#include <Events.hpp>
#include <System/Debugger.hpp>
#include <System/Memory.hpp>

namespace StickMatch
{
	KeyboardInputEventData::KeyboardInputEventData( )
	{
	}

	KeyboardInputEventData::~KeyboardInputEventData( )
	{
	}

	ZED_UINT32 KeyboardInputEventData::GetState( ZED_BYTE &p_Key,
		ZED_BOOL &p_State ) const
	{
		p_Key = m_Key;
		p_State = m_State;

		return ZED_OK;
	}

	void KeyboardInputEventData::SetState( const ZED_BYTE p_Key,
		const ZED_BOOL p_State )
	{
		m_Key = p_Key;
		m_State = p_State;
	}

	KeyboardEvent::KeyboardEvent( KeyboardInputEventData *p_pData,
		ZED_UINT64 p_DispatchTime ) :
		ZED::Utility::Event( KeyboardInputEventType.Name( ), p_pData,
			p_DispatchTime )
	{
		m_pData = p_pData;
	}

	KeyboardEvent::~KeyboardEvent( )
	{
	}

	void KeyboardEvent::State( const ZED_BYTE p_Key, const ZED_BOOL p_State )
	{
		m_Keyboard.SetState( p_Key, p_State );
	}

	SemanticInputEventData::SemanticInputEventData( )
	{
	}

	SemanticInputEventData::~SemanticInputEventData( )
	{
	}

	ZED_UINT32 SemanticInputEventData::SetSemantic(
		const ZED_UINT32 p_Semantic,
		const ZED_FLOAT32 p_Value )
	{
		m_Semantic = p_Semantic;
		ZED_FLOAT32 Value = p_Value;

		if( p_Value < 0.0f )
		{
			Value = 0.0f;
		}

		if( p_Value > 1.0f )
		{
			Value = 1.0f;
		}

		m_Value = Value;

		return ZED_OK;
	}

	void SemanticInputEventData::GetSemantic( ZED_UINT32 &p_Semantic,
		ZED_FLOAT32 &p_Value ) const
	{
		p_Semantic = m_Semantic;
		p_Value = m_Value;
	}

	SemanticInputEvent::SemanticInputEvent( SemanticInputEventData *p_pData,
		ZED_UINT64 p_DispatchTime ) :
			ZED::Utility::Event( SemanticInputEventType.Name( ), p_pData,
				p_DispatchTime )
	{
		m_pData = p_pData;
	}

	SemanticInputEvent::~SemanticInputEvent( )
	{
	}

	void SemanticInputEvent::Semantic( const ZED_UINT32 p_Semantic,
		const ZED_FLOAT32 p_Value )
	{
		zedTrace( "Setting semantic: %d\n", p_Semantic );
		m_Semantic.SetSemantic( p_Semantic, p_Value );
	}
}

