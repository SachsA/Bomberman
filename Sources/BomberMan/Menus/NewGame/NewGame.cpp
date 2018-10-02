/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** NewGame.cpp for cpp_indie_studio
*/

#include <iostream>
#include "NewGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

NewGame::NewGame(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver,
	BomberManConfig &config
)
	: AMenu(device, driver, config), _receiver(_device, *this)
{
	initMapCharacter("Gign");
	initMapCharacter("Guerilla");
	initMapCharacter("Phoenix");
	initMapCharacter("Sas");
	_mapCharacter.iterator = _mapCharacter.map.begin();
}

void NewGame::initMapCharacter(std::string name)
{
	std::string pathTexture("AssetsIndie/Character/" + name + "/" + name + ".png");

	_mapCharacter.map.emplace(name, Character());
	if (!(_mapCharacter.map[name].texture = _driver->getTexture(pathTexture.c_str()))) {
		_mapCharacter.map.erase(name);
		throw ErrorsNewGame(std::cerr, "Could not load " + pathTexture);
	}
	_mapCharacter.map.rbegin()->second.name = name;
}

void NewGame::displayFPSTitle()
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

void NewGame::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsNewGame(std::cerr, "Could not load " + path);
}

void NewGame::initImage()
{
	irr::core::dimension2d<irr::u32> size;

	loadImage("Galaxy", "AssetsIndie/Menus/Global/Galaxy.jpg");
	loadImage("NewGameTitle", "AssetsIndie/Menus/NewGame/NewGameTitle.png");
	loadImage("PlayerTitle", "AssetsIndie/Menus/NewGame/PlayerTitle.png");
	loadImage("Start", "AssetsIndie/Menus/NewGame/Start.png");
	loadImage("StartPress", "AssetsIndie/Menus/NewGame/StartPress.png");
	loadImage("ArrowRight", "AssetsIndie/Menus/NewGame/ArrowRight.png");
	loadImage("ArrowRightPress", "AssetsIndie/Menus/NewGame/ArrowRightPress.png");
	loadImage("ArrowLeft", "AssetsIndie/Menus/NewGame/ArrowLeft.png");
	loadImage("ArrowLeftPress", "AssetsIndie/Menus/NewGame/ArrowLeftPress.png");

	_env->addImage(_textures["Galaxy"], irr::core::position2d<int>(0, 0));
	size = _textures["NewGameTitle"]->getOriginalSize();
	_env->addImage(_textures["NewGameTitle"], irr::core::position2d<int>(960 - size.Width / 2, 20));
	size = _textures["PlayerTitle"]->getOriginalSize();
	_env->addImage(_textures["PlayerTitle"], irr::core::position2d<int>(960 - size.Width / 2, 150));
}

irr::gui::IGUIButton *NewGame::initButton(irr::core::rect<irr::s32> rect,
					  std::string image,
					  enum ButtonNewGame func)
{
	irr::gui::IGUIButton *button;

	button = _env->addButton(rect, 0, func);
	button->setImage(_textures[image]);
	button->setPressedImage(_textures[image + "Press"]);
	button->setUseAlphaChannel(true);
	button->setDrawBorder(0);
	return button;
}

void NewGame::displayWindow()
{
	displayFPSTitle();
	_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	_env->drawAll();
	_scene->drawAll();
}

void NewGame::PlaceOneButton(std::string name, enum ButtonNewGame func,
			     std::string button, int width, int height)
{
	int widthSrc = 0;
	int heightSrc = 0;
	int widthDest = 0;
	int heightDest = 0;
	irr::core::dimension2d<irr::u32> size;

	size = _textures[name.c_str()]->getOriginalSize();
	widthSrc = _driver->getScreenSize().Width / 2 - (int)size.Width / 2 + width;
	widthDest = _driver->getScreenSize().Width / 2 + (int)size.Width / 2 + width;
	heightSrc = _driver->getScreenSize().Height / 2 - (int)size.Height / 2 + height;
	heightDest = _driver->getScreenSize().Height / 2 + (int)size.Height / 2 + height;
	_buttons[button.c_str()] = initButton(irr::core::rect<irr::s32>(widthSrc, heightSrc, widthDest, heightDest),
	name, func);
}

