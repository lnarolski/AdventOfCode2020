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

void PrintGrid(std::vector<std::string>& grid)
{
    for (size_t i = 0; i < grid.size(); i++)
    {
        for (size_t j = 0; j < grid[i].size(); j++)
        {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

uint64_t Star1(std::vector<std::string> grid)
{
    int64_t state = -1, prevState = 0;
    uint64_t occupiedSeats;

    while (state != prevState)
    {
        if (state != -1)
            prevState = state;

        //PrintGrid(grid);
        std::vector<std::string> tempGrid = grid;

        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == '.')
                    continue;

                // Checking adjascent area of the seat ///////////////
                uint64_t emptySeats = 0, occupiedSeats = 0;
                for (int k = ((int) i - 1 < 0 ? 0 : -1); k < (i + 1 >= grid.size() ? 1 : 2); k++)
                {
                    for (int l = ((int) j - 1 < 0 ? 0 : -1); l < (j + 1 >= grid[i].size() ? 1 : 2); l++)
                    {
                        if (k == 0 && l == 0)
                            continue;

                        if (tempGrid[i + k][j + l] == 'L')
                        {
                            ++emptySeats;
                        }
                        else if (tempGrid[i + k][j + l] == '#')
                        {
                            ++occupiedSeats;
                        }
                    }
                }
                //////////////////////////////////////////////////

                if (tempGrid[i][j] == 'L' && occupiedSeats == 0)
                    grid[i][j] = '#';
                else if (tempGrid[i][j] == '#' && occupiedSeats >= 4)
                    grid[i][j] = 'L';
            }
        }

        // Calculating occupied seats
        occupiedSeats = 0;
        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == '#')
                {
                    ++occupiedSeats;
                }
            }
        }

        state = occupiedSeats;
    }

    //PrintGrid(grid);

    return occupiedSeats;
}

uint64_t Star2(std::vector<std::string> grid)
{
    int64_t state = -1, prevState = 0;
    uint64_t occupiedSeats;

    while (state != prevState)
    {
        if (state != -1)
            prevState = state;

        //PrintGrid(grid);
        std::vector<std::string> tempGrid = grid;

        for (int64_t i = 0; i < grid.size(); i++)
        {
            for (int64_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == '.')
                    continue;

                // Checking area of the seat ///////////////
                std::vector<std::string> tempArea = { "000", "000", "000" };
                uint64_t chairsFound = 0;
                int64_t k = 1;
                while (chairsFound != 8)
                {
                    if (tempArea[0][0] == '0') // UP-LEFT
                    {
                        if (i - k < 0 || j - k < 0)
                        {
                            tempArea[0][0] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i - k][j - k] != '.')
                        {
                            tempArea[0][0] = tempGrid[i - k][j - k];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[0][1] == '0') // UP
                    {
                        if (i - k < 0)
                        {
                            tempArea[0][1] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i - k][j] != '.')
                        {
                            tempArea[0][1] = tempGrid[i - k][j];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[0][2] == '0') // UP-RIGHT
                    {
                        if (i - k < 0 || j + k >= tempGrid[i].size())
                        {
                            tempArea[0][2] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i - k][j + k] != '.')
                        {
                            tempArea[0][2] = tempGrid[i - k][j + k];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[1][0] == '0') // LEFT
                    {
                        if (j - k < 0)
                        {
                            tempArea[1][0] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i][j - k] != '.')
                        {
                            tempArea[1][0] = tempGrid[i][j - k];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[1][2] == '0') // RIGHT
                    {
                        if (j + k >= tempGrid[i].size())
                        {
                            tempArea[1][2] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i][j + k] != '.')
                        {
                            tempArea[1][2] = tempGrid[i][j + k];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[2][0] == '0') // DOWN-LEFT
                    {
                        if (j - k < 0 || i + k >= tempGrid.size())
                        {
                            tempArea[2][0] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i + k][j - k] != '.')
                        {
                            tempArea[2][0] = tempGrid[i + k][j - k];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[2][1] == '0') // DOWN
                    {
                        if (i + k >= tempGrid.size())
                        {
                            tempArea[2][1] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i + k][j] != '.')
                        {
                            tempArea[2][1] = tempGrid[i + k][j];
                            ++chairsFound;
                        }
                    }
                    if (tempArea[2][2] == '0') // DOWN-RIGHT
                    {
                        if (i + k >= tempGrid.size() || j + k >= tempGrid[i].size())
                        {
                            tempArea[2][2] = '.';
                            ++chairsFound;
                        }
                        else if (tempGrid[i + k][j + k] != '.')
                        {
                            tempArea[2][2] = tempGrid[i + k][j + k];
                            ++chairsFound;
                        }
                    }

                    ++k;
                }

                // Checking tempArea///////////////
                uint64_t emptySeats = 0, occupiedSeats = 0;
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        if (k == 1 && l == 1)
                            continue;

                        if (tempArea[k][l] == 'L')
                        {
                            ++emptySeats;
                        }
                        else if (tempArea[k][l] == '#')
                        {
                            ++occupiedSeats;
                        }
                    }
                }
                //////////////////////////////////////////////////

                if (tempGrid[i][j] == 'L' && occupiedSeats == 0)
                    grid[i][j] = '#';
                else if (tempGrid[i][j] == '#' && occupiedSeats >= 5)
                    grid[i][j] = 'L';
            }
        }

        // Calculating occupied seats
        occupiedSeats = 0;
        for (size_t i = 0; i < grid.size(); i++)
        {
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == '#')
                {
                    ++occupiedSeats;
                }
            }
        }

        state = occupiedSeats;
    }

    //PrintGrid(grid);

    return occupiedSeats;
}

int main()
{
    std::vector<std::string>* grid = LoadFile("11.txt");

    std::cout << "Star1: " << Star1(*grid) << std::endl;
    std::cout << "Star2: " << Star2(*grid) << std::endl;

    delete grid;

    return 0;
}
