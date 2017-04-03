#include <iostream>
#include <time.h>
#include "Particle.h"				//the header files that are included
#include "Graphics.h"				
#include "Hash.h"
#include <windows.h>
#undef main

int main(int argc, char* args[])
{	
	std::shared_ptr<Graphics> sdl(new Graphics);																	//make a new graphics variable
	std::shared_ptr<Hash> hashTable(new Hash(sdl->GetScreenWidth(), sdl->GetScreenHeight()));						//make a new hash table variable
	srand(time(NULL));																								//set the seed for the random function
	
	std::vector<std::shared_ptr<Particle>> particlePool;															//make a particle pool
	int maximumAmountOfParticles = 50000;																			//max amount of particles
	int amountOfParticles = 10000;																					//current amount of particles
	
	
	bool exit = false;																								//the exit boolean
	
	#pragma omp parallel																							//this makes the function a parallel functions
	{
		#pragma omp for																								//makes the for loop parallel
		for(int i = 0; i < maximumAmountOfParticles; i++)															//for the max amount of particles
		{			
			#pragma omp critical 																					//critical because we are editing memory
			{
				std::shared_ptr<Particle> particle(new Particle);													//make a new particle
				particlePool.push_back(particle);																	//push it into the particle pool
			}
		}
	}	
	
	hashTable->GenerateHashTable(particlePool, amountOfParticles, sdl->GetScreenWidth(), sdl->GetScreenHeight());	//generate the hash table
	
	while(exit == false)																							//while the program hasnt escaped
	{
		switch(sdl->FirstUpdate())																					//call the first update function
		{
			case SDLK_ESCAPE:																						//if they have pressed escape
				exit = true;																						//exit
				break;
			case SDLK_UP:																							//if they press the up key
				if(amountOfParticles + 1000 <= particlePool.size())
				{
					amountOfParticles += 1000;																		//'make' more particles
					hashTable->GenerateHashTable(particlePool, amountOfParticles, sdl->GetScreenWidth(), sdl->GetScreenHeight());	//regenerate the hash table for that amount of particles
				}
				break;
			case SDLK_DOWN:
				if(amountOfParticles - 1000 >= 2000)																//if they press the down key
				{
					amountOfParticles -= 1000;																		//'remove' some particles
					hashTable->GenerateHashTable(particlePool, amountOfParticles, sdl->GetScreenWidth(), sdl->GetScreenHeight());	//regenerate the hash table for that amount of particles
				}
				break;
			case SDLK_q:																							//if you press q
				std::cout << "Average FPS of: " << sdl->GetAverageFPS() << " with " << amountOfParticles << " particles and " << hashTable->GetTableSize()  << " buckets." << std::endl;		//output to the console some statistics
				break;
		}				
		sdl->FPS(false);																		
		sdl->DrawLine(hashTable);																					//draw on the bucket lines
		#pragma omp parallel		
		{
			#pragma omp for
			for(int i = 0; i < amountOfParticles; i++)
			{
				hashTable->UpdateTable(particlePool.at(i));															//make the update function and collision detection for the particles parallel
				hashTable->CheckForCollision(particlePool.at(i));
				particlePool.at(i)->Update(sdl);				
			}	
		}		
		sdl->FlipScreen();																							//flip the screen
	}
  return 0;
}