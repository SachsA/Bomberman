/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/

#include <fstream>
#include <iostream>
#include "BomberManConfig.hpp"

BomberManConfig::BomberManConfig(std::string const &filePath)
	: _filePath(filePath), earthRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f)),
	earthPosition(irr::core::vector3df(0.0f, -5.0f, 0.0f)),
	earthRadius(40.0f)
{
	#ifdef __unix__
		_volumes.emplace(SoundType::MUSIC, 100);
		_volumes.emplace(SoundType::MENUS, 100);
		_volumes.emplace(SoundType::GAME, 100);
		_soundStatus.emplace(SoundType::MUSIC, true);
		_soundStatus.emplace(SoundType::MENUS, true);
		_soundStatus.emplace(SoundType::GAME, true);
	#endif
	parseFile();
}

std::string BomberManConfig::cleanStr(std::string &original)
{
	std::string cleanedStr;
	unsigned int idx = 0;

	while (idx < original.length()) {
		if (original[idx] != ' ' && original[idx] != '\t')
			cleanedStr += original[idx];
		idx++;
	}
	return cleanedStr;
}

void BomberManConfig::insertValues(std::string const &inputLine)
{
	std::string keyStr;
	std::string valueStr;
	auto sepPosition = inputLine.find('=');

	if (sepPosition != std::string::npos) {
		keyStr = inputLine.substr(0, sepPosition);
		valueStr = inputLine.substr(sepPosition + 1, inputLine.length());
	}
	if (keyStr.length() > 0 && valueStr.length() > 0) {
		_confValues[keyStr] = valueStr;
	}
}

std::unordered_map<std::string, std::string> const &BomberManConfig::parseFile()
{
	std::string str = {};
	std::ifstream ifs(_filePath);

	if (!ifs.is_open())
		throw ErrorsConfig(std::cerr, "ConfigIndie.cfg not found");
	while (std::getline(ifs, str)) {
		str = cleanStr(str);
		if (str.length() > 0 && str.at(0) != '#')
			insertValues(str);
	}
	return _confValues;
}

void BomberManConfig::setConfFile(std::string const &filePath)
{
	_filePath = filePath;
}

std::unordered_map<std::string, std::string> BomberManConfig::getConf()
{
	return _confValues;
}

std::string BomberManConfig::getConf(std::string const &key)
{
	if (_confValues.size() && _confValues.find(key) == _confValues.end()) {
		return "";
	}
	return _confValues[key];
}

#ifdef __unix__
std::unordered_map<SoundType, float> &BomberManConfig::getVolumes()
{
	return _volumes;
}

float &BomberManConfig::getVolumes(SoundType key)
{
	return _volumes[key];
}

void BomberManConfig::insertMusic(std::string const &key, std::string const &path)
{
	musics.emplace(key, std::make_unique<sf::Music>());
	if (!musics[key]->openFromFile(path)) {
		throw ErrorsSounds(std::cerr, "cannot load sound : " + key);
	} else {
		musics[key]->setLoop(true);
	}
}

void BomberManConfig::launchMusic(std::string const &key)
{
	if (musics.find(key) == musics.end())
		throw ErrorsSounds(std::cerr, "cannot launch music : " + key);

	if (!_soundStatus[MUSIC])
		return;

	auto music = musics.begin();
	while (music != musics.end()) {
		music->second->stop();
		music++;
	}

	musics[key]->play();
}

void BomberManConfig::pauseMusic(std::string const &key)
{
	if (musics.find(key) == musics.end())
		throw ErrorsSounds(std::cerr, "cannot paus sound : " + key);
	musics[key]->pause();
}

sf::Music::Status BomberManConfig::getMusicStatus(std::string const &key)
{
	if (musics.find(key) == musics.end())
		throw ErrorsSounds(std::cerr, "cannot get sound : " + key);
	return musics[key]->getStatus();
}

void BomberManConfig::insertSound(SoundType type, std::string const &key, std::string const &path)
{
	if (type == SoundType::MENUS) {
		menusSounds.emplace(key, std::make_unique<sf::Music>());
		if (!menusSounds[key]->openFromFile(path)) {
			throw ErrorsSounds(std::cerr, "cannot insert sound : " + key);
		}
	} else if (type == SoundType::GAME) {
		gameSounds.emplace(key, std::make_unique<sf::Music>());
		if (!gameSounds[key]->openFromFile(path)) {
			throw ErrorsSounds(std::cerr, "cannot insert sound : " + key);
		}
	} else {
		musics.emplace(key, std::make_unique<sf::Music>());
		if (!musics[key]->openFromFile(path)) {
			throw ErrorsSounds(std::cerr, "cannot insert sound : " + key);
		}
	}
}

void BomberManConfig::launchSound(SoundType type, std::string const &key)
{
	if (!_soundStatus[type])
		return;
	if (type == SoundType::MENUS) {
		if (menusSounds.find(key) == musics.end())
			throw ErrorsSounds(std::cerr, "cannot launch sound : " + key);
		menusSounds[key]->stop();
		menusSounds[key]->play();
	} else if (type == SoundType::GAME) {
		if (gameSounds.find(key) == musics.end())
			throw ErrorsSounds(std::cerr, "cannot launch sound : " + key);
		gameSounds[key]->stop();
		gameSounds[key]->play();
	} else {
		if (musics.find(key) == musics.end())
			throw ErrorsSounds(std::cerr, "cannot launch sound : " + key);
		musics[key]->pause();
		musics[key]->play();
	}
}

float BomberManConfig::getActiveVolume(SoundType type)
{
	if (type == SoundType::MENUS && menusSounds.size()) {
		return menusSounds.begin()->second->getVolume();
	} else if (type == SoundType::GAME && gameSounds.size()) {
		return gameSounds.begin()->second->getVolume();
	} else if (type == SoundType::MUSIC && musics.size()) {
		return musics.begin()->second->getVolume();
	} else
		return (-1);
}

void BomberManConfig::setVolumes(SoundType type, irr::s32 const &pos)
{
	if (type == SoundType::MENUS) {
		updateVolumes(menusSounds, pos);
	} else if (type == SoundType::GAME) {
		updateVolumes(gameSounds, pos);
	} else {
		updateVolumes(musics, pos);
	}
}

void BomberManConfig::updateVolumes(std::unordered_map<std::string, std::unique_ptr<sf::Music>> &sounds,
	irr::s32 const &pos
)
{
	auto music = sounds.begin();
	while (music != sounds.end()) {
		if (music->second->getStatus() == sf::Music::Paused)
			music->second->play();
		music->second->setVolume(pos);
		music++;
	}
}

void BomberManConfig::stopSound(SoundType type, std::string const &key)
{
	if (type == SoundType::MENUS) {
		menusSounds[key]->stop();
	} else if (type == SoundType::GAME) {
		gameSounds[key]->stop();
	} else {
		musics[key]->stop();
	}
}

void BomberManConfig::setSoundStatus(SoundType type, bool status)
{
	_soundStatus[type] = status;
}

bool BomberManConfig::getSoundStatus(SoundType type)
{
	return _soundStatus[type];
}
#endif