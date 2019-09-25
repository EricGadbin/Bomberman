/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Player
*/

#ifndef AI_H
# define AI_H

#include "APlayer.hpp"

namespace Indie {

class Map;

class Ai : public APlayer {
    public:
        Ai(mainDevice &start, std::string name, int playernb);
        Ai(const IPlayer &player);
        ~Ai();

        typedef enum direction_e {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            NONE,
        } direction_t;

        typedef enum action_e {
            WALK,
            DROP,
            FLEE,
        } action_t;

        std::map<std::string,irr::EKEY_CODE> getkeyMap() const;

        bool get_cooldownAi() const;
        void start_cooldownAi();

        void chooseAction(Indie::Map &map, std::vector<Indie::IPlayer*> &players);
        int chooseDirection(bool *walls, bool *inRange, bool *closest, bool *obstacles);
        void moveplayer(mainDevice &start, MyEventReceiver *receiver, Indie::Map &map, std::vector<Indie::IPlayer*> &players);
        int getDropdir();
        int getDirection();
        int getOppositeDir();
        void setDirection(int direction);
        int getOppositeOfGiven(int direction);

        int moveAi(Indie::Map &map, std::vector<Indie::IPlayer*> &players);
        int checkDirection(Indie::Map &map, std::vector<Indie::IPlayer*> &players, irr::core::vector3df pos, int length, int oldDir);
        int chooseFleeingDirection(Indie::Map &map, std::vector<Indie::IPlayer*> &players);
        int getBestPath(Indie::Map &map, std::vector<Indie::IPlayer*> &players, bool *obstacles);
        int findSmallestPath(std::vector<int> paths);
        void dropBomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, MyEventReceiver *receiver);

    private:
        double _cooldownDurationAi = 0.05;
        std::clock_t _cooldownAi = std::clock();
        std::map<std::string,irr::EKEY_CODE> _keyMap;

        direction_t _direction = NONE;
        action_t _action = WALK;
};

};

#endif
