#pragma once
#include "Piece.h"


class Pawn: public Piece {
public:
	Pawn(Colour color, int row, int col);
	std::vector<std::pair<int, int>> FindPossibleMoves() override; //returns all possible moves for the piece, later trimmed in board

	std::vector<std::pair<int, int>> capturingMoves;
};
