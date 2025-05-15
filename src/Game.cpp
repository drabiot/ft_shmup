/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:10 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 20:25:58 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

static str intToStr(int value);
//static str doubleToStr(double value);

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

chtype	Game::getInput( void ) {
	noecho();
	curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(this->_board, TRUE);
	cbreak();
	
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
		case 'p':
			this->_gameOver = true;
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
	init_pair(2, COLOR_BLACK, COLOR_CYAN);
	wattron(this->_board, A_BOLD);
	this->displayPlayer();
	wattroff(this->_board, A_BOLD);

	this->refreshBorder();
}

void	Game::createBackground( void ) {
	wattroff(this->_board, COLOR_PAIR(3));

	static char backgroundBase[HEIGHT][WIDTH];
	static char backgroundDetail[HEIGHT][WIDTH];
	static char backgroundFine[HEIGHT][WIDTH];
	static char backgroundFirst[HEIGHT][WIDTH];
	static bool initialized = false;
	static int	index = 0;


	static int	indexAddBase = 0;
	static int	indexAddDetail = 0;
	static int	indexAddFine = 0;

	static int	indexBase = 0;
	static int	indexDetail = 0;
	static int	indexFine = 0;

	//Randomly Generate Background
	if (!initialized) {
		double baseFreq   = (2.0 * M_PI) / 300;
		double detailFreq = (2.0 * M_PI) / 150;
		double fineFreq   = (2.0 * M_PI) / 100;
		double firstFreq   = (2.0 * M_PI) / 50;

		double baseAmp = HEIGHT / 5;
		double detailAmp = HEIGHT / 10;
		double fineAmp = HEIGHT / 20;
		double firstAmp = HEIGHT / 30;


		double offset = HEIGHT / 2.0;

		for (int x = 0; x < WIDTH; ++x) {
			
			double base = static_cast<int>(ft_sin(x * baseFreq) * baseAmp + offset * 2.0) - 25;
			double detail = static_cast<int>(ft_sin(x * detailFreq) * detailAmp + offset * 2.0) - 20;
			double fine = static_cast<int>(ft_sin(x * fineFreq) * fineAmp + offset * 2.0) - 15;
			double first = static_cast<int>(ft_sin(x * firstFreq) * firstAmp + offset * 2.0) - 7;

			for (int y = 0; y < HEIGHT; ++y) {
				if (y < base)
					backgroundBase[y][x] = SPACE;
				else
					backgroundBase[y][x] = BASE;
				if (y < detail)
					backgroundDetail[y][x] = SPACE;
				else
					backgroundDetail[y][x] = DETAIL;
				if (y < fine)
					backgroundFine[y][x] = SPACE;
				else
					backgroundFine[y][x] = FINE;
				if (y < first)
					backgroundFirst[y][x] = SPACE;
				else
					backgroundFirst[y][x] = FIRST;
			}
		}
		initialized = true;
	}

	//Scroll Background
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);

		
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			int wrapped_col = (j + indexBase) % WIDTH;
				wattron(this->_board, COLOR_PAIR(5));
				this->addAt(i, j, backgroundBase[i][wrapped_col]);
				wattroff(this->_board, COLOR_PAIR(5));
		}
	}
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			int wrapped_col = (j + indexDetail) % WIDTH;
				wattron(this->_board, COLOR_PAIR(5));
				if (backgroundDetail[i][wrapped_col] != SPACE)
					this->addAt(i, j, backgroundDetail[i][wrapped_col]);
				wattroff(this->_board, COLOR_PAIR(5));
		}
	}
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			int wrapped_col = (j + indexFine) % WIDTH;
				wattron(this->_board, COLOR_PAIR(4));
				if (backgroundFine[i][wrapped_col] != SPACE)
					this->addAt(i, j, backgroundFine[i][wrapped_col]);
				wattroff(this->_board, COLOR_PAIR(4));
		}
	}
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			int wrapped_col = (j + index) % WIDTH;
				wattron(this->_board, COLOR_PAIR(4));
				if (backgroundFirst[i][wrapped_col] != SPACE)
					this->addAt(i, j, backgroundFirst[i][wrapped_col]);
				wattroff(this->_board, COLOR_PAIR(4));
		}
	}
	index++;
	indexAddBase++;
	indexAddDetail++;
	indexAddFine++;
	if (indexAddBase % 15 == 0)
		indexBase++;
	if (indexAddDetail % 7 == 0)
		indexDetail++;
	if (indexAddFine % 3 == 0)
		indexFine++;

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

void	Game::displayPlayer( void ) {
	mvwprintw(this->_board, this->_player.getPosY(), this->_player.getPosX(), "🛸");
}

void	Game::displayEnd( void ) {
	this->clearBorder();
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
				this->addAt(i, j, ' ');
		}
	}
	this->addBorder();
	wattron(this->_board, A_BOLD);

	mvwprintw(this->_board, HEIGHT / 2 - 10, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 9, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁");
	mvwprintw(this->_board, HEIGHT / 2 - 8, LENGTH / 2 - 20, "⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁  ");
	mvwprintw(this->_board, HEIGHT / 2 - 7, LENGTH / 2 - 20, "⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 6, LENGTH / 2 - 20, "⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 5, LENGTH / 2 - 20, "⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀  ");
	mvwprintw(this->_board, HEIGHT / 2 - 4, LENGTH / 2 - 20, "⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ");
	mvwprintw(this->_board, HEIGHT / 2 - 3, LENGTH / 2 - 20, "⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 2, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆");
	mvwprintw(this->_board, HEIGHT / 2 - 1, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 0, LENGTH / 2 - 20, "⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 1, LENGTH / 2 - 20, "⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 2, LENGTH / 2 - 20, "⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 3, LENGTH / 2 - 20, "⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 4, LENGTH / 2 - 20, "⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");

	wattron(this->_board, A_BLINK);
	mvwprintw(this->_board, HEIGHT / 2 + 6, LENGTH / 2 - 10, "Press any Key to Quit!");
	wattroff(this->_board, A_BLINK);

	mvwprintw(this->_board, HEIGHT / 2 + 10, LENGTH / 2 - 20, "Score:");
	mvwprintw(this->_board, HEIGHT / 2 + 10, LENGTH / 2 + 14, "Time:");

	wattroff(this->_board, A_BOLD);
	
	const str	scoreDisplay = intToStr(this->_player.getScore());
	int			padding = scoreDisplay.size();
	if (padding % 2 != 0)
		padding++;
	mvwprintw(this->_board, HEIGHT / 2 + 11, LENGTH / 2 - 20 + 3 - (padding / 2), "%s", scoreDisplay.c_str());

	//double	endTime = static_cast<double>(this->_player.getTimeSurvived() - std::clock()) / CLOCKS_PER_SEC;
	//const str	timeDisplay = doubleToStr(endTime);
	//padding = timeDisplay.size();
	//if (padding % 2 != 0)
	//	padding++;
	//mvwprintw(this->_board, HEIGHT / 2 + 11, LENGTH / 2 + 14 + 3 - (padding / 2), "%s", scoreDisplay.c_str());

	this->refreshBorder();
	doupdate();
}

static str intToStr(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

/*static str doubleToStr(double value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}*/
