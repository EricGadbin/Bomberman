/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** block
*/

#include "../include/Block.hpp"

using namespace Indie;

Block::Block(irr::core::vector3df pos, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver)
{
    _break = true;
    _pos = pos;
    _cube = sceneManager->addCubeSceneNode(1.0f, 0, -1, _pos);
    _cube->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    _cube->setMaterialTexture(0, driver->getTexture("../assets/crate.jpg"));
    _cube->addShadowVolumeSceneNode();
}


Block::~Block()
{
}

bool Block::is_breakeable() const
{
    return (_break);
}

irr::core::vector3df Block::getPos() const
{
    return (_pos);
}

irr::scene::IMeshSceneNode* Block::getCube()
{
    return (_cube);
}

void Block::setPos(irr::core::vector3df newPos)
{
    _pos = newPos;
}


Indie::IObject::type_t Block::getType() const
{
    return (Indie::IObject::BLOCK);
}

bool Block::checkCollision(irr::core::vector3df nodePosition)
{
    if (nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1) {
        return (true);
    }
    return (false);
}
