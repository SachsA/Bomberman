//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// AI.hpp
//

#ifndef  AI_HPP
#define AI_HPP

#include "Errors.hpp"
#include "APlayer.hpp"
#include "World.hpp"


/*! \class ErrorsAi
 * \brief Used to handle custom error from AI.
 *
 *
 */

class ErrorsAi : public Errors {
public:
	ErrorsAi(std::ostream &, const std::string &) throw();
	virtual ~ErrorsAi(void) throw();
};

/*! \class Ai
 * \brief Everithing related to the Ai.
 *
 *
 */
class Ai : public APlayer {
public:
	Ai(std::string name, int _id, irr::core::vector2df pos, Character &character, irr::core::vector3df &rotation,
		std::unique_ptr<World> &world, std::vector<std::unique_ptr<APlayer>>& players);
	enum Action play();

private:
	Action defense();
	Action destroy();
	Action killEnemies();
	Action moveToMiddle();

	int isDestructiveBlock(int posX, int posY);
	bool dangerousZone(irr::core::vector2df const &playerPos);
	bool isBombDangerous(Bomb &, irr::core::vector2df const &);
	bool isFireDangerous(BombExplosion &, irr::core::vector2df const &);
	int findSafeDestination(int, int, int);
	int findBlockDestination(int, int, int);
	int findEnemiesDestination(int, int, int);
	int getNextEnemiesObjective(int posX, int posY, int dist);
	int getNextBlockObjective(int posX, int posY, int dist);
	int getNextSafeObjective(int posX, int posY, int dist);

	bool isEnemy(int, int);

	bool canMove();
	bool canMoveToPos(int posX, int posY);

private:
	Action _status;
	irr::core::vector2di _destination;
	std::unique_ptr<World> &_world;
	std::vector<std::unique_ptr<APlayer>>& _players;
	bool _deathCirle;
};

#endif /* end of include guard: AI_HPP */
