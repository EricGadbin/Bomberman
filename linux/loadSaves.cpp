#include "../include/MainMenu.hpp"
#include "../include/Event.hpp"
#include <dirent.h>

void CMainMenu::LoadSaves()
{
    std::string path = "../save";
    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;

    _saves.clear();
    _saves.push_back("no");
    while ((dp = readdir(dirp)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 &&
        strcmp(dp->d_name, "no") != 0) {
            _saves.push_back(dp->d_name);
        }
    }
    closedir(dirp);
}