#ifndef __STICKMATCH_BASEGAMEENTITY_HPP__
#define __STICKMATCH_BASEGAMEENTITY_HPP__

#include <System/DataTypes.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/Model.hpp>

namespace StickMatch
{
	class BaseGameEntity
	{
	public:
		virtual ~BaseGameEntity( );

		ZED_UINT32 ID( const ZED_CHAR8 *p_pName );

		ZED_UINT32 ID( ) const { return m_ID; }
		ZED_CHAR8 *Name( ) const { return m_pName; }

		virtual ZED_UINT32 Initialise( ) = 0;

		virtual void Update( const ZED_UINT64 p_ElapsedTime ) = 0;

		virtual void Render( ) = 0;

		ZED_UINT32 Renderer( ZED::Renderer::Renderer *p_pRenderer );

		ZED_UINT32 LoadModel( const ZED_CHAR8 *p_pFileName );

	protected:
		ZED_UINT32	m_ID;
		ZED_CHAR8	*m_pName;

		ZED::Renderer::Renderer	*m_pRenderer;
		ZED::Renderer::Model	*m_pModel;
	};
}

#endif // __STICKMATCH_BASEGAMEENTITY_HPP_0_

