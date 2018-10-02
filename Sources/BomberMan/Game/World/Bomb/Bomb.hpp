//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Bomb.hpp
//

#ifndef  BOMB_HPP
#define BOMB_HPP

	#include <irrlicht.h>
	#include <vector>
	#include <memory>
	#include "Errors.hpp"

	/*! \class ErrorsBomb
	 * \brief Used to handle custom error from Bomb.
	 *
	 *
	 */
	class ErrorsBomb: public Errors {
	public:
		ErrorsBomb(std::ostream &, const std::string &) throw();
		virtual ~ErrorsBomb(void) throw();
	};

	/*! \class Bomb
	 * \brief Implementation of everything related with a bomb
	 *
	 *
	 */
	class Bomb {
	public:
		Bomb(size_t range, irr::core::vector2df pos, int id,
			 irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
		~Bomb() = default;

		size_t& getRange();
		void loadImageA(std::string path, irr::video::IVideoDriver* driver);
		irr::core::vector2df& getPos();
		size_t& getTimePlaced();
		int& getId();
		irr::scene::IAnimatedMeshSceneNode& getNodeA();
		void placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);

	private:
		size_t _range;
		irr::core::vector2df _pos;
		size_t _timePlaced;
		int _id;

		irr::scene::IAnimatedMeshSceneNode* _nodeA;
	};

#endif /* end of include guard: BOMB_HPP */
