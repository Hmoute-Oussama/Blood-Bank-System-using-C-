#include<string>
#pragma once
using namespace std;
class Donor{
private:
int id;
string name;
int age;
string bloodType;
string phone;
string lastDonationDate;
public:
Donor();
Donor(int id, string name,int age,string bloodtype,string phone,string date);
// getters :
int getId() const;
string getName() const;
int getAge() const;
string getBloodType() const;
string getPhone() const;
string getLastDonationDate() const;
// setters :
void setId(int id);
void setName(string name);
void setAge(int age);
void setBloodType(string bloodType);
void setPhone(string phone);
void setLastDonationDate(string lastDonateDate);
void display() const;
bool isEligibleToDonate(const string& currentDate) const;
void displayDonorInfo() const;
};
