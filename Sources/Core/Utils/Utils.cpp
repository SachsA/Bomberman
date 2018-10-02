/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#include <string>
#include "Utils.hpp"

namespace Utils {

bool strIsNumber(std::string const &str)
{
	try {
		std::stoi(str);
	} catch (...) {
		return false;
	}
	return true;
}

}