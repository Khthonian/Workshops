#include <iostream>
#include <thread>

void greetings()
{
    std::cout << "Hello!";
}

void greetings2(std::string message)
{
    std::cout << "You said: " << message;
}

int main()
{
    std::thread greetMe(&greetings);
    std::thread greetMeCustom(&greetings2,
     "Good Morning!");

    greetMe.detach();
    greetMeCustom.join();

}