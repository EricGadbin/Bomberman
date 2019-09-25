/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** IBlock
*/

#ifndef IBLOCK_H
# define IBLOCK_H

#include "includes.hpp"
#include "IObject.hpp"

namespace Indie {

class IBlock : public IObject {
    public:
        virtual ~IBlock() = default;
        virtual bool is_breakeable() const = 0;
        virtual bool checkCollision(irr::core::vector3df nodePosition) = 0;


    private:
};

}

#endif