/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsAi.cpp for cpp_indie_studio
*/

#include "Ai.hpp"

ErrorsAi::ErrorsAi(std::ostream &os, const std::string &message) throw()
	: Errors(os, "ErrorsAi: " + message)
{}

ErrorsAi::~ErrorsAi(void) throw()
{}
