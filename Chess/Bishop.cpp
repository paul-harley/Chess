#include "Bishop.h"

Bishop::Bishop(Colour color, int row, int col)
	:Piece('b', color, row, col) {

	movement = 1;
}

std::vector<std::pair<int, int>> Bishop::FindPossibleMoves() {

	//can move 4 directions, unlimited each diagonal

	std::vector<std::pair<int, int>> allPairs;
	std::pair<int, int> pair;



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