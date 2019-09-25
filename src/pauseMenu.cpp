/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Bonus
*/

#include "../include/pauseMenu.hpp"

using namespace Indie;

pauseMenu::pauseMenu(mainDevice &start, irr::gui::IGUIEnvironment* &guienv)
{
    irr::gui::IGUITab* PauseTab = start.getTabctrl()->addTab(L"Pause");

    float height = start._driver->getScreenSize().Height;
	float width = start._driver->getScreenSize().Width;
	irr::gui::IGUIButton* SaveButton = guienv->addButton(irr::core::rect<int>(width/2.6,height/1.6,width/1.6,height/1.37), PauseTab, 23, L"SAVE");
    SaveButton->setImage(start._driver->getTexture("../assets/boutonr.png"));
    SaveButton->setScaleImage(true);
    SaveButton->setUseAlphaChannel(true);
    SaveButton->setDrawBorder(0);
    Buttons.push_back(SaveButton);
    irr::gui::IGUIButton* Quit = guienv->addButton(irr::core::rect<int>(width/2.6,height/1.33,width/1.6,height/1.16), PauseTab, 21, L"QUIT");
    Quit->setImage(start._driver->getTexture("../assets/boutonr.png"));
    Quit->setScaleImage(true);
    Quit->setUseAlphaChannel(true);
    Quit->setDrawBorder(0);
    Buttons.push_back(Quit);
    irr::gui::IGUIButton* Return = guienv->addButton(irr::core::rect<int>(width/2.6,height/3,width/1.6,height/2), PauseTab, 19, L"RETURN TO MENU");
    Return->setImage(start._driver->getTexture("../assets/boutonr.png"));
    Return->setScaleImage(true);
    Return->setUseAlphaChannel(true);
    Return->setDrawBorder(0);
    Buttons.push_back(Return);
}

pauseMenu::~pauseMenu()
{
}

bool pauseMenu::isPaused()
{
    return (_isPaused);
}

void pauseMenu::setPause(mainDevice &start, bool state, irr::gui::IGUIEnvironment* &guienv)
{
    _isPaused = state;
    if (state == false) {
        for (irr::u32 i = 0; i < 8 ; ++i) {
            irr::video::SColor color = guienv->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
            color.setAlpha(0);
            guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, color);
        }
        start.getTabctrl()->setActiveTab(start.getTabctrl()->getTab(0));
        start._device->getCursorControl()-> setVisible(false);
    } else {
        for (irr::u32 i = 0; i < 8 ; ++i) {
            irr::video::SColor color = guienv->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
            color.setRed(120);
            color.setAlpha(200);
            guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, color);
        }
        start.getTabctrl()->setActiveTab(start.getTabctrl()->getTab(2));
        start._device->getCursorControl()-> setVisible(true);
    }
}

void pauseMenu::start_cooldown()
{
    _cooldown = std::clock();
}

bool pauseMenu::get_cooldown() const
{
    return ((std::clock() - _cooldown) / static_cast<double>(CLOCKS_PER_SEC) >= _cooldownDuration);
}

void pauseMenu::manageTimer(CreateGame &game)
{
    if (_isPaused == true) {
        _saveTimer = std::clock();
    } else {
        game.setTimer(_saveTimer);
    }
}

void pauseMenu::isRun(mainDevice &start, Map &map, std::vector<Indie::IPlayer *> bombers, CreateGame &game, irr::gui::IGUIEnvironment* guienv, endMenu &end)
{
    if (start._receiver.getState() == 3) {
            map.create_save(bombers);

            start._receiver.setState(0);
        }
        if (start._receiver.getState() == 2 || start._receiver.getState() == 4) {
            start._device->closeDevice();
        }
        if (start._receiver.IsKeyDown(irr::KEY_ESCAPE) && get_cooldown() == true || !isPaused() && (end.getGameState() == Indie::endMenu::state_t::LOST || end.getGameState() == Indie::endMenu::state_t::WON)) {
            setPause(start, !isPaused(), guienv);
            manageTimer(game);
            start_cooldown();
        }
}
