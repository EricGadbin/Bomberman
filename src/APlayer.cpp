/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Aplayer
*/

#include "../include/APlayer.hpp"
#include "../include/Map.hpp"

using namespace Indie;

APlayer::APlayer(mainDevice &start, std::string name, int playernb) : _pos(0.0, 0.0, 0.0)
{
    _name = name;
    _type = IObject::PLAYER;
    _range = 2;
    _wallpass = false;
    _speed = 5.0;
    _then = start._device->getTimer()->getTime();
    _playernb = playernb;
}

APlayer::APlayer(const IPlayer &player)
{
    _name = player.getName();
    _type = IObject::PLAYER;
    _speed = player.getSpeed();
    _range = player.getRange();
    _ai = player.isAi();
    _pos = player.getPos();
    _nb = player.getBombNb();
}

APlayer::~APlayer()
{
    _bombs.clear();
    // _skin->remove();
}

std::string APlayer::getName() const
{
    return (_name);
}

IObject::type_t APlayer::getType() const
{
    return (_type);
}

float APlayer::getSpeed() const
{
    return (_speed);
}

void APlayer::setSpeed(float newSpeed)
{
    _speed = newSpeed;
}

int APlayer::getRange() const
{
    return (_range);
}

void APlayer::setRange(int newRange)
{
    _range = newRange;
}

irr::core::vector3df APlayer::getPos() const
{
    return (_pos);
}

void APlayer::setPos(irr::core::vector3df newPos)
{
    _pos = newPos;
    _skin->setPosition(_pos);
}

bool APlayer::isAi() const
{
    return (_ai);
}

int APlayer::getBombNb() const
{
    return (_nb);
}

void APlayer::setBombNb(int newNb)
{
    _nb = newNb;
}

bool APlayer::isMeg() const
{
    return _meg;
}

void APlayer::setMeg(bool meg)
{
    _meg = meg;
}

bool APlayer::isSanic() const
{
    return _sanic;
}

void APlayer::setSanic(bool sanic)
{
    _sanic = sanic;
}

bool APlayer::isWallpass() const
{
    return (_wallpass);
}

void APlayer::setWallpass(bool newValue)
{
    _wallpass = newValue;
}

irr::u32 APlayer::getThen(irr::IrrlichtDevice *device)
{
    return(device->getTimer()->getTime());

}

bool APlayer::isAlive() const
{
    return (_isAlive);
}


void APlayer::setSkin(mainDevice &start, int number)
{
    _skin = addplayer(start, number);
}

irr::scene::IAnimatedMeshSceneNode * APlayer::getSkin() const
{
    return(_skin);
}

int APlayer::getScore()
{
    return (_score);
}

void APlayer::setScore(int score)
{
    _score = score;
}

void APlayer::setAlive(bool liv)
{
    _isAlive = liv;
}

void APlayer::unlockMovement()
{
    canMove = true;
}


irr::scene::IAnimatedMeshSceneNode *APlayer::addplayer(mainDevice &start, int color)
{
    irr::video::IVideoDriver* driver = start._device->getVideoDriver();
    irr::scene::ISceneManager* sceneManager = start._device->getSceneManager();
    irr::scene::IAnimatedMeshSceneNode *skin = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("../assets/Bomberman.MD3"));
    skin->setMaterialFlag(irr::video::EMF_LIGHTING, true);
    skin->setAnimationSpeed(30);
    skin->setLoopMode(true);
    skin->setFrameLoop(27, 76);
    switch (color) {
        case 1:
            skin->setPosition(irr::core::vector3df(1,-0.5,19.f));
            skin->setMaterialTexture(0, driver->getTexture("../assets/Bomber.png"));
            break;
        case 2:
            skin->setPosition(irr::core::vector3df(19.f,-0.5,19.f));
            skin->setMaterialTexture(0, driver->getTexture("../assets/RedBomber.png"));
                break;
        case 3:
            skin->setPosition(irr::core::vector3df(1,-0.5,1));
            skin->setMaterialTexture(0, driver->getTexture("../assets/BlueBomber.png"));
                break;
        case 4:
            skin->setPosition(irr::core::vector3df(19.f,-0.5,1));
            skin->setMaterialTexture(0, driver->getTexture("../assets/YellowBomber.png"));
                break;
        default:
            break;
    }
    _pos = skin->getPosition();
    return (skin);
}

void APlayer::PlayAnimation(int anim)
{
    if (anim != _anim)
    {
        switch (anim)
        {
            case 0:
                _skin->setFrameLoop(27, 76);
                break;
            case 1:
                _skin->setFrameLoop(0, 26);
                break;
        }
        _anim = anim;
    }
}

std::vector<Indie::Bomb> *APlayer::getBombs()
{
    return (&_bombs);
}

int APlayer::getPlayerNb()
{
    return (_playernb);
}

void APlayer::setBomb(std::vector<Indie::Bomb> bomb)
{
    _bombs = bomb;
}

