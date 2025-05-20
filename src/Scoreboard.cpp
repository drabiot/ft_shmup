/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:08:59 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/20 23:53:16 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scoreboard.hpp"

static str intToStr(int value);

Scoreboard::Scoreboard( void ) {
	size_t	xMax;
	size_t	yMax;

	getmaxyx(stdscr, yMax, xMax);
	this->_scoreboard = newwin(4, LENGTH, (yMax / 2) - (HEIGHT / 2) + HEIGHT, (xMax / 2) - (LENGTH / 2));
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
	Player player;
	this->clearScoreboard();
	//this->updateScoreboard(player);
	this->refreshScoreboard();
}

void	Scoreboard::addBorder( void ) {
	box(this->_scoreboard, 0, 0);
}

void	Scoreboard::updateScoreboard( Player player ) {
	this->clearScoreboard();
	
	//Create Health Bar
	init_pair(1, COLOR_RED, COLOR_BLACK);
	mvwprintw(this->_scoreboard, 1, 12, "Life:");
	size_t	i = 0;
	size_t	padding = 10;
	for (; i < player.getLife(); ++i) {
		wattron(this->_scoreboard, COLOR_PAIR(1));
		mvwprintw(this->_scoreboard, 2, i + padding, "❤️");
		padding += 2;
		wattroff(this->_scoreboard, COLOR_PAIR(1));
	}
	for (; i < player.getMaxLife(); ++i) {
		wattron(this->_scoreboard, COLOR_PAIR(1));
		mvwprintw(this->_scoreboard, 2, i + padding, "🖤");
		padding += 2;
		wattroff(this->_scoreboard, COLOR_PAIR(1));
	}

	//Create Score
	mvwprintw(this->_scoreboard, 1, 50, "Score:");

    const str	scoreDisplay = intToStr(player.getScore());
	padding = scoreDisplay.size();
	if (padding % 2 != 0)
		padding++;
	mvwprintw(this->_scoreboard, 2,   3 + 50 - (padding / 2), "%s", scoreDisplay.c_str());

	//Create Timer
	mvwprintw(this->_scoreboard, 1, 80, "Timer:");

    const str	TimeDisplay = intToStr(player.getTimeSurvived());
	padding = TimeDisplay.size();
	if (padding % 2 != 0)
		padding++;
	mvwprintw(this->_scoreboard, 2,   3 + 80 - (padding / 2), "%s", TimeDisplay.c_str());
	
	//doupdate();
	this->refreshScoreboard();
}

void	Scoreboard::clearScoreboard( void ) {
	//werase(this->_scoreboard);
	wnoutrefresh(this->_scoreboard);
	this->addBorder();
}

void	Scoreboard::refreshScoreboard( void ) {
	wrefresh(this->_scoreboard);
}

static str intToStr(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}
