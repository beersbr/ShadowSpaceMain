#pragma once

#include <Windows.h>
#include <windowsx.h>

enum{
	NONE,
	SETUP,
	RUNNING,
	QUITTING,
	LOADING,
	CLEANUP
};

class Game
{
public:
	Game(void);
	~Game(void);

	int Setup(void);
	MSG Start(void);

public:
	int State;

};

