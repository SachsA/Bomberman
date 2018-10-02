//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Timer.hpp
//

#ifndef TIMER_HPP
	#define TIMER_HPP

	#include <sys/time.h>

	/*! \class Timer
	 * \brief Clock implementation used to delay something (bomb explosion)
	 *
	 *
	 */

	class Timer {
	public:
		Timer(int delay);
		~Timer() = default;

		bool canUpdate();
	private:
		float _delay;
		struct timeval _origin;
	};

#endif /* end of include guard: TIMER_HPP */
