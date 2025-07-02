#include "BoardRenderer.h"

BoardRenderer::BoardRenderer(int screenWidth, int screenHeight, int sqSize, int ofst) {

    window = sf::RenderWindow(sf::VideoMode({ static_cast<unsigned>(screenWidth), static_cast<unsigned>(screenHeight) }), "CHESS!");
    squareSize = sqSize;
    offSet = ofst;

}


void BoardRenderer::drawBoard(Board& board) {


    sf::Color backgroundColour(173, 216, 230); // light blue
    sf::Color lightSquares(196, 164, 132); //light brown
    sf::Color darkSquares(128, 101, 23); //oak


    window.clear(backgroundColour);
    drawBoardCords();

    //add all squares
    //moves from top left to bottom right
    bool isWhite = true;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            sf::Vector2f currentPos{ static_cast<float>(squareSize * j + offSet), static_cast<float>(squareSize * i + offSet) };

            //drawing square background
            sf::RectangleShape shape(sf::Vector2f{ static_cast<float>(squareSize), static_cast<float>(squareSize) });

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


string BoardRenderer::spriteFileToDraw(Board& board, int row, int col) {

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

std::vector<std::pair<int, int>> BoardRenderer::movesFromSquareClicked(Board& board) {

    std::pair<int, int> squareClicked = getSquareClicked();

    int row = squareClicked.second;
    int col = squareClicked.first;

    std::vector<std::pair<int, int>> possibleMoves;


    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        std::cout << " CLICKED AT! " <<  "row, col = " << row << "," << col << endl;
        possibleMoves = board.possibleMovesAt(col, row);
    }

    drawBoard(board);
    //DISPLAY MOVES AREA

    int numPairs = possibleMoves.size();
    for (int i = 0; i < numPairs; i++) {

        sf::Vector2f currentPos{ static_cast<float>(squareSize * possibleMoves.at(i).second + offSet), static_cast<float>(squareSize * possibleMoves.at(i).first + offSet) };

        //drawing square background
        sf::CircleShape shape;
        shape.setRadius(squareSize/2);
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(2);
        shape.setPosition(currentPos);
        window.draw(shape);
    }

    window.display();


    return possibleMoves;
}

std::pair<int, int> BoardRenderer::getSquareClicked() {

    sf::Vector2i mousePix = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(mousePix);

    //cpp trucs to 0 so have to floor to deal with out of bounds in top and left borders
    int row = std::floor((mousePos.x - offSet) / squareSize);
    int col = std::floor((mousePos.y - offSet) / squareSize);

    std::pair myPair = make_pair(col, row);

    return myPair;
}

void BoardRenderer::drawBoardCords() {

    const sf::Font font("Fonts/CoolveticaHvComp.otf");
    unsigned int fontSize = 30;

    sf::Text text(font, "1");
    text.setCharacterSize(fontSize);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Black);

    //TOP ROW
    for (int i = 0; i < 8; i++) {

        //ascii for a = 97

        char letter = i + 97;
        text.setString(letter);
        sf::Vector2f currentPos = { static_cast<float>((i * squareSize) + (offSet * 1.4)), static_cast<float>(offSet*0.4) };
        text.setPosition(currentPos);
        window.draw(text);
    }


    //BOTTOM ROW
    for (int i = 0; i < 8; i++) {

        //ascii for a = 97

        char letter = i + 97;
        text.setString(letter);
        sf::Vector2f currentPos = { static_cast<float>((i * squareSize) + (offSet * 1.4)), static_cast<float>(squareSize * 8 +  offSet) };
        text.setPosition(currentPos);
        window.draw(text);
    }


    //LEFT COL
    for (int i = 0; i < 8; i++) {

        text.setString(to_string(i + 1));
        sf::Vector2f currentPos = { static_cast<float>(offSet * 0.7), static_cast<float>(squareSize * i + offSet*1.2) };
        text.setPosition(currentPos);
        window.draw(text);
    }

    //LEFT COL
    for (int i = 0; i < 8; i++) {

        text.setString(to_string(i + 1));
        sf::Vector2f currentPos = { static_cast<float>(squareSize * 8 + offSet * 1.2), static_cast<float>(squareSize * i + offSet * 1.2) };
        text.setPosition(currentPos);
        window.draw(text);
    }

}
