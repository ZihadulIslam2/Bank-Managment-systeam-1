#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Bank Account Class
class BankAccount {
private:
    string accountHolderName;
    string accountNumber;
    double balance;

public:

    BankAccount(string name, string accNumber, double initialDeposit) {
        accountHolderName = name;
        accountNumber = accNumber;
        balance = initialDeposit;
    }


    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful. Current balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }


    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful. Current balance: $" << balance << endl;
            return true;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance!" << endl;
            return false;
        }
    }


    bool transferTo(BankAccount &recipient, double amount) {
        if (withdraw(amount)) { // Withdraw from sender
            recipient.deposit(amount); // Deposit to recipient
            cout << "Transfer successful! $" << amount << " transferred to " << recipient.getAccountNumber() << endl;
            return true;
        }
        return false;
    }


    void displayDetails() const {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }

    // Getter for Account Number
    string getAccountNumber() const {
        return accountNumber;
    }
};

// Function to find an account by account number
BankAccount* findAccount(vector<BankAccount> &accounts, const string &accNumber) {
    for (auto &account : accounts) {
        if (account.getAccountNumber() == accNumber) {
            return &account;
        }
    }
    return nullptr; // Account not found
}


int main() {
    vector<BankAccount> accounts; // Vector to store multiple bank accounts
    int choice;

    do {
        cout << "\n===== Bank Management System =====" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Transfer Money" << endl;
        cout << "5. Display Account Details" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name, accNumber;
            double initialDeposit;
            cout << "Enter Account Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Account Number: ";
            cin >> accNumber;
            cout << "Enter Initial Deposit: ";
            cin >> initialDeposit;
            accounts.emplace_back(name, accNumber, initialDeposit);
            cout << "Account created successfully!" << endl;
            break;
        }
        case 2: {
            string accNumber;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            BankAccount* account = findAccount(accounts, accNumber);
            if (account) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                account->deposit(amount);
            } else {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 3: {
            string accNumber;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            BankAccount* account = findAccount(accounts, accNumber);
            if (account) {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                account->withdraw(amount);
            } else {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 4: {
            string senderAcc, recipientAcc;
            double amount;
            cout << "Enter Sender Account Number: ";
            cin >> senderAcc;
            cout << "Enter Recipient Account Number: ";
            cin >> recipientAcc;
            BankAccount* sender = findAccount(accounts, senderAcc);
            BankAccount* recipient = findAccount(accounts, recipientAcc);
            if (sender && recipient) {
                cout << "Enter amount to transfer: ";
                cin >> amount;
                sender->transferTo(*recipient, amount);
            } else {
                cout << "One or both account numbers are invalid!" << endl;
            }
            break;
        }
        case 5: {
            string accNumber;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            BankAccount* account = findAccount(accounts, accNumber);
            if (account) {
                account->displayDetails();
            } else {
                cout << "Account not found!" << endl;
            }
            break;
        }
        case 6:
            cout << "Exiting the system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
