#include <shinobi.h>
#include <kamui2.h>
#include <sg_syCbl.h>
#include <sg_Chain.h>
#include <Hardware.h>

#define TEXTUREMEMORYSIZE	( 0x400000 )
#define MAXTEXTURES			( 4096 )
#define MAXSMALLVQ			( 0 )

#define VERTEXBUFFERSIZE	( 0x40000 )

#define VSYNC_PRIORITY		( 0x90 )

PDS_PERIPHERAL	*g_pController[ 4 ];

void *( *MallocPtr )( unsigned long ) = syMalloc;
void ( *FreePtr )( void * ) = syFree;
BOOL g_Run;
volatile KMDWORD g_VSync = KM_TRUE;
KMSTRIPHEAD	StripHead_01;

KMSTRIPCONTEXT DefaultContext =
{
	0x90,
	{
		KM_OPAQUE_POLYGON, KM_USERCLIP_DISABLE, KM_NORMAL_POLYGON,
		KM_FLOATINGCOLOR, KM_FALSE, KM_TRUE
	},
	{
		KM_GREATER, KM_CULLCCW, KM_FALSE, KM_FALSE, 0
	},
	{
		0, 0
	},
	{
		KM_ONE, KM_ZERO, KM_FALSE, KM_FALSE, KM_NOFOG, KM_FALSE, KM_FALSE,
		KM_FALSE, KM_NOFLIP, KM_NOCLAMP, KM_BILINEAR, KM_FALSE,
		KM_MIPMAP_D_ADJUST_1_00, KM_MODULATE, 0, 0
	}
};

#pragma aligndata32( TextureWorkArea)
KMDWORD TextureWorkArea[ MAXTEXTURES * 24 / 4 + MAXSMALLVQ * 76 / 4 ];

#define Align32Malloc	( *MallocPtr )
#define Align32Free		( *FreePtr )

#define Align32Byte( pAddr ) ( ( ( ( long ) pAddr ) + 0x1F ) & 0xFFFFFFE0 )

#define SH4_P1CachedMem( pAddr ) ( ( ( ( long )pAddr ) & 0x0FFFFFFF ) | 0x80000000 )
#define SH4_P2NonCachedMem( pAddr ) ( ( ( ( long )pAddr ) & 0x0FFFFFFF ) | 0xA0000000 )

KMVOID PALCallback( PKMVOID p_pArgs )
{
	PKMPALEXTINFO pInfo;

	pInfo = ( PKMPALEXTINFO )p_pArgs;
	pInfo->nPALExtMode = KM_PALEXT_HEIGHT_RATIO_1_133;

	return;
}

void *_Align32Malloc( unsigned long p_Size )
{
	void *pPtr, *pAlignedPtr;

	p_Size = ( p_Size + 0x1F ) & 0xFFFFFFE0;

	pPtr = syMalloc( p_Size + 32 );

	pAlignedPtr = ( void * )( ( ( ( long ) pPtr ) + 0x20 ) & 0xFFFFFFE0 );

	*( ( char * ) pAlignedPtr - 1 ) = ( char )( ( long ) pAlignedPtr - ( long ) pPtr );

	return ( pAlignedPtr );
}

void _Align32Free( void *p_pPtr )
{
	char Diff;

	Diff = *( ( char * ) p_pPtr - 1 );
	p_pPtr = ( void * )( ( long ) p_pPtr - Diff );

	syFree( p_pPtr );
}

void Init32Malloc( void )
{
	char *pPtr1, *pPtr2;

	MallocPtr = syMalloc;
	FreePtr = syFree;

	pPtr1 = syMalloc( 1 );
	pPtr2 = syMalloc( 1 );

	if( ( ( long ) pPtr1 & 0x1F ) || ( ( long ) pPtr2 & 0x1F ) )
	{
		MallocPtr = _Align32Malloc;
		FreePtr = _Align32Free;
	}

	syFree( pPtr1 );
	syFree( pPtr2 );
}


KMVOID RenderCallback( PKMVOID p_pArgs )
{
	KMVERTEX_01 Background[ 16 ];
	float Red, Green, Blue;

	if( g_Run )
	{
		Red = 0.14f;
		Green = 0.0f;
		Blue = 0.14f;
	}
	else
	{
		Red = 1.0f;
		Green = 0.0f;
		Blue = 0.0f;
	}

	if( g_VSync == KM_TRUE )
	{
		Background[ 0 ].ParamControlWord = KM_VERTEXPARAM_NORMAL;
		Background[ 0 ].fX = 0.0f;
		Background[ 0 ].fY = 479.0f;
		Background[ 0 ].u.fZ = 0.2f;
		Background[ 0 ].fBaseAlpha = 1.0f;
		Background[ 0 ].fBaseRed = Red;
		Background[ 0 ].fBaseGreen = Green;
		Background[ 0 ].fBaseBlue = Blue;

		Background[ 1 ].ParamControlWord = KM_VERTEXPARAM_NORMAL;
		Background[ 1 ].fX = 0.0f;
		Background[ 1 ].fY = 0.0f;
		Background[ 1 ].u.fZ = 0.2f;
		Background[ 1 ].fBaseAlpha = 1.0f;
		Background[ 1 ].fBaseRed = Red;
		Background[ 1 ].fBaseGreen = Green;
		Background[ 1 ].fBaseBlue = Blue;

		Background[ 2 ].ParamControlWord = KM_VERTEXPARAM_ENDOFSTRIP;
		Background[ 2 ].fX = 639.0f;
		Background[ 2 ].fY = 479.0f;
		Background[ 2 ].u.fZ = 0.2f;
		Background[ 2 ].fBaseAlpha = 1.0f;
		Background[ 2 ].fBaseRed = Red;
		Background[ 2 ].fBaseGreen = Green;
		Background[ 2 ].fBaseBlue = Blue;

		kmSetBackGround( &StripHead_01, KM_VERTEXTYPE_01,
			&Background[ 0 ], &Background[ 1 ], &Background[ 2 ] );

		g_VSync = KM_FALSE;
	}	
}

