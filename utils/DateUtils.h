#pragma once
#include <string>

class DateUtils {
public:
    // Convertit une date "YYYY-MM-DD" en nombre de jours total (pour comparer)
    static int toDays(const std::string& date);

    // Calcule la différence en jours entre deux dates (date2 - date1)
    static int daysBetween(const std::string& date1, const std::string& date2);

    // Vérifie si date1 est avant date2
    static bool isBefore(const std::string& date1, const std::string& date2);

    // Ajoute N jours à une date et retourne la nouvelle date "YYYY-MM-DD"
    static std::string addDays(const std::string& date, int days);

    // Retourne la date d'aujourd'hui "YYYY-MM-DD"
    static std::string today();
};