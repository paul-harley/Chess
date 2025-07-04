#include <iostream>
#include "Board.h"


Board::Board() {
	
	currentTurnColour = Colour::WHITE;

	// i = rows
	// j = cols

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			char pieceToCreate = pieceDefaultLoaction(i, j);
			switch (pieceToCreate)
			{
			case 'p':
				if(i == 1)
					board[i][j] = std::make_unique<Pawn>(Colour::BLACK, i, j);
				else
					board[i][j] = std::make_unique<Pawn>(Colour::WHITE, i, j);
				break;

			case 'r':
				if(i == 0)
					board[i][j] = std::make_unique<Rook>(Colour::BLACK, i, j);
				else
					board[i][j] = std::make_unique<Rook>(Colour::WHITE, i, j);
				break;

			case 'n':
				if (i == 0)
					board[i][j] = std::make_unique<Knight>(Colour::BLACK, i, j);
				else
					board[i][j] = std::make_unique<Knight>(Colour::WHITE, i, j);
				break;

			case 'b':
				if (i == 0)
					board[i][j] = std::make_unique<Bishop>(Colour::BLACK, i, j);
				else
					board[i][j] = std::make_unique<Bishop>(Colour::WHITE, i, j);
				break;

			case 'q':
				if (i == 0)
					board[i][j] = std::make_unique<Queen>(Colour::BLACK, i, j);
				else
					board[i][j] = std::make_unique<Queen>(Colour::WHITE, i, j);
				break;

			case 'k':
				if (i == 0)
					board[i][j] = std::make_unique<King>(Colour::BLACK, i, j);
				else
					board[i][j] = std::make_unique<King>(Colour::WHITE, i, j);
				break;
			default:
				board[i][j] = std::make_unique<EmptySquare>(i, j);
				if (i == 3 && j == 1)
					board[i][j] = std::make_unique<King>(Colour::WHITE, i, j);
				if (i == 4 && j == 2)
					board[i][j] = std::make_unique<Queen>(Colour::WHITE, i, j);
				if (i == 5 && j == 3)
					board[i][j] = std::make_unique<Bishop>(Colour::BLACK, i, j);
				if (i == 4 && j == 6)
					board[i][j] = std::make_unique<Knight>(Colour::WHITE, i, j);
				break;
			}

		}
	}

}


void Board::printBoard() {

	string col_labels = "    a   b   c   d   e   f   g   h";
	string board_border_horiz = "  ---------------------------------";


	std::cout << col_labels << endl;

	for (int i = 0; i < 8; i++) {
		std::cout << board_border_horiz << endl;
		std::cout << 8 - i;
		for (int j = 0; j < 8; j++) {
			std::cout <<" | " << board[i][j]->getSymbol() << "";
		}

		std::cout << " | " << 8-i <<endl;
	}
	std::cout << board_border_horiz << endl;
	std::cout << col_labels << endl;
}


char Board::pieceDefaultLoaction(int i, int j) {

	switch (i) {

		//Pawn rows
	case 1:
		return 'p';
	case 6:
		return 'p';

		//Piece rows
	case 0:
	case 7:
		switch (j)
		{
		//rook
		case 0:
		case 7:
			return 'r';

		//knight
		case 1:
		case 6:
			return 'n';

		//bishop
		case 2:
		case 5:
			return 'b';

		//queen
		case 3:
			return 'q';

		//king
		case 4:
			return 'k';

		default:
			return ' ';
			break;
		}
		break;

	default:
		return ' ';
	}
}

