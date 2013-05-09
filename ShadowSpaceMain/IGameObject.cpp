#include "IGameObject.h"

long IGameObject::instance_id_inc = 0;
std::list<IGameObject*> *IGameObject::game_objects = new std::list<IGameObject*>();

IGameObject::IGameObject(void)
{
	instance_id_inc = IGameObject::instance_id_inc++;
	game_objects->push_back(this);
}

IGameObject::~IGameObject(void)
{
}

int IGameObject::instance_id() const
{
	return _instance_id;
}

int IGameObject::object_type() const
{
	return _object_type;
}