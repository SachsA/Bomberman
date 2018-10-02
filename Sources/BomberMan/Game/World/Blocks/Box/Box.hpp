//
// EPITECH PROJECT, 2018
// indie-dev-client
// File description:
// Box.hpp
//

#ifndef BOX_HPP
	#define BOX_HPP

	#include <irrlicht.h>
	#include "ABlock.hpp"
	#include "Errors.hpp"

	/*! \class ErrorsBox
	 * \brief Used to handle custom error from Box.
	 *
	 *
	 */
	class ErrorsBox: public Errors {
	public:
		ErrorsBox(std::ostream &, const std::string &) throw();
		virtual ~ErrorsBox(void) throw();
	};

	/*! \class Box
	 * \brief Breakable object implemantation
	 *
	 *
	 */
	class Box : public ABlock {
	public:
		Box(irr::core::vector2df pos);
		~Box();

		void takeDamage(float damage) override;
		void placeEntity(irr::scene::ISceneManager* smgr,
				irr::video::IVideoDriver* driver,
				std::string theme) override;
	};
#endif /* end of include guard: BOX_HPP */
