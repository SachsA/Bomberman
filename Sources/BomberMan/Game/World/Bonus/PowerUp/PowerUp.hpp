//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// PowerUp.hpp
//

#ifndef POWERUP_HPP
	#define POWERUP_HPP

	#include "ABonus.hpp"
	#include "Errors.hpp"

	/*! \class ErrorsPowerUp
	 * \brief Used to handle custom error from PowerUp.
	 *
	 *
	 */
	class ErrorsPowerUp: public Errors {
	public:
		ErrorsPowerUp(std::ostream &, const std::string &) throw();
		virtual ~ErrorsPowerUp(void) throw();
	};

	/*! \class PowerUp
	 * \brief Implementation of the PowerUp Bonus.
	 *
	 *
	 */
	class PowerUp : public ABonus {
	public:
		PowerUp(irr::core::vector2df pos);
		~PowerUp();
		void placeEntity(irr::scene::ISceneManager* smgr,
					irr::video::IVideoDriver* driver) override;
	};

#endif /* end of include guard: POWERUP_HPP */