void Board::makeMove(Piece* pieceMoving, int toRow, int toCol) {

	//if piece is a rook or king, it can no longer castle after moving
	Rook* rookPtr = dynamic_cast<Rook*>(pieceMoving);
	if (rookPtr) {
		rookPtr->hasMoved = true;
	}

	King* kingPtr = dynamic_cast<King*>(pieceMoving);
	if (kingPtr) {
		kingPtr->hasMoved = true;
	}

	int fromR = pieceMoving->row;
	int fromC = pieceMoving->col;

	board[toRow][toCol] = std::move(board[pieceMoving->row][pieceMoving->col]);
	board[toRow][toCol]->row = toRow;
	board[toRow][toCol]->col = toCol;

	board[fromR][fromC] = std::make_unique<EmptySquare>(fromR, fromC);

	Colour boardCheck = boardHasAcheck();

	if (boardCheck!= Colour::EMPTY) {
		std::cout <<toString(boardCheck)<< " IS CHECKED" << endl;
	}

	changeTurnColour();
	std::cout << toString(getTurnColour()) << " up next" << endl;

}

Colour Board::getTurnColour() {
	return currentTurnColour;
}

void Board::changeTurnColour() {

	if (currentTurnColour == Colour::WHITE) {
		currentTurnColour = Colour::BLACK;
	}
	else {
		currentTurnColour = Colour::WHITE;
	}
}


char Board::typeOfPieceAtCords(int i, int j) {

	Piece* basePtr = board[i][j].get(); // Get raw pointer from unique_ptr

	//try cast as different pieces, return when cast works

	Pawn* pawnPtr = dynamic_cast<Pawn*>(basePtr);
	if (pawnPtr) {
		return 'p';
	}

	Bishop* bishopPtr = dynamic_cast<Bishop*>(basePtr);
	if (bishopPtr) {
		return 'b';
	}

	Knight* knightPtr = dynamic_cast<Knight*>(basePtr);
	if (knightPtr) {
		return 'n';
	}

	Rook* rookPtr = dynamic_cast<Rook*>(basePtr);
	if (rookPtr) {
		return 'r';
	}

	Queen* queenPtr = dynamic_cast<Queen*>(basePtr);
	if (queenPtr) {
		return 'q';
	}

	King* kingPtr = dynamic_cast<King*>(basePtr);
	if (kingPtr) {
		return 'k';
	}


	return ' ';
}


std::vector<std::pair<int, int>> Board::possibleMovesAt(int i, int j, bool checkingPins) {

	char pieceSymbol = typeOfPieceAtCords(i, j);
	Piece * basePtr = board[i][j].get(); // Get raw pointer from unique_ptr
	
	switch (pieceSymbol)
	{
	case 'p': {
		Pawn* pawnPtr = dynamic_cast<Pawn*>(basePtr);
		return trimPossiblePieceMoves(pawnPtr, checkingPins);
	}

	case 'r': {
		Rook* rookPtr = dynamic_cast<Rook*>(basePtr);
		return trimPossiblePieceMoves(rookPtr, checkingPins);
	}

	case 'n': {
		Knight* knightPtr = dynamic_cast<Knight*>(basePtr);
		return trimPossiblePieceMoves(knightPtr, checkingPins);
	}

	case 'b': {
		Bishop* bishopPtr = dynamic_cast<Bishop*>(basePtr);
		return trimPossiblePieceMoves(bishopPtr, checkingPins);
	}

	case 'q': {
		Queen* queenPtr = dynamic_cast<Queen*>(basePtr);
		return trimPossiblePieceMoves(queenPtr, checkingPins);
	}

	case 'k': {
		King* kingPtr = dynamic_cast<King*>(basePtr);
		return trimPossiblePieceMoves(kingPtr, checkingPins);
	}
	//empty square
	default: {
		std::vector<std::pair<int, int>> allPairs;
		return allPairs;
	}
	}

}

#pragma region trimming moves


