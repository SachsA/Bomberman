/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Character.hpp for cpp_indie_studio
*/

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <irrlicht.h>

/*! \class Character
 * \brief Class containing data related to a character
 *
 *
 */
struct Character {
	Character() = default;

	std::string name;
	irr::video::ITexture *texture;
	irr::scene::IAnimatedMeshSceneNode *mesh;
};

#endif //CHARACTER_HPP
