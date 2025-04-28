#include "SaveSystem.h"
#include <fstream>

using namespace std;

void SaveSystem::saveGame(GameManager* game){
    ofstream outFile("save.txt");
    if(!outFile){
        cout << "Error opening save file.\n";
        return;
    }

    outFile << game -> getCurrentLevel() << " "
            << game -> getCoins() << " "
            << game -> getScore() << endl;
    
    outFile << game -> getActiveVehicle() -> getVehicleType() << " "
            << game -> getActiveVehicle() -> getDurability() << " "
            << game -> getActiveVehicle() -> getCurrentFuel() << endl;

    outFile << game -> getOwnedVehicles().size() << endl;
    for (auto v : game->getOwnedVehicles()) {
        outFile << v->getVehicleType() << " "
                << v->getDurability() << " "
                << v->getCurrentFuel() << endl;
    }

    outFile.close();
    cout << "Game saved successfully to save.txt!\n";
}

void SaveSystem::loadGame(GameManager* game){
    string filename;
    cout << "Enter the save file name to load from: ";
    cin >> filename;

    ifstream inFile(filename);
    if(!inFile){
        cout << "Save file not found. Starting new game.\n";
        return;
    }
    int level, coins, score;
    inFile >> level >> coins >> score;

    string activeType;
    int activeDur, activeFuel;
    inFile >> activeType >> activeDur >> activeFuel;

    Vehicle* activeVehicle = nullptr;
    if (activeType == "SpaceX Rocket Buggy") activeVehicle = new SpaceX();
    else if (activeType == "Nasa Heavy Rover") activeVehicle = new Nasa();
    else if (activeType == "Blue Origin Hauler") activeVehicle = new BlueOrigin();
    else if (activeType == "Roscosmos Titan") activeVehicle = new Roscosmos();

    if(activeVehicle){
        activeVehicle->setDurability(activeDur);
        activeVehicle->setCurrentFuel(activeFuel);
    }

    game -> reset(level, coins, score, activeVehicle);

    int garageSize;
    inFile >> garageSize;
    for (int i = 0; i < garageSize; ++i){
        string type;
        int dur, fuel;
        inFile >> type >> dur >> fuel;

        Vehicle* v = nullptr;
        if (type == "SpaceX Rocket Buggy") v = new SpaceX();
        else if (type == "Nasa Heavy Rover") v = new Nasa();
        else if (type == "Blue Origin Hauler") v = new BlueOrigin();
        else if (type == "Roscosmos Titan") v = new Roscosmos();

        if (v) {
            v->setDurability(dur);
            v->setCurrentFuel(fuel);
            game->addVehicle(v);
        }
    }

    inFile.close();
    cout << "Game loaded successfully from " << filename << "!\n";
}
