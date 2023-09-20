#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class BankAccount
{
private:
    int account_number;
    string name;
    string address;
    string contact_details;
    double balance;
    string currency;
    string email; 
    vector<string> transaction_history;

public:
    BankAccount(int acc_number, const string &n, const string &addr, const string &contact, const string &mail, double initial_balance, const string &curr)
        : account_number(acc_number), name(n), address(addr), contact_details(contact), balance(initial_balance), currency(curr), email(mail) {}

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            transaction_history.push_back("Deposited " + to_string(amount) + " " + currency);

            
            cout << "Deposited " << amount << " " << currency << " to account " << account_number << "." << endl;

            
            send_email("Deposit Notification", "You have made a deposit of " + to_string(amount) + " " + currency + " to your account.");
        }
        else
        {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            transaction_history.push_back("Withdrew " + to_string(amount) + " " + currency);
        }
        else
        {
            cout << "Invalid withdrawal amount or insufficient funds." << endl;
        }
    }

    void display_info()
    {
        cout << "Account Information:" << endl;
        cout << "Account Number: " << account_number << endl;
        cout << "Account Holder's Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Contact Details: " << contact_details << endl;
        cout << "Email: " << email << endl; // Display email
        cout << "Current Balance: " << balance << " " << currency << endl;
        cout << "Transaction History:" << endl;
        for (const string &transaction : transaction_history)
        {
            cout << transaction << endl;
        }
    }

    // Implement the email notification method here
    void send_email(const string &subject, const string &message)
    {
        cout << "Email sent to " << email << " with subject: " << subject << endl;
        cout << "Message: " << message << endl;
    }

    // Getter methods
    int get_account_number() const
    {
        return account_number;
    }

    double get_balance() const
    {
        return balance;
    }

    const string &get_currency() const
    {
        return currency;
    }
};

void create_account(vector<BankAccount> &accounts)
{
    int account_number = accounts.size() + 1;
    string name, address, contact_details, currency, email;
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
    cout << "Enter the initial deposit amount: ";
    cin >> initial_deposit;
    cout << "Enter the currency (e.g., USD, EUR): ";
    cin >> currency;

    if (initial_deposit >= 0)
    {
        BankAccount new_account(account_number, name, address, contact_details, email, initial_deposit, currency);
        accounts.push_back(new_account);
        cout << "Account created successfully." << endl;
    }
    else
    {
        cout << "Invalid initial deposit amount." << endl;
    }
}

void deposit_cash(BankAccount &account)
{
    double amount;
    cout << "Enter the deposit amount in " << account.get_currency() << ": ";
    cin >> amount;
    account.deposit(amount);
    cout << "Deposit completed." << endl;
}

void withdraw_cash(BankAccount &account)
{
    double amount;
    cout << "Enter the withdrawal amount in " << account.get_currency() << ": ";
    cin >> amount;
    account.withdraw(amount);
    cout << "Withdrawal completed." << endl;
}

void transfer_funds(BankAccount &sender_account, BankAccount &recipient_account)
{
    double amount;
    cout << "Enter the transfer amount in " << sender_account.get_currency() << ": ";
    cin >> amount;
    if (sender_account.get_balance() >= amount)
    {
        sender_account.withdraw(amount);
        recipient_account.deposit(amount);
        cout << "Transfer completed." << endl;
    }
    else
    {
        cout << "Insufficient funds for the transfer." << endl;
    }
}

int main()
{
    vector<BankAccount> accounts;

    while (true)
    {
        cout << "\nBanking System Menu:" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. Deposit Cash" << endl;
        cout << "3. Withdraw Cash" << endl;
        cout << "4. Transfer Between Accounts" << endl;
        cout << "5. Display Account Information" << endl;
        cout << "6. Log Out" << endl;
        string choice;
        cout << "Enter your choice (1/2/3/4/5/6): ";
        cin >> choice;

        if (choice == "1")
        {
            create_account(accounts);
        }
        else if (choice == "2")
        {
            int account_number;
            cout << "Enter your account number: ";
            cin >> account_number;
            bool found = false;
            for (BankAccount &account : accounts)
            {
                if (account.get_account_number() == account_number)
                {
                    deposit_cash(account);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Account not found." << endl;
            }
        }
        else if (choice == "3")
        {
            int account_number;
            cout << "Enter your account number: ";
            cin >> account_number;
            bool found = false;
            for (BankAccount &account : accounts)
            {
                if (account.get_account_number() == account_number)
                {
                    withdraw_cash(account);
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Account not found." << endl;
            }
        }
        else if (choice == "4")
        {
            int sender_number, recipient_number;
            cout << "Enter your account number (sender): ";
            cin >> sender_number;
            cout << "Enter recipient's account number: ";
            cin >> recipient_number;
            bool sender_found = false, recipient_found = false;
            BankAccount *sender_account = nullptr;
            BankAccount *recipient_account = nullptr;
            for (BankAccount &account : accounts)
            {
                if (account.get_account_number() == sender_number)
                {
                    sender_account = &account;
                    sender_found = true;
                }
                if (account.get_account_number() == recipient_number)
                {
                    recipient_account = &account;
                    recipient_found = true;
                }
            }
            if (sender_found && recipient_found)
            {
                transfer_funds(*sender_account, *recipient_account);
            }
            else
            {
                cout << "One or both accounts not found." << endl;
            }
        }
        else if (choice == "5")
        {
            int account_number;
            cout << "Enter your account number: ";
            cin >> account_number;
            bool found = false;
            for (BankAccount &account : accounts)
            {
                if (account.get_account_number() == account_number)
                {
                    account.display_info();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "Account not found." << endl;
            }
        }
        else if (choice == "6")
        {
            cout << "Logging out." << endl;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
