/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:21 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 14:09:59 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

# include "utils.hpp"

class Entity {
	public:
		Entity( void );
		virtual ~Entity( void );

		size_t	getPosX( void );
		size_t	getPosY( void );
		size_t	getLife( void );

		void	setPosX( size_t newX );
		void	setPosY( size_t newY );
		void	setLife( size_t newLife );
	protected:
		size_t	_posX;
		size_t	_posY;
		size_t	_life;
};

#endif //ENTITY_HPP

