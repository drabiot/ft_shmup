/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:08:31 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 18:34:40 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <ncursesw/ncurses.h>
# include <unistd.h>
# include <cstdlib>
# include <ctime>

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

# define HEIGHT			40
# define LENGTH 		(40 + 20) * 2.5
# define WIDTH			300
# define FRAME_DELAY	16000
# define M_PI			3.14159265

# define SPACE          ' '
# define BASE           '.'
# define DETAIL         '%'
# define FINE           '*'
# define FIRST          '@'

double  ft_sin( double x );

#endif //UTILS_HPP
