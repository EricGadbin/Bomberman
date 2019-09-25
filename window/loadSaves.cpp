#include "../include/MainMenu.hpp"
#include "../include/Event.hpp"
#include <windows.h>

void CMainMenu::LoadSaves()
{
    std::string pattern("../save");
    pattern.append("\\*");
    WIN32_FIND_DATA data;
    HANDLE hFind;
    _saves.push_back("no");
    if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
        do {
            if (strcmp(data.cFileName, ".") != 0 && strcmp(data.cFileName, "..") != 0 &&
            strcmp(data.cFileName, "no") != 0) {
                _saves.push_back(data.cFileName);
        }
        } while (FindNextFile(hFind, &data) != 0);
        FindClose(hFind);
    }
}