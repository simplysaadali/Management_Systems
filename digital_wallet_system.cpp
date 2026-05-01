
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

// used to check the validation on the phone number, means whther this one is valid or not...
bool isValidPhone(string number){
    if(number.length() != 11)
        return false;
    if(number[0] != '0' && number[1] != '3')
        return false;
    for(char c : number){
        if(!isdigit(c)) return false;
    }
    return true;
}


class Transaction{
    protected:
        long long PhNumber;
        double amount;
        string timeStamp;

    public:
        Transaction() : PhNumber(0), amount(0.0), timeStamp(getCurrentTime()) {}

        Transaction(long long PhoneNumber, double amt){
                this->PhNumber = PhoneNumber;
                this->amount = amt;
                this->timeStamp = getCurrentTime();
        }

// this one used to get the current time for the recipt, time and date...
      string getCurrentTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        char forTime[30];
        strftime(forTime, sizeof(forTime), "%d-%m-%Y %I:%M:%S %p", ltm);

        return string(forTime);
    }

    virtual double calculateCommission() = 0;
    virtual void printReceipt() = 0;

    virtual ~Transaction() {
        ofstream file("log.txt", ios::app);
        file << "Transaction destroyed at " << timeStamp << endl;
        file.close();
    }
};

class MobileLoad : public Transaction{
    public:
        MobileLoad(long long PhoneNumber, double amt) : Transaction(PhoneNumber, amt){}

        double calculateCommission() override {
            double commission = amount * 0.025;
            return (commission < 2) ? 2 : commission;
        }

        void printReceipt() override {
            cout << "Mobile Load Receipt" << endl;
            cout << "Phone Number: " << PhNumber << endl;
            cout << "Amount is:" << amount << endl;
            cout << "Commission: " << calculateCommission() << endl;
            cout << "Timestamp: " << timeStamp << endl;
        }
};

class EasyPaisa : public Transaction{
   private:
        string sender, receiver, type;
    public:
        EasyPaisa(long long PhoneNumber, double amt, string t, string s, string r){
            this->PhNumber = PhoneNumber;
            this->amount = amt;
            this->type = t;
            this->sender = s;
            this->receiver = r;
            this->timeStamp = getCurrentTime();
        }

        double calculateCommission() override {
            if (amount <= 1000)
                return 10;
            else if (amount <= 5000)
                return 25;
            else
                return 25 + 0.003 * (amount - 5000);
        }

        void printReceipt() override {
            cout << "EasyPaisa Receipt" << endl;
            cout << "Phone Number: " << PhNumber << endl;
            cout << "Amount is:" << amount << endl;
            cout << "Commission: " << calculateCommission() << endl;
            cout << "Timestamp: " << timeStamp << endl;
            cout << "Sender: " << sender << endl;
            cout << "Receiver: " << receiver << endl;
        }
};

class SimReplacement : public Transaction{
    private:
        string oldNo, newNo;

    public:
        SimReplacement(long long PhoneNumber, string OldNu, string NewNu) : Transaction(PhoneNumber, 250){
            this->oldNo = OldNu;
            this->newNo = NewNu;
        }

        double calculateCommission() override {
            return 150;
        }

        void printReceipt() override {
            cout << "SIM Replacement Receipt" << endl;
            cout << "Timestamp: " << timeStamp << endl;
            cout << "Old SIM Number: " << oldNo << endl;
            cout << "New SIM Number: " << newNo << endl;
            cout << "Commission: " << calculateCommission() << endl;
        }
};

