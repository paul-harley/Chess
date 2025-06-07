#include <iostream>
#include <vector>
#include "Board.h"

void printVecPair(std::vector<std::pair<int, int>> myVec) {

    int size = myVec.size();

    for (int i = 0; i < size; i++) {
        std::cout << myVec.at(i).first << ", " << myVec.at(i).second << endl;
    }

}


int main()
{
    Board myBoard = Board();
    myBoard.printBoard();
    
    // any square chosen, return type of piece selected
    int row = 0;
    int col = 0;
    char pieceChose = myBoard.typeOfPieceAtCords(row,col);

    printVecPair(myBoard.possibleMovesAt(4,1));
    myBoard.setCheckStatus();

}


