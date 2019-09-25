/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** CreateGame.c
*/

#include "../include/CreateGame.hpp"
#include "../include/Ai.hpp"
#include "../include/Player.hpp"
#include <sstream>
#include <string>
#include <iomanip>

CreateGame::~CreateGame()
{
}

CreateGame::CreateGame(float x1, float y1, float z1)
{
    x = x1;
    y = y1;
    z = z1;
}

std::vector<Indie::IPlayer*> CreateGame::createPlayer(mainDevice &start)
{
    int i = 0;
    bool isAi[] = {false, false, true, true};
    std::vector<Indie::IPlayer*> bombers;

    isAi[1] = !start.getMenuchoosed();
    for (int i = 0; i < 4; i++) {
        if (isAi[i] == true) {
            bombers.push_back(new Indie::Ai(start, "Players", i + 1));
        } else {
            bombers.push_back(new Indie::Player(start, "IA", i + 1));
        }
    }
    for (std::vector<Indie::IPlayer*> ::iterator it = bombers.begin(); it != bombers.end(); ++it, ++i) {
        (*it)->setSkin(start, i + 1);
    }
    return (bombers);
}

void CreateGame::createCamera(mainDevice &start, int x, int y, int z)
{
    start._sceneManager->addCameraSceneNode(0, irr::core::vector3df(x, y, z),irr::core::vector3df(10, 8.5, 6.4));
}

void CreateGame::rotateCamera(mainDevice &start, float timer, std::vector<Indie::IPlayer*> &players)
{
    if (y > timer) {
        start._sceneManager->getActiveCamera()->setPosition(irr::core::vector3df(x, y, z));
        y -= 0.1;
        z -= 0.011;
        x -= 0.100667;
    } else if (animationFinished == false) {
        animationFinished = true;
        _timer = std::clock();
        for (std::vector<Indie::IPlayer*> ::iterator it = players.begin(); it != players.end(); ++it) {
            (*it)->unlockMovement();
        }
    }
}

void CreateGame::createLight(mainDevice &start, irr::video::E_LIGHT_TYPE type, irr::video::SColorf color , bool falloff)
{
    irr::scene::ILightSceneNode* light = start._sceneManager->addLightSceneNode(0, irr::core::vector3df(80, 130, -30), irr::video::SColorf(259.0f, 252.0f, 252.0f, 175.0f), 10000.0f);

    light->getLightData().Type = type;
    light->getLightData().AmbientColor = color;
    light->getLightData().Falloff = falloff;
}

