//
// EPITECH PROJECT, 2018
// indie-dev-client
// File description:
// Wall.cpp
//

#include <iostream>
#include "ABlock.hpp"
#include "Wall.hpp"

Wall::Wall(irr::core::vector2df pos)
	:	ABlock(-1, pos, WALL)
{}

void Wall::takeDamage(float damage)
{
	damage = 0;
	_health -= damage;
}

void Wall::placeEntity(irr::scene::ISceneManager* smgr,
			irr::video::IVideoDriver* driver,
			std::string theme)
{
	_node = smgr->addCubeSceneNode();
	if (_node)
	{
		std::string path = "AssetsIndie/Theme" + theme + "/Scenery/Wall/wall.jpg";
		loadImage(path, driver);
		_node->setMaterialTexture(0, driver->getTexture(path.c_str()));
		_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		_node->setScale(irr::core::vector3df(0.1,0.1,0.1));
		_node->setPosition(irr::core::vector3df(_pos.X+0.5, 100.5, -_pos.Y-0.5));
	} else {
		throw ErrorsWall(std::cerr, "! placeEntity Failed !");
	}
}
