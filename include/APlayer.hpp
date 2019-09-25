/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** APlayer
*/

#ifndef APLAYER_H
# define APLAYER_H

#include <irrlicht.h>
#include "IPlayer.hpp"
#include "Bomb.hpp"
#include "../include/mainDevice.hpp"

namespace Indie {

class Map;

class APlayer : public IPlayer {
    public:
        APlayer(mainDevice &start, std::string name, int playernb);
        APlayer(const IPlayer &player);
        ~APlayer();

        std::string getName() const;
        float getSpeed() const;
        int getRange() const;
        type_t getType() const;
        irr::core::vector3df getPos() const;
        int getBombNb() const;
        irr::u32 getThen(irr::IrrlichtDevice* device);
        irr::scene::IAnimatedMeshSceneNode * getSkin() const;
        std::vector<Indie::Bomb> *getBombs();
        virtual std::map<std::string,irr::EKEY_CODE> getkeyMap() const = 0;
        int getScore();
        int getPlayerNb();

        void setScore(int score);
        void setSpeed(float);
        void setRange(int);
        void setPos(irr::core::vector3df);
        void setBombNb(int nb);
        void setWallpass(bool);
        void setSkin(mainDevice &, int);
        void setBomb(std::vector<Indie::Bomb>);
        void setAlive(bool);

        void killPlayer();

        bool isAi() const;
        bool isAlive() const;
        bool isWallpass() const;

        bool get_cooldown() const;
        void start_cooldown();
        bool isMeg() const;
        void setMeg(bool meg);
        bool isSanic() const;
        void setSanic(bool sanic);

        irr::scene::IAnimatedMeshSceneNode *addplayer(mainDevice &start, int color);
        virtual void moveplayer(mainDevice &, MyEventReceiver *receiver, Map &map, std::vector<Indie::IPlayer*> &players) = 0;
        void moveSkin(irr::core::vector3df rotation, irr::core::vector3df nodePosition, irr::core::vector3df savePos, const irr::u32 now);
        bool checkMove(Map &map, std::vector<Indie::IPlayer*> &players, irr::core::vector3df &nodePosition, const irr::u32 now);
        void PlayAnimation(int anim);

        irr::core::vector3df getClosestPlayer(std::vector<Indie::IPlayer*> players);
        virtual void dropBomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, MyEventReceiver *receiver) = 0;

        void checkBombs(Indie::Map& map, std::vector<Indie::IPlayer*> &players, mainDevice &start);
        void unlockMovement();


    protected:
        int _playernb;
        bool _isAlive = true;
        irr::scene::IAnimatedMeshSceneNode *_skin;
        std::string _name;
        type_t _type;
        irr::f32 _speed = 5.f;
        bool _sanic = false;
        int _range;
        bool _meg = false;
        bool _ai;
        irr::core::vector3df _pos;
        int _nb = 1;
        bool _wallpass;
        irr::u32 _then;
        int _anim = 0;
        double _cooldownDuration = 0.2;
        std::clock_t _cooldown = std::clock();
        bool canMove = false;
        std::vector<Indie::Bomb> _bombs;
        unsigned int _score = 0;

    private:
};

}

#endif
