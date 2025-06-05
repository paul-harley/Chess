#pragma once

#include <iostream>
#include "vector"

using namespace std;

enum class Colour{
	WHITE,
	BLACK
};


class Piece {
public:
	Piece(char sym, Colour colour, int row, int col);
	virtual ~Piece() = default;
	virtual std::vector<std::pair<int, int>> FindPossibleMoves() ; //returns all possible moves for the piece, later trimmed in board


	Colour colour;
	int row;
	int col;

	char getSymbol();
	int getValue();

protected: 
	char symbol;
	int value;

	void setValue(char sym);
	bool validCords(std::pair<int, int>); // cords must fall in boards range (0,7)


};