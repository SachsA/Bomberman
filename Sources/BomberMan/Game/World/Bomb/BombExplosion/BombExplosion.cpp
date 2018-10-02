//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// BombExplosion.cpp
//

#include "BombExplosion.hpp"

BombExplosion::BombExplosion(irr::core::vector2df pos, int id,
	irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
	:	_timePlaced(2), _pos(pos), _id(id)
{
	placeEntity(smgr, driver, pos);
}

void BombExplosion::placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, irr::core::vector2df pos)
{
	_node = smgr->addCubeSceneNode();
	if (_node)
	{
		std::string path = "AssetsIndie/Common/Bomb/fire.jpg";
		loadImage(path, driver);
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setScale(irr::core::vector3df(0.1,0.1,0.1));
		_node->setPosition(irr::core::vector3df(static_cast<int>(pos.X)+0.5, 100, static_cast<int>(-pos.Y)-0.5));
	} else {
		throw ErrorsBombExplosion(std::cerr, "! placeEntity Failed !");
	}
}

irr::scene::ISceneNode& BombExplosion::getNode()
{
	return *_node;
}

size_t& BombExplosion::getTimePlaced()
{
	return _timePlaced;
}

irr::core::vector2df& BombExplosion::getPos()
{
	return _pos;
}

int& BombExplosion::getId()
{
	return _id;
}

void BombExplosion::loadImage(std::string path, irr::video::IVideoDriver* driver)
{
	if (driver->getTexture(path.c_str()) == NULL)
		throw ErrorsBombExplosion(std::cerr, "! loadImage Failed !");
	_node->setMaterialTexture(0, driver->getTexture(path.c_str()));
}
