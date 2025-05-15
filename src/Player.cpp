/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:43:02 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 20:23:13 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player( void ) {
	this->_posX = 30;
	this->_posY = 20;
	this->_life = 3;
	this->_score = 0;
	this->_timeSurvived = std::clock();
}

Player::~Player( void ) {}

size_t	Player::getScore( void ) {
	return (this->_score);
}

std::clock_t	Player::getTimeSurvived( void ) {
	return (this->_timeSurvived);
}

void	Player::updateScore( void ) {}
