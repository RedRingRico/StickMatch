#include <Hardware.h>

Uint8 g_GDFSWorkingDirectory[ gdFsGetWorkSize( MAX_OPEN_FILES ) ];
Uint8 g_GDFSCurrentDirectory[ gdFsGetDirrecSize( GDFS_BUFFERS ) ];

Uint8 g_MapleRecvBuff[ 1024 * 24 * 2 + 32 ];
Uint8 g_MapleSendBuff[ 1024 * 24 * 2 + 32 ];

void hwInitialise( Int p_Mode, Int p_Frame, Int p_Count )
{
	Sint8 Error;
	Sint32 i;

	set_imask( 15 );

	syHwInit( );

	syMallocInit( HEAP_AREA, HEAP_SIZE );

	syStartGlobalConstructor( );

	kmInitDevice( KM_DREAMCAST );
	kmSetDisplayMode( p_Mode, p_Frame, TRUE, FALSE );
	kmSetWaitVsyncCount( p_Count );

	syHwInit2( );

	pdInitPeripheral( PDD_PLOGIC_ACTIVE, g_MapleRecvBuff, g_MapleSendBuff );

	syRtcInit( );

	set_imask( 0 );

	/* Set up GDFS */
	for( i = 8; i > 0; --i )
	{
		Error = gdFsInit( MAX_OPEN_FILES, g_GDFSWorkingDirectory, GDFS_BUFFERS,
			g_GDFSCurrentDirectory );

		if( ( Error == GDD_ERR_TRAYOPEND ) || ( Error == GDD_ERR_UNITATTENT ) )
		{	
			hwTerminate( );
			syBtExit( );
		}
		if( Error == GDD_ERR_OK )
		{
			break;
		}
	}

	if( i == 0 )
	{
		hwTerminate( );
		syBtExit( );
	}
}

void hwTerminate( void )
{
	gdFsFinish( );

	syRtcFinish( );

	pdExitPeripheral( );

	kmUnloadDevice( );

	syStartGlobalDestructor( );

	syMallocFinish( );

	syHwFinish( );

	set_imask( 15 );
}

