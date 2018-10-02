/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** GameGfxEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "GameGfx.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

GameGfx::EventReceiver::EventReceiver(irr::IrrlichtDevice *device,
				      GameGfx &gameGfx)
	: _device(device), _gameGfx(gameGfx)
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool GameGfx::EventReceiver::buttonClicked(irr::s32 id)
{
	switch(id) {
		default:
			_gameGfx._buttonStatus = ButtonGameGfx::BUTTON_NOTHING_GAMEGFX;
			return false;
	}
	return false;
}

void GameGfx::EventReceiver::refresh()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;

}

bool GameGfx::EventReceiver::OnEvent(const irr::SEvent &event)
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
				_gameGfx._buttonStatus = ButtonGameGfx::BUTTON_NOTHING_GAMEGFX;
				break;
		}
	}
	return false;
}



bool GameGfx::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{

	return _KeyIsDown[keyCode];
}
