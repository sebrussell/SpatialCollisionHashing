#include <memory>
#include <vector>
#include <list>
#include <cmath>
#include <iostream>

class Particle;
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
	  int GetGridWidth() { return m_gridWidth; }
	  int GetGridHeight() { return m_gridHeight; }
	  int GetColumnAmount() { return m_columnAmount; }
	  void CheckForCollision(std::weak_ptr<Particle> _particle);
	  void WorkOutBestTableSize(int _averageFPS);
	private:	  
	  std::vector<std::list<std::weak_ptr<Particle>>> m_hashTable;		 
      double m_tableSize, m_gridWidth, m_gridHeight, m_columnAmount;
	  
	  //for the AI which works out the best table size
	  int m_targetParticlesPerBucket;
};