/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsBombExplosion.cpp for cpp_indie_studio
*/

#include "BombExplosion.hpp"

ErrorsBombExplosion::ErrorsBombExplosion(std::ostream &os, const std::string &message) throw()
	: Errors(os, "BombExplosion: " + message)
{}

ErrorsBombExplosion::~ErrorsBombExplosion(void) throw()
{}
