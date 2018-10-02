/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsBombUp.cpp for cpp_indie_studio
*/

#include "BombUp.hpp"

ErrorsBombUp::ErrorsBombUp(std::ostream &os, const std::string &message) throw()
	: Errors(os, "BombUp: " + message)
{}

ErrorsBombUp::~ErrorsBombUp(void) throw()
{}