irr::gui::IGUIEnvironment* CreateGame::createGUI(mainDevice &start)
{
    irr::gui::IGUIEnvironment* guienv1 = start._device->getGUIEnvironment();
    irr::gui::IGUISkin* newskin = guienv1->createSkin(irr::gui::EGST_BURNING_SKIN);
    irr::gui::IGUIFont* font = guienv1->getFont("../assets/arcade/arcade 56.xml");
    irr::gui::IGUITabControl* tabctrl = guienv1->addTabControl(irr::core::rect<int>(0,-35,1920, 1080), 0, true, true);
    irr::gui::IGUITab* MenuTab = tabctrl->addTab(L"Menu");
    irr::gui::IGUITab* EndTab = tabctrl->addTab(L"End");

    const irr::s32 leftX = 600;
    irr::s32 alpha = 255;
    guienv1->setSkin(newskin);
    newskin->drop();
    guienv1->getSkin()->setFont(font);
    guienv1->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)8, irr::video::SColor(255, 11, 60, 128));

    for (irr::u32 i = 0; i < 8 ; ++i) {
        irr::video::SColor color = guienv1->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        color.setAlpha(0);
        guienv1->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, color);
    }

    float height = start._driver->getScreenSize().Height;
    float width = start._driver->getScreenSize().Width;
    start.setTabctrl(tabctrl);
    start.setEndTab(EndTab);
    start.setPlayerHeadForEndGame(createPlayerUI(start, guienv1, EndTab, irr::core::rect<int>(width/50, height/25, width/5, height/5.55*4), ""));
    start.setTextForEndGame(createPlayerUI(start, guienv1, EndTab, irr::core::rect<int>(width/4, 0, width - width/4, height/3), ""));

    start.setPlayerTextForEndGame(createPlayerUINumbers(guienv1, EndTab, irr::core::rect<int>(width/8,height/10,width/4 + 1200, height/2), 0));
    start.setRestartForEndGame(guienv1->addButton(irr::core::rect<int>(width/2.6,height/2,width/1.6,height/1.66), EndTab, 19, L"RETURN TO MENU"));
    start.setQuitForEndGame(guienv1->addButton(irr::core::rect<int>(width/2.6,height/2 + 200,width/1.6,height/1.66 + 200), EndTab, 21, L"QUIT"));
    start.setScForEndGame(createPlayerUINumbers(guienv1, EndTab, irr::core::rect<int>(width/7,height/3,width/4 + 1200, height/2), 0));

    Death.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/100, height/50, width/10, height/5.55), "../assets/Bomber-head1.png"));
    Death.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.165,height/50, width/1.055, height/5.55), "../assets/Bomber-head2.png"));
    Death.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/100, height/2.05, width/10, height/1.55), "../assets/Bomber-head3.png"));
    Death.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.165, height/2.05, width/1.055, height/1.55), "../assets/Bomber-head4.png"));

    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/50,height/5.2,width/24, height/4.35), "../assets/bombUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.156, height/5.2, width/1.129, height/4.35), "../assets/bombUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/50, height/1.525, width/24, height/1.44), "../assets/bombUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.156, height/1.525, width/1.129, height/1.44), "../assets/bombUI.png"));

    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/50, height/4.20, width/24, height/3.6), "../assets/fireUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.156, height/4.20, width/1.129, height/3.6), "../assets/fireUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/50, height/1.425, width/24, height/1.345), "../assets/fireUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.156, height/1.425, width/1.129, height/1.345), "../assets/fireUI.png"));

    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/50,height/3.5,width/24,height/3.06), "../assets/speedUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.156, height/3.5, width/1.129, height/3.06), "../assets/speedUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/50, height/1.336, width/24,height/1.27), "../assets/speedUI.png"));
    BonusPlayerUIs.push_back(createPlayerUI(start, guienv1, MenuTab, irr::core::rect<int>(width/1.156, height/1.336, width/1.129, height/1.27), "../assets/speedUI.png"));

    Bnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/20, height/5.2, width/12, height/4.35), 1));
    Bnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.12, height/5.2, width/1.08, height/4.35), 1));
    Bnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/20, height/1.525, width/12, height/1.44), 1));
    Bnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.12, height/1.525, width/1.08, height/1.44), 1));

    Fnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/20, height/4.2, width/12, height/3.6), 1));
    Fnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.12, height/4.2, width/1.08, height/3.6), 1));
    Fnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/20, height/1.42, width/12, height/1.35), 1));
    Fnum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.12, height/1.42, width/1.08, height/1.35), 1));

    Snum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/20, height/3.45, width/12, height/3.1), 1));
    Snum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.12, height/3.45, width/1.08, height/3.1), 1));
    Snum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/20, height/1.33, width/12, height/1.265), 1));
    Snum.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.12, height/1.33, width/1.08, height/1.265), 1));

    Score.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(-width/20, height/2.6, width/5.5, height/2.2), 0));
    Score.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.26, height/2.6, width/0.98, height/2.2), 0));
    Score.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(-width/20, height/1.2, width/5.5, height/1.05), 0));
    Score.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/1.26, height/1.2,  width/0.98, height/1.05), 0));

    Timer.push_back(createPlayerUINumbers(guienv1, MenuTab, irr::core::rect<int>(width/3, height/50, width/1.5, height/8), 0));

    return (guienv1);
}

irr::gui::IGUIButton *CreateGame::createPlayerUI(mainDevice &start, irr::gui::IGUIEnvironment* &guienv, irr::gui::IGUITab* &MenuTab, irr::core::rect<int> form, std::string text)
{
    irr::gui::IGUIButton* player = guienv->addButton(form, MenuTab, 5, L"");
    player->setImage(start._driver->getTexture(text.c_str()));
    player->setScaleImage(true);
    player->setUseAlphaChannel(true);
    player->setDrawBorder(0);
    return (player);
}

irr::gui::IGUIButton *CreateGame::createPlayerUINumbers(irr::gui::IGUIEnvironment* &guienv, irr::gui::IGUITab* &MenuTab, irr::core::rect<int> form, int nb)
{
    irr::gui::IGUIButton* player = guienv->addButton(form, MenuTab, 5, L"");
    player->setScaleImage(true);
    player->setUseAlphaChannel(true);
    player->setDrawBorder(0);
    return (player);
}

