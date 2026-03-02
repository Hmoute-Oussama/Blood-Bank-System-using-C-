#include "RequestManager.h"
#include <iostream>
#include <algorithm>  // sort()

// ─── Constructeur ─────────────────────────────────────────────

RequestManager::RequestManager(const std::string& filename, BloodInventory& inventory)
    : filename(filename), inventory(inventory), nextId(1) {

    requests = FileHandler::loadRequests(filename);

    for (const Request& r : requests) {
        if (r.getRequestId() >= nextId) {
            nextId = r.getRequestId() + 1;
        }
    }
}

// ─── Helper privé ─────────────────────────────────────────────

int RequestManager::findIndexById(int requestId) const {
    for (int i = 0; i < (int)requests.size(); i++) {
        if (requests[i].getRequestId() == requestId) return i;
    }
    return -1;
}

// ─── Créer une demande ────────────────────────────────────────

bool RequestManager::createRequest(const std::string& patientName,
                                    const std::string& bloodType,
                                    double quantity, Urgency urgency) {

    if (!Validator::isValidBloodType(bloodType)) {
        std::cerr << "Error: Invalid blood type.\n";
        return false;
    }
    if (!Validator::isValidQuantity(quantity)) {
        std::cerr << "Error: Invalid quantity.\n";
        return false;
    }
    if (patientName.empty()) {
        std::cerr << "Error: Patient name cannot be empty.\n";
        return false;
    }

    std::string todayDate = DateUtils::today();
    Request newRequest(nextId++, patientName, bloodType, quantity, urgency, RequestStatus::Pending, todayDate);
    requests.push_back(newRequest);

    // Afficher un avertissement si stock insuffisant
    double available = inventory.getTotalQuantity(bloodType);
    if (available < quantity) {
        std::cout << "⚠ Warning: Insufficient stock for this request.\n"
                  << "  Available: " << available << "ml | Requested: " << quantity << "ml\n";
    }

    std::cout << "Request created with ID: " << (nextId - 1) << "\n";
    return save();
}

// ─── Fulfiller une demande ────────────────────────────────────

bool RequestManager::fulfillRequest(int requestId) {
    int index = findIndexById(requestId);

    if (index == -1) {
        std::cerr << "Error: Request ID " << requestId << " not found.\n";
        return false;
    }

    Request& r = requests[index];

    if (r.getStatus() != RequestStatus::Pending) {
        std::cerr << "Error: Request is already " << r.statusToString() << ".\n";
        return false;
    }

    // Essayer de consommer le stock via BloodInventory
    bool success = inventory.fulfillQuantity(r.getBloodType(), r.getQuantity());

    if (!success) {
        std::cerr << "Error: Could not fulfill request — insufficient stock.\n";
        return false;
    }

    r.setStatus(RequestStatus::Fulfilled);
    std::cout << "Request ID " << requestId << " fulfilled successfully.\n";
    return save();
}

// ─── Annuler ──────────────────────────────────────────────────

bool RequestManager::cancelRequest(int requestId) {
    int index = findIndexById(requestId);

    if (index == -1) {
        std::cerr << "Error: Request ID " << requestId << " not found.\n";
        return false;
    }

    Request& r = requests[index];

    if (r.getStatus() == RequestStatus::Fulfilled) {
        std::cerr << "Error: Cannot cancel an already fulfilled request.\n";
        return false;
    }
    if (r.getStatus() == RequestStatus::Cancelled) {
        std::cerr << "Error: Request is already cancelled.\n";
        return false;
    }

    r.setStatus(RequestStatus::Cancelled);
    std::cout << "Request ID " << requestId << " cancelled.\n";
    return save();
}

// ─── Recherche & Filtres ──────────────────────────────────────

std::vector<Request> RequestManager::getPendingRequests() const {
    return getByStatus(RequestStatus::Pending);
}

std::vector<Request> RequestManager::getByStatus(RequestStatus status) const {
    std::vector<Request> results;

    for (const Request& r : requests) {
        if (r.getStatus() == status) {
            results.push_back(r);
        }
    }

    return results;
}

std::vector<Request> RequestManager::getByBloodType(const std::string& bloodType) const {
    std::vector<Request> results;

    for (const Request& r : requests) {
        if (r.getBloodType() == bloodType) {
            results.push_back(r);
        }
    }

    return results;
}

std::vector<Request> RequestManager::getSortedByUrgency() const {
    std::vector<Request> sorted = requests;

    // Trier : CRITICAL en premier, LOW en dernier
    std::sort(sorted.begin(), sorted.end(), [](const Request& a, const Request& b) {
        return static_cast<int>(a.getUrgency()) > static_cast<int>(b.getUrgency());
    });

    return sorted;
}

// ─── Affichage ────────────────────────────────────────────────

void RequestManager::listAll() const {
    if (requests.empty()) {
        std::cout << "No requests found.\n";
        return;
    }

    std::cout << "\n===== All Requests (" << requests.size() << ") =====\n";
    for (const Request& r : requests) {
        r.display();
    }
}

void RequestManager::listPending() const {
    std::vector<Request> sorted = getSortedByUrgency();
    bool found = false;

    std::cout << "\n===== Pending Requests (by urgency) =====\n";
    for (const Request& r : sorted) {
        if (r.getStatus() == RequestStatus::Pending) {
            r.display();
            found = true;
        }
    }

    if (!found) std::cout << "No pending requests.\n";
}

// ─── Sauvegarde ───────────────────────────────────────────────

bool RequestManager::save() const {
    return FileHandler::saveRequests(requests, filename);
}

const std::vector<Request>& RequestManager::getAllRequests() const {
    return requests;
}