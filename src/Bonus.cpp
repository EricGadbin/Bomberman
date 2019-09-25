/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Bonus
*/

#include "../include/Bonus.hpp"

using namespace Indie;

std::string assets[] = {
    "../assets/wallbonus.png",
    "../assets/speedbonus.png",
    "../assets/bombbonus.png",
    "../assets/firebonus.png"
};

Bonus::Bonus(btype_t type, irr::core::vector3df pos, irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver) : _btype(type), _pos(pos), _sound(new sf::Music)
{
    _block = Indie::Block(pos, sceneManager, driver);
    _block.getCube()->setMaterialTexture(0, driver->getTexture(assets[type].c_str()));
    _block.getCube()->setScale(irr::core::vector3df(0.8,0.8,0.8));
    _sound->openFromFile("../powerUP.wav");
}



void powerUpSound()
{
    sf::Music sound;

    sound.openFromFile("../powerUP.wav");
    sound.play();
    while (sound.getStatus() == sf::SoundSource::Playing);
}

void Bonus::applyBonus(IPlayer *player) const
{
    switch (_btype) {
        case wUP:
            player->setWallpass(true);
            break;
        case sUP:
            player->setSpeed(player->getSpeed() * 1.25);
            if (player->getSpeed() > 15 && player->getSpeed() < 16)
                player->setSanic(true);
            break;
        case bUP:
            player->setBombNb(player->getBombNb() + 1);
            break;
        case fUP:
            player->setRange(player->getRange() + 1);
            if (player->getRange() == 10)
                player->setMeg(true);
            break;
        default:
            return;
    }
    _sound->play();
    //std::thread pow(&powerUpSound);
    //pow.detach();
}

bool Bonus::checkCollision(irr::core::vector3df nodePosition, IPlayer *player)
{
    if (nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1) {
        applyBonus(player);
        return (true);
    }
    return (false);
}

bool Bonus::get_time() const
{
    return ((std::clock() - _clock) / static_cast<double>(CLOCKS_PER_SEC) >= _iFrames);
}

Bonus::btype_t Bonus::getBonusType() const
{
    return _btype;
}

void Bonus::setBonusType(Bonus::btype_t btype)
{
    _btype = btype;
}

irr::core::vector3df Bonus::getPos() const
{
    return _pos;
}

void Bonus::setPos(irr::core::vector3df pos)
{
    _pos = pos;
}

IObject::type_t Bonus::getType() const
{
    return _type;
}
