/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsPrincipalMenuGame.cpp for cpp_indie_studio
*/

#include "PrincipalMenuGame.hpp"

ErrorsPrincipalMenuGame::ErrorsPrincipalMenuGame(std::ostream &os, const std::string &message) throw()
	: Errors(os, "PrincipalMenuGame -> " + message)
{}

ErrorsPrincipalMenuGame::~ErrorsPrincipalMenuGame(void) throw()
{}
