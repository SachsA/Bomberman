/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** QuickGame.cpp for cpp_indie_studio
*/

#include <sstream>
#include <iostream>
#include "QuickGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

QuickGame::QuickGame(irr::IrrlichtDevice *device,
		 irr::video::IVideoDriver *driver,
		 BomberManConfig &config)
	: AMenu(device, driver, config), _receiver(_device, *this)
{
	std::size_t i = 0;

	addToBoard();
	if (!(_font = _env->getFont("AssetsIndie/Fonts/malgun25.png")))
		throw ErrorsQuickGame(std::cerr, "can't load malgun font");
	_namePerso.emplace_back("Gign");
	_namePerso.emplace_back("Guerilla");
	_namePerso.emplace_back("Phoenix");
	_namePerso.emplace_back("Sas");
	for (size_t iname = 0; iname < _namePerso.size(); ++iname)
		initMapCharacter(_namePerso[iname]);
	while (++i <= 4) {
		_mapPlayer[i].iterator = _mapPlayer[i].map.begin();
		_mapBoard[i].iterator = _mapBoard[i].map.begin();
	}
}

void QuickGame::addToBoard()
{
	_positionBoard.emplace_back(irr::core::vector3df(-90, 10, 0));
	_positionBoard.emplace_back(irr::core::vector3df(-25, 10, 0));
	_positionBoard.emplace_back(irr::core::vector3df(-90, -20, 0));
	_positionBoard.emplace_back(irr::core::vector3df(-25, -20, 0));
}

void QuickGame::initMapCharacter(std::string name)
{
	std::size_t i = 0;
	irr::video::ITexture *texture;
	std::string pathTexture("AssetsIndie/Character/" + name + "/" + name + ".png");

	while (++i <= 4) {
		_mapPlayer[i].map.emplace(name, Character());
		_mapBoard[i].map.emplace(name, Character());
		if (!(texture = _driver->getTexture(pathTexture.c_str()))) {
			_mapPlayer[i].map.erase(name);
			_mapBoard[i].map.erase(name);
			throw ErrorsQuickGame(std::cerr, "Could not load " + pathTexture);
		}
		_mapPlayer[i].map[name].texture = texture;
		_mapPlayer[i].map.rbegin()->second.name = name;
		_mapBoard[i].map[name].texture = texture;
		_mapBoard[i].map.rbegin()->second.name = name;
	}
}

void QuickGame::displayFPSTitle()
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

void QuickGame::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsQuickGame(std::cerr, "Could not load " + path);
}

void QuickGame::initImage()
{
	irr::core::dimension2d<irr::u32> size;

	loadImage("Galaxy", "AssetsIndie/Menus/Global/Galaxy.jpg");
	loadImage("QuickGameTitle", "AssetsIndie/Menus/QuickGame/QuickGameTitle.png");
	loadImage("HumanTitle", "AssetsIndie/Menus/QuickGame/HumanTitle.png");
	loadImage("AITitle", "AssetsIndie/Menus/QuickGame/AITitle.png");
	loadImage("Start", "AssetsIndie/Menus/QuickGame/Start.png");
	loadImage("StartPress", "AssetsIndie/Menus/QuickGame/StartPress.png");
	loadImage("Add", "AssetsIndie/Menus/QuickGame/Add.png");
	loadImage("AddPress", "AssetsIndie/Menus/QuickGame/AddPress.png");
	loadImage("ArrowRight", "AssetsIndie/Menus/QuickGame/ArrowRight.png");
	loadImage("ArrowRightFocus", "AssetsIndie/Menus/QuickGame/ArrowRightFocus.png");
	loadImage("ArrowRightPress", "AssetsIndie/Menus/QuickGame/ArrowRightPress.png");
	loadImage("ArrowLeft", "AssetsIndie/Menus/QuickGame/ArrowLeft.png");
	loadImage("ArrowLeftFocus", "AssetsIndie/Menus/QuickGame/ArrowLeftFocus.png");
	loadImage("ArrowLeftPress", "AssetsIndie/Menus/QuickGame/ArrowLeftPress.png");
	loadImage("ArrowRightType", "AssetsIndie/Menus/QuickGame/ArrowRightType.png");
	loadImage("ArrowRightTypeFocus", "AssetsIndie/Menus/QuickGame/ArrowRightTypeFocus.png");
	loadImage("ArrowRightTypePress", "AssetsIndie/Menus/QuickGame/ArrowRightTypePress.png");
	loadImage("ArrowLeftType", "AssetsIndie/Menus/QuickGame/ArrowLeftType.png");
	loadImage("ArrowLeftTypeFocus", "AssetsIndie/Menus/QuickGame/ArrowLeftTypeFocus.png");
	loadImage("ArrowLeftTypePress", "AssetsIndie/Menus/QuickGame/ArrowLeftTypePress.png");

	_env->addImage(_textures["Galaxy"], irr::core::position2d<int>(0, 0));
	size = _textures["QuickGameTitle"]->getOriginalSize();
	_env->addImage(_textures["QuickGameTitle"], irr::core::position2d<int>(960 - size.Width / 2, 20));
	_sizeHuman = _textures["HumanTitle"]->getOriginalSize();
	_sizeAI = _textures["AITitle"]->getOriginalSize();
}

