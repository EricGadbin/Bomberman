 /*
** EPITECH PROJECT, 2019
** INDIE
** File description:
** Map
*/

#ifndef EVENT_H
# define EVENT_H

#include "includes.hpp"

class MyEventReceiver: public irr::IEventReceiver {
    public:
        MyEventReceiver();
        virtual bool OnEvent(const irr::SEvent& event);
        virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const;
        int getState();
        void setState(int s);

    private:
        bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
        int state = 0;
};

#endif