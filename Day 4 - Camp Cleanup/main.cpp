#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define PRINT_DEBUG_STATEMENTS 0

class Elf {
private:
	int m_startSection;
	int m_endSection;
public:
	Elf() {
		m_startSection = 0;
		m_endSection = 0;
	}

	Elf(int startSection, int endSection) {
		m_startSection = startSection;
		m_endSection = endSection;
	};
	~Elf() {};

	void setStartSection(int startSection) {
		m_startSection = startSection;
	}

	void setEndSection(int endSection) {
		m_endSection = endSection;
	}

	void setSectionRange(int startSection, int endSection) {
		m_startSection = startSection;
		m_endSection = endSection;
	}

	bool doesSectionRangeFullyContain(Elf otherElf) {
		return (m_startSection <= otherElf.m_startSection && m_endSection >= otherElf.m_endSection);
	}

	bool doesSectionRangeOverlapWith(Elf otherElf) {
		if ((m_startSection >= otherElf.m_startSection && m_endSection <= otherElf.m_startSection) ||
			(m_endSection >= otherElf.m_startSection && m_endSection <= otherElf.m_endSection)) {
			return true;
		}
		else return false;
	}
};

Elf createElf(std::string elfSectionStr) {
	Elf elf = Elf();

	int hyphenPos = elfSectionStr.find_first_of('-');
	if (hyphenPos != std::string::npos) {
		std::string firstSectionStr = elfSectionStr.substr(0, hyphenPos);
		std::string secondSectionStr = elfSectionStr.substr(hyphenPos + 1);
		elf.setSectionRange(std::stoi(elfSectionStr), std::stoi(secondSectionStr));
	}

	return elf;
}

// part 1: In how many assignment pairs does one range fully contain the other?
int getAnswer1(std::string fpath)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for elf sections
	std::string line;
	int doesFullyContainCount = 0;
	std::vector<std::pair<Elf, Elf>> elfPairs = std::vector<std::pair<Elf, Elf>>(); // may be useful for debugging

	while (std::getline(input, line))
	{
		// process input
		int commaPos = line.find_first_of(',');
		if (commaPos != std::string::npos) {
			std::string firstElfSectionStr = line.substr(0, commaPos);
			Elf firstElf = createElf(firstElfSectionStr);

			std::string secondElfSectionStr = line.substr(commaPos + 1);
			Elf secondElf = createElf(secondElfSectionStr);

			elfPairs.push_back(std::pair<Elf, Elf>(firstElf, secondElf));

			if (firstElf.doesSectionRangeFullyContain(secondElf) || secondElf.doesSectionRangeFullyContain(firstElf)) {
				doesFullyContainCount += 1;
			}
		}
	}

	//closing the file after reading
	input.close();
	std::cout << std::endl;

	return doesFullyContainCount;
}

// part 2: In how many assignment pairs do the ranges overlap?
int getAnswer2(std::string fpath)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for elf sections
	std::string line;
	int doesPartiallyContainCount = 0;
	std::vector<std::pair<Elf, Elf>> elfPairs = std::vector<std::pair<Elf, Elf>>(); // may be useful for debugging

	while (std::getline(input, line))
	{
		// process input
		int commaPos = line.find_first_of(',');
		if (commaPos != std::string::npos) {
			std::string firstElfSectionStr = line.substr(0, commaPos);
			Elf firstElf = createElf(firstElfSectionStr);

			std::string secondElfSectionStr = line.substr(commaPos + 1);
			Elf secondElf = createElf(secondElfSectionStr);

			elfPairs.push_back(std::pair<Elf, Elf>(firstElf, secondElf));

			if (firstElf.doesSectionRangeOverlapWith(secondElf) || secondElf.doesSectionRangeOverlapWith(firstElf)) {
				doesPartiallyContainCount += 1;
			}
		}
	}

	//closing the file after reading
	input.close();
	std::cout << std::endl;

	return doesPartiallyContainCount;
}

int main(int argc, char* argv[])
{
	// init file path
	std::cout << argv[0];
	std::string fpath = argv[0];
	fpath.append("\\..\\..\\Day 4 - Camp Cleanup\\section_ids.txt");

	// get answers for part 1 & 2
	// https://adventofcode.com/2022/day/4
	int answer1 = getAnswer1(fpath);
	int answer2 = getAnswer2(fpath);

	std::cout << "In how many assignment pairs does one range fully contain the other?: " << answer1 << std::endl << std::endl;
	std::cout << "In how many assignment pairs do the ranges overlap?: " << answer2 << std::endl << std::endl;
}