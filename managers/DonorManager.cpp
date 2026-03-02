#include "DonorManager.h"
#include <iostream>
#include <algorithm>  // transform() pour lowercase

// ─── Constructeur ─────────────────────────────────────────────

DonorManager::DonorManager(const std::string& filename) : filename(filename), nextId(1) {
    // Charger les donors existants depuis le fichier
    donors = FileHandler::loadDonors(filename);

    // Calculer le prochain ID disponible
    for (const Donor& d : donors) {
        if (d.getId() >= nextId) {
            nextId = d.getId() + 1;
        }
    }
}

// ─── Helper privé ─────────────────────────────────────────────

int DonorManager::findIndexById(int id) const {
    for (int i = 0; i < (int)donors.size(); i++) {
        if (donors[i].getId() == id) return i;
    }
    return -1;  // pas trouvé
}

// ─── CRUD ─────────────────────────────────────────────────────

bool DonorManager::addDonor(const std::string& name, int age, const std::string& bloodType,
                             const std::string& phone, const std::string& lastDonationDate) {

    // Validation des inputs
    if (!Validator::isValidAge(age)) {
        std::cerr << "Error: Invalid age. Must be between 18 and 65.\n";
        return false;
    }
    if (!Validator::isValidBloodType(bloodType)) {
        std::cerr << "Error: Invalid blood type.\n";
        return false;
    }
    if (!Validator::isValidPhone(phone)) {
        std::cerr << "Error: Invalid phone number. Must be 10 digits.\n";
        return false;
    }
    if (!lastDonationDate.empty() && !Validator::isValidDate(lastDonationDate)) {
        std::cerr << "Error: Invalid date format. Use YYYY-MM-DD.\n";
        return false;
    }

    // Créer et ajouter le donor
    Donor newDonor(nextId++, name, age, bloodType, phone, lastDonationDate);
    donors.push_back(newDonor);

    std::cout << "Donor added successfully with ID: " << (nextId - 1) << "\n";
    return save();
}

bool DonorManager::removeDonor(int id) {
    int index = findIndexById(id);

    if (index == -1) {
        std::cerr << "Error: Donor with ID " << id << " not found.\n";
        return false;
    }

    donors.erase(donors.begin() + index);
    std::cout << "Donor ID " << id << " removed successfully.\n";
    return save();
}

bool DonorManager::updateLastDonation(int id, const std::string& date) {
    if (!Validator::isValidDate(date)) {
        std::cerr << "Error: Invalid date format. Use YYYY-MM-DD.\n";
        return false;
    }

    int index = findIndexById(id);
    if (index == -1) {
        std::cerr << "Error: Donor with ID " << id << " not found.\n";
        return false;
    }

    donors[index].setLastDonationDate(date);
    std::cout << "Last donation date updated for Donor ID " << id << "\n";
    return save();
}

// ─── Recherche ────────────────────────────────────────────────

Donor* DonorManager::findById(int id) {
    int index = findIndexById(id);
    if (index == -1) return nullptr;
    return &donors[index];
}

std::vector<Donor> DonorManager::findByName(const std::string& name) const {
    std::vector<Donor> results;

    // Recherche case-insensitive
    std::string nameLower = name;
    std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

    for (const Donor& d : donors) {
        std::string donorNameLower = d.getName();
        std::transform(donorNameLower.begin(), donorNameLower.end(), donorNameLower.begin(), ::tolower);

        // Cherche si le nom contient le terme recherché (pas forcément exact)
        if (donorNameLower.find(nameLower) != std::string::npos) {
            results.push_back(d);
        }
    }

    return results;
}

std::vector<Donor> DonorManager::findByBloodType(const std::string& bloodType) const {
    std::vector<Donor> results;

    for (const Donor& d : donors) {
        if (d.getBloodType() == bloodType) {
            results.push_back(d);
        }
    }

    return results;
}

std::vector<Donor> DonorManager::getEligibleDonors() const {
    std::vector<Donor> results;
    std::string todayDate = DateUtils::today();

    for (const Donor& d : donors) {
        if (d.isEligibleToDonate(todayDate)) {
            results.push_back(d);
        }
    }

    return results;
}

// ─── Affichage ────────────────────────────────────────────────

void DonorManager::listAll() const {
    if (donors.empty()) {
        std::cout << "No donors registered.\n";
        return;
    }

    std::cout << "\n===== All Donors (" << donors.size() << ") =====\n";
    for (const Donor& d : donors) {
        d.display();
    }
}

// ─── Sauvegarde ───────────────────────────────────────────────

bool DonorManager::save() const {
    return FileHandler::saveDonors(donors, filename);
}

// ─── Getter ───────────────────────────────────────────────────

const std::vector<Donor>& DonorManager::getAllDonors() const {
    return donors;
}