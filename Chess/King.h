#pragma once
#include "Piece.h" 

class King : public Piece {

public:
	King(Colour color, int row, int col);
	std::vector<std::pair<int, int>> FindPossibleMoves() override; //returns all possible moves for the piece, later trimmed in board

	int movement;

};