irr::gui::IGUIButton *QuickGame::initButton(irr::core::rect<irr::s32> rect,
					    std::string image,
					    enum ButtonQuickGame func)
{
	irr::gui::IGUIButton *button;

	button = _env->addButton(rect, 0, func);
	button->setImage(_textures[image]);
	button->setPressedImage(_textures[image + "Press"]);
	button->setUseAlphaChannel(true);
	button->setDrawBorder(0);
	return button;
}

void QuickGame::displayWindow()
{
	displayFPSTitle();
	_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	_env->drawAll();
	_scene->drawAll();
}

void QuickGame::PlaceOneButton(std::string name, enum ButtonQuickGame func,
			       std::string button,
			       int width, int height)
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

void QuickGame::placeButtons()
{
	PlaceOneButton("Start", ButtonQuickGame::BUTTON_START_QUICK, "Start", -700, 400);
	PlaceOneButton("Add", ButtonQuickGame::BUTTON_ADD_QUICK, "Add", 500, 400);
	PlaceOneButton("ArrowRight", ButtonQuickGame::BUTTON_RIGHT_QUICK, "RightCharac", 700, 0);
	PlaceOneButton("ArrowLeft", ButtonQuickGame::BUTTON_LEFT_QUICK, "LeftCharac", 300, 0);
	PlaceOneButton("ArrowRightType", ButtonQuickGame::BUTTON_RIGHT_TYPE_QUICK, "RightType", 650, -300);
	PlaceOneButton("ArrowLeftType", ButtonQuickGame::BUTTON_LEFT_TYPE_QUICK, "LeftType", 350, -300);
	PlaceOneButton("HumanTitle", ButtonQuickGame::BUTTON_NOTHING_QUICK, "PlayerType", 500, -300);
	_buttons["PlayerType"]->setPressedImage(0);
	_buttons["LeftCharac"]->setImage(_textures["ArrowLeftFocus"]);
	_buttons["RightCharac"]->setImage(_textures["ArrowRightFocus"]);
}

void QuickGame::initInputUsername()
{
	std::string name;
	irr::gui::IGUIFont *font;
	irr::core::dimension2d<irr::u32> size;
	std::string path("AssetsIndie/Fonts/bauhaus.png");

	if (!(font = _env->getFont(path.c_str())))
		throw ErrorsQuickGame(std::cerr, "Could not load " + path);
	if (_player != 5)
		name = std::string("EDIT_") + _mapName[_player];
	else
		name = std::string("TEAM_COMPLETED");
	irr::core::stringw str = name.c_str();
	_inputBox = _env->addEditBox(str.c_str(), irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 2 - 0,
									    _driver->getScreenSize().Height / 2 + 165,
									    _driver->getScreenSize().Width / 2 + 1000,
									    _driver->getScreenSize().Height / 2 + 310),
									    false);
	_inputBox->setOverrideFont(font);
	_inputBox->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	_inputBox->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	_inputBox->setDrawBackground(false);
	_inputBox->setMax(15);
	_inputBox->setDrawBorder(0);
}

