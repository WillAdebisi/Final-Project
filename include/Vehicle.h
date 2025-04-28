#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Vehicle{
    protected:
        int maxDurability;
        int durability;
        int fuelCapacity;
        int currentFuel;
        int speed;
        int vehicleCost;
        int armorCost;
        int gasCost;
        bool isDestroyed;
        int fPurchaseTimes;
        int aPurchaseTimes;
        int sTimesBought;
        int dTimesBought;
        int fcapPurchaseTimes;
        string vehicleType;
        string perk;

    public:
        Vehicle(int dur, int spd, int fuelCap, int cost, int armor, int gas, std::string perk, std::string type) : 
            maxDurability(dur), speed(spd), fuelCapacity(fuelCap), currentFuel(fuelCap), vehicleCost(cost), armorCost(armor), gasCost(gas),
            isDestroyed(false), fPurchaseTimes(0), aPurchaseTimes(0),
            sTimesBought(0), dTimesBought(0),fcapPurchaseTimes(0), durability(dur), perk(perk), vehicleType(type){}
                
        virtual bool takeDamage(int amount){
            durability = max(durability - amount, 0);
            if(durability == 0){
                destroy();
                return false;
            }
            return true;
        }

        virtual void refuel(){
            currentFuel = fuelCapacity;
            cout << "Vehicle Refueled" << endl;
        };
        virtual void repair(){
            durability = maxDurability;
            cout << "Vehicle is repaired" << endl;
        }
        virtual bool upgrade(string statType){
            if(statType == "durability" && dTimesBought < 5){
                maxDurability = min(durability+5, 100);
                if(maxDurability == 100) dTimesBought = 5;
                else dTimesBought++;
                return true;
            } else if(statType == "speed" && sTimesBought < 5){
                speed = min(speed+5, 100);
                if(speed == 100) sTimesBought = 5;
                else sTimesBought++;
                return true;
            }else if(statType == "Fuel Size" && fcapPurchaseTimes < 5){
                fuelCapacity = min(fuelCapacity+5, 100);
                if(fuelCapacity == 100) fcapPurchaseTimes = 5;
                else fcapPurchaseTimes++;
                return true;
            }
            return false;

        }
        virtual void selfHeal(){
            int healAmount = 5;
            durability = min(durability + healAmount, maxDurability);
            cout << "Self-Heal Perk Activated! Recovered 5 durability. Current durability: " << durability << "/" << maxDurability << endl;
        }
        virtual void consumeFuel(){
            int fuelBurn = 10;

            if(perk == "fuel"){
                fuelBurn = 5;
                cout << "Fuel Perk Activated! Less fuel consumed this level.\n";
            }
            currentFuel = max(currentFuel - fuelBurn, 0);
            cout << "Fuel consumed. Remaining fuel: " << currentFuel << endl;
        }

        virtual void destroy(){
            isDestroyed = true;
            cout << "Vehicle destroyed!" << endl;

        }
        void setDurability(int dur) {durability = dur; }
        void setCurrentFuel(int fuel) {currentFuel = fuel; }
        bool getIsDestroyed() const { return isDestroyed; }
        string getPerk() const { return perk; }
        int getfPurchaseTimes() const { return fPurchaseTimes; }
        int getaPurchaseTimes() const { return aPurchaseTimes; }
        int getfcapPurchaseTimes() const { return fcapPurchaseTimes; }
        int getsTimesBought() const { return sTimesBought; }
        int getdTimesBought() const { return dTimesBought; }
        int getSpeed() const { return speed; }
        int getDurability() const { return durability; }
        int getMaxDurability() const {return maxDurability;}
        int getGasCost() const { return gasCost; }
        int getArmorCost() const { return armorCost; }
        int getVehicleCost() const { return vehicleCost; }
        int getCurrentFuel() const { return currentFuel; }
        int getFuelCapacity() const {return fuelCapacity;}
        string getVehicleType() const{return vehicleType;}
        
        virtual ~Vehicle(){};

};
class SpaceX : public Vehicle{
    public:
        SpaceX() : Vehicle(35, 100, 40, 500, 100, 50, std::string("money"), "SpaceX Rocket Buggy"){}
};

class Nasa: public Vehicle{
    public:
        Nasa(): Vehicle(80,50,70,500,100,50,std::string("balanced"), "Nasa Heavy Rover"){}
};

class BlueOrigin : public Vehicle {
    public:
        BlueOrigin(): Vehicle(75, 50, 70, 500, 100, 50, std::string("fuel"), "Blue Origin Hauler"){}

};

class Roscosmos : public Vehicle{
    public:
        Roscosmos() : Vehicle(100, 35, 50, 500, 100, 50, std::string("self-heal"), "Roscosmos Titan"){}
};
#endif