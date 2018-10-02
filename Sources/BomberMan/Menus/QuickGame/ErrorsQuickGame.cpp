/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsQuickGame.cpp for cpp_indie_studio
*/

#include "QuickGame.hpp"

ErrorsQuickGame::ErrorsQuickGame(std::ostream &os, const std::string &message) throw()
	: Errors(os, "ErrorsQuickGame -> " + message)
{}

ErrorsQuickGame::~ErrorsQuickGame(void) throw()
{}
