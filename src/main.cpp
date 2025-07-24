/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:32:51 by tchartie          #+#    #+#             */
/*   Updated: 2025/07/24 15:13:54 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Scoreboard.hpp"

int	main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	//Init Utils
	noecho();
	curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
	cbreak();
	setlocale(LC_ALL, "");
	mousemask(BUTTON1_CLICKED | BUTTON3_CLICKED, NULL);

	std::srand(std::time(0));

	try {
		Game		game;

		game.initializeBorder();

		while (!game.isStarted()) {
			game.introGame();
		}
		Scoreboard	scoreboard(game.getEmoji());
		scoreboard.initialize();
		
		game.refreshBorder();
		wnoutrefresh(game.getWindow());
		wnoutrefresh(scoreboard.getWindow());
		doupdate();
		//for (size_t i = 0; i < 4; ++i) {
		//	game.addDirection(i);
		//}
		while (!game.isGameOver()) {
			game.processInput();
			game.updateGame();
			scoreboard.updateScoreboard(game.getPlayer());
			game.refreshBorder();
			scoreboard.refreshScoreboard();

			wnoutrefresh(game.getWindow());
			wnoutrefresh(scoreboard.getWindow());
			doupdate();

			usleep(FRAME_DELAY);
		}
	
	//End Menu with total Score & Time Survivec
	game.endScreen();
	scoreboard.endScreen();
	getch();

	} catch (const std::exception& e) {
		endwin();
    	ERROR RED AND e.what() CENDL;
	}

	return (0);
}