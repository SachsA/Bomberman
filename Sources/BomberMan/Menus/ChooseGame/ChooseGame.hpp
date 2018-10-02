/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ChooseGame.hpp for cpp_indie_studio
*/

#ifndef CHOOSE_GAME_HPP_
#define CHOOSE_GAME_HPP_

#include <irrlicht.h>
#include "Errors.hpp"
#include "AMenu.hpp"

enum ButtonChooseGame {
	BUTTON_NOTHING_CHOOSE = -1,
	BUTTON_NEW_CHOOSE,
	BUTTON_QUICK_CHOOSE
};

/*! \class ErrorsChooseGame
 * \brief Used to handle custom error from ChooseGame.
 *
 *
 */
class ErrorsChooseGame: public Errors {
public:
	ErrorsChooseGame(std::ostream &, const std::string &) throw();
	virtual ~ErrorsChooseGame(void) throw();
};


/*! \class ChooseGame
 * \brief Implementation of the menu used to choose game type.
 *
 *
 */
class ChooseGame : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Handler for every event apearing while player is in chooseGame menu.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver(irr::IrrlichtDevice *, ChooseGame &);
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		void refresh();
		bool buttonClicked(irr::s32);
	private:
		ChooseGame &_choose;
		irr::IrrlichtDevice *_device;
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};

public:
	ChooseGame(irr::IrrlichtDevice *,
		irr::video::IVideoDriver *,
		BomberManConfig &
	);
	ChooseGame(ChooseGame const &) = default;
	ChooseGame &operator=(ChooseGame const &) = default;
	~ChooseGame() = default;

	SceneStatus launch() override;
private:
	void updateConfigValue(std::string const &, int &, int);
	void updateConfigValue(std::string const &, float &, float);
	void initCamera();
	void initEarth();
	void animation(irr::core::vector3df const &, int);
	void initImage();
	void displayWindow();
	void initialization();
	void displayFPSTitle();
	void loadImage(std::string, std::string);
	SceneStatus launchButton();
	irr::gui::IGUIButton *initButton(irr::core::rect<irr::s32>,
					 std::string,
					 enum ButtonChooseGame);

	int _fps;
	float _earthRotationSpeed;
	float _earthMovementSpeed;

	irr::scene::IMeshSceneNode *_earth;
	irr::gui::IGUIButton *_newGame;
	irr::gui::IGUIButton *_quickGame;
	ChooseGame::EventReceiver _receiver;
	irr::scene::ICameraSceneNode *_camera;
	enum ButtonChooseGame _buttonStatus = ButtonChooseGame::BUTTON_NOTHING_CHOOSE;
};

#endif //CHOOSE_GAME_HPP_
