/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Projectile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:12 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/27 17:56:51 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECTILE_HPP
# define PROJECTILE_HPP

# include "Entity.hpp"

class	Projectile : public Entity {
	public:
		Projectile( size_t x, size_t y, size_t dmUp );
		~Projectile( void );
    private:
        size_t _damage;
};

#endif //PROJECTILE_HPP

