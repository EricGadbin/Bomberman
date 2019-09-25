// This is a Demo of the Irrlicht Engine (c) 2005 by N.Gebhardt.
// This file is not documentated.

#ifndef __C_MAIN_MENU_H_INCLUDED__
#define __C_MAIN_MENU_H_INCLUDED__

#include "mainDevice.hpp"
#include "Map.hpp"
#include <irrlicht.h>

class CMainMenu : public irr::IEventReceiver {
public:

    CMainMenu();
    ~CMainMenu() {};
    bool run(mainDevice &start);

    std::string getSelectedLoad() const;
    void setMenuButton(irr::core::rect<int> rect, irr::gui::IGUITab* page, int id, const wchar_t * text, std::string image);
    void LoadSaves();
    void LoadSavesBox(irr::gui::IGUIEnvironment *, irr::core::recti );
    void initMenuButton();
    void resetLibButton();
    void HideMenu();
    void ShowMenu();
    void setSkin();
    void initMenu();
    virtual bool OnEvent(const irr::SEvent& event);

private:

    irr::IrrlichtDevice *MenuDevice;
    irr::video::IVideoDriver* driver;

    irr::gui::IGUITabControl* tabctrl;
    irr::gui::IGUITab* MenuTab;
    irr::gui::IGUITab* optTab;
    irr::gui::IGUITab* loadTab;
    irr::gui::IGUITab* EmptyTab;

    std::vector<irr::gui::IGUIButton*> MenuButton;
    std::clock_t _timer = std::clock();

    irr::gui::IGUIListBox* box;
    irr::gui::IGUISkin* newskin;
    irr::gui::IGUIFont* font;
    irr::gui::IGUIEnvironment* guienv;
    irr::scene::ISceneManager* smgr;
    irr::gui::IGUIInOutFader* fader;
    irr::scene::IAnimatedMeshSceneNode *skin;
    irr::video::ITexture* logo;
    irr::video::ITexture* irrlichtBack;
    irr::core::vector3df pos;
    irr::s32 selected;
    irr::s32 loadselected;

    bool test;
    bool move;
    int okk;
    int okkk;
    int showMenu;

    bool start;
    bool fullscreen;
    bool music;
    bool transparent;
    bool shadow;
    int MenuChoosed;

    float width;
    float height;

    std::vector<std::string> _saves;
    irr::gui::IGUIListBox* _savesbox;
    sf::Music menuMusic;
    sf::Music creditsMusic;
};

#endif
