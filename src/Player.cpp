/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:43:02 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 01:02:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player( void ) {
	this->_posX = 30;
	this->_posY = 20;
	this->_life = 3;
	this->_score = 0;
	this->_timeSurvived = 0;
}

Player::~Player( void ) {}

size_t	Player::getScore( void ) {
	return (this->_score);
}

size_t	Player::getTimeSurvived( void ) {
	return (this->_timeSurvived);
}

void	Player::updateScore( void ) {}

void	Player::updateTimeSurvived( void ) {
	(this->_timeSurvived)++;
}

