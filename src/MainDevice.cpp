/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** main
*/

#include "../include/mainDevice.hpp"

bool mainDevice::getFullscreen()
{
    return (_fullscreen);
}

bool mainDevice::getMusic()
{
    return(_music);
}

bool mainDevice::getShadows()
{
    return (_shadows);
}

bool mainDevice::getMenuchoosed()
{
    return (_menuchoosed);
}

void mainDevice::setFullscreen(bool full)
{
    _fullscreen = full;
}

void mainDevice::setMusic(bool mus)
{
    _music = mus;
}

void mainDevice::setShadows(bool sha)
{
    _shadows = sha;
}

void mainDevice::setMenuchoosed(int men)
{
    _menuchoosed = men;
}

void mainDevice::setDevice()
{
    _device = irr::createDevice(_driverType, irr::core::dimension2d<irr::u32>(1920,1080), 32, _fullscreen, _shadows, true, &_receiver);
}
void mainDevice::setDriver(irr::video::E_DRIVER_TYPE driver)
{
    _driverType = driver;
}

irr::video::IVideoDriver* mainDevice::getVideoDriver()
{
    return (_driver);
}

irr::scene::ISceneManager* mainDevice::getSceneManager()
{
    return (_sceneManager);
}

void mainDevice::setVideoDriver(irr::video::IVideoDriver *dri)
{
    _driver = dri;
}

void mainDevice::setSceneManager(irr::scene::ISceneManager *scene)
{
    _sceneManager = scene;
}

irr::gui::IGUIButton *mainDevice::getPlayerHeadForEndGame()
{
    return(_PlayerHeadForEndGame);
}

void mainDevice::setPlayerHeadForEndGame(irr::gui::IGUIButton *newP)
{
    _PlayerHeadForEndGame = newP;
}

irr::gui::IGUIButton *mainDevice::getTextForEndGame()
{
    return(_TextForEndGame);
}

void mainDevice::setTextForEndGame(irr::gui::IGUIButton *newP)
{
    _TextForEndGame = newP;
}

irr::gui::IGUIButton *mainDevice::getPlayerTextForEndGame()
{
    return(_PlayerTextForEndGame);
}

void mainDevice::setPlayerTextForEndGame(irr::gui::IGUIButton *newP)
{
    _PlayerTextForEndGame = newP;
}

irr::gui::IGUIButton *mainDevice::getQuitForEndGame()
{
    return(_QuitForEndGame);
}

void mainDevice::setQuitForEndGame(irr::gui::IGUIButton *newP)
{
    _QuitForEndGame = newP;
}

irr::gui::IGUIButton *mainDevice::getRestartForEndGame()
{
    return(_RestartForEndGame);
}

void mainDevice::setRestartForEndGame(irr::gui::IGUIButton *newP)
{
    _RestartForEndGame = newP;
}


irr::gui::IGUIButton *mainDevice::getScForEndGame()
{
    return(_ScForEndGame);
}

void mainDevice::setScForEndGame(irr::gui::IGUIButton *newP)
{
    _ScForEndGame = newP;
}

irr::gui::IGUITabControl* &mainDevice::getTabctrl()
{
    return(_tabctrl);
}

irr::gui::IGUITab* &mainDevice::getEndTab()
{
    return(_EndTab);
}

void mainDevice::setTabctrl(irr::gui::IGUITabControl* truc)
{
    _tabctrl = truc;
}
void mainDevice::setEndTab(irr::gui::IGUITab* truc)
{
    _EndTab = truc;
}