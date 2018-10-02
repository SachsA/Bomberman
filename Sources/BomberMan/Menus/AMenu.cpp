/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#include "AMenu.hpp"

AMenu::AMenu(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver,
	BomberManConfig &config)
	: _device(device), _driver(driver), _config(config)
{
	_env = _device->getGUIEnvironment();
	_scene = _device->getSceneManager();
}

void AMenu::clearScreen()
{
	_env->clear();
	_scene->clear();
}
