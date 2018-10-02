//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ErrorsGameGfx.cpp
//

#include "GameGfx.hpp"

ErrorsGameGfx::ErrorsGameGfx(std::ostream &os, const std::string &message) throw()
	: Errors(os, "GameGfx: " + message)
{}

ErrorsGameGfx::~ErrorsGameGfx(void) throw()
{}
