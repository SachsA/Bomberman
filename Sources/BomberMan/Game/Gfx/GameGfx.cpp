//
// EPITECH PROJECT, 2018
// indie-dev-client
// File description:
// GameGfx.cpp
//

#include <ctime>
#include <iostream>
#include "Clock/Clock.hpp"
#include "Utils/Utils.hpp"
#include "GameGfx.hpp"
#include "Box.hpp"
#include "Wall.hpp"
#include "SpeedUp.hpp"
#include "BombUp.hpp"
#include "PowerUp.hpp"
#include "Human.hpp"
#include "Ai.hpp"

GameGfx::GameGfx(irr::IrrlichtDevice *device,
	irr::video::IVideoDriver *driver,
	BomberManConfig &config)
	: AMenu(device, driver, config), _receiver(_device, *this)
{
	#ifdef __unix__
		_config.insertMusic("pause", "AssetsIndie/Common/Sounds/Pause.wav");
		_config.insertSound(SoundType::GAME, "move", "AssetsIndie/Common/Sounds/Move.wav");
		_config.insertSound(SoundType::GAME, "pickupbonus", "AssetsIndie/Common/Sounds/PickUpBonus.wav");
		_config.insertSound(SoundType::GAME, "placebomb", "AssetsIndie/Common/Sounds/PlaceBomb.wav");
		_config.insertSound(SoundType::GAME, "bombexplode", "AssetsIndie/Common/Sounds/Bomb.wav");
		_config.insertSound(SoundType::GAME, "usebonus", "AssetsIndie/Common/Sounds/UseBonus.wav");
	#endif
	updateConfigValue("FPS", _fps, 60);
	if (!(_font = _env->getFont("AssetsIndie/Fonts/malgun25.png")))
		throw ErrorsGameGfx(std::cerr, "can't load malgun font");
}

void GameGfx::updateConfigValue(std::string const &key, int &value, int defaultValue)
{
	if (Utils::strIsNumber(_config.getConf(key))) {
		value = std::stoi(_config.getConf(key));
	} else {
		value = defaultValue;
	}
}

void GameGfx::loadImageT(irr::scene::ISceneNode *n, std::string path)
{
	if (_driver->getTexture(path.c_str()) == NULL)
		throw ErrorsGameGfx(std::cerr, "! loadImage Failed !");
	n->setMaterialTexture(0, _driver->getTexture(path.c_str()));
}

void GameGfx::initGame()
{
	_device->setEventReceiver(&_receiver);
	std::srand(std::time(nullptr));

	int size = (std::rand() % 3) + 1;
	enum MapSize mapSize = SMALL;
	try {
		this->_bombRange = std::stoul(_config.getConf("BombRange"));
	} catch (...) {
		this->_bombRange = 3;
	}
	if (size == 1) {
		mapSize = SMALL;
	} else if (size == 2) {
		mapSize = MEDIUM;
	} else {
		mapSize = LARGE;
	}
	_world = std::make_unique<World>(mapSize, _config);
	_mapSize = _world->getMapSize();

	_theme = std::to_string((std::rand() % 3) + 1);
	#ifdef __unix__
		loadSound();
	#endif
	initPlayers();
	_device->getCursorControl()->setVisible(false);
	_receiver.refresh();
	_buttonStatus = ButtonGameGfx::BUTTON_NOTHING_GAMEGFX;
}

