#include "Menu.h"
#include <iostream>
#include <limits>   // numeric_limits

// ─── Constructeur ─────────────────────────────────────────────

Menu::Menu(DonorManager& dm, BloodInventory& inv, RequestManager& rm)
    : donorManager(dm), inventory(inv), requestManager(rm) {}

// ─── Helpers input ────────────────────────────────────────────

int Menu::getIntInput(const std::string& prompt) const {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            // Input invalide — nettoyer le buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

double Menu::getDoubleInput(const std::string& prompt) const {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::string Menu::getStringInput(const std::string& prompt) const {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

Urgency Menu::getUrgencyInput() const {
    std::cout << "Urgency:\n";
    std::cout << "  [1] Low\n";
    std::cout << "  [2] Medium\n";
    std::cout << "  [3] Critical\n";
    int choice = getIntInput("Choice: ");

    switch (choice) {
        case 1:  return Urgency::Low;
        case 2:  return Urgency::Medium;
        case 3:  return Urgency::Critical;
        default: return Urgency::Low;
    }
}

// ─── Main Loop ────────────────────────────────────────────────

void Menu::run() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n";
        std::cout << "╔══════════════════════════════╗\n";
        std::cout << "║    BLOOD BANK SYSTEM         ║\n";
        std::cout << "╠══════════════════════════════╣\n";
        std::cout << "║  [1] Donor Management        ║\n";
        std::cout << "║  [2] Blood Inventory         ║\n";
        std::cout << "║  [3] Requests                ║\n";
        std::cout << "║  [4] Reports                 ║\n";
        std::cout << "║  [0] Exit                    ║\n";
        std::cout << "╚══════════════════════════════╝\n";

        choice = getIntInput("Choose: ");

        switch (choice) {
            case 1: donorMenu();     break;
            case 2: inventoryMenu(); break;
            case 3: requestMenu();   break;
            case 4: reportsMenu();   break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// ─── Sous-menu Donors ─────────────────────────────────────────

void Menu::donorMenu() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n--- Donor Management ---\n";
        std::cout << "[1] Add Donor\n";
        std::cout << "[2] Remove Donor\n";
        std::cout << "[3] Search Donor\n";
        std::cout << "[4] List All Donors\n";
        std::cout << "[5] List Eligible Donors\n";
        std::cout << "[0] Back\n";

        choice = getIntInput("Choose: ");

        switch (choice) {
            case 1: addDonor();           break;
            case 2: removeDonor();        break;
            case 3: searchDonor();        break;
            case 4: donorManager.listAll(); break;
            case 5: listEligibleDonors(); break;
            case 0: break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// ─── Sous-menu Inventory ──────────────────────────────────────

void Menu::inventoryMenu() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n--- Blood Inventory ---\n";
        std::cout << "[1] Add Blood Unit\n";
        std::cout << "[2] Remove Blood Unit\n";
        std::cout << "[3] Remove Expired Units\n";
        std::cout << "[4] List All Units\n";
        std::cout << "[5] Stock Summary\n";
        std::cout << "[0] Back\n";

        choice = getIntInput("Choose: ");

        switch (choice) {
            case 1: addBloodUnit();            break;
            case 2: removeBloodUnit();         break;
            case 3: removeExpiredUnits();      break;
            case 4: inventory.listAll();       break;
            case 5: inventory.displayStockSummary(); break;
            case 0: break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// ─── Sous-menu Requests ───────────────────────────────────────

void Menu::requestMenu() {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n--- Requests ---\n";
        std::cout << "[1] New Request\n";
        std::cout << "[2] Fulfill Request\n";
        std::cout << "[3] Cancel Request\n";
        std::cout << "[4] List Pending Requests\n";
        std::cout << "[5] List All Requests\n";
        std::cout << "[0] Back\n";

        choice = getIntInput("Choose: ");

        switch (choice) {
            case 1: createRequest();              break;
            case 2: fulfillRequest();             break;
            case 3: cancelRequest();              break;
            case 4: requestManager.listPending(); break;
            case 5: requestManager.listAll();     break;
            case 0: break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

// ─── Sous-menu Reports ────────────────────────────────────────

void Menu::reportsMenu() {
    std::cout << "\n--- Reports ---\n";
    std::cout << "[1] Stock Summary\n";
    std::cout << "[2] Eligible Donors\n";
    std::cout << "[3] Pending Requests by Urgency\n";
    std::cout << "[0] Back\n";

    int choice = getIntInput("Choose: ");

    switch (choice) {
        case 1:
            inventory.displayStockSummary();
            break;
        case 2:
            listEligibleDonors();
            break;
        case 3:
            requestManager.listPending();
            break;
        case 0:
            break;
        default:
            std::cout << "Invalid option.\n";
    }
}

// ─── Actions Donors ───────────────────────────────────────────

void Menu::addDonor() {
    std::cout << "\n-- Add Donor --\n";

    std::string name     = getStringInput("Name: ");
    int age              = getIntInput("Age: ");
    std::string blood    = getStringInput("Blood Type (ex: A+): ");
    std::string phone    = getStringInput("Phone (10 digits): ");
    std::string lastDon  = getStringInput("Last Donation Date (YYYY-MM-DD, leave empty if never): ");

    donorManager.addDonor(name, age, blood, phone, lastDon);
}

void Menu::removeDonor() {
    std::cout << "\n-- Remove Donor --\n";
    int id = getIntInput("Donor ID: ");
    donorManager.removeDonor(id);
}

void Menu::searchDonor() {
    std::cout << "\n-- Search Donor --\n";
    std::cout << "[1] Search by ID\n";
    std::cout << "[2] Search by Name\n";
    std::cout << "[3] Search by Blood Type\n";

    int choice = getIntInput("Choose: ");

    if (choice == 1) {
        int id = getIntInput("Donor ID: ");
        Donor* d = donorManager.findById(id);
        if (d) d->display();
        else std::cout << "Donor not found.\n";

    } else if (choice == 2) {
        std::string name = getStringInput("Name: ");
        auto results = donorManager.findByName(name);
        if (results.empty()) std::cout << "No donors found.\n";
        else for (Donor& d : results) d.display();

    } else if (choice == 3) {
        std::string blood = getStringInput("Blood Type: ");
        auto results = donorManager.findByBloodType(blood);
        if (results.empty()) std::cout << "No donors found.\n";
        else for (Donor& d : results) d.display();
    }
}

void Menu::listEligibleDonors() {
    auto eligible = donorManager.getEligibleDonors();

    std::cout << "\n===== Eligible Donors (" << eligible.size() << ") =====\n";
    if (eligible.empty()) std::cout << "No eligible donors at the moment.\n";
    else for (Donor& d : eligible) d.display();
}

// ─── Actions Inventory ────────────────────────────────────────

void Menu::addBloodUnit() {
    std::cout << "\n-- Add Blood Unit --\n";

    std::string blood    = getStringInput("Blood Type (ex: O+): ");
    int donorId          = getIntInput("Donor ID: ");
    std::string colDate  = getStringInput("Collection Date (YYYY-MM-DD): ");
    double qty           = getDoubleInput("Quantity (ml): ");

    inventory.addBloodUnit(blood, donorId, colDate, qty);
}

void Menu::removeBloodUnit() {
    std::cout << "\n-- Remove Blood Unit --\n";
    int id = getIntInput("Unit ID: ");
    inventory.removeBloodUnit(id);
}

void Menu::removeExpiredUnits() {
    std::cout << "\n-- Remove Expired Units --\n";
    inventory.removeExpiredUnits();
}

// ─── Actions Requests ─────────────────────────────────────────

void Menu::createRequest() {
    std::cout << "\n-- New Blood Request --\n";

    std::string patient = getStringInput("Patient Name: ");
    std::string blood   = getStringInput("Blood Type (ex: B-): ");
    double qty          = getDoubleInput("Quantity needed (ml): ");
    Urgency urgency     = getUrgencyInput();

    requestManager.createRequest(patient, blood, qty, urgency);
}

void Menu::fulfillRequest() {
    std::cout << "\n-- Fulfill Request --\n";
    requestManager.listPending();
    int id = getIntInput("Request ID to fulfill: ");
    requestManager.fulfillRequest(id);
}

void Menu::cancelRequest() {
    std::cout << "\n-- Cancel Request --\n";
    requestManager.listPending();
    int id = getIntInput("Request ID to cancel: ");
    requestManager.cancelRequest(id);
}