/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:00:21 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/14 09:00:19 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <iostream>
# include <string>
# include <ncurses.h>
# include <unistd.h>

# include "color.hpp"

# define AND	<<
# define PRINT	std::cout AND
# define ERROR	std::cerr AND
# define NLINE	PRINT std::endl
# define ENDL	AND std::endl
# define CENDL	AND BASE_COLOR ENDL
# define TAB	"\t"

typedef std::string str;

# define cref(type) const type &
# define ref(type) type &

# define HEIGHT	40
# define LENGTH (40 + 20) * 2.5
# define FRAME_DELAY 16000

class Entity {
	public:
		Entity( void );
		virtual ~Entity( void );

		size_t	getPosX( void );
		size_t	getPosY( void );
		size_t	getLife( void );

		void	setPosX( size_t newX );
		void	setPosY( size_t newY );
		void	setLife( size_t newLife );
	protected:
		size_t	_posX;
		size_t	_posY;
		size_t	_life;
};

#endif //ENTITY_HPP

