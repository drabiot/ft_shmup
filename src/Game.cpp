/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:10 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 14:40:07 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game( void ) {
	size_t	xMax;
	size_t	yMax;

	//Init Game Screen
	initscr();

	//Create & Init Playing Board
	refresh();
	getmaxyx(stdscr, yMax, xMax);
	this->_board = newwin(HEIGHT, LENGTH, (yMax / 2) - (HEIGHT / 2), (xMax / 2) - (LENGTH / 2));

	this->_gameOver = false;
}

Game::~Game( void ) {
	//End the Game Screen
	endwin();
}

void	Game::initializeBorder( void ) {
	this->clearBorder();
	this->refreshBorder();
}

void	Game::addBorder( void ) {
	box(this->_board, 0, 0);
}

void	Game::clearBorder( void ) {
	wnoutrefresh(this->_board);
	this->addBorder();
}

void	Game::refreshBorder( void ) {
	wrefresh(this->_board);
}

void	Game::addAt( int y, int x, chtype ch) {
	mvwaddch(this->_board, y, x, ch);
}

chtype	Game::getInput( void ) {
	noecho();
	curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(this->_board, TRUE);
	
	return (wgetch(this->_board));
}

bool	Game::isGameOver( void ) {
	return (this->_gameOver);
}

void	Game::processInput( void ) {
	chtype	input = this->getInput();
	switch (input) {
		case 'w':
			if (this->_player.getPosY() - 1 > 0)
				this->_player.setPosY(this->_player.getPosY() - 1);
			break;
		case 's':
			if (this->_player.getPosY() + 1 < HEIGHT - 1)
				this->_player.setPosY(this->_player.getPosY() + 1);
			break;
		case 'd':
			if (this->_player.getPosX() + 1 < LENGTH - 1)
				this->_player.setPosX(this->_player.getPosX() + 1);
			break;
		case 'a':
			if (this->_player.getPosX() - 1 > 0)
				this->_player.setPosX(this->_player.getPosX() - 1);
			break;
		default:
			break;
	}
}

void	Game::updateGame( void ) {
	this->clearBorder();

	//Create Background
	this->createBackground();

	//Create Player
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	wattron(this->_board, COLOR_PAIR(2));
	wattron(this->_board, A_BOLD);
	this->addAt(this->_player.getPosY(), this->_player.getPosX(), '>');
	wattroff(this->_board, A_BOLD);
	wattroff(this->_board, COLOR_PAIR(2));
	
	this->refreshBorder();
}

void	Game::createBackground( void ) {
	wattroff(this->_board, COLOR_PAIR(3));
	//Create Background
	char background[40][300];

    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 300; j++) {
            background[i][j] = ' ';
        }
    }
	const char *art[] = {
	".......                                                                                      ..............                                                                                      ..............                                                                                      .......",
	"..........                                                                   .................................                                                                   .................................                                                                   .......................",
	".............                                                          ..........................................                                                          ..........................................                                                          .............................",
	"................ . . . .. .. . .                                 .. ................................................ . . . .. .. . .                                 .. ................................................ . . . .. .. . .                                 .. ................................",
	"...........................................                ....................................................................................                ....................................................................................                .........................................",
	"............................................................................................................................................................................................................................................................................................................",
	"............................................................................................................................................................................................................................................................................................................",
	"............................................................................................................................................................................................................................................................................................................",
	"xxx............................................................................................xxxxxxxx............................................................................................xxxxxxxx............................................................................................xxxxx",
	"xxxxxxxx..............................................................................xxxxxxxxxxxxxxxxxxxxxx..............................................................................xxxxxxxxxxxxxxxxxxxxxx..............................................................................xxxxxxxxxxxxxx",
	"xxxxxxxxxx.................................................................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.................................................................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.................................................................xxxxxxxxxxxxxxxxxxxxxxxxx",
	"xxxxxxxxxxxxxx.................................................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.................................................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx.................................................xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
	"XXXXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxx........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXXXXXXXXXXXXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxx........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXXXXXXXXXXXXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxx........xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXXXXXXXX",
	"XXXXXXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXXXXXXXXXXXXXXXXXXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXXXXXXXXXXXXXXXXXXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXXXXXXXXXXXX",
	"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    };

	int start_row = 24;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 300; j++) {
			background[start_row + i][j] = art[i][j];
		}
	}
	static int index = 0;
	int next_start_row = start_row + 1;
	if (next_start_row + 15 > 40) {
		next_start_row = 0;
	}

	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	wattron(this->_board, COLOR_PAIR(4));
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			int wrapped_col = (j + index) % 300;
			this->addAt(i, j, background[i][wrapped_col]);
		}
	}
	wattroff(this->_board, COLOR_PAIR(4));
	index++;
	
	this->addBorder();
	
	//Create Upper and Lower Layer
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	wattron(this->_board, COLOR_PAIR(3));
	for (size_t i = 0; i < LENGTH; ++i) {
		this->addAt(0, i, ' ');
		this->addAt(HEIGHT - 1, i, ' ');
	}
	wattroff(this->_board, COLOR_PAIR(3));
	
}
