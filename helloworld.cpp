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
}
*#include <iostream>
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
/*
*/
#include <iostream>
using namespace std;
#define SIZE 4
class Queue{
    private:
    int start;
    int end;
    int currentsize;
    int arr[SIZE]
    public:
    Queue(){
        int start = -1
        int end = -1
        int currentsize=0;
        
    
    }
    public:
    void enque(int val);
    int dequeue();
    int getSize();
    bool isFull();

    int peek();

};
void Queue::enque(int val){
    if (currentSize>=SIZE){
        cout<<"the queue is full"<<end;
    }
    if(start==-1 && end==-1){
        start=0;
        rear=0;
    }
    else{
        end=(end+1)%SIZE;

    }
    arr[end]=val;
    currentSize++;
    
}
