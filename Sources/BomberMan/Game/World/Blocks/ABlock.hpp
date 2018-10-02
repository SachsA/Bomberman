/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#ifndef INDIE_STUDIO_ABLOCK_HPP
	#define INDIE_STUDIO_ABLOCK_HPP

	#include <irrlicht.h>
	#include <string>
	#include "Errors.hpp"

	enum BlockType {
		WALL,
		BOX
	};

	/*! \class ErrorsABlock
	 * \brief Used to handle custom error from ABlock.
	 *
	 *
	 */
	class ErrorsABlock: public Errors {
	public:
		ErrorsABlock(std::ostream &, const std::string &) throw();
		virtual ~ErrorsABlock(void) throw();
	};

	/*! \class ABlock
	 * \brief Store every data related wich are common to every type of block.
	 *
	 *
	 */
	class ABlock {
	public:
		ABlock(size_t health, irr::core::vector2df pos, BlockType blocktype);
		~ABlock() = default;

		virtual void takeDamage(float damage) = 0;
		virtual void placeEntity(irr::scene::ISceneManager* smgr,
				 	irr::video::IVideoDriver* driver,
				 	std::string theme) = 0;
		BlockType& getBlockType();
		irr::scene::ISceneNode& getNode();
		irr::core::vector2df& getPos();
		void loadImage(std::string path, irr::video::IVideoDriver* driver);
		void breakBlock();
	protected:
		size_t _health;
		irr::core::vector2df _pos;
		BlockType _blockType;
		irr::scene::ISceneNode* _node;
	};

#endif //INDIE_STUDIO_ABLOCK_HPP
