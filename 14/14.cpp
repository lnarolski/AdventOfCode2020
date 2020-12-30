#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <bitset>

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

void GenerateAddress(std::string& addressString, std::vector<uint64_t>& addresses, size_t& index, std::string mask)
{
    size_t i = index - 1;
    for (; i != (size_t)-1; --i)
    {
        if (mask[i] == 'X')
        {
            std::string tempAddress[2] = { addressString , addressString };
            tempAddress[0][i] = '0';
            tempAddress[1][i] = '1';

            GenerateAddress(tempAddress[0], addresses, i, mask);
            GenerateAddress(tempAddress[1], addresses, i, mask);

            break;
        }
        else if (mask[i] == '1')
        {
            addressString[i] = '1';
        }
    }

    if (i == -1)
    {
        addresses.push_back(std::stoull(addressString, nullptr, 2));
    }
}

void GenerateAddresses(uint64_t address, std::vector<uint64_t>& addresses, std::string mask)
{
    std::vector<uint64_t> masks;
    std::string addressString = std::bitset<36>(address).to_string();

    size_t i = mask.size() - 1;
    for (; i != (size_t) -1; --i)
    {
        if (mask[i] == 'X')
        {
            std::string tempAddress[2] = { addressString , addressString };
            tempAddress[0][i] = '0';
            tempAddress[1][i] = '1';

            GenerateAddress(tempAddress[0], addresses, i, mask);
            GenerateAddress(tempAddress[1], addresses, i, mask);

            break;
        }
        else if (mask[i] == '1')
        {
            addressString[i] = '1';
        }
    }

    if (i == -1)
    {
        addresses.push_back(std::stoull(addressString, nullptr, 2));
    }
}

uint64_t Star2(std::vector<std::string> instructions)
{
    std::map <uint64_t, uint64_t> memory;
    std::string mask;

    for (std::string i : instructions)
    {
        if (i.find("mask") != std::string::npos) //mask
        {
            mask = i.substr(i.find("= ") + 2);
        }
        else //mem
        {
            uint64_t address = std::stoull(i.substr(4, i.find(']', 4) - 4));
            uint64_t value = std::stoull(i.substr(i.find("= ") + 2));

            std::vector<uint64_t> addresses;
            GenerateAddresses(address, addresses, mask);
            
            for (auto i : addresses)
            {
                if (memory.find(i) == memory.end())
                {
                    memory.insert({ i, 0 });
                }

                memory[i] = value;
            }
        }
    }

    uint64_t sum = 0;
    for (auto i : memory)
    {
        sum += i.second;
    }

    return sum;
}

int main()
{
    std::vector<std::string>* data = LoadFile("14.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
