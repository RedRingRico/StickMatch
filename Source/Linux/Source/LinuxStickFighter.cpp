#include <StickFighter.hpp>
#include <Renderer/OGL/GLModel.hpp>

namespace StickMatch
{
	ZED_UINT32 StickFighter::PreInitialise( )
	{
		m_pModel = new ZED::Renderer::GLModel( m_pRenderer );

		return ZED_OK;
	}
}

