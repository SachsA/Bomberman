/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** QuickGameEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "QuickGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

QuickGame::EventReceiver::EventReceiver(irr::IrrlichtDevice *device,
				      QuickGame &quickGame)
	: _device(device), _quickGame(quickGame)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool QuickGame::EventReceiver::buttonClicked(irr::s32 id)
{
	switch(id) {
		case ButtonQuickGame::BUTTON_RIGHT_QUICK:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_RIGHT_QUICK;
			return true;
		case ButtonQuickGame::BUTTON_LEFT_QUICK:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_LEFT_QUICK;
			return true;
		case ButtonQuickGame::BUTTON_RIGHT_TYPE_QUICK:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_RIGHT_TYPE_QUICK;
			return true;
		case ButtonQuickGame::BUTTON_LEFT_TYPE_QUICK:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_LEFT_TYPE_QUICK;
			return true;
		case ButtonQuickGame::BUTTON_START_QUICK:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_START_QUICK;
			return true;
		case ButtonQuickGame::BUTTON_ADD_QUICK:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_ADD_QUICK;
			return true;
		default:
			_quickGame._buttonStatus = ButtonQuickGame::BUTTON_NOTHING_QUICK;
			return false;
	}
	return false;
}

void QuickGame::EventReceiver::refresh()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;

}

bool QuickGame::EventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == irr::EET_GUI_EVENT)
	{
		irr::s32 id = event.GUIEvent.Caller->getID();
		switch(event.GUIEvent.EventType) {
			case irr::gui::EGET_BUTTON_CLICKED:
				return buttonClicked(id);
			default:
				_quickGame._buttonStatus = ButtonQuickGame::BUTTON_NOTHING_QUICK;
				break;
		}
	}
	return false;
}

bool QuickGame::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _KeyIsDown[keyCode];
}