/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:10 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/20 20:56:26 by tchartie         ###   ########.fr       */
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
	if (!this->_board)
		throw std::runtime_error("Can't initialize Game window");

	this->_gameOver = false;
}

Game::~Game( void ) {
	//End the Game Screen
	if (this->_board)
		delwin(this->_board);
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

bool	Game::isGameOver( void ) {
	return (this->_gameOver);
}

chtype	Game::getInput( void ) {
	noecho();
	curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(this->_board, TRUE);
	cbreak();
	
	return (wgetch(this->_board));
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
		case 'p':
			this->_gameOver = true;
			break;
		default:
			break;
	}
}

void	Game::updateGame( void ) {
	this->clearBorder();
	wattroff(this->_board, COLOR_PAIR(3));
	
	//Create & Display Background
	this->displayBackground();

	//Create & Display Foreground

	//Display Enemies

	//Display Player
	init_pair(2, COLOR_BLACK, COLOR_CYAN);
	wattron(this->_board, A_BOLD);
	this->displayPlayer();
	wattroff(this->_board, A_BOLD);

	this->refreshBorder();
}

void	Game::endScreen( void ) {
	this->clearBorder();
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
				this->addAt(i, j, ' ');
		}
	}
	this->addBorder();
	this->displayEnd();
	this->refreshBorder();
	doupdate();
}
