/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#ifndef INDIE_STUDIO_CLOCK_HPP
#define INDIE_STUDIO_CLOCK_HPP

#include <cstdlib>

#ifdef _WIN32
	#include "Windows.h"
#endif

/*! \class Clock
 * \brief Used to handle frame time display.
 *
 *
 */
class Clock
{
public:
	explicit Clock(int);
	~Clock();

	bool canUpdate();
private:
	float _delay;
	struct timeval _origin;
	int _nbFrames;
};

#endif //INDIE_STUDIO_CLOCK_HPP
