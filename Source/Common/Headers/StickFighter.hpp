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

		ZED_UINT32 Character( const ZED_UINT32 p_Character );

		void Type( const ZED_UINT32 p_Type ) { m_Type = p_Type; }

	protected:
		ZED_UINT32	m_Type;

	private:
		ZED_UINT32 PreInitialise( );
	};
}

#endif

