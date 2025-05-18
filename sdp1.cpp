#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class ATM {
private:
    string username;
    string pin;
    double balance=0.0;

public:


    int login() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter PIN: ";
        cin >> pin;

        ifstream file("Accounts/"+username + ".txt");
        if (!file) {
            cout << "Account not found.\n";
            return false;
        }

        string storedPin;
        file >> storedPin >> balance;

        if (pin == storedPin) {
            cout << "Login successful.\n";
            return true;
        } else {
            cout << "Incorrect PIN.\n";
            return false;
        }
    }

    void registerAccount() {
        cout << "Choose a username: ";
        cin >> username;
        cout << "Set a 4-digit PIN: ";
        cin >> pin;
        balance = 0.0;

        ofstream file("Accounts/"+username + ".txt");
        file << pin << "\n" << balance;
        file.close();



        cout << "Account created successfully.\n";
    }

    void checkBalance() {
        cout << "Your balance is: " << balance << endl;
    }

    void deposit() {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;
        balance += amount;
        updateFile();
        cout << "Deposit successful.\n";
    }

    void withdraw() {
        double amount;
        cout << "Enter amount to withdraw: $";
        cin >> amount;
        if (amount > balance) {
            cout << "Insufficient funds.\n";
        } else {
            balance -= amount;
            updateFile();
            cout << "Withdrawal successful.\n";
        }
    }

    void updateFile() {
        ofstream file("Accounts/"+username + ".txt");
        file << pin << "\n" << balance;
    }
};

int main() {
    ATM atm;
    int choice;

    cout << "$$$$$$$$$$$$  Welcome to Money  $$$$$$$$$$$$\n";
    cout << "1. Register\n2. Login\nChoose an option: ";
    cin >> choice;

    if (choice == 1) {
        atm.registerAccount();
    }

    if (choice == 2) {
        if (atm.login()) {
            do {
                cout << "\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Exit\nChoose an option: ";
                cin >> choice;

                switch (choice) {
                    case 1: atm.checkBalance();
                     break;
                    case 2: atm.deposit();
                    break;
                    case 3: atm.withdraw();
                    break;
                    case 4: cout << "Thank you for using ATM.\n";
                    break;
                    default: cout << "Invalid option.\n";
                    break;
                }
            }
            while (choice != 4);
        }
    }

    return 0;
}
