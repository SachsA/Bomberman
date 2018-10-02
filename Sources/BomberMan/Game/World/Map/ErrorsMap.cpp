//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ErrorsMap.cpp
//

#include "Map.hpp"

ErrorsMap::ErrorsMap(std::ostream &os, const std::string &message) throw()
	: Errors(os, "Map: " + message)
{}

ErrorsMap::~ErrorsMap(void) throw()
{}
