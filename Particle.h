#include <stdlib.h>
#include <memory>
#include <list>

class Graphics;
class Hash;

struct vec2
{
   double x, y;
};

class Particle
{	
	public:
	  
	  Particle();
	  ~Particle();	
	  vec2 GetPosition() { return m_position; }
	  void Update(std::weak_ptr<Graphics> _sdl);
	  //void SetHashOwner(std::list<std::weak_ptr<Particle>> _hashOwner) { m_hashOwner = std::make_shared<std::list<std::weak_ptr<Particle>>>(_hashOwner); }
	  void SetHashNumber(int _i) { m_hashValue = _i; }
	  //std::weak_ptr<std::list<std::weak_ptr<Particle>>> GetParticleHashOwner() { return m_hashOwner; }
	  int GetParticleHash() { return m_hashValue; }
	private:
	  vec2 m_position, m_velocity; 
	  //std::weak_ptr<std::list<std::weak_ptr<Particle>>> m_hashOwner;
	  int m_hashValue;
};
