#define M_PI 3.14

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

void RotateWaypoint(std::pair <int64_t, int64_t>& shipPosition, std::pair <int64_t, int64_t>& waypoint, int64_t value)
{
    if (value < 0)
        value = 360 + value;

    int64_t temp;

    switch (value)
    {
    case 90:
    case 270:
        temp = std::round(((double)waypoint.first) * std::cos(M_PI / 180.0 * (double)value) + ((double)waypoint.second) * std::sin(M_PI / 180.0 * (double)value));
        waypoint.second = std::round(((double)waypoint.second) * std::cos(M_PI / 180.0 * (double)value) - ((double)waypoint.first) * std::sin(M_PI / 180.0 * (double)value));
        waypoint.first = temp;
        break;
    case 180:
        waypoint.first *= -1;
        waypoint.second *= -1;
        break;
    default:
        break;
    }
}

uint64_t Star2(std::vector<std::string> instructions)
{
    std::pair <int64_t, int64_t> shipPosition = { 0, 0 };
    std::pair <int64_t, int64_t> waypoint = { 10, 1 };

    for (std::string instruction : instructions)
    {
        int64_t value = std::stoull(instruction.substr(1));

        switch (instruction[0])
        {
        case 'N':
            waypoint.second += value;
            break;
        case 'S':
            waypoint.second -= value;
            break;
        case 'E':
            waypoint.first += value;
            break;
        case 'W':
            waypoint.first -= value;
            break;
        case 'L':
            RotateWaypoint(shipPosition, waypoint, -value);
            break;
        case 'R':
            RotateWaypoint(shipPosition, waypoint, value);
            break;
        case 'F':
            shipPosition.first += waypoint.first * value;
            shipPosition.second += waypoint.second * value;
        default:
            break;
        }
    }

    return std::abs(shipPosition.first) + std::abs(shipPosition.second);
}

int main()
{
    std::vector<std::string>* instructions = LoadFile("12.txt");

    std::cout << "Star1: " << Star1(*instructions) << std::endl;
    std::cout << "Star2: " << Star2(*instructions) << std::endl;

    delete instructions;

    return 0;
}
