#include "Hash.h"
#include "Particle.h"

Hash::Hash(int _screenWidth, int _screenHeight)
{
	m_tableSize = (_screenWidth * _screenHeight) / 10;
}

Hash::~Hash()
{
//for(std::list<Particle*>::iterator it = buckets.at(i)->particles.begin(); it != buckets.at(i)->particles.end(); it++)
//{
	// // if we need to erase ->
	// std::list<Particle*>::iterator nit = it; nit++;
	// buckets.at(newHash).pushback(*it);
	// buckets.at(i)->particles.erase(it);	
	// it = nit;
	// // else
	// it++l
	//}	
}

void Hash::GenerateHashTable(std::vector<std::shared_ptr<Particle>> _particles)
{
	for(int i = 0; i < _particles.size(); i++)
	{
		
	}
}

int Hash::GetHashValue(vec2 _position)
{
	return (int)(_position.x * _position.y) % m_tableSize;
}