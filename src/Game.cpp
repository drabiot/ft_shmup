/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:10 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 15:37:03 by tchartie         ###   ########.fr       */
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

	static char background[HEIGHT][WIDTH];
	static bool initialized = false;
	static int index = 0;

	//Randomly Generate Background
	if (!initialized) {
		double baseFreq   = (2.0 * M_PI) / 300;
		double detailFreq = (2.0 * M_PI) / 150;
		double fineFreq   = (2.0 * M_PI) / 100;
		double firstFreq   = (2.0 * M_PI) / 50;

		double baseAmp    = HEIGHT / (std::rand() % 10 + 1);
		if (baseAmp < 5)
			baseAmp = 5;
		double detailAmp  = HEIGHT / (std::rand() % 15 + 1);
		if (detailAmp < 10)
			detailAmp = 10;
		double fineAmp    = HEIGHT / (std::rand() % 30 + 1);
		if (fineAmp > 20)
			fineAmp = 20;
		double firstAmp    = HEIGHT / (std::rand() % 45 + 1);
		if (firstAmp > 30)
			firstAmp = 30;


		double offset = HEIGHT / 2.0;

		for (int x = 0; x < WIDTH; ++x) {
			
			double base = static_cast<int>(ft_sin(x * baseFreq) * baseAmp + offset * 2.0) - 25;
			double detail = static_cast<int>(ft_sin(x * detailFreq) * detailAmp + offset * 2.0) - 20;
			double fine = static_cast<int>(ft_sin(x * fineFreq) * fineAmp + offset * 2.0) - 15;
			double first = static_cast<int>(ft_sin(x * firstFreq) * firstAmp + offset * 2.0) - 7;

			for (int y = 0; y < HEIGHT; ++y) {
				if (y < base)
					background[y][x] = ' ';
				else
					background[y][x] = '.';
				if (y >= detail)
					background[y][x] = '%';
				if (y >= fine)
					background[y][x] = 'X';
				if (y >= first)
					background[y][x] = '@';
			}
		}
		initialized = true;
	}

	//Scroll Background
	if (index % 1 == 0) {
		init_pair(4, COLOR_GREEN, COLOR_BLACK);
		wattron(this->_board, COLOR_PAIR(4));
		for (int i = 0; i < HEIGHT; ++i) {
			for (int j = 0; j < LENGTH; ++j) {
				int wrapped_col = (j + index) % WIDTH;
				this->addAt(i, j, background[i][wrapped_col]);
			}
		}
		wattroff(this->_board, COLOR_PAIR(4));
	}
	index++;

	//Create Upper & Lower Border
	this->addBorder();
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	wattron(this->_board, COLOR_PAIR(3));
	for (size_t i = 0; i < LENGTH; ++i) {
		this->addAt(0, i, ' ');
		this->addAt(HEIGHT - 1, i, ' ');
	}
	wattroff(this->_board, COLOR_PAIR(3));
}