std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Rook* basePtr, bool checkingPins) {

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> pairsBeingChecked;
	std::pair<int, int > pair;

	std::vector<std::pair<int, int>> trimmedPairs;

	//vertical moves - row change, col same
	//find all moves with same col,
	int totalPairsToCheck = allPairs.size();
	
	for (int i = 0; i < totalPairsToCheck; i++) {
		if (allPairs.at(i).second == basePtr->col) {
			pairsBeingChecked.push_back(allPairs.at(i));
		}
	}

	//from original row move up til either off board or a piece
	bool validMove = true;
	int row = basePtr->row;
	while (validMove) {
		row--;
		if (row >= 0) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(row, basePtr->col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;

	}

	//repeat for moving down
	row = basePtr->row;
	validMove = true;
	while (validMove) {
		row++;
		if (row < 8) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(row, basePtr->col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;
	}


	//horizontal moves - row same, col change
	//find all moves with same col,

	for (int i = 0; i < totalPairsToCheck; i++) {
		if (allPairs.at(i).first == basePtr->row) {
			pairsBeingChecked.push_back(allPairs.at(i));
		}
	}
	//from original col move right til either off board or a piece
	validMove = true;
	int col = basePtr->col;
	while (validMove) {
		col++;
		if (col < 8) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(basePtr->row, col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;

	}

	//repeat for moving left
	validMove = true;
	col = basePtr->col;
	while (validMove) {
		col--;
		if (col >= 0) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(basePtr->row, col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;

	}


	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Knight* basePtr, bool checkingPins) {

	//knight can jump, so colour of any piece there is all needs checked

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;
	int numPairsToCheck = allPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {

		//empty squre - can move
		if (typeOfPieceAtCords(allPairs.at(i).first, allPairs.at(i).second) == ' ') {
			if (checkingPins && isMovePinned(basePtr, allPairs.at(i).first, allPairs.at(i).second) == false) {
				trimmedPairs.push_back(allPairs.at(i));
			}
			else {
				trimmedPairs.push_back(allPairs.at(i));
			}
		}

		//different colour - can move
		else if (board[allPairs.at(i).first][allPairs.at(i).second]->colour != basePtr->colour	) {
			if (checkingPins && isMovePinned(basePtr, allPairs.at(i).first, allPairs.at(i).second) == false) {
				trimmedPairs.push_back(allPairs.at(i));
			}
			else {
				trimmedPairs.push_back(allPairs.at(i));
			}
		}

	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Pawn* basePtr, bool checkingPins) {

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;

	std::vector<std::pair<int, int>> capturingPairs;
	int numPairsToCheck = allPairs.size();
	bool blockCheck = false;

	for (int i = 0; i < numPairsToCheck; i++) {
		//split up capturing moves
		//pawns can only capture diagonally, so must be a different col
		if (allPairs.at(i).second != basePtr->col) {
			if (typeOfPieceAtCords(allPairs.at(i).first, allPairs.at(i).second) != ' ') {

				//piece on diagonal is a different colour 
				if (board[allPairs.at(i).first][allPairs.at(i).second]->colour != basePtr->colour) {
					if (checkingPins && isMovePinned(basePtr, allPairs.at(i).first, allPairs.at(i).second) == false) {
						trimmedPairs.push_back(allPairs.at(i));
					}
					else {
						trimmedPairs.push_back(allPairs.at(i));
					}
				}
			}		
		}
		//foward move
		else {
			//square in front has a piece
			//will check 1 square in front first

			if (typeOfPieceAtCords(allPairs.at(i).first, allPairs.at(i).second) != ' ' ) {
				blockCheck = true;
			}
			if (blockCheck == false) {
				if (checkingPins && isMovePinned(basePtr, allPairs.at(i).first, allPairs.at(i).second) == false) {
					trimmedPairs.push_back(allPairs.at(i));
				}
				else {
					trimmedPairs.push_back(allPairs.at(i));
				}
			}

		}
	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(King* basePtr, bool checkingLegality) {

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;
	
	int numPairsToCheck = allPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		
		//square is not empty
		if (typeOfPieceAtCords(allPairs.at(i).first, allPairs.at(i).second) != ' ') {
			if (board[allPairs.at(i).first][allPairs.at(i).second]->colour != basePtr->colour) {

				//kings cant be pinned, only restriction is not allowed to move into check
				if (checkingLegality && legalKingMove(basePtr, allPairs.at(i)) == true) {
					trimmedPairs.push_back(allPairs.at(i));
				}
				
			}
		}
		else {
			if (checkingLegality && legalKingMove(basePtr, allPairs.at(i)) == true) {
				trimmedPairs.push_back(allPairs.at(i));
			}
		}

	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Bishop* basePtr, bool checkingPins) {

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;
	

	//split moves into the 4 directions that can be moved
	int numPairsToCheck = allPairs.size();

	std::vector<std::pair<int, int>> upRightPairs;
	std::vector<std::pair<int, int>> downRightPairs;
	std::vector<std::pair<int, int>> upLeftPairs;
	std::vector<std::pair<int, int>> downLeftPairs;

	for (int i = 0; i < numPairsToCheck; i++) {
		
		//up and right = -row, +col
		if (allPairs.at(i).first < basePtr->row && allPairs.at(i).second > basePtr->col) {
			upRightPairs.push_back(allPairs.at(i));
		}

		//down and right = +row, +col
		if (allPairs.at(i).first > basePtr->row && allPairs.at(i).second > basePtr->col) {
			downRightPairs.push_back(allPairs.at(i));
		}

		//up and left = -row, -col
		if (allPairs.at(i).first < basePtr->row && allPairs.at(i).second < basePtr->col) {
			upLeftPairs.push_back(allPairs.at(i));
		}

		//down and left = +row, -col
		if (allPairs.at(i).first > basePtr->row && allPairs.at(i).second < basePtr->col) {
			downLeftPairs.push_back(allPairs.at(i));
		}

	}


	//moves will be in order starting from closest to start
	//loop through can can add move if valid
	//move on to next set of moves if invalid


	//up right
	upRightPairs = validMovesFromVector(upRightPairs, basePtr, checkingPins);
	numPairsToCheck = upRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upRightPairs.at(i));
	}

	//down right
	downRightPairs = validMovesFromVector(downRightPairs, basePtr, checkingPins);
	numPairsToCheck = downRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downRightPairs.at(i));
	}

	//up left
	upLeftPairs = validMovesFromVector(upLeftPairs, basePtr, checkingPins);
	numPairsToCheck = upLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upLeftPairs.at(i));
	}

	//down left

	downLeftPairs = validMovesFromVector(downLeftPairs, basePtr, checkingPins);
	numPairsToCheck = downLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downLeftPairs.at(i));
	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Queen* basePtr, bool checkingPins) {

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;

	std::vector<std::pair<int, int>> pairsBeingChecked;
	std::pair<int, int > pair;

	//vertical moves - row change, col same
	//find all moves with same col,
	int totalPairsToCheck = allPairs.size();

	for (int i = 0; i < totalPairsToCheck; i++) {
		if (allPairs.at(i).second == basePtr->col) {
			pairsBeingChecked.push_back(allPairs.at(i));
		}
	}

	//from original row move up til either off board or a piece
	bool validMove = true;
	int row = basePtr->row;
	while (validMove) {
		row--;
		if (row >= 0) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(row, basePtr->col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}

				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;

	}

	//repeat for moving down
	row = basePtr->row;
	validMove = true;
	while (validMove) {
		row++;
		if (row < 8) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(row, basePtr->col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, row, basePtr->col) == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(row, basePtr->col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;
	}


	//horizontal moves - row same, col change
	//find all moves with same col,

	for (int i = 0; i < totalPairsToCheck; i++) {
		if (allPairs.at(i).first == basePtr->row) {
			pairsBeingChecked.push_back(allPairs.at(i));
		}
	}
	//from original col move right til either off board or a piece
	validMove = true;
	int col = basePtr->col;
	while (validMove) {
		col++;
		if (col < 8) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(basePtr->row, col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}

			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;

	}

	//repeat for moving left
	validMove = true;
	col = basePtr->col;
	while (validMove) {
		col--;
		if (col >= 0) {
			//if empty square it is a valid move
			if (typeOfPieceAtCords(basePtr->row, col) == ' ') {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				if (checkingPins && isMovePinned(basePtr, basePtr->row, col) == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				else if (checkingPins == false) {
					pair = make_pair(basePtr->row, col);
					trimmedPairs.push_back(pair);
				}
				validMove = false;
			}
			//own colour piece blocking
			else {
				validMove = false;
			}
		}
		else
			validMove = false;

	}


	//split moves into the 4 diagonals directions that can be moved
	int numPairsToCheck = allPairs.size();

	std::vector<std::pair<int, int>> upRightPairs;
	std::vector<std::pair<int, int>> downRightPairs;
	std::vector<std::pair<int, int>> upLeftPairs;
	std::vector<std::pair<int, int>> downLeftPairs;

	for (int i = 0; i < numPairsToCheck; i++) {

		//up and right = -row, +col
		if (allPairs.at(i).first < basePtr->row && allPairs.at(i).second > basePtr->col) {
			upRightPairs.push_back(allPairs.at(i));
		}

		//down and right = +row, +col
		if (allPairs.at(i).first > basePtr->row && allPairs.at(i).second > basePtr->col) {
			downRightPairs.push_back(allPairs.at(i));
		}

		//up and left = -row, -col
		if (allPairs.at(i).first < basePtr->row && allPairs.at(i).second < basePtr->col) {
			upLeftPairs.push_back(allPairs.at(i));
		}

		//down and left = +row, -col
		if (allPairs.at(i).first > basePtr->row && allPairs.at(i).second < basePtr->col) {
			downLeftPairs.push_back(allPairs.at(i));
		}

	}


	//moves will be in order starting from closest to start
	//loop through can can add move if valid
	//move on to next set of moves if invalid


	//up right
	upRightPairs = validMovesFromVector(upRightPairs, basePtr, checkingPins);
	numPairsToCheck = upRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upRightPairs.at(i));
	}

	//down right
	downRightPairs = validMovesFromVector(downRightPairs, basePtr, checkingPins);
	numPairsToCheck = downRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downRightPairs.at(i));
	}

	//up left
	upLeftPairs = validMovesFromVector(upLeftPairs, basePtr, checkingPins);
	numPairsToCheck = upLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upLeftPairs.at(i));
	}

	//down left

	downLeftPairs = validMovesFromVector(downLeftPairs, basePtr, checkingPins);
	numPairsToCheck = downLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downLeftPairs.at(i));
	}

	return trimmedPairs;

}


