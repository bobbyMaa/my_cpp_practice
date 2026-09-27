#include <iostream>
#include "include/dynamic_array.h"

class Person {
    private:
        std::string name;
        int age;
    public:
        Person(std::string name, int age)
            : name(std::move(name)), age(age)
        {}
};

int main()
{
    MY_DA::dynamic_array<std::string> A(10);
    A.push_back("aaaa");
    A.push_back(std::string("bbbb"));
    std::cout << A[0] << '\n';
    std::cout << A[1] << '\n';
    MY_DA::dynamic_array<std::string> b = A;
    std::cout << A[0] << '\n';
    std::cout << A[1] << '\n';
    std::cout << b[0] << '\n';
    std::cout << b[1] << '\n';
    MY_DA::dynamic_array<std::string> temp;
    temp.push_back("xyz");
    temp.push_back("uvw");
    b = std::move(temp);
    std::cout << b[0] << '\n';
    std::cout << b[1] << '\n';
    MY_DA::dynamic_array<Person> person_List;
    person_List.emplace_back("Peter",25);
    return 0;
}