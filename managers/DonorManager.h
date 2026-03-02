#pragma once
#include <vector>
#include <string>
#include "../models/Donor.h"
#include "../utils/FileHandler.h"
#include "../utils/Validator.h"
#include "../utils/DateUtils.h"

class DonorManager {
private:
    std::vector<Donor> donors;
    std::string filename;
    int nextId;  // auto-increment ID

    // Helper privé pour trouver l'index d'un donor par ID
    int findIndexById(int id) const;

public:
    // Constructeur — charge les données depuis le fichier
    DonorManager(const std::string& filename);

    // CRUD
    bool addDonor(const std::string& name, int age, const std::string& bloodType,
                  const std::string& phone, const std::string& lastDonationDate);
    bool removeDonor(int id);
    bool updateLastDonation(int id, const std::string& date);

    // Recherche
    Donor* findById(int id);
    std::vector<Donor> findByName(const std::string& name) const;
    std::vector<Donor> findByBloodType(const std::string& bloodType) const;
    std::vector<Donor> getEligibleDonors() const;

    // Affichage
    void listAll() const;

    // Sauvegarde
    bool save() const;

    // Getter
    const std::vector<Donor>& getAllDonors() const;
};