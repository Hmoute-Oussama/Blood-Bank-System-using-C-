#pragma once
#include <vector>
#include <string>
#include "../models/Request.h"
#include "../managers/BloodInventory.h"
#include "../utils/FileHandler.h"
#include "../utils/Validator.h"
#include "../utils/DateUtils.h"

class RequestManager {
private:
    std::vector<Request> requests;
    std::string filename;
    int nextId;
    BloodInventory& inventory;  // référence — pas une copie !

    int findIndexById(int requestId) const;

public:
    // Constructeur — prend une référence à BloodInventory
    RequestManager(const std::string& filename, BloodInventory& inventory);

    // Créer une demande
    bool createRequest(const std::string& patientName, const std::string& bloodType,
                       double quantity, Urgency urgency);

    // Fulfiller une demande (consomme le stock)
    bool fulfillRequest(int requestId);

    // Annuler
    bool cancelRequest(int requestId);

    // Recherche & filtres
    std::vector<Request> getPendingRequests() const;
    std::vector<Request> getByStatus(RequestStatus status) const;
    std::vector<Request> getByBloodType(const std::string& bloodType) const;
    std::vector<Request> getSortedByUrgency() const;

    // Affichage
    void listAll() const;
    void listPending() const;

    // Sauvegarde
    bool save() const;

    const std::vector<Request>& getAllRequests() const;
};