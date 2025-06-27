/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:37:44 by tchartie          #+#    #+#             */
/*   Updated: 2025/06/27 18:50:51 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_HPP
# define WALL_HPP

# include "Entity.hpp"

class	Wall : public Entity {
	public:
		Wall( size_t x, size_t y );
		~Wall( void );

        void    moveWall( void );
};

#endif //WALL_HPP
