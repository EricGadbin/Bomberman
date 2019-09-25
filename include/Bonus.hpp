/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Bonus
*/

#ifndef BONUS_H
# define BONUS_H

#include "IObject.hpp"
#include "IPlayer.hpp"

namespace Indie {

class IPlayer;

class Bonus : IObject {
    public:
        enum btype_t {
            wUP,
            sUP,
            bUP,
            fUP
        };
        Bonus(btype_t type, irr::core::vector3df pos, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
        Bonus() {}
        ~Bonus() {}

        void applyBonus(IPlayer *player) const;
        bool checkCollision(irr::core::vector3df nodePosition, IPlayer *player);

        IObject::type_t getType() const;
        irr::core::vector3df getPos() const;
        bool get_time() const;
        void setPos(irr::core::vector3df pos);
        Bonus::btype_t getBonusType() const;
        void setBonusType(Bonus::btype_t type);
        Indie::Block _block;

    private:
        type_t _type;
        btype_t _btype;
        double _iFrames;
        std::clock_t _clock = std::clock();
        irr::core::vector3df _pos;
        sf::Music *_sound;
};

}

#endif
