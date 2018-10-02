/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsBomberMan.cpp for cpp_indie_studio
*/

#include "BomberMan.hpp"

ErrorsBomberMan::ErrorsBomberMan(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsBomberMan::~ErrorsBomberMan(void) throw()
{}
