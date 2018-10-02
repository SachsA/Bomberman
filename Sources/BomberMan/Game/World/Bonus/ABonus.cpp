//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ABonus.cpp
//

#include "ABonus.hpp"

ABonus::ABonus(BonusType bonusType, irr::core::vector2df pos)
	: _bonusType(bonusType), _pos(pos)
{}

ABonus::~ABonus()
{}

BonusType& ABonus::getType()
{
	return _bonusType;
}

irr::core::vector2df& ABonus::getPos()
{
	return _pos;
}

void ABonus::setRotation(irr::core::vector3df rotation)
{
	_rotation = rotation;
}

irr::core::vector3df& ABonus::getRotation()
{
	return _rotation;
}

irr::scene::IAnimatedMeshSceneNode& ABonus::getNodeA()
{
	return *_nodeA;
}

void ABonus::loadImage(std::string path, irr::video::IVideoDriver* driver)
{
	if (driver->getTexture(path.c_str()) == NULL)
		throw ErrorsABonus(std::cerr, "! loadImage Failed !");
	_nodeA->setMaterialTexture(0, driver->getTexture(path.c_str()));
}
