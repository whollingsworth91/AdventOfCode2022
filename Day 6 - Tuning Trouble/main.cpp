#include <iostream>
#include <fstream>
#include <sstream>

#define PRINT_DEBUG_STATEMENTS 0

bool areAllCharsUnique(std::string string) {
	for (size_t i = 0; i < string.size(); i++) {
		for (size_t j = 0; j < string.size(); j++) {
			if (j != i && string.at(i) == string.at(j)) {
				return false;
			}
		}
	}

	return true;
}

// How many characters need to be processed before the first start-of-packet/message marker is detected?
size_t getPositionOfUniqueString(std::string fpath, const size_t uniqueStringLength)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for datastream
	std::string datastream;
	std::getline(input, datastream);
	input.close();

	// process input
	// In the protocol being used by the Elves, the start of a packet or message is indicated by a sequence of N characters that are all different
	// Specifically, it needs to report the number of characters from the beginning of the buffer to the end of the first such N-character marker.

	size_t positionOfUniqueString = 0;
	std::string compareString;
	for (size_t i = 0; i < datastream.size() - uniqueStringLength; i++) {
		compareString = datastream.substr(i, uniqueStringLength);
		if (areAllCharsUnique(compareString)) {
			printf("\nUnique string: \"%s\"\n", compareString.c_str());
			positionOfUniqueString = i + uniqueStringLength;
			break;
		}
		compareString.clear();
	}

	return positionOfUniqueString;
}

int main(int argc, char* argv[])
{
	// init file path
	std::cout << argv[0];
	std::string fpath = argv[0];
	fpath.append("\\..\\..\\Day 6 - Tuning Trouble\\datastream.txt");

	// get answers for part 1 & 2
	// https://adventofcode.com/2022/day/6
	int answer1 = getPositionOfUniqueString(fpath, 4);
	std::cout << "How many characters need to be processed before the first start-of-packet marker is detected?: " << answer1 << std::endl;
	int answer2 = getPositionOfUniqueString(fpath, 14);
	std::cout << "How many characters need to be processed before the first start-of-message marker is detected?: " << answer2 << std::endl;
}