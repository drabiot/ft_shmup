/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:43:02 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/20 23:37:38 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player( void ) {
	this->_posX = 30;
	this->_posY = 20;
	this->_life = 3;
	this->_maxLife = 3;
	this->_score = 0;
	this->_timeSurvived = 0;
}

Player::~Player( void ) {}

size_t	Player::getScore( void ) {
	return (this->_score);
}

unsigned long long	Player::getTimeSurvived( void ) {
	return (this->_timeSurvived);
}

void	Player::updateScore( void ) {}

void	Player::updateTime( void ) {
	this->_timeSurvived++;
	//if (this->_timeSurvived > 1600000)
	//	this->_timeSurvived = 0;
}
