#include "Particle.h"
#include "Graphics.h"
#include "Hash.h"

Particle::Particle()
{	
	m_position.x = rand() % 800;
	m_position.y = rand() % 800;
	m_velocity.x = ((rand() % 200) - 100);
	m_velocity.y = ((rand() % 200) - 100);
	m_velocity.x /= rand() % 5 + 1;
	m_velocity.y /= rand() % 5 + 1;
}

Particle::~Particle()
{
	
}

void Particle::Update(std::weak_ptr<Graphics> _sdl)
{
	m_position.x += m_velocity.x * _sdl.lock()->GetDeltaTime();
	m_position.y += m_velocity.y * _sdl.lock()->GetDeltaTime();
	
	if(m_position.x < 0)
	{
		m_position.x = _sdl.lock()->GetScreenWidth();
	}
    if(m_position.y < 0)
	{
		m_position.y = _sdl.lock()->GetScreenHeight();
	}
	
	if(m_position.x > _sdl.lock()->GetScreenWidth())
	{
		m_position.x = 0;
	}
    if(m_position.y > _sdl.lock()->GetScreenHeight())
	{
		m_position.y = 0;
	}
	
	_sdl.lock()->Draw(m_position, m_hashValue);
}