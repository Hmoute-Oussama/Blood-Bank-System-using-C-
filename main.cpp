#include <iostream>
#include "managers/DonorManager.h"
#include "managers/BloodInventory.h"
#include "managers/RequestManager.h"
#include "ui/Menu.h"

int main() {
    const std::string DONORS_FILE    = "data/donors.txt";
    const std::string INVENTORY_FILE = "data/inventory.txt";
    const std::string REQUESTS_FILE  = "data/requests.txt";


    DonorManager    donorManager(DONORS_FILE);
    BloodInventory  inventory(INVENTORY_FILE);
    RequestManager  requestManager(REQUESTS_FILE, inventory);

    // ─── Lancement du menu ────────────────────────────────────
    Menu menu(donorManager, inventory, requestManager);
    menu.run();

    return 0;
}