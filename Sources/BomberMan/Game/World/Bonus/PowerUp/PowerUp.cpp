//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// PowerUp.cpp
//

#include "PowerUp.hpp"

PowerUp::PowerUp(irr::core::vector2df pos)
	:	ABonus(POWERUP, pos)
{
	_nodeA = nullptr;
}

PowerUp::~PowerUp()
{
}

void PowerUp::placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("AssetsIndie/Common/Bonus/PowerUp/star.obj");
	if (mesh) {
		_nodeA = smgr->addAnimatedMeshSceneNode(mesh);
		if (_nodeA) {
			loadImage("AssetsIndie/Common/Bonus/PowerUp/star.png", driver);
			_nodeA->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_nodeA->setScale(irr::core::vector3df(0.007,0.007,0.007));
			_nodeA->setPosition(irr::core::vector3df(_pos.X+0.5,100.5,-_pos.Y-0.5));
		}
	} else {
		throw ErrorsPowerUp(std::cerr, "! placeEntity Failed !");
	}
}
