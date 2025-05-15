/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:32:51 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 19:14:14 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Scoreboard.hpp"

int	main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	noecho();
	curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
	cbreak();
	setlocale(LC_ALL, "");
	
	std::srand(std::time(0));

	try {
		Game		game;
		Scoreboard	scoreboard;

		game.initializeBorder();
		scoreboard.initialize();

		while (!game.isGameOver()) {
			game.processInput();
			game.updateGame();
			game.refreshBorder();
			scoreboard.refreshScoreboard();
			doupdate();

			usleep(FRAME_DELAY);
		}
	
	//End Menu with total Score & Time Survivec
	game.displayEnd();
	getch();

	} catch (const std::exception& e) {
		endwin();
    	ERROR RED AND e.what() CENDL;
	}

	return (0);
}