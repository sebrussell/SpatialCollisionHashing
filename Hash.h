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
	  void GenerateHashTable(std::vector<std::shared_ptr<Particle>> _particles);
	  int GetHashValue(vec2 _position);
	  void UpdateTable(std::weak_ptr<Particle> _particle);
	  int GetTableSize() { return m_tableSize; }
	  int GetGridWidth() { return m_gridWidth; }
	  int GetGridHeight() { return m_gridHeight; }
	  int GetColumnAmount() { return m_columnAmount; }
	  void CheckForCollision(std::weak_ptr<Particle> _particle);
	private:	  
	  std::vector<std::list<std::weak_ptr<Particle>>> m_hashTable;		 
      int m_tableSize, m_gridWidth, m_gridHeight, m_columnAmount;
};