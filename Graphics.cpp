#include "Graphics.h"

Graphics::Graphics()
{
	SCREEN_HEIGHT = 800;
	SCREEN_WIDTH = 800;
	
	window = NULL;
    screenSurface = NULL;
	renderer = NULL;
	
	m_begin = 0;
	m_end = 0;
	m_deltaTime = 0;
	
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
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Graphics::FirstUpdate()
{	
	m_deltaTime = (double)(clock() - m_end) / 1000.0f;
	// if(m_deltaTime == 0)
	// {
		// m_deltaTime = 0.001;
	// }
	m_end = clock();
	//std::cout << m_deltaTime << std::endl;
	
	
	SDL_PollEvent(&event);		

	SDL_SetRenderDrawColor(renderer, 0, 0, 0,0);
	
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	
	if(event.type == SDL_QUIT)
	{		
		return false;
	}
	if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_ESCAPE)
		{
			return false;			
		}
	}
	
	
	return true;	
}

void Graphics::FlipScreen()
{	
	SDL_RenderPresent(renderer);
    	
}

void Graphics::Draw(int _positionX, int _positionY)
{
	SDL_RenderDrawPoint(renderer, _positionX, _positionY);
}