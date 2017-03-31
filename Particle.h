#include <stdlib.h>
#include <memory>

class Graphics;

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
	private:
	  vec2 m_position, m_velocity; 
	  int m_currentBucketID;    //change this to a weak ptr to the owner of the bucket
};
