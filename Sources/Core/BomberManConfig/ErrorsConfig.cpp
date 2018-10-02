/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsSounds.cpp for cpp_indie_studio
*/

#include "BomberManConfig.hpp"

ErrorsConfig::ErrorsConfig(std::ostream &os, const std::string &message) throw()
	: Errors(os, "ConfigError -> " + message)
{
}

ErrorsConfig::~ErrorsConfig(void) throw()
{}
