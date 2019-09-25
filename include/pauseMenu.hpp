/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** pauseMenu
*/

#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "CreateGame.hpp"
#include "mainDevice.hpp"
#include "endMenu.hpp"

namespace Indie {

    class pauseMenu {
        public:
            pauseMenu(mainDevice &start, irr::gui::IGUIEnvironment* &guienv);
            ~pauseMenu();
            bool isPaused();
            void setPause(mainDevice &start, bool state, irr::gui::IGUIEnvironment* &guienv);
            bool get_cooldown() const;
            void start_cooldown();
            void manageTimer(CreateGame &game);
            void isRun(mainDevice &start, Map &map, std::vector<Indie::IPlayer *> bombers, CreateGame &game, irr::gui::IGUIEnvironment* guienv, endMenu &end);
            std::vector<irr::gui::IGUIButton *> Buttons;


        private:
            bool _isPaused = false;
            double _cooldownDuration = 0.2;
            std::clock_t _cooldown = std::clock();
            std::clock_t _saveTimer;

    };
};
#endif
