#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Payable{
    protected:
        string name;
        string category;

    public:
        Payable(string n, string c) {
            this->name = n;
            this->category = c;
        }

        virtual double calculateGrossPay() = 0;
        virtual double calculateTax() = 0;

        double calculatePay(){
            double pay = calculateGrossPay() - calculateTax();
            return pay;
        }

        string getName(){
            return name;
        }
        string getCategory(){
            return category;
        }

        virtual void generatePaySlip(string month){
            double gross = calculateGrossPay();
            double tax = calculateTax();
            double net = calculatePay();

            // setting the spaces from left side so that it looks the same in the table...
            cout << left << setw(22) << name
                 << left << setw(25) << category
                 << left << setw(15) << gross
                 << left << setw(15) << tax
                 << left << setw(15) << net
                 << " | Month: " << month << endl;
        }

        virtual void generatePaySlip(string startDate, string endDate){
            double gross = calculateGrossPay();
            double tax = calculateTax();
            double net = calculatePay();

            cout << left << setw(22) << name
             << left << setw(25) << category
             << left << setw(15) << gross
             << left << setw(15) << tax
             << left << setw(15) << net
             << " | Period: " << startDate << " to " << endDate << endl;
        }

        virtual ~Payable(){}; // if we don' do virtual, it will not run destructor of child class, we have t do that by ourselves...
};

// consulant doctor class...
class ConsultantDoctor : public Payable{
    private:
        int consultationMoney;
        double surgeryFees;

    public:
    // constructor gets the name of the doctor and th money and the fees he takes as parameters...
        ConsultantDoctor(string name, int cMoney, double Fees) : Payable(name, "Consultant Doctor"){
            this->consultationMoney = cMoney;
            this->surgeryFees = Fees;
        }

        double calculateGrossPay() override{
            return (consultationMoney * 3500) + (surgeryFees * 0.40); //accroding to the condition...
        }

        double calculateTax() override{
            return calculateGrossPay() * 0.15; // 15% tax for consultant doctor...
        }
};

class SalariedDoctor : public Payable{
    protected:
        double fixedSalary;
        int emergencyNights;

    public:
        SalariedDoctor(string name, double salary, int nights) : Payable(name, "Salaried Doctor"){
            this->fixedSalary = salary;
            this->emergencyNights = nights;
        }

        double calculateGrossPay() override{
            return fixedSalary + (emergencyNights * 2000);
        }

        double calculateTax() override {
            if (calculateGrossPay() <= 50000){
                return 0;
            }
            else if(calculateGrossPay() > 50000 && calculateGrossPay() <= 100000){
                return calculateGrossPay() * 0.05; // 5% tax for gross pay between 50,000 and 100,000
            }
            else{
                return calculateGrossPay() * 0.125; // 12.5% tax for gross pay between 100,000 and 150,000
            }
        }
};

// Senior nurse class...
class SeniorNurse : public Payable{
    protected:
        double salary;
        int nightShifts;
        int yearsOfWork;
    
    public:
        SeniorNurse(string name, double salary, int nightShifts, int years) : Payable(name, "Senior Nurse"){
            this->salary = salary;
            this->nightShifts = nightShifts;
            this->yearsOfWork = years;
        }

        double calculateGrossPay() override {
            double bonus = (yearsOfWork > 5) ? 1500 : 0;
            return salary + (nightShifts * 800) + bonus;
        }

        double calculateTax() override {
            if (calculateGrossPay() <= 50000){
                return 0;
            }
            else if(calculateGrossPay() > 50000 && calculateGrossPay() <= 100000){
                return calculateGrossPay() * 0.05; // 5% tax for gross pay between 50,000 and 100,000
            }
            else{
                return calculateGrossPay() * 0.125; // 12.5% tax for gross pay between 100,000 and 150,000
            }
        }
};

class JuniorNurse : public Payable{
    protected:
        double salary;
    
    public:
        JuniorNurse(string name, double salary) : Payable(name, "Junior Nurse"){
            this->salary = salary;
        }

        double calculateGrossPay() override {
            return salary;
        }

        double calculateTax() override {
            return calculateGrossPay() * 0.025; // 2.5% tax for junior nurse...
        }
};

// Housekeeping guy...
class WardBoy : public Payable{
    protected:
        double dailyWage;
        int daysWorked;
        bool eidBonus;

    public:
        WardBoy(string name, double wage, int days, bool isEid ) : Payable(name, "Ward Boy"){ // bool as it showsd yes or no, means eid yes or no...
            this->dailyWage = wage;
            this->daysWorked = days;
            this->eidBonus = isEid;
        }

        double calculateGrossPay() override {
            double gross = dailyWage * daysWorked;
            if (eidBonus) {
                gross += dailyWage * 7; // Adding eid bonus if applicable
            }
            return gross;
        }

        double calculateTax() override {
            return 0;
        }
};

// Admin staff class...
class AdminStaff : public Payable{
    protected:
        double salary;
    
    public:
        AdminStaff (string name, double salary) : Payable (name, "Admin Staff"){
            this->salary = salary;
        }

        double calculateGrossPay() override {
            return salary;
        }

        double calculateTax() override {
            if (calculateGrossPay() <= 50000) 
                return 0;
            else if (calculateGrossPay() <= 100000)
                return calculateGrossPay() * 0.05;
            else
                return calculateGrossPay() * 0.125;
        }
};

int main(){
    vector<Payable*> staff;

    // push_back is used to add the staff to the vector list ctreated as asked in the code...

    staff.push_back(new ConsultantDoctor("Dr. Saad", 45, 250000));
    staff.push_back(new ConsultantDoctor("Dr. Aman", 30, 180000));

    staff.push_back(new SalariedDoctor("Dr. Zahid", 120000, 4));
    staff.push_back(new SalariedDoctor("Dr. Nauman", 85000, 6));

    staff.push_back(new SeniorNurse("Nurse Imama", 55000, 8, 7)); // >5 yrs
    staff.push_back(new SeniorNurse("Nurse Faiza", 52000, 5, 3)); // ≤5 yrs

    staff.push_back(new JuniorNurse("Nurse Javeria", 38000));
    staff.push_back(new JuniorNurse("Nurse Insa", 36000));

    staff.push_back(new WardBoy("Huzaifa Ansar", 1200, 26, false));
    staff.push_back(new WardBoy("Husnain Mukhtar", 1100, 26, true)); // Eid month gives the bonus bonus

    staff.push_back(new AdminStaff("Akber Ali", 75000));
    staff.push_back(new AdminStaff("Alishba", 48000));

    // print the header of the table...
    cout << left
         << setw(22) << "Name"
         << setw(25) << "Category"
         << left
         << setw(15) << "Gross (Rs.)"
         << left << setw(15) << "Tax (Rs.)"
         << left << setw(15) << "Net (Rs.)" << endl;

    cout << string(92, '-') << endl; // this will create a line to for the table to be separated from thr values...

    for (Payable* p : staff) {
        double gross = p->calculateGrossPay();
        double tax = p->calculateTax();
        double net = p->calculatePay();

        cout << left << setw(22) << p->getName()
             << setw(25) << p->getCategory()
             << setw(15) << gross
             << setw(15) << tax
             << setw(15) << net << endl;
    }

    cout << "Testing some of them by accessing" << endl;
    staff[0]->generatePaySlip("May 2026");
    staff[1]->generatePaySlip("01-May", "31-May");

    // cleanup of the code that we've created, cause ithose were n heap, not stack... deletion manually...
    for (Payable* p : staff) {
        delete p;
    }

    return 0;
}