std::vector<std::pair<int, int>> Board::validMovesFromVector(std::vector<std::pair<int, int>> myPairs, Piece* basePtr, bool checkingPins) {
	
	std::vector<std::pair<int, int>> trimmedPairs;

	int numPairsToCheck = myPairs.size();
	for (int i = 0; i < numPairsToCheck; i++) {

		//square is empty
		if (typeOfPieceAtCords(myPairs.at(i).first, myPairs.at(i).second) == ' ') {
			if (checkingPins && isMovePinned(basePtr, myPairs.at(i).first, myPairs.at(i).second) == false) {
				trimmedPairs.push_back(myPairs.at(i));
			}
			else if (checkingPins == false) {
				trimmedPairs.push_back(myPairs.at(i));
			}
		}

		//piece can be captured
		else if (board[myPairs.at(i).first][myPairs.at(i).second]->colour != basePtr->colour) {
			if (checkingPins && isMovePinned(basePtr, myPairs.at(i).first, myPairs.at(i).second) == false) {
				trimmedPairs.push_back(myPairs.at(i));
			}
			else if (checkingPins == false) {
				trimmedPairs.push_back(myPairs.at(i));
			}
			break;
		}
		else {
			break;
		}
	}

	return trimmedPairs;
}

#pragma endregion


