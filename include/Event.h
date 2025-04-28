#ifndef EVENT_H
#define EVENT_H

#include "Vehicle.h"
#include <cstdlib>
#include <ctime>

class GameManager;

class Event {

public:
    virtual void trigger(Vehicle* v, GameManager* g) = 0;
    virtual ~Event() {}
};

// ---------- ZombieAttack ----------
class ZombieAttack : public Event {
private:
    int damageAmount;

public:
    ZombieAttack(int dmg =5); // only DECLARATION
    void trigger(Vehicle* v, GameManager* g) override;
};

// ---------- MeteorShower ----------
class MeteorShower : public Event {
private:
    int damageAmount;

public:
    MeteorShower(int dmg = 20); // only DECLARATION
    void trigger(Vehicle* v, GameManager* g) override;
};

// ---------- RoadObstacle ----------
class RoadObstacle : public Event {
private:
    int damageAmount;

public:
    RoadObstacle(int dmg = 10); // only DECLARATION
    void trigger(Vehicle* v, GameManager* g) override;
};

// ---------- BanditAmbush ----------
class BanditAmbush : public Event {
public:
    void trigger(Vehicle* v, GameManager* g) override;
};

// ---------- SupplyCrate ----------
class SupplyCrate : public Event {
public:
    void trigger(Vehicle* v, GameManager* g) override;
};

#endif
