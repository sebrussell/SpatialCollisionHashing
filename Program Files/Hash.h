#include <memory>
#include <vector>
#include <list>						//the included headers
#include <cmath>
#include <iostream>

class Particle;						//forward declaring the programmer made classes for safety
struct vec2;

class Hash
{
	public:
	  Hash(int _screenWidth, int _screenHeight);
	  ~Hash();
	  void GenerateHashTable(std::vector<std::shared_ptr<Particle>> _particles, int _amountOfParticles, int _screenWidth, int _screenHeight);
	  int GetHashValue(vec2 _position);
	  void UpdateTable(std::weak_ptr<Particle> _particle);
	  int GetTableSize() { return m_tableSize; }
	  int GetGridWidth() { return m_gridWidth; }									//a list of the public functions used
	  int GetGridHeight() { return m_gridHeight; }
	  int GetColumnAmount() { return m_columnAmount; }
	  void CheckForCollision(std::weak_ptr<Particle> _particle);
	private:	  
	  std::vector<std::list<std::weak_ptr<Particle>>> m_hashTable;		 			//this is the hash table which is a vector is linked lists to particles
      double m_tableSize, m_gridWidth, m_gridHeight, m_columnAmount;				//different info on the table size etc
	  int m_targetParticlesPerBucket;
};
