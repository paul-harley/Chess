#include "Pawn.h"

Pawn::Pawn(Colour color, int row, int col)
	: Piece('p', color, row, col) {
	// probably something with movement in here
}

std::vector<std::pair<int, int>> Pawn::FindPossibleMoves() {

	capturingMoves.clear();

	std::vector<std::pair<int, int>> allPairs;
	std::pair<int, int> pair;

	//2 options
	// if its on starting square, can move up 1 or 2
	// if anywhere else 1 only

	//can get 1 square diagonal in front

	if (colour == Colour::WHITE) {
		if (row == 6) {

			pair = make_pair(row - 1, col);
			allPairs.push_back(pair);

			pair = make_pair(row - 2, col);
			allPairs.push_back(pair);
		}
		else {
			if (row - 1 >= 0) {
				pair = make_pair(row - 1, col);
				allPairs.push_back(pair);
			}
		}

		//front diagonals
		//front right
		if (col + 1 < 8 && row - 1 > 0) {
			pair = make_pair(row - 1, col + 1);
			capturingMoves.push_back(pair);
			allPairs.push_back(pair);
		}
		//front left
		if (col - 1 < 8 && row - 1 > 0) {
			pair = make_pair(row - 1, col - 1);
			capturingMoves.push_back(pair);
			allPairs.push_back(pair);
		}

	}
	//black pawns
	else {
		if (row == 1) {
			pair = make_pair(row + 1, col);
			allPairs.push_back(pair);

			pair = make_pair(row + 2, col);
			allPairs.push_back(pair);
		}
		else {
			if (row + 1 < 8) {
				pair = make_pair(row + 1, col);
				allPairs.push_back(pair);
			}
		}

		//front diagonals
		//front right
		if (col + 1 < 8 && row + 1 < 8) {
			pair = make_pair(row + 1, col + 1);
			capturingMoves.push_back(pair);
			allPairs.push_back(pair);
		}

		//front left
		if (col - 1 < 8 && row + 1 < 8) {
			pair = make_pair(row + 1, col - 1);
			capturingMoves.push_back(pair);
			allPairs.push_back(pair);
		}
	}
	return allPairs;
}