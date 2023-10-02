#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

class BankAccount {
	public:
		// Constructor
		BankAccount() {
			// Prompt the user for an account number
			std::cout << "Enter an account number: ";
			std::cin >> accountNumber;

			// Prompt the user for a name for the account
			std::cout << "Enter an account holder name: ";
			std::cin >> accountName;
		
			// Prompt the user for a starting balance
			std::cout << "Enter an initial balance: ";
			std::cin >> balance;
		}
		
		// Declare a function to deposit to the balance
		void Deposit(float x) {
			balance += x;
			std::cout << std::endl;
			std::cout << "Deposited $" << std::fixed << std::setprecision(2) << x << " into account." << std::endl;
		}
		
		// Declare a function to withdraw from the balance
		void Withdraw(float x) {
			if (balance - x >= 0) {
				balance -= x;
				std::cout << std::endl;
				std::cout << "Withdrawn $" << std::fixed << std::setprecision(2) << x << " into account." << std::endl;
			} else {
				std::cout << std::endl;
				std::cout << "You cannot withdraw $" << std::fixed << std::setprecision(2) << x << " from your account. You currently have $" << balance << "." << std::endl;
			}
		}

		// Declare a function to output the account information
		void DisplayAccountInfo() {
			std::cout << std::endl;
			std::cout << "Account Number: " << accountNumber << std::endl;
			std::cout << "Account Holder: " << accountName << std::endl;
			std::cout << "Balance: $" << std::fixed << std::setprecision(2) << balance << std::endl;
		}

	private:
		// Privately declare the account variables
		std::string accountNumber;
		std::string accountName;
		float balance;
};

int main() {
    BankAccount account1;
    account1.Deposit(500);
    account1.Withdraw(200);
    account1.DisplayAccountInfo();

    return 0;
}
