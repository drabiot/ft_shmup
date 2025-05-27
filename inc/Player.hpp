/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:15 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/27 17:58:48 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include "Entity.hpp"
# include "Projectile.hpp"

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
		void				rebootPower( void );

		void				getPendingRocket( std::vector<Projectile> &out );
		void				attack( void );
	private:
		size_t					_score;
		unsigned long long		_timeSurvived;
		size_t					_timer;
		size_t					_power;
		std::vector<Projectile> _pendingRocket;
};

#endif //PLAYER_HPP

