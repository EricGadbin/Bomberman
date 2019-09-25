/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** player
*/

#include "../include/Player.hpp"
#include "../include/APlayer.hpp"
#include "../include/Bomb.hpp"
#include "../include/mainDevice.hpp"
#include <irrlicht.h>

using namespace Indie;

Player::Player(mainDevice &start, std::string name, int playernb) : APlayer(start, name, playernb)
{
    _ai = false;
    switch (playernb) {
        case 1:
            _keyMap["left"] = irr::KEY_KEY_Q;
            _keyMap["right"] = irr::KEY_KEY_D;
            _keyMap["up"] = irr::KEY_KEY_Z;
            _keyMap["down"] = irr::KEY_KEY_S;
            _keyMap["drop"] = irr::KEY_KEY_E;
            break;
        case 2:
            _keyMap["left"] = irr::KEY_LEFT;
            _keyMap["right"] = irr::KEY_RIGHT;
            _keyMap["up"] = irr::KEY_UP;
            _keyMap["down"] = irr::KEY_DOWN;
            _keyMap["drop"] = irr::KEY_KEY_M;
            break;
        default:
            break;
    }
}

Player::Player(const Player &player) : APlayer(player)
{
    _keyMap = player.getkeyMap();
}

Player::~Player()
{
}

std::map<std::string,irr::EKEY_CODE> Player::getkeyMap() const
{
    return (_keyMap);
}

void Player::moveplayer(mainDevice &start, MyEventReceiver *receiver, Map &map, std::vector<Indie::IPlayer*> &players)
{
    const irr::u32 now = start._device->getTimer()->getTime();
    const irr::f32 frameDeltaTime = static_cast<irr::f32>((now - _then) / 1000.f);
    irr::core::vector3df nodePosition = _skin->getPosition();
    const irr::core::vector3df savePos = _skin->getPosition();
    irr::core::vector3df rotation;
    std::vector<Indie::Bomb> bombs;

    if (canMove == false) {
        _then = now;
        return;
    }
    if (receiver->IsKeyDown(_keyMap["up"])) {
        rotation = irr::core::vector3df(0,-180,0);
        _skin->setRotation(rotation);
        nodePosition.Z += _speed * frameDeltaTime;
        nodePosition.Z = (nodePosition.Z * 10.0)/10.0;
    } else if (receiver->IsKeyDown(_keyMap["down"])) {
        rotation = irr::core::vector3df(0,0,0);
        _skin->setRotation(rotation);
        nodePosition.Z -= _speed * frameDeltaTime;
        nodePosition.Z = (nodePosition.Z * 10.0)/10.0;
	}
    if (receiver->IsKeyDown(_keyMap["left"])) {
        rotation = irr::core::vector3df(0, 90,0);
        _skin->setRotation(rotation);
        nodePosition.X -= _speed * frameDeltaTime;
        nodePosition.X = (nodePosition.X * 10.0)/10.0;
    } else if (receiver->IsKeyDown(_keyMap["right"])) {
        rotation = irr::core::vector3df(0,-90,0);
        _skin->setRotation(rotation);
        nodePosition.X += _speed * frameDeltaTime;
        nodePosition.X = (nodePosition.X * 10.0)/10.0;
    }
    if (checkMove(map, players, nodePosition, now)) {
        moveSkin(rotation, nodePosition, savePos, now);
    }
}

void Player::dropBomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, MyEventReceiver *receiver)
{
    if (canMove == false) {
        return;
    }
    if (_isAlive == true && receiver->IsKeyDown(_keyMap["drop"])) {
        if (_nb > 0 && get_cooldown() == true) {
            irr::core::vector3df nodePosition = _skin->getPosition();
            nodePosition.X = round(nodePosition.X);
            nodePosition.Z = round(nodePosition.Z);
            Indie::Bomb bomb(sceneManager, driver, nodePosition, getRange());
            _nb -= 1;
            // PrintBombNb(Bnum, driver);
            _bombs.push_back(bomb);
            start_cooldown();
        }
    }
}
