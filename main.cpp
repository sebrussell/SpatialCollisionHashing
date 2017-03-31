#include <iostream>
#include <time.h>
#include "Particle.h"
#include "Graphics.h"
#include <windows.h>
#undef main

int main(int argc, char* args[])
{	
	std::shared_ptr<Graphics> sdl(new Graphics);
	
	srand(time(NULL));
	
	std::vector<std::shared_ptr<Particle>> particlePool;
	
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < 10000; i++)
		{			
			#pragma omp critical 
			{
				std::shared_ptr<Particle> particle(new Particle);
				particlePool.push_back(particle);
			}
		}
	}
	
	
	
	
	
	while(sdl->FirstUpdate() != false)
	{
		for(int i = 0; i < particlePool.size(); i++)
		{
			particlePool[i]->Update(sdl);
		}	
		
		
		sdl->FlipScreen();
	}

  return 0;
}