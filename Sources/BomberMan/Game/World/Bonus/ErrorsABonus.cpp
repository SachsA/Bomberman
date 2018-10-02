/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsABonus.cpp for cpp_indie_studio
*/

#include "ABonus.hpp"

ErrorsABonus::ErrorsABonus(std::ostream &os, const std::string &message) throw()
	: Errors(os, "ABonus: " + message)
{}

ErrorsABonus::~ErrorsABonus(void) throw()
{}
