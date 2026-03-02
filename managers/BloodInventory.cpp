#include "BloodInventory.h"
#include <iostream>
#include <algorithm>  // sort()

// ─── Constructeur ─────────────────────────────────────────────

BloodInventory::BloodInventory(const std::string& filename) : filename(filename), nextId(1) {
    units = FileHandler::loadBloodUnits(filename);

    for (const BloodUnit& u : units) {
        if (u.getUnitId() >= nextId) {
            nextId = u.getUnitId() + 1;
        }
    }
}

// ─── Helper privé ─────────────────────────────────────────────

int BloodInventory::findIndexById(int unitId) const {
    for (int i = 0; i < (int)units.size(); i++) {
        if (units[i].getUnitId() == unitId) return i;
    }
    return -1;
}

// ─── CRUD ─────────────────────────────────────────────────────

bool BloodInventory::addBloodUnit(const std::string& bloodType, int donorId,
                                   const std::string& collectionDate, double quantity) {

    if (!Validator::isValidBloodType(bloodType)) {
        std::cerr << "Error: Invalid blood type.\n";
        return false;
    }
    if (!Validator::isValidDate(collectionDate)) {
        std::cerr << "Error: Invalid collection date.\n";
        return false;
    }
    if (!Validator::isValidQuantity(quantity)) {
        std::cerr << "Error: Invalid quantity. Must be between 0 and 500ml.\n";
        return false;
    }

    // Expiry = collection + 42 jours (standard médical)
    std::string expiryDate = DateUtils::addDays(collectionDate, 42);

    BloodUnit newUnit(nextId++, bloodType, donorId, collectionDate, expiryDate, quantity);
    units.push_back(newUnit);

    std::cout << "Blood unit added. ID: " << (nextId - 1)
              << " | Expires: " << expiryDate << "\n";

    return save();
}

bool BloodInventory::removeBloodUnit(int unitId) {
    int index = findIndexById(unitId);

    if (index == -1) {
        std::cerr << "Error: Blood unit ID " << unitId << " not found.\n";
        return false;
    }

    units.erase(units.begin() + index);
    std::cout << "Blood unit ID " << unitId << " removed.\n";
    return save();
}

// ─── Logique métier ───────────────────────────────────────────

int BloodInventory::removeExpiredUnits() {
    std::string todayDate = DateUtils::today();
    int count = 0;

    // Parcourir en sens inverse pour supprimer sans décaler les index
    for (int i = (int)units.size() - 1; i >= 0; i--) {
        if (units[i].isExpired(todayDate)) {
            units.erase(units.begin() + i);
            count++;
        }
    }

    if (count > 0) {
        std::cout << count << " expired unit(s) removed.\n";
        save();
    } else {
        std::cout << "No expired units found.\n";
    }

    return count;
}

bool BloodInventory::fulfillQuantity(const std::string& bloodType, double quantity) {
    // Vérifier si on a assez en stock
    double available = getTotalQuantity(bloodType);

    if (available < quantity) {
        std::cerr << "Error: Not enough " << bloodType << " in stock. "
                  << "Available: " << available << "ml, Requested: " << quantity << "ml\n";
        return false;
    }

    double remaining = quantity;

    // Consommer les unités les plus anciennes en premier (FIFO)
    // Trier par date de collection croissante
    std::sort(units.begin(), units.end(), [](const BloodUnit& a, const BloodUnit& b) {
        return a.getDonationDate() < b.getDonationDate();
    });

    for (int i = (int)units.size() - 1; i >= 0 && remaining > 0; i--) {
        if (units[i].getBloodType() != bloodType) continue;

        double unitQty = units[i].getQuantity();

        if (unitQty <= remaining) {
            // Consommer cette unité entièrement
            remaining -= unitQty;
            units.erase(units.begin() + i);
        } else {
            // Consommer partiellement
            units[i].setQuantity(unitQty - remaining);
            remaining = 0;
        }
    }

    return save();
}

// ─── Recherche & Stats ────────────────────────────────────────

std::vector<BloodUnit> BloodInventory::getByBloodType(const std::string& bloodType) const {
    std::vector<BloodUnit> results;

    for (const BloodUnit& u : units) {
        if (u.getBloodType() == bloodType) {
            results.push_back(u);
        }
    }

    return results;
}

double BloodInventory::getTotalQuantity(const std::string& bloodType) const {
    double total = 0.0;

    for (const BloodUnit& u : units) {
        if (u.getBloodType() == bloodType) {
            total += u.getQuantity();
        }
    }

    return total;
}

std::map<std::string, double> BloodInventory::getStockSummary() const {
    std::map<std::string, double> summary;

    // Initialiser tous les groupes à 0
    const std::string types[] = {"A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"};
    for (const std::string& t : types) {
        summary[t] = 0.0;
    }

    // Additionner les quantités
    for (const BloodUnit& u : units) {
        summary[u.getBloodType()] += u.getQuantity();
    }

    return summary;
}

// ─── Affichage ────────────────────────────────────────────────

void BloodInventory::listAll() const {
    if (units.empty()) {
        std::cout << "No blood units in inventory.\n";
        return;
    }

    std::cout << "\n===== Blood Inventory (" << units.size() << " units) =====\n";
    for (const BloodUnit& u : units) {
        u.displayBloodUnitInfo();
    }
}

void BloodInventory::displayStockSummary() const {
    std::map<std::string, double> summary = getStockSummary();

    std::cout << "\n===== Stock Summary =====\n";
    for (const auto& pair : summary) {
        std::cout << pair.first << " : " << pair.second << " ml";

        // Avertissement si stock bas (moins de 450ml = moins d'une unité)
        if (pair.second < 450.0) {
            std::cout << "  ⚠ LOW STOCK";
        }

        std::cout << "\n";
    }
    std::cout << "=========================\n";
}

// ─── Sauvegarde ───────────────────────────────────────────────

bool BloodInventory::save() const {
    return FileHandler::saveBloodUnits(units, filename);
}

const std::vector<BloodUnit>& BloodInventory::getAllUnits() const {
    return units;
}