#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

enum Command
{
	nop,
	acc,
	jmp
};

struct ProgramCommand
{
	Command command;
	long long value;
	size_t numOfExec = 0;
};

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

std::vector<ProgramCommand>* LoadFile(std::string fileName)
{
	std::vector<ProgramCommand>* program = new std::vector<ProgramCommand>();

	std::fstream input;
	input.open(fileName, std::fstream::in);
	std::string fileLine;

	while (std::getline(input, fileLine))
	{
		// Parsing every line from file
		std::vector<std::string> temp = split(fileLine, " ");

		Command tempCommand;
		if (temp[0] == "nop")
		{
			tempCommand = nop;
		}
		else if (temp[0] == "acc")
		{
			tempCommand = acc;
		}
		else if (temp[0] == "jmp")
		{
			tempCommand = jmp;
		}

		long long tempValue = std::strtoll(temp[1].c_str(), NULL, 10);

		program->push_back(ProgramCommand{ tempCommand, tempValue, 0 });
	}
	input.close();

	return program;
}

long long Star1(std::vector<ProgramCommand>& program)
{
	long long accumulator = 0;

	for (size_t i = 0; i < program.size();)
	{
		if (program[i].numOfExec == 1)
			return accumulator;

		++program[i].numOfExec;
		switch (program[i].command)
		{
		case nop:
			++i;
			continue;
			break;
		case acc:
			accumulator += program[i].value;
			++i;
			break;
		case jmp:
			i += program[i].value;
			break;
		default:
			break;
		}
	}

	return accumulator;
}

long long Star2(std::vector<ProgramCommand>& program)
{
	return 0;
}

int main()
{
	std::vector<ProgramCommand>* program = LoadFile("8.txt");

	std::cout << "Star1: " << Star1(*program) << std::endl;
	std::cout << "Star2: " << Star2(*program) << std::endl;

	delete program;

	return 0;
}