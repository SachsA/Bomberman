/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** NewGameEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "NewGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

NewGame::EventReceiver::EventReceiver(irr::IrrlichtDevice *device,
				      NewGame &newGame)
	: _device(device), _newGame(newGame)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool NewGame::EventReceiver::buttonClicked(irr::s32 id)
{
	switch(id) {
		case ButtonNewGame::BUTTON_RIGHT_NEW:
			_newGame._buttonStatus = ButtonNewGame::BUTTON_RIGHT_NEW;
			return true;
		case ButtonNewGame::BUTTON_LEFT_NEW:
			_newGame._buttonStatus = ButtonNewGame::BUTTON_LEFT_NEW;
			return true;
		case ButtonNewGame::BUTTON_START_NEW:
			_newGame._buttonStatus = ButtonNewGame::BUTTON_START_NEW;
			return true;
		default:
			_newGame._buttonStatus = ButtonNewGame::BUTTON_NOTHING_NEW;
			return false;
	}
	return false;
}

void NewGame::EventReceiver::refresh()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;

}

bool NewGame::EventReceiver::OnEvent(const irr::SEvent &event)
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
				_newGame._buttonStatus = ButtonNewGame::BUTTON_NOTHING_NEW;
				break;
		}
	}
	return false;
}

bool NewGame::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _KeyIsDown[keyCode];
}