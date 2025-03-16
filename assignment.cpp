#include <iostream>
int main(){
    std::string name;
    int age;

    std::cout << "what is your name?  ";
    std::cin >> name;
    std::cout << "How old are you?  ";
    std::cin >> age;

    std::cout<< "Hello " << name << '\n';
    std::cout<< "You are " << age <<"yearssss old. ";
    return 0;
}
