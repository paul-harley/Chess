#pragma once

#include "Piece.h"


class EmptySquare : public Piece {

public:
	EmptySquare(int r, int c);
	std::vector<std::pair<int, int>> FindPossibleMoves() override; //returns all possible moves for the piece, later trimmed in board


};