//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Wall.hpp
//

#ifndef WALL_HPP
#define WALL_HPP

#include <irrlicht.h>
#include "ABlock.hpp"
#include "Errors.hpp"

/*! \class ErrorsWall
 * \brief Used to handle custom error from Wall.
 *
 *
 */
class ErrorsWall: public Errors {
public:
	ErrorsWall(std::ostream &, const std::string &) throw();
	virtual ~ErrorsWall(void) throw();
};


/*! \class Wall
 * \brief Unbreakable object implemantation
 *
 *
 */
class Wall : public ABlock{
public:
	Wall(irr::core::vector2df pos);
	~Wall() = default;
	void takeDamage(float damage) override;
	void placeEntity(irr::scene::ISceneManager* smgr,
			 irr::video::IVideoDriver* driver,
		 	 std::string theme) override;
};

#endif  //WALL_HPP
