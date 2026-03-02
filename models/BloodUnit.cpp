#include<iostream>
#include "BloodUnit.h"
using namespace std;
// implementation of the constructors :
BloodUnit::BloodUnit() : unitId(0),bloodType(""),donorId(0),donationDate(""),expiryDate(""),quantity(0.0) {}
BloodUnit::BloodUnit(int unitId,string bloodType,int donorId,string donationDate,string expiryDate,double quantity) : unitId(unitId),bloodType(bloodType),donorId(donorId),donationDate(donationDate),expiryDate(expiryDate),quantity(quantity) {}
// implementation of the getters :
int BloodUnit::getUnitId() const {
    return unitId;
}
string BloodUnit::getBloodType() const {
    return bloodType;
}
int BloodUnit::getDonorId() const {
    return donorId;
}
string BloodUnit::getDonationDate() const {
    return donationDate;
}
string BloodUnit::getCollectionDate() const {
    return donationDate;
}
string BloodUnit::getExpiryDate() const {
    return expiryDate;
}
double BloodUnit::getQuantity() const {
    return quantity;
}
// implementation of the setters :
void BloodUnit::setUnitId(int unitId){
    this->unitId = unitId;
}
void BloodUnit::setBloodType(string bloodType){
    this->bloodType = bloodType;
}
void BloodUnit::setDonorId(int donorId){
    this->donorId = donorId;
}
void BloodUnit::setDonationDate(string donationDate){
    this->donationDate = donationDate;
}
void BloodUnit::setExpiryDate(string expiryDate){
    this->expiryDate = expiryDate;
}
void BloodUnit::setQuantity(double quantity){
    this->quantity = quantity;
}
// implementation of the isExpired function :
bool BloodUnit::isExpired(const string& currentDate) const {
    int expY = std::stoi(expiryDate.substr(0, 4));
    int expM = std::stoi(expiryDate.substr(5, 2));
    int expD = std::stoi(expiryDate.substr(8, 2));

    int todayY = std::stoi(currentDate.substr(0, 4));
    int todayM = std::stoi(currentDate.substr(5, 2));
    int todayD = std::stoi(currentDate.substr(8, 2));

    int expTotal   = expY   * 365 + expM   * 30 + expD;
    int todayTotal = todayY * 365 + todayM * 30 + todayD;

    return todayTotal > expTotal;
}
// implementation of the display function :
void BloodUnit::displayBloodUnitInfo() const {
    cout << "────────────────────────────────" << endl;
    cout<<"Unit ID: " << unitId << endl;
    cout<<"Blood Type: " << bloodType << endl;
    cout<<"Donor ID: " << donorId << endl;
    cout<<"Donation Date: " << donationDate << endl;
    cout<<"Expiry Date: " << expiryDate << endl;
    cout<<"Quantity: " << quantity << " ml" << endl;
    cout << "────────────────────────────────" << endl;
}