//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Timer.cpp
//

#include <iostream>
#include "Timer.hpp"

Timer::Timer(int delay)
	:	_delay(delay)
{
	gettimeofday(&_origin, nullptr);
}

bool Timer::canUpdate()
{
	struct timeval now = {0, 0};
	long milisec = 0;

	gettimeofday(&now, nullptr);
	milisec = (now.tv_sec - _origin.tv_sec) * 1000 + (now.tv_usec - _origin.tv_usec) / 1000;

	if (milisec > _delay) {
		gettimeofday(&_origin, nullptr);
		return true;
	}
	return false;
}
