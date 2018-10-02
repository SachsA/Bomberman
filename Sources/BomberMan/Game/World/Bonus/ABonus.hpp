//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// ABonus.hpp
//

#ifndef ABONUS_HPP
	#define ABONUS_HPP

	#include <irrlicht.h>
	#include <memory>
	#include "Errors.hpp"

	enum BonusType {
		SPEEDUP,
		BOMBUP,
		POWERUP
	};

	/*! \class ErrorsABonus
	 * \brief Used to handle custom error from World.
	 *
	 *
	 */
	class ErrorsABonus: public Errors {
	public:
		ErrorsABonus(std::ostream &, const std::string &) throw();
		virtual ~ErrorsABonus(void) throw();
	};

	/*! \class ABonus
	 * \brief Abstract class containing every data wich are common to all the bonus.
	 *
	 *
	 */
	class ABonus {
	public:
		explicit ABonus(BonusType bonusType, irr::core::vector2df pos);
		~ABonus();

		BonusType& getType();
		irr::core::vector3df& getRotation();
		irr::scene::IAnimatedMeshSceneNode& getNodeA();
		void setRotation(irr::core::vector3df rotation);
		virtual void placeEntity(irr::scene::ISceneManager* smgr,
					irr::video::IVideoDriver* driver) = 0;
		void loadImage(std::string path, irr::video::IVideoDriver* driver);
		irr::core::vector2df &getPos();
	protected:
		BonusType _bonusType;
		irr::core::vector2df _pos;
		irr::core::vector3df _rotation;
		irr::scene::IAnimatedMeshSceneNode* _nodeA;
	};

#endif /* end of include guard: ABONUS_HPP */
