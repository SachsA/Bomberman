/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ChooseGame.cpp for cpp_indie_studio
*/

#include <iostream>
#include "Clock/Clock.hpp"
#include "Utils/Utils.hpp"
#include "ChooseGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

ChooseGame::ChooseGame(irr::IrrlichtDevice *device,
		       irr::video::IVideoDriver *driver,
	BomberManConfig &config)
	: AMenu(device, driver, config), _receiver(_device, *this)
{
	updateConfigValue("FPS", _fps, 60);
	updateConfigValue("EarthRotationSpeed", _earthRotationSpeed, 0.1);
	updateConfigValue("EarthMovementSpeed", _earthMovementSpeed, 50);
}

void ChooseGame::updateConfigValue(std::string const &key, int &value, int defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stoi(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void ChooseGame::updateConfigValue(std::string const &key, float &value, float defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stof(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void ChooseGame::displayFPSTitle()
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

void ChooseGame::initCamera()
{
	_camera = _scene->addCameraSceneNode(0,
		irr::core::vector3df(0.0f, 0.0f, -100.0f),
		irr::core::vector3df(0.0f, 0.0f, 0.0f));
	_camera->setFOV(60.0f * irr::core::DEGTORAD);
}

void ChooseGame::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsChooseGame(std::cerr, "Could not load " + path);
}

void ChooseGame::initEarth()
{
	loadImage("Galaxy", "AssetsIndie/Menus/Global/Galaxy.jpg");
	_env->addImage(_textures["Galaxy"], irr::core::position2d<int>(0, 0));
	_earth = _scene->addSphereSceneNode(_config.earthRadius, 255, 0, -1,
		_config.earthPosition,
		_config.earthRotation);
	_earth->setMaterialTexture(0, _config.earthTexture);
	_earth->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	initCamera();
}

void ChooseGame::initImage()
{
	loadImage("NewGame", "AssetsIndie/Menus/ChooseGame/NewGame.png");
	loadImage("NewGamePress", "AssetsIndie/Menus/ChooseGame/NewGamePress.png");
	loadImage("QuickGame", "AssetsIndie/Menus/ChooseGame/QuickGame.png");
	loadImage("QuickGamePress", "AssetsIndie/Menus/ChooseGame/QuickGamePress.png");
	loadImage("Galaxy", "AssetsIndie/Menus/Global/Galaxy.jpg");
	loadImage("ChooseGameTitle", "AssetsIndie/Menus/ChooseGame/ChooseGameTitle.png");

	_env->addImage(_textures["Galaxy"], irr::core::position2d<int>(0, 0));
	irr::core::dimension2d<irr::u32> size = _textures["ChooseGameTitle"]->getOriginalSize();
	_env->addImage(_textures["ChooseGameTitle"], irr::core::position2d<int>(960 - size.Width / 2, 20));
}

irr::gui::IGUIButton *ChooseGame::initButton(irr::core::rect<irr::s32> rect,
					     std::string image,
					     enum ButtonChooseGame func)
{
	irr::gui::IGUIButton *button;

	button = _env->addButton(rect, 0, func);
	button->setImage(_textures[image]);
	button->setPressedImage(_textures[image + "Press"]);
	button->setUseAlphaChannel(true);
	button->setDrawBorder(0);
	return button;
}

void ChooseGame::displayWindow()
{
	displayFPSTitle();
	_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	_env->drawAll();
	_scene->drawAll();
}

void ChooseGame::initialization()
{
	_receiver.refresh();
	_buttonStatus = ButtonChooseGame::BUTTON_NOTHING_CHOOSE;
	_device->setEventReceiver(&_receiver);
	initImage();
	_newGame = initButton(irr::core::rect<irr::s32>(1200, 450, 1550, 525), "NewGame",
	ButtonChooseGame::BUTTON_NEW_CHOOSE);
	_quickGame = initButton(irr::core::rect<irr::s32>(1200, 600, 1550, 675), "QuickGame",
	ButtonChooseGame::BUTTON_QUICK_CHOOSE);
}

SceneStatus ChooseGame::launchButton()
{
	SceneStatus status = SceneStatus::NOTHING;

	clearScreen();
	switch (_buttonStatus) {
		case ButtonChooseGame::BUTTON_NEW_CHOOSE:
			status = SceneStatus::NEW_GAME;
			break;
		case ButtonChooseGame::BUTTON_QUICK_CHOOSE:
			status = SceneStatus::QUICK_GAME;
			break;
		default:
			break;
	}
	return status;
}

void ChooseGame::animation(irr::core::vector3df const &to, int frames)
{
	int idx = 0;
	Clock clock(_fps);

	irr::core::vector3df vector = {(to.X - _config.earthPosition.X) / frames,
		(to.Y - _config.earthPosition.Y) / frames,
		(to.Z - _config.earthPosition.Z) / frames
	};
	while (_device->run() && _driver && _device->isWindowActive() && idx < frames) {
		if (clock.canUpdate()) {
			_config.earthRotation.Y += _earthRotationSpeed;
			_config.earthPosition.X += vector.X;
			_config.earthPosition.Z += vector.Z;
			_earth->setRotation(_config.earthRotation);
			_earth->setPosition(_config.earthPosition);
			displayWindow();
			_driver->endScene();
			idx++;
		}
	}
}

SceneStatus ChooseGame::launch()
{
	SceneStatus status = SceneStatus::CHOOSE_GAME;

	initEarth();
	animation(irr::core::vector3df(-30, 0, 0), _earthMovementSpeed);
	initialization();
	Clock clock(_fps);

	while(_device->run() && _driver && status == SceneStatus::CHOOSE_GAME) {
		if (_buttonStatus != ButtonChooseGame::BUTTON_NOTHING_CHOOSE) {
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Confirmation");
			#endif
			status = launchButton();
			clearScreen();
			initEarth();
			animation(irr::core::vector3df(-80, 0, -80), _earthMovementSpeed);
		} else if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Back");
			#endif
			clearScreen();
			initEarth();
			animation(irr::core::vector3df(0, 0, 0), _earthMovementSpeed);
			status = SceneStatus::PRINCIPAL_MENU;
		} else if (_device->isWindowActive() && clock.canUpdate()) {
			_config.earthRotation.Y += _earthRotationSpeed;
			_earth->setRotation(_config.earthRotation);
			displayWindow();
			_driver->endScene();
		}
	}
	clearScreen();
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}