/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsBox.cpp for cpp_indie_studio
*/

#include "Box.hpp"

ErrorsBox::ErrorsBox(std::ostream &os, const std::string &message) throw()
	: Errors(os, "Box: " + message)
{}

ErrorsBox::~ErrorsBox(void) throw()
{}
