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

enum Direction
{
    north = 0,
    east = 90,
    south = 180,
    west = 270
};

void ChangeDirection(Direction& shipDirection, int64_t value)
{
    if (value < 0)
        value = 360 + value;

    int64_t tempValue = shipDirection + value;
    if (tempValue >= 360)
        tempValue -= 360;

    shipDirection = (Direction) tempValue;
}

uint64_t Star1(std::vector<std::string> instructions)
{
    Direction shipDirection = east;
    std::pair <int64_t, int64_t> shipPosition = { 0, 0 };

    for (std::string instruction : instructions)
    {
        int64_t value = std::stoull(instruction.substr(1));

        switch (instruction[0])
        {
        case 'N':
            shipPosition.first += value;
            break;
        case 'S':
            shipPosition.first -= value;
            break;
        case 'E':
            shipPosition.second += value;
            break;
        case 'W':
            shipPosition.second -= value;
            break;
        case 'L':
            ChangeDirection(shipDirection, -value);
            break;
        case 'R':
            ChangeDirection(shipDirection, value);
            break;
        case 'F':
            switch (shipDirection)
            {
            case north:
                shipPosition.first += value;
                break;
            case east:
                shipPosition.second += value;
                break;
            case south:
                shipPosition.first -= value;
                break;
            case west:
                shipPosition.second -= value;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    return std::abs(shipPosition.first) + std::abs(shipPosition.second);
}

uint64_t Star2(std::vector<std::string>& instructions)
{
    return 0;
}

int main()
{
    std::vector<std::string>* instructions = LoadFile("12.txt");

    std::cout << "Star1: " << Star1(*instructions) << std::endl;
    //std::cout << "Star2: " << Star2(*instructions) << std::endl;

    delete instructions;

    return 0;
}