std::vector<irr::EKEY_CODE> GameGfx::giveControls(size_t who)
{
	std::vector<irr::EKEY_CODE> controls;
	switch (who) {
	case 0:
		controls.push_back(irr::KEY_KEY_A);
		controls.push_back(irr::KEY_KEY_Z);
		controls.push_back(irr::KEY_KEY_Q);
		controls.push_back(irr::KEY_KEY_S);
		controls.push_back(irr::KEY_KEY_D);
		break;
	case 1:
		controls.push_back(irr::KEY_RSHIFT);
		controls.push_back(irr::KEY_UP);
		controls.push_back(irr::KEY_DOWN);
		controls.push_back(irr::KEY_LEFT);
		controls.push_back(irr::KEY_RIGHT);
		break;
	case 2:
		controls.push_back(irr::KEY_KEY_T);
		controls.push_back(irr::KEY_KEY_Y);
		controls.push_back(irr::KEY_KEY_G);
		controls.push_back(irr::KEY_KEY_H);
		controls.push_back(irr::KEY_KEY_J);
		break;
	case 3:
		controls.push_back(irr::KEY_KEY_I);
		controls.push_back(irr::KEY_KEY_O);
		controls.push_back(irr::KEY_KEY_K);
		controls.push_back(irr::KEY_KEY_L);
		controls.push_back(irr::KEY_KEY_M);
		break;
	default:
		throw ErrorsGameGfx(std::cerr, "! giveControls Failed !");
	}
	return controls;
}

void GameGfx::initPlayers()
{
	size_t place = 0;
	int nbPlayer = 0;
	int id;
	irr::core::vector2df pos;
	irr::core::vector3df rotation;

	for (auto character : _config._users) {
		if (place == 0) {
			pos = irr::core::vector2df(0 + 0.5, 0 + 0.5);
			rotation = irr::core::vector3df(0, 0, 0);
			id = 0;
		} else if (place == 1) {
			pos = irr::core::vector2df(_mapSize - 1 + 0.5, 0 + 0.5);
			rotation = irr::core::vector3df(0, 0, 0);
			id = 1;
		} else if (place == 2) {
			pos = irr::core::vector2df(0 + 0.5, _mapSize - 1);
			rotation = irr::core::vector3df(0, 180, 0);
			id = 2;
		} else {
			pos = irr::core::vector2df(_mapSize - 1 + 0.5, _mapSize - 1);
			rotation = irr::core::vector3df(0, 180, 0);
			id = 3;
		}
		if (character.type == HUMAN) {
			nbPlayer++;
			_players.push_back(std::make_unique<Human>(character.userName, id, pos,
									character.character, giveControls(place),
									_receiver, rotation));
		} else {
			_players.push_back(std::make_unique<Ai>(character.userName, id, pos, character.character, rotation, _world, _players));
		}
		place++;
	}
	if (nbPlayer > 1)
		_solo = false;
	else
		_solo = true;
	_cameraSolo = false;
}

SceneStatus GameGfx::launchButton()
{
	SceneStatus status = SceneStatus::NOTHING;

	clearScreen();
	switch (_buttonStatus) {
	default:
		break;
	}
	return status;
}

void GameGfx::clearPlayers()
{
	for (auto &player : _players) {
		player->die();
	}
	_players.clear();
}

bool GameGfx::endGame()
{
	int nbAlive = 0;
	int nbHuman = 0;

	for (auto &player : _players) {
		if (player->getAlive())
			nbAlive++;
		if (player->getPlayerType() == HUMAN)
			nbHuman++;
	}
	if (nbAlive <= 1 || nbHuman == 0) {
		return true;
	} else {
		return false;
	}
}

void GameGfx::playersMove()
{
	for (auto player = _players.begin(); player != _players.end(); ++player) {
		auto res = _world->updatePlayerData((*player), (*player)->play(), _scene, _driver);
		updatePlayerAnimation(res, (*player));
	}
}

void GameGfx::updatePlayerAnimation(enum Action res, std::unique_ptr<APlayer> &player)
{
	switch (player->getStatus()) {
	case IDLE:
		if (res == MOVE_UP || res == MOVE_DOWN ||
			res == MOVE_LEFT || res == MOVE_RIGHT) {
			player->getNodeA().remove();
			player->placeEntity(_scene, _driver, RUN);
			player->setStatus(RUN);
			updatePlayerRotation(res, player);
		}
		break;
	case RUN:
		if (res == NO) {
			player->getNodeA().remove();
			player->placeEntity(_scene, _driver, IDLE);
			player->setStatus(IDLE);
		} else if (res == MOVE_UP || res == MOVE_DOWN ||
			res == MOVE_LEFT || res == MOVE_RIGHT) {
			auto posi = player->getPos();
			player->getNodeA().setPosition(irr::core::vector3df(posi.X, 100, -posi.Y));
			updatePlayerRotation(res, player);
			break;
		}
	}
}

