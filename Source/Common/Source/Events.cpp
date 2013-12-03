#include <Events.hpp>
#include <System/Memory.hpp>

namespace StickMatch
{
	KeyboardInputEventData::KeyboardInputEventData( )
	{
	}

	KeyboardInputEventData::~KeyboardInputEventData( )
	{
	}

	KeyboardEvent::KeyboardEvent( KeyboardInputEventData *p_pData,
		ZED_UINT64 p_DispatchTime ) :
		ZED::Utility::Event( KeyboardInputEventType.Name( ), p_pData,
			p_DispatchTime )
	{
		m_pData = &m_Keyboard;
	}

	KeyboardEvent::~KeyboardEvent( )
	{
	}

	void KeyboardEvent::State( const ZED_BYTE p_Key, const ZED_BOOL p_State )
	{
		m_Keyboard.State( p_Key, p_State );
	}

	SemanticInputEventData::SemanticInputEventData( )
	{
	}

	SemanticInputEventData::~SemanticInputEventData( )
	{
	}

	ZED_UINT32 SemanticInputEventData::Semantic( const ZED_UINT32 p_Semantic,
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
		m_Semantic.Semantic( p_Semantic, p_Value );
	}
}

