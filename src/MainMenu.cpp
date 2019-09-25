#include "../include/MainMenu.hpp"
#include "../include/Event.hpp"

CMainMenu::CMainMenu()
: MenuDevice(0), selected(2), start(false), fullscreen(true),
	music(true), transparent(true), MenuChoosed(-1)
{
    LoadSaves();
}

std::string CMainMenu::getSelectedLoad() const
{
    if (loadselected == 0)
        return ("no");
    for (int i = 0; i < _saves.size(); i++) {
        if (loadselected == i)
            return (_saves[i]);
    }
    return ("no");
}

void CMainMenu::LoadSavesBox(irr::gui::IGUIEnvironment *guienv, irr::core::recti rect)
{
    std::string narrow_string;
    std::wstring wide_string;
    const wchar_t* widecstr;

    _savesbox = guienv->addListBox(rect, loadTab, 1);
    for (std::vector<std::string>::iterator i = _saves.begin(); i != _saves.end(); i++) {
        narrow_string = *i;
        wide_string = std::wstring(narrow_string.begin(), narrow_string.end());
        const wchar_t* result = wide_string.c_str();
        _savesbox->addItem(result);
    }
    _savesbox->setItemHeight(72);
    _savesbox->setSelected(selected);
}

void CMainMenu::setMenuButton(irr::core::rect<int>rect, irr::gui::IGUITab* page, int id, const wchar_t * text, std::string image)
{
	irr::gui::IGUIButton* OneButton = guienv->addButton(rect, page, id, text);
	OneButton->setImage(driver->getTexture(image.c_str()));
	OneButton->setScaleImage(true);
	OneButton->setUseAlphaChannel(true);
	OneButton->setDrawBorder(0);
	MenuButton.push_back(OneButton);
}

void CMainMenu::resetLibButton()
{
    MenuButton[5]->setImage(driver->getTexture("../assets/boutonr.png"));
    MenuButton[6]->setImage(driver->getTexture("../assets/boutonr.png"));
    MenuButton[7]->setImage(driver->getTexture("../assets/boutonr.png"));
}

void CMainMenu::initMenuButton()
{
	setMenuButton(irr::core::rect<int>(width/2.6,height/2.634,width/1.6,height/2.037), MenuTab, 5, L"1 PLAYER", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/2.6,height/1.963,width/1.6,height/1.611), MenuTab, 6, L"2 PLAYERS", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/2.6,height/1.565,width/1.6,height/1.33), MenuTab, 7, L"LOAD", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/2.6,height/1.3,width/1.6,height/1.137), MenuTab, 8, L"QUIT", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/1.05,height/12,width,height/6.353), MenuTab, 9, L"", "../assets/option.png");

	setMenuButton(irr::core::rect<int>(width/1.65,height/2.634,width/1.16,height/2.037), optTab, 10, L"OpenGL", "../assets/boutonrs.png");
	setMenuButton(irr::core::rect<int>(width/1.65,height/1.862,width/1.16,height/1.543), optTab, 11, L"DirectX 8", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/1.65,height/1.44,width/1.16,height/1.241), optTab, 12, L"DirectX 9", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/8,height/2.634,width/2.5,height/2.037), optTab, 13, L"FullScreen", "../assets/boutonrs.png");
	setMenuButton(irr::core::rect<int>(width/8,height/1.862,width/2.5,height/1.543), optTab, 14, L"Music", "../assets/boutonrs.png");
	setMenuButton(irr::core::rect<int>(width/8,height/1.44,width/2.5,height/1.241), optTab, 18, L"Shadows", "../assets/boutonrs.png");
	setMenuButton(irr::core::rect<int>(width/2.6,height/1.2,width/1.6,height/1.06), optTab, 15, L"Back", "../assets/boutonr.png");

	setMenuButton(irr::core::rect<int>(width/16,height/2.45,width/4,height/1.928), loadTab, 16, L"Load", "../assets/boutonr.png");
	setMenuButton(irr::core::rect<int>(width/16,height/1.8,width/4,height/1.5), loadTab, 17, L"Back", "../assets/boutonr.png");
}

