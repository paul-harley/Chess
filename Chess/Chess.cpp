#include <iostream>
#include <vector>
#include "Board.h"

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

string spriteFileToDraw(Board& board, int row, int col) {

    //add piece if there is one
    char piece = board.typeOfPieceAtCords(row, col);

    switch (piece)
    {

    case 'p':
        if (board.board[row][col].get()->colour == Colour::BLACK) {
            return "Images/blackPawn.png";
        }
        else {
            return "Images/whitePawn.png";
        }

    case 'n':
        if (board.board[row][col].get()->colour == Colour::BLACK) {
            return "Images/blackKnight.png";
        }
        else {
            return "Images/whiteKnight.png";
        }

    case 'b':
        if (board.board[row][col].get()->colour == Colour::BLACK) {
            return "Images/blackBishop.png";
        }
        else {
            return "Images/whiteBishop.png";
        }

    case 'r':
        if (board.board[row][col].get()->colour == Colour::BLACK) {
            return "Images/blackRook.png";
        }
        else {
            return "Images/whiteRook.png";
        }

    case 'q':
        if (board.board[row][col].get()->colour == Colour::BLACK) {
            return "Images/blackQueen.png";
        }
        else {
            return "Images/whiteQueen.png";
        }

    case 'k':
        if (board.board[row][col].get()->colour == Colour::BLACK) {
            return "Images/blackKing.png";
        }
        else {
            return "Images/whiteKing.png";
        }



    default:
        return "";
    }

}

void drawBoard(sf::RenderWindow& window, Board& board) {

    sf::Color backgroundColour(173, 216, 230); // light blue
    sf::Color lightSquares(196, 164, 132); //light brown
    sf::Color darkSquares(128, 101, 23); //oak


    window.clear(backgroundColour);

    int squareSize = 60;

    //add all squares
    //moves from top left to bottom right
    bool isWhite = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            sf::Vector2f currentPos{ static_cast<float>(squareSize * j + 60), static_cast<float>(squareSize * i + 60) };

            //drawing square background
            sf::RectangleShape shape(sf::Vector2f{ static_cast<float>(squareSize), static_cast<float>(squareSize)});

            if (isWhite == true) {
                shape.setFillColor(darkSquares);
                //last colour of one row is same as start on next
                if (j != 7) {
                    isWhite = false;
                }
            }
            else {
                shape.setFillColor(lightSquares);
                //last colour of one row is same as start on next
                if (j != 7) {
                    isWhite = true;
                }
            }
            shape.setPosition(currentPos);
            window.draw(shape);
            
            //add piece if there is one
            string pieceFileName = spriteFileToDraw(board, i, j);
            if (pieceFileName.length() > 0) {
                const sf::Texture piece(pieceFileName);
                sf::Sprite sprite(piece);
                sprite.setPosition(currentPos);
                window.draw(sprite);
            }
        }
    }

    window.display();


}



int main() {


    Board myBoard = Board();
    myBoard.printBoard();
    sf::RenderWindow window(sf::VideoMode({ 600, 700 }), "CHESS!");


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        drawBoard(window, myBoard);

    }


    return 0;
}




