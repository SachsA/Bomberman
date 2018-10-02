/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsNewGame.cpp for cpp_indie_studio
*/

#include "NewGame.hpp"

ErrorsNewGame::ErrorsNewGame(std::ostream &os, const std::string &message) throw()
	: Errors(os, "NewGame -> " + message)
{}

ErrorsNewGame::~ErrorsNewGame(void) throw()
{}
