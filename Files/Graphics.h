#include <vector>
#include <memory>
#include <SDL.h>		//the include files
#include <iostream>
#include <ctime>
#include <SDL_ttf.h>
#include <sstream>

struct vec2;			//forward declaring programmer made classes because it is safer
class Hash;

class Graphics
{
	public:
	  Graphics();											
	  ~Graphics();										
      SDL_Keycode FirstUpdate(int _amountOfParticles);			
	  void FlipScreen();							
	  void Draw(vec2 _position, int _hashValue);
	  void DrawLine(std::weak_ptr<Hash> _hashTable);
	  int GetScreenWidth() { return SCREEN_WIDTH; }						//public functions list
	  int GetScreenHeight() { return SCREEN_HEIGHT; }
	  double GetDeltaTime() { return m_deltaTime; }
	  void FPS(bool _display);
	  int GetAverageFPS() { return m_averageFPS; }
	private:
		int SCREEN_HEIGHT;												//the window height
		int SCREEN_WIDTH;
	
		SDL_Window* window;
		SDL_Surface* screenSurface;
		SDL_Surface* messageSurface;
		SDL_Renderer* renderer;											//variables to draw using SDL
		SDL_Event event;
		TTF_Font* arial;
		SDL_Color textColor;
		
		std::clock_t m_end;												//the variable which stores the previous time (to work out delta time)
		double m_deltaTime;												//delta time
		int m_averageFPS;												//the average fps
		std::stringstream m_fpsStream;
		int m_tableSize;

};
