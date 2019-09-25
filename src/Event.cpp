/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Event
*/

#include "../include/Event.hpp"

MyEventReceiver::MyEventReceiver()
{
    for (irr::u32 i=0; i< irr::KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
}

bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    if (event.EventType == irr::EET_GUI_EVENT) {
        switch (event.GUIEvent.Caller->getID()) {
            case 19:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
                    state = 2;
                break;
            case 21:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
                    state = 4;
                break;
            case 23:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED)
                    state = 3;
                break;
        }
    }
        return false;
}

bool MyEventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return KeyIsDown[keyCode];
}

int MyEventReceiver::getState() {
    return (state);
}

void MyEventReceiver::setState(int s) {
    state = s;
}