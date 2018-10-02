/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#ifndef INDIE_STUDIO_IMENUS_HPP
#define INDIE_STUDIO_IMENUS_HPP

#include <map>
#include <string>
#include <memory>
#include <irrlicht.h>
#include <unordered_map>
#include "BomberManConfig.hpp"

enum SceneStatus {
	errorScene = -2,
	QUIT,
	NOTHING,
	INTRO,
	PRINCIPAL_MENU,
	SETTINGS_MENU,
	CHOOSE_GAME,
	NEW_GAME,
	QUICK_GAME,
	GFX_GAME,
};

/*! \class dataMap
 * \brief Used to get an interator link to this map.
 *
 *
 */
template<typename T, typename U>
class dataMap {
public:
	dataMap() = default;
	dataMap(const dataMap<T, U> &) = default;
	~dataMap() = default;
	typename std::map<T, U> map;
	typename std::map<T, U>::iterator iterator;
};

/*! \class AMenu
 * \brief Abstract class containing everything that are common to every menu.
 *
 *
 */
class AMenu {
public:
	explicit AMenu(irr::IrrlichtDevice *, irr::video::IVideoDriver *,
		BomberManConfig &);
	virtual ~AMenu() = default;

	virtual SceneStatus launch() = 0;

public:
	BomberManConfig &_config;

protected:

	void clearScreen();

	std::unordered_map<std::string, irr::video::ITexture *> _textures;
	#ifdef __unix__
		std::unordered_map<std::string, std::unique_ptr<sf::Music>> _music;
	#endif

	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;
	irr::gui::IGUIEnvironment *_env;
	irr::scene::ISceneManager *_scene;
};

#endif //INDIE_STUDIO_IMENUS_HPP
