/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#ifndef INDIE_STUDIO_APLAYER_HPP
#define INDIE_STUDIO_APLAYER_HPP

	#include <irrlicht.h>
	#include <iostream>
	#include <memory>
	#include <string>
	#include "Action.hpp"
	#include "Errors.hpp"
	#include "UserData.hpp"

	enum Status {
		IDLE,
		RUN
	};

	/*! \class ErrorsAPlayer
	 * \brief Used to handle custom error from APlayer.
	 *
	 *
	 */

	class ErrorsAPlayer: public Errors {
	public:
		ErrorsAPlayer(std::ostream &, const std::string &) throw();
		virtual ~ErrorsAPlayer(void) throw();
	};

	/*! \class APlayer
	 * \brief Abstract Class, containing every data that are shared with every player.
	 *
	 *
	 */
	class APlayer {
	public:
		explicit APlayer(std::string name, int _id, PlayerType playerType,
			irr::core::vector2df pos, Character& character, irr::core::vector3df& rotation);

		std::string& getCharacterName();
		std::string& getName();
		PlayerType& getPlayerType();
		size_t& getNbBombUp();
		int& getId();
		int& getAvailableBomb();
		irr::scene::IAnimatedMeshSceneNode& getNodeA();
		size_t& getNbSpeedUp();
		irr::core::vector2df& getPos();
		irr::core::vector3df& getRotation();
		void die();
		enum Status& getStatus();
		void setStatus(enum Status status);
		bool getAlive();
		void setAlive(bool alive);
		void loadImage(std::string path, irr::video::IVideoDriver* driver);
		void setPos(irr::core::vector2df pos);
		void placeEntity(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, Status status);

		virtual enum Action play() = 0;
	protected:
		std::string _name;
		int _id;
		PlayerType _playerType;
		int _availableBomb;
		size_t _nbBombUp;
		size_t _nbSpeedUp;
		irr::core::vector2df _pos;
		bool _alive;
		irr::core::vector3df _rotation;
		enum Status _status;

		irr::scene::IAnimatedMeshSceneNode* _nodeA;
		Character& _character;
	};

#endif //INDIE_STUDIO_APLAYER_HPP
