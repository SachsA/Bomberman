//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// SpeedUp.cpp
//

#include "SpeedUp.hpp"

SpeedUp::SpeedUp(irr::core::vector2df pos)
	:	ABonus(SPEEDUP, pos)
{
	_nodeA = nullptr;
}

SpeedUp::~SpeedUp()
{}

void SpeedUp::placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver)
{
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("AssetsIndie/Common/Bonus/SpeedUp/converse_obj.obj");
	if (mesh) {
		_nodeA = smgr->addAnimatedMeshSceneNode(mesh);
		if (_nodeA) {
			_rotation = irr::core::vector3df(30 ,180, 0);
			loadImage("AssetsIndie/Common/Bonus/SpeedUp/converse.jpg", driver);
			_nodeA->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			_nodeA->setScale(irr::core::vector3df(0.02,0.02,0.02));
			_nodeA->setPosition(irr::core::vector3df(_pos.X+0.5,100.5,-_pos.Y-0.5));
			_nodeA->setRotation(_rotation);
		}
	} else {
		throw ErrorsSpeedUp(std::cerr, "! placeEntity Failed !");
	}
}