void GameGfx::updatePlayerRotation(enum Action res, std::unique_ptr<APlayer> &player)
{
	switch (res) {
	case MOVE_UP:
		player->getRotation().Y = 180;
		player->getNodeA().setRotation(player->getRotation());
		break;
	case MOVE_DOWN:
		player->getRotation().Y = 0;
		player->getNodeA().setRotation(player->getRotation());
		break;
	case MOVE_LEFT:
		player->getRotation().Y = 90;
		player->getNodeA().setRotation(player->getRotation());
		break;
	case MOVE_RIGHT:
		player->getRotation().Y = 270;
		player->getNodeA().setRotation(player->getRotation());
		break;
	}
}

void GameGfx::displayBlock()
{

	for (auto x = _world->getMap().begin(); x != _world->getMap().end(); ++x) {
		for (auto y = (*x).begin(); y != (*x).end(); ++y) {
			if ((*y) != nullptr)
				(*y)->placeEntity(_scene, _driver, _theme);
		}
	}
}

void GameGfx::displayPlayer()
{
	for (auto player = _players.begin(); player != _players.end(); ++player) {
		(*player)->placeEntity(_scene, _driver, IDLE);
	}
}

void GameGfx::displayBonus()
{
	for (auto bonus = _world->getBonus().begin(); bonus != _world->getBonus().end(); ++bonus) {
		(*bonus)->placeEntity(_scene, _driver);
	}
}

#ifdef __unix__
void GameGfx::loadSound()
{
	std::string path = "";

	path = "AssetsIndie/Theme" + _theme + "/Sounds/music.wav";
	_config.insertMusic("music", path);
}
#endif

void GameGfx::setSkybox()
{
	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);
	std::string path = "AssetsIndie/Theme" + _theme + "/Scenery/Other/SkyBox/skydome.jpg";
	irr::scene::ISceneNode *skydome = _scene->addSkyDomeSceneNode(_driver->getTexture(path.c_str()), 50, 35, 1.0f,
		2.0f, 1000.0f);
	if (skydome == NULL)
		throw ErrorsGameGfx(std::cerr, "! setSkybox Failed !");
	_driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
}

void GameGfx::checkPlayerDeath(irr::core::vector2df pos, int id)
{
	auto player = _players.begin();

	while (player != _players.end()) {
		if (static_cast<int>((*player)->getPos().X) == static_cast<int>(pos.X)
			&& static_cast<int>((*player)->getPos().Y) == static_cast<int>(pos.Y)) {
			if ((*player)->getId() == id) {
				if (_world->getScores()[(*player)->getId()] >= 200)
					_world->getScores()[(*player)->getId()] -= 200;
				else
					_world->getScores()[(*player)->getId()] = 0;

			}
			else
				_world->getScores()[id] += 400;
			(*player)->die();
			_players.erase(player);
		} else {
			player++;
		}
	}
}

void GameGfx::checkExplosion()
{
	auto fire = _world->getExplosion().begin();

		while (fire != _world->getExplosion().end()) {
			(*fire)->getTimePlaced()--;
			checkPlayerDeath((*fire)->getPos(), (*fire)->getId());
			if ((*fire)->getTimePlaced() <= 0) {
				(*fire)->getNode().remove();
				_world->getExplosion().erase((fire));
			} else {
				fire++;
			}
	}
}

void GameGfx::checkBombExplosion()
{
	auto bomb = _world->getBomb().begin();

	while (bomb != _world->getBomb().end()) {
		(*bomb)->getTimePlaced()--;
		if ((*bomb)->getTimePlaced() <= 0) {
			#ifdef __unix__
				_config.launchSound(SoundType::GAME, "bombexplode");
			#endif
			_world->updateMap((*bomb), _scene, _driver);
			(*bomb)->getNodeA().remove();
			addBombAvailableAfterExplosion(*bomb);
			_world->getBomb().erase((bomb));
		} else {
			bomb++;
		}
	}
}

