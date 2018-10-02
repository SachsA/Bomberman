//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// AI.cpp
//

#include <array>
#include <algorithm>
#include "Utils/Utils.hpp"
#include "Ai.hpp"

Ai::Ai(std::string name, int id, irr::core::vector2df pos, Character &character, irr::core::vector3df &rotation,
	std::unique_ptr<World> &world, std::vector<std::unique_ptr<APlayer>> &players
)
	: APlayer(name, id, AI, pos, character, rotation), _status(NO), _world(world), _players(players),
	_deathCirle(false)
{
}

bool Ai::isEnemy(int posX, int posY)
{
	auto enemy = _players.begin();

	while (enemy != _players.end()) {
		if (((int)_pos.Y != (int)(*enemy)->getPos().Y || (int)_pos.X != (int)(*enemy)->getPos().X) &&
			posY == (int)(*enemy)->getPos().Y && posX == (int)(*enemy)->getPos().X)
			return true;
		enemy++;
	}
	return false;
}

int Ai::getNextEnemiesObjective(int posX, int posY, int dist)
{
	std::unordered_map<Action, int> dir;

	dir[MOVE_UP] = findEnemiesDestination(posX, posY - 1, dist + 1);
	dir[MOVE_DOWN] = findEnemiesDestination(posX, posY + 1, dist + 1);
	dir[MOVE_LEFT] = findEnemiesDestination(posX - 1, posY, dist + 1);
	dir[MOVE_RIGHT] = findEnemiesDestination(posX + 1, posY, dist + 1);

	return Utils::getMinMapValue(dir);
}

int Ai::findEnemiesDestination(int posX, int posY, int dist)
{
	if (dist >= 5) {
		return -1;
	} else if (posY >= 0 && posX >= 0 &&
		posY < (int)(_world->getMap().size()) &&
		posX < (int)_world->getMap()[posY].size() &&
		_world->getMap()[posY][posX] == nullptr &&
		!dangerousZone(irr::core::vector2df(posX, posY))) {
		if (isEnemy(posX, posY - 1) || isEnemy(posX, posY + 1) || isEnemy(posX - 1, posY) ||
			isEnemy(posX + 1, posY)) {
			return dist;
		}
		return getNextEnemiesObjective(posX, posY, dist);
	}
	return -1;
}

Action Ai::killEnemies()
{
	std::unordered_map<Action, int> dir;

	dir[MOVE_UP] = findEnemiesDestination(_pos.X, _pos.Y - 1, 0);
	dir[MOVE_DOWN] = findEnemiesDestination(_pos.X, _pos.Y + 1, 0);
	dir[MOVE_LEFT] = findEnemiesDestination(_pos.X - 1, _pos.Y, 0);
	dir[MOVE_RIGHT] = findEnemiesDestination(_pos.X + 1, _pos.Y, 0);

	auto dist = Utils::getMinMapValue(dir);
	auto key = Utils::getMinMapKey(dir);

	if (dist == 0) {
		key = PLACE_BOMB;
	} else if (dist == -1 || dist > 5) {
		key = NO;
	}
	return key;
}

int Ai::isDestructiveBlock(int posX, int posY)
{
	return (posX >= 0 && posY >= 0 &&
		posY < (int)(_world->getMap().size()) &&
		posX < (int)_world->getMap()[posY].size() &&
		_world->getMap()[posY][posX] != nullptr &&
		_world->getMap()[posY][posX]->getBlockType() == BOX);
}

int Ai::getNextBlockObjective(int posX, int posY, int dist)
{
	std::unordered_map<Action, int> dir;

	dir[MOVE_UP] = findBlockDestination(posX, posY - 1, dist + 1);
	dir[MOVE_DOWN] = findBlockDestination(posX, posY + 1, dist + 1);
	dir[MOVE_LEFT] = findBlockDestination(posX - 1, posY, dist + 1);
	dir[MOVE_RIGHT] = findBlockDestination(posX + 1, posY, dist + 1);

	return Utils::getMinMapValue(dir);
}

int Ai::findBlockDestination(int posX, int posY, int dist)
{
	if (dist > 5) {
		return dist;
	} else if (posY >= 0 && posX >= 0 &&
		posY < (int)(_world->getMap().size()) &&
		posX < (int)_world->getMap()[posY].size()) {
		if (dangerousZone(irr::core::vector2df(posX, posY))) {
			return -1;
		} else if (_world->getMap()[posY][posX] != nullptr &&
			_world->getMap()[posY][posX]->getBlockType() != BOX) {
			return -1;
		} else if (_world->getMap()[posY][posX] != nullptr &&
			_world->getMap()[posY][posX]->getBlockType() == BOX) {
			return dist;
		} else if (isDestructiveBlock(posX - 1, posY) ||
			isDestructiveBlock(posX + 1, posY) ||
			isDestructiveBlock(posX, posY - 1) ||
			isDestructiveBlock(posX, posY + 1)) {
			return dist + 1;
		} else {
			return getNextBlockObjective(posX, posY, dist);
		}
	}
	return -1;
}