#pragma region checking checks

Colour Board::boardHasAcheck() {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			char pieceSymbol = typeOfPieceAtCords(i, j);
			switch (pieceSymbol)
			{
			case ' ':
				break;

				//pawns are different because not all moves are capturing moves
			case 'p': {
				Piece* basePtr = board[i][j].get();
				Pawn* pawnPtr = dynamic_cast<Pawn*>(basePtr);
				pawnPtr->FindPossibleMoves();
				Colour result = movesIncludeACheck(pawnPtr->capturingMoves, pawnPtr->colour);
				if (result != Colour::EMPTY) {
					cout << "(" << i << ", " << j << "), gave a check";
					return result;
				}
				break;
			}

					//piece here needs its moves checked
					//if a possible move includes a king, check status needs changed to in check
					//if none found, set it to not in check
			default: {

				Colour result = movesIncludeACheck(possibleMovesAt(i, j, false), board[i][j]->colour);
				if (result != Colour::EMPTY) {
					cout << "(" << i << ", " << j << "), gave a check";
					return result;
				}
			}

			}
		}

	}

	return Colour::EMPTY;
}

bool Board::boardHasAcheckPins(Colour pieceMovingCol) {

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			char pieceSymbol = typeOfPieceAtCords(i, j);
			switch (pieceSymbol)
			{
			case ' ':
				break;

			//pawns are different because not all moves are capturing moves
			case 'p': {
				Piece* basePtr = board[i][j].get();
				Pawn* pawnPtr = dynamic_cast<Pawn*>(basePtr);
				pawnPtr->FindPossibleMoves();
				bool result = movesIncludeACheckPins(pawnPtr->capturingMoves, pieceMovingCol);
				if (result) {
					cout << "(" << i << ", " << j << "), gave a check";
					return true;
				}
				break;
				}

			//piece here needs its moves checked
			//if a possible move includes a king, check status needs changed to in check
			//if none found, set it to not in check
			default: {
				bool result;
				result = movesIncludeACheckPins(possibleMovesAt(i, j, false), pieceMovingCol);
				if (result) {
					cout << "(" << i << ", " << j << "), gave a check";
					return true;
				}
			}
			
			}
		}

	}

	return false;
}



