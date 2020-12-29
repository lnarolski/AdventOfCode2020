#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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
    uint64_t departureTime = std::stoull(instructions[0]);
    std::vector<std::string> ids = split(instructions[1], ",");
    std::vector<uint64_t> idsUint;

    for (auto i : ids)
    {
        if (i != "x")
            idsUint.push_back(std::stoull(i));
    }

    std::vector<uint64_t> departureTimes;
    std::vector<uint64_t> timeToWait;
    for (auto i : idsUint)
    {
        departureTimes.push_back(((departureTime / i) + 1) * i);
        timeToWait.push_back(departureTimes.back() - departureTime);
    }

    uint64_t foundId, minimumTime = -1;
    for (size_t i = 0; i < timeToWait.size(); ++i)
    {
        if (timeToWait[i] < minimumTime)
        {
            foundId = idsUint[i];
            minimumTime = timeToWait[i];
        }
    }

    return foundId * minimumTime;
}

uint64_t Star2(std::vector<std::string> instructions)
{
    std::vector<std::string> ids = split(instructions[1], ",");
    std::vector<uint64_t> delays, idsUint;

    uint64_t delay = 0, highestId = 0;
    size_t highestI = 0;

    for (auto i : ids)
    {
        if (i == "x")
        {
            delay++;
        }
        else
        {
            delays.push_back(delay);

            idsUint.push_back(std::stoull(i));
            if (idsUint.back() > highestId)
            {
                highestId = idsUint.back();
                highestI = idsUint.size() - 1;
            }

            delay++;
        }
    }

    bool offsetFound;
    uint64_t offsetToCheck = 0, offsetToReturn = 0;
    offsetToCheck += highestId;
    do
    {
        offsetFound = true;

        uint64_t tempOffset = offsetToCheck - delays[highestI];

        for (size_t i = 0; i < idsUint.size(); ++i)
        {
            if ((((tempOffset + delays[i]) % idsUint[i])) != 0)
            {
                offsetFound = false;
                break;
            }
        }

        if (!offsetFound)
            offsetToCheck += highestId;
        else
            offsetToReturn = tempOffset;
    } while (!offsetFound);

    return offsetToReturn;
}

int main()
{
    std::vector<std::string>* data = LoadFile("13.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
