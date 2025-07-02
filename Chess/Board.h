#pragma once

#include <iostream>
#include <array>
#include <memory>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "EmptySquare.h"

class Board {
public:
	Board();

	void printBoard();
	void makeMove(Piece* pieceMoving, int toRow, int toCol);
	char typeOfPieceAtCords(int i, int j);
	std::vector<std::pair<int, int>> possibleMovesAt(int i, int j, bool checkingPins = true);
	bool boardHasAcheck();
	bool isMovePinned(Piece* pieceMoving, int toRow, int toCol);
	bool validMove(std::vector<std::pair<int, int>> legalMoves, std::pair<int, int> moveToMake);

	std::unique_ptr<Piece> board[8][8];

private:

	char pieceDefaultLoaction(int i, int j);
	std::vector<std::pair<int, int>> validMovesFromVector(std::vector<std::pair<int, int>> myPairs, Piece* basePtr, bool checkingPins);

	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Pawn* basePtr, bool checkingPins); //returns current legal moves on the board
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Rook* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Knight* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Bishop* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Queen* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(King* basePtr, bool checkingPins);

	bool movesIncludeACheck(std::vector<std::pair<int, int>> pairs);

	//TIME IN HERE AT SOME STAGE
};