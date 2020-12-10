#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<uint64_t>* LoadFile(std::string fileName)
{
    std::vector<uint64_t>* data = new std::vector<uint64_t>();

    std::fstream input;
    input.open(fileName, std::fstream::in);
    std::string fileLine;

    while (std::getline(input, fileLine))
    {
        data->push_back(strtoull(fileLine.c_str(), NULL, 10));
    }
    input.close();

    return data;
}

uint64_t Star1(std::vector<uint64_t>& outputJoltage)
{
    uint64_t differencesOf1Jolt = 0, differencesOf3Jolt = 0;
    uint64_t tempJoltage = 0;

    for (size_t i = 0; i < outputJoltage.size(); i++)
    {
        if (outputJoltage[i] - tempJoltage == 1)
        {
            differencesOf1Jolt++;
        }
        else if (outputJoltage[i] - tempJoltage == 3)
        {
            differencesOf3Jolt++;
        }

        tempJoltage = outputJoltage[i];
    }

    ++differencesOf3Jolt;

    return differencesOf1Jolt * differencesOf3Jolt;
}

uint64_t Star2(std::vector<uint64_t> outputJoltage)
{
    return 0;
}

int main()
{
    std::vector<uint64_t>* outputJoltage = LoadFile("10.txt");
    std::sort(outputJoltage->begin(), outputJoltage->end());

    std::cout << "Star1: " << Star1(*outputJoltage) << std::endl;
    std::cout << "Star2: " << Star2(*outputJoltage) << std::endl;

    delete outputJoltage;

    return 0;
}
