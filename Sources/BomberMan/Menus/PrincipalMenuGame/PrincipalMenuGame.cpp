/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PrincipalMenuGame.cpp for cpp_indie_studio
*/

#include <iostream>
#include "Utils/Utils.hpp"
#include "Clock/Clock.hpp"
#include "PrincipalMenuGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

PrincipalMenuGame::PrincipalMenuGame(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver,
	BomberManConfig &config)
	: AMenu(device, driver, config), _receiver(_device, *this)
{
	#ifdef __unix__
		_config.insertMusic("Theme", "AssetsIndie/Sounds/R6.wav");
	#endif
	updateConfigValue("FPS", _fps, 60);
	updateConfigValue("EarthRotationSpeed", _earthRotationSpeed, 0.1);
}

void PrincipalMenuGame::updateConfigValue(std::string const &key, int &value, int defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stoi(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void PrincipalMenuGame::updateConfigValue(std::string const &key, float &value, float defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stof(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void PrincipalMenuGame::displayFPSTitle()
{
	int lastFPS = -1;
	int fps = _driver->getFPS();

	if (lastFPS != fps) {
		irr::core::stringw str = L"Indie Studio : BomberMan";
		str += " Runs at FPS:";
		str += fps;
		_device->setWindowCaption(str.c_str());
		lastFPS = fps;
	}
}

void PrincipalMenuGame::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsPrincipalMenuGame(std::cerr, "Could not load " + path);
}

void PrincipalMenuGame::initImage()
{
	loadImage("Galaxy", "AssetsIndie/Menus/Global/Galaxy.jpg");
	loadImage("BombermanTitle", "AssetsIndie/Menus/Principal/BombermanTitle.png");
	loadImage("Play", "AssetsIndie/Menus/Principal/button_play.png");
	loadImage("PlayPress", "AssetsIndie/Menus/Principal/button_play_press.png");
	loadImage("Quit", "AssetsIndie/Menus/Principal/button_quit.png");
	loadImage("QuitPress", "AssetsIndie/Menus/Principal/button_quit_press.png");
	loadImage("Settings", "AssetsIndie/Menus/Principal/button_settings.png");
	loadImage("SettingsPress", "AssetsIndie/Menus/Principal/button_settings_press.png");

	_env->addImage(_textures["Galaxy"], irr::core::position2d<int>(0, 0));
	irr::core::dimension2d<irr::u32> size = _textures["BombermanTitle"]->getOriginalSize();
	_env->addImage(_textures["BombermanTitle"], irr::core::position2d<int>(960 - size.Width / 2, 20));
}

void PrincipalMenuGame::initCamera()
{
	_camera = _scene->addCameraSceneNode(0,
		irr::core::vector3df(0.0f, 0.0f, -100.0f),
		irr::core::vector3df(0.0f, 0.0f, 0.0f));
	_camera->setFOV(60.0f * irr::core::DEGTORAD);
}

void PrincipalMenuGame::initEarth()
{
	_config.earthPosition.X = 0;

	_earth = _scene->addSphereSceneNode(_config.earthRadius, 100, 0, -1,
		_config.earthPosition,
		_config.earthRotation);
	_earth->setMaterialTexture(0, _config.earthTexture);
	_earth->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	initCamera();
}

irr::gui::IGUIButton *PrincipalMenuGame::initButton(irr::core::rect<irr::s32> rect,
	std::string image,
	enum ButtonPrincipal func)
{
	irr::gui::IGUIButton *button;

	button = _env->addButton(rect, 0, func);
	button->setImage(_textures[image]);
	button->setPressedImage(_textures[image + "Press"]);
	button->setUseAlphaChannel(true);
	button->setDrawBorder(0);
	return button;
}

void PrincipalMenuGame::displayWindow()
{
	displayFPSTitle();
	_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	_env->drawAll();
	_scene->drawAll();
}

void PrincipalMenuGame::initialization()
{
	_receiver.refresh();
	_buttonStatus = ButtonPrincipal::BUTTON_NOTHING_PRINCIP;
	_device->setEventReceiver(&_receiver);
	initImage();
	initEarth();
	_playButton = initButton(irr::core::rect<irr::s32>(100, 300, 450, 375), "Play",
		ButtonPrincipal::BUTTON_PLAY_PRINCIP);
	_settingsButton = initButton(irr::core::rect<irr::s32>(100, 450, 450, 525), "Settings",
		ButtonPrincipal::BUTTON_SETTINGS_PRINCIP);
	_quitButton = initButton(irr::core::rect<irr::s32>(100, 600, 450, 675), "Quit",
		ButtonPrincipal::BUTTON_QUIT_PRINCIP);
}

SceneStatus PrincipalMenuGame::launchButton()
{
	SceneStatus status = SceneStatus::NOTHING;

	clearScreen();
	switch (_buttonStatus) {
	case ButtonPrincipal::BUTTON_QUIT_PRINCIP:
		status = SceneStatus::QUIT;
		break;
	case ButtonPrincipal::BUTTON_SETTINGS_PRINCIP:
		status = SceneStatus::SETTINGS_MENU;
		break;
	case ButtonPrincipal::BUTTON_PLAY_PRINCIP:
		status = SceneStatus::CHOOSE_GAME;
		break;
	default:
		break;
	}
	return status;
}

SceneStatus PrincipalMenuGame::launch()
{
	SceneStatus status = SceneStatus::PRINCIPAL_MENU;
	initialization();
	Clock clock(_fps);

	#ifdef __unix__
		if (_config.getMusicStatus("Theme") == sf::Music::Stopped)
			_config.launchMusic("Theme");
	#endif
	while (_device->run() && _driver && status == SceneStatus::PRINCIPAL_MENU) {
		if (_buttonStatus != ButtonPrincipal::BUTTON_NOTHING_PRINCIP) {
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Confirmation");
			#endif
			status = launchButton();
		} else if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			status = SceneStatus::QUIT;
		} else if (_device->isWindowActive() && clock.canUpdate()) {
			_config.earthRotation.Y += _earthRotationSpeed;
			_earth->setRotation(_config.earthRotation);
			displayWindow();
			_driver->endScene();
		}
	}
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}
