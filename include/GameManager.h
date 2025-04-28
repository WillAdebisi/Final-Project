#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Vehicle.h"
#include "Event.h"
using namespace std;

class GameManager{
    private:
        int currentLevel;
        int score;
        int coins;
        int fuelCost;
        int armorCost;
        vector <Vehicle*>ownedVehicles;
        Vehicle* activeVehicle;
        bool gameOver;
        const float MULTIPLIER = 1.25;
        vector<Event*> eventQueue;
    
    public:
        int getCurrentLevel() const { return currentLevel; }
        int getCoins() const { return coins; }
        int getScore() const {return score; }
        Vehicle* getActiveVehicle() const { return activeVehicle; }
        vector <Vehicle*> getOwnedVehicles() const { return ownedVehicles; }
        void reset(int lvl, int c, int s, Vehicle* v){
            currentLevel = lvl;
            coins = c;
            score = s;
            activeVehicle = v;
            ownedVehicles.clear();
            ownedVehicles.push_back(v);
            gameOver = false;
        }
        void addVehicle(Vehicle* v){
            ownedVehicles.push_back(v);
        }
        GameManager(Vehicle* vh) 
        : currentLevel(1), score(0), coins(500),
         fuelCost(50), armorCost(100), gameOver(false),
         activeVehicle(vh) {
            ownedVehicles.push_back(vh);
         }
        void startGame(){
            while(!gameOver){
                runLevel();
                if(!gameOver){
                    if(activeVehicle->getPerk() == "self-heal"){
                        activeVehicle->selfHeal();
                    }
                    showStats();
                    postLevelEvent();
                }
                currentLevel++;
            }
            endGame();
        }
        void handleDestroyedVehicle(){
            if(!activeVehicle || !activeVehicle -> getIsDestroyed()) return;
            cout << "Removing destroyed vehicle..." << endl;

            ownedVehicles.erase(
                remove(ownedVehicles.begin(), ownedVehicles.end(), activeVehicle),
                ownedVehicles.end()
            );

            switchVehicle();
        }
        void deductCoins(int amount){
            coins = max(coins-amount, 0);
        }
        Event* generateRandomEvent(){
            int roll = rand() % 100;
            if (roll < 30) return new ZombieAttack();
            else if (roll < 55) return new RoadObstacle();
            else if (roll < 75) return new MeteorShower();
            else if (roll < 90) return new BanditAmbush();
            else return new SupplyCrate();
        }
        void runLevel(){
            int obstacleCount = calculateObstacles(activeVehicle -> getSpeed());
            for (int i = 0; i < obstacleCount; ++i){
                Event* e = generateRandomEvent();
                e -> trigger(activeVehicle, this);
                handleDestroyedVehicle();
                delete e;

                if(gameOver){
                    return;
                }
                int reward = static_cast<int>(100 * pow(MULTIPLIER, currentLevel));
                if (activeVehicle->getPerk() == "money") {
                    reward = static_cast<int>(reward * 1.25); // Boost reward by 25%
                    cout << "Money Perk Activated! Bonus coins earned!\n";
                }
                
                coins += reward;
                score += reward;
                cout << "You earned " << reward << " coins!\n";
                cout << "Current Score: " << score << endl;
            }1
            activeVehicle -> consumeFuel();
            if(activeVehicle -> getCurrentFuel()<= 0){
                cout << "You ran out of fuel and your vehicle was destroyed!\n";
                activeVehicle -> destroy();
                handleDestroyedVehicle();
            }

        }
        void postLevelEvent(){
            int roll = rand() % 100;
            cout << "\n--- Post Level Event ---\n";

            if(roll < 30){
                cout << "You found a Mechanic Shop! Repair 10 durability for 100 coins? (1 = Yes, 2 = No): ";
                int choice;
                cin >> choice;
                if (choice == 1 && coins >= 100){
                    activeVehicle -> repair();
                    coins -= 100;
                    cout << "Durability repaired!\n";
                } else if (choice == 1) {
                    cout << "Not enough coins.\n";
                }

                }else if(roll < 60){
                cout << "You found a Gas Station! Refuel tank for 75 coins? (1 = yes, 2 = no): \n";
                int choice;
                cin >> choice;
                if(choice == 1 && coins >= 75){
                    activeVehicle -> refuel();
                    coins -= 75;
                    cout << "Vehicle refueled!\n";
                } else if (choice == 1){
                    cout << "Not enough coins.\n";
                }
                }
                else if(roll < 85){
                    cout << "You found a Vehicle Shop! Which vehicle would you like to buy?\n";
                    cout << "1) SpaceX Rocket Buggy (300 coins)\n";
                    cout << "2) NASA Heavy Rover (500 coins)\n";
                    cout << "3) Blue Origin Hauler (400 coins)\n";
                    cout << "4) Roscosmos Titan (450 coins)\n";
                    cout << "5) No thanks\n";
                    cout << "Choice: ";
                    int choice;
                    cin >> choice;
                    switch (choice){
                        case 1:
                            if(coins >= 300){
                                Vehicle* newCar = new SpaceX();
                                ownedVehicles.push_back(newCar);
                                coins -= 300;
                                cout << "SpaceX Rocket Buggy added to your garage!\n";
                            }else{
                                cout << "Not enough coins.\n";
                            }
                            break;
                            case 2:
                            if (coins >= 500) {
                                Vehicle* newCar = new Nasa();
                                ownedVehicles.push_back(newCar);
                                coins -= 500;
                                cout << "NASA Heavy Rover added to your garage!\n";
                            } else {
                                cout << "Not enough coins.\n";
                            }
                            break;
                        case 3:
                            if (coins >= 400) {
                                Vehicle* newCar = new BlueOrigin();
                                ownedVehicles.push_back(newCar);
                                coins -= 400;
                                cout << "Blue Origin Hauler added to your garage!\n";
                            } else {
                                cout << "Not enough coins.\n";
                            }
                            break;
                        case 4:
                            if (coins >= 450) {
                                Vehicle* newCar = new Roscosmos();
                                ownedVehicles.push_back(newCar);
                                coins -= 450;
                                cout << "Roscosmos Titan added to your garage!\n";
                            } else {
                                cout << "Not enough coins.\n";
                            }
                            break;
                        case 5:
                            cout << "No vehicle purchased.\n";
                            break;
                        default:
                            cout << "Invalid choice.\n";
                            break;
                    }
                }
    
        }
        bool isGameOver() const{return gameOver; }
        void increaseLevel() {currentLevel++;}
        
