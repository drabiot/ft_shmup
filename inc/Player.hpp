/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:15 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 20:15:38 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Entity.hpp"

class	Player : public Entity{
	public:
		Player( void );
		~Player( void );

		size_t			getScore( void );
		std::clock_t	getTimeSurvived( void );

		void			updateScore( void );
	private:
		size_t			_score;
		std::clock_t	_timeSurvived;
};

#endif //PLAYER_HPP

