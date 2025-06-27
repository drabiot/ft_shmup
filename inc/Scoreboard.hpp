/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scoreboard.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:05:21 by tchartie          #+#    #+#             */
/*   Updated: 2025/06/25 22:55:53 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOREBOARD_HPP
# define SCOREBOARD_HPP

# include "Player.hpp"

class Scoreboard {
	public:
		Scoreboard( void );
		Scoreboard( bool emoji );
		Scoreboard( cref(Scoreboard) src );
		Scoreboard &operator = ( cref(Scoreboard) rhs );
		~Scoreboard( void );

		WINDOW	*getWindow( void );
		
		void	initialize( void );
		void	addBorder( void );
		void	updateScoreboard( Player *player );
		void	clearScoreboard( void );
		void	refreshScoreboard( void );
		void	endScreen( void );
	private:
		WINDOW	*_scoreboard;
		bool	_emoji;
};

#endif //SCOREBOARD_HPP
