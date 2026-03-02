#pragma once
#include <string>
using namespace std;
class Validator{
public:
static bool isValidBloodType( const string& bloodType);
static bool isValidAge(int age);
static bool isValidPhone(const  string& phone);
static bool isValidDate(const  string& date);
static bool isValidQuantity(double quantity);
};