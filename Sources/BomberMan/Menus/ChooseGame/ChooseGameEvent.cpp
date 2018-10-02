/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ChooseGameEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "ChooseGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

ChooseGame::EventReceiver::EventReceiver(irr::IrrlichtDevice *device,
					 ChooseGame &choose)
	: _device(device), _choose(choose)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool ChooseGame::EventReceiver::buttonClicked(irr::s32 id)
{
	switch(id) {
		case ButtonChooseGame::BUTTON_NEW_CHOOSE:
			_choose._buttonStatus = ButtonChooseGame::BUTTON_NEW_CHOOSE;
			return true;
		case ButtonChooseGame::BUTTON_QUICK_CHOOSE:
			_choose._buttonStatus = ButtonChooseGame::BUTTON_QUICK_CHOOSE;
			return true;
		default:
			_choose._buttonStatus = ButtonChooseGame::BUTTON_NOTHING_CHOOSE;
			return false;
	}
	return false;
}

void ChooseGame::EventReceiver::refresh()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool ChooseGame::EventReceiver::OnEvent(const irr::SEvent &event)
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
				_choose._buttonStatus = ButtonChooseGame::BUTTON_NOTHING_CHOOSE;
				break;
		}
	}
	return false;
}

bool ChooseGame::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _KeyIsDown[keyCode];
}