#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

std::tuple<double, char, std::string, std::vector<int>> get_student(int id)
{
    std::vector<int> someVector(3);
    someVector = {1,2,3};
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson", someVector);
    throw std::invalid_argument("id");
}

int main()
{
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n'
              << "vector contents:" << std::get<3>(student0)[1];

 }
