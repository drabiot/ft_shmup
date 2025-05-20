/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:19 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/20 23:41:40 by tchartie         ###   ########.fr       */
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

		bool	isGameOver( void );
		Player	getPlayer( void );
		WINDOW	*getWindow( void );

		chtype	getInput( void );
		void	processInput( void );
		void	updateGame( void );
		void	endScreen( void );

		void	displayBackground( void );
		void	displayPlayer( void );
		void    displayEnd( void );
	private:
		WINDOW		*_board;
		bool		_gameOver;
		Player		_player;

		void	addBorder( void );
		void	clearBorder( void );
};

//const str   *selectBackground( int type );

#endif //GAME_HPP

