#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "GameManager.h"
#include <fstream>
#include <string>

class SaveSystem {
    public:
        static void saveGame(GameManager* game);
        static void loadGame(GameManager* game);
    private:
        SaveSystem() = delete;

    };  


#endif