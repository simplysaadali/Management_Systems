#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

// validation for the phone number...
bool isValidPhone(string number) {
    if (number.length() != 11)
        return false;

    if (number.substr(0, 2) != "03")
        return false;

    for (char c : number) {
        if (!isdigit(c)) return false;
    }
    return true;
}

bool isValidAmount(double amount) {
    return amount > 0;
}

class Transaction {
protected:
    string PhNumber;
    double amount;
    string timeStamp;

public:
    Transaction() {
        this->PhNumber = "";
        this->amount = 0.0;
        this->timeStamp = getCurrentTime();
    }

    Transaction(string PhoneNumber, double amt) {
        this->PhNumber = PhoneNumber;
        this->amount = amt;
        this->timeStamp = getCurrentTime();
    }

    // This one used to get the current time and date for the transaction...
    static string getCurrentTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);

        char buffer[30];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S %p", ltm);

        return string(buffer);
    }

    virtual double calculateCommission() = 0;
    virtual void printReceipt() = 0;

    virtual ~Transaction() {
        ofstream file("log.txt", ios::app);
        file << "Transaction destroyed at " << timeStamp << endl;
        file.close();
    }
};

class MobileLoad : public Transaction {
public:
    MobileLoad(string PhoneNumber, double amt)
        : Transaction(PhoneNumber, amt) {}

    double calculateCommission() override {
        double commission = amount * 0.025;
        return (commission < 2) ? 2 : commission;
    }

    void printReceipt() override {
        cout << "\n--- Mobile Load Receipt ---\n";
        cout << "Phone Number: " << PhNumber << endl;
        cout << "Amount: " << amount << endl;
        cout << "Commission: " << calculateCommission() << endl;
        cout << "Timestamp: " << timeStamp << endl;
    }
};

class EasyPaisa : public Transaction {
private:
    string sender, receiver, type;

public:
    EasyPaisa(double amt, string t, string s, string r)
        : Transaction() {
        this->amount = amt;
        this->type = t;
        this->sender = s;
        this->receiver = r;
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
        cout << "\n--- EasyPaisa Receipt ---\n";
        cout << "Phone Number: " << PhNumber << endl;
        cout << "Amount: " << amount << endl;
        cout << "Commission: " << calculateCommission() << endl;
        cout << "Timestamp: " << timeStamp << endl;
        cout << "Sender: " << sender << endl;
        cout << "Receiver: " << receiver << endl;
        cout << "Type: " << type << endl;
    }
};

class SimReplacement : public Transaction {
private:
    string oldNo, newNo;

public:
    SimReplacement(string OldNu, string NewNu)
        : Transaction("SIM_REPLACEMENT", 250) {
        this->oldNo = OldNu;
        this->newNo = NewNu;
    }

    double calculateCommission() override {
        return 150;
    }

    void printReceipt() override {
        cout << "\n--- SIM Replacement Receipt ---\n";
        cout << "Timestamp: " << timeStamp << endl;
        cout << "Old Number: " << oldNo << endl;
        cout << "New Number: " << newNo << endl;
        cout << "Commission: " << calculateCommission() << endl;
    }
};

class DailyLedger {
private:
    vector<Transaction*> t_list;

public:
    void addTransaction(Transaction* t) {
        t_list.push_back(t);
    }

    void printDailyLedger() {
        cout << "\n===== DAILY LEDGER =====\n";
        for (Transaction* t : t_list) {
            t->printReceipt();
            cout << "------------------------\n";
        }
    }

    double totalCommission() {
        double total = 0;
        for (auto t : t_list) {
            total += t->calculateCommission();
        }
        return total;
    }

    ~DailyLedger() {
        for (Transaction* t : t_list) {
            delete t;
        }
    }
};

int main() {
    int choice;
    DailyLedger ledger;

    do {
        cout << "1. Mobile Load" << endl;
        cout << "2. EasyPaisa" << endl;
        cout << "3. SIM Replacement" << endl;
        cout << "4. Show Ledger" << endl;
        cout << "5. Exit" << endl;
        cout << "------------------------" << endl;
        cout << "Enter choice: " <<  endl;
        cin >> choice;

// for Easyload, masn mobile load...
        if (choice == 1) {
            string number;
            double amount;

            while (true) {
                cout << "Enter phone number: ";
                cin >> number;

                if (isValidPhone(number))
                    break;

                cout << "Invalid phone number. Try again.\n";
            }

            while(true){
                cout << "Enter amount: ";
                cin >> amount;

                if (isValidAmount(amount))
                    break;

                cout << "Invalid amount. Try again.\n";
            }

            cout << "---Done---" << endl;

            ledger.addTransaction(new MobileLoad(number, amount));
        }

        // For easypaisa...
        else if (choice == 2) {
            string sender, receiver, direction;
            double amount;

            cout << "Enter direction (in/out): ";
            cin >> direction;

            while (true) {
                cout << "Enter sender number: ";
                cin >> sender;

                if (isValidPhone(sender))
                    break;

                cout << "Invalid phone number. Try again.\n";
            }

            while (true) {
                cout << "Enter sreceiver number: ";
                cin >> receiver;

                if (isValidPhone(receiver))
                    break;

                cout << "Invalid phone number. Try again.\n";
            }

            while(true){
                cout << "Enter amount: ";
                cin >> amount;

                if (isValidAmount(amount))
                    break;

                cout << "Invalid amount. Try again.\n";
            }

            cout << "---Done---" << endl;

            ledger.addTransaction(new EasyPaisa(amount, direction, sender, receiver));
        }

        // This houce number 3 is for sim repllacemnt...
        else if (choice == 3) {
            string oldN, newN;

            while (true) {
                cout << "Old Number: ";
                cin >> oldN;
                if (isValidPhone(oldN)) break;
                cout << "Invalid number. Try again." << endl;
            }

            while (true) {
                cout << "New Number: ";
                cin >> newN;
                if (isValidPhone(newN)) break;
                cout << "Invalid number. Try again." << endl;
            }

            ledger.addTransaction(new SimReplacement(oldN, newN));
            cout << "---Done---" << endl;
        }

        // for the daiy ledger and total commission... and recerptsof the previous task
        else if (choice == 4) {
            ledger.printDailyLedger();
            cout << endl << "Total Commission: " << ledger.totalCommission() << endl;
        }

        // Exit function...
        else if (choice == 5) {
            cout << "Exiting..." << endl;
            cout << "------------------------" << endl;
            exit(0);
        }

        else {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}