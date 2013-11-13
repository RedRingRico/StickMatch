#include <BaseGameEntity.hpp>
#include <System/Memory.hpp>
#include <ctype.h>
#include <cstring>

namespace StickMatch
{
	BaseGameEntity::~BaseGameEntity( )
	{
		zedSafeDeleteArray( m_pName );
		zedSafeDelete( m_pModel );
	}

	ZED_UINT32 BaseGameEntity::ID( const ZED_CHAR8 *p_pName )
	{
		if( p_pName == ZED_NULL )
		{
			return ZED_FAIL;
		}

		ZED_MEMSIZE NameLength = strlen( p_pName );
		m_pName = new ZED_CHAR8 [ NameLength ];
		
		const ZED_UINT32 Base = 65521;
		const ZED_UINT32 Max = 5552;

		ZED_UINT32 Str1 = 0, Str2 = 0;

#define DO1( Buff, i ) Str1 += tolower( Buff[ i ] ); Str2 += Str1;
#define DO2( Buff, i ) DO1( Buff, i ); DO1( Buff, i );
#define DO4( Buff, i ) DO2( Buff, i ); DO2( Buff, i );
#define DO8( Buff, i ) DO4( Buff, i ); DO4( Buff, i+4 );
#define DO16( Buff ) DO8( Buff, 0 ); DO8( Buff, 0 );

		for( ZED_MEMSIZE StrLen = strlen( p_pName ); StrLen > 0; )
		{
			ZED_UINT32 K = StrLen < Max ? StrLen : Max;

			StrLen -= K;

			while( K >= 16 )
			{
				DO16( p_pName );
				p_pName += 16;
				K -= 16;
			}

			if( K != 0 )
			{
				do
				{
					Str1 += *p_pName++;
					Str2 += Str1;
				}while( --K );
			}

			Str1 % Base;
			Str2 % Base;
		}

		return ( ( Str2 << 16 ) | Str1 );

#undef DO1
#undef DO2
#undef DO4
#undef DO8
#undef DO16
	}

	ZED_UINT32 BaseGameEntity::Renderer( ZED::Renderer::Renderer *p_pRenderer )
	{
		if( p_pRenderer )
		{
			m_pRenderer = p_pRenderer;

			return ZED_OK;
		}

		return ZED_FAIL;
	}

	ZED_UINT32 BaseGameEntity::LoadModel( const ZED_CHAR8 *p_pFileName )
	{
		return m_pModel->Load( p_pFileName );
	}
}

