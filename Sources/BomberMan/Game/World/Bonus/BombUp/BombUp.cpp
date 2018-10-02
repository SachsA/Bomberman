//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// BombUp.cpp
//

#include "BombUp.hpp"

BombUp::BombUp(irr::core::vector2df pos)
	:	ABonus(BOMBUP, pos)
{
	_nodeA = nullptr;
}

BombUp::~BombUp()
{}

void BombUp::placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("AssetsIndie/Common/Bonus/BombUp/bomb.obj");
	if (mesh) {
		_nodeA = smgr->addAnimatedMeshSceneNode(mesh);
		if (_nodeA) {
			_rotation = irr::core::vector3df(-50,-50,29);
			loadImage("AssetsIndie/Common/Bonus/BombUp/bomb.jpg", driver);
			_nodeA->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_nodeA->setScale(irr::core::vector3df(0.3,0.3,0.3));
			_nodeA->setPosition(irr::core::vector3df(_pos.X+0.5,100.5,-_pos.Y-0.5));
			_nodeA->setRotation(_rotation);
		}
	} else {
		throw ErrorsBombUp(std::cerr, "! placeEntity Failed !");
	}
}
