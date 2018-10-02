/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** NewGame.hpp for cpp_indie_studio
*/

#ifndef NEW_GAME_HPP_
#define NEW_GAME_HPP_

#include <map>
#include <irrlicht.h>
#include "AMenu.hpp"
#include "Character.hpp"
#include "Errors.hpp"

enum ButtonNewGame {
	BUTTON_NOTHING_NEW = -1,
	BUTTON_START_NEW,
	BUTTON_RIGHT_NEW,
	BUTTON_LEFT_NEW
};

/*! \class ErrorsNewGame
 * \brief Used to handle custom error from IntroGame.
 *
 *
 */
class ErrorsNewGame: public Errors {
public:
	ErrorsNewGame(std::ostream &, const std::string &) throw();
	virtual ~ErrorsNewGame(void) throw();
};

/*! \class NewGame
 * \brief Implementation new game's menu
 *
 *
 */
class NewGame : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Event handling which happend during the NewGame menu display.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver(irr::IrrlichtDevice *, NewGame &);
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		void refresh();
		bool buttonClicked(irr::s32);
	private:
		NewGame &_newGame;
		irr::IrrlichtDevice *_device;
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
public:
	NewGame(irr::IrrlichtDevice *,
		irr::video::IVideoDriver *,
		BomberManConfig &);
	NewGame(NewGame const &) = default;
	NewGame &operator=(NewGame const &) = default;
	~NewGame() = default;

	SceneStatus launch() override;
private:
	void initText();
	void initImage();
	void checkFocus();
	void initCamera();
	void launchButton();
	void placeButtons();
	void initCharacter();
	void displayWindow();
	void fillUserDataAI();
	void arrowFunctions();
	void initialization();
	void displayFPSTitle();
	void browseCharacter();
	void keyboardFunctions();
	void initInputUsername();
	void fillUserDataPlayer();
	std::string getUserInput();
	void changeCharacterLeft();
	void changeCharacterRight();
	SceneStatus launchSceneButton();
	void initMapCharacter(std::string);
	void loadImage(std::string, std::string);
	void PlaceOneButton(std::string, enum ButtonNewGame,
			    std::string, int, int);
	irr::gui::IGUIButton *initButton(irr::core::rect<irr::s32>,
					 std::string,
					 enum ButtonNewGame);

	irr::gui::IGUIEditBox *_inputBox;
	NewGame::EventReceiver _receiver;
	irr::scene::ICameraSceneNode *_camera;

	std::string _userName;

	std::unordered_map<std::string, irr::gui::IGUIButton *> _buttons;

	dataMap<std::string, Character> _mapCharacter;

	enum ButtonNewGame _buttonStatus = ButtonNewGame::BUTTON_NOTHING_NEW;
};

#endif //NEW_GAME_HPP_
