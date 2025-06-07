#include "Rook.h"

Rook::Rook(Colour color, int row, int col)
	:Piece('r', color, row, col) {

	hasMoved = false;
}

std::vector<std::pair<int, int>> Rook::FindPossibleMoves() {

	//moves 4 cardinal directions, unlimited amount

	std::vector<std::pair<int, int>> allPairs;
	pair<int, int> pair;

	//vertical moves
	for (int i = 0; i < 8; i++) {
		if (i != row) {
			pair = make_pair(i, col);
			allPairs.push_back(pair);
		}

	}

	//horizontal move
	for (int j = 0; j < 8; j++) {
		if (j != col) {
			pair = make_pair(row, j);
			allPairs.push_back(pair);
		}

	}



	return allPairs;
}