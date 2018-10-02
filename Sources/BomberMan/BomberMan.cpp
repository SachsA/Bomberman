/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#include <iostream>
#include "BomberMan.hpp"
#include "IntroGame.hpp"
#include "SettingsMenu.hpp"
#include "PrincipalMenuGame.hpp"
#include "ChooseGame.hpp"
#include "NewGame.hpp"
#include "QuickGame.hpp"
#include "GameGfx.hpp"

BomberMan::BomberMan()
	: _config("ConfigIndie/ConfigIndie.cfg")
{
	_device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(1920, 1080),
		16, false, false, false);
	if (!_device)
		throw ErrorsBomberMan(std::cerr, "! createDevice Failed !");
	_driver = _device->getVideoDriver();
	if (!_driver)
		throw ErrorsBomberMan(std::cerr, "! getVideoDriver Failed !");

	_config.earthTexture = _driver->getTexture("AssetsIndie/Menus/Principal/earth.jpg");

	_menus.emplace(SceneStatus::INTRO, std::make_unique<IntroGame>(_device, _driver, _config));
	_menus.emplace(SceneStatus::PRINCIPAL_MENU, std::make_unique<PrincipalMenuGame>(_device, _driver, _config));
	_menus.emplace(SceneStatus::SETTINGS_MENU, std::make_unique<SettingsMenu>(_device, _driver, _config));
	_menus.emplace(SceneStatus::CHOOSE_GAME, std::make_unique<ChooseGame>(_device, _driver, _config));
	_menus.emplace(SceneStatus::NEW_GAME, std::make_unique<NewGame>(_device, _driver, _config));
	_menus.emplace(SceneStatus::QUICK_GAME, std::make_unique<QuickGame>(_device, _driver, _config));
	_menus.emplace(SceneStatus::GFX_GAME, std::make_unique<GameGfx>(_device, _driver, _config));

	_device->setResizable(false);

	#ifdef __unix__
		_config.insertSound(SoundType::MENUS, "Confirmation", "AssetsIndie/Sounds/Confirmation.wav");
		_config.insertSound(SoundType::MENUS, "Press","AssetsIndie/Sounds/Press.wav");
		_config.insertSound(SoundType::MENUS, "Back","AssetsIndie/Sounds/Back.wav");
	#endif
}

BomberMan::~BomberMan()
{
	_device->closeDevice();
	_device->run();
	_device->drop();
}

SceneStatus BomberMan::launchScene(SceneStatus const &scene)
{
	return _menus[scene]->launch();
}

void BomberMan::launchBomberMan()
{
	SceneStatus status = INTRO;

	while (status > 0) {
		status = launchScene(status);
	}
}
