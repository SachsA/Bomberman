/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsHuman.cpp for cpp_indie_studio
*/

#include "Human.hpp"

ErrorsHuman::ErrorsHuman(std::ostream &os, const std::string &message) throw()
	: Errors(os, "Human: " + message)
{}

ErrorsHuman::~ErrorsHuman(void) throw()
{}
