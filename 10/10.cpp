#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

uint64_t Star1(std::vector<uint64_t>& outputJoltage)
{
    uint64_t differencesOf1Jolt = 0, differencesOf3Jolt = 0;
    uint64_t tempJoltage = 0;

    for (size_t i = 0; i < outputJoltage.size(); i++)
    {
        if (outputJoltage[i] - tempJoltage == 1)
        {
            differencesOf1Jolt++;
        }
        else if (outputJoltage[i] - tempJoltage == 3)
        {
            differencesOf3Jolt++;
        }

        tempJoltage = outputJoltage[i];
    }

    ++differencesOf3Jolt;

    return differencesOf1Jolt * differencesOf3Jolt;
}

// Source: http://www.algorytm.org/algorytmy-arytmetyczne/symbol-newtona/newton-symbol-2-c.html
unsigned long long Newton(unsigned int n, unsigned int k)      // Funkcja obliczaj¹ca symbol newtona
{
    double Wynik = 1;       // Deklaracja zmiennej ( u¿ywamy double dla dok³adnoœci obliczeñ )

    for (unsigned int i = 1; i <= k; i++)   // Od 1 do k wykonujemy :
    {
        Wynik = Wynik * (n - i + 1) / i;      // Obliczanie ze wzoru iteracyjnego
    }

    return (unsigned long long) Wynik;      // Zwróæ Wynik
}

void PrintCombination(std::vector<uint64_t>& outputJoltage)
{
    for (size_t i = 0; i < outputJoltage.size(); i++)
    {
        std::cout << outputJoltage[i] << " ";
    }

    std::cout << std::endl;
}

void CalculateCombinations(uint64_t& combinations, std::vector<uint64_t>& outputJoltage)
{
    bool deleted = false;
    for (size_t i = 1; i < outputJoltage.size() - 1; i++)
    {
        if ((outputJoltage[i] - outputJoltage[i - 1] == 1 && outputJoltage[i + 1] - outputJoltage[i] == 1) || (outputJoltage[i] - outputJoltage[i - 1] == 1 && outputJoltage[i + 1] - outputJoltage[i] == 2) || (outputJoltage[i] - outputJoltage[i - 1] == 2 && outputJoltage[i + 1] - outputJoltage[i] == 1))
        {
            std::vector<uint64_t> tempOutputJoltage = outputJoltage;
            tempOutputJoltage.erase(tempOutputJoltage.begin() + i);
            combinations++;
            deleted = true;

            //PrintCombination(tempOutputJoltage);

            CalculateCombinations(combinations, tempOutputJoltage);
        }
    }

    if (!deleted)
    {
        combinations--;
        //std::cout << "KONIEC" << std::endl;
    }
    
}

uint64_t Star2(std::vector<uint64_t>& outputJoltage)
{
    uint64_t combinations = 0;

    outputJoltage.insert(outputJoltage.begin(), 0);

    CalculateCombinations(combinations, outputJoltage);

    return combinations - 1;
}

int main()
{
    std::vector<uint64_t>* outputJoltage = LoadFile("10.txt");
    std::sort(outputJoltage->begin(), outputJoltage->end());

    std::cout << "Star1: " << Star1(*outputJoltage) << std::endl;
    //std::cout << "Star2: " << Star2(*outputJoltage) << std::endl;

    delete outputJoltage;

    return 0;
}
