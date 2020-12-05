#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string>* LoadFile(std::string fileName)
{
	std::vector<std::string>* passports = new std::vector<std::string>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;
	std::string temp;

	while (std::getline(input, fileLine))
	{
		if (fileLine == "")
		{
			passports->push_back(temp);
			temp = "";
		}
		else
		{
			temp += fileLine + "\n";
		}
			
	}
	input.close();

	passports->push_back(temp);

	return passports;
}

uint32_t Star1(std::vector<std::string>* passports)
{
	uint32_t validPasports = 0;

	std::string fields[] = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

	for (size_t i = 0; i < passports->size(); ++i)
	{
		bool valid = true;
		for (std::string field : fields)
		{
			if (passports->at(i).find(field) == std::string::npos)
			{
				valid = false;
				break;
			}
		}

		if (valid)
			++validPasports;
	}

	return validPasports;
}



uint32_t Star2(std::vector<std::string>* passports)
{
	uint32_t validPasports = 0;

	std::string fields[] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	for (size_t i = 0; i < passports->size(); ++i)
	{
		bool valid = true;

		for (std::string field : fields)
		{
			std::string temp = "";
			size_t start;
			size_t end;

			size_t position = passports->at(i).find(field);
			if (position == std::string::npos)
			{
				valid = false;
				break;
			}
			else
			{
				start = position + 4;

				size_t tempEnd[2];
				tempEnd[0] = passports->at(i).find(" ", start);
				tempEnd[1] = passports->at(i).find("\n", start);

				if (tempEnd[0] < tempEnd[1])
					end = tempEnd[0] - 1;
				else
					end = tempEnd[1] - 1;
				/*else if (tempEnd[0] > tempEnd[1])
					end = tempEnd[1] - 1;*/
					/*else
						end = passports->at(i).size() - 1;*/

				temp = passports->at(i).substr(start, end - start + 1);

				if (field == "byr")
				{
					uint32_t value = static_cast<uint32_t>(std::stoul(temp));

					if (value < 1920 || value > 2002)
					{
						valid = false;
						break;
					}
				}
				else if (field == "iyr")
				{
					uint32_t value = static_cast<uint32_t>(std::stoul(temp));

					if (value < 2010 || value > 2020)
					{
						valid = false;
						break;
					}
				}
				else if (field == "eyr")
				{
					uint32_t value = static_cast<uint32_t>(std::stoul(temp));

					if (value < 2020 || value > 2030)
					{
						valid = false;
						break;
					}
				}
				else if (field == "hgt")
				{
					size_t unitPosition;

					if ((unitPosition = temp.find("cm")) != std::string::npos)
					{
						uint32_t value = static_cast<uint32_t>(std::stoul(temp.substr(0, unitPosition)));

						if (value < 150 || value > 193)
						{
							valid = false;
							break;
						}
					}
					else if ((unitPosition = temp.find("in")) != std::string::npos)
					{
						uint32_t value = static_cast<uint32_t>(std::stoul(temp.substr(0, unitPosition)));

						if (value < 59 || value > 76)
						{
							valid = false;
							break;
						}
					}
					else
					{
						valid = false;
						break;
					}
				}
				else if (field == "hcl")
				{
					if (temp[0] != '#' || temp.size() > 7)
					{
						valid = false;
						break;
					}

					for (size_t i = 1; i < temp.size(); ++i)
					{
						if (!((temp[i] >= '0' && temp[i] <= '9') || (temp[i] >= 'a' && temp[i] <= 'f')))
						{
							valid = false;
							break;
						}
					}

					if (!valid)
						break;
				}
				else if (field == "ecl")
				{
					std::vector <std::string> validEyeColors = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

					if (std::find(validEyeColors.begin(), validEyeColors.end(), temp) == validEyeColors.end())
					{
						valid = false;
						break;
					}
				}
				else if (field == "pid")
				{
					if (temp.size() != 9)
					{
						valid = false;
						break;
					}

					for (size_t i = 0; i < temp.size(); ++i)
					{
						if (temp[i] < '0' || temp[i] > '9')
						{
							valid = false;
							break;
						}
					}

					if (!valid)
						break;
				}
			}
		}

		if (valid)
			++validPasports;
	}

	return validPasports;
}

int main()
{
	std::vector <std::string>* passports = LoadFile("4.txt");

	std::cout << "Star1: " << Star1(passports) << std::endl;
	std::cout << "Star2: " << Star2(passports) << std::endl;

	delete passports;

	return 0;
}