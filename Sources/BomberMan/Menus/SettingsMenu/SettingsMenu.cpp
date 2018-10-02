/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** SettingsMenu.cpp for cpp_indie_studio
*/

#include <iostream>
#include "Clock/Clock.hpp"
#include "Utils/Utils.hpp"
#include "SettingsMenu.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

SettingsMenu::SettingsMenu(irr::IrrlichtDevice *device,
			   irr::video::IVideoDriver *driver,
			   BomberManConfig &config)
	: AMenu(device, driver, config), _receiver(_device, *this)
{
	_device = device;
	_driver = driver;
	_env = _device->getGUIEnvironment();
	_scene = _device->getSceneManager();
	updateConfigValue("FPS", _fps, 60);
	updateConfigValue("EarthRotationSpeed", _earthRotationSpeed, 0.1);
	updateConfigValue("EarthMovementSpeed", _earthMovementSpeed, 50);

}

void SettingsMenu::updateConfigValue(std::string const &key, int &value, int defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stoi(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void SettingsMenu::updateConfigValue(std::string const &key, float &value, float defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stof(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}


void SettingsMenu::displayFPSTitle()
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

void SettingsMenu::initCamera()
{
	_camera = _scene->addCameraSceneNode(0,
		irr::core::vector3df(0.0f, 0.0f, -100.0f),
		irr::core::vector3df(0.0f, 0.0f, 0.0f));
	_camera->setFOV(60.0f * irr::core::DEGTORAD);
}

void SettingsMenu::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsSettingsMenu(std::cerr, "Could not load " + path);
}

void SettingsMenu::initEarth()
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

void SettingsMenu::initImage()
{
	loadImage("Game", "AssetsIndie/Menus/Settings/game.png");
	loadImage("Menus", "AssetsIndie/Menus/Settings/menus.png");
	loadImage("Music", "AssetsIndie/Menus/Settings/musicButton.png");
	loadImage("SettingsTitle", "AssetsIndie/Menus/Settings/SettingsTitle.png");
	loadImage("Volume", "AssetsIndie/Menus/Settings/volume.png");

	irr::core::dimension2d<irr::u32> size = _textures["SettingsTitle"]->getOriginalSize();
	_env->addImage(_textures["SettingsTitle"], irr::core::position2d<int>(960 - size.Width / 2, 20));
	_env->addImage(_textures["Volume"], irr::core::position2d<int>(1980 * 0.4, 1080 * 0.3));
}

void SettingsMenu::initButton(std::string const &button,
			      irr::core::rect<irr::s32> rect,
			      std::string image,
			      enum ButtonSettings func)
{
	_buttons[button] = _env->addButton(rect, 0, func);
	_buttons[button]->setImage(_textures[image]);
	_buttons[button]->setUseAlphaChannel(true);
	_buttons[button]->setDrawBorder(false);
}

void SettingsMenu::initScrollBar(std::string const &scrollbar,
	irr::core::rect<irr::s32> rect,
	enum ButtonSettings func)
{
	_scrollbars[scrollbar] = _env->addScrollBar(true,
		rect, 0, func);
	_scrollbars[scrollbar]->setMax(100);
}

irr::gui::IGUIScrollBar* SettingsMenu::getScrollBar(std::string const &key)
{
	return _scrollbars[key];
}

void SettingsMenu::displayWindow()
{
	displayFPSTitle();
	_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	_env->drawAll();
	_scene->drawAll();
}

void SettingsMenu::initialization()
{
	_receiver.refresh();
	_buttonStatus = ButtonSettings::BUTTON_NOTHING;
	_device->setEventReceiver(&_receiver);
	initImage();

	initScrollBar("Music", irr::core::rect<irr::s32>(400, 400, 1100, 475), MUSIC_SCROLL_BAR);
	initScrollBar("Menus", irr::core::rect<irr::s32>(400, 600, 1100, 675), MENUS_SCROLL_BAR);
	initScrollBar("Game", irr::core::rect<irr::s32>(400, 800, 1100, 875), GAME_SCROLL_BAR);

	#ifdef __unix__
	if (_config.getActiveVolume(SoundType::MUSIC) != _config.getVolumes(SoundType::MUSIC))
		_scrollbars["Music"]->setPos(0);
	else
		_scrollbars["Music"]->setPos(_config.getVolumes(SoundType::MUSIC));

	if (_config.getActiveVolume(SoundType::MENUS) != _config.getVolumes(SoundType::MENUS))
		_scrollbars["Menus"]->setPos(0);
	else
		_scrollbars["Menus"]->setPos(_config.getVolumes(SoundType::MENUS));

	if (_config.getActiveVolume(SoundType::GAME) != _config.getVolumes(SoundType::GAME))
		_scrollbars["Game"]->setPos(0);
	else
		_scrollbars["Game"]->setPos(_config.getVolumes(SoundType::GAME));
	#endif

	initButton("Music", irr::core::rect<irr::s32>(100, 400, 350, 475), "Music",
		ButtonSettings::MUSIC_BUTTON);
	initButton("Menus", irr::core::rect<irr::s32>(100, 600, 350, 675), "Menus",
		ButtonSettings::MENUS_BUTTON);
	initButton("Game", irr::core::rect<irr::s32>(100, 800, 350, 875), "Game",
		ButtonSettings::GAME_BUTTON);
	irr::gui::IGUISkin *skin = _env->getSkin();
	for (irr::s32 i = 0; i < irr::gui::EGDC_COUNT; ++i) {
		irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
	}
}

void SettingsMenu::animation(irr::core::vector3df const &to, int frames)
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

SceneStatus SettingsMenu::launch()
{
	SceneStatus status = SceneStatus::SETTINGS_MENU;
	initEarth();
	animation(irr::core::vector3df(65, 0, 20), _earthMovementSpeed);
	initialization();
	Clock clock(_fps);

	while (_device->run() && _driver && status == SETTINGS_MENU) {
		if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Back");
			#endif
			status = SceneStatus::PRINCIPAL_MENU;
		} else if (_device->isWindowActive() && clock.canUpdate()) {
			_config.earthRotation.Y += _earthRotationSpeed;
			_earth->setRotation(_config.earthRotation);
			displayWindow();
			_driver->endScene();
		}
	}
	clearScreen();
	initEarth();
	animation(irr::core::vector3df(0, 0, 0), _earthMovementSpeed);
	clearScreen();
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}
