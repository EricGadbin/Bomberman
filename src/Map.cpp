/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Map
*/

#include "../include/IPlayer.hpp"
#include "../include/Map.hpp"
#include "../include/wallBlock.hpp"
#include "../include/Block.hpp"
#include "../include/includes.hpp"
#include "../include/Player.hpp"
#include "../include/Ai.hpp"

using namespace Indie;

Map::Map(irr::scene::ISceneManager* sceneManager, unsigned int size, irr::video::IVideoDriver* driver)
{
    _size = size;
    srand(time(NULL));
    for (int i = 0; i < size + 1; i++) {
        for (int j = 0; j < size + 1; j++) {
            if ((i % 2 == 0 && j % 2 == 0) || i == 0 || i == size || j == 0 || j == size) {
                Indie::wallBlock block(irr::core::vector3df(i, 0, j), sceneManager, true, driver);
                _walls.push_back(block);
            } else if (((i > 3 && i < size - 3) || (j > 3 && j < size - 3)) && (rand() % 2) == 0) {
                Indie::Block breakable_block(irr::core::vector3df(i, 0, j), sceneManager, driver);
                _blocks.push_back(breakable_block);
            }
            Indie::wallBlock floor(irr::core::vector3df(i, -1, j), sceneManager, false, driver);
            _floor.push_back(floor);
        }
    }
    _blocks.push_back(Block(irr::core::vector3df(100, 0, 100), sceneManager, driver));
    _bonus.push_back(Bonus(Bonus::wUP, irr::core::vector3df(101, 0, 101), sceneManager, driver));
}

Map::~Map()
{
}

bool Map::getObstaclesLeft()
{
    return (_left);
}

bool Map::getObstaclesRight()
{
    return (_right);
}

bool Map::getObstaclesUp()
{
    return (_up);
}

bool Map::getObstaclesDown()
{
    return (_down);
}

std::vector<std::string> split_string(std::string str, std::string del)
{
    size_t pos = 0;
    std::string token;
    std::vector<std::string> tab;

    while ((pos = str.find(del)) != std::string::npos) {
        token = str.substr(0, pos);
        tab.push_back(token);
        str.erase(0, pos + del.length());
    }
    tab.push_back(str);
    return (tab);
}

void load_player(Indie::IPlayer *ai, std::ifstream *file, mainDevice &start)
{
    static int ind = 0;
    std::string str = "";
    std::vector<std::string> tab;
    std::vector<std::string>::iterator i;

    getline(*file, str);
    tab = split_string(str, ",");
    i = tab.begin();
    ai->setSkin(start, ind + 1);
    ai->setPos(irr::core::vector3df(atof(i[0].c_str()), atof(i[1].c_str()), atof(i[2].c_str())));
    getline(*file, str);
    ai->setSpeed(atof(str.c_str()));
    getline(*file, str);
    ai->setRange(atoi(str.c_str()));
    getline(*file, str);
    ai->setBombNb(atoi(str.c_str()));
    getline(*file, str);
    ai->setScore(atoi(str.c_str()));
    getline(*file, str);
    ai->setAlive(((str == "1") ? false : true));
    getline(*file, str);
    ai->setWallpass(((str == "1") ? false : true));
    getline(*file, str);
    ind = (ind == 3) ? 0 : ind + 1;
}

void load_bomber(std::vector<IPlayer*> &players, std::ifstream *file, mainDevice &start)
{
    std::string str = "";
    std::vector<std::string> tab;
    std::vector<std::string>::iterator i;
    Indie::Ai *ai;
    Indie::APlayer *player;
    static int ind = 0;

    getline(*file, str);
    if (str == "1") {
        ai = new Indie::Ai(start, "bob", ind + 1);
        load_player(ai, file, start);
        players.push_back(ai);
        ind = (ind == 3) ? 0 : ind + 1;
    } else {
        player = new Indie::Player(start, "bob", ind + 1);
        load_player(player, file, start);
        players.push_back(player);
        ind = (ind == 3) ? 0 : ind + 1;
    }
}

