/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** IObject
*/

#ifndef IOBJECT_H
# define IOBJECT_H

#include "includes.hpp"

namespace Indie {

class IObject {
    public:
        typedef enum type_e {
            BOMB,
            BLOCK,
            PLAYER,
            WALL,
            BONUS,
        } type_t;
        virtual ~IObject() = default;
        virtual type_t getType() const = 0;
        virtual irr::core::vector3df getPos() const = 0;
        virtual void setPos(irr::core::vector3df) = 0;

    private:
};

}

#endif