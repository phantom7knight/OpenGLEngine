#include <iostream>
#include <stdio.h>

#include "../Game.h"

using namespace std;

//Lerp Template function

template <class T>
T Lerp(T v0, T v1, float t)
{
	return (1 - t) * v0 + t * v1;
}


int main(void)
{

	//Game *gameState = new Game();
	if (Game::getInstance()->Init())
	{
		Game::getInstance()->Run();
		
		Game::getInstance()->Update();
	}

	Game::getInstance()->Destroy();

	return 0;

}