/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** wallBlock
*/

#ifndef WALLBLOCK_H
# define WALLBLOCK_H

#include "IBlock.hpp"

namespace Indie {

class wallBlock : public IBlock {
    public:
        wallBlock(irr::core::vector3df pos, irr::scene::ISceneManager* sceneManager, bool is_wall, irr::video::IVideoDriver* driver);
        ~wallBlock();

        irr::core::vector3df getPos() const;
        bool is_breakeable() const;
        Indie::IObject::type_t getType() const;

        void setPos(irr::core::vector3df);
        bool checkCollision(irr::core::vector3df nodePosition);

    private:
        bool _break;
        irr::core::vector3df _pos;
        irr::scene::IMeshSceneNode* _cube;
};

}

#endif