int Map::load_save(std::string name, std::vector<IPlayer*> &players, mainDevice &start)
{
    std::ifstream file("../save/" + name, std::ios::in);
    std::string str = "";
    std::vector<std::string> tab;
    std::vector<std::string>::iterator i;

    if (!file)
        return (1);

    if (_blocks.size() != 0) {
        for (std::vector<Indie::Block>::iterator it = _blocks.begin(); it != _blocks.end(); it++)
            it->getCube()->remove();
       _blocks.clear();
    }
    getline(file, str);
    while (str != "------") {
        tab = split_string(str, ",");
        i = tab.begin();
        Indie::Block breakable_block(irr::core::vector3df(atof(i[0].c_str()), 0, atof(i[2].c_str())), start._sceneManager, start._driver);
        _blocks.push_back(breakable_block);
        getline(file, str);
    }
    for (std::vector<Indie::IPlayer*> ::iterator it = players.begin(); it !=players.end(); ++it)
        (*it)->getSkin()->remove();
    players.clear();
    load_bomber(players, &file, start);
    load_bomber(players, &file, start);
    load_bomber(players, &file, start);
    load_bomber(players, &file, start);
    file.close();
    return (0);
}


bool Map::checkCollision(irr::core::vector3df &nodePosition, IPlayer *player)
{
    irr::core::vector3df block_pos;
    irr::core::vector3df escape;

    for (std::vector<Indie::wallBlock>::iterator it = _walls.begin(); it != _walls.end(); ++it) {
        if (it->checkCollision(nodePosition)) {
            escape = player->getPos();
            block_pos = it->getPos();
            if (block_pos.Z - 0.3 > escape.Z && (player->getSkin()->getRotation() == irr::core::vector3df(0,-90,0) || player->getSkin()->getRotation() == irr::core::vector3df(0,90,0))) {
                escape.Z -= 0.1;
                player->setPos(escape);
            } else if (block_pos.Z + 0.3 < escape.Z && (player->getSkin()->getRotation() == irr::core::vector3df(0,-90,0) || player->getSkin()->getRotation() == irr::core::vector3df(0,90,0))) {
                escape.Z += 0.1;
                player->setPos(escape);
            } else if (block_pos.X - 0.3 > escape.X && (player->getSkin()->getRotation() == irr::core::vector3df(0,-180,0) || player->getSkin()->getRotation() == irr::core::vector3df(0,0,0))) {
                escape.X -= 0.1;
                player->setPos(escape);
            } else if (block_pos.X + 0.3 < escape.X && (player->getSkin()->getRotation() == irr::core::vector3df(0,-180,0) || player->getSkin()->getRotation() == irr::core::vector3df(0,0,0))) {
                escape.X += 0.1;
                player->setPos(escape);
            }
            return (true);
        }
    }
    if (_blocks.size() != 0) {
        for (std::vector<Indie::Block>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
            if (it->checkCollision(nodePosition)) {
                return (true);
            }
        }
    }
    if (_bonus.size() != 0) {
        for (std::vector<Indie::Bonus>::iterator it = _bonus.begin(); it != _bonus.end();) {
            if (it->checkCollision(nodePosition, player)) {
                it->_block.getCube()->remove();
                it = _bonus.erase(it);
                return false;
            } else {
                ++it;
            }
        }
    }
    return (false);
}

void Map::isInTheWay(irr::core::vector3df nodePosition, irr::core::vector3df block_pos, int tmp)
{
    if (block_pos.Z == nodePosition.Z && block_pos.X == nodePosition.X - tmp) {
        _left = true;
    }
    if (block_pos.Z == nodePosition.Z && block_pos.X == nodePosition.X + tmp) {
        _right = true;
    }
    if (block_pos.X == nodePosition.X && block_pos.Z == nodePosition.Z - tmp) {
        _down = true;
    }
    if (block_pos.X == nodePosition.X && block_pos.Z == nodePosition.Z + tmp) {
        _up = true;
    }
}

