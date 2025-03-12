#include <iostream>

class Rectangle {
    public:
        int Length;
        int Breadth;

    Rectangle()
    {
        Length = 5;
        Breadth = 5;
    }

    void Display()
    {
        std::cout<<"Length: "<<Length<<std::endl;
        std::cout<<"Breadth: "<<Breadth<<std::endl;
    }
};

int main()
{
    Rectangle r;
    r.Display();
    return 0;
}