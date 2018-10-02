/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsBomb.cpp for cpp_indie_studio
*/

#include "Bomb.hpp"

ErrorsBomb::ErrorsBomb(std::ostream &os, const std::string &message) throw()
	: Errors(os, "Bomb: " + message)
{}

ErrorsBomb::~ErrorsBomb(void) throw()
{}
