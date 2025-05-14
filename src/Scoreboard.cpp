/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:08:59 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 14:41:22 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scoreboard.hpp"

Scoreboard::Scoreboard( void ) {
	size_t	xMax;
	size_t	yMax;

	getmaxyx(stdscr, yMax, xMax);
	this->_scoreboard = newwin(4, LENGTH, (yMax / 2) - (HEIGHT / 2) + HEIGHT, (xMax / 2) - (LENGTH / 2));
}

Scoreboard::Scoreboard( cref(Scoreboard) src ) {
	*this = src;
}

Scoreboard &Scoreboard::operator = ( cref(Scoreboard) rhs ) {
	if (this == &rhs)
		return (*this);
	this->_scoreboard = rhs._scoreboard;
	this->_player = rhs._player;
	return (*this);
}

Scoreboard::~Scoreboard( void ) {}

void	Scoreboard::initialize( void ) {
	this->clearScoreboard();
	this->updateScoreboard();
	this->refreshScoreboard();
}

void	Scoreboard::addBorder( void ) {
	box(this->_scoreboard, 0, 0);
}

void	Scoreboard::updateScoreboard( void ) {
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	mvwprintw(this->_scoreboard, 1, 3, "Life:");
	size_t	i = 0;
	size_t	padding = 1;
	for (; i < this->_player.getLife(); ++i) {
		wattron(this->_scoreboard, COLOR_PAIR(1));
		mvwprintw(this->_scoreboard, 2, i + padding, "<3");
		padding += 2;
		wattroff(this->_scoreboard, COLOR_PAIR(1));
	}
}

void	Scoreboard::clearScoreboard( void ) {
	wclear(this->_scoreboard);
	this->addBorder();
}

void	Scoreboard::refreshScoreboard( void ) {
	wrefresh(this->_scoreboard);
}

