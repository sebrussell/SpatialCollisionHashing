#include "Graphics.h"
#include "Particle.h"
#include "Hash.h"


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

SDL_Keycode Graphics::FirstUpdate()
{	
	m_deltaTime = (double)(clock() - m_end) / 1000.0f;
	m_end = clock();
	
	SDL_PollEvent(&event);		

	SDL_SetRenderDrawColor(renderer, 0, 0, 0,0);
	
	SDL_RenderClear(renderer);
	//SDL_SetRenderDrawColor(renderer, 108, 149, 90, 255);
	SDL_SetRenderDrawColor(renderer, 174, 174, 174, 100);
	
	if(event.type == SDL_QUIT)
	{		
		return SDLK_ESCAPE;
	}
	if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == SDLK_w)
		{
			std::cout << m_averageFPS << std::endl;
		}
		return event.key.keysym.sym;
	}
	
	return true;	
}

void Graphics::FlipScreen()
{	
	SDL_RenderPresent(renderer);    	
}

void Graphics::DrawLine(std::weak_ptr<Hash> _hashTable)
{
	std::shared_ptr<Hash> tempHashTable = _hashTable.lock();
	for(int i = 0; i < tempHashTable->GetColumnAmount(); i++)
	{
		SDL_RenderDrawLine(renderer, tempHashTable->GetGridWidth() * i, 0, tempHashTable->GetGridWidth() * i, SCREEN_HEIGHT);
		SDL_RenderDrawLine(renderer, 0, tempHashTable->GetGridHeight() * i, SCREEN_WIDTH, tempHashTable->GetGridHeight() * i);
	}
}

void Graphics::Draw(vec2 _position, int _hashValue)
{
	if(_hashValue % 3 == 0)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);	
	}
	else if(_hashValue % 3 == 1)
	{
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);	
	}
	else{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	SDL_RenderDrawPoint(renderer, _position.x, _position.y);
}

void Graphics::FPS(bool _display)
{
	int currentFPS = 1.0 / m_deltaTime;

	m_averageFPS = (m_averageFPS + currentFPS) / 2;
	
	
}