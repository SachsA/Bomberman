//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// header for World class
//

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <memory>
#include <unordered_map>
#include "Map.hpp"
#include "ABonus.hpp"
#include "APlayer.hpp"

/*! \class ErrorsWorld
 * \brief Used to handle custom error from World.
 *
 *
 */
class ErrorsWorld: public Errors {
public:
	ErrorsWorld(std::ostream &, const std::string &) throw();
	virtual ~ErrorsWorld(void) throw();
};

/*! \class World
 * \brief Class containing everything about the game itself (bombs, bonus, player, bomb)
 *
 *
 */
class World {
public:
	World(enum MapSize mapSize, BomberManConfig &config);
	~World() = default;

	void placeBomb(irr::core::vector2df pos, size_t bombRange, int id,
		       irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver);
	enum Action updatePlayerData(std::unique_ptr<APlayer> &player,
				     enum Action action, irr::scene::ISceneManager* smgr,
				     irr::video::IVideoDriver* driver);
	void updateMap(std::unique_ptr<Bomb> &bomb, irr::scene::ISceneManager* smgr,
		       irr::video::IVideoDriver* driver);
	bool noBombThere(irr::core::vector2df pos);
	bool enoughBomb(std::unique_ptr<APlayer> &player);
	bool posHasBonus(irr::core::vector2df pos);
	void updatePlayerStat(std::unique_ptr<ABonus>& bonus,
				     std::unique_ptr<APlayer> &player);
	void checkNewPos(std::unique_ptr<APlayer>& player, irr::core::vector2df pos);
	void removeBonus(irr::core::vector2df pos);

	std::unordered_map<int, size_t>& getScores();
	void getBonus(irr::core::vector2df pos, std::unique_ptr<APlayer>& player);
	std::vector<std::unique_ptr<Bomb>>& getBomb();
	std::vector<std::unique_ptr<BombExplosion>>& getExplosion();
	std::vector<std::unique_ptr<ABonus>>& getBonus();
	std::vector<std::vector<std::unique_ptr<ABlock>>>& getMap();
	bool isABomb(irr::core::vector2df pos, enum Action action);
	size_t& getMapSize();

private:
	BomberManConfig &_config;
	size_t _bombRange;

	void generateBonus();
	void generateBonus(int nbrUltimate, enum BonusType type);
	void addBonus(size_t posX, size_t posY, enum BonusType type);
	bool caseHasBonus(size_t posX, size_t posY);

	std::vector<std::unique_ptr<Bomb>> _bombs;
	std::vector<std::unique_ptr<ABonus>> _bonus;
	std::unique_ptr<Map> _map;
};

#endif // WORLD_HPP_
