/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projectile.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:14:46 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/27 17:21:54 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Projectile.hpp"

Projectile::Projectile( size_t x, size_t y, size_t dmUp ) {
    this->_posX = x + 1;
	this->_posY = y;
	this->_life = 1;
	this->_maxLife = 1;
    this->_damage = 1 + dmUp;
}

Projectile::~Projectile( void ) {

}