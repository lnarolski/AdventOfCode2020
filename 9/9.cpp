#define UINT64_MAX = 0xFFFFFFFFFFFFFFFFULL

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

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

long long Star1(std::vector<uint64_t>& data)
{
    uint64_t wrongNumber = 0;

    for (size_t i = 25; i < data.size(); ++i)
    {
        bool correctNumber = false;
        bool stop = false;

        for (size_t j = i - 25; !stop && j < i - 1; ++j)
        {
            for (size_t k = j + 1; !stop && k < i; ++k)
            {
                if (data[j] + data[k] == data[i])
                {
                    correctNumber = true;
                    stop = true;
                }
            }
        }

        if (!correctNumber)
            return data[i];
    }

    return wrongNumber;
}

uint64_t Star2(std::vector<uint64_t> data, uint64_t wrongNumber)
{
    size_t startIndex, endIndex;
    bool found = false;

    for (size_t i = 0; !found && i < data.size(); ++i)
    {
        uint64_t sum = 0;
        startIndex = i;

        size_t j = i;
        while (sum < wrongNumber && j < data.size())
        {
            sum += data[j];
            endIndex = j;
            ++j;
        }

        if (sum == wrongNumber)
            found = true;
    }

    found = false;
    uint64_t maxValue = 0, minValue = UINT64_MAX;
    for (size_t i = startIndex; i <= endIndex; ++i)
    {
        if (data[i] < minValue)
            minValue = data[i];
        if (data[i] > maxValue)
            maxValue = data[i];
    }

    return minValue + maxValue;
}

int main()
{
    std::vector<uint64_t>* data = LoadFile("9.txt");

    uint64_t wrongNumber = Star1(*data);
    std::cout << "Star1: " << wrongNumber << std::endl;
    std::cout << "Star2: " << Star2(*data, wrongNumber) << std::endl;

    delete data;

    return 0;
}
