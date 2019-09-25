/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Bomb
*/

#include "../include/Bomb.hpp"
#include "../include/Map.hpp"
#include "../include/mainDevice.hpp"

using namespace Indie;

Bomb::Bomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, irr::core::vector3df pos, int range): _range(range), _pos(pos), _sound(new sf::Music)
{
    _skin = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh ("../assets/Bomb.obj"));
    _skin->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _skin->setMaterialTexture(0, driver->getTexture("../assets/Rough.png"));
    _skin->setScale(irr::core::vector3df(3, 3, 3));
    _skin->setPosition(_pos);
    _sound->openFromFile("../boom.wav");
    _size_particles = 120;
    _upRange = _range;
    _downRange = _range;
    _leftRange = _range;
    _rightRange = _range;
}

Bomb::~Bomb()
{
}

irr::core::vector3df Bomb::getPos() const
{
    return (_pos);
}

Indie::IObject::type_t Bomb::getType() const
{
    return (Indie::IObject::BOMB);
}

void Bomb::setPos(irr::core::vector3df pos)
{
    _pos = pos;
    _skin->setPosition(_pos);
}

int Bomb::get_range() const
{
    return (_range);
}

bool Bomb::is_explosed()
{
    return (_explosed);
}

void Bomb::set_explosed()
{
    _explosed = true;
}

bool Bomb::get_time() const
{
    return ((std::clock() - _time) / static_cast<double>(CLOCKS_PER_SEC) >= _timeDuration);
}

void Bomb::set_time(int time)
{
    _time = time;
}

void Bomb::force_explode()
{
    _timeDuration = 0;
}

bool Bomb::get_time_end() const
{
    return ((std::clock() - _time) / static_cast<double>(CLOCKS_PER_SEC) >= _timeDuration+0.01);
}

void Bomb::start_time()
{
    _time = std::clock();
}

void Bomb::change_opacity()
{
    _opacity = true;
}

bool Bomb::get_opacity()
{
    return (_opacity);
}

bool Bomb::checkCollision(irr::core::vector3df nodePosition)
{
    if (nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z > _pos.Z && nodePosition.Z < _pos.Z + 1 ||
        nodePosition.X + 0.2 > _pos.X && nodePosition.X + 0.2 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1 ||
        nodePosition.X + 0.9 > _pos.X && nodePosition.X + 0.9 < _pos.X + 1 && nodePosition.Z + 0.7 > _pos.Z && nodePosition.Z + 0.7 < _pos.Z + 1) {
        return (true);
    }
    return (false);
}

irr::scene::IAnimatedMeshSceneNode *Bomb::get_skin()
{
    return (_skin);
}


        irr::scene::IParticleSystemSceneNode* getparticleSystem();
        irr::scene::IParticleSystemSceneNode* getparticleSystem2();

void Bomb::playBoomSound()
{
    _sound->play();
}


irr::scene::IParticleSystemSceneNode* Bomb::getparticleSystem()
{
    return (_particleSystem);
}

irr::scene::IParticleSystemSceneNode* Bomb::getparticleSystem2()
{
    return (_particleSystem2);
}

void Bomb::setparticleSystem(irr::scene::IParticleSystemSceneNode* part)
{
    _particleSystem = part;
}

void Bomb::setparticleSystem2(irr::scene::IParticleSystemSceneNode* part)
{
    _particleSystem2 = part;
}

std::vector<irr::f32> Bomb::getRangeParticules()
{
    return (_rangeParticules);
}

void Bomb::setRangeParticules(Indie::Map &map)
{
    irr::f32 y = getPos().Z;
    irr::f32 x = getPos().X;
    irr::f32 x_left = -1;
    irr::f32 x_right = -1;
    irr::f32 y_down = -1;
    irr::f32 y_up = -1;
    int i = 1;
    bool bl = true;
    bool br = true;
    bool bu = true;
    bool bd = true;

    if (x_left < 0)
        x_left = x - _leftRange - 0.8;
    if (x_right < 0)
        x_right = x + _rightRange + 0.8;
    if (y_up < 0)
        y_up = y + _upRange + 0.8;
    if (y_down < 0)
        y_down = y - _downRange - 0.8;

    _rangeParticules.push_back(y_down);
    _rangeParticules.push_back(y_up);
    _rangeParticules.push_back(x_right);
    _rangeParticules.push_back(x_left);

}

