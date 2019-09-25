/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Bomb
*/

#ifndef BOMB_H
# define BOMB_H

#include "IObject.hpp"
#include "includes.hpp"
#include "../include/mainDevice.hpp"

namespace Indie {

class Map;

class Bomb : public IObject {
    public:
        Bomb(irr::scene::ISceneManager* sceneManager, irr::video::IVideoDriver* driver, irr::core::vector3df pos, int range);
        ~Bomb();
        int get_range() const;
        irr::core::vector3df getPos() const;
        Indie::IObject::type_t getType() const;
        void setPos(irr::core::vector3df);
        void force_explode();
        bool get_time() const;
        void set_time(int);
        bool get_time_end() const;
        void start_time();
        bool get_opacity();
        void change_opacity();
        bool is_explosed();
        void set_explosed();
        void make_explosion(mainDevice &start, Indie::Map &map);
        bool finish_explosion(mainDevice &start, Indie::Map &map);
        unsigned int explode(Indie::Map &map, mainDevice &start);
        bool checkCollision(irr::core::vector3df nodePosition);
        void setRanges(Indie::Map &map);
        irr::scene::IAnimatedMeshSceneNode *get_skin();
        irr::scene::IParticleEmitter* setParticules(int xy, int size, Indie::Map &map, mainDevice &start);
        void playBoomSound();
        irr::scene::IParticleSystemSceneNode* getparticleSystem();
        irr::scene::IParticleSystemSceneNode* getparticleSystem2();
        void setparticleSystem(irr::scene::IParticleSystemSceneNode* part);
        void setparticleSystem2(irr::scene::IParticleSystemSceneNode* part);
        void setRangeParticules(Indie::Map &map);
        std::vector<irr::f32> getRangeParticules();
        void makeBlink( mainDevice &start);
        irr::scene::IParticleEmitter *setEmmiter(int size, int a, int b, int c, int d);

        int _upRange;
        int _downRange;
        int _leftRange;
        int _rightRange;
    private:
        irr::scene::IParticleSystemSceneNode* _particleSystem;
        irr::scene::IParticleSystemSceneNode* _particleSystem2;
        int _size_particles;
        int _range;
        int _blink = 0;
        irr::core::vector3df _pos;
        irr::scene::IAnimatedMeshSceneNode *_skin;
        double _timeDuration = 3;
        std::clock_t _time = std::clock();
        bool _opacity = false;
        bool _explosed = false;
        sf::Music *_sound;
        std::vector<irr::f32> _rangeParticules;
};

}

#endif
