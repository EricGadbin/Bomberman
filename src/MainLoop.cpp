/*
** EPITECH PROJECT, 2019
** INDIE_STUDIO
** File description:
** main
*/

#include "../include/MainLoop.hpp"

using namespace Indie;

MainLoop::MainLoop()
{
}

MainLoop::~MainLoop()
{
}

void MainLoop::setRestart(mainDevice &start, sf::Music &music)
{
    if (start._receiver.getState() == 2) {
	    music.stop();
        CMainMenu newmenu;
        mainDevice newstart;
        start._receiver.setState(0);
        if (newmenu.run(newstart)) {
            newstart.setDevice();
            newstart.setVideoDriver(newstart._device->getVideoDriver());
            newstart.setSceneManager(newstart._device->getSceneManager());
            GameLoop(newstart, newmenu.getSelectedLoad());
        }
    }
}

void MainLoop::checkStats(std::vector<IPlayer*> bombers, mainDevice &start, Map &map, CreateGame &game, pauseMenu &pause)
{
     for (std::vector<IPlayer*> ::iterator it = bombers.begin(); pause.isPaused() == false && it != bombers.end(); ++it) {
            if ((*it)->isAlive() == true) {
                (*it)->moveplayer(start, &start._receiver, map, bombers);
            }
            (*it)->dropBomb(start._sceneManager, start._driver, &start._receiver);
            (*it)->checkBombs(map, bombers, start);
            if ((*it)->isMeg()) {
                (*it)->setMeg(false);
                game.BonusPlayerUIs[(it - bombers.begin()) + 4]->setImage(start._driver->getTexture("../assets/megumin.png"));
            }
            if ((*it)->isSanic()) {
                (*it)->setSanic(false);
                game.BonusPlayerUIs[(it - bombers.begin()) + 8]->setImage(start._driver->getTexture("../assets/sanic.png"));
            }
        }
}
void MainLoop::setBasics(mainDevice &start, sf::Music &music, CreateGame &game)
{
    music.openFromFile("../music.wav");
    if (start.getMusic())
        music.play();
    else
        music.pause();
    music.setLoop(true);
    music.setVolume(25);
    srand(time(NULL));
    start._device->getCursorControl()-> setVisible(false);
    game.createCamera(start, 25, 30, 6);
    game.createLight(start, irr::video::ELT_DIRECTIONAL, irr::video::SColorf(50.0f, 252.0f, 252.0f, 175.0f), true);
    game.createTerrain(start);
}

void MainLoop::GameLoop(mainDevice &start, std::string ns)
{
    sf::Music music;
    CreateGame game(25, 30, 6);
    endMenu end;
    std::vector<IPlayer*> bombers = game.createPlayer(start);
    Map map(start._sceneManager, 20, start._driver);
    irr::gui::IGUIEnvironment* guienv1 = game.createGUI(start);
    pauseMenu pause(start, guienv1);

    setBasics(start, music, game);
    if (ns != "no")
        map.load_save(ns, bombers, start);
    while (start._device->run()) {
        game.rotateCamera(start, 15, bombers);
        start._driver->beginScene(true, true, irr::video::SColor(0,30,30,30));
        start._sceneManager->drawAll();
        guienv1->drawAll();
        start._driver->endScene();
        checkStats(bombers, start, map, game, pause);
        if (pause.isPaused() == true) {
            for (std::vector<IPlayer*> ::iterator it = bombers.begin(); it != bombers.end(); ++it) {
                for (std::vector<Bomb>::iterator its = (*it)->getBombs()->begin(); its != (*it)->getBombs()->end(); its++)
                    its->start_time();
            }
        }
        pause.isRun(start, map, bombers, game, guienv1, end);
        game.printDisplay(start._driver, bombers);
        end.gameIsOver(bombers, start);
    }
    start._device->drop();
    for (IPlayer *player : bombers)
        delete player;
    setRestart(start, music);
    return;
}
