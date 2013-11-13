#ifndef __STICKMATCH_STICKFIGHTER_HPP__
#define __STICKMATCH_STICKFIGHTER_HPP__

#include <BaseGameEntity.hpp>
#include <Renderer/Model.hpp>
#include <Renderer/Renderer.hpp>

namespace StickMatch
{
	static ZED_CHAR8 *g_pStickFighterName = "Stick Fighter";

	class StickFighter : public BaseGameEntity
	{
	public:
		StickFighter( );
		virtual ~StickFighter( );

		virtual ZED_UINT32 Initialise( );

		virtual void Update( const ZED_UINT64 p_ElapsedTime );

		virtual void Render( );

	protected:
		ZED::Renderer::Model	*m_pModel;
	};
}

#endif

