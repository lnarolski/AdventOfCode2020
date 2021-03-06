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
    ThreeDimensionalArea* nextLayer = NULL;
    ThreeDimensionalArea* previousLayer = NULL;

    const size_t size = 100;

    ThreeDimensionalArea()
    {
        for (size_t i = 0; i < size; ++i)
        {
            layer.push_back(std::string(size, '.'));
        }
    }
};

void DeleteOldLayers(ThreeDimensionalArea* firstLayer)
{
    ThreeDimensionalArea* layerToDelete = firstLayer;
    do
    {
        ThreeDimensionalArea* tempLayer = layerToDelete->nextLayer;
        delete layerToDelete;

        layerToDelete = tempLayer;
    } while (layerToDelete != NULL);
}

uint64_t CountActiveStates(ThreeDimensionalArea* firstLayer)
{
    uint64_t activeStates = 0;

    do
    {
        for (size_t y = 1; y < firstLayer->layer.size() - 1; ++y)
        {
            for (size_t x = 1; x < firstLayer->layer[0].size() - 1; ++x)
            {
                if (firstLayer->layer[y][x] == '#')
                    ++activeStates;
            }
        }

        firstLayer = firstLayer->nextLayer;
    } while (firstLayer != NULL);

    return activeStates;
}

uint64_t Star1(std::vector<std::string> area)
{
    ThreeDimensionalArea* firstLayer = new ThreeDimensionalArea();

    // First layer initialisation
    size_t start = (firstLayer->size / 2) - 1 - (area[0].size() / 2);
    size_t i = 0;
    for (size_t y = start; y < start + area.size(); ++y)
    {
        size_t j = 0;
        for (size_t x = start; x < start + area[0].size(); ++x)
        {
            firstLayer->layer[y][x] = area[i][j];

            ++j;
        }

        ++i;
    }

    size_t cycle = 0;
    while (cycle < 6)
    {
        ThreeDimensionalArea* newFirstLayer;
        ThreeDimensionalArea* newTempLayer = new ThreeDimensionalArea();
        newFirstLayer = newTempLayer;

        firstLayer->previousLayer = new ThreeDimensionalArea();
        firstLayer->previousLayer->nextLayer = firstLayer;
        firstLayer = firstLayer->previousLayer;

        ThreeDimensionalArea* actualLayer = firstLayer;

        bool stop = false, stopping = false;
        do
        {
            if (!stopping && actualLayer->nextLayer == 0)
            {
                actualLayer->nextLayer = new ThreeDimensionalArea();
                actualLayer->nextLayer->previousLayer = actualLayer;

                stopping = true;
            }
            else if (stopping)
            {
                stop = true;
            }

            for (size_t y = 1; y < actualLayer->layer.size() - 1; ++y)
            {
                for (size_t x = 1; x < actualLayer->layer[0].size() - 1; ++x)
                {
                    uint64_t activeNeighborsCount = 0;

                    for (size_t i = y - 1; i <= y + 1; ++i)
                    {
                        for (size_t j = x - 1; j <= x + 1; ++j)
                        {
                            if (i == y && j == x)
                                continue;

                            if (actualLayer->layer[i][j] == '#')
                                ++activeNeighborsCount;
                        }
                    }

                    if (actualLayer->previousLayer != 0)
                    {
                        for (size_t i = y - 1; i <= y + 1; ++i)
                        {
                            for (size_t j = x - 1; j <= x + 1; ++j)
                            {
                                if (actualLayer->previousLayer->layer[i][j] == '#')
                                    ++activeNeighborsCount;
                            }
                        }
                    }
                    if (actualLayer->nextLayer != 0)
                    {
                        for (size_t i = y - 1; i <= y + 1; ++i)
                        {
                            for (size_t j = x - 1; j <= x + 1; ++j)
                            {
                                if (actualLayer->nextLayer->layer[i][j] == '#')
                                    ++activeNeighborsCount;
                            }
                        }
                    }

                    if (actualLayer->layer[y][x] == '#')
                    {
                        if (activeNeighborsCount == 2 || activeNeighborsCount == 3)
                        {
                            newTempLayer->layer[y][x] = '#';
                        }
                        else
                        {
                            newTempLayer->layer[y][x] = '.';
                        }
                    }
                    else
                    {
                        if (activeNeighborsCount == 3)
                        {
                            newTempLayer->layer[y][x] = '#';
                        }
                        else
                        {
                            newTempLayer->layer[y][x] = '.';
                        }
                    }
                }
            }

            actualLayer = actualLayer->nextLayer;
            newTempLayer->nextLayer = new ThreeDimensionalArea();
            newTempLayer->nextLayer->previousLayer = newTempLayer;
            newTempLayer = newTempLayer->nextLayer;


        } while (!stop);

        DeleteOldLayers(firstLayer);
        firstLayer = newFirstLayer;

        ++cycle;
    }

    return CountActiveStates(firstLayer);
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
