//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// BombExplosion.hpp
//

#ifndef BOMB_EXPLOSION_HPP_
	#define BOMB_EXPLOSION_HPP_

	#include <irrlicht.h>
	#include "Errors.hpp"

	/*! \class ErrorsBombExplosion
	 * \brief Used to handle custom error from BombExplosion.
	 *
	 *
	 */
	class ErrorsBombExplosion: public Errors {
	public:
		ErrorsBombExplosion(std::ostream &, const std::string &) throw();
		virtual ~ErrorsBombExplosion(void) throw();
	};

	/*! \class BombExplosion
	 * \brief Implementation of everything related to a bomb explosion
	 *
	 *
	 */
	class BombExplosion {
	public:
		BombExplosion(irr::core::vector2df pos, int id,
			irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
		~BombExplosion() = default;

		void placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, irr::core::vector2df pos);
		irr::scene::ISceneNode& getNode();
		size_t& getTimePlaced();
		int& getId();
		irr::core::vector2df& getPos();
		void loadImage(std::string path, irr::video::IVideoDriver* driver);

	private:
		size_t _timePlaced;
		irr::core::vector2df _pos;
		int _id;
		irr::scene::ISceneNode* _node;
	};


#endif /* end of include guard: BOMB_EXPLOSION_HPP_ */
