/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PrincipalMenuGame.hpp for cpp_indie_studio
*/

#ifndef PRINCIPAL_MENU_GAME_HPP_
#define PRINCIPAL_MENU_GAME_HPP_

#include <irrlicht.h>
#include "BomberManConfig.hpp"
#include "AMenu.hpp"
#include "Errors.hpp"

enum ButtonPrincipal {
	BUTTON_NOTHING_PRINCIP = -1,
	BUTTON_QUIT_PRINCIP = 0,
	BUTTON_PLAY_PRINCIP,
	BUTTON_SETTINGS_PRINCIP
};

/*! \class ErrorsPrincipalMenuGame
 * \brief Used to handle custom error from PrincipalMenuGame.
 *
 *
 */
class ErrorsPrincipalMenuGame: public Errors {
public:
	ErrorsPrincipalMenuGame(std::ostream &, const std::string &) throw();
	virtual ~ErrorsPrincipalMenuGame(void) throw();
};

/*! \class PrincipalMenuGame
 * \brief Implemantation of the main menu.
 *
 *
 */
class PrincipalMenuGame : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Event handling wich happend during PrincipalMenuGame display.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver(irr::IrrlichtDevice *, PrincipalMenuGame &);
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		void refresh();
		bool buttonClicked(irr::s32);
	private:
		PrincipalMenuGame &_principal;
		irr::IrrlichtDevice *_device;
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};

public:
	PrincipalMenuGame(irr::IrrlichtDevice *,
		irr::video::IVideoDriver *,
		BomberManConfig &
	);
	PrincipalMenuGame(PrincipalMenuGame const &) = default;
	PrincipalMenuGame &operator=(PrincipalMenuGame const &) = default;
	~PrincipalMenuGame() = default;

	SceneStatus launch() override;


private:
	void updateConfigValue(std::string const &, int &, int);
	void updateConfigValue(std::string const &, float &, float);
	void initImage();
	void initEarth();
	void initCamera();
	void displayWindow();
	void initialization();
	void displayFPSTitle();
	SceneStatus launchButton();
	void loadImage(std::string, std::string);
	irr::gui::IGUIButton *initButton(irr::core::rect<irr::s32>,
					 std::string,
					 enum ButtonPrincipal);

	int _fps;
	float _earthRotationSpeed;

	irr::gui::IGUIButton *_playButton;
	irr::gui::IGUIButton *_quitButton;
	irr::gui::IGUIButton *_settingsButton;
	irr::scene::IMeshSceneNode *_earth;
	irr::scene::ICameraSceneNode *_camera;
	PrincipalMenuGame::EventReceiver _receiver;
	enum ButtonPrincipal _buttonStatus = ButtonPrincipal::BUTTON_NOTHING_PRINCIP;
};

#endif //PRINCIPAL_MENU_GAME_HPP_