void QuickGame::initCharacter(irr::core::vector3df scale,
			      irr::core::vector3df position,
			      irr::core::vector3df rotation,
		      	      dataMap<std::string, Character> &elem)
{
	irr::scene::IAnimatedMesh *node;
	std::string name = elem.iterator->first;
	std::string path("AssetsIndie/Character/" + name + "/" + name + "Idle.MD3");

	if (!(node = _scene->getMesh(path.c_str())))
		throw ErrorsQuickGame(std::cerr, "Could not load " + path);
	if (node) {
		elem.iterator->second.mesh = _scene->addAnimatedMeshSceneNode(node);
		if (elem.iterator->second.mesh) {
			elem.iterator->second.mesh->setMaterialTexture(0, elem.iterator->second.texture);
			elem.iterator->second.mesh->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			elem.iterator->second.mesh->setScale(scale);
			elem.iterator->second.mesh->setPosition(position);
			elem.iterator->second.mesh->setRotation(rotation);
		}
	}
}

void QuickGame::initCamera()
{
	_camera = _scene->addCameraSceneNode(0,
		irr::core::vector3df(0.0f, 0.0f, -100.0f),
		irr::core::vector3df(0.0f, 0.0f, 0.0f));
	_camera->setFOV(60.0f * irr::core::DEGTORAD);
}

void QuickGame::clearPlayer()
{
	std::size_t i = 0;

	_scene->clear();
	initCamera();
	initCharacter(irr::core::vector3df(0.5, 0.5, 0.5),
		      irr::core::vector3df(60, -10, 0),
		      irr::core::vector3df(0, 30, 0),
	      	      _mapPlayer[_player]);
	while (i < _config._users.size()) {
		initCharacter(_scaleBoard, _positionBoard.at(i), _rotationBoard, _mapBoard[i + 1]);
		i++;
	}
}

void QuickGame::refreshConfigs()
{
	std::size_t i = 0;
	std::string player("Player");

	_down = true;
	_player = 1;
	_playerNature = HUMAN;
	_config._users.clear();
	while (++i <= 4) {
		std::stringstream ss;
		_mapPlayer[i].iterator = _mapPlayer[i].map.begin();
		ss << player << i;
		_mapName[i] = ss.str();
	}
	_receiver.refresh();
	_buttonStatus = ButtonQuickGame::BUTTON_NOTHING_QUICK;
	_device->setEventReceiver(&_receiver);
}

void QuickGame::initialization()
{
	refreshConfigs();
	initImage();
	placeButtons();
	initInputUsername();
	initCharacter(irr::core::vector3df(0.5, 0.5, 0.5),
		      irr::core::vector3df(60, -10, 0),
		      irr::core::vector3df(0, 30, 0),
	      	      _mapPlayer[_player]);
	initCamera();
}

std::string QuickGame::getUserInput()
{
	std::wstring wUsername(_inputBox->getText());
	std::string username(wUsername.begin(), wUsername.end());
	return username;
}

void QuickGame::changeCharacterLeft()
{
	if (_mapPlayer[_player].iterator == _mapPlayer[_player].map.begin()) {
		_mapPlayer[_player].iterator = _mapPlayer[_player].map.end();
		_mapPlayer[_player].iterator--;
	} else
		_mapPlayer[_player].iterator--;
	clearPlayer();
}

void QuickGame::changeCharacterRight()
{
	browseCharacter();
	clearPlayer();
}

void QuickGame::browseCharacter()
{
	if (_mapPlayer[_player].iterator->first == _mapPlayer[_player].map.rbegin()->first)
		_mapPlayer[_player].iterator = _mapPlayer[_player].map.begin();
	else
		_mapPlayer[_player].iterator++;
}

void QuickGame::inversePlayerNature()
{
	if (_playerNature == HUMAN) {
		_buttons["PlayerType"]->setImage(_textures["AITitle"]);
		_playerNature = AI;
	} else {
		_buttons["PlayerType"]->setImage(_textures["HumanTitle"]);
		_playerNature = HUMAN;
	}
}

