#include <iostream>
#include <iterator>
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
  std::string studentID;
  double gpa;

public:
  Student(const std::string &n, int a, const std::string &s, double g)
      : Person(n, a), studentID(s), gpa(g) {}

  // Getters for the attributes
  std::string getID() const { return studentID; }
  double getGpa() const { return gpa; }

  // Setters for the attributes
  void setID(const std::string &s) { studentID = s; }
  void setGpa(double g) { gpa = g; }

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
  std::string employeeID;
  std::string department;

public:
  Faculty(const std::string &n, int a, const std::string &e,
          const std::string &d)
      : Person(n, a), employeeID(e), department(d) {}

  // Getters for the attributes
  std::string getEmployeeID() const { return employeeID; }
  std::string getDepartment() const { return department; }

  // Setters for the attributes
  void setEmployeeID(const std::string &e) { employeeID = e; }
  void setDepartment(const std::string &d) { department = d; }

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
  std::string staffID;

public:
  Staff(const std::string &n, int a, const std::string &s)
      : Person(n, a), staffID(s) {}

  // Getters for the attributes
  std::string getStaffID() const { return staffID; }

  // Setters for the attributes
  void setStaffID(const std::string &s) { staffID = s; }

  void displayDetails() const override {
    std::cout << "Staff Name: " << getName() << std::endl
              << "Age: " << getAge() << std::endl
              << "Staff ID: " << getStaffID() << std::endl
              << std::endl;
  }
};

int main() {
  const int SIZE = 5;
  Person *people[SIZE] = {nullptr};

  // Create objects of different classes dynamically
  people[0] = new Student("John Doe", 20, "S12345", 3.8);
  people[1] = new Faculty("Dr. Smith", 40, "F98765", "Computer Science");
  people[2] = new Staff("Jane Johnson", 30, "E54321");

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
