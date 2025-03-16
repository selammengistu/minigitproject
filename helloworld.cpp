/*#include <iostream>

/*int main(){
    std::cout << "I like burger" << std::endl;
    std::cout << "I like noodels";
#include <iostream>

namespace first{
    int x = 1;
}
namespace second{
    int x = 2;
}
int main() {
    using namespace second; 
    std::cout << x;
}*/
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
