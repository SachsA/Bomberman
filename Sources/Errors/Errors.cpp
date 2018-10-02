/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Errors.cpp for cpp_indie_studio
*/

#include "Errors.hpp"

Errors::Errors(std::ostream &os, const std::string &message) throw()
	: _os(os)
{
	_message = message;
}

Errors::~Errors(void) throw()
{}

const char *Errors::what(void) const throw()
{
	return _message.c_str();
}
