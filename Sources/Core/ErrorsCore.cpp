/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsBomberMan.cpp for cpp_indie_studio
*/

#include "Core.hpp"

ErrorsCore::ErrorsCore(std::ostream &os, const std::string &message) throw()
	: Errors(os, message)
{}

ErrorsCore::~ErrorsCore(void) throw()
{}
