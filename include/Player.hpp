/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Player
*/

#ifndef PLAYER_H
# define PLAYER_H

#include "APlayer.hpp"
#include "../include/mainDevice.hpp"

namespace Indie {

class Map;

class Player : public APlayer {
    public:
        Player(mainDevice &start, std::string name, int playernb);
        Player(const Player &player);
        ~Player();
        std::map<std::string,irr::EKEY_CODE> getkeyMap() const;


        void moveplayer(mainDevice &, MyEventReceiver *receiver, Map &map, std::vector<Indie::IPlayer*> &players);
        void dropBomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, MyEventReceiver *receiver);

    private:
        std::map<std::string,irr::EKEY_CODE> _keyMap;

};

};

#endif
