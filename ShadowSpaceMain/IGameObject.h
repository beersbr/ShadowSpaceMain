#pragma once

#include <list>
#include <allegro5\allegro.h>

class IGameObject
{
public:
	IGameObject(void);
	virtual ~IGameObject(void);

	virtual int update(double timestamp) = 0;
	virtual int draw(ALLEGRO_DISPLAY *context) = 0;
	int instance_id() const;
	int object_type() const;

protected:
	int _object_type;

private:
	long _instance_id;
	static long instance_id_inc;
	static std::list<IGameObject*> *game_objects;
};

