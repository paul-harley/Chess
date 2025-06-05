#include "Queen.h"

Queen::Queen(Colour color, int row, int col)
	:Piece('q', color, row, col) {

	movement = 1;
}

std::vector<std::pair<int, int>> Queen::FindPossibleMoves() {

	// all directions, unlimited amount

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


	//up and right
	int i = row;
	int j = col;
	while (true) {
		i--;
		j++;
		pair = make_pair(i, j);
		if (validCords(pair)) {
			allPairs.push_back(pair);
		}
		else {
			break;
		}
	}

	//down and right
	i = row;
	j = col;
	while (true) {
		i++;
		j++;
		pair = make_pair(i, j);
		if (validCords(pair)) {
			allPairs.push_back(pair);
		}
		else {
			break;
		}
	}

	//up and left
	i = row;
	j = col;
	while (true) {
		i--;
		j--;
		pair = make_pair(i, j);
		if (validCords(pair)) {
			allPairs.push_back(pair);
		}
		else {
			break;
		}
	}

	//down and left
	i = row;
	j = col;
	while (true) {
		i++;
		j--;
		pair = make_pair(i, j);
		if (validCords(pair)) {
			allPairs.push_back(pair);
		}
		else {
			break;
		}
	}


	return allPairs;
}