void NewGame::placeButtons()
{
	PlaceOneButton("Start", ButtonNewGame::BUTTON_START_NEW, "Start", 0, 400);
	PlaceOneButton("ArrowRight", ButtonNewGame::BUTTON_RIGHT_NEW, "ArrRight", 350, 0);
	PlaceOneButton("ArrowLeft", ButtonNewGame::BUTTON_LEFT_NEW, "ArrLeft", -350, 0);
}

void NewGame::initInputUsername()
{
	irr::gui::IGUIFont *font;
	irr::core::dimension2d<irr::u32> size;
	std::string path("AssetsIndie/Fonts/bauhaus.png");

	if (!(font = _env->getFont(path.c_str())))
		throw ErrorsNewGame(std::cerr, "Could not load " + path);
	_inputBox = _env->addEditBox(L"EDIT_USER_NAME",
		irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 2 - 500,
			_driver->getScreenSize().Height / 2 + 165,
			_driver->getScreenSize().Width / 2 + 500,
			_driver->getScreenSize().Height / 2 + 310),
		false);
	_inputBox->setOverrideFont(font);
	_inputBox->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	_inputBox->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	_inputBox->setDrawBackground(false);
	_inputBox->setMax(15);
	_inputBox->setDrawBorder(0);
}

void NewGame::initCharacter()
{
	irr::scene::IAnimatedMesh *node;
	std::string name = _mapCharacter.iterator->first;
	std::string path("AssetsIndie/Character/" + name + "/" + name + "Idle.MD3");

	if (!(node = _scene->getMesh(path.c_str())))
		throw ErrorsNewGame(std::cerr, "Could not load " + path);
	if (node) {
		_mapCharacter.iterator->second.mesh = _scene->addAnimatedMeshSceneNode(node);
		if (_mapCharacter.iterator->second.mesh) {
			_mapCharacter.iterator->second.mesh->setMaterialTexture(0,
				_mapCharacter.iterator->second.texture);
			_mapCharacter.iterator->second.mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_mapCharacter.iterator->second.mesh->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
			_mapCharacter.iterator->second.mesh->setPosition(irr::core::vector3df(0, -10, 0));
			_mapCharacter.iterator->second.mesh->setRotation(irr::core::vector3df(0, 0, 0));
		}
	}
}

void NewGame::initCamera()
{
	_camera = _scene->addCameraSceneNode(0,
		irr::core::vector3df(0.0f, 0.0f, -100.0f),
		irr::core::vector3df(0.0f, 0.0f, 0.0f));
	_camera->setFOV(60.0f * irr::core::DEGTORAD);
}

void NewGame::initialization()
{
	_config._users.clear();
	_userName = "Player";
	_mapCharacter.iterator = _mapCharacter.map.begin();
	_receiver.refresh();
	_buttonStatus = ButtonNewGame::BUTTON_NOTHING_NEW;
	_device->setEventReceiver(&_receiver);
	initImage();
	placeButtons();
	initInputUsername();
	initCharacter();
	initCamera();
}

std::string NewGame::getUserInput()
{
	std::wstring wUsername(_inputBox->getText());
	std::string username(wUsername.begin(), wUsername.end());
	return username;
}

void NewGame::changeCharacterLeft()
{
	if (_mapCharacter.iterator == _mapCharacter.map.begin()) {
		_mapCharacter.iterator = _mapCharacter.map.end();
		_mapCharacter.iterator--;
	} else
		_mapCharacter.iterator--;
	_scene->clear();
	initCamera();
	initCharacter();
}

void NewGame::changeCharacterRight()
{
	browseCharacter();
	_scene->clear();
	initCamera();
	initCharacter();
}

void NewGame::browseCharacter()
{
	if (_mapCharacter.iterator->first == _mapCharacter.map.rbegin()->first)
		_mapCharacter.iterator = _mapCharacter.map.begin();
	else
		_mapCharacter.iterator++;
}

