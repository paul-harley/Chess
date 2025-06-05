#include <iostream>
#include "Piece.h"

using namespace std;


Piece::Piece(char sym, Colour color, int r, int c) {

	colour = color;
	row = r;
	col = c;
	symbol = sym;

	Piece::setValue(sym);
}

char Piece::getSymbol() {
	return symbol;
}

int Piece::getValue() {
	return value;
}

void Piece::setValue(char sym) {
	switch (sym)
	{
	case 'p':
		value = 1;
		break;

	case 'b':
	case 'n':
		value = 3;
		break;

	case 'r':
		value = 5;
		break;

	case 'q':
		value = 10;
		break;

	case 'k':
		value = 100;
		break;

	default:
		value = 0;
		break;
	}
}

std::vector<std::pair<int, int>> Piece::FindPossibleMoves() {

	std::vector<std::pair<int, int>> allPairs;

	return allPairs;
}

bool Piece::validCords(std::pair<int, int> pair) {

	if (pair.first > 7 || pair.first < 0) {
		return false;
	}

	if (pair.second > 7 || pair.second < 0) {
		return false;
	}

	return true;

}
