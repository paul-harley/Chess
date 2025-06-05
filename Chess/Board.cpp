#include <iostream>
#include "Board.h"


Board::Board() {
	
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
				if (i == 2 && j == 3)
					board[i][j] = std::make_unique<Queen>(Colour::WHITE, i, j);
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

	int fromR = pieceMoving->row;
	int fromC = pieceMoving->col;

	board[toRow][toCol] = std::move(board[pieceMoving->row][pieceMoving->col]);
	board[toRow][toCol]->row = toRow;
	board[toRow][toCol]->col = toCol;

	board[fromR][fromC] = std::make_unique<EmptySquare>(fromR, fromC);
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


std::vector<std::pair<int, int>> Board::possibleMovesAt(int i, int j) {

	char pieceSymbol = typeOfPieceAtCords(i, j);
	Piece * basePtr = board[i][j].get(); // Get raw pointer from unique_ptr
	
	switch (pieceSymbol)
	{
	case 'p': {
		Pawn* pawnPtr = dynamic_cast<Pawn*>(basePtr);
		return trimPossiblePieceMoves(pawnPtr);
	}

	case 'r': {
		Rook* rookPtr = dynamic_cast<Rook*>(basePtr);
		return trimPossiblePieceMoves(rookPtr);
	}

	case 'n': {
		Knight* knightPtr = dynamic_cast<Knight*>(basePtr);
		return trimPossiblePieceMoves(knightPtr);
	}

	case 'b': {
		Bishop* bishopPtr = dynamic_cast<Bishop*>(basePtr);
		return trimPossiblePieceMoves(bishopPtr);
	}

	case 'q': {
		Queen* queenPtr = dynamic_cast<Queen*>(basePtr);
		return trimPossiblePieceMoves(queenPtr);
	}

	case 'k': {
		King* kingPtr = dynamic_cast<King*>(basePtr);
		return trimPossiblePieceMoves(kingPtr);
	}
	//empty square
	default: {
		std::vector<std::pair<int, int>> allPairs;
		return allPairs;
	}
	}

}


std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Rook* basePtr) {

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
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
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
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
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
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
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
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
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

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Knight* basePtr) {

	//knight can jump, so colour of any piece there is all needs checked

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;
	int numPairsToCheck = allPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {

		//empty squre - can move
		if (typeOfPieceAtCords(allPairs.at(i).first, allPairs.at(i).second) == ' ') {
			trimmedPairs.push_back(allPairs.at(i));
		}

		//different colour - can move
		else if (board[allPairs.at(i).first][allPairs.at(i).second]->colour != basePtr->colour	) {
			trimmedPairs.push_back(allPairs.at(i));
		}

	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Pawn* basePtr) {

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
				trimmedPairs.push_back(allPairs.at(i));
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
				trimmedPairs.push_back(allPairs.at(i));
			}

		}
	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(King* basePtr) {

	std::vector<std::pair<int, int>> allPairs = basePtr->FindPossibleMoves();
	std::vector<std::pair<int, int>> trimmedPairs;
	
	int numPairsToCheck = allPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		
		//square is not empty
		if (typeOfPieceAtCords(allPairs.at(i).first, allPairs.at(i).second) != ' ') {
			if (board[allPairs.at(i).first][allPairs.at(i).first]->colour != basePtr->colour) {
				trimmedPairs.push_back(allPairs.at(i));
			}
		}
		else {
			trimmedPairs.push_back(allPairs.at(i));
		}

	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Bishop* basePtr) {

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
	upRightPairs = validMovesFromVector(upRightPairs, basePtr);
	numPairsToCheck = upRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upRightPairs.at(i));
	}

	//down right
	downRightPairs = validMovesFromVector(downRightPairs, basePtr);
	numPairsToCheck = downRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downRightPairs.at(i));
	}

	//up left
	upLeftPairs = validMovesFromVector(upLeftPairs, basePtr);
	numPairsToCheck = upLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upLeftPairs.at(i));
	}

	//down left

	downLeftPairs = validMovesFromVector(downLeftPairs, basePtr);
	numPairsToCheck = downLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downLeftPairs.at(i));
	}

	return trimmedPairs;

}

std::vector<std::pair<int, int>> Board::trimPossiblePieceMoves(Queen* basePtr) {

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
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
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
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[row][basePtr->col]->colour != basePtr->colour) {
				pair = make_pair(row, basePtr->col);
				trimmedPairs.push_back(pair);
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
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
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
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
			}
			//opposite colour can add, but is the end
			else if (board[basePtr->row][col]->colour != basePtr->colour) {
				pair = make_pair(basePtr->row, col);
				trimmedPairs.push_back(pair);
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
	upRightPairs = validMovesFromVector(upRightPairs, basePtr);
	numPairsToCheck = upRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upRightPairs.at(i));
	}

	//down right
	downRightPairs = validMovesFromVector(downRightPairs, basePtr);
	numPairsToCheck = downRightPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downRightPairs.at(i));
	}

	//up left
	upLeftPairs = validMovesFromVector(upLeftPairs, basePtr);
	numPairsToCheck = upLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(upLeftPairs.at(i));
	}

	//down left

	downLeftPairs = validMovesFromVector(downLeftPairs, basePtr);
	numPairsToCheck = downLeftPairs.size();

	for (int i = 0; i < numPairsToCheck; i++) {
		trimmedPairs.push_back(downLeftPairs.at(i));
	}

	return trimmedPairs;

}



std::vector<std::pair<int, int>> Board::validMovesFromVector(std::vector<std::pair<int, int>> myPairs, Piece* basePtr) {
	
	std::vector<std::pair<int, int>> trimmedPairs;

	int numPairsToCheck = myPairs.size();
	for (int i = 0; i < numPairsToCheck; i++) {

		//square is empty
		if (typeOfPieceAtCords(myPairs.at(i).first, myPairs.at(i).second) == ' ') {
			trimmedPairs.push_back(myPairs.at(i));
		}

		//piece can be captured
		else if (board[myPairs.at(i).first][myPairs.at(i).second]->colour != basePtr->colour) {
			trimmedPairs.push_back(myPairs.at(i));
			break;
		}
		else {
			break;
		}
	}

	return trimmedPairs;
}
