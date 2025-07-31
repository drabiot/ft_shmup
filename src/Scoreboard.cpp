/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:08:59 by tchartie          #+#    #+#             */
/*   Updated: 2025/07/31 18:29:56 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scoreboard.hpp"

static str intToStr(int value);
static str	createTimerFormat(int value);

Scoreboard::Scoreboard( void ) {
	size_t	xMax;
	size_t	yMax;

	getmaxyx(stdscr, yMax, xMax);
	this->_scoreboard = newwin(4, LENGTH, (yMax / 2) - (HEIGHT / 2) + HEIGHT, (xMax / 2) - (LENGTH / 2));
	this->_emoji = false;
	if (!this->_scoreboard)
		throw std::runtime_error("Can't initialize Scoreboard window");
}

Scoreboard::Scoreboard( bool emoji ) {
	size_t	xMax;
	size_t	yMax;

	getmaxyx(stdscr, yMax, xMax);
	this->_scoreboard = newwin(4, LENGTH, (yMax / 2) - (HEIGHT / 2) + HEIGHT, (xMax / 2) - (LENGTH / 2));
	this->_emoji = emoji;
	if (!this->_scoreboard)
		throw std::runtime_error("Can't initialize Scoreboard window");
}

Scoreboard::Scoreboard( cref(Scoreboard) src ) {
	*this = src;
}

Scoreboard &Scoreboard::operator = ( cref(Scoreboard) rhs ) {
	if (this == &rhs)
		return (*this);
	this->_scoreboard = rhs._scoreboard;
	return (*this);
}

Scoreboard::~Scoreboard( void ) {
	if (this->_scoreboard)
		delwin(this->_scoreboard);
}

WINDOW	*Scoreboard::getWindow( void ) {
	return (this->_scoreboard);
}

void	Scoreboard::initialize( void ) {
	this->clearScoreboard();
	this->refreshScoreboard();
}

void	Scoreboard::addBorder( void ) {
	box(this->_scoreboard, 0, 0);
}

void	Scoreboard::updateScoreboard( Player *player ) {
	this->clearScoreboard();
	
	//Create Layout P1
	wattron(this->_scoreboard, COLOR_PAIR(PLAYER_1));
	mvwprintw(this->_scoreboard, 1, 1, "P1");
	wattroff(this->_scoreboard, COLOR_PAIR(PLAYER_1));

	//Create Health Bar
	mvwprintw(this->_scoreboard, 1, 6, "Life:");
	size_t	i = 0;
	size_t	padding = 12;
	for (; i < player->getMaxLife(); ++i) {
		if (this->_emoji) {
			if (i < player->getLife())
				mvwprintw(this->_scoreboard, 1, i + padding, "❤️");
			else
				mvwprintw(this->_scoreboard, 1, i + padding, "🖤");
		}
		else {
			if (i < player->getLife()) {
				wattron(this->_scoreboard, COLOR_PAIR(HEALTH));
				mvwprintw(this->_scoreboard, 1, i + padding, "<3");
				wattroff(this->_scoreboard, COLOR_PAIR(HEALTH));
			}
			else
				mvwprintw(this->_scoreboard, 1, i + padding, "<3");
		}
		padding += 2;
	}

	//Create Laser
	mvwprintw(this->_scoreboard, 1, 26, "Laser:");
	wattron(this->_scoreboard, A_REVERSE);

	for (float i = 0; i < 20; ++i) {
		if (i < static_cast<float>(player->getPower()) * 4) {
			wattron(this->_scoreboard, COLOR_PAIR(PLAYER_1));
			mvwprintw(this->_scoreboard, 1, 33 + i, " ");
			wattroff(this->_scoreboard, COLOR_PAIR(PLAYER_1));
		}
		else {
			mvwprintw(this->_scoreboard, 1, 33 + i, " ");
		}
	}
	wattroff(this->_scoreboard, A_REVERSE);
	//Create Score
	mvwprintw(this->_scoreboard, 2, 26, "Score:");
	wattron(this->_scoreboard, COLOR_PAIR(PLAYER_1));
    const str	scoreDisplay = intToStr(player->getScore());
	mvwprintw(this->_scoreboard, 2, 33, "%s", scoreDisplay.c_str());
	wattroff(this->_scoreboard, COLOR_PAIR(PLAYER_1));

	//Create Timer
	mvwprintw(this->_scoreboard, 2, 6, "Time:");
	wattron(this->_scoreboard, COLOR_PAIR(PLAYER_1));
    const str	timeDisplay = createTimerFormat(player->getTimer());
	mvwprintw(this->_scoreboard, 2, 12, "%s", timeDisplay.c_str());
	wattroff(this->_scoreboard, COLOR_PAIR(PLAYER_1));
	
	this->refreshScoreboard();
}

void	Scoreboard::clearScoreboard( void ) {
	wnoutrefresh(this->_scoreboard);
	this->addBorder();
}

void	Scoreboard::refreshScoreboard( void ) {
	wrefresh(this->_scoreboard);
}

void	Scoreboard::endScreen( void ) {
	this->clearScoreboard();
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
				mvwaddch(this->_scoreboard, i, j, ' ');
		}
	}
	this->addBorder();
	this->refreshScoreboard();
	doupdate();
}

static str intToStr(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

static str	createTimerFormat(int value) {
	int	sec = value % 60;
	int	min = (value / 60) % 60;
	int hour = value / 3600;

    std::ostringstream oss;

    oss << std::setw(2) << std::setfill('0') << hour << ":"
		<< std::setw(2) << std::setfill('0') << min << ":"
        << std::setw(2) << std::setfill('0') << sec;

    return oss.str();
}
