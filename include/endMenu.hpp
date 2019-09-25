/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** endMenu
*/

#ifndef ENDMENU_H
#define ENDMENU_H

#include "CreateGame.hpp"

#include <sstream>
#include <string>
#include <iomanip>

namespace Indie {

    class endMenu {
        public:
            endMenu();
            ~endMenu();

            typedef enum state_e {
                WON,
                LOST,
                ONGOING,
            } state_t;

            void gameIsOver(std::vector<Indie::IPlayer*> &players, mainDevice &start);
            state_t getGameState();

          //  void endMenu::createScreenDeath();

            void createScreenForEnd(mainDevice &start, int playerID, int final, int sc);


            int setCamera(mainDevice &start, int z);
            void setButtonEndScreen(mainDevice &start);
            void setTextMultPlayerEndScreen(mainDevice &start, int playerID, int final);
            void setScMultPlayerEndScreen(mainDevice &start, int final, int sc);
            void setImgPlayerEndScreen(mainDevice &start, int final);
            int setDeath(mainDevice &start, int sc, int id, int z, int nbPlayer);
            int setAllDeath(mainDevice &start, int sc, int z, int nbPlayer);
            int setWin(mainDevice &start, int playerAlive, int id, int sc, int z);


        private:
            int _winner = 0;
            state_t _state = ONGOING;

    };
};
#endif
