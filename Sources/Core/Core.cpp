/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include "Core.hpp"

#ifdef __unix__
	#include <unistd.h>
#endif
#ifdef _WIN32
	#include <Windows.h>
#endif

Core::Core(int ac, char *av[], char *ev[]) :
	_argc(ac)
{
	 bool isDisplay = false;

	for (int i = 0; i < ac; ++i) {
		_argv.emplace_back(av[i]);
	}
	for (int i = 0; ev[i]; ++i) {
		if (!(std::strncmp(ev[i], "DISPLAY=", std::strlen("DISPLAY="))))
			isDisplay = true;
	}
	#ifdef __unix__
		if (!isDisplay) {
			throw ErrorsCore(std::cerr, "ENV not available");
		}
	#endif
}

int Core::getArgc() const
{
	return _argc;
}

std::vector<std::string> Core::getArgv() const
{
	return _argv;
}

void Core::launchBomberMan()
{
	BomberMan bomberMan;

	bomberMan.launchBomberMan();
}

void Core::updateDirectory()
{
	std::ifstream ifs("ConfigIndie/ConfigIndie.cfg");

	if (ifs.is_open()) {
		ifs.close();
		return;
	}

	#ifdef __unix__
		if (chdir("/usr/bin"))
			throw ErrorsCore(std::cerr, "cannot change directory");
	#endif

	ifs.open("ConfigIndie/ConfigIndie.cfg");
	if (ifs.is_open()) {
		ifs.close();
		return;
	}
	std::string str("/ ! \\ You have to start \"bomberman\" where the ressources are installed.\n"
			"Otherwise you need to perform a \"sudo make install\".\n");
	throw ErrorsCore(std::cerr, str);
}
