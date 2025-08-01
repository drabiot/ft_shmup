/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:38:44 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/01 16:34:34 by tchartie         ###   ########.fr       */
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
    this->_posX--;
}
