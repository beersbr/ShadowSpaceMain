#include "Entity.h"


Entity::Entity(void)
{
	x, y, accel_x, accel_y = 0;
	width = height = 0;
}

Entity::Entity(Entity &entity)
{
	x = entity.x;
	y = entity.y;
	width = entity.width;
	height = entity.height;
}

Entity::~Entity(void)
{
}
