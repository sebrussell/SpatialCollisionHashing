#include "Hash.h"
#include "Particle.h"


Hash::Hash(int _screenWidth, int _screenHeight)
{
	m_tableSize = 1000;
	m_targetParticlesPerBucket = 10;
	m_columnAmount = pow(m_tableSize, 0.5);
	m_gridWidth = ceil(_screenWidth / m_columnAmount);
	m_gridHeight = ceil(_screenHeight / m_columnAmount);	
}

Hash::~Hash()
{

}

void Hash::GenerateHashTable(std::vector<std::shared_ptr<Particle>> _particles, int _amountOfParticles, int _screenWidth, int _screenHeight)
{	
	m_tableSize = _amountOfParticles / m_targetParticlesPerBucket;
	m_columnAmount = pow(m_tableSize, 0.5);
	m_gridWidth = ceil(_screenWidth / m_columnAmount);
	m_gridHeight = ceil(_screenHeight / m_columnAmount);
	m_hashTable.clear();
	for(int i = 0; i < m_tableSize; i++)
	{
		std::list<std::weak_ptr<Particle>> temp;
		m_hashTable.push_back(temp);
	}	
	
	for(int i = 0; i < _amountOfParticles; i++)
	{		
		int hashValue = GetHashValue(_particles.at(i)->GetPosition());			
		m_hashTable.at(hashValue).push_back(_particles.at(i));
		_particles.at(i)->SetHashNumber(hashValue);
	}
	
}

void Hash::UpdateTable(std::weak_ptr<Particle> _particle)
{
	int hashValue = GetHashValue(_particle.lock()->GetPosition());

	if(hashValue != _particle.lock()->GetParticleHash())
    {		
	    m_hashTable.at(hashValue).push_back(_particle);
		_particle.lock()->SetHashNumber(hashValue);		
		for(std::list<std::weak_ptr<Particle>>::iterator it = m_hashTable.at(hashValue).begin(); it != m_hashTable.at(hashValue).end(); it++)
		{
			if(it->lock() == _particle.lock())
			{
				m_hashTable.at(hashValue).erase(it);
				break;
			}			
		}
	}
}

int Hash::GetHashValue(vec2 _position)
{
	int temp = (int)(floor(_position.x / m_gridWidth)) + ((floor(_position.y / m_gridHeight) * m_columnAmount));
	if(temp >= m_tableSize)
	{
		temp = m_tableSize - 1;
	}
	return temp;
}

void Hash::CheckForCollision(std::weak_ptr<Particle> _particle)
{
	std::shared_ptr<Particle> tempParticle = _particle.lock();
	for(std::list<std::weak_ptr<Particle>>::iterator it = m_hashTable.at(tempParticle->GetParticleHash()).begin(); it != m_hashTable.at(tempParticle->GetParticleHash()).end(); it++)
	{
		if(it->lock()->GetPosition().x == tempParticle->GetPosition().x && it->lock()->GetPosition().y == tempParticle->GetPosition().y)
		{
			if(it->lock() != tempParticle)
			{
				if(it->lock()->GetMagintude() > tempParticle->GetMagintude())
				{
					tempParticle->SetVelocity(it->lock()->GetVelocity());
				}
				else{
					it->lock()->SetVelocity(tempParticle->GetVelocity());
				}
			}			
		}			
	}
}


