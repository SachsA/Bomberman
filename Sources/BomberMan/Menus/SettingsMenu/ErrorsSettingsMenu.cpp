/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsSettingsMenu.cpp for cpp_indie_studio
*/

#include "SettingsMenu.hpp"

ErrorsSettingsMenu::ErrorsSettingsMenu(std::ostream &os, const std::string &message) throw()
	: Errors(os, "SettingsMenu -> " + message)
{}

ErrorsSettingsMenu::~ErrorsSettingsMenu(void) throw()
{}
