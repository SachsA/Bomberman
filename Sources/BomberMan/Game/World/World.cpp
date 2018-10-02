//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// World class implementation
//

#include <memory>
#include <vector>
#include <ctime>
#include "World.hpp"
#include "ABonus.hpp"
#include "BombUp.hpp"
#include "PowerUp.hpp"
#include "SpeedUp.hpp"
#include "BomberManConfig.hpp"

World::World(enum MapSize mapSize, BomberManConfig &config)
	: _config(config)
{
	this->_map = std::make_unique<Map>(mapSize, config);

	try {
		auto range = std::stoi(_config.getConf("BombRange"));
		if (range <= 1) {
			this->_bombRange = 2;
		} else {
			this->_bombRange = range;
		}
	} catch (...) {
		this->_bombRange = 2;
	}
	generateBonus();
}

void World::placeBomb(irr::core::vector2df pos,
	size_t nbrBombUp, int id,
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver
)
{
	size_t bombRange = this->_bombRange + nbrBombUp;
	#ifdef __unix__
	this->_config.launchSound(SoundType::GAME, "placebomb");
	#endif
	pos.X = (int)pos.X + 0.5;
	pos.Y = (int)pos.Y + 0.5;
	_bombs.push_back(std::make_unique<Bomb>(bombRange, pos, id, smgr, driver));
}

size_t &World::getMapSize()
{
	return _map->getSize();
}

bool World::posHasBonus(irr::core::vector2df pos)
{
	int posX = pos.X;
	int posY = pos.Y;

	for (auto &bonus : this->_bonus) {
		auto bonusPos = bonus->getPos();
		if (posX == bonusPos.X && posY == bonusPos.Y)
			return true;
	}
	return false;
}

void World::updatePlayerStat(std::unique_ptr<ABonus> &bonus,
	std::unique_ptr<APlayer> &player
)
{
	switch (bonus->getType()) {
	case POWERUP:
		player->getAvailableBomb()++;
		_map->getScores()[player->getId()] += 10;
		#ifdef __unix__
		this->_config.launchSound(SoundType::GAME, "pickupbonus");
		#endif
		break;
	case SPEEDUP:
		player->getNbSpeedUp()++;
		_map->getScores()[player->getId()] += 10;
		#ifdef __unix__
		this->_config.launchSound(SoundType::GAME, "pickupbonus");
		#endif
		break;
	case BOMBUP:
		player->getNbBombUp()++;
		_map->getScores()[player->getId()] += 30;
		#ifdef __unix__
		this->_config.launchSound(SoundType::GAME, "pickupbonus");
		#endif
		break;
	default:
		throw ErrorsWorld(std::cerr, "Bonus not registered");
	}
}

void World::removeBonus(irr::core::vector2df pos)
{
	auto iteBonus = this->_bonus.begin();
	while (iteBonus != this->_bonus.end()) {
		if (static_cast<int>((*iteBonus)->getPos().X) == static_cast<int>(pos.X)
			&& static_cast<int>((*iteBonus)->getPos().Y) == static_cast<int>(pos.Y)) {
			(*iteBonus)->getNodeA().remove();
			this->_bonus.erase(iteBonus);
		} else {
			iteBonus++;
		}
	}
}

void World::getBonus(irr::core::vector2df pos, std::unique_ptr<APlayer> &player)
{
	auto iteBonus = this->_bonus.begin();
	while (iteBonus != this->_bonus.end()) {
		if (static_cast<int>((*iteBonus)->getPos().X) == static_cast<int>(pos.X)
			&& static_cast<int>((*iteBonus)->getPos().Y) == static_cast<int>(pos.Y)) {
			updatePlayerStat(*iteBonus, player);
			removeBonus(pos);
		} else {
			iteBonus++;
		}
	}
}

bool World::isABomb(irr::core::vector2df pos, enum Action action)
{
	bool retVal = false;
	for (auto &bomb : this->_bombs) {
		auto bombPos = bomb->getPos();
		switch (action) {
		case MOVE_UP:
			if ((int)(pos.Y - 0.5) == static_cast<int>(bombPos.Y) &&
				(int)pos.X == static_cast<int>(bombPos.X)) {
				retVal = true;
			}
			break;
		case MOVE_DOWN:
			if ((int)(pos.Y + 0.5) == static_cast<int>(bombPos.Y) &&
				(int)pos.X == static_cast<int>(bombPos.X)) {
				retVal = true;
			}
			break;
		case MOVE_LEFT:
			if ((int)pos.Y == static_cast<int>(bombPos.Y) &&
				(int)(pos.X - 0.5) == static_cast<int>(bombPos.X)) {
				retVal = true;
			}
			break;
		case MOVE_RIGHT:
			if ((int)(pos.Y) == static_cast<int>(bombPos.Y) &&
				(int)(pos.X + 0.5) == static_cast<int>(bombPos.X)) {
				retVal = true;
			}
			break;
		default:
			retVal = false;
		}
	}
	return retVal;
}

