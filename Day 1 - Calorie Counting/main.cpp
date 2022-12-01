#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

#define PRINT_DEBUG_STATEMENTS 0

class Elf
{
public:
	Elf(int calories) : m_calories(calories) { }

	bool operator<(const Elf& other) const {
		return m_calories < other.m_calories;
	}

	bool operator>(const Elf& other) const {
		return m_calories > other.m_calories;
	}

	int getCalories() { return m_calories; }

private:
	int m_calories;
};

int getAnswer(std::string fpath, const int numOfElvesToGetCaloriesFor)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		printf("Could not read the file\n");
	}

	// parse file for Elf calories
	std::string line;
	int currCalories = 0;

	std::list<Elf> elves = std::list<Elf>();
	while (std::getline(input, line)) {
		// process input
		if (strcmp(line.c_str(), "") == 0) {
			elves.push_back(Elf(currCalories));
			currCalories = 0;
		}
		else {
			currCalories += std::stoi(line);
		}
	}

	// closing the file after reading
	input.close();

	elves.sort(std::greater<Elf>());
	int totalCalories = 0;

	for (int i = 0; i < numOfElvesToGetCaloriesFor; i++) {
		totalCalories += elves.front().getCalories();
		elves.pop_front();
	}

	return totalCalories;
}

int main(int argc, char* argv[])
{
	// init file path
	printf("argv: %s\n", argv[0]);
	std::string fpath = argv[0];
	fpath.append("\\..\\..\\Day 1 - Calorie Counting\\elf_calories.txt");

	// get answers for part 1 & 2
	// https://adventofcode.com/2022/day/1
	printf("What is the most calories a single elf is carrying?: %d\n", getAnswer(fpath, 1));
	printf("What is the total calories of the top 3 elves?: %d\n", getAnswer(fpath, 3));
}
