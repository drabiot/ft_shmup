/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:19 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 01:37:39 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Scoreboard.hpp"

class Game {
	public:
		Game( void );
		~Game( void );

		void	initializeBorder( void );
		void	refreshBorder( void );
		void	addAt( int y, int x, chtype ch);

		chtype	getInput( void );
		bool	isGameOver( void );

		void	processInput( void );
		void	updateGame( void );
	private:
		WINDOW		*_board;
		bool		_gameOver;
		//Scoreboard	_scoreboard;

		void	addBorder( void );
		void	clearBorder( void );
};

#endif //GAME_HPP

