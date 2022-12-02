#include <iostream>
#include <fstream>
#include <sstream>

#define PRINT_DEBUG_STATEMENTS 0

enum Move {
	Rock,
	Paper,
	Scissors
};

enum Outcome {
	Win,
	Loss,
	Draw
};

static Move getMove(const char* moveStr) {
	if (strcmp(moveStr, "A") == 0 || strcmp(moveStr, "X") == 0) {
		return Move::Rock;
	}
	else if (strcmp(moveStr, "B") == 0 || strcmp(moveStr, "Y") == 0) {
		return Move::Paper;
	}
	else if (strcmp(moveStr, "C") == 0 || strcmp(moveStr, "Z") == 0) {
		return Move::Scissors;
	}
}

static int getScoreOfMove(Move move) {
	if (move == Move::Rock) {
		return 1;
	}
	else if (move == Move::Paper) {
		return 2;
	}
	else if (move == Move::Scissors) {
		return 3;
	}
}

static Outcome getOutcome(const char* outcomeStr) {
	if (strcmp(outcomeStr, "X") == 0) {
		return Outcome::Loss;
	}
	else if (strcmp(outcomeStr, "Y") == 0) {
		return Outcome::Draw;
	}
	else if (strcmp(outcomeStr, "Z") == 0) {
		return Outcome::Win;
	}
}

static Outcome determineOutcome(Move elfMove, Move yourMove) {
	if (elfMove == yourMove) {
		return Outcome::Draw;
	}
	else if (elfMove == Move::Paper) {
		if (yourMove == Move::Rock) {
			return Outcome::Loss;
		}
		else {
			return Outcome::Win;
		}
	}
	else if (elfMove == Move::Rock) {
		if (yourMove == Move::Paper) {
			return Outcome::Win;
		}
		else {
			return Outcome::Loss;
		}
	}
	else if (elfMove == Move::Scissors) {
		if (yourMove == Move::Paper) {
			return Outcome::Loss;
		}
		else {
			return Outcome::Win;
		}
	}
}

static int getScoreOfOutcome(Outcome outcome) {
	if (outcome == Outcome::Win) {
		return 6;
	}
	if (outcome == Outcome::Loss) {
		return 0;
	}
	if (outcome == Outcome::Draw) {
		return 3;
	}
}

// part 1: What would your total score be if everything goes exactly according to your strategy guide?:
int getAnswer1(std::string fpath)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for rock, paper scissors info
	std::string line;
	std::string elfMoveStr;
	std::string yourMoveStr;
	Move elfMove;
	Move yourMove;
	int yourScore = 0;

	while (std::getline(input, line))
	{
		std::istringstream iss(line);
		if (!(iss >> elfMoveStr >> yourMoveStr)) {
			break; // error
		}

		// process input

		// A, X = rock
		// B, Y = paper
		// C, Z = scissors
		// The score for a single round is the score for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors) 
		// plus the score for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).

		elfMove = getMove(elfMoveStr.c_str());
		yourMove = getMove(yourMoveStr.c_str());
		yourScore += getScoreOfMove(yourMove);
		yourScore += getScoreOfOutcome(determineOutcome(elfMove, yourMove));
	}

	// close the file after reading
	input.close();
	std::cout << std::endl;

	return yourScore;
}

// part 2: What would your total score be if everything goes exactly according to the elf's strategy guide?
int getAnswer2(std::string fpath)
{
	// open file for parsing
	std::ifstream input;
	input.open(fpath, std::ios::in);

	if (!input) {
		std::cout << std::endl << "Could not read the file" << std::endl;
	}

	// parse file for rock, paper scissors info
	std::string line;
	std::string elfMoveStr;
	std::string yourMoveStr;
	Move elfMove;
	Move yourMove;
	Outcome desiredOutcome;
	int yourScore = 0;

	while (std::getline(input, line))
	{
		std::istringstream iss(line);
		if (!(iss >> elfMoveStr >> yourMoveStr)) {
			break; // error
		}

		// process input

		// A = rock
		// B = paper
		// C = scissors
		// "Anyway, the second column says how the round needs to end: 
		//		X means you need to lose
		//		Y means you need to end the round in a draw
		//		Z means you need to win. Good luck!"
		elfMove = getMove(elfMoveStr.c_str());
		yourMove = getMove(yourMoveStr.c_str());

		desiredOutcome = getOutcome(yourMoveStr.c_str());
		yourScore += getScoreOfOutcome(desiredOutcome);

		if (desiredOutcome == Outcome::Loss) {
			if (elfMove == Move::Rock) {
				yourScore += getScoreOfMove(Move::Scissors);
			}
			else if (elfMove == Move::Paper) {
				yourScore += getScoreOfMove(Move::Rock);
			}
			else if (elfMove == Move::Scissors) {
				yourScore += getScoreOfMove(Move::Paper);
			}
		}
		else if (desiredOutcome == Outcome::Draw) {
			yourScore += getScoreOfMove(elfMove);
		}
		else if (desiredOutcome == Outcome::Win) {
			if (elfMove == Move::Rock) {
				yourScore += getScoreOfMove(Move::Paper);
			}
			else if (elfMove == Move::Paper) {
				yourScore += getScoreOfMove(Move::Scissors);
			}
			else if (elfMove == Move::Scissors) {
				yourScore += getScoreOfMove(Move::Rock);
			}
		}
	}

	// close the file after reading
	input.close();
	std::cout << std::endl;

	return yourScore;
}

int main(int argc, char* argv[])
{
	// init file path
	std::cout << argv[0];
	std::string fpath = argv[0];
	fpath.append("\\..\\..\\Day 2 - Rock Paper Scissors\\encrypted_strategies.txt");

	// get answers for part 1 & 2
	// https://adventofcode.com/2022/day/2
	int answer1 = getAnswer1(fpath);
	int answer2 = getAnswer2(fpath);

	std::cout << "What would your total score be if everything goes exactly according to your strategy guide?: " << answer1 << std::endl << std::endl;
	std::cout << "What would your total score be if everything goes exactly according to the elf's strategy guide?: " << answer2 << std::endl << std::endl;
}