void GameGfx::addBombAvailableAfterExplosion(std::unique_ptr<Bomb>& bomb)
{
	for (auto player = _players.begin(); player != _players.end(); ++player) {
		if ((*player)->getId() == bomb->getId()) {
			(*player)->getAvailableBomb()++;
		}
	}
}

void GameGfx::drawBorderW(irr::core::vector3df pos)
{
	int i = 0;
	while (i < _mapSize) {
		irr::scene::ISceneNode *n = _scene->addCubeSceneNode();
		if (n) {
			std::string path = "AssetsIndie/Theme" + _theme + "/Scenery/Wall/wall.jpg";
			loadImageT(n, path);
			n->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			n->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
			n->setPosition(pos);
		}
		pos.X += 1;
		i++;
	}
}

void GameGfx::drawBorderH(irr::core::vector3df pos)
{
	int i = 0;
	while (i < _mapSize + 2) {
		irr::scene::ISceneNode *n = _scene->addCubeSceneNode();
		if (n) {
			std::string path = "AssetsIndie/Theme" + _theme + "/Scenery/Wall/wall.jpg";
			loadImageT(n, path);
			n->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			n->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
			n->setPosition(pos);
		}
		pos.Z -= 1;
		i++;
	}
}

void GameGfx::drawHigh()
{
	irr::core::vector3df pos = irr::core::vector3df((_mapSize / 2) + 0.5, 94, (-_mapSize / 2) - 0.5);

	for (size_t i = 0; i < 50; i++) {
		irr::scene::ISceneNode *n = _scene->addCubeSceneNode();
		if (n) {
			std::string path = "AssetsIndie/Theme" + _theme + "/Scenery/Height/height.jpg";
			loadImageT(n, path);
			n->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			n->setPosition(pos);
			n->setScale(irr::core::vector3df(_mapSize * 0.1, 1, _mapSize * 0.1));
		}
		pos.Y -= 10;
	}
}

void GameGfx::drawEnv()
{
	irr::core::vector3df pos = irr::core::vector3df((_mapSize / 2) + 0.5, 99.5, (-_mapSize / 2) - 0.5);
	irr::scene::ISceneNode *n = _scene->addCubeSceneNode();
	if (n) {
		std::string path = "AssetsIndie/Theme" + _theme + "/Scenery/Ground/ground.jpg";
		loadImageT(n, path);
		n->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		n->setScale(irr::core::vector3df(_mapSize * 0.1, 0.1, _mapSize * 0.1));
		n->setPosition(pos);
	}
	drawBorderW(irr::core::vector3df(0+0.5, 100.5, 1-0.5));
	drawBorderW(irr::core::vector3df(0+0.5, 100.5, -_mapSize-0.5));
	drawBorderH(irr::core::vector3df(_mapSize+0.5, 100.5, 1-0.5));
	drawBorderH(irr::core::vector3df(-1+0.5, 100.5, 1-0.5));
	setSkybox();
	drawHigh();
	displayBlock();
	displayBonus();
	displayPlayer();
}

void GameGfx::changeCamera()
{
	if (_receiver.IsKeyDown(irr::KEY_F1)) {
		_cameraSolo = false;
		_scene->addCameraSceneNode(NULL, irr::core::vector3df(_mapSize / 2, 100 + _mapSize, -_mapSize + -3),
			irr::core::vector3df(_mapSize / 2, 60, -_mapSize / 2 + 15));
	} else if (_receiver.IsKeyDown(irr::KEY_F2)) {
		_cameraSolo = false;
		_scene->addCameraSceneNode(NULL, irr::core::vector3df(_mapSize / 2, 100 + _mapSize, -_mapSize + -10),
			irr::core::vector3df(_mapSize / 2, 70, 40));
	} else if (_receiver.IsKeyDown(irr::KEY_F3) && _solo ) {
		_cameraSolo = true;
	}
}

