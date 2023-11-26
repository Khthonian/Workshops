// Copyright 2023 Stewart Charles Fisher II

// Import libraries
#include <iostream>
#include <limits>
#include <string>

class Person {
 protected:
  std::string name;
  int age;

 public:
  Person(const std::string &n, int a) : name(n), age(a) {}

  std::string getName() const { return name; }

  void setName(const std::string &n) { name = n; }

  int getAge() const { return age; }

  void setAge(int a) { age = a; }

  virtual void displayDetails() const = 0;

  virtual ~Person() = default;
};

class Student : public Person {
 private:
  // Add private attributes for Student class
  std::string _studentID_;
  double _gpa_;

 public:
  Student(const std::string &n, int a, const std::string &s, double g)
      : Person(n, a), _studentID_(s), _gpa_(g) {}

  // Getters for the attributes
  std::string getID() const { return _studentID_; }
  double getGpa() const { return _gpa_; }

  // Setters for the attributes
  void setID(const std::string &s) { _studentID_ = s; }
  void setGpa(double g) { _gpa_ = g; }

  void displayDetails() const override {
    std::cout << "Student Name: " << getName() << std::endl
              << "Age: " << getAge() << std::endl
              << "Student ID: " << getID() << std::endl
              << "GPA: " << getGpa() << std::endl
              << std::endl;
  }
};

class Faculty : public Person {
 private:
  // Add private attributes for Faculty class
  std::string _employeeID_;
  std::string _department_;

 public:
  Faculty(const std::string &n, int a, const std::string &e,
          const std::string &d)
      : Person(n, a), _employeeID_(e), _department_(d) {}

  // Getters for the attributes
  std::string getEmployeeID() const { return _employeeID_; }
  std::string getDepartment() const { return _department_; }

  // Setters for the attributes
  void setEmployeeID(const std::string &e) { _employeeID_ = e; }
  void setDepartment(const std::string &d) { _department_ = d; }

  void displayDetails() const override {
    std::cout << "Faculty Name: " << getName() << std::endl
              << "Age: " << getAge() << std::endl
              << "Faculty ID: " << getEmployeeID() << std::endl
              << "Department: " << getDepartment() << std::endl
              << std::endl;
  }
};

class Staff : public Person {
 private:
  // Add private attributes for Staff class
  std::string _staffID_;

 public:
  Staff(const std::string &n, int a, const std::string &s)
      : Person(n, a), _staffID_(s) {}

  // Getters for the attributes
  std::string getStaffID() const { return _staffID_; }

  // Setters for the attributes
  void setStaffID(const std::string &s) { _staffID_ = s; }

  void displayDetails() const override {
    std::cout << "Staff Name: " << getName() << std::endl
              << "Age: " << getAge() << std::endl
              << "Staff ID: " << getStaffID() << std::endl
              << std::endl;
  }
};

int main() {
  // Dynamically declare the array and size
  const int SIZE = 5;
  Person *people[SIZE] = {nullptr};

  // Declare variables to hold the inputs
  std::string name;
  int age;
  double gpa;
  std::string ID;
  std::string department;
  std::string personType;

  // Loop through the array and input details
  for (int i = 0; i < SIZE; ++i) {
    std::cout << "Enter the details of Person " << i + 1 << ":" << std::endl;
    std::cout << "Name: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Age: ";
    std::cin >> age;

    std::cout << "Enter the type of person (S for Student, F for Faculty, ST "
                 "for Staff): ";
    std::cin >> personType;

    if (personType == "S") {
      std::cout << "Enter the Student ID: ";
      std::cin >> ID;
      std::cout << "Enter the GPA: ";
      std::cin >> gpa;
      people[i] = new Student(name, age, ID, gpa);
    } else if (personType == "F") {
      std::cout << "Enter the Faculty ID: ";
      std::cin >> ID;
      std::cout << "Enter the Department: ";
      std::cin >> department;
      people[i] = new Faculty(name, age, ID, department);
    } else if (personType == "ST") {
      std::cout << "Enter the Staff ID: ";
      std::cin >> ID;
      people[i] = new Staff(name, age, ID);
    } else {
      std::cout << "This is not a valid person type. Skipping to next person."
                << std::endl;
    }

    std::cout << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  // Display details of each person using polymorphism
  for (int i = 0; i < SIZE; ++i) {
    if (people[i]) {
      people[i]->displayDetails();
    }
  }

  // Delete dynamically allocated objects using range-based for loop
  for (auto person : people) {
    delete person;
  }

  return 0;
}
