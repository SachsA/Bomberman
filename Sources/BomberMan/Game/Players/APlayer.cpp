/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#include "APlayer.hpp"

APlayer::APlayer(std::string name, int id, PlayerType playerType, irr::core::vector2df pos,
	Character& character, irr::core::vector3df& rotation)
	:	_name(name), _id(id), _playerType(playerType),
		_availableBomb(1), _nbBombUp(0), _nbSpeedUp(0), _pos(pos), _alive(true),
		_character(character), _rotation(rotation), _status(IDLE)
{
}

void APlayer::placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, Status status)
{
	std::string pathObj = "";
	if (status == RUN)
		pathObj = "AssetsIndie/Character/" + _character.name + "/" + _character.name + "Run.MD3";
	else
		pathObj = "AssetsIndie/Character/" + _character.name + "/" + _character.name + "Idle.MD3";
	std::string pathPng("AssetsIndie/Character/" + _character.name + "/" + _character.name + ".png");
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh(pathObj.c_str());
	if (mesh) {
		_nodeA = smgr->addAnimatedMeshSceneNode(mesh);
		if (_nodeA) {
			loadImage(pathPng, driver);
			_nodeA->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_nodeA->setScale(irr::core::vector3df(0.02,0.02,0.02));
			_nodeA->setRotation(_rotation);
			_nodeA->setPosition(irr::core::vector3df(_pos.X, 100, -_pos.Y));
		}
	} else {
		throw ErrorsAPlayer(std::cerr, "! placeEntityIdle Failed !");
	}
}

std::string& APlayer::getCharacterName()
{
	return _character.name;
}

int& APlayer::getId()
{
	return _id;
}

int& APlayer::getAvailableBomb()
{
	return _availableBomb;
}

irr::scene::IAnimatedMeshSceneNode& APlayer::getNodeA()
{
	return *_nodeA;
}

std::string& APlayer::getName()
{
	return _name;
}

PlayerType& APlayer::getPlayerType()
{
	return _playerType;
}

size_t& APlayer::getNbBombUp()
{
	return _nbBombUp;
}

size_t& APlayer::getNbSpeedUp()
{
	return _nbSpeedUp;
}

irr::core::vector2df& APlayer::getPos()
{
	return _pos;
}

void APlayer::setPos(irr::core::vector2df pos)
{
	_pos = pos;
}

enum Status& APlayer::getStatus()
{
	return _status;
}

void APlayer::setStatus(enum Status status)
{
	_status = status;
}

void APlayer::die()
{
	if (_nodeA)
		_nodeA->remove();
}

irr::core::vector3df& APlayer::getRotation()
{
	return _rotation;
}

bool APlayer::getAlive()
{
	return _alive;
}

void APlayer::setAlive(bool alive)
{
	_alive = alive;
}

void APlayer::loadImage(std::string path, irr::video::IVideoDriver* driver)
{
	if (driver->getTexture(path.c_str()) == NULL)
		throw ErrorsAPlayer(std::cerr, "! loadImage Failed !");
	_nodeA->setMaterialTexture(0, driver->getTexture(path.c_str()));
}
