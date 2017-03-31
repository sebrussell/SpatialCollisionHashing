#include <memory>
#include <vector>
#include <list>

class Particle;
struct vec2;

class Hash
{
	public:
	  Hash(int _screenWidth, int _screenHeight);
	  ~Hash();
	  void GenerateHashTable(std::vector<std::shared_ptr<Particle>> _particles);
	  int GetHashValue(vec2 _position);
	private:	  
	  std::vector<std::list<std::weak_ptr<Particle>>> m_hashTable;		 
      int m_tableSize;	  
};