enum Action World::updatePlayerData(std::unique_ptr<APlayer> &player,
	enum Action action,
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver
)
{
	auto pos = player->getPos();
	switch (action) {
	case MOVE_UP:
		pos.Y -= 0.05 + (0.04 * player->getNbSpeedUp());
		if (pos.Y > 0.3 &&
			!_map->isABlock(irr::core::vector2di(pos.X, pos.Y - 0.5)) &&
			!isABomb(irr::core::vector2df(pos.X, pos.Y - 0.5), action))
			checkNewPos(player, pos);
		break;
	case MOVE_DOWN:
		pos.Y += 0.05 + (0.04 * player->getNbSpeedUp());
		if (pos.Y + 0.5 < _map->getMap().size() &&
			!_map->isABlock(irr::core::vector2di(pos.X, pos.Y + 0.5)) &&
			!isABomb(irr::core::vector2df(pos.X, pos.Y), action))
			checkNewPos(player, pos);
		break;
	case MOVE_LEFT:
		pos.X -= 0.05 + (0.04 * player->getNbSpeedUp());
		if (pos.X > 0.3 &&
			!_map->isABlock(irr::core::vector2di(pos.X - 0.5, pos.Y)) &&
			!isABomb(irr::core::vector2df(pos.X, pos.Y - 0.5), action))
			checkNewPos(player, pos);
		break;
	case MOVE_RIGHT:
		pos.X += 0.05 + (0.04 * player->getNbSpeedUp());
		if (pos.X < _map->getMap()[pos.Y].size() &&
			!_map->isABlock(irr::core::vector2di(pos.X + 0.5, pos.Y)) &&
			!isABomb(irr::core::vector2df(pos.X, pos.Y - 0.5), action))
			checkNewPos(player, pos);
		break;
	case PLACE_BOMB:
		if (enoughBomb(player) && noBombThere(player->getPos())) {
			player->getAvailableBomb()--;
			placeBomb(player->getPos(), player->getNbBombUp(), player->getId(), smgr, driver);
		}
		break;
	default:
		return NO;
	}
	return action;
}

void World::checkNewPos(std::unique_ptr<APlayer> &player, irr::core::vector2df pos)
{
	player->setPos(pos);
	if (posHasBonus(pos) == true) {
		getBonus(pos, player);
		removeBonus(pos);
	}
}

bool World::noBombThere(irr::core::vector2df pos)
{
	for (auto bomb = _bombs.begin(); bomb != _bombs.end(); ++bomb) {
		if (static_cast<int>((*bomb)->getPos().X) == static_cast<int>(pos.X)
			&& static_cast<int>((*bomb)->getPos().Y) == static_cast<int>(pos.Y)) {
			return false;
		}
	}
	return true;
}

bool World::enoughBomb(std::unique_ptr<APlayer> &player)
{
	if (player->getAvailableBomb() <= 0) {

		return false;
	}
	return true;
}

void World::updateMap(std::unique_ptr<Bomb> &bomb,
	irr::scene::ISceneManager *smgr,
	irr::video::IVideoDriver *driver
)
{
	_map->updateMap(bomb, smgr, driver);
}

std::vector<std::unique_ptr<BombExplosion>> &World::getExplosion()
{
	return _map->getExplosion();
}

void World::generateBonus()
{
	size_t nbrBox = this->_map->getNbrBox();
	int nbrPowerUp = (nbrBox * 10) / 100;
	int nbrUlti = (nbrPowerUp * 25) / 100;
	int nbrBonus = nbrPowerUp - nbrUlti;
	int nbrSpeedUp = nbrBonus / 2;
	int nbrBombUp = nbrBonus / 2;
	generateBonus(nbrUlti, POWERUP);
	generateBonus(nbrSpeedUp, SPEEDUP);
	generateBonus(nbrBombUp, BOMBUP);
}

void World::generateBonus(int nbrBonus, enum BonusType type)
{
	std::srand(std::time(nullptr));
	if (nbrBonus <= 0)
		return;
	while (nbrBonus > 0) {
		for (size_t posY = 0; posY < this->_map->getSize(); posY++) {
			for (size_t posX = 0; posX < this->_map->getSize(); posX++) {
				if (_map->getMap()[posY][posX] != nullptr && std::rand() % 10 == 0 &&
					_map->getMap()[posY][posX]->getBlockType() == BOX &&
					caseHasBonus(posX, posY) == false) {
					addBonus(posX, posY, type);
					nbrBonus--;
				}
			}
		}
	}
}

bool World::caseHasBonus(size_t posX, size_t posY)
{
	for (auto &bonus : this->_bonus) {
		auto pos = bonus->getPos();
		if (pos.X == posX && pos.Y == posY) {
			return true;
		}
	}
	return false;
}

void World::addBonus(size_t posX, size_t posY, enum BonusType type)
{
	switch (type) {
	case SPEEDUP:
		this->_bonus.push_back(std::make_unique<SpeedUp>(irr::core::vector2df(posX, posY)));
		break;
	case BOMBUP:
		this->_bonus.push_back(std::make_unique<BombUp>(irr::core::vector2df(posX, posY)));
		break;
	case POWERUP:
		this->_bonus.push_back(std::make_unique<PowerUp>(irr::core::vector2df(posX, posY)));
		break;
	default:
		throw ErrorsWorld(std::cerr, "Not a bonus");
	};
}

std::vector<std::unique_ptr<Bomb>> &World::getBomb()
{
	return _bombs;
}

std::vector<std::unique_ptr<ABonus>> &World::getBonus()
{
	return _bonus;
}

std::vector<std::vector<std::unique_ptr<ABlock>>> &World::getMap()
{
	return _map->getMap();
}

std::unordered_map<int, size_t> &World::getScores()
{
	return _map->getScores();
}
