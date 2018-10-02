/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** UserData.hpp for cpp_indie_studio
*/

#ifndef USERDATA_HPP
#define USERDATA_HPP

#include "Character.hpp"

enum PlayerType {
	HUMAN = 0,
	AI
};

/*! \class UserData
 * \brief Store date related to the player himself
 *
 * 
 */
struct UserData {
	UserData(Character &origin) : character(origin) {};
	Character &character;
	std::string userName;
	enum PlayerType type;
	int score;
	int level;
};

#endif //USERDATA_HPP
