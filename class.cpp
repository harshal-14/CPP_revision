#include <iostream>
#include <string>

class Human {
    public:
        // properties
        int age;
        int weight;

        // beghaviour
        void sleep(){
            std::cout << "He is sleeping" << std::endl;
        }

        void eat(){
            std::cout << "He is eating" << std::endl;
        }
}

int main(){
    Human chitti;
    citti.age = 20;
    chitti.weight = 50;

    chitti.sleep();
    chitti.eat();
}