bool APlayer::checkMove(Map &map, std::vector<Indie::IPlayer*> &players, irr::core::vector3df &nodePosition, const irr::u32 now)
{
    std::vector<Indie::Bomb> *bombs;

    for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer) {
        bombs = (*itPlayer)->getBombs();
        for (std::vector<Indie::Bomb>::iterator it = bombs->begin(); it != bombs->end(); ++it) {
            if (it->get_opacity() == true && it->checkCollision(nodePosition) && !(*itPlayer)->isWallpass()) {
                _then = now;
                return (false);
            }
        }
        (*itPlayer)->setBomb(*bombs);
    }
    if (map.checkCollision(nodePosition, this) == true) {
        _then = now;
        return (false);
    }
    return (true);
}

void APlayer::moveSkin(irr::core::vector3df rotation, irr::core::vector3df nodePosition, irr::core::vector3df savePos, const irr::u32 now)
{
    _skin->setPosition(nodePosition);
    _skin->setRotation(rotation);
    setPos(nodePosition);
    if (savePos == _skin->getPosition()) {
        PlayAnimation(0);
    } else {
        PlayAnimation(1);
    }
    _then = now;
}


irr::core::vector3df APlayer::getClosestPlayer(std::vector<Indie::IPlayer*> players)
{
    irr::core::vector3df pos;
    irr::core::vector3df save;
    bool playerFound = false;

    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        if ((*it)->isAlive() == true) {
            save = (*it)->getPos();
            playerFound = true;
            break;
        }
    }
    if (playerFound == false) {
        return (players[0]->getPos());
    }
    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        if ((*it)->isAlive() == true) {
            pos = (*it)->getPos();
            if ((pos.X != _pos.X || pos.Z != _pos.Z) && sqrt(pow(pos.X - _pos.X, 2) + pow(pos.Y - _pos.Y, 2)) < sqrt(pow(save.X - _pos.X, 2) + pow(save.Y - _pos.Y, 2))) {
                save = pos;
            }
        }
    }
    return (save);
}

void APlayer::start_cooldown()
{
    _cooldown = std::clock();
}

bool APlayer::get_cooldown() const
{
    return ((std::clock() - _cooldown) / static_cast<double>(CLOCKS_PER_SEC) >= _cooldownDuration);
}

void scream()
{
    sf::Music sound;

    sound.openFromFile("../scream.wav");
    sound.play();
    while (sound.getStatus() == sf::SoundSource::Playing);
}

void APlayer::killPlayer()
{
    _isAlive = false;
    std::thread sound(&scream);
    sound.detach();
    _skin->setPosition(irr::core::vector3df(1,-5,19));
}

void Bomb::makeBlink( mainDevice &start)
{
    auto normal = start.getVideoDriver()->getTexture("../assets/Rough.png");
    auto red = start.getVideoDriver()->getTexture("../assets/Rough2.png");

    if (_blink  == 10) {
        get_skin()->setMaterialTexture(0, normal);
    }
    if (_blink == 20) {
        get_skin()->setMaterialTexture(0, red);
        _blink = 0;
    }
    _blink++;
}

void APlayer::checkBombs(Indie::Map &map, std::vector<Indie::IPlayer*> &players, mainDevice &start)
{

    bool col = false;


    for (std::vector<Indie::Bomb>::iterator it = _bombs.begin(); it != _bombs.end(); ++it) {
        if (it->get_opacity() == false) {
            for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer)
                col = col || it->checkCollision((*itPlayer)->getPos());
            if (col == false)
                it->change_opacity();
        }
        if (it->is_explosed() == true) {
            if (it->get_time_end() == true  && it->finish_explosion(start, map)) {
                it = _bombs.erase(it);
                _nb += 1;
                if (_bombs.size() == 0)
                    return;
            } else {
                for (std::vector<Indie::IPlayer*>::iterator itPlayer = players.begin(); itPlayer != players.end(); ++itPlayer) {
                    if (map.isInRange((*itPlayer)->getPos(), &_bombs[it - _bombs.begin()]) && (*itPlayer)->isAlive()) {
                        if ((*itPlayer)->getPlayerNb() != getPlayerNb())
                            _score += 100;
                        (*itPlayer)->killPlayer();
                    }
                    std::vector<Indie::Bomb> *bombs = (*itPlayer)->getBombs();
                    for (std::vector<Indie::Bomb>::iterator itb = bombs->begin(); itb != bombs->end(); ++itb) {
                        if (itb->getPos() == it->getPos())
                            continue;
                        if (map.isInRange(itb->getPos(), &_bombs[it - _bombs.begin()]) && !itb->is_explosed())
                            _score += itb->explode(map, start);
                    }
                }
            }
        }
        if (it->get_time() == true && it->is_explosed() != true) {
            _score += it->explode(map, start);
        }

        if (it->get_time() != true && it->is_explosed() != true) {
            it->makeBlink(start);
        }
    }
}
