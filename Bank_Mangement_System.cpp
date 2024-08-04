#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

// Transaction Class
class Transaction {
private:
    int transactionID;
    int accountNumber;
    string transactionType;
    double amount;
    string dateTime;

public:
    Transaction(int id, int accNumber, const string& type, double amt)
        : transactionID(id), accountNumber(accNumber), transactionType(type), amount(amt) {
        // Get the current time and convert it to a string
        time_t now = time(NULL);
        dateTime = ctime(&now);
    }

    string getTransactionDetails() const {
        return "ID: " + to_string(transactionid) + ", Type: " + transactionType + ", Amount: " + to_string(amount) + ", DateTime: " + dateTime;
    }
};

// Account Class
class Account {
private:
    int accountNumber;
    string accountType;
    double balance;
    int customerID;
    vector<Transaction> transactions;

public:
    Account(int number, const string& type, double initialBalance, int customerId)
        : accountNumber(number), accountType(type), balance(initialBalance), customerID(customerId) {}

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back(transactions.size() + 1, accountNumber, "Deposit", amount);
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactions.emplace_back(transactions.size() + 1, accountNumber, "Withdrawal", amount);
        } else {
            cout << "Insufficient funds for withdrawal.\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    void addTransaction(const Transaction& transaction) {
        transactions.push_back(transaction);
    }

    void printAccountDetails() const {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Type: " << accountType << "\n";
        cout << "Balance: $" << balance << "\n";
        cout << "Transactions:\n";
        for (const auto& transaction : transactions) {
            cout << transaction.getTransactionDetails() << "\n";
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }
};

// Customer Class
class Customer {
private:
    int customerID;
    string name;
    string address;
    string contactInfo;

public:
    Customer(int id, const string& n, const string& addr, const string& contact)
        : customerID(id), name(n), address(addr), contactInfo(contact) {}

    int getCustomerID() const {
        return customerID;
    }

    string getName() const {
        return name;
    }

    void updateContactInfo(const string& newContact) {
        contactInfo = newContact;
    }

    void printCustomerDetails() const {
        cout << "Customer ID: " << customerID << "\n";
        cout << "Name: " << name << "\n";
        cout << "Address: " << address << "\n";
        cout << "Contact Info: " << contactInfo << "\n";
    }
};

// BankingService Class
class BankingService {
private:
    vector<Customer> customers;
    vector<Account> accounts;

public:
    void createCustomer() {
        string name, address, contactInfo;
        cout << "Enter customer name: ";
        getline(cin, name);
        cout << "Enter customer address: ";
        getline(cin, address);
        cout << "Enter customer contact info: ";
        getline(cin, contactInfo);
        
        int id = customers.size() + 1;
        customers.emplace_back(id, name, address, contactInfo);
        cout << "Customer created with ID: " << id << "\n";
    }

    void createAccount() {
        int customerID;
        string accountType;
        double initialBalance;
        
        cout << "Enter customer ID: ";
        cin >> customerID;
        cin.ignore(); // Clear newline character from buffer
        cout << "Enter account type (Checking/Savings): ";
        getline(cin, accountType);
        cout << "Enter initial balance: ";
        cin >> initialBalance;
        cin.ignore(); // Clear newline character from buffer
        
        int accNumber = accounts.size() + 1;
        accounts.emplace_back(accNumber, accountType, initialBalance, customerID);
        cout << "Account created with Account Number: " << accNumber << "\n";
    }

    void deposit() {
        int accountNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter amount to deposit: ";
        cin >> amount;

        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                account.deposit(amount);
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void withdraw() {
        int accountNumber;
        double amount;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter amount to withdraw: ";
        cin >> amount;

        for (auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                account.withdraw(amount);
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void transferFunds() {
        int fromAccountNumber, toAccountNumber;
        double amount;

        cout << "Enter from account number: ";
        cin >> fromAccountNumber;
        cout << "Enter to account number: ";
        cin >> toAccountNumber;
        cout << "Enter amount to transfer: ";
        cin >> amount;

        Account* fromAccount = nullptr;
        Account* toAccount = nullptr;

        for (auto& account : accounts) {
            if (account.getAccountNumber() == fromAccountNumber) {
                fromAccount = &account;
            }
            if (account.getAccountNumber() == toAccountNumber) {
                toAccount = &account;
            }
        }

        if (fromAccount && toAccount) {
            fromAccount->withdraw(amount);
            toAccount->deposit(amount);
        } else {
            cout << "One or both accounts not found.\n";
        }
    }

    void viewAccountInfo() {
        int accountNumber;

        cout << "Enter account number: ";
        cin >> accountNumber;

        for (const auto& account : accounts) {
            if (account.getAccountNumber() == accountNumber) {
                account.printAccountDetails();
                return;
            }
        }
        cout << "Account not found.\n";
    }
};

// Main Function
int main() {
    BankingService bank;
    int choice;

    while (true) {
        cout << "\nBanking Service Menu:\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer Funds\n";
        cout << "6. View Account Info\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                bank.createCustomer();
                break;
            case 2:
                bank.createAccount();
                break;
            case 3:
                bank.deposit();
                break;
            case 4:
                bank.withdraw();
                break;
            case 5:
                bank.transferFunds();
                break;
            case 6:
                bank.viewAccountInfo();
                break;
            case 7:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

