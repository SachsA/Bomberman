/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#ifndef INDIE_STUDIO_BOMBERMANCONFIG_HPP
#define INDIE_STUDIO_BOMBERMANCONFIG_HPP

#include <irrlicht.h>
#include <unordered_map>
#include <string>
#include <map>
#include <vector>
#ifdef __unix__
	#include <SFML/Audio.hpp>
#endif
#include "UserData.hpp"
#include "Errors.hpp"

#ifdef __unix__
	enum SoundType {
		MUSIC,
		MENUS,
		GAME
	};
#endif

/*! \class ErrorsSounds
 * \brief Used to handle custom error related to sound.
 *
 * 
 */
class ErrorsSounds: public Errors {
public:
	ErrorsSounds(std::ostream &, const std::string &) throw();
	virtual ~ErrorsSounds(void) throw();
};

/*! \class ErrorsConfig
 * \brief Used to handle custom error coming from BomberManConfig
 *
 *
 */

class ErrorsConfig: public Errors {
public:
	ErrorsConfig(std::ostream &, const std::string &) throw();
	virtual ~ErrorsConfig(void) throw();
};


/*! \class BomberManConfig
 * \brief Used to get data from the game's config file
 *
 * 
 */

class BomberManConfig {
public:
	BomberManConfig(std::string const &);
	BomberManConfig(BomberManConfig const &) = default;
	BomberManConfig &operator=(BomberManConfig const &) = default;

	~BomberManConfig() = default;

	std::unordered_map<std::string, std::string> const &parseFile();
	void setConfFile(std::string const &filePath);

	std::unordered_map<std::string, std::string> getConf();
	std::string getConf(std::string const &);

	#ifdef __unix__
		std::unordered_map<SoundType, float> &getVolumes();
		float &getVolumes(SoundType);

		void insertMusic(std::string const &, std::string const &);
		void launchMusic(std::string const &);
		void pauseMusic(std::string const &);
		sf::Music::Status getMusicStatus(std::string const &);

		void insertSound(SoundType, std::string const &, std::string const &);
		void launchSound(SoundType, std::string const &);
		float getActiveVolume(SoundType);

		void setVolumes(SoundType, irr::s32 const &pos);
		void stopSound(SoundType, std::string const &);

		bool getSoundStatus(SoundType);
		void setSoundStatus(SoundType, bool);
	#endif

public:
	std::vector<UserData> _users;
	irr::core::vector3df earthRotation;
	irr::core::vector3df earthPosition;
	irr::f32 earthRadius;
	irr::video::ITexture *earthTexture;
private:
	#ifdef __unix__
		void updateVolumes(std::unordered_map<std::string, std::unique_ptr<sf::Music>> &, irr::s32 const &);
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> musics;
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> menusSounds;
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> gameSounds;
	#endif

	void insertValues(std::string const &inputLine);
	std::string cleanStr(std::string &);
private:
	std::string _filePath;
	std::unordered_map<std::string, std::string> _confValues;
	#ifdef __unix__
		std::unordered_map<SoundType, bool> _soundStatus;
		std::unordered_map<SoundType, float> _volumes;
	#endif
};

#endif //INDIE_STUDIO_BOMBERMANCONFIG_HPP
