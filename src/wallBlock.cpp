/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** wallblock
*/

#include "../include/wallBlock.hpp"
#include "../include/IObject.hpp"
#include "../include/includes.hpp"

using namespace Indie;

wallBlock::wallBlock(irr::core::vector3df pos, irr::scene::ISceneManager* sceneManager, bool is_wall, irr::video::IVideoDriver* driver)
{
    _break = false;
    _pos = pos;
    _cube = sceneManager->addCubeSceneNode(1.0f, 0, -1, _pos);
    _cube->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    _cube->addShadowVolumeSceneNode();
    if (is_wall) {
        _cube->setMaterialTexture(0, driver->getTexture("../assets/wall.jpg"));
    } else {
        _cube->setMaterialTexture(0, driver->getTexture("../assets/grass3.png"));
    }
}

wallBlock::~wallBlock()
{
}

bool wallBlock::is_breakeable() const
{
    return (_break);
}

irr::core::vector3df wallBlock::getPos() const
{
    return (_pos);
}

void wallBlock::setPos(irr::core::vector3df newPos)
{
    _pos = newPos;
}

Indie::IObject::type_t wallBlock::getType() const
{
    return (Indie::IObject::WALL);
}

bool wallBlock::checkCollision(irr::core::vector3df nodePosition)
{
    if (nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1) {
        return (true);
    }
    return (false);
}