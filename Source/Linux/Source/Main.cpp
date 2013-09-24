#include <GitVersion.hpp>
#include <Game.hpp>
#include <iostream>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "StickMatch [Rev. " << GIT_COMMITHASH  << "]" << std::endl;

	StickMatch::Game TheGame;
	if( TheGame.Initialise( ) == 0 )
	{
		std::cout << "[main] Failed to initialise the game!" << std::endl;
		return 0;
	}

	return TheGame.Execute( );
}

