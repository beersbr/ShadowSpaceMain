#include "Particle.h"

std::list<Particle*> *Particle::particles = new std::list<Particle*>();

Particle::Particle(void)
{
	Particle::particles->push_back(this);
}

Particle::~Particle(void)
{
}

int Particle::Update(double timestamp)
{
	position += ((Point)accel*static_cast<float>(timestamp));
	return 0;
}

int Particle::Draw()
{
	return 0;
}
