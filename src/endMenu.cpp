/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** Bonus
*/

#include "../include/endMenu.hpp"

#include <sstream>
#include <string>
#include <iomanip>

using namespace Indie;

endMenu::endMenu()
{
}

endMenu::~endMenu()
{
}

int endMenu::setCamera(mainDevice &start, int z)
{
    static irr::core::vector3df Target = start._sceneManager->getActiveCamera()->getTarget();
    static irr::core::vector3df Pos = start._sceneManager->getActiveCamera()->getPosition();

    if (z < 10 && z >= 0) {
        Target.Y -= 16;
        Target.Z -= 16;
        start._sceneManager->getActiveCamera()->setTarget(irr::core::vector3df(Target.X, Target.Y, Target.Z));
        start._sceneManager->getActiveCamera()->setPosition(irr::core::vector3df(Pos.X, Pos.Y, 0));
    } else {
        Pos = start._sceneManager->getActiveCamera()->getPosition();
        Target = start._sceneManager->getActiveCamera()->getTarget();
    }
    z++;
    return (z);
}

void endMenu::setButtonEndScreen(mainDevice &start)
{
    start.getRestartForEndGame()->setImage(start._driver->getTexture("../assets/boutonr.png"));
    start.getRestartForEndGame()->setScaleImage(true);
    start.getRestartForEndGame()->setUseAlphaChannel(true);
    start.getRestartForEndGame()->setDrawBorder(0);
	start.getQuitForEndGame()->setImage(start._driver->getTexture("../assets/boutonr.png"));
    start.getQuitForEndGame()->setScaleImage(true);
    start.getQuitForEndGame()->setUseAlphaChannel(true);
    start.getQuitForEndGame()->setDrawBorder(0);
}

void endMenu::setTextMultPlayerEndScreen(mainDevice &start, int playerID, int final)
{
    std::string playerText;
    std::string Sc;

    if (playerID > -1) {
        playerText = "Player ";
        playerText += std::to_string(playerID);
    } else
        playerText = "All Players";
    if (final)
        playerText += "  shame on you !";
    else
        playerText += "  congratulation !";

    std::wstring widestr(playerText.begin(), playerText.end());
    const wchar_t* widecstr(widestr.c_str());
    start.getPlayerTextForEndGame()->setText(widecstr);
}

void endMenu::setScMultPlayerEndScreen(mainDevice &start, int final, int sc)
{
    std::string Sc;

    Sc = "Score ";
    Sc += std::to_string(sc);
    std::wstring widestr2(Sc.begin(), Sc.end());
    const wchar_t* widecstr2(widestr2.c_str());
    start.getScForEndGame()->setText(widecstr2);
}

void endMenu::setImgPlayerEndScreen(mainDevice &start, int final)
{
    if (final) {
        start.getPlayerHeadForEndGame()->setImage(start._driver->getTexture("../assets/looser.png"));
        start.getTextForEndGame()->setImage(start._driver->getTexture("../assets/gameOver.png"));
    } else {
        start.getPlayerHeadForEndGame()->setImage(start._driver->getTexture("../assets/winner.png"));
        start.getTextForEndGame()->setImage(start._driver->getTexture("../assets/victory.png"));
    }
}

void endMenu::createScreenForEnd(mainDevice &start, int playerID, int final, int sc)
{
    start._device->getCursorControl()-> setVisible(true);
    
    if (playerID > -1)
        setScMultPlayerEndScreen(start, final, sc);
    setTextMultPlayerEndScreen(start, playerID, final);
    setImgPlayerEndScreen(start, final);
    setButtonEndScreen(start);
    start.getTabctrl()->setActiveTab(start.getEndTab());
}

int findAiPlayer(std::vector<Indie::IPlayer*> &players, int ai)
{
    int aiAlive = 0;
    int nbPlayer = 0;

    for (std::vector<Indie::IPlayer*> ::iterator it = players.begin(); it !=players.end(); ++it) {
        if ((*it)->isAlive() == true && (*it)->isAi() == true)
            aiAlive += 1;
        else if ((*it)->isAi() == false)
            nbPlayer += 1;
    }
    if (ai)
        return (aiAlive);
    return(nbPlayer);
}

void endMenu::gameIsOver(std::vector<Indie::IPlayer*> &players, mainDevice &start)
{
    int nbPlayer = 0;
    int playerAlive = 0;
    int playerID_live = -1;
    int playerID_dead = -1;
    int aiAlive = 0;
    int sc = -1;
    static int z = -1;

    aiAlive = findAiPlayer(players, 1);
    nbPlayer = findAiPlayer(players, 0);

    for (std::vector<Indie::IPlayer*> ::iterator it = players.begin(); it !=players.end(); ++it) {
        if (nbPlayer == 1) {
            if ((*it)->isAlive() == true && (*it)->isAi() == false) {
                playerID_live = (*it)->getPlayerNb();
                sc = (*it)->getScore(); 
            }
            if ((*it)->isAlive() != true && (*it)->isAi() == false) {
                playerID_dead = (*it)->getPlayerNb();
                sc = (*it)->getScore(); 
            }
        } else {
            if ((*it)->isAlive() == true && (*it)->isAi() == false) {
                playerID_live = (*it)->getPlayerNb();
                sc = (*it)->getScore();
            } if ((*it)->isAlive() != true && (*it)->isAi() == false)
                playerID_dead = (*it)->getPlayerNb();
        }
        if ((*it)->isAlive() == true && (*it)->isAi() == false) {
            playerAlive += 1;
            playerID_live = (*it)->getPlayerNb();
            sc = (*it)->getScore();
        }
    }

    if (playerAlive == 0 && nbPlayer == 2 && aiAlive == 0) {
        z = setAllDeath(start, sc, z, nbPlayer);
    } else if (playerAlive == 0 && aiAlive > 0)
        z = setDeath(start, sc, playerID_dead, z, nbPlayer);
    else if (aiAlive == 0 && playerAlive > 0) {
        z = setWin(start, playerAlive, playerID_live, sc, z);
    } else
        z = -1;
    
}

int endMenu::setDeath(mainDevice &start, int sc, int id, int z, int nbPlayer)
{
    if (nbPlayer == 1) 
        createScreenForEnd(start, id, 1, sc);
    else
        createScreenForEnd(start, -1, 1, sc);
    _state = LOST;
    return (setCamera(start, z));
}

int endMenu::setAllDeath(mainDevice &start, int sc, int z, int nbPlayer)
{
    _state = LOST;
    createScreenForEnd(start, -1, 1, sc);
    return (setCamera(start, z));
}

int endMenu::setWin(mainDevice &start, int playerAlive, int id, int sc, int z)
{
    if (playerAlive == 1) {
        _state = WON;
        createScreenForEnd(start, id, 0, sc);
        return(setCamera(start, z));
    }
    return (z);
}

endMenu::state_t endMenu::getGameState()
{
    return (_state);
}
