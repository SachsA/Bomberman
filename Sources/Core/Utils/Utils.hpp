/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Created by Kellian CIPIERRE,
*/
#ifndef INDIE_STUDIO_UTILS_HPP
#define INDIE_STUDIO_UTILS_HPP

#include <unordered_map>
#include <iostream>

/*! \namespace Utils
 * \brief namespace containing some usefull template function which are not part of an object.
 *
 *
 */
namespace Utils {

bool strIsNumber(std::string const &);

/*! \class ErrorsABonus
 * \brief Used to get a key from a map.
 *
 *
 */
template<typename T, typename U>
T getMinMapKey(std::unordered_map<T, U> const &data)
{
	T minKey = data.begin()->first;
	U minValue = data.begin()->second;

	auto pos = data.begin();
	while (pos != data.end()) {
		if ((pos->second >= 0 && pos->second < minValue) ||
			(pos->second >= 0 && minValue < 0)) {
			minValue = pos->second;
			minKey = pos->first;
		}
		pos++;
	}
	return minKey;
}

/*! \class ErrorsABonus
 * \brief Used to get the minimal value in a map.
 *
 *
 */
template<typename T, typename U>
U getMinMapValue(std::unordered_map<T, U> const &data)
{
	T minKey = data.begin()->first;
	U minValue = data.begin()->second;

	auto pos = data.begin();
	while (pos != data.end()) {
		if ((pos->second >= 0 && pos->second < minValue) ||
		(pos->second >= 0 && minValue < 0)) {
			minValue = pos->second;
			minKey = pos->first;
		}
		pos++;
	}
	return minValue;
}

}

#endif //INDIE_STUDIO_UTILS_HPP
