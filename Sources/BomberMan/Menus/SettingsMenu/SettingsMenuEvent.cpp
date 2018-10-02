/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** SettingsMenuEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "SettingsMenu.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

SettingsMenu::EventReceiver::EventReceiver(irr::IrrlichtDevice *device,
	SettingsMenu &settings
)
	: _device(device), _settings(settings)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

#ifdef __unix__
void SettingsMenu::EventReceiver::updateSounds(std::string const &type, SoundType soundType)
{
	if (!_settings._config.getSoundStatus(soundType)) {
		_settings._config.setSoundStatus(soundType, true);
		_settings._config.setVolumes(soundType, _settings._config.getVolumes(soundType));
		_settings.getScrollBar(type)->setPos(_settings._config.getVolumes(soundType));
	} else {
		_settings._config.setSoundStatus(soundType, false);
		_settings._config.setVolumes(soundType, 0);
		_settings.getScrollBar(type)->setPos(0);
	}
}

bool SettingsMenu::EventReceiver::buttonClicked(irr::s32 id)
{
	switch (id) {
	case MUSIC_BUTTON:
		updateSounds("Music", SoundType::MUSIC);
		break;
	case MENUS_BUTTON:
		updateSounds("Menus", SoundType::MENUS);
		break;
	case GAME_BUTTON:
		updateSounds("Game", SoundType::GAME);
		break;
	default:
		_settings._buttonStatus = ButtonSettings::BUTTON_NOTHING;
		return false;
	}
	return true;
}

bool SettingsMenu::EventReceiver::scrollBarClicked(const irr::SEvent &event)
{
	irr::s32 id = event.GUIEvent.Caller->getID();
	irr::s32 pos;

	switch (id) {
	case MUSIC_SCROLL_BAR:
		pos = ((irr::gui::IGUIScrollBar *)event.GUIEvent.Caller)->getPos();
		_settings._config.getVolumes(SoundType::MUSIC) = pos;
		_settings._config.setVolumes(SoundType::MUSIC, pos);
		break;
	case MENUS_SCROLL_BAR:
		pos = ((irr::gui::IGUIScrollBar *)event.GUIEvent.Caller)->getPos();
		_settings._config.getVolumes(SoundType::MENUS) = pos;
		_settings._config.setVolumes(SoundType::MENUS, pos);
		break;
	case GAME_SCROLL_BAR:
		pos = ((irr::gui::IGUIScrollBar *)event.GUIEvent.Caller)->getPos();
		_settings._config.getVolumes(SoundType::GAME) = pos;
		_settings._config.setVolumes(SoundType::GAME, pos);
		break;
	default:
		_settings._buttonStatus = ButtonSettings::BUTTON_NOTHING;
		return false;
	}
	return true;
}
#endif

void SettingsMenu::EventReceiver::refresh()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool SettingsMenu::EventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == irr::EET_GUI_EVENT) {
		irr::s32 id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType) {
		#ifdef __unix__
		case irr::gui::EGET_SCROLL_BAR_CHANGED:
			_settings._config.launchSound(SoundType::MENUS, "Press");
			return scrollBarClicked(event);

		case irr::gui::EGET_BUTTON_CLICKED:
			_settings._config.launchSound(SoundType::MENUS, "Press");
			return buttonClicked(id);
		#endif
		default:
			_settings._buttonStatus = ButtonSettings::BUTTON_NOTHING;
			break;
		}
	}

	return false;
}

bool SettingsMenu::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _KeyIsDown[keyCode];
}