#include "Entity.h"


Entity::Entity(void)
{
	position = Point();
	accel = Vector();
	width = height = 0;
}

Entity::Entity(Entity &entity)
{
	position = entity.position;
	accel = entity.accel;
	width = entity.width;
	height = entity.height;
}

Entity::~Entity(void)
{
}
