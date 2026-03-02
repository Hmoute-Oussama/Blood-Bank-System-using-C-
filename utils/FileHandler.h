#pragma once
#include <string>
#include <vector>
#include "../models/Donor.h"
#include "../models/BloodUnit.h"
#include "../models/Request.h"

class FileHandler {
public:
    // ─── Donors ───────────────────────────────────────────────
    static bool saveDonors(const std::vector<Donor>& donors, const std::string& filename);
    static std::vector<Donor> loadDonors(const std::string& filename);

    // ─── BloodUnits ───────────────────────────────────────────
    static bool saveBloodUnits(const std::vector<BloodUnit>& units, const std::string& filename);
    static std::vector<BloodUnit> loadBloodUnits(const std::string& filename);

    // ─── Requests ─────────────────────────────────────────────
    static bool saveRequests(const std::vector<Request>& requests, const std::string& filename);
    static std::vector<Request> loadRequests(const std::string& filename);

private:
    // Helpers pour convertir les enums en int pour le fichier
    static int urgencyToInt(Urgency u);
    static Urgency intToUrgency(int i);
    static int statusToInt(RequestStatus s);
    static RequestStatus intToStatus(int i);
};