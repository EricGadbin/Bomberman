/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** player
*/

#include "../include/Map.hpp"
#include "../include/Ai.hpp"
#include "../include/Bomb.hpp"
#include "../include/mainDevice.hpp"
#include <irrlicht.h>

using namespace Indie;
Ai::Ai(mainDevice &start, std::string name, int playernb) : APlayer(start, name, playernb)
{
    _ai = true;
}

Ai::Ai(const IPlayer &player) : APlayer(player)
{
}

Ai::~Ai()
{
}

void Ai::start_cooldownAi()
{
    _cooldownAi = std::clock();
}

bool Ai::get_cooldownAi() const
{
    return ((std::clock() - _cooldownAi) / static_cast<double>(CLOCKS_PER_SEC) >= _cooldownDurationAi);
}

std::map<std::string,irr::EKEY_CODE> Ai::getkeyMap() const
{
    std::map<std::string,irr::EKEY_CODE> map;
    return (map);
}

void Ai::setDirection(int direction)
{
    switch (direction) {
    case 0:
        _direction = UP;
        break;
    case 1:
        _direction = DOWN;
        break;
    case 2:
        _direction = LEFT;
        break;
    case 3:
        _direction = RIGHT;
        break;
    default:
        _direction = NONE;
        break;
    }
}

int Ai::getDirection()
{
    switch (_direction) {
    case UP:
        return (0);
    case DOWN:
        return (1);
    case LEFT:
        return (2);
    case RIGHT:
        return (3);
    default:
        return (4);
    }
}

int Ai::getOppositeOfGiven(int direction)
{

    switch (direction) {
    case 0:
        return (1);
    case 1:
        return (0);
    case 2:
        return (3);
    case 3:
        return (2);
    default:
        return (4);
    }
}

int Ai::getOppositeDir()
{
    switch (_direction) {
    case UP:
        return (1);
    case DOWN:
        return (0);
    case LEFT:
        return (3);
    case RIGHT:
        return (2);
    default:
        return (4);
    }
}


int Ai::findSmallestPath(std::vector<int> lenghtsFound)
{
    if (lenghtsFound.size() == 0) {
        return (-1);
    }
    int smallest = lenghtsFound[0];
    for (int i = 1; i < lenghtsFound.size(); i++) {
        if (lenghtsFound[i] < smallest) {
            smallest = lenghtsFound[i];
        }
    }
    return (smallest);
}


int Ai::checkDirection(Indie::Map &map, std::vector<Indie::IPlayer*> &players, irr::core::vector3df pos, int length, int oldDir)
{
    if (length > 20) {
        return (-1);
    }
    map.checkForAnyObstacles(pos, 1);
    bool obstacles[] = {map.getObstaclesUp(), map.getObstaclesDown(), map.getObstaclesLeft(), map.getObstaclesRight()};
    std::vector<Indie::Bomb> *bombs;
    bool inRange[] = {false, false, false, false};

    for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer) {
        bombs = (*itPlayer)->getBombs();
        for (std::vector<Indie::Bomb>::iterator it = bombs->begin(); it != bombs->end(); ++it) {
            inRange[0] = inRange[0] || map.isInRange(irr::core::vector3df(pos.X, pos.Y, pos.Z + 1), &(*bombs)[it - bombs->begin()]);
            inRange[1] = inRange[1] || map.isInRange(irr::core::vector3df(pos.X, pos.Y, pos.Z - 1), &(*bombs)[it - bombs->begin()]);
            inRange[2] = inRange[2] || map.isInRange(irr::core::vector3df(pos.X - 1, pos.Y, pos.Z), &(*bombs)[it - bombs->begin()]);
            inRange[3] = inRange[3] || map.isInRange(irr::core::vector3df(pos.X + 1, pos.Y, pos.Z), &(*bombs)[it - bombs->begin()]);
        }
    }
    std::vector<int> lenghtsFound;
    irr::core::vector3df move[] = {irr::core::vector3df(0, 0, 1), irr::core::vector3df(0, 0, -1), irr::core::vector3df(-1, 0, 0), irr::core::vector3df(1, 0, 0)};

    for (int i = 0; i < 4; i += 1) {
        if (!obstacles[i] == true && i != oldDir && inRange[i] == false) {
            return (length);
        }
        if (!obstacles[i] == true && i != oldDir) {
            lenghtsFound.push_back(checkDirection(map, players, irr::core::vector3df(pos.X + move[i].X, pos.Y, pos.Z +move[i].Z), length + 1, getOppositeOfGiven(i)));
        }
    }
    return (findSmallestPath(lenghtsFound));
}

