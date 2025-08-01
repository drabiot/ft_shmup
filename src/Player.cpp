/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 00:43:02 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/01 16:15:46 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"
#include "Projectile.hpp"

Player::Player( void ) {
	this->_posX = BASE_X_1;
	this->_posY = BASE_Y_1;
	this->_life = 3;
	this->_maxLife = 3;
	this->_score = 0;
	this->_timeSurvived = 0;
	this->_timer = 0;
	this->_power = 0;
	this->_invincibility = 2;
}

Player::~Player( void ) {}

size_t	Player::getScore( void ) {
	return (this->_score);
}

unsigned long long	Player::getTimeSurvived( void ) {
	return (this->_timeSurvived);
}

size_t	Player::getTimer( void ) {
	return (this->_timer);
}

size_t	Player::getPower( void ) {
	return (this->_power);
}

size_t	Player::getInvincibility( void ) {
	return (this->_invincibility);
}

void	Player::setScore( size_t value ) {
	this->_score += value;
}

void	Player::setInvincibility( size_t value ) {
	this->_invincibility = value;
}

void	Player::updateTime( void ) {
	this->_timeSurvived++;
	if (static_cast<int>(this->_timeSurvived * 0.016) >= 1) {
		this->_timeSurvived = 0;
		this->updateTimer();
	}
}

void	Player::updateTimer( void ) {
	this->_timer++;
	this->updatePower();
}

void	Player::updatePower( void ) {
	if (this->_power < 5)
		this->_power++;
}

void	Player::rebootPower( void ) {
	this->_power = 0;
}

void	Player::updateInvincibility( void ) {
	if (this->_invincibility > 0)
		this->_invincibility--;
}

void	Player::getPendingRocket( std::vector<Projectile> &out ) {
	out.insert(out.end(), this->_pendingRocket.begin(), this->_pendingRocket.end());
    this->_pendingRocket.clear();
}

void	Player::attack( void ) {
	Projectile rocket(getPosX(), getPosY(), getPower());

	this->_pendingRocket.push_back(rocket);
	this->rebootPower();
}
