/*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** mainDevice
*/

#ifndef MAINDEVICE_H
# define MAINDEVICE_H

#include "Event.hpp"
#include "includes.hpp"
#include <irrlicht.h>

class mainDevice {
    public:
        mainDevice();
        ~mainDevice();
        bool getFullscreen();
        bool getMusic();
        bool getShadows();
        bool getMenuchoosed();
        bool OnEvent(const irr::SEvent& event);


        irr::video::E_DRIVER_TYPE getDriver();
        irr::video::IVideoDriver* getVideoDriver();
        irr::scene::ISceneManager* getSceneManager();
        irr::gui::IGUIButton *getPlayerHeadForEndGame();
        irr::gui::IGUIButton *getTextForEndGame();
        irr::gui::IGUIButton *getPlayerTextForEndGame();
        irr::gui::IGUIButton *getQuitForEndGame();
        irr::gui::IGUIButton *getRestartForEndGame();
        irr::gui::IGUIButton *getScForEndGame();
        irr::gui::IGUITabControl* &getTabctrl();
        irr::gui::IGUITab* &getEndTab();

        void setFullscreen(bool);
        void setMusic(bool);
        void setShadows(bool);
        void setMenuchoosed(int);
        void setDriver(irr::video::E_DRIVER_TYPE);
        void setVideoDriver(irr::video::IVideoDriver*);
        void setSceneManager(irr::scene::ISceneManager*);
        void setDevice();
        void setPlayerHeadForEndGame(irr::gui::IGUIButton *newP);
        void setQuitForEndGame(irr::gui::IGUIButton *newP);
        void setRestartForEndGame(irr::gui::IGUIButton *newP);
        void setScForEndGame(irr::gui::IGUIButton *newP);
        void setTextForEndGame(irr::gui::IGUIButton *newP);
        void setPlayerTextForEndGame(irr::gui::IGUIButton *newP);
        void setTabctrl(irr::gui::IGUITabControl* truc);
        void setEndTab(irr::gui::IGUITab* truc);


        MyEventReceiver _receiver;
        irr::IrrlichtDevice* _device;
        irr::video::IVideoDriver* _driver;
        irr::scene::ISceneManager* _sceneManager;

    private:
        irr::video::E_DRIVER_TYPE _driverType = irr::video::EDT_OPENGL;
        bool _fullscreen = false;
        bool _music = true;
        bool _shadows = false;
        int _menuchoosed = -1;
        irr::gui::IGUIButton *_PlayerHeadForEndGame;
        irr::gui::IGUIButton *_TextForEndGame;
        irr::gui::IGUIButton *_PlayerTextForEndGame;
        irr::gui::IGUIButton *_RestartForEndGame;
        irr::gui::IGUIButton *_QuitForEndGame;
        irr::gui::IGUIButton *_ScForEndGame;
        irr::gui::IGUITabControl* _tabctrl;
        irr::gui::IGUITab* _EndTab;
};
#endif
