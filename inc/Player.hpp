/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:15 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/21 21:33:37 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Entity.hpp"

class	Player : public Entity{
	public:
		Player( void );
		~Player( void );

		size_t				getScore( void );
		unsigned long long	getTimeSurvived( void );
		size_t				getTimer( void );
		size_t				getPower( void );

		void				setScore( size_t value );
		void				updateTime( void );
		void				updateTimer( void );
		void				updatePower( void );
	private:
		size_t				_score;
		unsigned long long	_timeSurvived;
		size_t				_timer;
		size_t				_power;
};

#endif //PLAYER_HPP

