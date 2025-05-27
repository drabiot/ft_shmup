/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:42:20 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/27 17:57:38 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.hpp"

Entity::Entity( void ) {
	this->_posX = 0;
	this->_posY = 0;
	this->_life = 0;
}

Entity::~Entity( void ) {}

size_t	Entity::getPosX( void ) {
	return (this->_posX);
}

size_t	Entity::getPosY( void ) {
	return (this->_posY);
}

size_t	Entity::getLife( void ) {
	return (this->_life);
}

size_t	Entity::getMaxLife( void ) {
	return (this->_maxLife);
}

void	Entity::setPosX( size_t newX ) {
	this->_posX = newX;
}

void	Entity::setPosY( size_t newY ) {
	this->_posY = newY;
}

void	Entity::setLife( size_t newLife ) {
	this->_life = newLife;
}

void	Entity::setMaxLife( size_t newMaxLife ) {
	this->_maxLife = newMaxLife;
}
