#include "Knight.h"

Knight::Knight(Colour color, int row, int col)
	:Piece('n', color, row, col) {

	movement = 1;
}

std::vector<std::pair<int, int>> Knight::FindPossibleMoves() {

	// L shapes in all directions 

	std::vector<std::pair<int, int>> allPairs;
	std::pair<int, int> pair;

	// 2 up and left
	pair = make_pair(row - 1, col - 2);
	if (validCords(pair))
		allPairs.push_back(pair);

	pair = make_pair(row - 2, col - 1);
	if (validCords(pair))
		allPairs.push_back(pair);



	// 2 up and right
	pair = make_pair(row - 1, col + 2);
	if (validCords(pair))
		allPairs.push_back(pair);

	pair = make_pair(row - 2, col + 1);
	if (validCords(pair))
		allPairs.push_back(pair);



	// 2 down and left
	pair = make_pair(row + 1, col - 2);
	if (validCords(pair))
		allPairs.push_back(pair);

	pair = make_pair(row + 2, col - 1);
	if (validCords(pair))
		allPairs.push_back(pair);



	// 2 down and rihgt
	pair = make_pair(row + 1, col + 2);
	if (validCords(pair))
		allPairs.push_back(pair);

	pair = make_pair(row + 2, col + 1);
	if (validCords(pair))
		allPairs.push_back(pair);


	return allPairs;
}