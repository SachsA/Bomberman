/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsSpeedUp.cpp for cpp_indie_studio
*/

#include "SpeedUp.hpp"

ErrorsSpeedUp::ErrorsSpeedUp(std::ostream &os, const std::string &message) throw()
	: Errors(os, "SpeedUp: " + message)
{}

ErrorsSpeedUp::~ErrorsSpeedUp(void) throw()
{}