        int calculateObstacles(int speed){
            if (speed <= 45) return 5;
            if (speed <= 60) return 4;
            if (speed <= 75) return 3;
            if (speed <= 90) return 2;
            return 1;
        }

        void handleEvent(Event* e){
            e->trigger(activeVehicle, this);
        }
        void switchVehicle(){
            if(ownedVehicles.empty()){
                cout << "No vehicles left to switch to. \n";
                gameOver = true;
                return;
            }

            activeVehicle = ownedVehicles.front();
            cout << "Switching to a new vehicle....\n";
        }
        void showStats(){
            cout << "\n=== CURRENT STATUS ===\n";
            cout << "Current Vehicle:\n";
            cout << "Vehicle Type: " << activeVehicle->getVehicleType() << endl;
            cout << "Durability: " << activeVehicle->getDurability() << "/" << activeVehicle->getMaxDurability() << endl;
            cout << "Fuel: " << activeVehicle->getCurrentFuel() << "/" << activeVehicle->getFuelCapacity() << endl;
            cout << "Speed: " << activeVehicle->getSpeed() << endl;
            cout << "Perk: " << activeVehicle->getPerk() << endl;
            cout << "------------------------\n";
            cout << "Coins: " << coins << endl;
            cout << "Score: " << score << endl;
            cout << "Garage Vehicles Owned: " << ownedVehicles.size() << endl;
            cout << "Garage: ";
            for (size_t i = 0; i < ownedVehicles.size(); ++i) {
                cout << ownedVehicles[i]->getVehicleType();
                if (i != ownedVehicles.size() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;

            cout << "========================\n";
        }
        void endGame(){
            cout << "\n=== GAME OVER ===\n";
            cout << "Final Level Reached: " << currentLevel << endl;
            cout << "Total Coins Remaining: " << coins << endl;
            cout << "Score: " << score << endl;
            cout << "Thanks for playing Wasteland Runners!\n";
        }


};
#endif