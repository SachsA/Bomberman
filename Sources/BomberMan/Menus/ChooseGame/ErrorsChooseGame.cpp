/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsChooseGame.cpp for cpp_indie_studio
*/

#include "ChooseGame.hpp"

ErrorsChooseGame::ErrorsChooseGame(std::ostream &os, const std::string &message) throw()
	: Errors(os, "ChooseGame -> " + message)
{}

ErrorsChooseGame::~ErrorsChooseGame(void) throw()
{}
