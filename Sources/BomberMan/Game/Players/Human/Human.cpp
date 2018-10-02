//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Character.cpp
//

#include "Human.hpp"

Human::Human(std::string name, int id, irr::core::vector2df pos,
	Character& character, std::vector<irr::EKEY_CODE> controls, GameGfx::EventReceiver& receiver, irr::core::vector3df& rotation)
	:	APlayer(name, id, HUMAN, pos, character, rotation), _controls(controls), _receiver(receiver)
{
}

enum Action Human::play()
{
	for (auto control : _controls) {
		if (_receiver.IsKeyDown(control)) {
			switch (control) {
				case irr::KEY_KEY_A:
				case irr::KEY_RSHIFT:
				case irr::KEY_KEY_I:
				case irr::KEY_KEY_T:
					return PLACE_BOMB;
				case irr::KEY_KEY_Z:
				case irr::KEY_UP:
				case irr::KEY_KEY_O:
				case irr::KEY_KEY_Y:
					return MOVE_UP;
				case irr::KEY_KEY_S:
				case irr::KEY_DOWN:
				case irr::KEY_KEY_L:
				case irr::KEY_KEY_H:
					return MOVE_DOWN;
				case irr::KEY_KEY_Q:
				case irr::KEY_LEFT:
				case irr::KEY_KEY_K:
				case irr::KEY_KEY_G:
					return MOVE_LEFT;
				case irr::KEY_KEY_D:
				case irr::KEY_RIGHT:
				case irr::KEY_KEY_M:
				case irr::KEY_KEY_J:
					return MOVE_RIGHT;
				default:
					return NO;

			}
		}
	}
	return NO;
}
