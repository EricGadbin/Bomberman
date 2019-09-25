/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** main
*/

#include "../include/includes.hpp"
#include "../include/MainMenu.hpp"
#include "../include/MainLoop.hpp"
#include "../include/mainDevice.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

mainDevice::~mainDevice()
{
}

mainDevice::mainDevice()
{
}

int main(void)
{
    CMainMenu menu;
    MainLoop loop;
    mainDevice start;

    if (menu.run(start)) {
        start.setDevice();
        start.setVideoDriver(start._device->getVideoDriver());
        start.setSceneManager(start._device->getSceneManager());
        loop.GameLoop(start, menu.getSelectedLoad());
    }
}