void QuickGame::displayNatureBoard()
{
	int x = 0;
	int y = 0;
	int width = _driver->getScreenSize().Width / 2 - 860;
	int height = _driver->getScreenSize().Height / 2 - 345;
	std::string image;
	std::size_t i = -1;

	while (++i < _config._users.size()) {
		if (_config._users.at(i).type == HUMAN) {
			image = std::string("HumanTitle");
			_env->addImage(_textures[image.c_str()],
				      irr::core::position2d<int>(width + x - _sizeHuman.Width / 2,
					      			 height + y  - _sizeHuman.Height / 2));
		} else {
			image = std::string("AITitle");
			_env->addImage(_textures[image.c_str()],
				      irr::core::position2d<int>(width + x - _sizeAI.Width / 2,
					      			 height + y  - _sizeAI.Height / 2));
		}
		x += 610;
		if (i == 1) {
			x = 0;
   			y += 280;
   		}
	}
}

void QuickGame::displayNameBoard()
{
	int x = 0;
	int y = 0;
	std::size_t i = -1;

	while (++i < _config._users.size()) {
		irr::core::stringw str = _mapName[i + 1].c_str();
		_font->draw(str.c_str(), irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 2 - 750 + x,
								   _driver->getScreenSize().Height / 2 - 230 + y,
								   _driver->getScreenSize().Width / 2 - 650 + x,
								   _driver->getScreenSize().Height / 2 - 130 + y),
		irr::video::SColor(255, 255, 0, 0));
		x += 600;
		if (i == 1) {
			x = 0;
			y += 280;
		}
	}
}

void QuickGame::displayBoardCharac()
{
	displayNatureBoard();
	displayNameBoard();
}

void QuickGame::launchButton()
{
	switch (_buttonStatus) {
		case ButtonQuickGame::BUTTON_ADD_QUICK:
			if (_config._users.size() < 4) {
				#ifdef __unix__
					_config.launchSound(SoundType::MENUS, "Confirmation");
				#endif
				_mapBoard[_player].iterator = _mapPlayer[_player].iterator;
				fillUserDataPlayer(_playerNature);
				_mapPlayer[_player].iterator = _mapPlayer[_player].map.begin();
				clearPlayer();
				_player++;
				_inputBox->remove();
				initInputUsername();
			}
			break;
		case ButtonQuickGame::BUTTON_RIGHT_QUICK:
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Press");
			#endif
			changeCharacterRight();
			break;
		case ButtonQuickGame::BUTTON_LEFT_QUICK:
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Press");
			#endif
			changeCharacterLeft();
			break;
		case ButtonQuickGame::BUTTON_RIGHT_TYPE_QUICK:
			inversePlayerNature();
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Press");
			#endif
			break;
		case ButtonQuickGame::BUTTON_LEFT_TYPE_QUICK:
			inversePlayerNature();
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Press");
			#endif
			break;
		default:
			break;
	}
}

void QuickGame::fillUserDataPlayer(enum PlayerType playerNature)
{
	_config._users.emplace_back(_mapPlayer[_player].iterator->second);
	_config._users.back().userName = _mapName[_player];
	_config._users.back().score = 0;
	_config._users.back().level = 0;
	_config._users.back().type = playerNature;
}

void QuickGame::fillUserDataAI()
{
	std::string name;

	while (_config._users.size() < 4) {
		name = _mapPlayer[_player].iterator->first;
		_mapPlayer[_player].iterator = _mapPlayer[_player - 1].iterator;
		browseCharacter();
		_config._users.emplace_back(_mapPlayer[_player].iterator->second);
		_config._users.back().userName = _mapName[_player];
		_config._users.back().score = 0;
		_config._users.back().level = 0;
		_config._users.back().type = AI;
		_player++;
	}
}

SceneStatus QuickGame::launchSceneButton()
{
	SceneStatus status = SceneStatus::NOTHING;

	clearScreen();
	switch (_buttonStatus) {
		case ButtonQuickGame::BUTTON_START_QUICK:
			if (_config._users.size() == 0) {
				fillUserDataPlayer(HUMAN);
				_player++;
			}
			fillUserDataAI();
			status = SceneStatus::GFX_GAME;
			break;
		default:
			break;
	}
	return status;
}

