/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projectile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:46 by tchartie          #+#    #+#             */
/*   Updated: 2025/06/25 23:49:39 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Projectile.hpp"

Projectile::Projectile( size_t x, size_t y, size_t dmUp ) {
    this->_posX = x + 1;
	this->_posY = y;
	this->_life = 1;
	this->_maxLife = 1;
    this->_damage = dmUp;
	if (this->_damage == 0)
		this->_damage = 1;
}

Projectile::~Projectile( void ) {}

size_t	Projectile::getDamage( void ) {
	return (this->_damage);
}
