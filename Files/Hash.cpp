#include "Hash.h"
#include "Particle.h"				//included header files


Hash::Hash(int _screenWidth, int _screenHeight)
{
	m_tableSize = 1000;											//a default table size of 1000
	m_targetParticlesPerBucket = 10;							//this is so the table can expand and shrink depending on how many particles are in the simulation
	m_columnAmount = pow(m_tableSize, 0.5);						//works out the column amount
	m_gridWidth = ceil(_screenWidth / m_columnAmount);			//works out the width and height from the column amount
	m_gridHeight = ceil(_screenHeight / m_columnAmount);	
}

Hash::~Hash()
{

}

void Hash::GenerateHashTable(std::vector<std::shared_ptr<Particle>> _particles, int _amountOfParticles, int _screenWidth, int _screenHeight)
{	
	m_tableSize = _amountOfParticles / m_targetParticlesPerBucket;
	m_columnAmount = pow(m_tableSize, 0.5);										//works out the best size for the buckets
	m_gridWidth = ceil(_screenWidth / m_columnAmount);
	m_gridHeight = ceil(_screenHeight / m_columnAmount);
	m_hashTable.clear();														//clear the table
	for(int i = 0; i < m_tableSize; i++)										//for how big the table should be
	{
		std::list<std::weak_ptr<Particle>> temp;								//push back a temporary weak pointer
		m_hashTable.push_back(temp);											
	}	
	
	for(int i = 0; i < _amountOfParticles; i++)									//for the particles that are being used
	{		
		int hashValue = GetHashValue(_particles.at(i)->GetPosition());			//get the hash value of the particle
		m_hashTable.at(hashValue).push_back(_particles.at(i));					//push the particle into the correct table
		_particles.at(i)->SetHashNumber(hashValue);								//update the particles hash value
	}
	
}

void Hash::UpdateTable(std::weak_ptr<Particle> _particle)
{
	int hashValue = GetHashValue(_particle.lock()->GetPosition());				//get the particles hash value

	if(hashValue != _particle.lock()->GetParticleHash())						//if they are different values
    {		
	    m_hashTable.at(hashValue).push_back(_particle);							//push the particle into the correct bucket
		_particle.lock()->SetHashNumber(hashValue);								//update the hash value
		for(std::list<std::weak_ptr<Particle>>::iterator it = m_hashTable.at(hashValue).begin(); it != m_hashTable.at(hashValue).end(); it++)		//iterate through the linked list
		{
			if(it->lock() == _particle.lock())					//if the iterator is equal to the particle
			{
				m_hashTable.at(hashValue).erase(it);			//remove it 
				break;											//break from the loop
			}			
		}
	}
}

int Hash::GetHashValue(vec2 _position)																					//function which returns the hash value for the particle
{
	int temp = (int)(floor(_position.x / m_gridWidth)) + ((floor(_position.y / m_gridHeight) * m_columnAmount));		//my hash function
	if(temp >= m_tableSize)																								//sometimes returns a value larger than the max
	{
		temp = m_tableSize - 1;																							//set it to the max value
	}
	return temp;																										//return the hash value
}

void Hash::CheckForCollision(std::weak_ptr<Particle> _particle)
{
	std::shared_ptr<Particle> tempParticle = _particle.lock();															//get reference to the weak pointer
	for(std::list<std::weak_ptr<Particle>>::iterator it = m_hashTable.at(tempParticle->GetParticleHash()).begin(); it != m_hashTable.at(tempParticle->GetParticleHash()).end(); it++)	//for every particle in the  list
	{
		if(it->lock()->GetPosition().x == tempParticle->GetPosition().x && it->lock()->GetPosition().y == tempParticle->GetPosition().y)		//if the positions are the same as this particle
		{
			if(it->lock() != tempParticle)													//and the iterator isnt the same as the particle
			{
				if(it->lock()->GetMagintude() > tempParticle->GetMagintude())				//whichever particle has a larger velocity
				{
					tempParticle->SetVelocity(it->lock()->GetVelocity());					//set the lower velocitied particle to the higher velocitied particles velocity.
				}
				else{
					it->lock()->SetVelocity(tempParticle->GetVelocity());
				}
			}			
		}			
	}
}


