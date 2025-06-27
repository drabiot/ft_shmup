/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:19 by tchartie          #+#    #+#             */
/*   Updated: 2025/06/27 19:01:49 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Scoreboard.hpp"
# include "Projectile.hpp"
# include "Wall.hpp"

class Game {
	public:
		Game( void );
		~Game( void );

		void	initializeBorder( void );
		void	refreshBorder( void );
		void	addAt( int y, int x, chtype ch);

		bool	isStarted( void );
		bool	isGameOver( void );

		Player	*getPlayer( void );
		WINDOW	*getWindow( void );
		bool	getEmoji( void );

		void	addDirection( int type );

		chtype	getInput( void );
		void	processInput( void );
		void	introGame( void );
		void	updateGame( void );
		void	endScreen( void );

		void	displayBackground( void );
		void	displayPlayer( void );
		void	displayObstacle( void );
		void    displayEnd( void );

		void	checkColision( void );

		void	addRocket( Projectile newRocket );
		void	removeRocket( Projectile oldRocket );
		void	updateRocket( void );
		void	displayRocket( void );
	private:
		bool					_emoji;
		WINDOW					*_board;
		bool					_start;
		bool					_gameOver;
		Player					_player;

		std::vector<Projectile>	_rocket;
		std::vector<Wall>		_obstacle;

		chtype					_up;
		chtype					_down;
		chtype					_left;
		chtype					_right;

		void	addBorder( void );
		void	clearBorder( void );
};

//const str   *selectBackground( int type );

#endif //GAME_HPP

