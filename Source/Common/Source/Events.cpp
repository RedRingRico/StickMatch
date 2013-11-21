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
		ZED_FLOAT32 p_DispatchTime ) :
		ZED::Utility::Event( KeyboardInputEvent.Name( ), p_pData,
			p_DispatchTime )
	{
		m_pData = &m_Keyboard;
	}

	KeyboardEvent::~KeyboardEvent( )
	{
	}

	void KeyboardEvent::State( const ZED_KEYBOARDSTATE *p_pData )
	{
		m_Keyboard.State( p_pData );
	}
}