void CMainMenu::HideMenu()
{
	pos = skin->getPosition();
	if (pos.X >= 0 && move) {
		skin->setFrameLoop(27, 76);
		skin->setRotation(irr::core::vector3df(0,10,0));
		move = false;
	} else if (pos.X < 0)
		skin->setPosition(irr::core::vector3df(pos.X + 0.1, pos.Y, pos.Z));
	if (!move)
		driver->draw2DImage(logo, irr::core::position2d<int>(0,0));
	if ((std::clock() - _timer) / static_cast<double>(CLOCKS_PER_SEC) > 1.5) {
		showMenu = true;
		test = false;
		skin->remove();
		fader->setColor(irr::video::SColor(0,0,0,0));
		fader->setMaxSize(irr::core::dimension2du(2000, 2000));
		fader->setMinSize(irr::core::dimension2du(2000, 2000));
		fader->fadeIn(4000);
	}
}

void CMainMenu::ShowMenu()
{
	driver->draw2DImage(irrlichtBack, irr::core::position2d<int>(0,0));
	if (okkk == 0) {
		tabctrl->setActiveTab(MenuTab);
		menuMusic.openFromFile("../menu.wav");
		menuMusic.play();
		menuMusic.setLoop(true);
		okkk = 1;
	}
	if ((std::clock() - _timer) / static_cast<double>(CLOCKS_PER_SEC) > 2 && okk == 0) {
		guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)8, irr::video::SColor(255, 11, 6, 128));
		initMenuButton();
		okk = 1;
	}
	guienv->drawAll();
}

void CMainMenu::setSkin()
{
	skin = smgr->addAnimatedMeshSceneNode(smgr->getMesh("../assets/Bomberman.MD3"));
	skin->setMaterialFlag(irr::video::EMF_LIGHTING, true);
	skin->setAnimationSpeed(30);
	skin->setLoopMode(true);
	skin->setFrameLoop(27, 76);
	skin->setPosition(irr::core::vector3df(-15,0,0));
	skin->setRotation(irr::core::vector3df(0,-90,0));
	skin->setMaterialTexture(0, driver->getTexture("../assets/Bomber.png"));
	skin->setFrameLoop(0, 26);
}

void CMainMenu::initMenu()
{
	driver = MenuDevice->getVideoDriver();
	smgr = MenuDevice->getSceneManager();
	guienv = MenuDevice->getGUIEnvironment();
	newskin = guienv->createSkin(irr::gui::EGST_BURNING_SKIN);
	font = guienv->getFont("../assets/myfont.xml");

	height = driver->getScreenSize().Height;
	width = driver->getScreenSize().Width;

	guienv->setSkin(newskin);
	newskin->drop();
	guienv->getSkin()->setFont(font);
	loadselected = 0;
	fader = MenuDevice->getGUIEnvironment()->addInOutFader();
}

bool CMainMenu::run(mainDevice &MDevice)
{
    creditsMusic.openFromFile("../assets/credits.ogg");
    creditsMusic.play();

    MenuDevice = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1920,1080), 32, true, true, true, this);

    test = true;
    move = true;
    okk = 0;
    okkk = 0;
    showMenu = false;
    shadow = true;

    initMenu();

    for (irr::u32 i = 0; i < 8 ; ++i) {
    	irr::video::SColor color = guienv->getSkin()->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
    	color.setAlpha(0);
    	guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, color);
    }

    // add tab control
    tabctrl = guienv->addTabControl(irr::core::rect<int>(0, -100, 1920, 1080), 0, true, true);
    MenuTab = tabctrl->addTab(L"Menu");
    optTab = tabctrl->addTab(L"Options");
    loadTab = tabctrl->addTab(L"Load");
    EmptyTab = tabctrl->addTab(L"Empty");

    guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)8,irr::video::SColor(255,255,140,0));

    LoadSaves();
    LoadSavesBox(guienv, irr::core::rect<int>(width/3.2,height/2.4,width/1.32,height/1.08));

    // add about text
    irrlichtBack = driver->getTexture("../assets/titlebackground.png");
    logo = driver->getTexture("../assets/credits.png");

    setSkin();

    smgr->addCameraSceneNode(0, irr::core::vector3df(0, 5, -10),irr::core::vector3df(0, 0, 0));
    irr::scene::ILightSceneNode* light = smgr->addLightSceneNode(0, irr::core::vector3df(80, 130, -30), irr::video::SColorf(259.0f, 252.0f, 252.0f, 175.0f), 10000.0f);

    light->getLightData().Type = irr::video::ELT_POINT;
    light->getLightData().AmbientColor = irr::video::SColorf(50.0f, 252.0f, 252.0f, 175.0f);
    light->getLightData().Falloff = false;

    guienv->getSkin()->setColor((irr::gui::EGUI_DEFAULT_COLOR)8, irr::video::SColor(0,0,0,0));
    tabctrl->setActiveTab(EmptyTab);

    while(MenuDevice->run()) {
        if (MenuDevice->isWindowActive()) {
            driver->beginScene(test, true, irr::video::SColor(0,0,0,0));
            if (!showMenu)
            	HideMenu();
            else
            	ShowMenu();
            smgr->drawAll();
            driver->endScene();
        }
    }
    menuMusic.stop();
    MenuDevice->drop();
    MDevice.setFullscreen(fullscreen);
    MDevice.setMusic(music);
    MDevice.setMenuchoosed(MenuChoosed);
    MDevice.setShadows(shadow);
    MDevice.setMusic(music);
    switch(selected) {
        case 2:
            MDevice.setDriver(irr::video::EDT_OPENGL);
            break;
        case 1:
            MDevice.setDriver(irr::video::EDT_DIRECT3D8);
            break;
        case 0:
            MDevice.setDriver(irr::video::EDT_DIRECT3D9);
            break;
    }
    return (start);
}

