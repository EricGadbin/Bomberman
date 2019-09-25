/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Block
*/

#ifndef BLOCK_H
# define BLOCK_H

#include "IBlock.hpp"

namespace Indie {

class Block : public IBlock {
    public:
        Block() {};
        Block(irr::core::vector3df pos, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver);
        ~Block();

        irr::core::vector3df getPos() const;
        bool is_breakeable() const;
        Indie::IObject::type_t getType() const;
        irr::scene::IMeshSceneNode* getCube();

        void setPos(irr::core::vector3df);

        bool checkCollision(irr::core::vector3df nodePosition);

    private:
        bool _break;
        irr::core::vector3df _pos;
        irr::scene::IMeshSceneNode* _cube;
};

}

#endif
