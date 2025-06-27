/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:38:44 by tchartie          #+#    #+#             */
/*   Updated: 2025/06/27 18:50:57 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Wall.hpp"

Wall::Wall( size_t x, size_t y ) {
    this->_posX = x;
	this->_posY = y;
	this->_life = -1;
	this->_maxLife = -1;
}

Wall::~Wall( void ) {}

void    Wall::moveWall( void ) {
    if (this->_posX - 1 >= 0)
        this->_posX -= 1;
}
