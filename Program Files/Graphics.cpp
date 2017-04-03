#include "Graphics.h"
#include "Particle.h"			//the header files that need to be included. Ok to include these inside cpp files
#include "Hash.h"
#include "SDL_ttf.h"


Graphics::Graphics()
{
	SCREEN_HEIGHT = 800;			//sets a default screen width/height
	SCREEN_WIDTH = 800;
	
	window = NULL;
    screenSurface = NULL;			//makes the window, surface and renderer null
	renderer = NULL;
	
	m_end = 0;						//setting default values for variables
	m_deltaTime = 0;
	
	
	//code below is used to initliase SDL2
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
	}
	else{
		window = SDL_CreateWindow("Spatial Particle Hashing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if(window == NULL)
		{
			printf("SDL could not create window! SDL_Error: %s\n", SDL_GetError());
		}
		else{
			screenSurface = SDL_GetWindowSurface(window);		
			
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
			
			if(renderer == NULL)
			{
				printf("SDL could not create renderer! SDL_Error: %s\n", SDL_GetError());
			}			
		}		
	}	

}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);			//when the sdl class is deleted it will destroy the window and quit
	SDL_Quit();
}

SDL_Keycode Graphics::FirstUpdate()
{	
	m_deltaTime = (double)(clock() - m_end) / 1000.0f;						//work out delta time
	m_end = clock();														//update the time so you it can workout delta time next frame
	
	SDL_PollEvent(&event);													//poll for events

	SDL_SetRenderDrawColor(renderer, 0, 0, 0,0);							//set the default background to black
	
	SDL_RenderClear(renderer);												//clear the renderer
	//SDL_SetRenderDrawColor(renderer, 108, 149, 90, 255);
	SDL_SetRenderDrawColor(renderer, 174, 174, 174, 100);					//set a draw colour for the lines which display the buckets
	
	if(event.type == SDL_QUIT)												//if the user has pressed the exit button
	{		
		return SDLK_ESCAPE;													//for ease in code return escape as they will have the same functionaility
	}
	if(event.type == SDL_KEYDOWN)											//if a key has been pressed
	{
		return event.key.keysym.sym;										//return the key press
	}	
	return true;															//else return true
}

void Graphics::FlipScreen()
{	
	SDL_RenderPresent(renderer);    										//renders the render to the screen
}

void Graphics::DrawLine(std::weak_ptr<Hash> _hashTable)
{
	std::shared_ptr<Hash> tempHashTable = _hashTable.lock();				//to save multiple locks which use more cpu cycles
	for(int i = 0; i < tempHashTable->GetColumnAmount(); i++)				//for every column (same amount of columns as there are rows)
	{
		SDL_RenderDrawLine(renderer, tempHashTable->GetGridWidth() * i, 0, tempHashTable->GetGridWidth() * i, SCREEN_HEIGHT);	//draw a line for the row			-> used to show the buckets
		SDL_RenderDrawLine(renderer, 0, tempHashTable->GetGridHeight() * i, SCREEN_WIDTH, tempHashTable->GetGridHeight() * i);	//draw a line for the column
	}
}

void Graphics::Draw(vec2 _position, int _hashValue)							//take a position and hash value
{
	if(_hashValue % 3 == 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	
	}
	else if(_hashValue % 3 == 1)											//depending on the modulus of the hash value it will draw a different colour
	{																		//this is so it is easier to see the particles changing between buckets
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);	
	}
	else{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	SDL_RenderDrawPoint(renderer, _position.x, _position.y);				//render a single pixel for the particle
}

void Graphics::FPS(bool _display)											
{
	int currentFPS = 1.0 / m_deltaTime;										//works out how long it took to generate the current frame by dividing 1.0 by the delta time 
	m_averageFPS = (m_averageFPS + currentFPS) / 2;							//gets the previous average and works out the new average
}