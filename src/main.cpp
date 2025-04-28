#include <iostream>
#include <ctime>
#include "GameManager.h"
#include "Vehicle.h"
#include "SaveSystem.h"

using namespace std;

int main() {
    srand(time(0)); // seed random

    cout << "=== WASTELAND RUNNERS ===" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "Choice: ";
    int choice;
    cin >> choice;

    GameManager* game = nullptr;

    if(choice == 1){
        cout << "Choose your starter vehicle:\n\n";
        cout << "1. SpaceX Rocket Buggy       | Speed: 100 | Durability: 35 | Fuel: 40 | Perk: Extra Money\n";
        cout << "2. NASA Heavy Rover        | Speed: 50  | Durability: 80 | Fuel: 70 | Perk: N/A\n";
        cout << "3. Blue Origin Hauler  | Speed: 50  | Durability: 75 | Fuel: 70 | Perk: Lesser Fuel\n";
        cout << "4. Roscosmos Titan    | Speed: 35  | Durability: 100| Fuel: 50 | Perk: Self Repair\n";

        int vChoice;
        cin >> vChoice;

        Vehicle* starter = nullptr;

        switch (vChoice) {
            case 1: starter = new SpaceX(); break;
            case 2: starter = new Nasa(); break;
            case 3: starter = new BlueOrigin(); break;
            case 4: starter = new Roscosmos(); break;
            default:
                cout << "Invalid choice. Defaulting to SpaceX.\n";
                starter = new SpaceX();
                break;
        }

        game = new GameManager(starter);
    }
    else if (choice==2){
        Vehicle* dummy = new SpaceX();
        game = new GameManager(dummy);
        SaveSystem::loadGame(game);
    }
    else {
        cout << "Invalid option. Exiting...\n";
        return 0;
    }
    
    while(true){
        game->runLevel();

        if (game->isGameOver()){
            break;
        }

        if(!game -> isGameOver()){
            if(game->getActiveVehicle()->getPerk()=="self-heal"){
                game->getActiveVehicle()->selfHeal();
            }
            game->showStats();
            game->postLevelEvent();

            cout << "\n1. Continue" << endl;
            cout << "2. Save and Exit" << endl;
            cout << "Choice: ";
            int nextChoice;
            cin >> nextChoice;

            if(nextChoice==2){
                SaveSystem::saveGame(game);
                cout << "Game saved. Exiting..." << endl;
                break;
            }
        }
        game->increaseLevel();
    }
    game->endGame();
    delete game;
    return 0;
}   
