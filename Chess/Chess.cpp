#include <iostream>
#include <vector>
#include "BoardRenderer.h"

void printVecPair(std::vector<std::pair<int, int>> myVec) {

    cout << "Possible moves then" << endl;
    int size = myVec.size();

    for (int i = 0; i < size; i++) {
        std::cout << myVec.at(i).first << ", " << myVec.at(i).second << endl;
    }

}


int main1()
{
    Board myBoard = Board();
    myBoard.printBoard();
    
    // any square chosen, return type of piece selected
    int row = 0;
    int col = 0;
    char pieceChose = myBoard.typeOfPieceAtCords(row,col);

    printVecPair(myBoard.possibleMovesAt(4,2));

    return 0;

}

#include <SFML/Graphics.hpp>




int main() {


    Board myBoard = Board();
    myBoard.printBoard();

    int screenWidth = 600;
    int screenHeight = 700;
    int squareSize = 60;
    int offSet = 60;

    bool pieceSelected = false;
    std::vector<std::pair<int, int>> moves;
    std::pair<int, int> firstSqrClicked;


    BoardRenderer br(screenWidth, screenHeight, squareSize, offSet);


    br.drawBoard(myBoard);

    while (br.window.isOpen())
    {
        while (const std::optional event = br.window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                br.window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {

                //br.drawBoard(myBoard);

                //user has not chose a piece to move yet
                if (pieceSelected == false) {
                    firstSqrClicked = br.getSquareClicked();
                    if (myBoard.board[firstSqrClicked.first][firstSqrClicked.second]->colour == myBoard.getTurnColour()) {

                        moves = br.movesFromSquareClicked(myBoard);
                        printVecPair(moves);
                        if (moves.size() > 0) {
                            pieceSelected = true;
                        }
                        else {
                            pieceSelected = false;
                        }
                    }
                }
                else{
                    std::pair<int, int> secondSqrClicked = br.getSquareClicked();
                    std::cout << secondSqrClicked.first << ", " << secondSqrClicked.second << endl;

                    if (myBoard.validMove(moves, secondSqrClicked) == true) {
                        myBoard.makeMove(myBoard.board[firstSqrClicked.first][firstSqrClicked.second].get(), secondSqrClicked.first, secondSqrClicked.second);
                    }

                    br.drawBoard(myBoard);
                    pieceSelected = false;
                }

                //printVecPair( br.movesFromSquareClicked(myBoard));
            }
        }
    }


    return 0;
}




