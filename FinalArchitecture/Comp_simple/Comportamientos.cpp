// Comportamientos.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Game/Game.h"

/*
Este es el main del jueg, aqui se instancia el juego, se llama a la logica y al render
*/

int _tmain(int argc, _TCHAR* argv[])
{
	CGame * myGame = NEW (CGame, ());
	myGame->Init();

	while (myGame->GetScreen()->IsOpened() && !myGame->GetScreen()->KeyPressed(GLFW_KEY_ESC))
	{
		//Logica
		myGame->Update();
		//Render
		myGame->Render();
	}

	myGame->End();

		return 0;
}

