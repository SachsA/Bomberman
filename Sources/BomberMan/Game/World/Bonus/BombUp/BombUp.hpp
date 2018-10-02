//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// BombUp.hpp
//

#ifndef BOMBUP_HPP
	#define BOMBUP_HPP

	#include "ABonus.hpp"
	#include "Errors.hpp"

	/*! \class ErrorsBombUp
	 * \brief Used to handle custom error from BombUp.
	 *
	 *
	 */
	class ErrorsBombUp: public Errors {
	public:
		ErrorsBombUp(std::ostream &, const std::string &) throw();
		virtual ~ErrorsBombUp(void) throw();
	};

	/*! \class BombUp
	 * \brief Implementation of the BombUp bonus.
	 *
	 *
	 */
	class BombUp : public ABonus {
	public:
		BombUp(irr::core::vector2df pos);
		~BombUp();
		void placeEntity(irr::scene::ISceneManager* smgr,
					irr::video::IVideoDriver* driver) override;
	};

#endif /* end of include guard: BOMBUP_HPP */
