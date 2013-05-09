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
	position += *(Point*)&accel;
	return 0;
}

int Particle::draw(void)
{
	return 0;
}