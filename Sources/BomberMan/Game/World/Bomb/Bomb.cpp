//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Bomb.cpp
//

#include <string>
#include "Bomb.hpp"

Bomb::Bomb(size_t range, irr::core::vector2df pos, int id, irr::scene::ISceneManager* smgr,
			 irr::video::IVideoDriver* driver)
	:	_range(range), _pos(pos), _timePlaced(20), _id(id)
{
	placeEntity(smgr, driver);

}

void Bomb::loadImageA(std::string path, irr::video::IVideoDriver* driver)
{
	if (driver->getTexture(path.c_str()) == NULL)
		throw ErrorsBomb(std::cerr, "! loadImage Failed !");
	_nodeA->setMaterialTexture(0, driver->getTexture(path.c_str()));
}

size_t& Bomb::getTimePlaced()
{
	return _timePlaced;
}

irr::scene::IAnimatedMeshSceneNode& Bomb::getNodeA()
{
	return *_nodeA;
}

int& Bomb::getId()
{
	return _id;
}

size_t& Bomb::getRange()
{
	return _range;
}

irr::core::vector2df& Bomb::getPos()
{
	return _pos;
}

void Bomb::placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("AssetsIndie/Common/Bomb/bomb.obj");
	if (mesh) {
		_nodeA = smgr->addAnimatedMeshSceneNode(mesh);
		if (_nodeA) {
			loadImageA("AssetsIndie/Common/Bomb/bomb.png", driver);
			_nodeA->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_nodeA->setScale(irr::core::vector3df(0.5,0.5,0.5));
			_nodeA->setPosition(irr::core::vector3df(_pos.X, 100.5, -_pos.Y));
		}
	} else {
		throw ErrorsBomb(std::cerr, "! placeEntity Failed !");
	}
}
