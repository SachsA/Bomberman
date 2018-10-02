/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#ifndef INDIE_STUDIO_CORE_HPP
#define INDIE_STUDIO_CORE_HPP

#include "BomberMan.hpp"

/*! \class ErrorsCore
 * \brief Used to handle custom error coming from Core.
 *
 *
 */

class ErrorsCore: public Errors {
public:
	ErrorsCore(std::ostream &, const std::string &) throw();
	virtual ~ErrorsCore(void) throw();
};

/*! \class Core
 * \brief Main class of the game, this class is used to launch the game.
 *
 *
 */

class Core {
public:
	Core(int, char **, char **);
	~Core() = default;

	int getArgc() const;
	void launchBomberMan();
	void updateDirectory();

	std::vector<std::string> getArgv() const;

private:
	int _argc;
	std::vector<std::string> _argv;
};

#endif //INDIE_STUDIO_CORE_HPP