Action Ai::destroy()
{
	std::unordered_map<Action, int> dir;

	dir[MOVE_UP] = findBlockDestination(_pos.X, _pos.Y - 1, 0);
	dir[MOVE_DOWN] = findBlockDestination(_pos.X, _pos.Y + 1, 0);
	dir[MOVE_LEFT] = findBlockDestination(_pos.X - 1, _pos.Y, 0);
	dir[MOVE_RIGHT] = findBlockDestination(_pos.X + 1, _pos.Y, 0);

	auto dist = Utils::getMinMapValue(dir);
	auto key = Utils::getMinMapKey(dir);

	if (!dist) {
		key = PLACE_BOMB;
	} else if (dist == -1 || dist > 5) {
		key = NO;
	}
	return key;
}

int Ai::getNextSafeObjective(int posX, int posY, int dist)
{
	std::unordered_map<Action, int> dir;

	dir[MOVE_UP] = findSafeDestination(posX, posY - 1, dist + 1);
	dir[MOVE_DOWN] = findSafeDestination(posX, posY + 1, dist + 1);
	dir[MOVE_LEFT] = findSafeDestination(posX - 1, posY, dist + 1);
	dir[MOVE_RIGHT] = findSafeDestination(posX + 1, posY, dist + 1);

	return Utils::getMinMapValue(dir);
}

int Ai::findSafeDestination(int posX, int posY, int dist)
{
	if (dist > 5)
		return dist;
	else if (posY >= 0 && posX >= 0 &&
		posY < (int)(_world->getMap().size()) &&
		posX < (int)_world->getMap()[posY].size()) {

		if (_world->getMap()[posY][posX] != nullptr)
			return -1;
		else if (!dangerousZone(irr::core::vector2df(posX, posY)))
			return dist;
		return getNextSafeObjective(posX, posY, dist);
	}
	return -1;
}

Action Ai::defense()
{
	std::unordered_map<Action, int> dir;

	dir[MOVE_UP] = findSafeDestination(_pos.X, _pos.Y - 1, 1);
	dir[MOVE_DOWN] = findSafeDestination(_pos.X, _pos.Y + 1, 1);
	dir[MOVE_LEFT] = findSafeDestination(_pos.X - 1, _pos.Y, 1);
	dir[MOVE_RIGHT] = findSafeDestination(_pos.X + 1, _pos.Y, 1);

	return Utils::getMinMapKey(dir);
}

bool Ai::isBombDangerous(Bomb &bomb, irr::core::vector2df const &playerPos)
{
	return (((int)bomb.getPos().X == (int)playerPos.X &&
		std::abs((int)bomb.getPos().Y - (int)playerPos.Y) < (int)bomb.getRange() + 1) ||
		((int)bomb.getPos().Y == (int)playerPos.Y &&
			std::abs((int)bomb.getPos().X - (int)playerPos.X) < (int)bomb.getRange() + 1));
}

bool Ai::isFireDangerous(BombExplosion &bomb, irr::core::vector2df const &playerPos)
{
	return (int)bomb.getPos().X == (int)playerPos.X &&
		(int)bomb.getPos().Y == (int)playerPos.Y;
}

bool Ai::dangerousZone(irr::core::vector2df const &playerPos)
{
	auto bomb = _world->getBomb().begin();

	while (bomb != _world->getBomb().end()) {
		if (isBombDangerous(**bomb, playerPos)) {
			_deathCirle = true;
			return true;
		}
		bomb++;
	}

	auto fire = _world->getExplosion().begin();
	while (fire != _world->getExplosion().end()) {
		if (isFireDangerous(**fire, playerPos)) {
			_deathCirle = true;
			return true;
		}
		fire++;
	}

	return false;
}

Action Ai::moveToMiddle()
{
	auto decimalY = (int)(_pos.Y * 100) % 100;
	auto decimalX = (int)(_pos.X * 100) % 100;

	Action status = NO;

	if (decimalY > 60)
		status = MOVE_UP;
	else if (decimalY < 40)
		status = MOVE_DOWN;
	if (decimalX > 60)
		status = MOVE_LEFT;
	else if (decimalX < 40)
		status = MOVE_RIGHT;
	return status;
}

bool Ai::canMoveToPos(int posX, int posY)
{
	return (posY >= 0 && posX >= 0 &&
		posY < (int)(_world->getMap().size()) &&
		posX < (int)_world->getMap()[posY].size() &&
		_world->getMap()[posY][posX] == nullptr &&
		!dangerousZone(irr::core::vector2df(posX, posY)));
}

bool Ai::canMove()
{
	return canMoveToPos(_pos.X, _pos.Y - 1) ||
		canMoveToPos(_pos.X, _pos.Y + 1) ||
		canMoveToPos(_pos.X - 1, _pos.Y) ||
		canMoveToPos(_pos.X + 1, _pos.Y);
}

enum Action Ai::play()
{
	_status = NO;

	if (dangerousZone(_pos)) {
		_status = defense();
	} else if (!canMove() || !_availableBomb) {
		_status = moveToMiddle();
	} else {
		_status = killEnemies();
		if (_status == NO)
			_status = destroy();
	}
	return _status;
}
