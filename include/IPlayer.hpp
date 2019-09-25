/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** IPlayer
*/

#ifndef IPLAYER_H
# define IPLAYER_H

#include "Bomb.hpp"
#include "Event.hpp"
#include "wallBlock.hpp"
#include "Block.hpp"
#include "mainDevice.hpp"

namespace Indie {

class IPlayer : public IObject {
    public:
        virtual ~IPlayer() = default;

        virtual std::string getName() const = 0;
        virtual float getSpeed() const = 0;
        virtual int getRange() const = 0;
        virtual type_t getType() const = 0;
        virtual irr::core::vector3df getPos() const = 0;
        virtual int getBombNb() const = 0;
        virtual irr::u32 getThen(irr::IrrlichtDevice* device) = 0;
        virtual irr::scene::IAnimatedMeshSceneNode * getSkin() const = 0;
        virtual std::vector<Indie::Bomb> *getBombs() = 0;
        virtual std::map<std::string,irr::EKEY_CODE> getkeyMap() const = 0;

        virtual int getScore() = 0;
        virtual int getPlayerNb() = 0;

        virtual void setScore(int score) = 0;

        virtual void setSpeed(float) = 0;
        virtual void setRange(int) = 0;
        virtual void setPos(irr::core::vector3df) = 0;
        virtual void setBombNb(int nb) = 0;
        virtual void setWallpass(bool) = 0;
        virtual void setSkin(mainDevice &start, int) = 0;
        virtual void setBomb(std::vector<Indie::Bomb>) = 0;
        virtual void setAlive(bool) = 0;
        virtual void setMeg(bool) = 0;
        virtual void setSanic(bool sanic) = 0;

        virtual void killPlayer() = 0;

        virtual bool isAi() const = 0;
        virtual bool isAlive() const = 0;
        virtual bool isWallpass() const = 0;
        virtual bool isMeg() const = 0;
        virtual bool isSanic() const = 0;

        virtual bool get_cooldown() const = 0;
        virtual void start_cooldown() = 0;

        virtual irr::scene::IAnimatedMeshSceneNode *addplayer(mainDevice &start, int color) = 0;
        virtual void moveplayer(mainDevice &start, MyEventReceiver *receiver, Map &map, std::vector<Indie::IPlayer*> &players) = 0;
        virtual void moveSkin(irr::core::vector3df rotation, irr::core::vector3df nodePosition, irr::core::vector3df savePos, const irr::u32 now) = 0;
        virtual bool checkMove(Map &map, std::vector<Indie::IPlayer*> &players, irr::core::vector3df &nodePosition, const irr::u32 now) = 0;
        virtual void PlayAnimation(int anim) = 0;

        virtual irr::core::vector3df getClosestPlayer(std::vector<Indie::IPlayer*> players) = 0;
        virtual void dropBomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, MyEventReceiver *receiver) = 0;

        virtual void checkBombs(Indie::Map &map, std::vector<Indie::IPlayer*> &players, mainDevice &start) = 0;
        virtual void unlockMovement() = 0;
    private:

};

}

#endif
