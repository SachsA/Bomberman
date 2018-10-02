/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** SettingsMenu.hpp for cpp_indie_studio
*/

#ifndef SETTINGS_MENU_HPP_
#define SETTINGS_MENU_HPP_

#include <irrlicht.h>
#include "AMenu.hpp"
#include "Errors.hpp"

enum ButtonSettings {
	BUTTON_NOTHING= -1,
	MUSIC_BUTTON,
	MUSIC_SCROLL_BAR,
	MENUS_BUTTON,
	MENUS_SCROLL_BAR,
	GAME_BUTTON,
	GAME_SCROLL_BAR
};

/*! \class ErrorsSettingsMenu
 * \brief Used to handle custom error from SettingsMenu.
 *
 *
 */
class ErrorsSettingsMenu: public Errors {
public:
	ErrorsSettingsMenu(std::ostream &, const std::string &) throw();
	virtual ~ErrorsSettingsMenu(void) throw();
};

/*! \class SettingsMenu
 * \brief SettingsMenu implementation.
 *
 *
 */
class SettingsMenu : public AMenu {
public:
	/*! \class EventReceiver
	 * \brief Event handling wich happend during SettingMenu display.
	 *
	 *
	 */
	class EventReceiver : public irr::IEventReceiver {
	public:
		EventReceiver(irr::IrrlichtDevice *, SettingsMenu &);
		~EventReceiver() = default;
		virtual bool OnEvent(const irr::SEvent &event);
		virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
		void refresh();
		#ifdef __unix__
			bool buttonClicked(irr::s32);
			bool scrollBarClicked(const irr::SEvent &event);
			void updateSounds(std::string const &type, SoundType);
		#endif

	private:
		#ifdef __unix__
			void updateMusicVolume(std::unordered_map<std::string, std::unique_ptr<sf::Music>> &, irr::s32 const &pos);
		#endif

		SettingsMenu &_settings;
		irr::IrrlichtDevice *_device;
		bool _KeyIsDown[irr::KEY_KEY_CODES_COUNT];
	};
public:
	SettingsMenu(irr::IrrlichtDevice *,
		  irr::video::IVideoDriver *,
		BomberManConfig &);
	SettingsMenu(SettingsMenu const &) = default;
	SettingsMenu &operator=(SettingsMenu const &) = default;
	~SettingsMenu() = default;


	irr::gui::IGUIScrollBar *getScrollBar(std::string const &);

	SceneStatus launch() override;
private:
	void updateConfigValue(std::string const &, int &, int);
	void updateConfigValue(std::string const &, float &, float);
	void animation(irr::core::vector3df const &, int);
	void initCamera();
	void initEarth();
	void initImage();
	void displayWindow();
	void initialization();
	void displayFPSTitle();
	void loadImage(std::string, std::string);
	void initButton(std::string const &, irr::core::rect<irr::s32>,
		std::string, enum ButtonSettings
	);
	void initScrollBar(std::string const &,
		irr::core::rect<irr::s32>,
		enum ButtonSettings func);

	int _fps;
	float _earthRotationSpeed;
	float _earthMovementSpeed;

	std::unordered_map<std::string, irr::gui::IGUIScrollBar *> _scrollbars;
	std::unordered_map<std::string, irr::gui::IGUIButton *> _buttons;

	irr::scene::IMeshSceneNode *_earth;
	SettingsMenu::EventReceiver _receiver;
	irr::scene::ICameraSceneNode *_camera;
	enum ButtonSettings _buttonStatus = ButtonSettings::BUTTON_NOTHING;
};

#endif //SETTINGS_MENU_HPP_
