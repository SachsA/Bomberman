
//
// EPITECH PROJECT, 2018
// cpp_indie
// File description:
// Map handling class implementation
//

#include <cstdlib>
#include <ctime>
#include <irrlicht.h>
#include <iostream>
#include <vector>
#include <memory>
#include <vector2d.h>
#include "ABlock.hpp"
#include "BomberManConfig.hpp"
#include "Wall.hpp"
#include "Map.hpp"
#include "Box.hpp"
#include "Bomb.hpp"

Map::Map(enum MapSize mapSize, BomberManConfig &confParsing)
	: _mapSize(mapSize), _conf(confParsing)
{
	initData();
}

void Map::initData()
{
	int width = 0;

	switch (_mapSize) {
	case SMALL:
		try {
			auto size = stoi(_conf.getConf("MapSizeSmall"));
			if (size <= 10 || size % 2 == 0)
				this->_width = 11;
			else
				this->_width = size;
		} catch (...) {
			this->_width = 15;
		};
		break;
	case MEDIUM:
		try {
			auto size = stoi(_conf.getConf("MapSizeMedium"));
			if (size <= 10 || size % 2 == 0)
				this->_width = 15;
			else
				this->_width = size;
		} catch (...) {
			this->_width = 15;
		};
		break;
	case LARGE:
		try {
			auto size = stoi(_conf.getConf("MapSizeBig"));
			if (size <= 10 || size % 2 == 0)
				this->_width = 21;
			else
				this->_width = size;
		} catch (...) {
			this->_width = 15;
		};
		break;
	default:
		throw ErrorsMap(std::cerr, "Map size not register");
	}
	this->_height = this->_width;
	resizeMap();
	initPlayerPos();
	initMap();
	initScores();
}

void Map::initScores()
{
	int i = 0;

	while (i != 3) {
		_scores[i] = 0;
		i++;
	}
}

void Map::initPlayerPos()
{
	_player1Pos.X = 0;
	_player1Pos.Y = 0;
	_player2Pos.X = this->_width - 1;
	_player2Pos.Y = 0;
	_player3Pos.X = 0;
	_player3Pos.Y = this->_width - 1;
	_player4Pos.X = this->_width - 1;
	_player4Pos.Y = this->_width - 1;
}

std::vector<std::vector<std::unique_ptr<ABlock>>> &Map::getMap()
{
	return this->_map;
}

void Map::resizeMap()
{
	this->_map.resize(this->_width);
	for (auto &x : this->_map) {
		x.resize(this->_height);
	}
}

void Map::initMap()
{
	std::vector<std::vector<int>> map(this->_width, std::vector<int>(this->_height));
	size_t x = 0;
	size_t y = 0;
	for (y = 0; y < this->_height; y++) {
		for (x = 0; x < this->_width; x++) {
			if (y == 0 || y == this->_height - 1 || y % 2 == 0) {
				map[y][x] = 0;
			} else {
				if (x == 0 || x == this->_width - 1 || x % 2 == 0) {
					map[y][x] = 0;
				} else {
					map[y][x] = 1;
				}
			}
		}
	}
	placeWall(map);
	placeDestructiveBlock();
}

void Map::placeWall(std::vector<std::vector<int>> map)
{
	size_t x = 0;
	size_t y = 0;
	Wall *block;
	std::srand(std::time(nullptr));

		for (y = 0; y < this->_height; y++) {
			for (x = 0; x < this->_width; x++) {
				if (map[x][y] == 1) {
					this->_map[y][x] = std::make_unique<Wall>(irr::core::vector2df(x, y));
					this->_nbrWall++;
				} else {
					this->_map[y][x] = nullptr;
				}
			}
		}
}

bool Map::isFreeSpot(size_t posX, size_t posY)
{
	if (isInSpawn(posX, posY) == false) {
		return true;
	}
	return false;
}

bool Map::isPlayerPos(int posX, int posY)
{
	if ((posX == _player1Pos.X && posY == _player1Pos.Y) ||
		(posX == _player2Pos.X && posY == _player2Pos.Y) ||
		(posX == _player3Pos.X && posY == _player3Pos.Y) ||
		(posX == _player4Pos.X && posY == _player4Pos.Y)) {
		return true;
	}
	return false;
}

