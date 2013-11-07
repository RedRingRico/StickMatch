#include <iostream>
#include <Game.hpp>

int main( int p_Argc, char **p_ppArgv )
{
	std::cout << "StickMatch" << std::endl;

	StickMatch::Game TheGame;

	if( TheGame.Initialise( ) != ZED_OK )
	{
		std::cout << "[StickMatch::main] <ERROR> Failed to initialise the "
			"game" << std::endl;

		return ZED_FAIL;
	}

	return TheGame.Execute( );
}

