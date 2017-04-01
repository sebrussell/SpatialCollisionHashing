#include <vector>
#include <memory>
#include <SDL.h>
#include <iostream>
#include <ctime>

struct vec2;
class Hash;

class Graphics
{
	public:
	  Graphics();
	  ~Graphics();
      bool FirstUpdate();	
	  void FlipScreen();
	  void Draw(vec2 _position, int _hashValue);
	  void DrawLine(std::weak_ptr<Hash> _hashTable);
	  int GetScreenWidth() { return SCREEN_WIDTH; }
	  int GetScreenHeight() { return SCREEN_HEIGHT; }
	  double GetDeltaTime() { return m_deltaTime; }
	private:
		int SCREEN_HEIGHT;
		int SCREEN_WIDTH;
	
		SDL_Window* window;
		SDL_Surface* screenSurface;
		SDL_Renderer* renderer;
		SDL_Event event;
		
		std::clock_t m_begin, m_end;
		double m_deltaTime;

};