Colour Board::movesIncludeACheck(std::vector<std::pair<int, int>> pairs, Colour colourOfPieceChecked) {

	int numMoves = pairs.size();

	for (int i = 0; i < numMoves; i++) {
		Piece* basePtr = board[pairs.at(i).first][pairs.at(i).second].get();
		
		//capturing king is a possible move and is a check
		King* kingPtr = dynamic_cast<King*>(basePtr);
		if (kingPtr && kingPtr->colour != colourOfPieceChecked) {
			kingPtr->inCheck = true;
			return kingPtr->colour;
		}
	}

	return Colour::EMPTY;
}

bool Board::movesIncludeACheckPins(std::vector<std::pair<int, int>> pairs, Colour colourOfPieceChecked) {

	int numMoves = pairs.size();

	for (int i = 0; i < numMoves; i++) {
		Piece* basePtr = board[pairs.at(i).first][pairs.at(i).second].get();

		//capturing king is a possible move and is a check
		King* kingPtr = dynamic_cast<King*>(basePtr);
		if (kingPtr && kingPtr->colour == colourOfPieceChecked) {
			kingPtr->inCheck = true;
			cout << "CHECK";
			return true;
		}
	}

	return false;
}


#pragma endregion


#pragma region legal move checks

//probably check for this while trimming moves down
bool Board::isMovePinned(Piece* pieceMoving, int toRow, int toCol) {

	//for each move, simulate the board if it happened
	//if a check is found on the board the piece is pinned and cannot make that move

	//saving key data before move is made to allow for its reversal

	int fromR = pieceMoving->row;
	int fromC = pieceMoving->col;

	//saving piece captured so it can be replaced 
	unique_ptr<Piece> pieceCaptured = std::move(board[toRow][toCol]);

	board[toRow][toCol] = std::move(board[pieceMoving->row][pieceMoving->col]);
	board[toRow][toCol]->row = toRow;
	board[toRow][toCol]->col = toCol;

	board[fromR][fromC] = std::make_unique<EmptySquare>(fromR, fromC);
	std::cout << "...MOVE BEING TESTED..." << endl;
	printBoard();

	//move needs reversed and cannot be added
	//should check only if own king is in check
	if (boardHasAcheckPins(pieceMoving->colour) == true) {

		//set piece moving back to original square
		board[fromR][fromC] = std::move(board[toRow][toCol]);
		board[fromR][fromC]->row = fromR;
		board[fromR][fromC]->col = fromC;

		//set the captured piece back to its orginal location
		board[toRow][toCol] = std::move(pieceCaptured);
		board[toRow][toCol]->row = toRow;
		board[toRow][toCol]->col = toCol;

		std::cout << "...MOVE REVERSED..." << endl;
		printBoard();

		return true;
	}

	//move needs reversed but can be added to legal moves
	else {

		//set piece moving back to original square
		board[fromR][fromC] = std::move(board[toRow][toCol]);
		board[fromR][fromC]->row = fromR;
		board[fromR][fromC]->col = fromC;

		//set the captured piece back to its orginal location
		board[toRow][toCol] = std::move(pieceCaptured);
		board[toRow][toCol]->row = toRow;
		board[toRow][toCol]->col = toCol;

		std::cout << "...MOVE REVERSED..." << endl;
		printBoard();

		return false;
	}

}

