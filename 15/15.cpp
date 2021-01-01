#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

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

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        tokens.push_back(token);

        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

struct Number
{
    uint64_t lastSeen;
    uint64_t recentlySeen;
};

uint64_t Star1(std::vector<std::string> instructions)
{
    std::vector<std::string> temp = split(instructions[0], ",");
    uint64_t turn = 1;
    uint64_t lastNumber;

    std::map<uint64_t, Number> numbers;
    bool zeroAdded = false;

    for (size_t i = 0; i < temp.size() - 1; ++i)
    {
        numbers.insert({stoull(temp[i]) , {turn, turn} });
        ++turn;

        if (stoull(temp[i]) == 0)
            zeroAdded = true;
    }

    lastNumber = stoull(temp[temp.size() - 1]);

    while (turn != 2020)
    {
        if (numbers.find(lastNumber) != numbers.end())
        {
            if (numbers[lastNumber].recentlySeen != numbers[lastNumber].lastSeen)
            {
                numbers[lastNumber].recentlySeen = numbers[lastNumber].lastSeen;
            }
            numbers[lastNumber].lastSeen = turn;

            lastNumber = numbers[lastNumber].lastSeen - numbers[lastNumber].recentlySeen;
        }
        else
        {
            numbers.insert({ lastNumber , {turn, turn} });
            lastNumber = 0;
        }

        ++turn;
    }

    return lastNumber;
}

uint64_t Star2(std::vector<std::string> instructions)
{
    std::vector<std::string> temp = split(instructions[0], ",");
    uint64_t turn = 1;
    uint64_t lastNumber;

    std::map<uint64_t, Number> numbers;
    bool zeroAdded = false;

    for (size_t i = 0; i < temp.size() - 1; ++i)
    {
        numbers.insert({ stoull(temp[i]) , {turn, turn} });
        ++turn;

        if (stoull(temp[i]) == 0)
            zeroAdded = true;
    }

    lastNumber = stoull(temp[temp.size() - 1]);

    while (turn != 2020)
    {
        if (numbers.find(lastNumber) != numbers.end())
        {
            if (numbers[lastNumber].recentlySeen != numbers[lastNumber].lastSeen)
            {
                numbers[lastNumber].recentlySeen = numbers[lastNumber].lastSeen;
            }
            numbers[lastNumber].lastSeen = turn;

            lastNumber = numbers[lastNumber].lastSeen - numbers[lastNumber].recentlySeen;
        }
        else
        {
            numbers.insert({ lastNumber , {turn, turn} });
            lastNumber = 0;
        }

        ++turn;
    }

    return lastNumber;
}

int main()
{
    std::vector<std::string>* data = LoadFile("15.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
