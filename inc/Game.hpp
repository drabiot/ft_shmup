/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:19 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 00:10:57 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <iostream>
# include <string>
# include <ncurses.h>

# include "color.hpp"

# define AND	<<
# define PRINT	std::cout AND
# define ERROR	std::cerr AND
# define NLINE	PRINT std::endl
# define ENDL	AND std::endl
# define CENDL	AND BASE_COLOR ENDL
# define TAB	"\t"

typedef std::string str;

# define cref(type) const type &
# define ref(type) type &

# define HEIGHT	40
# define LENGTH (40 + 20) * 2.5

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
		WINDOW *_board;
		bool	_gameOver;

		void	addBorder( void );
		void	clearBorder( void );
};

#endif //GAME_HPP

