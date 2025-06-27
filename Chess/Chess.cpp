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

void drawBoard(sf::RenderWindow& window, Board& board) {

    //sets whole window to this colour
    sf::Color backgroundColour(0xADD8E6); // light blue
    window.clear(backgroundColour);

    int squareSize = 60;

    //add all squares
    //moves from top left to bottom right
    bool isWhite = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            //drawing square background
            sf::RectangleShape shape(sf::Vector2f{ static_cast<float>(squareSize), static_cast<float>(squareSize)});

            if (isWhite == true) {
                shape.setFillColor(sf::Color::White);
                //last colour of one row is same as start on next
                if (j != 7) {
                    isWhite = false;
                }
            }
            else {
                shape.setFillColor(sf::Color::Black);
                //last colour of one row is same as start on next
                if (j != 7) {
                    isWhite = true;
                }
            }
            shape.setPosition(sf::Vector2f{static_cast<float>(squareSize*j + 60), static_cast<float>(squareSize* i + 60) });
            //window.draw(shape);
            //add piece if there is one

            char piece = board.typeOfPieceAtCords(i, j);
            if (piece != ' ') {
                shape.setFillColor(sf::Color::Red);
            }
            window.draw(shape);

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