int Ai::getBestPath(Indie::Map &map, std::vector<Indie::IPlayer*> &players, bool *obstacles)
{
    int size = 0;
    int smallest = -1;
    int direction = 4;
    irr::core::vector3df move[] = {irr::core::vector3df(0, 0, -1), irr::core::vector3df(-1, 0, 0), irr::core::vector3df(1, 0, 0)};

    for (int i = 0; i < 4; i++) {
        if (!obstacles[i] == true) {
            size = checkDirection(map, players, irr::core::vector3df(_pos.X + move[i - 1].X, _pos.Y, _pos.Z + + move[i - 1].Z), 1, getOppositeOfGiven(i));
            if (smallest == -1) {
                smallest = size;
                direction = i;
            } else if (size != -1 && size < smallest) {
                smallest = size;
                direction = i;
            }
        }
    }
    return (direction);
}

int Ai::chooseFleeingDirection(Indie::Map &map, std::vector<Indie::IPlayer*> &players)
{
    map.checkForAnyObstacles(_pos, 1);
    bool obstacles[] = {map.getObstaclesUp(), map.getObstaclesDown(), map.getObstaclesLeft(), map.getObstaclesRight()};
    std::vector<Indie::Bomb> *bombs;
    bool inRange[] = {false, false, false, false};

    for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer) {
        bombs = (*itPlayer)->getBombs();
        for (std::vector<Indie::Bomb>::iterator it = bombs->begin(); it != bombs->end(); ++it) {
            inRange[0] = inRange[0] || map.isInRange(irr::core::vector3df(_pos.X, _pos.Y, _pos.Z + 1), &(*bombs)[it - bombs->begin()]);
            inRange[1] = inRange[1] || map.isInRange(irr::core::vector3df(_pos.X, _pos.Y, _pos.Z - 1), &(*bombs)[it - bombs->begin()]);
            inRange[2] = inRange[2] || map.isInRange(irr::core::vector3df(_pos.X - 1, _pos.Y, _pos.Z), &(*bombs)[it - bombs->begin()]);
            inRange[3] = inRange[3] || map.isInRange(irr::core::vector3df(_pos.X + 1, _pos.Y, _pos.Z), &(*bombs)[it - bombs->begin()]);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (!obstacles[i] == true && inRange[i] == false) {
            return (i);
        }
    }
    return (getBestPath(map, players, obstacles));
}

int Ai::chooseDirection(bool *walls, bool *inRange, bool *closest, bool *obstacles)
{
    bool notDeadEnd[] = {inRange[0] == false && obstacles[0] == false, inRange[1] == false && obstacles[1] == false, inRange[2] == false && obstacles[2] == false, inRange[3] == false && obstacles[3] == false};
    bool isNotStuck = notDeadEnd[0] || notDeadEnd[1] || notDeadEnd[2] || notDeadEnd[3];
    bool canDropBomb = _nb > 0 && get_cooldown() == true && isNotStuck;

    if (canDropBomb) {
        for (int i = 0; i < 4; i += 1) {
            if (!walls[i] == true && inRange[i] == false && closest[i] == true && i != getOppositeDir()) {
                return (i);
            }
        }
        for (int i = 0; i < 4; i += 1) {
            if (!walls[i] == true && inRange[i] == false && i != getOppositeDir()) {
                return (i);
            }
        }
    } else {
        for (int i = 0; i < 4; i += 1) {
            if (!obstacles[i] == true && inRange[i] == false && closest[i] == true && i != getOppositeDir()) {
                return (i);
            }
        }
        for (int i = 0; i < 4; i += 1) {
            if (!obstacles[i] == true && inRange[i] == false && i != getOppositeDir()) {
                return (i);
            }
        }
    }
    return (4);
}

