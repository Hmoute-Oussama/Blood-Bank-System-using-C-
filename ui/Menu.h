#pragma once
#include <string>
#include "../managers/DonorManager.h"
#include "../managers/BloodInventory.h"
#include "../managers/RequestManager.h"

class Menu {
private:
    DonorManager& donorManager;
    BloodInventory& inventory;
    RequestManager& requestManager;

    // ─── Helpers input ────────────────────────────────────────
    int getIntInput(const std::string& prompt) const;
    double getDoubleInput(const std::string& prompt) const;
    std::string getStringInput(const std::string& prompt) const;
    Urgency getUrgencyInput() const;

    // ─── Sous-menus ───────────────────────────────────────────
    void donorMenu();
    void inventoryMenu();
    void requestMenu();
    void reportsMenu();

    // ─── Actions Donors ───────────────────────────────────────
    void addDonor();
    void removeDonor();
    void searchDonor();
    void listEligibleDonors();

    // ─── Actions Inventory ────────────────────────────────────
    void addBloodUnit();
    void removeBloodUnit();
    void removeExpiredUnits();

    // ─── Actions Requests ─────────────────────────────────────
    void createRequest();
    void fulfillRequest();
    void cancelRequest();

public:
    Menu(DonorManager& dm, BloodInventory& inv, RequestManager& rm);
    void run();
};