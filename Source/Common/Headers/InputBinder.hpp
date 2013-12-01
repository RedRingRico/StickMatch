#ifndef __STICKMATCH_INPUTBINDER_HPP__
#define __STICKMATCH_INPUTBINDER_HPP__

#include <System/Keyboard.hpp>
#include <System/Mouse.hpp>
#include <map>

namespace StickMatch
{
	typedef std::map< ZED_BYTE, ZED_UINT32 > KeyMap;

	class InputBinder
	{
	public:
		InputBinder( );
		~InputBinder( );

		ZED_UINT32 BindKey( const ZED_BYTE p_Key,
			const ZED_UINT32 p_Semantic );
		ZED_UINT32 BindButton( const ZED_UINT32 p_Button,
			const ZED_UINT32 p_Semantic );

		ZED_UINT32 Key( const ZED_BYTE p_Key );

	private:
		KeyMap m_Key;
	};
}

#endif

