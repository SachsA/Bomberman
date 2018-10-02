/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#ifndef INDIE_STUDIO_BOMBERMAN_HPP
#define INDIE_STUDIO_BOMBERMAN_HPP

#include <memory>
#include <unordered_map>
#include "Errors.hpp"
#include "Core/BomberManConfig/BomberManConfig.hpp"
#include "AMenu.hpp"


/*! \class ErrorsBomberMan
 * \brief Used to handle custom error comming from BomberMan.
 *
 *
 */
class ErrorsBomberMan: public Errors {
public:
	ErrorsBomberMan(std::ostream &, const std::string &) throw();
	virtual ~ErrorsBomberMan(void) throw();
};


/*! \class BomberMan
 * \brief Class containing irrlicht device and driver.
 *
 *
 */
class BomberMan {
public:
	BomberMan();
	~BomberMan();

	void launchBomberMan();

	SceneStatus launchScene(SceneStatus const &);
private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_driver;

	std::unordered_map<SceneStatus, std::unique_ptr<AMenu>> _menus;
	BomberManConfig _config;
};

#endif //INDIE_STUDIO_BOMBERMAN_HPP
