#include <StickFighter.hpp>
#include <System/Memory.hpp>
#include <System/File.hpp>

namespace StickMatch
{
	StickFighter::StickFighter( ) :
		m_Type( 0 )
	{
		m_pModel = ZED_NULL;
	}

	StickFighter::~StickFighter( )
	{
		zedSafeDelete( m_pModel );
	}

	ZED_UINT32 StickFighter::Initialise( )
	{
		if( this->PreInitialise( ) != ZED_OK )
		{
			return ZED_FAIL;
		}

		if( m_pModel == ZED_NULL )
		{
			return ZED_FAIL;
		}

		return ZED_OK;
	}

	void StickFighter::Update( const ZED_UINT64 p_ElapsedTime )
	{
	}

	void StickFighter::Render( )
	{
		m_pModel->Render( );
	}

	ZED_UINT32 StickFighter::Character( const ZED_UINT32 p_Character )
	{
		ZED_CHAR8 *pBaseDirectory = new ZED_CHAR8[ 256 ];
		ZED::System::GetExecutablePath( &pBaseDirectory, 256 );

		ZED_CHAR8 *pModelPath = new ZED_CHAR8[ 256 ];
		strncpy( pModelPath, pBaseDirectory, strlen( pBaseDirectory ) );

		ZED_CHAR8 *pModelFile = new ZED_CHAR8[ 256 ];

		switch( p_Character )
		{
			case 1:
			{
				strncpy( pModelFile, "../GameMedia/Models/TestFighter.zed",
					strlen( "../GameMedia/Models/TestFighter.zed" ) );
				break;
			}
			default:
			{
				strncpy( pModelFile, "../GameMedia/Models/TestFighter.zed",
					strlen( "../GameMedia/Models/TestFighter.zed" ) );
				break;
			}
		}

		strncpy( pModelPath+strlen( pModelPath ), pBaseDirectory,
			strlen( pModelFile ) );
		m_pModel->Load( pModelPath );

		zedSafeDeleteArray( pBaseDirectory );
		zedSafeDeleteArray( pModelPath );
		zedSafeDeleteArray( pModelFile );

		return ZED_OK;
	}
}

