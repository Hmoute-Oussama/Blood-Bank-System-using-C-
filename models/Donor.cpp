#include<iostream>
#include "Donor.h"
using namespace std;
// implementation of the constructor :
Donor::Donor() {
    id = 0;
    name = "";
    age = 0;
    bloodType = "";
    phone = "";
    lastDonationDate = "";
}
Donor::Donor(int id, string name,int age,string bloodType,string phone,string date) : id(id),name(name),age(age),bloodType(bloodType),phone(phone),lastDonationDate(date) {}
// implementation of the getters :
int Donor::getId() const {
    return id;
}
string Donor::getName() const {
    return name;
}
int Donor::getAge() const {
    return age;
}
string Donor::getBloodType() const {
    return bloodType;
}
string Donor::getPhone() const {
    return phone;
}
string Donor::getLastDonationDate() const {
    return lastDonationDate;
}
// implementation of the setters :
void Donor::setId(int id){
    this->id = id;
}
void Donor::setName(string name){
    this->name = name;
}
void Donor::setAge(int age){
    this->age = age;
}
void Donor::setBloodType(string bloodType){
    this->bloodType = bloodType;
}
void Donor::setPhone(string phone){
    this->phone = phone;
}
void Donor::setLastDonationDate(string lastDonationDate){
    this->lastDonationDate = lastDonationDate;
}
// implementation of the display function :
void Donor::display() const {
    displayDonorInfo();
}
// implementation of the isEligibleToDonate function :
bool Donor::isEligibleToDonate(const string& currentDate) const {
    // If no previous donation, eligible
    if (lastDonationDate.empty()) {
        return true;
    }

    // Parse dates: YYYY-MM-DD format
    int lastY = std::stoi(lastDonationDate.substr(0, 4));
    int lastM = std::stoi(lastDonationDate.substr(5, 2));
    int lastD = std::stoi(lastDonationDate.substr(8, 2));

    int currY = std::stoi(currentDate.substr(0, 4));
    int currM = std::stoi(currentDate.substr(5, 2));
    int currD = std::stoi(currentDate.substr(8, 2));

    // Convert to days since epoch (approximate)
    int lastTotal   = lastY * 365 + lastM * 30 + lastD;
    int currTotal   = currY * 365 + currM * 30 + currD;
    int daysSince   = currTotal - lastTotal;

    // Standard medical requirement: 56 days (8 weeks) between donations
    return daysSince >= 56;
}
// implementation of the displayDonorInfo function :
void Donor::displayDonorInfo() const {
    cout << "────────────────────────────────" << endl;
    cout<<"ID: " << id << endl;
    cout<<"Name: " << name << endl;
    cout<<"Age: " << age << endl;
    cout<<"Blood Type: " << bloodType << endl;
    cout<<"Phone: " << phone << endl;
    cout<<"Last Donation Date: " << lastDonationDate << endl;
    cout << "────────────────────────────────" << endl;
}