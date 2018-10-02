/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#include "ABlock.hpp"

ABlock::ABlock(size_t health,
	irr::core::vector2df pos, BlockType blocktype)
	:	_health(health), _pos(pos), _blockType(blocktype)
{}

BlockType& ABlock::getBlockType()
{
	return this->_blockType;
}

irr::core::vector2df& ABlock::getPos()
{
	return this->_pos;
}

void ABlock::loadImage(std::string path, irr::video::IVideoDriver* driver)
{
	if (driver->getTexture(path.c_str()) == NULL)
		throw ErrorsABlock(std::cerr, "! loadImage Failed !");
	_node->setMaterialTexture(0, driver->getTexture(path.c_str()));
}

irr::scene::ISceneNode& ABlock::getNode()
{
	return *_node;
}
