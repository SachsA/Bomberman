/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** IntroGame.cpp for cpp_indie_studio
*/

#include <iostream>
#include "Clock/Clock.hpp"
#include "Utils/Utils.hpp"
#include "IntroGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

IntroGame::IntroGame(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver,
	BomberManConfig &config
)
	: AMenu(device, driver, config)
{
	#ifdef __unix__
		_config.insertMusic("Play", "AssetsIndie/Sounds/Playstation.wav");
		_config.insertSound(SoundType::MENUS, "Shot", "AssetsIndie/Sounds/Shot.wav");
	#endif
	updateConfigValue("BirdSpeed", _birdSpeed, 300);
	updateConfigValue("FPS", _fps, 60);
}

void IntroGame::updateConfigValue(std::string const &key, int &value, int defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stoi(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void IntroGame::displayFPSTitle()
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

void IntroGame::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsIntroGame(std::cerr, "Could not load " + path);
}

void IntroGame::initImage()
{
	_pos_x_rarog = (_driver->getScreenSize().Width / 2) - 655;
	_pos_y_rarog = (_driver->getScreenSize().Height / 2) - 240;
	_pos_x_bird = _driver->getScreenSize().Width;
	_pos_y_bird = _driver->getScreenSize().Height / 2 - 175;

	loadImage("Rarog", "AssetsIndie/Menus/Intro/rarog.png");
	loadImage("CDProjekt", "AssetsIndie/Menus/Intro/CDProjekt.png");
	loadImage("Background", "AssetsIndie/Menus/Intro/Background.jpg");
	loadImage("SpaceToStart", "AssetsIndie/Menus/Intro/SpaceToStart.png");
	loadImage("Bird", "AssetsIndie/Menus/Intro/red_bird.png");

	_env->addImage(_textures["Bird"], irr::core::position2d<int>(_pos_x_bird, _pos_y_bird));
}

void IntroGame::launchFader(irr::video::SColor color, irr::u32 timeFade)
{
	irr::gui::IGUIInOutFader *fader;

	fader = _device->getGUIEnvironment()->addInOutFader();
	fader->setColor(color);
	fader->fadeIn(timeFade);
}

void IntroGame::displayCDProjekt()
{
	int width = 0;
	int height = 0;

	if (_textures["CDProjekt"]) {
		_size = _textures["CDProjekt"]->getOriginalSize();
		width = _driver->getScreenSize().Width / 2 - _size.Width / 2;
		height = _driver->getScreenSize().Height / 2 - _size.Height / 2;
		_env->addImage(_textures["CDProjekt"], irr::core::position2d<int>(width, height));
	}

	if (_textures["SpaceToStart"]) {
		_size = _textures["SpaceToStart"]->getOriginalSize();
		width = _driver->getScreenSize().Width / 2 - _size.Width / 2;
		height = 650;
		_env->addImage(_textures["SpaceToStart"], irr::core::position2d<int>(width, height));
	}
}

void IntroGame::move_bird(irr::u32 &after, bool &placed)
{
	clearScreen();
	_env->addImage(_textures["Background"], irr::core::position2d<int>(0, 0));
	displayCDProjekt();
	if (_pos_x_bird > _pos_x_rarog) {
		const irr::u32 now = _device->getTimer()->getTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - after) / 1000.f;
		after = now;
		_pos_x_bird -= _birdSpeed * frameDeltaTime;
		_env->addImage(_textures["Bird"], irr::core::position2d<int>(_pos_x_bird, _pos_y_bird));
	} else {
		#ifdef __unix__
			_config.stopSound(SoundType::MUSIC, "Play");
			_config.launchSound(SoundType::MENUS, "Shot");
		#endif
		launchFader(irr::video::SColor(0, 255, 255, 255), 500);
		_env->addImage(_textures["Rarog"], irr::core::position2d<int>(_pos_x_rarog, _pos_y_rarog));
		placed = true;
	}
}

void IntroGame::displayWindow()
{
	displayFPSTitle();
	_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	_env->drawAll();
	_scene->drawAll();
	_driver->endScene();
}

void IntroGame::initialization()
{
	_device->setEventReceiver(&_receiver);
	initImage();
}

SceneStatus IntroGame::launch()
{
	bool placed = false;
	SceneStatus status = SceneStatus::INTRO;
	irr::u32 after = _device->getTimer()->getTime();
	Clock clock(_fps);

	initialization();
	#ifdef __unix__
		_config.launchMusic("Play");
	#endif
	while (_device->run() && _driver && status == SceneStatus::INTRO) {
		if (_receiver.IsKeyDown(irr::KEY_ESCAPE))
			status = SceneStatus::QUIT;
		else if (_receiver.IsKeyDown(irr::KEY_SPACE)) {
			clearScreen();
			launchFader(irr::video::SColor(0, 255, 255, 255), 3000);
			status = SceneStatus::PRINCIPAL_MENU;
		} else if (_device->isWindowActive()) {
			if (clock.canUpdate()) {
				if (placed == false)
					move_bird(after, placed);
				displayWindow();
			}
		}
	}
	#ifdef __unix__
		_config.stopSound(SoundType::MENUS, "Shot");
	#endif
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}
