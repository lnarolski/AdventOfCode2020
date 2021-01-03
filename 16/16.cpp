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

bool CheckRule(uint64_t& value, Rule& rule)
{
    bool valid = false;

    for (size_t ii = 0; ii < rule.ruleMin.size(); ++ii)
    {
        if (value >= rule.ruleMin[ii] && value <= rule.ruleMax[ii])
        {
            valid = true;
            break;
        }
    }

    if (valid)
        return true;

    return false;
}

uint64_t Star2(std::vector<std::string> instructions)
{
    bool rulesLoading = true, yourTicket = false, nearbyTickets = false;
    std::vector<Rule> rules;
    
    std::vector<std::vector <uint64_t>> nearbyTicketsVector;
    std::vector<uint64_t> yourTicketVector;

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
            std::vector<std::string> ticketValues = split(line, ",");

            for (auto i : ticketValues)
            {
                yourTicketVector.push_back(stoull(i));
            }
        }
        else if (line == "nearby tickets:")
        {
            nearbyTickets = true;
        }
        else if (nearbyTickets)
        {
            // Loading nearby tickets
            std::vector<std::string> ticketValues = split(line, ",");

            std::vector<uint64_t> tempTicketVaules;
            for (auto i : ticketValues)
            {
                tempTicketVaules.push_back(stoull(i));
            }
            nearbyTicketsVector.push_back(tempTicketVaules);
        }
    }

    //Checking tickets
    for (auto i = nearbyTicketsVector.end() - 1; i != nearbyTicketsVector.begin();)
    {
        bool valid = false;

        for (auto valueToCheck : *i)
        {
            valid = false;

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
                break;
        }

        if (!valid)
        {
            i = nearbyTicketsVector.erase(i) - 1;
        }
        else
        {
            --i;
        }
    }

    // Finding column names
    std::vector<std::string> columnNames(rules.size(), "");
    std::vector<bool> usedRules(rules.size(), false);

    size_t foundNames = 0;
    while (foundNames != rules.size())
    {
        for (size_t ii = 0; ii < nearbyTicketsVector[0].size(); ++ii)
        {
            std::vector<uint64_t> rulesPassed(rules.size(), 0);

            for (size_t i = 0; i < nearbyTicketsVector.size(); ++i)
            {
                for (size_t j = 0; j < rules.size(); j++)
                {
                    if (CheckRule(nearbyTicketsVector[i][ii], rules[j]))
                    {
                        ++rulesPassed[j];
                    }
                }
            }

            size_t ruleCandidate = -1;
            for (size_t j = 0; j < rulesPassed.size(); j++)
            {
                if (!usedRules[j] && rulesPassed[j] == nearbyTicketsVector.size())
                {
                    if (ruleCandidate == -1)
                    {
                        ruleCandidate = j;
                    }
                    else
                    {
                        ruleCandidate = -1;
                        break;
                    }
                }
            }

            if (ruleCandidate != -1)
            {
                columnNames[ii] = rules[ruleCandidate].name;
                usedRules[ruleCandidate] = true;
                ++foundNames;
            }
        }
    }

    // Calculating answer
    uint64_t multiplication = 1;
    uint64_t j = 0;
    for (size_t i = 0; i < yourTicketVector.size(); ++i)
    {
        if (columnNames[i].find("departure") != std::string::npos)
        {
            multiplication *= yourTicketVector[i];

            ++j;
        }

        if (j >= 6)
            break;
    }

    return multiplication;
}

int main()
{
    std::vector<std::string>* data = LoadFile("16.txt");

    std::cout << "Star1: " << Star1(*data) << std::endl;
    std::cout << "Star2: " << Star2(*data) << std::endl;

    delete data;

    return 0;
}
