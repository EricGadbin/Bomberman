 /*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Map
*/

#ifndef MAP_H
# define MAP_H

#include "includes.hpp"
#include "mainDevice.hpp"
#include "Bonus.hpp"

namespace Indie {

class IPlayer;
class Bonus;

class Map {
    public:
        Map(irr::scene::ISceneManager* sceneManager, unsigned int size, irr::video::IVideoDriver* driver);
        ~Map();

        irr::scene::IMeshSceneNode* getBlock(irr::core::vector3df pos);
        bool getObstaclesLeft();
        bool getObstaclesRight();
        bool getObstaclesUp();
        bool getObstaclesDown();

        int create_save(std::vector<IPlayer*>);
        int load_save(std::string name, std::vector<IPlayer*> &players, mainDevice &start);
        bool checkCollision(irr::core::vector3df &nodePosition);
        bool checkCollision(irr::core::vector3df &nodePosition, IPlayer *player);

        std::vector<Indie::Block>::iterator removeBlock(std::vector<Indie::Block>::iterator &it, mainDevice &start);
        unsigned int removeBlocks(irr::core::vector3df nodePosition, Bomb *bomb, mainDevice &start);
        void checkForObstacles(irr::core::vector3df nodePosition, int range, bool checkBlocks);
        void checkForAnyObstacles(irr::core::vector3df nodePosition, int range);

        void isInTheWay(irr::core::vector3df nodePos, irr::core::vector3df bloskPos, int tmp);
        bool isInRange(irr::core::vector3df playerPos, Bomb *bomb);

    private:
        std::vector<Indie::wallBlock> _walls;
        std::vector<Indie::wallBlock> _floor;
        std::vector<Indie::Block> _blocks;
        std::vector<Indie::Bonus> _bonus;
        unsigned int _size = 0;
        bool _left;
        bool _right;
        bool _down;
        bool _up;
};

};

#endif
