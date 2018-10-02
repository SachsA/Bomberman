//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Human.hpp
//

#ifndef HUMAN_HPP
#define HUMAN_HPP

	#include <vector>
	#include "Errors.hpp"
	#include "APlayer.hpp"
	#include "GameGfx.hpp"

	/*! \class ErrorsHuman
	 * \brief Used to handle custom error from Human.
	 *
	 *
	 */

	class ErrorsHuman: public Errors {
	public:
		ErrorsHuman(std::ostream &, const std::string &) throw();
		virtual ~ErrorsHuman(void) throw();
	};

	/*! \class Human
	 * \brief Everithing remated to the character being playedr by a human.
	 *
	 *
	 */

	class Human : public APlayer {
	public:
		Human(std::string name, int _id, irr::core::vector2df pos,
			Character& character, std::vector<irr::EKEY_CODE> controls, GameGfx::EventReceiver& _receiver, irr::core::vector3df& rotation);
		enum Action play();

	private:
		std::vector<irr::EKEY_CODE> _controls;
		GameGfx::EventReceiver& _receiver;
	};

#endif /* end of include guard: HUMAN_HPP */
