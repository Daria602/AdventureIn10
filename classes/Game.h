#pragma once
#include "Room.h"

class Game
{
	bool running;
	int dayCount;

public:

	Game() { this->running = true; this->dayCount = 1; }
	virtual ~Game() {}

	bool const getRunning() { return this->running; }
	int const getDayCount() { return this->dayCount; }

	void setRunningFalse() { this->running = false; }
	void incrementDayCount() { this->dayCount++; std::cout << "You rested. Starting Day " << this->dayCount << std::endl; }

};