bool CMainMenu::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EET_GUI_EVENT) {
        irr::s32 id = event.GUIEvent.Caller->getID();
        switch (id) {
            case 45:
                if (event.GUIEvent.EventType == irr::gui::EGET_MENU_ITEM_SELECTED) {
                    irr::s32 s = ((irr::gui::IGUIContextMenu *) event.GUIEvent.Caller)->getSelectedItem();
                    if (s == 0 || s == 1) {
                        transparent = !transparent;
                    }
                }
                break;
            case 5:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    MenuDevice->closeDevice();
                    MenuChoosed = 0;
                    start = true;
                }
                break;
            case 6:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    MenuDevice->closeDevice();
                    MenuChoosed = 1;
                    start = true;
                }
                break;
            case 7:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    tabctrl->setActiveTab(loadTab);
                    start = false;
                }
                break;
            case 8:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    MenuDevice->closeDevice();
                    MenuChoosed = 3;
                    start = false;
                }
                break;
            case 9:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    tabctrl->setActiveTab(optTab);
                    start = false;
                }
                break;
            case 10:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    selected = 2;
                    resetLibButton();
                    MenuButton[5]->setImage(driver->getTexture("../assets/boutonrs.png"));
                    start = false;
                }
                break;
            case 11:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    resetLibButton();
                    MenuButton[6]->setImage(driver->getTexture("../assets/boutonrs.png"));
                    selected = 1;
                    start = false;
                }
                break;
            case 12:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    selected = 0;
                    resetLibButton();
                    MenuButton[7]->setImage(driver->getTexture("../assets/boutonrs.png"));
                    start = false;
                }
                break;
            case 13:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    if (!fullscreen) {
                        fullscreen = true;
                        MenuButton[8]->setImage(driver->getTexture("../assets/boutonrs.png"));
                    } else {
                        fullscreen = false;
                        MenuButton[8]->setImage(driver->getTexture("../assets/boutonr.png"));
                    }
                    start = false;
                }
                break;
            case 14:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    if (!music) {
                        music = true;
                        MenuButton[9]->setImage(driver->getTexture("../assets/boutonrs.png"));
                    } else {
                        music = false;
			MenuButton[9]->setImage(driver->getTexture("../assets/boutonr.png"));
                    }
                    start = false;
                }
                break;
            case 15:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    tabctrl->setActiveTab(MenuTab);
                    start = false;
                }
                break;
            case 16:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    loadselected = _savesbox->getSelected();
                    MenuDevice->closeDevice();
                    MenuChoosed = 1;
                    start = true;
                }
                break;
            case 17:
                if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
                    tabctrl->setActiveTab(MenuTab);
                    start = false;
                }
                break;
            case 18:
		if (event.GUIEvent.EventType == irr::gui::EGET_BUTTON_CLICKED) {
			if (!shadow) {
				shadow = true;
				MenuButton[10]->setImage(driver->getTexture("../assets/boutonrs.png"));
			} else {
				shadow = false;
				MenuButton[10]->setImage(driver->getTexture("../assets/boutonr.png"));
			}
			start = false;
		}
		break;
        }
    }
    return false;
}
