#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>

class BoardRenderer {
public:
	BoardRenderer(int screenWidth, int screenHeight, int squareSize, int offSet);
	void drawBoard(Board& board);
	std::vector<std::pair<int, int>> movesFromSquareClicked(Board& board);
	std::pair<int, int> getSquareClicked();

	sf::RenderWindow window;

private:
	int squareSize;
	int offSet;

	string spriteFileToDraw(Board& board, int row, int col);
	void drawBoardCords();

};
