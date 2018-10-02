/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsPowerUp.cpp for cpp_indie_studio
*/

#include "PowerUp.hpp"

ErrorsPowerUp::ErrorsPowerUp(std::ostream &os, const std::string &message) throw()
	: Errors(os, "PowerUp: " + message)
{}

ErrorsPowerUp::~ErrorsPowerUp(void) throw()
{}
