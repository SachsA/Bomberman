/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Errors.hpp for cpp_indie_studio
*/

#ifndef ERRORS_HPP_
#define ERRORS_HPP_

#include <exception>
#include <iostream>
#include <string>

/*! \class Errors
 * \brief Classe used to handle custom error.
 *
 *
 */

class Errors: public std::exception {
public:
	Errors(std::ostream &, const std::string &) throw();
	virtual ~Errors(void) throw();

	const char *what(void) const throw();

private:
	std::string _message;
	std::ostream &_os;
};

#endif /* !ERRORS_HPP_ */
