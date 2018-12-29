#include <iostream>
#include <stdio.h>

#include "../Game.h"

using namespace std;


int main(void)
{

	if (Game::getInstance()->Init())
	{
		Game::getInstance()->Run();
		
	}

	Game::getInstance()->Destroy();

	return 0;

}