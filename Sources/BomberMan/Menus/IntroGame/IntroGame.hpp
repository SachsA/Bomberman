/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** IntroGame.hpp for cpp_indie_studio
*/

#ifndef INTRO_GAME_HPP_
#define INTRO_GAME_HPP_

#include <irrlicht.h>
#include <map>
#include "Errors.hpp"

#include "AMenu.hpp"

/*! \class ErrorsIntroGame
 * \brief Used to handle custom error from IntroGame.
 *
 *
 */
class ErrorsIntroGame: public Errors {
public:
	ErrorsIntroGame(std::ostream &, const std::string &) throw();
	virtual ~ErrorsIntroGame(void) throw();
};

/*! \class IntroGame
 * \brief Implementation of the game's intro.
 *
 *
 */
class IntroGame : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Event handling which happend during intro.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver();
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
	private:
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};

public:
	IntroGame(irr::IrrlichtDevice *,
		irr::video::IVideoDriver *,
		BomberManConfig &
	);
	IntroGame(IntroGame const &) = default;
	IntroGame &operator=(IntroGame const &) = default;
	~IntroGame() = default;

	SceneStatus launch() override;
	void move_bird(irr::u32 &, bool &);
private:
	void initImage();
	void updateConfigValue(std::string const &, int &, int);
	void displayWindow();
	void initialization();
	void displayFPSTitle();
	void displayCDProjekt();
	void loadImage(std::string name, std::string path);
	void launchFader(irr::video::SColor, irr::u32);


	int _fps;
	int _birdSpeed;

	int _pos_x_bird;
	int _pos_y_bird;
	int _pos_x_rarog;
	int _pos_y_rarog;
	irr::core::dimension2d<irr::u32> _size;

	irr::scene::IMeshSceneNode *_node;

	IntroGame::EventReceiver _receiver;
};

#endif //INTRO_GAME_HPP_
