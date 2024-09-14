#include <iostream>
#include <map>
#include <string>
using namespace std;

// Structure to represent a bank account
struct Account {
    string name;
    int accountNumber;
    double balance;
};

// Function to create a new account
void createAccount(map<int, Account>& accounts, int& nextAccountNumber, string name, double initialDeposit) {
    if (initialDeposit < 0) {
        cout << "Initial deposit cannot be negative!" << endl;
        return;
    }

    Account newAccount;
    newAccount.name = name;
    newAccount.accountNumber = nextAccountNumber;
    newAccount.balance = initialDeposit;

    accounts[nextAccountNumber] = newAccount;
    cout << "Account created successfully! Account Number: " << nextAccountNumber << endl;

    nextAccountNumber++;
}

// Function to find an account by account number
Account* findAccount(map<int, Account>& accounts, int accountNumber) {
    if (accounts.find(accountNumber) != accounts.end()) {
        return &accounts[accountNumber];
    } else {
        cout << "Account not found!" << endl;
        return nullptr;
    }
}

// Function to deposit money into an account
void deposit(Account* account, double amount) {
    if (amount > 0) {
        account->balance += amount;
        cout << "Successfully deposited: $" << amount << endl;
    } else {
        cout << "Deposit amount should be positive!" << endl;
    }
}

// Function to withdraw money from an account
void withdraw(Account* account, double amount) {
    if (amount > 0 && amount <= account->balance) {
        account->balance -= amount;
        cout << "Successfully withdrew: $" << amount << endl;
    } else {
        cout << "Insufficient funds or invalid amount!" << endl;
    }
}

// Function to transfer money between accounts
void transfer(Account* fromAccount, Account* toAccount, double amount) {
    if (amount > 0 && amount <= fromAccount->balance) {
        fromAccount->balance -= amount;
        toAccount->balance += amount;
        cout << "Successfully transferred: $" << amount << " to Account " << toAccount->accountNumber << endl;
    } else {
        cout << "Transfer failed. Insufficient funds or invalid amount!" << endl;
    }
}

// Function to display account information
void displayAccountInfo(const Account& account) {
    cout << "Account Holder: " << account.name << endl;
    cout << "Account Number: " << account.accountNumber << endl;
    cout << "Balance: $" << account.balance << endl;
}

// Main program function
int main() {
    map<int, Account> accounts;  // Map to store accounts
    int nextAccountNumber = 1001; // Starting account number
    int choice, accountNumber, toAccountNumber;
    string name;
    double amount;

    do {
        cout << "\n===== Online Banking System Menu =====" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit" << endl;
        cout << "3. Withdraw" << endl;
        cout << "4. Transfer" << endl;
        cout << "5. Display Account" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter account holder name: ";
                cin.ignore(); // Clear the buffer
                getline(cin, name);
                cout << "Enter initial deposit amount: ";
                cin >> amount;
                createAccount(accounts, nextAccountNumber, name, amount);
                break;

            case 2:
                cout << "Enter account number: ";
                cin >> accountNumber;
                {
                    Account* account = findAccount(accounts, accountNumber);
                    if (account != nullptr) {
                        cout << "Enter deposit amount: ";
                        cin >> amount;
                        deposit(account, amount);
                    }
                }
                break;

            case 3:
                cout << "Enter account number: ";
                cin >> accountNumber;
                {
                    Account* account = findAccount(accounts, accountNumber);
                    if (account != nullptr) {
                        cout << "Enter withdraw amount: ";
                        cin >> amount;
                        withdraw(account, amount);
                    }
                }
                break;

            case 4:
                cout << "Enter your account number: ";
                cin >> accountNumber;
                cout << "Enter recipient account number: ";
                cin >> toAccountNumber;
                {
                    Account* fromAccount = findAccount(accounts, accountNumber);
                    Account* toAccount = findAccount(accounts, toAccountNumber);
                    if (fromAccount != nullptr && toAccount != nullptr) {
                        cout << "Enter transfer amount: ";
                        cin >> amount;
                        transfer(fromAccount, toAccount, amount);
                    }
                }
                break;

            case 5:
                cout << "Enter account number: ";
                cin >> accountNumber;
                {
                    Account* account = findAccount(accounts, accountNumber);
                    if (account != nullptr) {
                        displayAccountInfo(*account);
                    }
                }
                break;

            case 6:
                cout << "Exiting system..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
