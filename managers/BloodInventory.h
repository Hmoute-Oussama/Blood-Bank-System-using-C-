#pragma once
#include <vector>
#include <string>
#include <map>
#include "../models/BloodUnit.h"
#include "../utils/FileHandler.h"
#include "../utils/Validator.h"
#include "../utils/DateUtils.h"

class BloodInventory {
private:
    std::vector<BloodUnit> units;
    std::string filename;
    int nextId;

    int findIndexById(int unitId) const;

public:
    // Constructeur
    BloodInventory(const std::string& filename);

    // CRUD
    bool addBloodUnit(const std::string& bloodType, int donorId,
                      const std::string& collectionDate, double quantity);
    bool removeBloodUnit(int unitId);

    // Logique métier
    int removeExpiredUnits();   // retourne le nombre d'unités supprimées
    bool fulfillQuantity(const std::string& bloodType, double quantity);  // pour les requests

    // Recherche & Stats
    std::vector<BloodUnit> getByBloodType(const std::string& bloodType) const;
    double getTotalQuantity(const std::string& bloodType) const;
    std::map<std::string, double> getStockSummary() const;

    // Affichage
    void listAll() const;
    void displayStockSummary() const;

    // Sauvegarde
    bool save() const;

    const std::vector<BloodUnit>& getAllUnits() const;
};