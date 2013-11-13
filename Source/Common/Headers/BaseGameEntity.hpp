#ifndef __STICKMATCH_BASEGAMEENTITY_HPP__
#define __STICKMATCH_BASEGAMEENTITY_HPP__

#include <System/DataTypes.hpp>

namespace StickMatch
{
	class BaseGameEntity
	{
	public:
		virtual ~BaseGameEntity( );

		ZED_UINT32 ID( const ZED_CHAR8 *p_pName );

		ZED_UINT32 ID( ) const { return m_ID; }
		ZED_CHAR8 *Name( ) const { return m_pName; }

	protected:
		ZED_UINT32	m_ID;
		ZED_CHAR8	*m_pName;
	};
}

#endif // __STICKMATCH_BASEGAMEENTITY_HPP_0_

