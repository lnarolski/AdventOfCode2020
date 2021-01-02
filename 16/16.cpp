#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>

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

struct Rule
{
    std::string name;
    std::vector<uint64_t> ruleMin;
    std::vector<uint64_t> ruleMax;
};

uint64_t Star1(std::vector<std::string> instructions)
{
    bool rulesLoading = true, yourTicket = false, nearbyTickets = false;
    std::vector<Rule> rules;
    std::vector<uint64_t> invalidValues;

    for (std::string line : instructions)
    {
        if (line == "")
        {
            rulesLoading = false;
            yourTicket = false;
            nearbyTickets = false;
        }
        else if (rulesLoading)
        {
            Rule tempRule;
            std::vector<std::string> tempSplit = split(line, ": ");

            tempRule.name = tempSplit[0];

            tempSplit = split(tempSplit[1], " or ");
            for (auto i : tempSplit)
            {
                std::vector<std::string> tempRange = split(i, "-");
                tempRule.ruleMin.push_back(stoull(tempRange[0]));
                tempRule.ruleMax.push_back(stoull(tempRange[1]));
            }

            rules.push_back(tempRule);
        }
        else if (!rulesLoading && !yourTicket && !nearbyTickets && line == "your ticket:")
        {
            yourTicket = true;
        }
        else if (yourTicket)
        {

        }
        else if (line == "nearby tickets:")
        {
            nearbyTickets = true;
        }
        else if (nearbyTickets)
        {
            std::vector<std::string> valuesToCheck = split(line, ",");

            for (auto i : valuesToCheck)
            {
                uint64_t valueToCheck = stoull(i);
                bool valid = false;

                for (Rule rule : rules)
                {
                    for (size_t ii = 0; ii < rule.ruleMin.size(); ++ii)
                    {
                        if (valueToCheck >= rule.ruleMin[ii] && valueToCheck <= rule.ruleMax[ii])
                        {
                            valid = true;
                            break;
                        }
                    }

                    if (valid)
                        break;
                }

                if (!valid)
                {
                    invalidValues.push_back(valueToCheck);
                }
            }
        }
    }

    return std::accumulate(invalidValues.begin(), invalidValues.end(), 0);
}

uint64_t Star2(std::vector<std::string> instructions)
{
    return 0;
}

int main()
{
    std::vector<std::string>* data = LoadFile("16.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
