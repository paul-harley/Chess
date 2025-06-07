#include "King.h"

King::King(Colour color, int row, int col)
	:Piece('k', color, row, col) {

	hasMoved = false;
	inCheck = false;
}

std::vector<std::pair<int, int>> King::FindPossibleMoves() {

	//can move 1 square, all directions

	std::vector<std::pair<int, int>> allPairs;
	std::pair<int, int> pair;


	//top row
		//top left
	pair = make_pair(row - 1, col - 1);
	if (validCords(pair))
		allPairs.push_back(pair);
		//top mid
	pair = make_pair(row - 1, col);
	if (validCords(pair))
		allPairs.push_back(pair);
		//top right
	pair = make_pair(row - 1, col + 1);
	if (validCords(pair))
		allPairs.push_back(pair);

	//mid row
		//mid left
	pair = make_pair(row, col - 1);
	if (validCords(pair))
		allPairs.push_back(pair);
		//mid right
	pair = make_pair(row, col + 1);
	if (validCords(pair))
		allPairs.push_back(pair);


	//bottom row
		//bottom left
	pair = make_pair(row + 1, col - 1);
	if (validCords(pair))
		allPairs.push_back(pair);
		//bottom mid
	pair = make_pair(row + 1, col);
	if (validCords(pair))
		allPairs.push_back(pair);
		//bottom right
	pair = make_pair(row + 1, col + 1);
	if (validCords(pair))
		allPairs.push_back(pair);

	return allPairs;
}
