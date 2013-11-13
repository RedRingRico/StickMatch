#include <StickFighter.hpp>

namespace StickMatch
{
	StickFighter::StickFighter( )
	{
		m_pModel = ZED_NULL;
	}

	StickFighter::~StickFighter( )
	{
		if( m_pModel )
		{
			delete m_pModel;
			m_pModel = ZED_NULL;
		}
	}

	void StickFighter::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	void StickFighter::Render( )
	{
		m_pModel->Render( );
	}
}

