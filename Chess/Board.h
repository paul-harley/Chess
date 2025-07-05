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
	Colour boardHasAcheck(); //general check on board for any checks, returns colour of piece in check, empty colour if no checks
	bool boardHasAcheckPins(Colour pieceMovingCol); //checks for pin checks on own king
	bool validMove(std::vector<std::pair<int, int>> legalMoves, std::pair<int, int> moveToMake);

	Colour getTurnColour();

	std::unique_ptr<Piece> board[8][8];


private:

	char pieceDefaultLoaction(int i, int j);
	std::vector<std::pair<int, int>> validMovesFromVector(std::vector<std::pair<int, int>> myPairs, Piece* basePtr, bool checkingPins);
	Colour currentTurnColour;
	void changeTurnColour();

	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Pawn* basePtr, bool checkingPins); //returns current legal moves on the board
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Rook* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Knight* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Bishop* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(Queen* basePtr, bool checkingPins);
	std::vector<std::pair<int, int>> trimPossiblePieceMoves(King* basePtr, bool checkingLegality); // king cannot be pinned

	Colour movesIncludeACheck(std::vector<std::pair<int, int>> pairs, Colour colourOfPieceChecked);
	bool movesIncludeACheckPins(std::vector<std::pair<int, int>> pairs, Colour colourOfPieceChecked);
	bool isMovePinned(Piece* pieceMoving, int toRow, int toCol);
	bool legalKingMove(King* basePtr, std::pair<int, int> pair);

	//TIME IN HERE AT SOME STAGE
};