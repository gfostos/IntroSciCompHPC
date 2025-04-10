#include <iostream> 
#include <string> 

int main(void) 
{
    std::string name;
    std::cout << "Please write your name:" << std::endl;
    //std::cin >> name;
    std::getline(std::cin, name);
    std::cout << "Hola " + name + "\n";
    return 0;
}