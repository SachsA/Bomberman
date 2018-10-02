//
// EPITECH PROJECT, 2018
// indie-dev-client
// File description:
// GameGfx.hpp
//

#ifndef GAMEGFX_HPP
#define GAMEGFX_HPP

#include <irrlicht.h>
#include <string>
#include <memory>
#include <vector>
#include "ABlock.hpp"
#include "APlayer.hpp"
#include "Bomb.hpp"
#include "Timer.hpp"
#include "ABonus.hpp"
#include "World.hpp"
#include "AMenu.hpp"

enum ButtonGameGfx {
	BUTTON_NOTHING_GAMEGFX = -1
};

/*! \class ErrorsGameGfx
 * \brief Used to handle custom error from GameGfx.
 *
 *
 */
class ErrorsGameGfx: public Errors {
public:
	ErrorsGameGfx(std::ostream &, const std::string &) throw();
	virtual ~ErrorsGameGfx(void) throw();
};

/*! \class GameGfx
 * \brief Everything related to the graphism of the game.
 *
 *
 */
class GameGfx : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Event handling class for the game.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver(irr::IrrlichtDevice *, GameGfx &);
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		bool &getIsPress();
		void refresh();
		bool buttonClicked(irr::s32);
	private:
		GameGfx &_gameGfx;
		irr::IrrlichtDevice *_device;
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
public:
	GameGfx(irr::IrrlichtDevice *device,
		irr::video::IVideoDriver *driver,
		BomberManConfig &config);
	~GameGfx() = default;

	SceneStatus launch();
	SceneStatus launchButton();
	#ifdef __unix__
		void loadSound();
	#endif
	void updateConfigValue(std::string const &key, int &value, int defaultValue);

	void initGame();
	void initTextures();
	void loadImage(std::string name, std::string path);
	void initPlayers();
	void drawBorderW(irr::core::vector3df pos);
	void drawBorderH(irr::core::vector3df pos);
	void drawHigh();
	void drawEnv();
	void printPlayerImage(std::unique_ptr<APlayer>& player, irr::core::position2d<int> pos);
	void introGame();
	void initIntroMessage(irr::core::stringw str);
	void fightMessagePrint();
	void drawGui();
	void setSkybox();
	void displayBlock();
	void displayPlayer();
	void drawNamePlayer();
	void displayBonus();
	std::vector<irr::EKEY_CODE> giveControls(size_t who);
	void initEndMessage(irr::core::stringw str, irr::core::rect<irr::s32> rect);

	void updatePlayerAnimation(enum Action res, std::unique_ptr<APlayer>& player);
	void updatePlayerRotation(enum Action res, std::unique_ptr<APlayer>& player);
	void loadImageT(irr::scene::ISceneNode* n, std::string path);
	void clearPlayers();
	SceneStatus pauseScreen();
	void addBombAvailableAfterExplosion(std::unique_ptr<Bomb>& bomb);

	//GAMEPLAY
	void playersMove();
	void checkBombExplosion();
	void checkExplosion();
	void checkPlayerDeath(irr::core::vector2df pos, int id);
	void printWinner();
	bool endGame();
	//!GAMEPLAY

	void changeCamera();
private:
	GameGfx::EventReceiver _receiver;
	int _fps;
	enum ButtonGameGfx _buttonStatus = ButtonGameGfx::BUTTON_NOTHING_GAMEGFX;

	bool _solo;
	bool _cameraSolo;
	std::string _theme;
	size_t _bombRange;
	int _mapSize;

	irr::gui::IGUIFont *_font;

	irr::gui::IGUIEditBox *_inputBox;

	std::vector<std::unique_ptr<APlayer>> _players;
	std::unique_ptr<World> _world;
};

#endif /* end of include guard: GAMEGFX_HPP */