void Map::checkForObstacles(irr::core::vector3df nodePosition, int range, bool checkBlocks)
{
    irr::core::vector3df block_pos;

    _left = false;
    _right = false;
    _down = false;
    _up = false;
    for (int tmp = 1; tmp <= range; ++tmp) {
        if (!checkBlocks && _walls.size() > 0) {
            for (std::vector<Indie::wallBlock>::iterator it = _walls.begin(); it != _walls.end(); ++it) {
                isInTheWay(nodePosition, it->getPos(), tmp);
            }
        } else if (checkBlocks && _blocks.size() > 0){
            for (std::vector<Indie::Block>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
                isInTheWay(nodePosition, it->getPos(), tmp);
            }
        }
    }
}


void Map::checkForAnyObstacles(irr::core::vector3df nodePosition, int range)
{
    irr::core::vector3df block_pos;

    _left = false;
    _right = false;
    _down = false;
    _up = false;
    for (int tmp = 1; tmp <= range; ++tmp) {
        if (_walls.size() > 0) {
            for (std::vector<Indie::wallBlock>::iterator it = _walls.begin(); it != _walls.end(); ++it) {
                isInTheWay(nodePosition, it->getPos(), tmp);
            }
            for (std::vector<Indie::Block>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
                isInTheWay(nodePosition, it->getPos(), tmp);
            }
        }
    }
}

std::vector<Indie::Block>::iterator Map::removeBlock(std::vector<Indie::Block>::iterator &it, mainDevice &start)
{
    int rng = rand() % 100;
    Bonus bonus;

    if (rng < 4)
        _bonus.push_back(Bonus(Bonus::wUP, it->getPos(), start._sceneManager, start._driver));
    else if (rng < 10)
        _bonus.push_back(Bonus(Bonus::sUP, it->getPos(), start._sceneManager, start._driver));
    else if (rng < 16)
        _bonus.push_back(Bonus(Bonus::bUP, it->getPos(), start._sceneManager, start._driver));
    else if (rng < 25)
        _bonus.push_back(Bonus(Bonus::fUP, it->getPos(), start._sceneManager, start._driver));
    it->getCube()->remove();
    it = _blocks.erase(it);
    return _blocks.begin();
}

unsigned int Map::removeBlocks(irr::core::vector3df nodePosition, Bomb *bomb, mainDevice &start)
{
    irr::core::vector3df block_pos;
    unsigned int addToScore = 0;

    for (std::vector<Indie::Bonus>::iterator it = _bonus.begin(); it != _bonus.end();) {
        if (isInRange(it->getPos(), bomb)) {
            it->_block.getCube()->remove();
            it = _bonus.erase(it);
            return false;
        } else {
            ++it;
        }
    }
    for (std::vector<Indie::Block>::iterator it = _blocks.begin(); it != _blocks.end(); ++it) {
        if (isInRange(it->getPos(), bomb)) {
            it = removeBlock(it, start);
            ++addToScore;
        }
    }
    return (addToScore);
}

bool Map::isInRange(irr::core::vector3df playerPos, Bomb *bomb)
{
    float PPosX = playerPos.X + 0.5;
    float PPosZ = playerPos.Z + 0.5;
    float BPosX = bomb->getPos().X;
    float BPosZ = bomb->getPos().Z;

    if ((BPosZ <= PPosZ && BPosZ + 1 >= PPosZ && BPosX <= PPosX && BPosX + bomb->_rightRange + 1 >= PPosX) || (BPosZ <= PPosZ && BPosZ + 1 >= PPosZ && BPosX >= PPosX && BPosX - bomb->_leftRange <= PPosX) || (BPosX <= PPosX && BPosX + 1 >= PPosX && BPosZ <= PPosZ && BPosZ + bomb->_upRange + 1 >= PPosZ) || (BPosX <= PPosX && BPosX + 1 >= PPosX && BPosZ >= PPosZ && BPosZ - bomb->_downRange <= PPosZ))
        return (true);
    return (false);
}
