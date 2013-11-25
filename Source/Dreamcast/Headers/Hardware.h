#ifndef __STICKMATCH_HARDWARE_H__
#define __STICKMATCH_HARDWARE_H__

#include <shinobi.h>
#include <sg_syhw.h>
#include <kamui2.h>

extern Uint8 *_BSG_END;

/* SH-4 program area address */
#define P1AREA 0x80000000
/* Work RAM end address [16MiB] */
#define WORK_END ( ( ( Uint32 ) _BSG_END ) & 0xE0000000 | 0x0D000000 )

#define HEAP_AREA ( ( void *)( ( ( ( Uint32 ) _BSG_END | P1AREA ) & 0xFFFFFFE0 ) + 0x20 ) )
#define HEAP_SIZE ( WORK_END - ( Uint32 )HEAP_AREA )

#define MAX_OPEN_FILES	8
#define GDFS_BUFFERS	1024

void hwInitialise( Int p_Mode, Int p_Frame, Int p_Count );
void hwTerminate( void );

#endif