void GameGfx::initEndMessage(irr::core::stringw str, irr::core::rect<irr::s32> rect)
{
	irr::gui::IGUIEditBox * inputBox;
	irr::gui::IGUIFont *font;
	irr::core::dimension2d<irr::u32> size;
	std::string path("AssetsIndie/Fonts/bauhaus.png");

	if (!(font = _env->getFont(path.c_str())))
		throw ErrorsGameGfx(std::cerr, "Could not load " + path);
	inputBox = _env->addEditBox(str.c_str(), rect, false);
	inputBox->setOverrideFont(font);
	inputBox->setOverrideColor(irr::video::SColor(255, 179, 0, 0));
	inputBox->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	inputBox->setDrawBackground(false);
	inputBox->setMax(15);
	inputBox->setDrawBorder(0);
}

void GameGfx::printWinner()
{
	int y = 0;
	Timer end(50);

	if (_players.size() != 0) {
		irr::core::stringw name = _players.front()->getName().c_str();
		irr::core::stringw bestScore = std::to_string(_world->getScores()[_players.front()->getId()]).c_str();
		initEndMessage(name, irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 3,
			_driver->getScreenSize().Height / 3 - 110,
			_driver->getScreenSize().Width / 2 + 400,
			_driver->getScreenSize().Height / 2 + 110));
		initEndMessage(bestScore, irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 3,
			_driver->getScreenSize().Height / 3 + 25,
			_driver->getScreenSize().Width / 2 + 400,
			_driver->getScreenSize().Height / 2 + 125));
		initEndMessage("Game Over", irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 3,
			_driver->getScreenSize().Height / 3 + 100,
			_driver->getScreenSize().Width / 2 + 400,
			_driver->getScreenSize().Height / 2 + 200));
		while (y != 101 && _device->isWindowActive()) {
			if (end.canUpdate()) {
				_driver->beginScene(true, true, 0);
				_scene->drawAll();
				_env->drawAll();
				_driver->endScene();
				y++;
			}
		}
		_env->clear();
		clearPlayers();
	}
}

void GameGfx::introGame()
{
	int y = 0;
	Timer intro(30);

	initIntroMessage("Get Ready ...");
	while (y != 101 && _device->isWindowActive()) {
		if (intro.canUpdate()) {
			_scene->addCameraSceneNode(NULL,
				irr::core::vector3df(_mapSize / 2, y + _mapSize, -_mapSize + -3),
				irr::core::vector3df(_mapSize / 2, 60, -_mapSize / 2 + 15));
			_driver->beginScene(true, true, 0);
			_scene->drawAll();
			_env->drawAll();
			_driver->endScene();
			y++;
		}
	}
	_env->clear();
	fightMessagePrint();
}

void GameGfx::fightMessagePrint()
{
	int y = 0;
	Timer intro(30);

	initIntroMessage("Fight !");
	while (y != 3 && _device->isWindowActive()) {
		if (intro.canUpdate()) {
			_driver->beginScene(true, true, 0);
			_scene->drawAll();
			_env->drawAll();
			_driver->endScene();
			y++;
		}
	}
	_env->clear();
}

void GameGfx::printPlayerImage(std::unique_ptr<APlayer>& player, irr::core::position2d<int> pos)
{
	_env->addImage(_textures[player->getCharacterName().c_str()], pos);
}

void GameGfx::initTextures()
{
	loadImage("Gign", "AssetsIndie/Character/Gign/GignHead.png");
	loadImage("Guerilla", "AssetsIndie/Character/Guerilla/GuerillaHead.png");
	loadImage("Phoenix", "AssetsIndie/Character/Phoenix/PhoenixHead.png");
	loadImage("Sas", "AssetsIndie/Character/Sas/SasHead.png");
}

void GameGfx::drawGui()
{
	initTextures();
	int width = 20;
	int height = _driver->getScreenSize().Height / 6;
	for (auto player = _players.begin(); player != _players.end(); ++player) {
		printPlayerImage((*player), irr::core::position2d<int>(width, height));
		height += 180;
	}
}

