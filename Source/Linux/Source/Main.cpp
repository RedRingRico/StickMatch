#include <System/Debugger.hpp>
#include <GitVersion.hpp>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	zedTrace( "StickMatch [Rev. %s]\n", GIT_COMMITHASH );

	StickMatch::Game TheGame;
	if( TheGame.Initialise( ) != ZED_OK )
	{
		zedTrace( "[main] Failed to initialise the game!\n" );
		return 0;
	}

	return TheGame.Execute( );
}