void NewGame::launchButton()
{
	switch (_buttonStatus) {
	case ButtonNewGame::BUTTON_RIGHT_NEW:
		#ifdef __unix__
			_config.launchSound(SoundType::MENUS, "Press");
		#endif
		changeCharacterRight();
		break;
	case ButtonNewGame::BUTTON_LEFT_NEW:
		#ifdef __unix__
			_config.launchSound(SoundType::MENUS, "Press");
		#endif
		changeCharacterLeft();
		break;
	default:
		break;
	}
}

void NewGame::fillUserDataPlayer()
{
	_config._users.emplace_back(_mapCharacter.iterator->second);
	_config._users.back().userName = _userName;
	_config._users.back().score = 0;
	_config._users.back().level = 0;
	_config._users.back().type = HUMAN;
}

void NewGame::fillUserDataAI()
{
	int i = 1;
	std::string userAI = "AI_";
	std::string name = _mapCharacter.iterator->first;

	browseCharacter();
	while (name != _mapCharacter.iterator->first) {
		_config._users.emplace_back(_mapCharacter.iterator->second);
		_config._users.back().userName = userAI + std::to_string(i);
		_config._users.back().score = 0;
		_config._users.back().level = 0;
		_config._users.back().type = AI;
		browseCharacter();
		i++;
	}
}

SceneStatus NewGame::launchSceneButton()
{
	SceneStatus status = SceneStatus::NOTHING;

	clearScreen();
	switch (_buttonStatus) {
	case ButtonNewGame::BUTTON_START_NEW:
		fillUserDataPlayer();
		fillUserDataAI();
		status = SceneStatus::GFX_GAME;
		break;
	default:
		break;
	}
	return status;
}

void NewGame::arrowFunctions()
{
	static bool pressRight = false;
	static bool pressLeft = false;

	if (_receiver.IsKeyDown(irr::KEY_RIGHT) && pressRight == false) {
		pressRight = true;
		_buttons["ArrRight"]->setPressed(true);
	} else if (!_receiver.IsKeyDown(irr::KEY_RIGHT) && pressRight == true) {
		pressRight = false;
		_buttons["ArrRight"]->setPressed(false);
		_buttonStatus = ButtonNewGame::BUTTON_RIGHT_NEW;
	}
	if (_receiver.IsKeyDown(irr::KEY_LEFT) && pressLeft == false) {
		pressLeft = true;
		_buttons["ArrLeft"]->setPressed(true);
	} else if (!_receiver.IsKeyDown(irr::KEY_LEFT) && pressLeft == true) {
		pressLeft = false;
		_buttons["ArrLeft"]->setPressed(false);
		_buttonStatus = ButtonNewGame::BUTTON_LEFT_NEW;
	}
}

void NewGame::keyboardFunctions()
{
	if (_receiver.IsKeyDown(irr::KEY_KEY_T))
		_env->setFocus(_inputBox);
	else if (_receiver.IsKeyDown(irr::KEY_RETURN)) {
		_env->setFocus(0);
		_userName = getUserInput();
	} else if (_env->getFocus() != _inputBox) {
		arrowFunctions();
	}
}

void NewGame::checkFocus()
{
	if (_env->getFocus() == _inputBox)
		_inputBox->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
	else
		_inputBox->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

SceneStatus NewGame::launch()
{
	SceneStatus status = SceneStatus::NEW_GAME;

	initialization();
	while (_device->run() && _driver && status == SceneStatus::NEW_GAME) {
		if (_buttonStatus != ButtonNewGame::BUTTON_NOTHING_NEW) {
			if (_buttonStatus == ButtonNewGame::BUTTON_START_NEW) {
				#ifdef __unix__
					_config.launchSound(SoundType::MENUS, "Confirmation");
				#endif
				status = launchSceneButton();
			} else
				launchButton();
			_buttonStatus = ButtonNewGame::BUTTON_NOTHING_NEW;
		} else if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Back");
			#endif
			status = SceneStatus::CHOOSE_GAME;
		} else if (_device->isWindowActive()) {
			checkFocus();
			keyboardFunctions();
			displayWindow();
		}
		_driver->endScene();
	}
	clearScreen();
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}