void GameGfx::loadImage(std::string name, std::string path)
{
	if (!(_textures[name] = _driver->getTexture(path.c_str())))
		throw ErrorsGameGfx(std::cerr, "Could not load " + path);
}

void GameGfx::initIntroMessage(irr::core::stringw str)
{
	irr::gui::IGUIFont *font;
	irr::core::dimension2d<irr::u32> size;
	std::string path("AssetsIndie/Fonts/bauhaus.png");

	if (!(font = _env->getFont(path.c_str())))
		throw ErrorsGameGfx(std::cerr, "Could not load " + path);
	_inputBox = _env->addEditBox(str.c_str(),
		irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 3,
			_driver->getScreenSize().Height / 3,
			_driver->getScreenSize().Width / 2 + 400,
			_driver->getScreenSize().Height / 2 + 200),
		false);
	_inputBox->setOverrideFont(font);
	_inputBox->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	_inputBox->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
	_inputBox->setDrawBackground(false);
	_inputBox->setMax(15);
	_inputBox->setDrawBorder(0);
}

SceneStatus GameGfx::pauseScreen()
{
	SceneStatus status = NOTHING;

	initIntroMessage("PAUSE");
	_receiver.refresh();
	while (_device->run() && _driver && _device->isWindowActive() && status == NOTHING) {
		if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			status = SceneStatus::CHOOSE_GAME;
			clearPlayers();
		}
		else if (_receiver.IsKeyDown(irr::KEY_SPACE))
			status = SceneStatus::GFX_GAME;
		_driver->beginScene(true, true, 0);
		_scene->drawAll();
		_env->drawAll();
		_driver->endScene();
	}
	_inputBox->remove();
	return status;
}

void GameGfx::drawNamePlayer()
{
	int y = _driver->getScreenSize().Height / 6 + 50;

	for (auto player = _players.begin(); player != _players.end(); ++player) {
		irr::core::stringw str = (*player)->getName().c_str();
		_font->draw(str.c_str(), irr::core::rect<irr::s32>(_driver->getScreenSize().Width / 2 - 750,
								   y,
								   _driver->getScreenSize().Width / 2 - 650,
								   y),
		irr::video::SColor(255, 255, 0, 0));
		y += _driver->getScreenSize().Height / 6;
	}
}

SceneStatus GameGfx::launch()
{
	Timer timer(100);
	Timer timerExplo(200);
	SceneStatus status = SceneStatus::GFX_GAME;
	initGame();
	#ifdef __unix__
		_config.launchMusic("music");
	#endif
	drawEnv();
	Clock clock(_fps);
	introGame();
	drawGui();
	while (_device->run() && _driver && status == SceneStatus::GFX_GAME) {
		if (endGame()) {
			printWinner();
			status = SceneStatus::CHOOSE_GAME;
		} else if (_buttonStatus != ButtonGameGfx::BUTTON_NOTHING_GAMEGFX) {
			status = launchButton();
		} else if (_receiver.IsKeyDown(irr::KEY_ESCAPE)) {
			#ifdef __unix__
				_config.launchMusic("pause");
			#endif
			status = pauseScreen();
			if (status == SceneStatus::GFX_GAME) {
				#ifdef __unix__
					_config.launchMusic("music");
				#endif
			} else {
				#ifdef __unix__
					_config.launchMusic("Theme");
				#endif
			}
		} else if (_device->isWindowActive() && clock.canUpdate()) {
			playersMove();
			if (timer.canUpdate())
				checkBombExplosion();
			if (timerExplo.canUpdate())
				checkExplosion();
			_driver->beginScene(true, true, 0);
			_scene->drawAll();
			drawNamePlayer();
			_env->drawAll();
			_driver->endScene();
		}
	}
	clearScreen();
	_device->getCursorControl()->setVisible(true);
	if (!_device->run())
		status = SceneStatus::QUIT;
	return status;
}
