#include <stdlib.h>
#include <memory>
#include <list>
#include <cmath>

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
	  vec2 GetVelocity() { return m_velocity; }
	  int GetMagintude() { return m_magnitude; }
	  void SetVelocity(vec2 _velocity) { m_velocity = _velocity; m_magnitude = pow(m_velocity.x, 2) + pow(m_velocity.y, 2);}
	  void Update(std::weak_ptr<Graphics> _sdl);
	  //void SetHashOwner(std::list<std::weak_ptr<Particle>> _hashOwner) { m_hashOwner = std::make_shared<std::list<std::weak_ptr<Particle>>>(_hashOwner); }
	  void SetHashNumber(int _i) { m_hashValue = _i; }
	  //std::weak_ptr<std::list<std::weak_ptr<Particle>>> GetParticleHashOwner() { return m_hashOwner; }
	  int GetParticleHash() { return m_hashValue; }
	private:
	  vec2 m_position, m_velocity; 
	  //std::weak_ptr<std::list<std::weak_ptr<Particle>>> m_hashOwner;
	  int m_hashValue, m_magnitude;
};
