/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:15 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 00:55:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Entity.hpp"

class	Player : public Entity{
	public:
		Player( void );
		~Player( void );

		size_t	getScore( void );
		size_t	getTimeSurvived( void );

		void	updateScore( void );
		void	updateTimeSurvived( void );
	private:
		size_t	_score;
		size_t	_timeSurvived;
};

#endif //PLAYER_HPP