bool Map::isInPlayerSpawn(enum Player player, int posX, int posY)
{
	switch (player) {
	case PLAYER1:
		if ((posX == _player1Pos.X + 1 && posY == _player1Pos.Y) ||
			(posX == _player1Pos.X && posY == _player1Pos.Y + 1) ||
			(posX == _player1Pos.X && posY == _player1Pos.Y))
			return true;
		break;
	case PLAYER2:
		if ((posX == _player2Pos.X - 1 && posY == _player2Pos.Y) ||
			(posX == _player2Pos.X && posY == _player2Pos.Y + 1) ||
			(posX == _player2Pos.X && posY == _player2Pos.Y))
			return true;
		break;
	case PLAYER3:
		if ((posX == _player3Pos.X && posY == _player3Pos.Y - 1) ||
			(posX == _player3Pos.X + 1 && posY == _player3Pos.Y) ||
			(posX == _player3Pos.X && posY == _player3Pos.Y))
			return true;
		break;
	case PLAYER4:
		if ((posX == _player4Pos.X && posY == _player4Pos.Y - 1) ||
			(posX == _player4Pos.X - 1 && posY == _player4Pos.Y) ||
			(posX == _player4Pos.X && posY == _player4Pos.Y))
			return true;
		break;
	default:
		return false;
	}
	return false;
}

bool Map::isInSpawn(int posX, int posY)
{
	if (isInPlayerSpawn(PLAYER1, posX, posY) == true ||
		isInPlayerSpawn(PLAYER2, posX, posY) == true ||
		isInPlayerSpawn(PLAYER3, posX, posY) == true ||
		isInPlayerSpawn(PLAYER4, posX, posY) == true)
		return true;
	return false;
}

void Map::placeDestructiveBlock()
{
	std::srand(std::time(nullptr));
	size_t posX = 0;
	size_t posY = 0;
	Box *box;
	int nbrBox = ((this->_width * this->_width) / 4) * 2;
	this->_nbrBox = nbrBox;
	do {
		posX = 0;
		posY = 0;
		for (posY = 0; posY < this->_width; posY++) {
			for (posX = 0; posX < this->_width; posX++) {
				if (this->_map[posY][posX] == nullptr &&
					isInSpawn(posX, posY) == false) {
					if (std::rand() % 2 == 0) {
						this->_map[posY][posX] = std::make_unique<Box>(
							irr::core::vector2df(posX, posY));
						nbrBox--;
					}
				}
			}
		}
	} while (nbrBox > 0);
}

void Map::updateMap(std::unique_ptr<Bomb> &bomb,
		    irr::scene::ISceneManager* smgr,
		    irr::video::IVideoDriver* driver)
{
	size_t range = bomb->getRange();
	updateUp(range, bomb->getPos(), bomb->getId(), smgr, driver);
	updateDown(range, bomb->getPos(), bomb->getId(),smgr, driver);
	updateLeft(range, bomb->getPos(), bomb->getId(),smgr, driver);
	updateRight(range, bomb->getPos(), bomb->getId(),smgr, driver);
}

void Map::updateUp(size_t range, irr::core::vector2df bombPos, int id,
		   irr::scene::ISceneManager* smgr,
		   irr::video::IVideoDriver* driver)
{
	int endY = bombPos.Y - range;
	int posY = bombPos.Y;

	while (posY > endY && posY >= 0) {
		if (this->_map[posY][bombPos.X] == nullptr) {
				_fire.push_back(std::make_unique<BombExplosion>(
					irr::core::vector2df(bombPos.X, posY), id ,smgr, driver));
		} else if (this->_map[posY][bombPos.X]->getBlockType() == BOX) {
			_scores[id] += 40;
			this->_map[posY][bombPos.X]->getNode().remove();
			this->_map[posY][bombPos.X] = nullptr;
			_fire.push_back(std::make_unique<BombExplosion>(
				irr::core::vector2df(bombPos.X, posY), id ,smgr, driver));
			return;
		} else if (this->_map[posY][bombPos.X]->getBlockType() == WALL) {
		 	return;
		}
		posY--;
	}
}