KMVOID VSyncCallback( PKMVOID p_pArgs )
{
	g_VSync = KM_TRUE;

	return;
}

int main( void )
{
	KMSYSTEMCONFIGSTRUCT	KamuiConfig;
	SYCHAIN					VSyncChainID;
	PKMSURFACEDESC			FrameBufferSurfaces[ 2 ];
	KMSURFACEDESC			FrontSurface;
	KMSURFACEDESC			BackSurface;
	PKMDWORD				pVertexBuffer;
	KMVERTEXBUFFDESC		VertexBufferDesc;

	switch( syCblCheck( ) )
	{	
		case SYE_CBL_NTSC:
		{
			hwInitialise( KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1 );
			break;
		}
		case SYE_CBL_PAL:
		{
			hwInitialise( KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, 1 );
			kmSetPALEXTCallback( PALCallback, NULL );
			kmSetDisplayMode( KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565,
				TRUE, FALSE );
			break;
		}
		case SYE_CBL_VGA:
		{
			hwInitialise( KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1 );
			break;
		}
		default:
		{
			syBtExit( );
			break;
		}
	}

	Init32Malloc( );

	VSyncChainID = syChainAddHandler( SYD_CHAIN_EVENT_IML6_VBLANK,
		VSyncCallback, VSYNC_PRIORITY, NULL );

	kmSetEORCallback( RenderCallback, NULL );

	KamuiConfig.dwSize = sizeof( KMSYSTEMCONFIGSTRUCT );
	KamuiConfig.flags = KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER |
						KM_CONFIGFLAG_NOWAITVSYNC |
						KM_CONFIGFLAG_ENABLE_2V_LATENCY;

	/* Frame buffer */
	FrameBufferSurfaces[ 0 ] = &FrontSurface;
	FrameBufferSurfaces[ 1 ] = &BackSurface;
	KamuiConfig.ppSurfaceDescArray = FrameBufferSurfaces;
	KamuiConfig.fb.nNumOfFrameBuffer = 2;
	KamuiConfig.fb.nStripBufferHeight = 32;

	/* Texture handler */
	KamuiConfig.nTextureMemorySize = TEXTUREMEMORYSIZE;
	KamuiConfig.nNumOfTextureStruct = MAXTEXTURES;
	KamuiConfig.nNumOfSmallVQStruct = MAXSMALLVQ;
	KamuiConfig.pTextureWork = TextureWorkArea;

	pVertexBuffer = ( PKMDWORD )Align32Malloc( VERTEXBUFFERSIZE );

	KamuiConfig.pVertexBuffer =
		( PKMDWORD )SH4_P2NonCachedMem( pVertexBuffer );
	KamuiConfig.pBufferDesc = &VertexBufferDesc;
	KamuiConfig.nVertexBufferSize = VERTEXBUFFERSIZE;
	KamuiConfig.nNumOfVertexBank = 1;

	KamuiConfig.nPassDepth = 1;
	KamuiConfig.Pass[ 0 ].dwRegionArrayFlag = KM_PASSINFO_AUTOSORT;

	KamuiConfig.Pass[ 0 ].nDirectTransferList = KM_OPAQUE_POLYGON;
	KamuiConfig.Pass[ 0 ].fBufferSize[ 0 ] = 0.0f;
	KamuiConfig.Pass[ 0 ].fBufferSize[ 1 ] = 0.0f;
	KamuiConfig.Pass[ 0 ].fBufferSize[ 2 ] = 50.0f;
	KamuiConfig.Pass[ 0 ].fBufferSize[ 3 ] = 0.0f;
	KamuiConfig.Pass[ 0 ].fBufferSize[ 4 ] = 50.0f;

	kmSetSystemConfiguration( &KamuiConfig );

	memset( &StripHead_01, 0, sizeof( StripHead_01 ) );
	kmGenerateStripHead01( &StripHead_01, &DefaultContext );

	g_Run = TRUE;

	RenderCallback( NULL );

	while( g_Run == TRUE )
	{
		g_pController[ 0 ] = pdGetPeripheral( PDD_PORT_A0 );

		kmBeginScene( &KamuiConfig );
		kmBeginPass( &VertexBufferDesc );
		kmEndPass( &VertexBufferDesc );
		kmRender( KM_RENDER_FLIP );
		kmEndScene( &KamuiConfig );

		if( g_pController[ 0 ]->press & PDD_DGT_ST )
		{
			g_Run = FALSE;
		}

		pdExecPeripheralServer( );
	}

	syChainDeleteHandler( VSyncChainID );

	hwTerminate( );

	syBtExit( );

	return 0;
}

