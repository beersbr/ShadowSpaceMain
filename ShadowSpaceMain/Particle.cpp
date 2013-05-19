#include "Particle.h"

std::list<Particle*> *Particle::particles = new std::list<Particle*>();

Particle::Particle(void)
{
}

Particle::~Particle(void)
{
}

int Particle::update(double timestamp)
{
	position += ((Point)accel*timestamp);
	return 0;
}

int Particle::draw(void)
{
	al_draw_filled_rectangle(position.x, position.y, position.x+1, position.y+1, al_map_rgb(144, 144, 255));
	return 0;
}