int Ai::moveAi(Indie::Map &map, std::vector<Indie::IPlayer*> &players)
{
    map.checkForAnyObstacles(_pos, 1);
    bool obstacles[] = {map.getObstaclesUp(), map.getObstaclesDown(), map.getObstaclesLeft(), map.getObstaclesRight()};
    map.checkForObstacles(_pos, 1, false);
    bool walls[] = {map.getObstaclesUp(), map.getObstaclesDown(), map.getObstaclesLeft(), map.getObstaclesRight()};
    irr::core::vector3df closestPos = getClosestPlayer(players);
    bool closest[] = {closestPos.Z > _pos.Z  + 1, closestPos.Z < _pos.Z - 1, closestPos.X < _pos.X - 1, closestPos.X > _pos.X + 1};
    std::vector<Indie::Bomb> *bombs;
    bool inRange[] = {false, false, false, false};
    bool enemyFound[] = {closestPos.Z <= _pos.Z  + 2 && closestPos.Z >= _pos.Z, closestPos.Z >= _pos.Z - 2 && closestPos.Z <= _pos.Z, closestPos.X >= _pos.X - 2 && closestPos.X <= _pos.X, closestPos.X <= _pos.X + 2 && closestPos.X >= _pos.X};
    bool gotcha = (enemyFound[0] && enemyFound[2]) || (enemyFound[0] && enemyFound[3]) || (enemyFound[1] && enemyFound[2]) || (enemyFound[1] && enemyFound[3]);
    int direction;
    bool canDropBomb = _nb > 0 && get_cooldown() == true;


    for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer) {
        bombs = (*itPlayer)->getBombs();
        for (std::vector<Indie::Bomb>::iterator it = bombs->begin(); it != bombs->end(); ++it) {
            inRange[0] = inRange[0] || map.isInRange(irr::core::vector3df(_pos.X, _pos.Y, _pos.Z + 1), &(*bombs)[it - bombs->begin()]);
            inRange[1] = inRange[1] || map.isInRange(irr::core::vector3df(_pos.X, _pos.Y, _pos.Z - 1), &(*bombs)[it - bombs->begin()]);
            inRange[2] = inRange[2] || map.isInRange(irr::core::vector3df(_pos.X - 1, _pos.Y, _pos.Z), &(*bombs)[it - bombs->begin()]);
            inRange[3] = inRange[3] || map.isInRange(irr::core::vector3df(_pos.X + 1, _pos.Y, _pos.Z), &(*bombs)[it - bombs->begin()]);
        }
    }
    if ((inRange[0] == true && inRange[1] == true) || (inRange[2] == true && inRange[3] == true)) {
        _action = FLEE;
        return (4);
    }
    direction = chooseDirection(walls, inRange, closest, obstacles);
    if ((direction != 4 && obstacles[direction] == true) || (canDropBomb && gotcha == true)) {
        _action = DROP;
    }
    return (direction);

}

void Ai::chooseAction(Indie::Map &map, std::vector<Indie::IPlayer*> &players)
{
    int direction = 4;

    if (_pos.X == round(_pos.X) && _pos.Z == round(_pos.Z)) {
        if (_action == FLEE) {
            bool characterIsInRange = false;
            std::vector<Indie::Bomb> *bombs;
            for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer) {
                bombs = (*itPlayer)->getBombs();
                for (std::vector<Indie::Bomb>::iterator it = bombs->begin(); it != bombs->end(); ++it) {
                    if (map.isInRange(_pos, &(*bombs)[it - bombs->begin()]) == true) {
                        characterIsInRange = true;
                    }
                }
            }
            if (characterIsInRange == false) {
                _action = WALK;
                setDirection(4);
                return;
            }
            direction = chooseFleeingDirection(map,players);
        }
        if (_action == WALK) {
            direction = moveAi(map, players);
        }
        setDirection(direction);
    }
}

void Ai::moveplayer(mainDevice &start, MyEventReceiver *receiver, Map &map, std::vector<Indie::IPlayer*> &players)
{
    const irr::u32 now = start._device->getTimer()->getTime();
    const irr::f32 frameDeltaTime = static_cast<irr::f32>((now - _then) / 1000.f);
    irr::core::vector3df nodePosition = _skin->getPosition();
    const irr::core::vector3df savePos = _skin->getPosition();
    irr::core::vector3df rotation;
    std::vector<Indie::Bomb> bombs;
    double move = (_speed > 10) ? 0.5f : 0.2f;

    if (canMove == false || get_cooldownAi() == false) {
        _then = now;
        return;
    }
    start_cooldownAi();
    chooseAction(map, players);
    if (_action == DROP) {
        _then = now;
        return;
    }
    switch (getDirection()) {
        case 0:
            rotation = irr::core::vector3df(0,-180,0);
            nodePosition.Z += move;
            nodePosition.Z = round(nodePosition.Z * 10.f)/10.f;
            break;
        case 1:
            rotation = irr::core::vector3df(0,0,0);
            nodePosition.Z -= move;
            nodePosition.Z = round(nodePosition.Z * 10.f)/10.f;
            break;
        case 2:
            rotation = irr::core::vector3df(0, 90,0);
            nodePosition.X -= move;
            nodePosition.X = round(nodePosition.X * 10.f)/10.f;
            break;
        case 3:
            rotation = irr::core::vector3df(0,-90,0);
            nodePosition.X += move;
            nodePosition.X = round(nodePosition.X * 10.f)/10.f;
            break;
        default:
            PlayAnimation(0);
            _then = now;
            return;
    }
    if (checkMove(map, players, nodePosition, now)) {
        moveSkin(rotation, nodePosition, savePos, now);
    }
}


void Ai::dropBomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, MyEventReceiver *receiver)
{
    if (_action == DROP) {
            irr::core::vector3df nodePosition = _skin->getPosition();
            nodePosition.X = round(nodePosition.X);
            nodePosition.Z = round(nodePosition.Z);
            Indie::Bomb bomb(sceneManager, driver, nodePosition, getRange());
            _nb -= 1;
            _bombs.push_back(bomb);
            start_cooldown();
            _action = FLEE;
        }
}
