#include "Event.h"
#include "GameManager.h"

using namespace std;

// ---------- ZombieAttack ----------
ZombieAttack::ZombieAttack(int dmg) : damageAmount(dmg) {}

void ZombieAttack::trigger(Vehicle* v, GameManager* g) {
    cout << "Zombie attack! -" << damageAmount << " durability.\n";
    if (!v->takeDamage(damageAmount)) {
        cout << "Your vehicle was destroyed by zombies!\n";
        v->destroy();
    }
}

// ---------- MeteorShower ----------
MeteorShower::MeteorShower(int dmg) : damageAmount(dmg) {}

void MeteorShower::trigger(Vehicle* v, GameManager* g) {
    cout << "Meteor Shower Incoming! -" << damageAmount << " durability.\n";
    if (!v->takeDamage(damageAmount)) {
        cout << "Your vehicle was destroyed by a meteor shower!\n";
        v->destroy();
    }
}

// ---------- RoadObstacle ----------
RoadObstacle::RoadObstacle(int dmg) : damageAmount(dmg) {}

void RoadObstacle::trigger(Vehicle* v, GameManager* g) {
    cout << "You ran into a wall! -" << damageAmount << " durability.\n";
    if (!v->takeDamage(damageAmount)) {
        cout << "Your vehicle was destroyed by a wall!\n";
        v->destroy();
    }
}

// ---------- BanditAmbush ----------
void BanditAmbush::trigger(Vehicle* v, GameManager* g) {
    int loss = (rand() % 46 + 25);
    cout << "Bandits ambushed you and stole " << loss << " coins!\n";
    g->deductCoins(loss);
}

// ---------- SupplyCrate ----------
void SupplyCrate::trigger(Vehicle* v, GameManager* g) {
    int choice = rand() % 2;
    if (choice == 1) {
        v->refuel();
        cout << "Fuel crate found! Fuel restored.\n";
    } else {
        v->repair();
        cout << "Armor crate found! Durability restored.\n";
    }
}
