#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ─── Helpers Enums ────────────────────────────────────────────

int FileHandler::urgencyToInt(Urgency u) {
    switch(u) {
        case Urgency::Low:      return 0;
        case Urgency::Medium:   return 1;
        case Urgency::Critical: return 2;
        default:                return 0;
    }
}

Urgency FileHandler::intToUrgency(int i) {
    switch(i) {
        case 0:  return Urgency::Low;
        case 1:  return Urgency::Medium;
        case 2:  return Urgency::Critical;
        default: return Urgency::Low;
    }
}

int FileHandler::statusToInt(RequestStatus s) {
    switch(s) {
        case RequestStatus::Pending:   return 0;
        case RequestStatus::Fulfilled: return 1;
        case RequestStatus::Cancelled: return 2;
        default:                       return 0;
    }
}

RequestStatus FileHandler::intToStatus(int i) {
    switch(i) {
        case 0:  return RequestStatus::Pending;
        case 1:  return RequestStatus::Fulfilled;
        case 2:  return RequestStatus::Cancelled;
        default: return RequestStatus::Pending;
    }
}

// ─── Donors ───────────────────────────────────────────────────

// Format dans le fichier (une ligne par donor) :
// id|name|age|bloodType|phone|lastDonationDate

bool FileHandler::saveDonors(const  vector<Donor>& donors, const  string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << "\n";
        return false;
    }

    for (const Donor& d : donors) {
        file << d.getId()             << "|"
             << d.getName()           << "|"
             << d.getAge()            << "|"
             << d.getBloodType()      << "|"
             << d.getPhone()          << "|"
             << d.getLastDonationDate() << "\n";
    }

    file.close();
    return true;
}

vector<Donor> FileHandler::loadDonors(const string& filename) {
    vector<Donor> donors;
    ifstream file(filename);

    if (!file.is_open()) {
        // Fichier n'existe pas encore — pas une erreur, juste vide
        return donors;
    }

    string line;
    while ( getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> fields;

        // Découper la ligne par "|"
        while (getline(ss, token, '|')) {
            fields.push_back(token);
        }

        if (fields.size() != 6) continue; // ligne corrompue → on skip

        int id      = stoi(fields[0]);
        string name = fields[1];
        int age     = stoi(fields[2]);
        string bloodType = fields[3];
        string phone     = fields[4];
        string lastDonation = fields[5];

        donors.push_back(Donor(id, name, age, bloodType, phone, lastDonation));
    }

    file.close();
    return donors;
}

// ─── BloodUnits ───────────────────────────────────────────────

// Format : unitId|bloodType|donorId|collectionDate|expiryDate|quantity

bool FileHandler::saveBloodUnits(const vector<BloodUnit>& units, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << "\n";
        return false;
    }

    for (const BloodUnit& u : units) {
        file << u.getUnitId()        << "|"
             << u.getBloodType()     << "|"
             << u.getDonorId()       << "|"
             << u.getCollectionDate()<< "|"
             << u.getExpiryDate()    << "|"
             << u.getQuantity()      << "\n";
    }

    file.close();
    return true;
}

vector<BloodUnit> FileHandler::loadBloodUnits(const string& filename) {
    vector<BloodUnit> units;
    ifstream file(filename);

    if (!file.is_open()) return units;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> fields;

        while (getline(ss, token, '|')) {
            fields.push_back(token);
        }

        if (fields.size() != 6) continue;

        int unitId          = stoi(fields[0]);
        string bloodType    = fields[1];
        int donorId         = stoi(fields[2]);
        string collectionDate = fields[3];
        string expiryDate     = fields[4];
        double quantity     = stod(fields[5]);

        units.push_back(BloodUnit(unitId, bloodType, donorId,
                                  collectionDate, expiryDate, quantity));
    }

    file.close();
    return units;
}

// ─── Requests ─────────────────────────────────────────────────

// Format : requestId|patientName|bloodType|quantity|urgency|status|date

bool FileHandler::saveRequests(const vector<Request>& requests, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << "\n";
        return false;
    }

    for (const Request& r : requests) {
        file << r.getRequestId()   << "|"
             << r.getPatientName() << "|"
             << r.getBloodType()   << "|"
             << r.getQuantity()    << "|"
             << urgencyToInt(r.getUrgency()) << "|"
             << statusToInt(r.getStatus())   << "|"
             << r.getDate()        << "\n";
    }

    file.close();
    return true;
}

vector<Request> FileHandler::loadRequests(const string& filename) {
    vector<Request> requests;
    ifstream file(filename);

    if (!file.is_open()) return requests;

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        vector<string> fields;

        while (getline(ss, token, '|')) {
            fields.push_back(token);
        }

        if (fields.size() != 7) continue;

        int requestId            = stoi(fields[0]);
        string patientName  = fields[1];
        string bloodType    = fields[2];
        double quantity          = stod(fields[3]);
        Urgency urgency          = intToUrgency(stoi(fields[4]));
        RequestStatus status     = intToStatus(stoi(fields[5]));
        string date         = fields[6];

        Request r(requestId, patientName, bloodType, quantity, urgency, status, date);
        requests.push_back(r);
    }

    file.close();
    return requests;
}