void CreateGame::createTerrain(mainDevice &start)
{
    irr::scene::ITerrainSceneNode* terrain = start._sceneManager->addTerrainSceneNode("../assets/terrain-heightmap.bmp", 0, -1,
        irr::core::vector3df(-100.f, -1.f, -1000.f),        // position
        irr::core::vector3df(0.f, 0.f, 0.f),                // rotation
        irr::core::vector3df(40.f, 4.4f, 40.f),             // scale
        irr::video::SColor ( 255, 255, 255, 255 ),          // vertexColor
        5,                                                  // maxLOD
        irr::scene::ETPS_17,                                // patchSize
        4                                                   // smoothFactor
        );
    terrain->setScale(irr::core::vector3df(10, 0.f, 10));
    terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    terrain->setMaterialTexture(0, start._driver->getTexture("../assets/sand2.jpg"));
    terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);
    terrain->scaleTexture(300.0f, 300.0f);
}

void CreateGame::displayTime(irr::video::IVideoDriver* driver)
{
    double seconds = (std::clock() - _timer) / static_cast<double>(CLOCKS_PER_SEC);
    double minutes = seconds / 60.f;

    if (minutes > 60) {
        return;
    }
    if (animationFinished == false) {
        return;
    }
    seconds = static_cast<int>(seconds) % 60;
    std::string str = std::to_string(static_cast<int>(minutes) / 10) + std::to_string(static_cast<int>(minutes) % 10) + ":" + std::to_string(static_cast<int>(seconds) / 10) + std::to_string(static_cast<int>(seconds) % 10);
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();
    Timer[0]->setText(widecstr);
}

void CreateGame::displayScore(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players)
{
    int nb = 0;

    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        nb = (*it)->getScore();
        if (nb < 1000) {
            std::ostringstream oss;
            oss << "SC " << std::setfill('0') << std::setw(3) << nb;
            std::string str = oss.str();
            std::wstring widestr = std::wstring(str.begin(), str.end());
            const wchar_t* widecstr = widestr.c_str();
            Score[(*it)->getPlayerNb() - 1]->setText(widecstr);
        }
    }
}

void CreateGame::displayDeath(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players)
{
    bool state = 0;

    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        state = (*it)->isAlive();
        if (state == false) {
            Death[(*it)->getPlayerNb() -1]->setImage(driver->getTexture("../assets/DeadBomberman.png"));
        }
    }
}

void CreateGame::PrintBombNb(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players)
{
    int nb = 0;

    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        nb = (*it)->getBombNb();
        if (nb >= 0) {
            std::string str = std::to_string(nb);
            std::wstring widestr = std::wstring(str.begin(), str.end());
            const wchar_t* widecstr = widestr.c_str();
            Bnum[(*it)->getPlayerNb() - 1]->setText(widecstr);
        }
    }
}

void CreateGame::PrintFireNb(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players)
{
    int nb = 0;

    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        nb = (*it)->getRange();
        if (nb >= 0) {
            std::string str = std::to_string(nb);
            std::wstring widestr = std::wstring(str.begin(), str.end());
            const wchar_t* widecstr = widestr.c_str();
            Fnum[(*it)->getPlayerNb() - 1]->setText(widecstr);
        }
    }
}

void CreateGame::PrintSpeedNb(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players)
{
    int nb = 0;

    for (std::vector<Indie::IPlayer*>::iterator it = players.begin(); it != players.end(); ++it) {
        nb = (*it)->getSpeed();
        if (nb >= 0) {
            std::string str = std::to_string(nb);
            std::wstring widestr = std::wstring(str.begin(), str.end());
            const wchar_t* widecstr = widestr.c_str();
            Snum[(*it)->getPlayerNb() - 1]->setText(widecstr);
        }
    }
}

void CreateGame::printDisplay(irr::video::IVideoDriver* driver, std::vector<Indie::IPlayer*> players)
{
    displayTime(driver);
    PrintBombNb(driver, players);
    PrintFireNb(driver, players);
    PrintSpeedNb(driver, players);
    displayScore(driver, players);
    displayDeath(driver, players);
}

void CreateGame::setTimer(std::clock_t time)
{
    _timer += std::clock() - time;
    //time = _timer - time;
}

std::clock_t CreateGame::getTimer()
{
    return (_timer);
}
