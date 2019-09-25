/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Map
*/

#include "../include/IPlayer.hpp"
#include "../include/Map.hpp"
#include "../include/wallBlock.hpp"
#include "../include/Block.hpp"
#include "../include/includes.hpp"
#include "../include/Player.hpp"
#include "../include/Ai.hpp"
#include <windows.h>

using namespace Indie;

int Map::create_save(std::vector<IPlayer*> players)
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    std::string str = "C:\\..\\save\\save " + std::to_string(now->tm_mday) + "-" + std::to_string(now->tm_mon + 1) + "-" +
    std::to_string(now->tm_year + 1900) + " " + std::to_string(now->tm_hour) + ":" +
    std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec);
    std::ofstream o(str);


    if (o.bad())
        std::cout << "failed to open\n";
    for (std::vector<Block>::iterator i = _blocks.begin(); i != _blocks.end(); i++)
        o << i->getPos().X << "," << (int)i->getPos().Y << "," << i->getPos().Z << std::endl;
    o << "------\n";
    for (std::vector<IPlayer*>::iterator i = players.begin(); i != players.end(); i++) {
        o << (((*i)->isAi() == true) ? "1\n" : "0\n");
        o << std::round((*i)->getPos().X) << "," << (*i)->getPos().Y << "," << std::round((*i)->getPos().Z) << std::endl;
        o << (*i)->getSpeed() << std::endl;
        o << (*i)->getRange() << std::endl;
        o << (*i)->getBombNb() + (*i)->getBombs()->size() << std::endl;
        o << (*i)->getScore() << std::endl;
        if ((*i)->isAlive() == false)
            o << "1\n";
        else
            o << "0\n";
        if ((*i)->isWallpass() == false)
            o << "1\n";
        else
            o << "0\n";
        o << "------\n";
    }
    o.close();
    return (0);
}