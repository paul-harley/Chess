#include "EmptySquare.h"

EmptySquare::EmptySquare(int r, int c) 
	:Piece(' ', Colour::WHITE, r, c) {

}

std::vector<std::pair<int, int>> EmptySquare::FindPossibleMoves() {
	std::vector<std::pair<int, int>> allPairs;
	return allPairs;
}