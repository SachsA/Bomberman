/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** QuickGame.hpp for cpp_indie_studio
*/

#ifndef QUICK_GAME_HPP_
#define QUICK_GAME_HPP_

#include <map>
#include <irrlicht.h>
#include "AMenu.hpp"
#include "Character.hpp"
#include "Errors.hpp"

enum ButtonQuickGame {
	BUTTON_NOTHING_QUICK = -1,
	BUTTON_START_QUICK,
	BUTTON_RIGHT_QUICK,
	BUTTON_LEFT_QUICK,
	BUTTON_RIGHT_TYPE_QUICK,
	BUTTON_LEFT_TYPE_QUICK,
	BUTTON_ADD_QUICK
};

/*! \class ErrorsQuickGame
 * \brief Used to handle custom error from QuickGame.
 *
 *
 */
class ErrorsQuickGame: public Errors {
public:
	ErrorsQuickGame(std::ostream &, const std::string &) throw();
	virtual ~ErrorsQuickGame(void) throw();
};

/*! \class QuickGame
 * \brief QuickGame menu implemantation.
 *
 *
 */
class QuickGame : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Event handling wich happend during QuickGame display.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver(irr::IrrlichtDevice *, QuickGame &);
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		void refresh();
		bool buttonClicked(irr::s32);
	private:
		QuickGame &_quickGame;
		irr::IrrlichtDevice *_device;
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
public:
	QuickGame(irr::IrrlichtDevice *,
		irr::video::IVideoDriver *,
		BomberManConfig &);
	QuickGame(QuickGame const &) = default;
	QuickGame &operator=(QuickGame const &) = default;
	~QuickGame() = default;

	SceneStatus launch() override;
private:
	void initText();
	void initImage();
	void checkFocus();
	void initCamera();
	void addToBoard();
	void clearPlayer();
	void launchButton();
	void placeButtons();
	void displayWindow();
	void refreshConfigs();
	void fillUserDataAI();
	void initialization();
	void displayFPSTitle();
	void browseCharacter();
	void displayNameBoard();
	void keyboardFunctions();
	void initInputUsername();
	void displayNatureBoard();
	void displayBoardCharac();
	void arrowFunctionsType();
	void inversePlayerNature();
	std::string getUserInput();
	void changeCharacterLeft();
	void changeCharacterRight();
	void arrowFunctionsCharac();
	SceneStatus launchSceneButton();
	void initMapCharacter(std::string);
	void loadImage(std::string, std::string);
	void fillUserDataPlayer(enum PlayerType);
	void arrowsFocus(std::string, std::string);
	void PlaceOneButton(std::string, enum ButtonQuickGame,
			    std::string, int, int);
	irr::gui::IGUIButton *initButton(irr::core::rect<irr::s32>,
					 std::string,
					 enum ButtonQuickGame);
	 void initCharacter(irr::core::vector3df,
 			    irr::core::vector3df,
			    irr::core::vector3df,
		    	    dataMap<std::string, Character> &);

	irr::gui::IGUIEditBox *_inputBox;
	QuickGame::EventReceiver _receiver;
	irr::scene::ICameraSceneNode *_camera;

	bool _down = true;

	size_t _player = 1;

	irr::gui::IGUIFont *_font;

	enum PlayerType _playerNature = HUMAN;

	irr::core::dimension2d<irr::u32> _sizeAI;
	irr::core::dimension2d<irr::u32> _sizeHuman;

	std::vector<std::string> _namePerso;
	std::unordered_map<std::size_t, std::string> _mapName;
	std::unordered_map<std::string, irr::gui::IGUIButton *> _buttons;
	std::unordered_map<std::size_t, dataMap<std::string, Character>> _mapPlayer;
	std::unordered_map<std::size_t, dataMap<std::string, Character>> _mapBoard;

	std::vector<irr::core::vector3df> _positionBoard;
	irr::core::vector3df _scaleBoard = irr::core::vector3df(0.3, 0.3, 0.3);
	irr::core::vector3df _rotationBoard = irr::core::vector3df(0, -30, 0);

	enum ButtonQuickGame _buttonStatus = ButtonQuickGame::BUTTON_NOTHING_QUICK;
};

#endif //QUICK_GAME_HPP_