void QuickGame::arrowFunctionsCharac()
{
	static bool pressRight = false;
	static bool pressLeft = false;

	if (_receiver.IsKeyDown(irr::KEY_RIGHT) && pressRight == false) {
		pressRight = true;
		_buttons["RightCharac"]->setPressed(true);
	} else if (!_receiver.IsKeyDown(irr::KEY_RIGHT) && pressRight == true) {
		pressRight = false;
		_buttons["RightCharac"]->setPressed(false);
		_buttonStatus = ButtonQuickGame::BUTTON_RIGHT_QUICK;
	} if (_receiver.IsKeyDown(irr::KEY_LEFT) && pressLeft == false) {
		pressLeft = true;
		_buttons["LeftCharac"]->setPressed(true);
	} else if (!_receiver.IsKeyDown(irr::KEY_LEFT) && pressLeft == true) {
		pressLeft = false;
		_buttons["LeftCharac"]->setPressed(false);
		_buttonStatus = ButtonQuickGame::BUTTON_LEFT_QUICK;
	}
}

void QuickGame::arrowFunctionsType()
{
	static bool pressRight = false;
	static bool pressLeft = false;

	if (_receiver.IsKeyDown(irr::KEY_RIGHT) && pressRight == false) {
		pressRight = true;
		_buttons["RightType"]->setPressed(true);
	} else if (!_receiver.IsKeyDown(irr::KEY_RIGHT) && pressRight == true) {
		pressRight = false;
		_buttons["RightType"]->setPressed(false);
		_buttonStatus = ButtonQuickGame::BUTTON_RIGHT_TYPE_QUICK;
	} if (_receiver.IsKeyDown(irr::KEY_LEFT) && pressLeft == false) {
		pressLeft = true;
		_buttons["LeftType"]->setPressed(true);
	} else if (!_receiver.IsKeyDown(irr::KEY_LEFT) && pressLeft == true) {
		pressLeft = false;
		_buttons["LeftType"]->setPressed(false);
		_buttonStatus = ButtonQuickGame::BUTTON_LEFT_TYPE_QUICK;
	}
}

void QuickGame::arrowsFocus(std::string type, std::string charac)
{
	std::string rightType("ArrowRightType");
	std::string leftType("ArrowLeftType");
	std::string rightCharac("ArrowRight");
	std::string leftCharac("ArrowLeft");

	_buttons["RightType"]->setImage(_textures[std::string(rightType + type).c_str()]);
	_buttons["LeftType"]->setImage(_textures[std::string(leftType + type).c_str()]);
	_buttons["RightCharac"]->setImage(_textures[std::string(rightCharac + charac).c_str()]);
	_buttons["LeftCharac"]->setImage(_textures[std::string(leftCharac + charac).c_str()]);
}

void QuickGame::keyboardFunctions()
{
	if (_receiver.IsKeyDown(irr::KEY_KEY_T))
		_env->setFocus(_inputBox);
	else if (_receiver.IsKeyDown(irr::KEY_RETURN)) {
		_env->setFocus(0);
		_mapName[_player] = getUserInput();
	} else if (_env->getFocus() != _inputBox) {
		if (_receiver.IsKeyDown(irr::KEY_UP)) {
			arrowsFocus("Focus", "");
			_down = false;
		} else if (_receiver.IsKeyDown(irr::KEY_DOWN)) {
			arrowsFocus("", "Focus");
			_down = true;
		} if (_down == true)
			arrowFunctionsCharac();
		else
			arrowFunctionsType();
	}
}

void QuickGame::checkFocus()
{
	if (_env->getFocus() == _inputBox)
		_inputBox->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
	else
		_inputBox->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

SceneStatus QuickGame::launch()
{
	SceneStatus status = SceneStatus::QUICK_GAME;

	initialization();
	while (_device->run() && _driver && status == SceneStatus::QUICK_GAME) {
		if (_buttonStatus != ButtonQuickGame::BUTTON_NOTHING_QUICK) {
			if (_buttonStatus == ButtonQuickGame::BUTTON_START_QUICK) {
				#ifdef __unix__
					_config.launchSound(SoundType::MENUS, "Confirmation");
				#endif
				status = launchSceneButton();
			} else
				if (_player <= 4)
					launchButton();
			_buttonStatus = ButtonQuickGame::BUTTON_NOTHING_QUICK;
		} else if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			#ifdef __unix__
				_config.launchSound(SoundType::MENUS, "Back");
			#endif
			status = SceneStatus::CHOOSE_GAME;
		}
		else if (_device->isWindowActive()) {
			checkFocus();
			keyboardFunctions();
			displayWindow();
			displayBoardCharac();
		}
		_driver->endScene();
	}
	clearScreen();
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}