void Map::updateDown(size_t range, irr::core::vector2df bombPos, int id,
		     irr::scene::ISceneManager* smgr,
		     irr::video::IVideoDriver* driver)
{
	int endY = bombPos.Y + range;
	int posY = bombPos.Y;

	while (posY < endY && posY < static_cast<int>(_height)) {
		if (this->_map[posY][bombPos.X] == nullptr) {
				_fire.push_back(std::make_unique<BombExplosion>(
					irr::core::vector2df(bombPos.X, posY), id ,smgr, driver));
		} else if (this->_map[posY][bombPos.X]->getBlockType() == BOX) {
			_scores[id] += 40;
			this->_map[posY][bombPos.X]->getNode().remove();
			this->_map[posY][bombPos.X] = nullptr;
			_fire.push_back(std::make_unique<BombExplosion>(
				irr::core::vector2df(bombPos.X, posY), id ,smgr, driver));
			return;
		} else if (this->_map[posY][bombPos.X]->getBlockType() == WALL) {
			return;
		}
		posY++;
	}
}

void Map::updateLeft(size_t range, irr::core::vector2df bombPos, int id,
		     irr::scene::ISceneManager* smgr,
		     irr::video::IVideoDriver* driver)
{
	int endX = bombPos.X - range;
	int posX = bombPos.X;

	while (posX > endX && posX >= 0) {
		if (this->_map[bombPos.Y][posX] == nullptr) {
				_fire.push_back(std::make_unique<BombExplosion>(
					irr::core::vector2df(posX, bombPos.Y), id ,smgr, driver));
		} else if (this->_map[bombPos.Y][posX]->getBlockType() == BOX) {
			_scores[id] += 40;
			this->_map[bombPos.Y][posX]->getNode().remove();
			this->_map[bombPos.Y][posX] = nullptr;
			_fire.push_back(std::make_unique<BombExplosion>(
				irr::core::vector2df(posX, bombPos.Y), id ,smgr, driver));
			return;
		} else if (this->_map[bombPos.Y][posX]->getBlockType() == WALL) {
			return;
		}
		posX--;
	}
}

void Map::updateRight(size_t range, irr::core::vector2df bombPos, int id,
		      irr::scene::ISceneManager* smgr,
		      irr::video::IVideoDriver* driver)
{
	int endX = bombPos.X + range;
	int posX = bombPos.X;

	while (posX < endX && posX < static_cast<int>(_width)) {
		if (this->_map[bombPos.Y][posX] == nullptr) {
				_fire.push_back(std::make_unique<BombExplosion>(
					irr::core::vector2df(posX, bombPos.Y), id ,smgr, driver));
		} else if (this->_map[bombPos.Y][posX]->getBlockType() == BOX) {
			_scores[id] += 40;
			this->_map[bombPos.Y][posX]->getNode().remove();
			this->_map[bombPos.Y][posX] = nullptr;
			_fire.push_back(std::make_unique<BombExplosion>(
				irr::core::vector2df(posX, bombPos.Y), id ,smgr, driver));
			return;
		} else if (this->_map[bombPos.Y][posX]->getBlockType() == WALL) {
			return;
		}
		posX++;
	}
}

bool Map::isInMap(irr::core::vector2di pos)
{
	return pos.Y >= 0 && pos.X >= 0
		&& pos.Y < static_cast<int>(_map.size())
		&& pos.X < static_cast<int>(_map[pos.Y].size());
}

bool Map::isABlock(irr::core::vector2di pos)
{
	if (this->_map[pos.Y][pos.X] == nullptr)
		return false;
	return true;
}

size_t&	Map::getSize()
{
	return this->_width;
}

size_t Map::getNbrBox()
{
	return this->_nbrBox;
}

std::vector<std::unique_ptr<BombExplosion>>& Map::getExplosion()
{
	return _fire;
}

std::unordered_map<int, size_t>& Map::getScores()
{
	return _scores;
}
