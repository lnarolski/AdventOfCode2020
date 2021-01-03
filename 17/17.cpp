#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <list>

std::vector<std::string>* LoadFile(std::string fileName)
{
    std::vector<std::string>* data = new std::vector<std::string>();

    std::fstream input;
    input.open(fileName, std::fstream::in);
    std::string fileLine;

    while (std::getline(input, fileLine))
    {
        data->push_back(fileLine);
    }
    input.close();

    return data;
}

class ThreeDimensionalArea
{
public:
    std::vector<std::string> layer;
    std::list<std::vector<std::string>>* nextLayer = NULL;
    std::list<std::vector<std::string>>* previousLayer = NULL;


};

uint64_t Star1(std::vector<std::string> area)
{
    std::list<std::vector<std::string>> threeDimensionalArea;



    return 0;
}

uint64_t Star2(std::vector<std::string> area)
{
    return 0;
}

int main()
{
    std::vector<std::string>* data = LoadFile("17.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
