#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class BankAccount {
private:
    int account_number;
    string name;
    string address;
    string contact_details;
    double balance;
    string currency;
    string email; // New member variable for email address
    vector<string> transaction_history;

public:
    BankAccount(int acc_number, const string& n, const string& addr, const string& contact, const string& mail, double initial_balance, const string& curr)
        : account_number(acc_number), name(n), address(addr), contact_details(contact), balance(initial_balance), currency(curr), email(mail) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transaction_history.push_back("Deposited " + to_string(amount) + " " + currency);

            // Print deposit statement to terminal
            cout << "Deposited " << amount << " " << currency << " to account " << account_number << "." << endl;

            // Send an email notification
            send_email("Deposit Notification", "You have made a deposit of " + to_string(amount) + " " + currency + " to your account.");
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transaction_history.push_back("Withdrew " + to_string(amount) + " " + currency);
        } else {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }

    void display_info() {
        cout << "Account Information:" << endl;
        cout << "Account Number: " << account_number << endl;
        cout << "Account Holder's Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Contact Details: " << contact_details << endl;
        cout << "Email: " << email << endl; // Display email
        cout << "Current Balance: " << balance << " " << currency << endl;
        cout << "Transaction History:" << endl;
        for (const string& transaction : transaction_history) {
            cout << transaction << endl;
        }
    }

    // Implement the email notification method here
    void send_email(const string& subject, const string& message) {
        cout << "Email sent to " << email << " with subject: " << subject << endl;
        cout << "Message: " << message << endl;
    }

    // Getter methods
    int get_account_number() const {
        return account_number;
    }

    double get_balance() const {
        return balance;
    }

    const string& get_currency() const {
        return currency;
    }
};

void create_account(vector<BankAccount>& accounts) {
    int account_number = accounts.size() + 1;
    string name, address, contact_details, currency = "INR", email;
    double initial_deposit;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your address: ";
    cin.ignore();
    getline(cin, address);
    cout << "Enter your contact details: ";
    cin.ignore();
    getline(cin, contact_details);
    cout << "Enter your email: ";
    cin >> email; // Prompt for and store the email address
    cout << "Enter the initial deposit amount in INR (minimum 1000): ";
    cin >> initial_deposit;

    if (initial_deposit >= 1000) { // Enforce minimum deposit of 1000 INR
        BankAccount new_account(account_number, name, address, contact_details, email, initial_deposit, currency);
        accounts.push_back(new_account);
        cout << "Account created successfully." << endl;
    } else {
        cout << "Invalid initial deposit amount. Minimum deposit amount is 1000 INR." << endl;
    }
}

void deposit_cash(BankAccount& account) {
    double amount;
    cout << "Enter the deposit amount in " << account.get_currency() << ": ";
    cin >> amount;
    account.deposit(amount);
    cout << "Deposit completed." << endl;
}

void withdraw_cash(BankAccount& account) {
    double amount;
    cout << "Enter the withdrawal amount in " << account.get_currency() << ": ";
    cin >> amount;
    account.withdraw(amount);
    cout << "Withdrawal completed." << endl;
}

void transfer_funds(BankAccount& sender_account, BankAccount& recipient_account) {
    double amount;
    cout << "Enter the transfer amount in " << sender_account.get_currency() << ": ";
    cin >> amount;
    if (sender_account.get_balance() >= amount) {
        sender_account.withdraw(amount);
        recipient_account.deposit(amount);
        cout << "Transfer completed." << endl;
    } else {
        cout << "Insufficient funds for the transfer." << endl;
    }
}

int login(vector<BankAccount>& accounts) {
    int account_number;
    cout << "Enter your account number: ";
    cin >> account_number;

    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].get_account_number() == account_number) {
            return i; // Return the index of the logged-in account
        }
    }

    return -1; // Account not found
}

int main() {
    vector<BankAccount> accounts;
    int active_account_index = -1; // No active account initially

    while (true) {
        if (active_account_index == -1) {
            // No active account, ask user to log in or create an account
            cout << "\nBanking System Menu:" << endl;
            cout << "1. Create New Account" << endl;
            cout << "2. Log In" << endl;
            cout << "3. Exit" << endl;
            string choice;
            cout << "Enter your choice (1/2/3): ";
            cin >> choice;

            if (choice == "1") {
                create_account(accounts);
            } else if (choice == "2") {
                active_account_index = login(accounts);
                if (active_account_index == -1) {
                    cout << "Account not found." << endl;
                } else {
                    cout << "Logged in as account " << accounts[active_account_index].get_account_number() << "." << endl;
                }
            } else if (choice == "3") {
                cout << "Exiting." << endl;
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        } else {
            // Active account is logged in
            cout << "\nBanking System Menu:" << endl;
            cout << "1. Deposit Cash" << endl;
            cout << "2. Withdraw Cash" << endl;
            cout << "3. Transfer Between Accounts" << endl;
            cout << "4. Display Account Information" << endl;
            cout << "5. Log Out" << endl;
            string choice;
            cout << "Enter your choice (1/2/3/4/5): ";
            cin >> choice;

            if (choice == "1") {
                deposit_cash(accounts[active_account_index]);
            } else if (choice == "2") {
                withdraw_cash(accounts[active_account_index]);
            } else if (choice == "3") {
                int recipient_index = login(accounts);
                if (recipient_index == -1) {
                    cout << "Recipient account not found." << endl;
                } else {
                    transfer_funds(accounts[active_account_index], accounts[recipient_index]);
                }
            } else if (choice == "4") {
                accounts[active_account_index].display_info();
            } else if (choice == "5") {
                cout << "Logging out." << endl;
                active_account_index = -1; // Log out the active account
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }

    return 0;
}
