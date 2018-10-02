//
// EPITECH PROJECT, 2018
// cpp_indie
// File description:
// Map handling class implementation
//

#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "BombExplosion.hpp"
#include "Errors.hpp"
#include "ABlock.hpp"
#include "Bomb.hpp"
#include "Errors.hpp"
#include "BomberManConfig.hpp"

enum MapSize
{
	SMALL,
	MEDIUM,
	LARGE
};

enum Player
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4
};

/*! \class ErrorsMap
 * \brief Used to handle custom error from Map.
 *
 *
 */
class ErrorsMap: public Errors {
public:
	ErrorsMap(std::ostream &, const std::string &) throw();
	virtual ~ErrorsMap(void) throw();
};

/*! \class Map
 * \brief Everything related to the map handling (creation/update/...)
 *
 *
 */
class Map {
public:
	Map(enum MapSize mapSize, BomberManConfig &conf);
	~Map() = default;

	void initMap();
	std::vector<std::vector<std::unique_ptr<ABlock>>>& getMap();
	std::vector<std::unique_ptr<BombExplosion>>& getExplosion();
	void initData();
	void updateMap(std::unique_ptr<Bomb> &bomb,
		irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
	bool isABlock(irr::core::vector2di pos);
	bool isInMap(irr::core::vector2di pos);

	size_t& getSize();
	size_t getNbrBox();
	std::unordered_map<int, size_t>& getScores();

private:
	BomberManConfig &_conf;

	enum MapSize _mapSize;
	size_t _width;
	size_t _height;
	size_t _nbrPlayer;
	size_t _nbrWall;
	size_t _nbrBox;
	irr::core::vector2d<int> _player1Pos;
	irr::core::vector2d<int> _player2Pos;
	irr::core::vector2d<int> _player3Pos;
	irr::core::vector2d<int> _player4Pos;

	void placeWall(std::vector<std::vector<int>> map);
	void placeDestructiveBlock();
	void resizeMap();
	void initScores();
	void initPlayerPos();
	bool isFreeSpot(size_t posX, size_t posY);
	bool isPlayerPos(int posX, int posY);
	bool isInSpawn(int posX, int posY);
	bool isInPlayerSpawn(enum Player player, int posX, int posY);
	void updateUp(size_t range, irr::core::vector2df, int id,
		irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
	void updateDown(size_t range, irr::core::vector2df, int id,
		irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
	void updateLeft(size_t range, irr::core::vector2df, int id,
		irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
	void updateRight(size_t range, irr::core::vector2df, int id,
		irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
	void clearMap();

	std::vector<std::vector<std::unique_ptr<ABlock>>> _map;
	std::vector<std::unique_ptr<BombExplosion>> _fire;
	std::unordered_map<int, size_t> _scores;
};

#endif // MAP_HPP_
