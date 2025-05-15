/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 22:32:51 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 13:58:36 by tchartie         ###   ########.fr       */
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
	
	std::srand(std::time(0));

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

	getch();

	return (0);
}