irr::scene::IParticleEmitter *Indie::Bomb::setEmmiter(int size, int a, int b, int c, int d)
{
    irr::scene::IParticleEmitter* emitter;
    emitter = getparticleSystem()->createBoxEmitter(
		irr::core::aabbox3d<irr::f32>(a, 0, b , c, 0.5, d),
        irr::core::vector3df(0.00f, 0.0005f, 0.0f),
        size, size+(size/4),
        irr::video::SColor(80-size, 226, 40, 34),
        irr::video::SColor(80-size, 226, 136, 34),
        (size*10)-200, (size*10) + 200,
        300,
        irr::core::dimension2df(0.1f, 0.3f),
        irr::core::dimension2df(0.4f, 0.4f));


    return (emitter);
}


irr::scene::IParticleEmitter* Bomb::setParticules(int xy, int size, Indie::Map &map, mainDevice &start)
{
    irr::scene::IParticleEmitter* emitter;

    if (xy) {
        emitter = setEmmiter(size, getRangeParticules().at(3), getPos().Z, getRangeParticules().at(2), getPos().Z);
        getparticleSystem()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        getparticleSystem()->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
        irr::video::ITexture *fireTexture = start._device->getVideoDriver()->getTexture("../assets/fire.bmp");
        getparticleSystem()->setMaterialTexture(0, fireTexture);
        getparticleSystem()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    } else {
        emitter = setEmmiter(size, getPos().X, getRangeParticules().at(0), getPos().X, getRangeParticules().at(1));
        getparticleSystem2()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        getparticleSystem2()->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
        irr::video::ITexture *fireTexture = start._device->getVideoDriver()->getTexture("../assets/fire.bmp");
        getparticleSystem2()->setMaterialTexture(0, fireTexture);
        getparticleSystem2()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    }
    return emitter;
}

void Bomb::make_explosion(mainDevice &start, Indie::Map &map)
{
	_particleSystem = start._sceneManager->addParticleSystemSceneNode(false);
	_particleSystem->setEmitter(setParticules(1, 100, map, start));
	_particleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	_particleSystem2 = start._sceneManager->addParticleSystemSceneNode(false);
	_particleSystem2->setEmitter(setParticules(0, 100, map, start));
	_particleSystem2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

bool Bomb::finish_explosion(mainDevice &start, Indie::Map &map)
{
    if (_size_particles > 0 && _size_particles < 70) {
        _particleSystem->setEmitter(setParticules(1, _size_particles, map, start));
        _particleSystem2->setEmitter(setParticules(0, _size_particles, map, start));
        _size_particles -= 2;
        return false;
	} else if (_size_particles >= 70) {
		_size_particles -= 1;
		return false;
	}
	_size_particles = 120;
	_particleSystem->remove();
	_particleSystem2->remove();
	return true;
}

void Bomb::setRanges(Indie::Map &map)
{
    bool Bleft = false;
    bool Bright = false;
    bool Bup = false;
    bool Bdown = false;

    bool Wleft = false;
    bool Wright = false;
    bool Wup = false;
    bool Wdown = false;

    for(int i = 1; i <= _range; ++i) {
        map.checkForObstacles(_pos, i, true);
        if (map.getObstaclesLeft() && !Bleft) {
            Bleft = true;
            _leftRange = i;
        }
        if (map.getObstaclesRight() &&  !Bright) {
            Bright = true;
            _rightRange = i;
        }
        if (map.getObstaclesUp() && !Bup) {
            Bup = true;
            _upRange = i;
        }
        if (map.getObstaclesDown() && !Bdown) {
            Bdown = true;
            _downRange = i;
        }
    }
    for(int i = 1; i <= _range; ++i) {
        map.checkForObstacles(_pos, i, false);
        if (map.getObstaclesLeft() && !Wleft && _leftRange > i) {
            Wleft = true;
            _leftRange = i - 1;
        }
        if (map.getObstaclesRight() && !Wright && _rightRange > i) {
            Wright = true;
            _rightRange = i - 1;
        }
        if (map.getObstaclesUp() && !Wup && _upRange > i) {
            Wup = true;
            _upRange = i - 1;
        }
        if (map.getObstaclesDown() && !Wdown && _downRange > i) {
            Wdown = true;
            _downRange = i - 1;
        }
    }

}
unsigned int Bomb::explode(Indie::Map &map, mainDevice &start)
{
    unsigned int addToScore = 0;

    set_explosed();
    playBoomSound();
    setRanges(map);
    setRangeParticules(map);
    addToScore = map.removeBlocks(getPos(), this, start);
    get_skin()->remove();
    make_explosion(start, map);
    return (addToScore);
}