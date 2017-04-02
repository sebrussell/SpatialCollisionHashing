#include <iostream>
#include <time.h>
#include "Particle.h"
#include "Graphics.h"
#include "Hash.h"
#include <windows.h>
#undef main

int main(int argc, char* args[])
{	
	std::shared_ptr<Graphics> sdl(new Graphics);
	std::shared_ptr<Hash> hashTable(new Hash(sdl->GetScreenWidth(), sdl->GetScreenHeight()));
	srand(time(NULL));	
	
	std::vector<std::shared_ptr<Particle>> particlePool;
	int maximumAmountOfParticles = 50000;
	int amountOfParticles = 10000;
	
	
	bool exit = false;
	
	#pragma omp parallel
	{
		#pragma omp for
		for(int i = 0; i < maximumAmountOfParticles; i++)
		{			
			#pragma omp critical 
			{
				std::shared_ptr<Particle> particle(new Particle);
				particlePool.push_back(particle);
			}
		}
	}	
	
	hashTable->GenerateHashTable(particlePool, amountOfParticles, sdl->GetScreenWidth(), sdl->GetScreenHeight());
	
	while(exit == false)
	{
		switch(sdl->FirstUpdate())
		{
			case SDLK_ESCAPE:
				exit = true;
				break;
			case SDLK_UP:
				if(amountOfParticles + 1000 <= particlePool.size())
				{
					amountOfParticles += 1000;
					hashTable->GenerateHashTable(particlePool, amountOfParticles, sdl->GetScreenWidth(), sdl->GetScreenHeight());
				}
				break;
			case SDLK_DOWN:
				if(amountOfParticles - 1000 >= 2000)
				{
					amountOfParticles -= 1000;
					hashTable->GenerateHashTable(particlePool, amountOfParticles, sdl->GetScreenWidth(), sdl->GetScreenHeight());
				}
				break;
			case SDLK_q:
				std::cout << "Average FPS of: " << sdl->GetAverageFPS() << " with " << amountOfParticles << " particles and " << hashTable->GetTableSize()  << " buckets." << std::endl;
				break;
		}				
		sdl->FPS(false);
		sdl->DrawLine(hashTable);
		#pragma omp parallel
		{
			#pragma omp for
			for(int i = 0; i < amountOfParticles; i++)
			{
				hashTable->UpdateTable(particlePool.at(i));
				hashTable->CheckForCollision(particlePool.at(i));
				particlePool.at(i)->Update(sdl);				
			}	
		}		
		sdl->FlipScreen();
	}
  return 0;
}