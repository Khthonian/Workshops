#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>

class Account {
private:
  int _accountNumber_;
  double _balance_;

public:
  // Constructor
  Account(int accountNumber) : _accountNumber_(accountNumber), _balance_(0.0) {}

  // Define a getter function for account number
  int getAccountNumber() const { return _accountNumber_; }

  // Define a getter function for balance
  double getBalance() const { return _balance_; }

  // Define a function to deposit money into the account
  void deposit(double amount) { _balance_ = _balance_ + amount; }

  // Define a function to withdraw money from the account
  void withdraw(double amount) {
    if (_balance_ - amount < 0) {
      return;
    }
    _balance_ = _balance_ - amount;
  }
};

class Customer {
private:
  std::string _name_;
  Account _account_;

public:
  // Constructor
  Customer(const std::string &name, int accountNumber)
      : _name_(name), _account_(accountNumber) {}

  // Define a getter function for customer name
  std::string getName() const { return _name_; }

  // Define a getter function for customer account number
  int getAccountNumber() const { return _account_.getAccountNumber(); }

  // Define a getter function for customer account balance
  double getAccountBalance() const { return _account_.getBalance(); }

  // Define a function to deposit money into the customer's account
  void deposit(double amount) {
    _account_.deposit(amount);
    std::cout << "Depositing $" << amount << " into " << _name_ << "'s account"
              << std::endl;
  }

  // Define a function to withdraw money from the customer's account
  void withdraw(double amount) {
    _account_.withdraw(amount);
    std::cout << "Withdrawing $" << amount << " from " << _name_ << "'s account"
              << std::endl;
  }
};

class Bank {
private:
  std::string _bankName_;
  std::vector<Customer *> _customers_;

public:
  // Constructor
  Bank(const std::string &name) : _bankName_(name) {
    std::cout << "Welcome to " << _bankName_ << std::endl;
    std::cout << std::endl;
  };

  // Define a function to add a new bank customer
  void addCustomer(Customer *customer) {
    _customers_.push_back(customer);
    std::cout << "Adding Customer: " << customer->getName() << std::endl;
  }

  // Define a function to display customer information
  void displayCustomerInfo(int accountNumber) const {
    for (const auto &customer : _customers_) {
      if (customer->getAccountNumber() == accountNumber) {
        std::cout << "Name: " << customer->getName() << std::endl;
        std::cout << "Account Number: " << customer->getAccountNumber()
                  << std::endl;
        std::cout << "Account Balance: $" << customer->getAccountBalance()
                  << std::endl;
        std::cout << std::endl;
        return;
      }
    }
    std::cout << "Customer with Account Number " << accountNumber
              << " not found." << std::endl;
    std::cout << std::endl;
  }
};

int main() {
  // Create Bank object
  Bank bank("XYZ Bank");

  // Create Customer objects and add pointers to the bank
  Customer *alice = new Customer("Alice", 12345);
  Customer *bob = new Customer("Bob", 67890);
  bank.addCustomer(alice);
  bank.addCustomer(bob);
  std::cout << std::endl;

  // Perform transactions
  alice->deposit(1300);
  bob->deposit(1000);
  alice->withdraw(500);
  bob->withdraw(600);
  std::cout << std::endl;

  // Display customer information
  std::cout << "Customer Information:" << std::endl;
  bank.displayCustomerInfo(alice->getAccountNumber());
  bank.displayCustomerInfo(bob->getAccountNumber());

  return 0;
}
