#include <iostream>
#include <stdexcept>
#include <iomanip> 

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:

    BankAccount(int accNumber, double initialBalance, double intRate) {
        this->accountNumber = accNumber;
        this->balance = initialBalance;
        this->interestRate = intRate;
    }

    void deposit(double amount) {
        if (amount < 0) {
            throw invalid_argument("Amount cannot be negative");
        }
        this->balance += amount;
    }

    void withdraw(double amount) {
        if (amount < 0) {
            throw invalid_argument("Amount cannot be negative");
        }
        if (amount > this->balance) {
            throw invalid_argument("Insufficient funds");
        }
        this->balance -= amount;
    }

    double getBalance() const {
        return this->balance;
    }

    double getInterest() const {
        return (this->balance * this->interestRate * (1.0 / 12.0));
    }

    void setInterestRate(double rate) {
        this->interestRate = rate;
    }

    int getAccountNumber() const {
        return this->accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount < 0) {
        throw invalid_argument("Transfer amount cannot be negative");
    }
    if (amount > from.balance) {
        cout << "Transfer failed: Insufficient funds in source account" << endl;
        return false;
    }
    from.balance -= amount;
    to.balance += amount;
    cout << "Transfer successful" << endl;
    return true;
}
int main() {
    BankAccount account1(123456, 1000.0, 0.05); 
    BankAccount account2(654321, 500.0, 0.03); 

    cout << fixed << setprecision(2); 

    int choice;
    double amount;

    do {
        cout << "\nChoose an operation:\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Transfer\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            try {
                account1.deposit(amount);
                cout << "Deposit successful. Current balance: " << account1.getBalance() << endl;
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            try {
                account1.withdraw(amount);
                cout << "Withdrawal successful. Current balance: " << account1.getBalance() << endl;
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 3:
            cout << "Enter amount to transfer from account 1 to account 2: ";
            cin >> amount;
            try {
                if (transfer(account1, account2, amount)) {
                    cout << "Transfer successful.\n";
                }
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
