/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsAPlayer.cpp for cpp_indie_studio
*/

#include "APlayer.hpp"

ErrorsAPlayer::ErrorsAPlayer(std::ostream &os, const std::string &message) throw()
	: Errors(os, "APlayer: " + message)
{}

ErrorsAPlayer::~ErrorsAPlayer(void) throw()
{}
