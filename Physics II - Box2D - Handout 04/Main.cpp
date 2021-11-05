#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include <time.h>

#include <iostream>
#include <chrono>
#include <stack>
using namespace std;


#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};
int main(int argc, char ** argv)
{
	LOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;



	while (state != MAIN_EXIT)
	{
		double t = 0.0;
		float dt = 16.0;

		//TIC
		auto start = chrono::steady_clock::now();

		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;


		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with ERROR");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
		//TOC
		auto end = chrono::steady_clock::now();
		//Check en salida de la diferencia de temps
		auto telapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		//Entra si hay diferencia de tiempo
		if (dt - telapsed > 0.0f) 
			//Para el programa el tiempo restante
			Sleep(dt - telapsed);
	}

	delete App;
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}