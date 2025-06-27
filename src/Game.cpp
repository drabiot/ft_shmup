/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:10 by tchartie          #+#    #+#             */
/*   Updated: 2025/06/27 19:30:13 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game( void ) {
	size_t	xMax;
	size_t	yMax;

	//Init Game Screen
	initscr();

	//Init Colors
	if (!has_colors())
		throw std::runtime_error("Can't initialize Colors");
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);		//Foreground
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//Far Background Night
    init_pair(3, COLOR_GREEN, COLOR_BLACK);		//Midground Night
	init_pair(4, COLOR_CYAN, COLOR_BLACK);		//Player 1
	init_pair(6, COLOR_RED, COLOR_BLACK);		//Health

	//Create & Init Playing Board
	refresh();
	getmaxyx(stdscr, yMax, xMax);
	this->_board = newwin(HEIGHT, LENGTH, (yMax / 2) - (HEIGHT / 2), (xMax / 2) - (LENGTH / 2));
	if (!this->_board)
		throw std::runtime_error("Can't initialize Game window");

	this->_start = false;
	this->_gameOver = false;

	this->_up = 0;
	this->_down = 0;
	this->_left = 0;
	this->_right = 0;

	for (size_t i = 0; i < HEIGHT; ++i) {
		if (1 + std::rand() % HEIGHT - 2 != (int)i)
			this->_obstacle.push_back(Wall(100, (int)i));
		if (1 + std::rand() % HEIGHT - 2 != (int)i)
			this->_obstacle.push_back(Wall(200, (int)i));
		if ( 1 + std::rand() % HEIGHT - 2 != (int)i)
			this->_obstacle.push_back(Wall(300, (int)i));
	}

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

bool	Game::isStarted( void ) {
	return (this->_start);
}

bool	Game::isGameOver( void ) {
	return (this->_gameOver);
}

Player	*Game::getPlayer( void ) {
	return &(this->_player);
}

WINDOW	*Game::getWindow( void ) {
	return (this->_board);
}

bool	Game::getEmoji( void ) {
	return (this->_emoji);
}

void	Game::introGame( void ) {
	this->clearBorder();

	wattron(this->_board, COLOR_PAIR(4));
	mvwprintw(this->_board, HEIGHT / 2 - 10, LENGTH / 2 - 24 , "   _    _      _                               ");
	mvwprintw(this->_board, HEIGHT / 2 - 9, LENGTH / 2 - 24 , "  | |  | |    | |                              ");
	mvwprintw(this->_board, HEIGHT / 2 - 8, LENGTH / 2 - 24 , "  | |  | | ___| | ___ ___  _ __ ___   ___      ");
	mvwprintw(this->_board, HEIGHT / 2 - 7, LENGTH / 2 - 24 , "  | |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\     ");
	mvwprintw(this->_board, HEIGHT / 2 - 6, LENGTH / 2 - 24 , "  \\  /\\  /  __/ | (_| (_) | | | | | |  __/     ");
	mvwprintw(this->_board, HEIGHT / 2 - 5, LENGTH / 2 - 24 , "   \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|     ");
	mvwprintw(this->_board, HEIGHT / 2 - 4, LENGTH / 2 - 24 , "  __ _         _     _                        ");
	mvwprintw(this->_board, HEIGHT / 2 - 3, LENGTH / 2 - 24 , " / _| |       | |   | |                        ");
	mvwprintw(this->_board, HEIGHT / 2 - 2, LENGTH / 2 - 24 , "| |_| |_   ___| |__ | |_ _ __ ___  _   _ _ __  ");
	mvwprintw(this->_board, HEIGHT / 2 - 1, LENGTH / 2 - 24 , "|  _| __| / __| '_ \\| __| '_ ` _ \\| | | | '_ \\ ");
	mvwprintw(this->_board, HEIGHT / 2 + 0, LENGTH / 2 - 24 , "| | | |_  \\__ \\ | | | |_| | | | | | |_| | |_) |");
	mvwprintw(this->_board, HEIGHT / 2 + 1, LENGTH / 2 - 24 , "|_|  \\__| |___/_| |_|\\__|_| |_| |_|\\__,_| .__/ ");
	mvwprintw(this->_board, HEIGHT / 2 + 2, LENGTH / 2 - 24 , "      ______                            | |    ");
	mvwprintw(this->_board, HEIGHT / 2 + 3, LENGTH / 2 - 24 , "     |______|                           |_|    ");
	wattroff(this->_board, COLOR_PAIR(4));

	mvwprintw(this->_board, HEIGHT / 2 + 7, LENGTH / 2 - 40, "Press 1: for Emojies");
	mvwprintw(this->_board, HEIGHT / 2 + 7, LENGTH / 2 + 20, "Press 2: for ASCII");

	wattron(this->_board, A_BLINK);
	mvwprintw(this->_board, HEIGHT / 2 + 12, LENGTH / 2 - 22, "*If this text don't blink select ASCII mode*");
	wattroff(this->_board, A_BLINK);

	chtype	input = this->getInput();
	switch (input) {
		case '1':
			this->_emoji = true;
			this->_start = true;
			break;
		case '2':
			this->_emoji = false;
			this->_start = true;
			break;
		default:
			break;
	}

	this->refreshBorder();
}

void	Game::addDirection( int type ) {
	chtype	input = wgetch(this->_board);
	while (input != this->_up && input != this->_down && input != this->_left && input != this->_right) {
		input = wgetch(this->_board);
	}
	switch (type) {
		case 0:
			this->_up = input;
			break;
		case 1:
			this->_down = input;
			break;
		case 2:
			this->_left = input;
			break;
		case 3:
			this->_right = input;
			break;
		default:
			break;
	}
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
	static unsigned int	attackSpeed = 0;
	attackSpeed++;

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
		case ' ':
			if (attackSpeed > 5) {
				this->_player.attack();
				attackSpeed = 0;
			}
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
	
	//Create & Display Background
	this->displayBackground();

	//Display Foreground
	this->displayObstacle();
	for (size_t i = 0; i < this->_obstacle.size(); ++i) {
		this->_obstacle[i].moveWall();
	}

	//Display Enemies

	//Display Player & Check colisions
	wattron(this->_board, A_BOLD);
	this->displayPlayer();
	wattroff(this->_board, A_BOLD);
	this->checkColision();

	//Display & Update Projectile
	this->updateRocket();
	wattron(this->_board, A_BOLD);
	this->displayRocket();
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

void	Game::addRocket( Projectile newRocket ) {
	this->_rocket.push_back(newRocket);
}

void	Game::removeRocket( Projectile oldRocket ) {
	(void)oldRocket;
}

void	Game::updateRocket( void ) {
	this->_player.getPendingRocket(this->_rocket);
	for (size_t i = 0; i < this->_rocket.size(); ++i) {
    	this->_rocket[i].setPosX(this->_rocket[i].getPosX() + 1);
	}
}

void	Game::checkColision( void ) {
	if (this->_player.getLife() == 0) {
		this->_gameOver = true;
		return ;
	}

	size_t x = this->_player.getPosX();
	size_t y = this->_player.getPosY();

	for (size_t i = 0; i < this->_obstacle.size(); ++i) {
		if (x == this->_obstacle[i].getPosX() && y == this->_obstacle[i].getPosY()) {
			this->_player.setLife(this->_player.getLife() - 1);
			//go behind the end of the wall
			return ;
		}
	}
}
