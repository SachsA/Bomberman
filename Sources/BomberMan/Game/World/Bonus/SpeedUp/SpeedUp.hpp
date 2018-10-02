//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// SpeedUp.hpp
//

#ifndef SPEEDUP_HPP
	#define SPEEDUP_HPP

	#include "ABonus.hpp"
	#include "Errors.hpp"

	/*! \class ErrorsSpeedUp
	 * \brief Used to handle custom error from SpeedUp.
	 *
	 *
	 */
	class ErrorsSpeedUp: public Errors {
	public:
		ErrorsSpeedUp(std::ostream &, const std::string &) throw();
		virtual ~ErrorsSpeedUp(void) throw();
	};

	/*! \class SpeedUp
	 * \brief Implementation of the SpeedUp bonus.
	 *
	 *
	 */
	class SpeedUp : public ABonus {
	public:
		SpeedUp(irr::core::vector2df pos);
		~SpeedUp();
		void placeEntity(irr::scene::ISceneManager* smgr,
					irr::video::IVideoDriver* driver) override;
	};

#endif /* end of include guard: SPEEDUP_HPP */
