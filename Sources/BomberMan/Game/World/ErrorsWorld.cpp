//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ErrorsWorld.cpp
//

#include "World.hpp"

ErrorsWorld::ErrorsWorld(std::ostream &os, const std::string &message) throw()
	: Errors(os, "World: " + message)
{}

ErrorsWorld::~ErrorsWorld(void) throw()
{}
