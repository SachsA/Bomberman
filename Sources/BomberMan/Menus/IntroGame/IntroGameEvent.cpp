/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** IntroGameEvent.cpp for cpp_indie_studio
*/

#include <iostream>
#include "IntroGame.hpp"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "Irrlicht.lib")
	#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

IntroGame::EventReceiver::EventReceiver()
{
	for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
		_KeyIsDown[i] = false;
}

bool IntroGame::EventReceiver::OnEvent(const irr::SEvent &event)
{
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		_KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	return false;
}

bool IntroGame::EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
	return _KeyIsDown[keyCode];
}