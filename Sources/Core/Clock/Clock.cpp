/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#include <sys/time.h>
#include <iostream>
#include "Clock.hpp"

Clock::Clock(int delay)
	: _delay(delay), _origin{0, 0}, _nbFrames(0)
{
	gettimeofday(&_origin, nullptr);
}

Clock::~Clock()
{
}

bool Clock::canUpdate()
{
	struct timeval now = {0, 0};
	long expectedFrames = 0;

	gettimeofday(&now, nullptr);
	expectedFrames = (now.tv_sec - _origin.tv_sec) * 1000 + (now.tv_usec - _origin.tv_usec) / 1000;
	expectedFrames *= _delay / 1000;
	if (_nbFrames < expectedFrames) {
		_nbFrames++;
		return true;
	}
	return false;

}
