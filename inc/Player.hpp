/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:15 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/20 22:53:55 by tchartie         ###   ########.fr       */
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
		unsigned long long	getTimeSurvived( void );

		void			updateScore( void );
		void			updateTime( void );
	private:
		size_t				_score;
		unsigned long long	_timeSurvived;
};

#endif //PLAYER_HPP