bool Board::validMove(std::vector<std::pair<int, int>> legalMoves, std::pair<int, int> moveToMake) {

	int numLegalMoves = legalMoves.size();

	for (int i = 0; i < numLegalMoves; i++) {

		if (legalMoves.at(i).first == moveToMake.first && legalMoves.at(i).second == moveToMake.second) {
			return true;
		}
	}

	return false;

}

bool Board::legalKingMove(King* basePtr, std::pair<int, int> pair) {
	//saving key data before move is made to allow for its reversal

	int fromR = basePtr->row;
	int fromC = basePtr->col;

	//saving piece captured so it can be replaced 
	int toRow = pair.first;
	int toCol = pair.second;

	unique_ptr<Piece> pieceCaptured = std::move(board[toRow][toCol]);

	board[toRow][toCol] = std::move(board[basePtr->row][basePtr->col]);
	board[toRow][toCol]->row = toRow;
	board[toRow][toCol]->col = toCol;

	board[fromR][fromC] = std::make_unique<EmptySquare>(fromR, fromC);
	std::cout << "...MOVE BEING TESTED..." << endl;
	printBoard();

	//move needs reversed and cannot be added
	//should check only if own king is in check
	if (boardHasAcheck() == basePtr->colour) {

		//set piece moving back to original square
		board[fromR][fromC] = std::move(board[toRow][toCol]);
		board[fromR][fromC]->row = fromR;
		board[fromR][fromC]->col = fromC;

		//set the captured piece back to its orginal location
		board[toRow][toCol] = std::move(pieceCaptured);
		board[toRow][toCol]->row = toRow;
		board[toRow][toCol]->col = toCol;

		std::cout << "...MOVE REVERSED... ILLEGAL KING MOVE..." << endl;
		printBoard();
		return false;

	}

	//move needs reversed but can be added to legal moves
	else {

		//set piece moving back to original square
		board[fromR][fromC] = std::move(board[toRow][toCol]);
		board[fromR][fromC]->row = fromR;
		board[fromR][fromC]->col = fromC;

		//set the captured piece back to its orginal location
		board[toRow][toCol] = std::move(pieceCaptured);
		board[toRow][toCol]->row = toRow;
		board[toRow][toCol]->col = toCol;

		std::cout << "...MOVE REVERSED... LEGAL KING MOVE..." << endl;
		printBoard();

		return true;
	}

	return false;
}


#pragma endregion