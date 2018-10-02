/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** PrincipalMenuGameEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "PrincipalMenuGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

PrincipalMenuGame::EventReceiver::EventReceiver(irr::IrrlichtDevice *device,
						PrincipalMenuGame &principal)
	: _device(device), _principal(principal)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool PrincipalMenuGame::EventReceiver::buttonClicked(irr::s32 id)
{
	switch(id) {
		case ButtonPrincipal::BUTTON_QUIT_PRINCIP:
			_principal._buttonStatus = ButtonPrincipal::BUTTON_QUIT_PRINCIP;
			return true;
		case ButtonPrincipal::BUTTON_SETTINGS_PRINCIP:
			_principal._buttonStatus = ButtonPrincipal::BUTTON_SETTINGS_PRINCIP;
			return true;
		case ButtonPrincipal::BUTTON_PLAY_PRINCIP:
			_principal._buttonStatus = ButtonPrincipal::BUTTON_PLAY_PRINCIP;
			return true;
		default:
			_principal._buttonStatus = ButtonPrincipal::BUTTON_NOTHING_PRINCIP;
			return false;
	}
	return false;
}

void PrincipalMenuGame::EventReceiver::refresh()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;

}

bool PrincipalMenuGame::EventReceiver::OnEvent(const irr::SEvent &event)
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
				_principal._buttonStatus = ButtonPrincipal::BUTTON_NOTHING_PRINCIP;
				break;
		}
	}
	return false;
}

bool PrincipalMenuGame::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _KeyIsDown[keyCode];
}