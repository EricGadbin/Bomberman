/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Map
*/

#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "includes.hpp"
#include "Map.hpp"
#include "mainDevice.hpp"
#include "IPlayer.hpp"
#include "Bomb.hpp"
#include "MainMenu.hpp"

class CreateGame {
    public:
        CreateGame(float x1, float y1, float z1);
        ~CreateGame();

        std::vector<Indie::IPlayer*> createPlayer(mainDevice &start);
        void createCamera(mainDevice &start, int, int, int);
        void rotateCamera(mainDevice &start, float, std::vector<Indie::IPlayer*> &players);
        void createLight(mainDevice &start, irr::video::E_LIGHT_TYPE, irr::video::SColorf, bool);
        irr::gui::IGUIEnvironment* createGUI(mainDevice &start);
        irr::gui::IGUIButton *createPlayerUI(mainDevice &, irr::gui::IGUIEnvironment* &, irr::gui::IGUITab* &, irr::core::rect<int>, std::string);
        irr::gui::IGUIButton *createPlayerUINumbers(irr::gui::IGUIEnvironment* &guienv, irr::gui::IGUITab* &MenuTab, irr::core::rect<int> form, int nb);
        void createTerrain(mainDevice &);
        std::vector<irr::gui::IGUIButton *> Bnum;
        std::vector<irr::gui::IGUIButton *> Snum;
        std::vector<irr::gui::IGUIButton *> Fnum;
        std::vector<irr::gui::IGUIButton *> BonusPlayerUIs;
        std::vector<irr::gui::IGUIButton *> Timer;
        std::vector<irr::gui::IGUIButton *> Score;
        std::vector<irr::gui::IGUIButton *> Death;
        std::vector<irr::video::ITexture *> numbers;
        void displayTime(irr::video::IVideoDriver* driver);
        void displayScore(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players);
        void PrintBombNb(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players);
        void PrintSpeedNb(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players);
        void PrintFireNb(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players);
        void printDisplay(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players);
        void displayDeath(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players);
        irr::gui::IGUIButton *getPlayerHeadForEndGame();

        void setTimer(std::clock_t time);
        std::clock_t getTimer();

    private:
        std::clock_t _timer = std::clock();
        bool animationFinished = false;
        float x = 0;
        float y = 0;
        float z = 0;

};

#endif
