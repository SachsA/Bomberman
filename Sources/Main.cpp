/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#ifdef __unix__
	#include <unistd.h>
#endif

#ifdef _WIN32
	#include <Windows.h>
#endif

#include "Core.hpp"
#include "Errors.hpp"
#include "IntroGame.hpp"

int main(int ac, char **av, char **env)
{
	#ifdef _WIN32
		std::cout << "WINDOWS CAN'T LOAD SFML AUDIO" << std::endl;
	#endif

	try {
		Core core(ac, av, env);

		core.updateDirectory();
		core.launchBomberMan();
	} catch (const Errors &e) {
		std::cerr << "Error(s): " << e.what() << std::endl;
		return 84;
	} catch (...) {
		std::cerr << "Unknown Error(s)." << std::endl;
		return 84;
	}
	return 0;
}
