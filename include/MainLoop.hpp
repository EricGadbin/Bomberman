/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** mainDevice
*/

#ifndef MAINLOOP_H
# define MAINLOOP_H

#include "includes.hpp"
#include "Ai.hpp"
#include "Map.hpp"
#include "mainDevice.hpp"
#include "CreateGame.hpp"
#include "IPlayer.hpp"
#include "Bomb.hpp"
#include "MainMenu.hpp"
#include "endMenu.hpp"
#include "pauseMenu.hpp"
#include "MainLoop.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <irrlicht.h>

class MainLoop {
    public:

    MainLoop();
    ~MainLoop();
    void GameLoop(mainDevice &start, std::string);
    void setRestart(mainDevice &start, sf::Music &music);
    void checkStats(std::vector<Indie::IPlayer*> bombers, mainDevice &start, Indie::Map &map, CreateGame &game, Indie::pauseMenu &pause);
    void setBasics(mainDevice &start, sf::Music &music, CreateGame &game);

};
#endif
