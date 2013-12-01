#include <InputBinder.hpp>

namespace StickMatch
{
	InputBinder::InputBinder( )
	{
	}

	InputBinder::~InputBinder( )
	{
	}

	ZED_UINT32 InputBinder::BindKey( const ZED_BYTE p_Key,
		const ZED_UINT32 p_Semantic )
	{
		m_Key[ p_Key ] = p_Semantic;

		return ZED_OK;
	}

	ZED_UINT32 InputBinder::BindButton( const ZED_UINT32 p_Button,
		const ZED_UINT32 p_Semantic )
	{
		return ZED_OK;
	}

	ZED_UINT32 InputBinder::Key( const ZED_BYTE p_Key )
	{
		KeyMap::const_iterator Itr = m_Key.find( p_Key );

		if( Itr == m_Key.end( ) )
		{
			return 0;
		}

		return Itr->second;
	}
}

