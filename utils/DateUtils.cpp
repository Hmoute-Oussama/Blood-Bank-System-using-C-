#include "DateUtils.h"
#include <ctime>    // time(), localtime()
#include <sstream>  // ostringstream
#include <iomanip>  // setw(), setfill()

// ─── toDays ───────────────────────────────────────────────────

// Convertit "YYYY-MM-DD" en un entier comparable
// C'est la même logique qu'on avait dans Donor et BloodUnit
// mais maintenant centralisée ici — plus de répétition !
int DateUtils::toDays(const std::string& date) {
    int y = std::stoi(date.substr(0, 4));
    int m = std::stoi(date.substr(5, 2));
    int d = std::stoi(date.substr(8, 2));

    return y * 365 + m * 30 + d;
}

// ─── daysBetween ─────────────────────────────────────────────

int DateUtils::daysBetween(const std::string& date1, const std::string& date2) {
    return toDays(date2) - toDays(date1);
}

// ─── isBefore ────────────────────────────────────────────────

bool DateUtils::isBefore(const std::string& date1, const std::string& date2) {
    return toDays(date1) < toDays(date2);
}

// ─── addDays ─────────────────────────────────────────────────

// Ajoute N jours à une date — utile pour calculer l'expiry date
// d'une unité de sang (collectionDate + 42 jours)
std::string DateUtils::addDays(const std::string& date, int days) {
    int y = std::stoi(date.substr(0, 4));
    int m = std::stoi(date.substr(5, 2));
    int d = std::stoi(date.substr(8, 2));

    d += days;

    // Gérer le dépassement des jours dans le mois
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (true) {
        // Année bissextile → février a 29 jours
        int feb = (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 29 : 28;
        daysInMonth[2] = feb;

        if (d <= daysInMonth[m]) break;

        d -= daysInMonth[m];
        m++;

        if (m > 12) {
            m = 1;
            y++;
        }
    }

    // Formater en "YYYY-MM-DD" avec les zéros si nécessaire
    std::ostringstream oss;
    oss << y << "-"
        << std::setw(2) << std::setfill('0') << m << "-"
        << std::setw(2) << std::setfill('0') << d;

    return oss.str();
}

// ─── today ───────────────────────────────────────────────────

// Utilise la librairie <ctime> pour récupérer la date système
std::string DateUtils::today() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::ostringstream oss;
    oss << (1900 + ltm->tm_year) << "-"
        << std::setw(2) << std::setfill('0') << (1 + ltm->tm_mon) << "-"
        << std::setw(2) << std::setfill('0') << ltm->tm_mday;

    return oss.str();
}