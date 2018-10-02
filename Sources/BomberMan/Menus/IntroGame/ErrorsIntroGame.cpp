/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsIntroGame.cpp for cpp_indie_studio
*/

#include "IntroGame.hpp"

ErrorsIntroGame::ErrorsIntroGame(std::ostream &os, const std::string &message) throw()
	: Errors(os, "IntroGame -> " + message)
{}

ErrorsIntroGame::~ErrorsIntroGame(void) throw()
{}
