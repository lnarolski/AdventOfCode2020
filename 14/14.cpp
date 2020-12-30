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

uint64_t Star1(std::vector<std::string> instructions)
{
    std::map <uint64_t, uint64_t> memory;
    uint64_t mask[2] = {0};

    for (std::string i : instructions)
    {
        if (i.find("mask") != std::string::npos) //mask
        {
            std::string maskString[2] = { i.substr(i.find("= ") + 2), i.substr(i.find("= ") + 2) };
            std::replace(maskString[0].begin(), maskString[0].end(), 'X', '1');
            std::replace(maskString[1].begin(), maskString[1].end(), 'X', '0');

            mask[0] = stoull(maskString[0], nullptr, 2);
            mask[1] = stoull(maskString[1], nullptr, 2);
        }
        else //mem
        {
            uint64_t address = std::stoull(i.substr(4, i.find(']', 4) - 4));
            uint64_t value = std::stoull(i.substr(i.find("= ") + 2));

            if (memory.find(address) == memory.end())
            {
                memory.insert({ address, 0 });
            }
            
            memory[address] = (value | mask[1]) & mask[0];
        }
    }

    uint64_t sum = 0;
    for (auto i : memory)
    {
        sum += i.second;
    }

    return sum;
}

uint64_t Star2(std::vector<std::string> instructions)
{
    return 0;
}

int main()
{
    std::vector<std::string>* data = LoadFile("14.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
