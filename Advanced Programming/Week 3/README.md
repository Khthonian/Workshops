# Students
## Problem Statement
"You are tasked with writing a C++ program to analyse the scores of a class of students. Your program should define a `Student` class to store individual student scores and then calculate and display various statistics based on the provided scores."

## The Student Class
### Constructors
In my implementation of the requested `Student` class, I opted to use two constructors to fulfill two different tasks. The default constructor, as seen below, was made to allow for the creation of the `students` array.
```cpp
Student() {
    // Empty default constructor
}
```
Another constructor, seen below, was made so that I could initialise new `Student` objects before inputting them to the `students` array. This second constructor takes in an integer and assigns the integer value to the `score` variable of the `Student` object. In the frame of encapsulation, we could consider this a setter function.
```cpp
Student(int newScore) {
    // Assign the user input to the class variable
    score = newScore;
}
```

### The `getScore` Function
The `getScore` function is the function of the `Student` class that essentially operates as the getter function; all it does is return the value of the `score` variable, maintaining encapsulation.

### The `score` Variable
The `score` variable is private declared within the class, such that it can only be accessed by functions within the class and cannot be accessed a user from outside the class. This is important as it ensures improved data control and security.

## The `main` Function
### The `students` Array
An array of type `Student` is declared with a size of 10. Reasons to use an array as opposed to a vector include:
- Better memory efficiency
- Constant time element indexing

### Calculating the Information
#### The Input For-Loop
A for-loop is being used to loop through each `Student` object in the `students` array. For each object, the program tries to prompt the user for a score input and take in the user's input as an integer. The try statements are used to prevent cases where a user might input a string such as `hello` to the console, which cannot be used. If the input is invalid, an error message is output to the console and the program exits. Otherwise, the current value of `tempScore` is used to initialise the next `Student` object in the `students` array.

#### The Calculation
##### The Total Number of Students
The total number of students is simply an integer variable assigned with a value of 10.

##### The Average Score
The average score is calculated by summing the scores and dividing by the total number of students.

##### The Highest and Lowest Score
The highest and lowest scores are found by using an if statement to check if the new value is higher or lower respectively than the current value. If it's true, it becomes the new value.

##### The Above and Below Average
The above and below average also uses an if statement, to check whether the current score if above or below the average score respectively. If it's true, the corresponding variable is incremented by 1.
