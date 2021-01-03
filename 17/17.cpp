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
            layer.push_back(std::string(100, '.'));
        }
    }
};

uint64_t Star1(std::vector<std::string> area)
{
    ThreeDimensionalArea* zeroLayer = new ThreeDimensionalArea();
    ThreeDimensionalArea* firstLayer = zeroLayer;
    ThreeDimensionalArea* lastLayer = zeroLayer;

    // First layer initialisation
    size_t start = (zeroLayer->size / 2) - 1 - (area[0].size() / 2);
    size_t i = 0;
    for (size_t y = start; y < start + 3; ++y)
    {
        size_t j = 0;
        for (size_t x = start; x < start + 3; ++x)
        {
            zeroLayer->layer[y][x] = area[i][j];

            ++j;
        }

        ++i;
    }

    size_t cycle = 0;
    ThreeDimensionalArea* actualLayer = zeroLayer;
    std::vector<ThreeDimensionalArea*> layersToDelete;
    while (cycle < 6)
    {
        // Creating copy
        ThreeDimensionalArea* tempLayer = firstLayer;
        do
        {

        } while (tempLayer != lastLayer);

        for (size_t y = 1; y < actualLayer->layer.size() - 1; ++y)
        {
            for (size_t x = 1; x < actualLayer->layer[0].size() - 1; ++x)
            {
                actualLayer->layer[y][x];
            }
        }

        ++cycle;
    }

    return 0;
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
