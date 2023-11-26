# University Management System
## Problem Statement
"Design a University Management System that models the hierarchy of students, faculty, and staff. Implement the system using classes and demonstrate the use of **inheritance**, **polymorphism**, and **memory management** techniques."

## Protected Access
The `Person` class contains variables that have `protected` access, `name` and `age`. The `protected` access modifier is used here to allow the child classes, `Student`, `Faculty`, and `Staff`, to access the variables upon inheritance whilst maintaining the privacy of the variables to external factors, similar to how the `private` access modifier operates.

## Virtual Functions
The `Person` class also uses `virtual` functions. Virtual functions can be overridden in derived classes, maintaining a function name while allowing differing operation; virtual functions allow an application to achieve runtime polymorphism. 

The notable usage of a virtual function in this application is the `displayDetails` function. The three derived classes have different member variables and therefore require different operations of output. Using the virtual modifier allows the function from the base class to be overridden to operate as necessary.

In order to ensure dynamic memory allocation can function correctly, a virtual destructor has to be used to ensure that upon deallocation, the destructor of the most derived class is being called so that all resources are properly released.

## Dynamic Memory Allocation
The application dynamically creates objects of classes `Student`, `Faculty`, and `Staff` using the `new` operator; the `new` operator allocates memory on the heap in runtime and returns a pointer. Any object that is declared with the `new` operator will continue to exist until the object is explicitly deallocated with the `delete` operator. The pointers that are created are stored in an array of pointers.
