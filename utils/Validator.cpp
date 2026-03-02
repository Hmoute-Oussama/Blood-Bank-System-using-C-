#include "Validator.h"
#include <cctype>
bool Validator::isValidBloodType(const std::string& bloodType) {
    const std::string validTypes[] = {
        "A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"
    };

    for (const std::string& t : validTypes) {
        if (bloodType == t) return true;
    }
    return false;
}
bool Validator::isValidAge(int age) {
    return age >= 18 && age <= 65;
}

bool Validator::isValidPhone(const std::string& phone) {
    if (phone.length() != 10) return false;

    for (char c : phone) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}
bool Validator::isValidDate(const std::string& date) {
    if (date.length() != 10) return false; 
    if (date[4] != '-' || date[7] != '-') return false;  
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) return false;
    }

    
    int month = std::stoi(date.substr(5, 2));
    int day   = std::stoi(date.substr(8, 2));

    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31)     return false;

    return true;
}
bool Validator::isValidQuantity(double quantity) {
    return quantity > 0.0 && quantity <= 500.0;
}