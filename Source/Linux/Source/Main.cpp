#include <System/Debugger.hpp>
#include <GitVersion.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	zedTrace( "StickMatch [Rev. %s]\n", GIT_COMMITHASH );
	return 0;
}

