/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsWall.cpp for cpp_indie_studio
*/

#include "Wall.hpp"

ErrorsWall::ErrorsWall(std::ostream &os, const std::string &message) throw()
	: Errors(os, "Wall: " + message)
{}

ErrorsWall::~ErrorsWall(void) throw()
{}
