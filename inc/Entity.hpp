/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:21 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/01 16:25:00 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "utils.hpp"

class Entity {
	public:
		Entity( void );
		virtual ~Entity( void );

		int		getPosX( void );
		int		getPosY( void );
		size_t	getLife( void );
		size_t	getMaxLife( void );

		void	setPosX( int newX );
		void	setPosY( int newY );
		void	setLife( size_t newLife );
		void	setMaxLife( size_t newMaxLife );
	protected:
		int		_posX;
		int		_posY;
		size_t	_life;
		size_t	_maxLife;
};

#endif //ENTITY_HPP

