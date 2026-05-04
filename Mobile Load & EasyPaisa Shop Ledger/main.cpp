#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <ctime>
#include <cmath>
#include <limits>

using namespace std;

// validation for the phone number...
bool isValidPhone(string number) {
    // check length
    if (number.length() != 12)
        return false;

    // must start with 03
    if (number.substr(0, 2) != "03")
        return false;

    // dash must be at index 4
    if (number[4] != '-')
        return false;

    // check all characters
    for (int i = 0; i < number.length(); i++) {
        if (i == 4) continue; // skip dash

        if (!isdigit(number[i]))
            return false;
    }

    return true;
}

class Transaction {
protected:
    string PhNumber;
    double amount;
    string timeStamp;

public:
// default construvotr
    Transaction() {
        this->PhNumber = "";
        this->amount = 0.0;
        this->timeStamp = getCurrentTime();
    }

    // fully parametrized constructor...
    Transaction(string PhoneNumber, double amt) {
        this->PhNumber = PhoneNumber;
        this->amount = amt;
        this->timeStamp = getCurrentTime();
    }

    // convenience Constructor...
    Transaction(string PhoneNumber) {
        this->PhNumber = PhoneNumber;
        this->amount = 0.0;   // default value
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
    virtual void saveToFile(ofstream& out) = 0;

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
        return (commission < 2) ? 2 : floor (commission);
    }

    void saveToFile(ofstream& out) override {
        out << "\n--- Mobile Load Receipt ---\n";
        out << "Phone Number: " << PhNumber << endl;
        out << "Amount: " << amount << endl;
        out << "Commission: " << calculateCommission() << endl;
        out << "Timestamp: " << timeStamp << endl;
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
        : Transaction(s, amt) {
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
            return floor(25 + 0.003 * (amount - 5000));
    }

    void saveToFile(ofstream& out) override {
        out << "\n--- EasyPaisa Receipt ---\n";
        out << "Amount: " << amount << endl;
        out << "Commission: " << calculateCommission() << endl;
        out << "Timestamp: " << timeStamp << endl;
        out << "Sender: " << sender << endl;
        out << "Receiver: " << receiver << endl;
        out << "Type: " << type << endl;
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

    void saveToFile(ofstream& out) override {
        out << "\n--- SIM Replacement Receipt ---\n";
        out << "Timestamp: " << timeStamp << endl;
        out << "Old Number: " << oldNo << endl;
        out << "New Number: " << newNo << endl;
        out << "Commission: " << calculateCommission() << endl;
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

    void printRecentTransaction() {
    }

    void printDailyLedger() {
    }

    double totalCommission() {
        double total = 0;
        for (int i = 0; i < t_list.size(); i++) {
            total += t_list[i]->calculateCommission();
        }
        return total;
    }

    void generateReceipt(bool fullLedger) {
        ofstream file("receipt.txt", ios :: app);

        if (!file) {
            cout << "Error creating file!\n";
            return;
        }

        if (fullLedger) {
            file  << endl << "--- DAILY LEDGER ---\n";

            for (int i = 0; i < t_list.size(); i++) {
                t_list[i]->saveToFile(file);
                file << "------------------------\n";
            }

            file << "\nTotal Commission: " << totalCommission() << endl;
        }
        else {
            if (t_list.empty()) {
                file << "No transactions available.\n";
            } else {
                file << "--- MOST RECENT TRANSACTION ---\n";
                t_list.back()->saveToFile(file);
            }
        }

        file.close();
    }

    ~DailyLedger() {
        for (int i = 0; i < t_list.size(); i++) {
            delete t_list[i];
        }
    }
};

int main() {
    DailyLedger ledger;
    string temp;
    int input;
    bool valid = true;


    while (true) {

        cout << endl << "1. Mobile Load" << endl;
        cout << "2. EasyPaisa" << endl;
        cout << "3. SIM Replacement" << endl;
        cout << "4. Show Ledger" << endl;
        cout << "5. Exit" << endl;
        cout << "------------------------" << endl;

        cout << "Enter choice: ";
        cin >> temp;

        // check if ALL characters are digits
        for (int i = 0; i < temp.length(); i++) {
            if (!isdigit(temp[i])) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            cout << "Invalid input! Please enter numbers only.\n";
            continue;
        }

        input = stoi(temp);

        // mobile load...
        if (input == 1) {
            string number;
            string temp;
            double amount;

            while (true) {
                cout << "Enter phone number: ";
                cin >> number;

                if (isValidPhone(number)) break;
                cout << "Invalid phone number. Try again" << endl;
            }

            while (true) {
                cout << "Enter amount: ";
                cin >> temp;

                bool valid = true;

                for (int i = 0; i < temp.length(); i++) {
                    if (!isdigit(temp[i])) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) {
                    cout << "Invalid amount!" << endl;
                    continue;
                }

// string to double...
                amount = stod(temp);

                break;
            }

            ledger.addTransaction(new MobileLoad(number, amount));
            cout << "---Done---\n";
        }

        // Easypaisa...
        else if (input == 2) {
            string sender, receiver, direction, temp;
            double amount;

            cout << "Enter direction (in/out): ";
            cin >> direction;

            while (true) {
                cout << "Enter sender number: ";
                cin >> sender;
                if (isValidPhone(sender)) break;
                cout << "Invalid phone number. Try again.\n";
            }

            while (true) {
                cout << "Enter receiver number: ";
                cin >> receiver;

                if (isValidPhone(receiver)) break;
                cout << "Invalid phone number. Try again.\n";
            }

            while (true) {
                cout << "Enter amount: ";
                cin >> temp;

                bool valid = true;

                for (int i = 0; i < temp.length(); i++) {
                    if (!isdigit(temp[i])) {
                        valid = false;
                        break;
                    }
                }

                if (!valid) {
                    cout << "Invalid amount!" << endl;
                    continue;
                }

                amount = stod(temp);

                break;
            }

            ledger.addTransaction(new EasyPaisa(amount, direction, sender, receiver));
            cout << "---Done---\n";
        }

        //Sim replacement...
        else if (input == 3) {
            string oldN, newN;

            while (true) {
                cout << "Old Number: ";
                cin >> oldN;
                if (isValidPhone(oldN)) break;
                cout << "Invalid number. Try again.\n";
            }

            while (true) {
                cout << "New Number: ";
                cin >> newN;
                if (isValidPhone(newN)) break;
                cout << "Invalid number. Try again.\n";
            }

            ledger.addTransaction(new SimReplacement(oldN, newN));
            cout << "---Done---\n";
        }

        // Ledger...
        else if (input == 4) {
            int subChoice;

            cout << "\n1. Recent Transaction\n";
            cout << "2. Full Day Ledger\n";
            cout << "Enter choice: ";
            cin >> subChoice;

            if (cin.fail()) {
                cin.clear();

                // clear leftover, and removes everyting  until next line...
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input!" << endl;
                continue;
            }

            if (subChoice == 1) {
                ledger.generateReceipt(false);
            }
            else if (subChoice == 2) {
                ledger.generateReceipt(true);
            }
            else {
                cout << "Invalid choice!\n";
            }
        }

        else if (input == 5) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}