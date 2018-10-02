/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** ErrorsABlock.cpp for cpp_indie_studio
*/

#include "ABlock.hpp"

ErrorsABlock::ErrorsABlock(std::ostream &os, const std::string &message) throw()
	: Errors(os, "ABlock: " + message)
{}

ErrorsABlock::~ErrorsABlock(void) throw()
{}
