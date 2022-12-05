#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>

#define PRINT_DEBUG_STATEMENTS 0

class Crate {
private:
	char m_crateLetter;
public:
	Crate(char crateLetter) {
		m_crateLetter = crateLetter;
	}

	char getLetter() {
		return m_crateLetter;
	}
};

class LoadingBay {
private:
	std::vector<std::list<Crate>> m_columns;
public:
	LoadingBay() {}
	LoadingBay(const int numColumns) {
		m_columns = std::vector<std::list<Crate>>(numColumns);
	}

	std::string getTopLetterOfEachColumn() {
		std::string ret;

		for (int i = 0; i < m_columns.size(); i++) {
			ret += m_columns.at(i).front().getLetter();
		}

		return ret;
	}

	void addCrate(int row, int column, Crate crate) {
		m_columns.at(column).push_back(crate);
	}

	void moveCrate(size_t numToMove, size_t fromColumnIdx, size_t toColumnIdx) {
		_ASSERT(m_columns.size() > 0 && m_columns.size() >= fromColumnIdx && m_columns.size() >= toColumnIdx);

		for (size_t i = 0; i < numToMove; i++) {
			m_columns.at(toColumnIdx).push_front(m_columns.at(fromColumnIdx).front());
			m_columns.at(fromColumnIdx).pop_front();
		}
	}

	void moveCrateRange(size_t numToMove, size_t fromColumnIdx, size_t toColumnIdx) {
		_ASSERT(m_columns.size() > 0 && m_columns.size() >= fromColumnIdx && m_columns.size() >= toColumnIdx);
		std::list<Crate> cratesToMove = std::list<Crate>();

		for (size_t i = 0; i < numToMove; i++) {
			cratesToMove.push_back(m_columns.at(fromColumnIdx).front());
			m_columns.at(fromColumnIdx).pop_front();
		}

		for (size_t j = 0; j < numToMove; j++) {
			m_columns.at(toColumnIdx).push_front(cratesToMove.back()); 
			cratesToMove.pop_back();
		}
	}
};

// part 1: After the rearrangement procedure completes, what crate ends up on top of each stack?
std::string getAnswer1(std::string fpath)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for loading bay
	std::string line;
	std::string garbage;
	LoadingBay loadingBay;
	int howManyToMove = 0;
	int fromColumnIdx = 0;
	int toColumnIdx = 0;
	loadingBay = LoadingBay(9);// line.size() / 4);

	while (std::getline(input, line))
	{
		// process input
		if (strcmp(line.substr(0, 4).c_str(), "move") == 0) {
			std::istringstream iss(line);
			if (!(iss >> garbage >> howManyToMove >> garbage >> fromColumnIdx >> garbage >> toColumnIdx)) {
				break; // error
			}

			loadingBay.moveCrate(howManyToMove, fromColumnIdx - 1, toColumnIdx - 1); // 0-based array indices
		}
		else {
			std::vector<std::pair<int, Crate>> rowColumn = std::vector<std::pair<int, Crate>>();

			for (size_t i = 0; i < line.size(); i++) {
				if (i % 4 == 0) {
					std::string crateLetterStr = line.substr(i, 4);
					if (crateLetterStr.at(0) == '[') {
						char crateLetter = crateLetterStr.at(1);
						rowColumn.push_back(std::pair<int, Crate>((i/4) + 1, Crate(crateLetter)));
						loadingBay.addCrate(0, (i / 4), Crate(crateLetter)); // 0-based array indices
					}
				}
			}
		}
	}

	//closing the file after reading
	input.close();
	std::cout << std::endl;

	return loadingBay.getTopLetterOfEachColumn();
}

// part 2: ?
std::string getAnswer2(std::string fpath)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for loading bay
	std::string line;
	std::string garbage;
	LoadingBay loadingBay;
	int howManyToMove = 0;
	int fromColumnIdx = 0;
	int toColumnIdx = 0;
	loadingBay = LoadingBay(9);// line.size() / 4);

	while (std::getline(input, line))
	{
		// process input
		if (strcmp(line.substr(0, 4).c_str(), "move") == 0) {
			std::istringstream iss(line);
			if (!(iss >> garbage >> howManyToMove >> garbage >> fromColumnIdx >> garbage >> toColumnIdx)) {
				break; // error
			}

			loadingBay.moveCrateRange(howManyToMove, fromColumnIdx - 1, toColumnIdx - 1); // 0-based array indices
		}
		else {
			std::vector<std::pair<int, Crate>> rowColumn = std::vector<std::pair<int, Crate>>();

			for (size_t i = 0; i < line.size(); i++) {
				if (i % 4 == 0) {
					std::string crateLetterStr = line.substr(i, 4);
					if (crateLetterStr.at(0) == '[') {
						char crateLetter = crateLetterStr.at(1);
						rowColumn.push_back(std::pair<int, Crate>((i / 4) + 1, Crate(crateLetter)));
						loadingBay.addCrate(0, (i / 4), Crate(crateLetter)); // 0-based array indices
					}
				}
			}
		}
	}

	//closing the file after reading
	input.close();
	std::cout << std::endl;

	return loadingBay.getTopLetterOfEachColumn();
}

int main(int argc, char* argv[])
{
	// init file path
	std::cout << argv[0];
	std::string fpath = argv[0];
	fpath.append("\\..\\..\\Day 5 - Supply Stacks\\rearrangement_instructions.txt");

	// get answers for part 1 & 2
	// https://adventofcode.com/2022/day/5
	std::string answer1 = getAnswer1(fpath);
	std::string answer2 = getAnswer2(fpath);

	std::cout << "After the rearrangement procedure completes, what crate ends up on top of each stack when using the CrateMaster 9000?: " << answer1 << std::endl << std::endl;
	std::cout << "After the rearrangement procedure completes, what crate ends up on top of each stack when using the CrateMaster 9001?: " << answer2 << std::endl << std::endl;
}