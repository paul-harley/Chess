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

void drawBoard(sf::RenderWindow& window, Board& board, int squareSize, int offSet) {

    sf::Color backgroundColour(173, 216, 230); // light blue
    sf::Color lightSquares(196, 164, 132); //light brown
    sf::Color darkSquares(128, 101, 23); //oak


    window.clear(backgroundColour);

    //add all squares
    //moves from top left to bottom right
    bool isWhite = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            sf::Vector2f currentPos{ static_cast<float>(squareSize * j + offSet), static_cast<float>(squareSize * i + offSet) };

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


std::vector<std::pair<int, int>> movesFromSquareClicked(sf::RenderWindow& window, Board& board, int squareSize, int offSet) {

    sf::Vector2i mousePix = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePix);

    //cpp trucs to 0 so have to floor to deal with out of bounds in top and left border
    int row = std::floor((mousePos.x - offSet) / squareSize);
    int col = std::floor((mousePos.y - offSet) / squareSize);

    std::vector<std::pair<int, int>> possibleMoves;


    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        std::cout << " CLICKED AT! " << mousePos.x << ", " << mousePos.y << "row, col = " << row << "," << col << endl;
        possibleMoves = board.possibleMovesAt(col, row);
        printVecPair(possibleMoves);
    }
    return possibleMoves;
}


int main() {


    Board myBoard = Board();
    myBoard.printBoard();
    sf::RenderWindow window(sf::VideoMode({ 600, 700 }), "CHESS!");
    int squareSize = 60;
    int offSet = 60;



    drawBoard(window, myBoard, squareSize, offSet);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::MouseButtonPressed>()) {
                movesFromSquareClicked(window, myBoard, squareSize, offSet);
            }
        }
    }


    return 0;
}




